/**
 *
 * @file TitleScene.cpp
 *
 * @brief �^�C�g���V�[����\���N���X�̃\�[�X�t�@�C��
 *
 * @author Kato Yuki
 *
 * @date 2023/11/8
 *
 */
#include "pch.h"
#include "TitleScene.h"
#include "Game/MyLibrary/CommonResource/GameResource.h"
#include "Game/Scene/StageSelectScene.h"
#include "Game/UI/SceneUI/TitleSceneUI.h"
#include "Game/Stage/TitleStage.h"
#include "Game/Camera/SceneCamera/TitleCamera.h"
#include "Game/SkyDome/SkyDome.h"
#include "Game/MyLibrary/GameParameter/GameParameter.h"
#include "Game/MyLibrary/Utility/MyUtility.h"

using namespace DirectX;

//------------------------------------------------------------------
/**
 * @brief �R���X�g���N�^
 *
 * @param sceneManager�F�V�[���}�l�[�W���[�̃|�C���^
 */
TitleScene::TitleScene(SceneManager* sceneManager)
	: m_sceneManager(sceneManager)
	, m_stage(nullptr)
	, m_camera(nullptr)
	, m_ui(nullptr)
	, m_skyDome(nullptr)
	, m_titleState(TitleState::PUSH_ENTER)
	, m_nextMode(NextMode::PLAY)
{
}

//------------------------------------------------------------------
/**
 * @brief �f�X�g���N�^
 *
 */
TitleScene::~TitleScene()
{
}

//------------------------------------------------------------------
/**
 * @brief ������
 *
 * @param  �Ȃ�
 * @return �Ȃ�
 */
void TitleScene::Initialize()
{
	// �e�탊�\�[�X�擾
	GameResource*        gameResource    = GameResource::GetInstance();
	DX::DeviceResources* deviceResources = gameResource->GetDeviceResources();
	StageManager*        stageManager    = gameResource->GetStageManager();
	InputManager*        inputManager    = gameResource->GetInputManager();
	ResourceManager*     resourceManager = gameResource->GetResourceManager();

	// �g�p����L�[�̓o�^
	inputManager->AddKey({ Keyboard::Keys::Up, Keyboard::Keys::Down, Keyboard::Keys::Enter });

	// ��ʔ���v�Z
	RECT rect = deviceResources->GetOutputSize();
	float aspectRatio = static_cast<float>(rect.right) / static_cast<float>(rect.bottom);

	// �X�e�[�W�쐬
	int stageNumber = KT::GameParam::TITLE_STAGE_NUM;
	KT::Stage::Size stageSize = stageManager->GetStageSize(stageNumber);
	m_stage = std::make_unique<TitleStage>(this, stageNumber, stageSize);
	m_stage->Initialize();
	// �J�����쐬
	m_camera = std::make_unique<TitleCamera>(this, aspectRatio, stageSize.GetVector3());
	m_camera->InitialCameraSetting();
	// UI�쐬
	m_ui = std::make_unique<TitleSceneUI>(this);
	m_ui->Initialize();
	// �X�J�C�h�[���쐬 
	// �X�e�[�W�̒��S���ʒu�ɐݒ�
	m_skyDome = std::make_unique<SkyDome>(stageSize.GetVector3() * 0.5f);

	// BGM�𗬂�
	resourceManager->PlaySound(KT::Sound::BGM, KT::Sound::BGMNumber::XACT_WAVEBANK_BGM_TITLE);
}

//------------------------------------------------------------------
/**
 * @brief �X�V
 *
 * @param �Ȃ�
 * @return �Ȃ�
 */
void TitleScene::Update()
{
	// �e�탊�\�[�X�擾
	GameResource*     gameResource    = GameResource::GetInstance();
	InputManager*     inputManager    = gameResource->GetInputManager();
	ResourceManager*  resourceManager = gameResource->GetResourceManager();
	Imase::DebugFont* debugFont       = gameResource->GetDebugFont();

	debugFont->AddString(0, L"�^�C�g���V�[��");


	// �^�C�g���̏�Ԃ��؂�ւ�
	if (m_titleState == TitleState::SWITCHING)
	{
		// �J�������؂�ւ����I��������
		if (!m_camera->IsOperation())
		{
			// �^�C�g���̏�Ԃ�؂�ւ���
			ChangeState();
		}
	}
	// �ؑ֏�ԈȊO�̎��ɓ��͑�����s��
	else
	{
		// ���[�h�I��
		if (m_titleState == TitleState::MODE_SELECT)
		{
			KT::MyUtility::MenuSelect(
				inputManager->GetKey(Keyboard::Keys::Up).press,
				inputManager->GetKey(Keyboard::Keys::Down).press,
				m_nextMode);
		}
		// ��ԑJ��
		if (inputManager->GetKey(Keyboard::Keys::Enter).press)
		{
			// SE�𗬂�
			resourceManager->PlaySound(KT::Sound::SE, KT::Sound::SENumber::XACT_WAVEBANK_SE_DECISION);
			ChangeState();
		}
	}
	// �^�C�g���̏�Ԃ����[�h�Z���N�g�ȊO�̎�
	if (m_titleState != TitleState::MODE_SELECT)
	{
		// �J�����X�V
		m_camera->Update();
	}

	// �X�e�[�W�X�V
	m_stage->Update();
}

//------------------------------------------------------------------
/**
 * @brief �`��
 *
 * @param �Ȃ�
 * @return �Ȃ�
 */
void TitleScene::Render()
{
	// �e�탊�\�[�X�擾
	GameResource*         gameResource    = GameResource::GetInstance();
	Imase::DebugFont*     debugFont       = gameResource->GetDebugFont();

	// �r���[�A�ˉe�s����󂯎��
	SimpleMath::Matrix view, projection;
	view       = m_camera->GetViewMatrix();
	projection = m_camera->GetProjectionMatrix();

	// �X�J�C�h�[���̕`��
	m_skyDome->Render(view, projection);
	// �X�e�[�W�̕`��
	m_stage->Render(view, projection);



	//----------------------------------------------
	// �f�o�b�O�\��
	//----------------------------------------------
	switch (m_titleState)
	{
		// �G���^�[
	case TitleScene::TitleState::PUSH_ENTER: debugFont->AddString(0, L"PushEnter"); break;
		// �I���{�^���I��
	case TitleScene::TitleState::MODE_SELECT: debugFont->AddString(0, L"ModeSelect"); break;
	default:
		break;
	}
	switch (m_nextMode)
	{
		// �X�^�[�g�{�^���I��
	case TitleScene::NextMode::PLAY: debugFont->AddString(0, L"PlayMode"); break;
		// �I���{�^���I��
	case TitleScene::NextMode::EXIT: debugFont->AddString(0, L"ExitMode"); break;
	default:
		break;
	}
}

//------------------------------------------------------------------
/**
 * @brief �㏈��
 *
 * @param  �Ȃ�
 * @return �Ȃ�
 */
void TitleScene::Finalize()
{
}

//------------------------------------------------------------------
/**
 * @brief �V�[���؂�ւ�
 *
 * @param  �Ȃ�
 * @return �Ȃ�
 */
void TitleScene::ChangeScene()
{
	switch (m_nextMode)
	{
	// �X�e�[�W�Z���N�g�V�[���֑J��
	case TitleScene::NextMode::PLAY:
		m_sceneManager->SetNextScene<StageSelectScene>();
		break;
	// �Q�[���I��
	case TitleScene::NextMode::EXIT:
		PostQuitMessage(0);
		break;
	default:
		break;
	}
}

//------------------------------------------------------------------
/**
 * @brief �^�C�g���V�[���̏�Ԑ؂�ւ�
 *
 * @param  �Ȃ�
 * @return �Ȃ�
 */
void TitleScene::ChangeState()
{
	switch (m_titleState)
	{
	// �ؑ֏�Ԃ�
	case TitleScene::TitleState::PUSH_ENTER:
		m_titleState = TitleState::SWITCHING;
		m_ui->ChangeStateSwitching();
		// �J�����̎����؂�ւ�
		m_camera->ChangeDimension();
		break;
	// ���[�h�Z���N�g��Ԃ�
	case TitleScene::TitleState::SWITCHING:
		m_titleState = TitleState::MODE_SELECT;
		m_ui->ChangeStateModeSelect();
		break;
	// �v���C�V�[����
	case TitleScene::TitleState::MODE_SELECT:
		ChangeScene();
		break;
	// ��O
	default:
		break;
	}
}

//------------------------------------------------------------------
/**
 * @brief �^�C�g���V�[���̏�Ԏ擾
 *
 * @param  �Ȃ�
 * @return �Ȃ�
 */
TitleScene::TitleState TitleScene::GetTitleState() const
{
	return m_titleState;
}

//------------------------------------------------------------------
/**
 * @brief �^�C�g���V�[���̏�Ԏ擾
 *
 * @param  �Ȃ�
 * @return �Ȃ�
 */
TitleScene::NextMode TitleScene::GetMode() const
{
	return m_nextMode;
}