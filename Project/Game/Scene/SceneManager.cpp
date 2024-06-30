/**
 *
 * @file SceneManager.cpp
 *
 * @brief �V�[���Ǘ��N���X�̃\�[�X�t�@�C��
 *
 * @author Kato Yuki
 *
 * @date 2023/11/8
 *
 */
#include "pch.h"
#include "SceneManager.h"
#include "Game/Scene/IScene.h"
#include "Game/Scene/TitleScene.h"
#include "Game/Scene/StageSelectScene.h"
#include "Game/Scene/PlayScene.h"
#include "Game/Scene/ResultScene.h"
#include "Game/MyLibrary/CommonResource/GameResource.h"
#include "Game/Scene/SceneShareData.h"


//------------------------------------------------------------------
/**
 * @brief �R���X�g���N�^
 *
 * @param �Ȃ�
 */
SceneManager::SceneManager()
	: m_currentScene(nullptr)
	, m_nextScene(nullptr)
	, m_fade(nullptr)
	, m_sceneShareData(nullptr)
{
}

//------------------------------------------------------------------
/**
 * @brief �f�X�g���N�^
 */
SceneManager::~SceneManager()
{
	Finalize();
}

//------------------------------------------------------------------
/**
 * @brief ������
 *
 * @param  �Ȃ�
 * @return �Ȃ�
 */
void SceneManager::Initialize()
{
	// �Q�[�����\�[�X�擾
	GameResource* gameResource = GameResource::GetInstance();
	// �t�F�[�h�擾
	m_fade = gameResource->GetFade();
	// �N���V�[���̐ݒ�A������
	m_currentScene = std::make_unique<TitleScene>(this);
	m_currentScene->Initialize();
	// �V�[�����L�f�[�^�쐬
	m_sceneShareData = std::make_unique<SceneShareData>(this);
}

//------------------------------------------------------------------
/**
 * @brief �X�V
 *
 * @param  �Ȃ�
 * @return �Ȃ�
 */
void SceneManager::Update()
{
	// �V�[����؂�ւ��Ă��悢��
	if (IsChangeScene())
	{
		// �؂�ւ�������
		if (ChangeScene())
		{
			// ���j���[���J���Ă��邩������Ȃ��̂ŕ��Ă���
			m_sceneShareData->GetMenuWindow()->Close();
			// �t�F�[�h�C���X�^�[�g
			m_fade->StartFadeIn();
		}
	}

	// ���݃V�[���̍X�V
	m_currentScene->Update();

	// ���̃V�[�����ݒ肳��Ă�����
	if (m_nextScene)
	{
		// �t�F�[�h�A�E�g�X�^�[�g
		m_fade->StartFadeOut();
	}
}

//------------------------------------------------------------------
/**
 * @brief �`��
 *
 * @param  �Ȃ�
 * @return �Ȃ�
 */
void SceneManager::Render()
{
	// ���݃V�[���̕`��
	m_currentScene->Render();
}

//------------------------------------------------------------------
/**
 * @brief �㏈��
 *
 * @param  �Ȃ�
 * @return �Ȃ�
 */
void SceneManager::Finalize()
{
	m_currentScene.reset();
	m_nextScene.reset();
}

//------------------------------------------------------------------
/**
 * @brief �V�[���̐؂�ւ�
 *
 * @param  �Ȃ�
 * @return true�F�؂�ւ�����
 * @return false�F�؂�ւ���
 */
bool SceneManager::ChangeScene()
{
	assert(m_nextScene && "���̃V�[�����ݒ肳��Ă��܂���");

	// ���݃V�[���폜
	DeleteCurrentScene();
	// �V�[���̐؂�ւ�
	m_currentScene = std::move(m_nextScene);
	// �V�����V�[���̏�����
	m_currentScene->Initialize();
	// ���̃V�[����������
	m_nextScene = nullptr;

	return true;
}

//------------------------------------------------------------------
/**
 * @brief ���݃V�[���̍폜
 *
 * @param  �Ȃ�
 * @return �Ȃ�
 */
void SceneManager::DeleteCurrentScene()
{
	if (m_currentScene)
	{
		// �㏈��
		m_currentScene->Finalize();
		// ���݃V�[���̃��j�[�N�|�C���^�����
		m_currentScene.reset();
		// ��ɂ���
		m_currentScene = nullptr;

		// �Q�[�����\�[�X�擾
		GameResource* gameResource = GameResource::GetInstance();
		// UI�o�^����
		gameResource->GetUIManager()->Clear();
		// �G�t�F�N�g�o�^����
		gameResource->GetEffectManager()->Clear();	
		// �L�[�o�^����
		gameResource->GetInputManager()->Clear();
		// BGM��~
		gameResource->GetResourceManager()->StopSound(KT::Sound::BGM);
	}
}

//------------------------------------------------------------------
/**
 * @brief �V�[����؂�ւ��Ă悢��
 *
 * @param  �Ȃ�
 * @return true�F�؂�ւ��o����
 * @return false�F�؂�ւ��o���Ȃ�
 */
bool SceneManager::IsChangeScene()
{
	// ���̃V�[�����ݒ肳��Ă��邩�t�F�[�h�C���ҋ@��Ԃ�
	return m_nextScene && m_fade->CheckFadeState(Fade::FadeState::FADE_IN_WAIT);
}

//------------------------------------------------------------------
/**
 * @brief �V�[�����L�f�[�^�̎擾
 *
 * @param  �Ȃ�
 * @return SceneShareData�F�V�[�����L�f�[�^�̃|�C���^
 */
SceneShareData* SceneManager::GetSceneShareData() const
{
	return m_sceneShareData.get();
}