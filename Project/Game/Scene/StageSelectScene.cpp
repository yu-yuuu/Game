/**
 *
 * @file StageSelectScene.cpp
 *
 * @brief �X�e�[�W�I���V�[����\���N���X�̃\�[�X�t�@�C��
 *
 * @author Kato Yuki
 *
 * @date 2023/11/8
 *
 */
#include "pch.h"
#include "StageSelectScene.h"
#include "Game/MyLibrary/CommonResource/GameResource.h"
#include "Game/Camera/SceneCamera/StageSelectCamera.h"
#include "Game/Camera/CameraProjection.h"
#include "Game/Camera/State/CameraStateLerpSwitch.h"
#include "Game/Stage/SelectStage.h"
#include "Game/Scene/PlayScene.h"
#include "Game/UI/SceneUI/StageSelectSceneUI.h"
#include "Game/Window/MenuWindow.h"
#include "Game/Scene/SceneShareData.h"
#include "Game/SkyDome/SkyDome.h"

using namespace DirectX;

//------------------------------------------------------------------
/**
 * @brief �R���X�g���N�^
 *
 * @param sceneManager�F�V�[���}�l�[�W���[�̃|�C���^
 */
StageSelectScene::StageSelectScene(SceneManager* sceneManager)
	: m_sceneManager(sceneManager)
	, m_stage(nullptr)
	, m_camera(nullptr)
	, m_ui(nullptr)
	, m_skyDome(nullptr)
	, m_sceneState(SceneState::SELECT)
	, m_stageNumberList()
	, m_stageNumberIndex(0)
	, m_isSwitchFinished(false)
{
}

//------------------------------------------------------------------
/**
 * @brief �f�X�g���N�^
 *
 */
StageSelectScene::~StageSelectScene()
{
}

//------------------------------------------------------------------
/**
 * @brief ������
 *
 * @param  �Ȃ�
 * @return �Ȃ�
 */
void StageSelectScene::Initialize()
{
	// �e�탊�\�[�X�擾
	GameResource*        gameResource    = GameResource::GetInstance();
	StageManager*        stageManager    = gameResource->GetStageManager();
	DX::DeviceResources* deviceResources = gameResource->GetDeviceResources();
	InputManager*        inputManager    = gameResource->GetInputManager();
	ResourceManager*     resourceManager = gameResource->GetResourceManager();

	// �g�p����L�[�̓o�^
	inputManager->AddKey(
		{
			Keyboard::Keys::Up,    Keyboard::Keys::Down,
			Keyboard::Keys::Right, Keyboard::Keys::Left,
			Keyboard::Keys::Enter, Keyboard::Keys::Escape
		}
	);
	
	// ��ʔ���v�Z
	RECT rect = deviceResources->GetOutputSize();
	float aspectRatio = static_cast<float>(rect.right) / static_cast<float>(rect.bottom);

	// �I�����Ă���X�e�[�W�ԍ����擾
	int stageNum = m_sceneManager->GetSceneShareData()->GetSelectStageNumber();
	// �擾�����X�e�[�W�ԍ���v�f�ԍ��֕ϊ�
	m_stageNumberIndex = std::max(stageNum - 1, 0);
	// �X�e�[�W�쐬
	m_stageNumberList = stageManager->GetStageNumberList();
	KT::Stage::Size stageSize = stageManager->GetStageSize(m_stageNumberList[m_stageNumberIndex]);
	m_stage = std::make_unique<SelectStage>(m_stageNumberList[m_stageNumberIndex], stageSize);
	m_stage->Initialize();
	// �J�����쐬
	m_camera = std::make_unique<StageSelectCamera>(this, aspectRatio, stageSize.GetVector3());
	m_camera->InitialCameraSetting();
	// UI�쐬
	m_ui = std::make_unique<StageSelectSceneUI>(this);
	m_ui->Initialize();
	m_ui->SelectTriangleRenderSetting(m_stageNumberIndex == 0, m_stageNumberIndex == m_stageNumberList.size() - 1);
	// �X�J�C�h�[���쐬 
	// �X�e�[�W�̒��S���ʒu�ɐݒ�
	m_skyDome = std::make_unique<SkyDome>(stageSize.GetVector3() * 0.5f);

	// �X�e�[�W�I�����
	m_sceneState = SceneState::SELECT;
	// BGM�𗬂�
	resourceManager->PlaySound(KT::Sound::BGM, KT::Sound::BGMNumber::XACT_WAVEBANK_BGM_SELECT);
}

//------------------------------------------------------------------
/**
 * @brief �X�V
 *
 * @param �Ȃ�
 * @return �Ȃ�
 */
void StageSelectScene::Update()
{
	// �X�V����
	switch (m_sceneState)
	{
	// �X�e�[�W�I��
	case StageSelectScene::SceneState::SELECT: SelectUpdate(); break;
	// ���j���[
	case StageSelectScene::SceneState::MENU:   MenuUpdate();   break;
	// ��O
	default: assert(false && "�X�e�[�W�Z���N�g�V�[����sceneState�������̒l�ł�");break;
	}
}

//------------------------------------------------------------------
/**
 * @brief �`��
 *
 * @param  �Ȃ�
 * @return �Ȃ�
 */
void StageSelectScene::Render()
{
	// �e�탊�\�[�X�󂯎��
	GameResource*     gameResource  = GameResource::GetInstance();
	EffectManager*    effectManager = gameResource->GetEffectManager();

	// �r���[�A�ˉe�s��󂯎��
	SimpleMath::Matrix view, projection;
	view       = m_camera->GetViewMatrix();
	projection = m_camera->GetProjectionMatrix();
	// �X�J�C�h�[���`��
	m_skyDome->Render(view, projection);
	// �X�e�[�W�`��
	m_stage->Render(view, projection);
	// �J�����ʒu�A�����_�A���̌����擾
	SimpleMath::Vector3 eye, target, up;
	eye    = m_camera->GetTargetPosition() + SimpleMath::Vector3::Transform(m_camera->GetEyePosition(), m_camera->GetRotation());
	target = m_camera->GetTargetPosition();
	up     = m_camera->GetUpVector();
	// �G�t�F�N�g�`��
	effectManager->Render(view, projection, eye, target, up);
	// ���j���[�E�B���h�E�`��
	m_sceneManager->GetSceneShareData()->GetMenuWindow()->Render();
}

//------------------------------------------------------------------
/**
 * @brief �㏈��
 *
 * @param  �Ȃ�
 * @return �Ȃ�
 */
void StageSelectScene::Finalize()
{
}

//------------------------------------------------------------------
/**
 * @brief �V�[���؂�ւ�
 *
 * @param  �Ȃ�
 * @return �Ȃ�
 */
void StageSelectScene::ChangeScene()
{
	// ���L�f�[�^�ɑI�������X�e�[�W�ԍ���ݒ肷��
	// ( �v�f�ԍ�����X�e�[�W�ԍ��ɒ������� + 1 )
	m_sceneManager->GetSceneShareData()->SetSelectStageNumber(m_stageNumberIndex + 1);
	// ���̃V�[���Ƀv���C�V�[�����Z�b�g
	m_sceneManager->SetNextScene<PlayScene>();
}

//------------------------------------------------------------------
/**
 * @brief �X�e�[�W�I�����̍X�V����
 *
 * @param  keyList�F���͂��ꂽ�L�[���X�g
 * @return �Ȃ�
 */
void StageSelectScene::SelectUpdate()
{
	// �e�탊�\�[�X�擾
	GameResource*    gameResource    = GameResource::GetInstance();
	InputManager*    inputManager    = gameResource->GetInputManager();
	ResourceManager* resourceManager = gameResource->GetResourceManager();

	// �X�e�[�W�I��
	if(!m_camera->IsOperation()) StageSelect();

	// �V�[���J��
	if (inputManager->GetKey(Keyboard::Keys::Enter).press)
	{
		// SE�𗬂�
		resourceManager->PlaySound(KT::Sound::SE, KT::Sound::SENumber::XACT_WAVEBANK_SE_DECISION);
		ChangeScene();
	}
	// ���j���[��ʂ��J��
	if (inputManager->GetKey(Keyboard::Keys::Escape).press)
	{
		m_sceneManager->GetSceneShareData()->GetMenuWindow()->Open(MenuWindow::OpenScene::SELECT);
		m_sceneState = SceneState::MENU;
		m_ui->DeleteUIManagerAll();
	}

	// �X�V
	m_camera->Update();
	m_stage->Update();
	GameResource::GetInstance()->GetEffectManager()->Update();
	m_skyDome->SetPosition(m_camera->GetTargetPosition());
}

//------------------------------------------------------------------
/**
 * @brief ���j���[�\�����̍X�V����
 *
 * @param  keyList�F���͂��ꂽ�L�[���X�g
 * @return �Ȃ�
 */
void StageSelectScene::MenuUpdate()
{
	// �L�[�}�l�[�W���[�擾
	InputManager* inputManager = GameResource::GetInstance()->GetInputManager();

	// ���j���[���
	if (inputManager->GetKey(Keyboard::Keys::Escape).press)
	{
		m_sceneManager->GetSceneShareData()->GetMenuWindow()->Close();
		m_sceneState = SceneState::SELECT;
		m_ui->AddUIManagerAll();
		m_ui->SelectTriangleRenderSetting(m_stageNumberIndex == 0, m_stageNumberIndex == m_stageNumberList.size() - 1);
	}

	// ���j���[�̍X�V
	m_sceneManager->GetSceneShareData()->GetMenuWindow()->Update();
}

//------------------------------------------------------------------
/**
 * @brief �X�e�[�W�I��
 *
 * @param  key�F���͂��ꂽ�L�[
 * @return �Ȃ�
 */
void StageSelectScene::StageSelect()
{
	// �e�탊�\�[�X�擾
	GameResource*    gameResource    = GameResource::GetInstance();
	InputManager*    inputManager    = gameResource->GetInputManager();

	// �ؑ֊���������
	if (m_isSwitchFinished) 
	{
		StageSwitchComplete();
		m_isSwitchFinished = false;
	}

	// ���͑O��Ԃ�ۑ�
	int afterIndex = m_stageNumberIndex;

	// �㉺�L�[���͂Ő؂�ւ�
	if      (inputManager->GetKey(Keyboard::Keys::Up).press)   m_stageNumberIndex--;
	else if (inputManager->GetKey(Keyboard::Keys::Down).press) m_stageNumberIndex++;
	// �͈͊O�ɍs���Ȃ��悤�ɃN�����v
	m_stageNumberIndex = std::max(0, std::min(m_stageNumberIndex, 
		static_cast<int>(m_stageNumberList.size() - 1)));

	// �ؑւ��Ă������Ȃ�I��
	if (m_stageNumberIndex == afterIndex) return;

	// SE�𗬂�
	gameResource->GetResourceManager()->PlaySound(KT::Sound::SE, KT::Sound::SENumber::XACT_WAVEBANK_SE_MOVECURSOL);	
	// �\������X�e�[�W���X�V
	m_stage->ChangeStageSetting(m_stageNumberIndex);
	// UI���X�V
	m_ui->SelectTriangleRenderSetting(m_stageNumberIndex == 0, m_stageNumberIndex == m_stageNumberList.size() - 1);
	// �J�����̐ݒ�
	SimpleMath::Vector3 stageSize = m_stage->GetNextStageSize().GetVector3();
	SimpleMath::Vector3 basePosition = m_stage->GetNextBasePosition();	
	m_camera->StageSelectSetting(basePosition + stageSize * 0.5f, stageSize);
	// �t���O�𗧂Ă�
	m_isSwitchFinished = true;
}

//------------------------------------------------------------------
/**
 * @brief ���ݑI�����Ă���X�e�[�W�̗v�f�ԍ��擾
 *
 * @param  �Ȃ�
 * @return �Ȃ�
 */
int StageSelectScene::GetSelectIndex()
{
	return m_stageNumberIndex;
}

//------------------------------------------------------------------
/**
 * @brief �X�e�[�W�̐�
 *
 * @param  �Ȃ�
 * @return �Ȃ�
 */
int StageSelectScene::GetStageNum()
{
	return static_cast<int>(m_stageNumberList.size());
}

//------------------------------------------------------------------
/**
 * @brief �X�e�[�W�ؑ֊���������
 *
 * @param  �Ȃ�
 * @return �Ȃ�
 */
void StageSelectScene::StageSwitchComplete()
{
	m_stage->StageSwitchComplete();
}
