/**
 *
 * @file ResultScene.h
 *
 * @brief ���U���g�V�[����\���N���X�̃w�b�_�[�t�@�C��
 *
 * @author Kato Yuki
 *
 * @date 2023/11/8
 *
 */
#include "pch.h"
#include "ResultScene.h"
#include "Game/MyLibrary/CommonResource/GameResource.h"
#include "Game/MyLibrary/GameParameter/GameParameter.h"
#include "Game/MyLibrary/Utility/MyUtility.h"
#include "Game/Scene/SceneShareData.h"
#include "Game/Scene/StageSelectScene.h"
#include "Game/Camera/Camera.h"
#include "Game/Camera/CameraProjection.h"
#include "Game/Stage/Stage.h"
#include "Game/Stage/StageData.h"
#include "Game/SkyDome/SkyDome.h"
#include "Game/Player/Player.h"
#include "Game/Block/BlockFactory.h"
#include "Game/Block/Block.h"
#include "Game/UI/SceneUI/ResultSceneUI.h"

using namespace DirectX;

//------------------------------------------------------------------
/**
 * @brief �R���X�g���N�^
 *
 * @param sceneManager�F�V�[���}�l�[�W���[�̃|�C���^
 */
ResultScene::ResultScene(SceneManager* sceneManager)
	: m_sceneManager(sceneManager)
	, m_camera(nullptr)
	, m_block(nullptr)
	, m_skyDome(nullptr)
	, m_player(nullptr)
	, m_ui(nullptr)
	, m_nextMode(NextMode::NEXT)
	, m_stageNum(0)
	, m_currentStageNumber(0)
{
}

//------------------------------------------------------------------
/**
 * @brief �f�X�g���N�^
 */
ResultScene::~ResultScene()
{
}

//------------------------------------------------------------------
/**
 * @brief ������
 *
 * @param  �Ȃ�
 * @return �Ȃ�
 */
void ResultScene::Initialize()
{
	// �e�탊�\�[�X�擾
	GameResource*    gameResource    = GameResource::GetInstance();
	InputManager*    inputManager    = gameResource->GetInputManager();
	StageManager*    stageManager    = gameResource->GetStageManager();
	ResourceManager* resourceManager = gameResource->GetResourceManager();

	// �X�e�[�W���擾
	m_stageNum = stageManager->GetStageNum();
	// ���݂̃X�e�[�W�ԍ��擾
	m_currentStageNumber = m_sceneManager->GetSceneShareData()->GetSelectStageNumber();
	// �g�p����L�[�̓o�^
	inputManager->AddKey({ Keyboard::Keys::Up, Keyboard::Keys::Down, Keyboard::Keys::Enter });

	// ��ʔ�v�Z
	RECT  screen = gameResource->GetDeviceResources()->GetOutputSize();
	float aspectRatio = static_cast<float>(screen.right) / static_cast<float>(screen.bottom);
	// �J�����쐬
	m_camera = std::make_unique<Camera>(aspectRatio);
	m_camera->SetTargetPosition(CAMERA_TARGET_POSITION);
	m_camera->SetEyePosition(CAMERA_EYE_POSITION);
	m_camera->CreateViewMatrix();
	m_camera->SetProjectionMatrix(CameraProjection::CreatePerspectiveProjection(aspectRatio));
	// �u���b�N�쐬
	m_block = BlockFactory::CreateBlock(KT::Block::Type::GOAL, GOAL_BLOCK_POSITION);
	m_block->Initialize();
	// �X�J�C�h�[���쐬 
	// �X�e�[�W�̒��S���ʒu�ɐݒ�
	m_skyDome = std::make_unique<SkyDome>(SimpleMath::Vector3::Zero);
	m_skyDome->SetRotationSpeed(SKY_DOME_ROTATION_SPEED);
	// �v���C���[�쐬
	m_player = std::make_unique<Player>(PLAYER_POSITION);
	m_player->Initialize();
	m_player->TurnHeading(m_camera->GetTargetPosition() + SimpleMath::Vector3::Transform(m_camera->GetEyePosition(), m_camera->GetRotation()) - m_player->GetPosition());
	// UI�쐬
	m_ui = std::make_unique<ResultSceneUI>(this);
	m_ui->Initialize();

	// �Ō�̃X�e�[�W�Ȃ�ŏ��ɑI������Ă��郁�j���[��ς���
	if (IsEndStageNumber()) m_nextMode = NextMode::STAGE_SELECT;

	// BGM�𗬂�
	resourceManager->PlaySound(KT::Sound::BGM, KT::Sound::BGMNumber::XACT_WAVEBANK_BGM_RESULT);
}

//------------------------------------------------------------------
/**
 * @brief �X�V
 *
 * @param  �Ȃ�
 * @return �Ȃ�
 */
void ResultScene::Update()
{
	// �e�탊�\�[�X�擾
	GameResource*    gameResource    = GameResource::GetInstance();
	InputManager*    inputManager    = gameResource->GetInputManager();
	ResourceManager* resourceManager = gameResource->GetResourceManager();
	EffectManager*   effectManager   = gameResource->GetEffectManager();

	// �G���^�[�L�[�������ꂽ��
	if (inputManager->GetKey(Keyboard::Keys::Enter).press)
	{
		// SE�𗬂�
		resourceManager->PlaySound(KT::Sound::SE, KT::Sound::SENumber::XACT_WAVEBANK_SE_DECISION);
		// �V�[���J��
		ChangeScene();
	}

	// �Ō�̃X�e�[�W�ȊO��
	if (!IsEndStageNumber())
	{
		// ���j���[�I��
		KT::MyUtility::MenuSelect(
			inputManager->GetKey(Keyboard::Keys::Up).press, 
			inputManager->GetKey(Keyboard::Keys::Down).press,
			m_nextMode);
		// UI�̑I������
		m_ui->Select(static_cast<int>(m_nextMode));
	}

	// �X�J�C�h�[���X�V
	m_skyDome->Update();
	// �v���C���[�X�V
	m_player->Update();
	// �G�t�F�N�g�X�V
	effectManager->Update();
}

//------------------------------------------------------------------
/**
 * @brief �`��
 *
 * @param  �Ȃ�
 * @return �Ȃ�
 */
void ResultScene::Render()
{
	// �e�탊�\�[�X�󂯎��
	GameResource*     gameResource  = GameResource::GetInstance();
	EffectManager*    effectManager = gameResource->GetEffectManager();
	Imase::DebugFont* debugFont     = gameResource->GetDebugFont();

	debugFont->AddString(0, L"���U���g�V�[��");

	// �r���[�A�ˉe�s��󂯎��
	SimpleMath::Matrix view, projection;
	view       = m_camera->GetViewMatrix();
	projection = m_camera->GetProjectionMatrix();

	// �X�J�C�h�[���`��
	m_skyDome->Render(view, projection);
	// �u���b�N�`��
	m_block->Render(view, projection);
	// �v���C���[�`��
	m_player->Render(view, projection);

	// �J�����ʒu�A�����_�A���̌����擾
	SimpleMath::Vector3 eye, target, up;
	eye    = m_camera->GetTargetPosition() + SimpleMath::Vector3::Transform(m_camera->GetEyePosition(), m_camera->GetRotation());
	target = m_camera->GetTargetPosition();
	up     = m_camera->GetUpVector();

	// �G�t�F�N�g�`��
	effectManager->Render(view, projection, eye, target, up);

	// �f�o�b�O
	int num = static_cast<int>(m_nextMode);
	if     (num == 0) debugFont->AddString(0, L"NEXT");
	else if(num == 1) debugFont->AddString(0, L"STAGE_SELECT");
}

//------------------------------------------------------------------
/**
 * @brief �㏈��
 *
 * @param  �Ȃ�
 * @return �Ȃ�
 */
void ResultScene::Finalize()
{
}

//------------------------------------------------------------------
/**
 * @brief �V�[���؂�ւ�
 *
 * @param  �Ȃ�
 * @return �Ȃ�
 */
void ResultScene::ChangeScene()
{
	switch (m_nextMode)
	{
	// ���̃X�e�[�W��
	case ResultScene::NextMode::NEXT:
	{		
		// �X�e�[�W�ԍ�����i�߂�
		m_currentStageNumber++;
		// �X�e�[�W�ԍ���ݒ�
		m_sceneManager->GetSceneShareData()->SetSelectStageNumber(m_currentStageNumber);
		// ���̃V�[�����v���C�V�[����
		m_sceneManager->SetNextScene<PlayScene>();
		break;
	}
	// �Z���N�g�V�[����
	case ResultScene::NextMode::STAGE_SELECT:
		m_sceneManager->SetNextScene<StageSelectScene>();
		break;
	// ��O
	case ResultScene::NextMode::COUNT:
	default:
		assert(false && "���U���g�V�[���̑J�ڐ惂�[�h�������ł�");
		break;
	}
}

//------------------------------------------------------------------
/**
 * @brief �Ō�̃X�e�[�W���ǂ���
 *
 * @param �Ȃ�
 * @return true �F�Ō�̃X�e�[�W
 * @return false�F�Ō�̃X�e�[�W�łȂ�
 */
bool ResultScene::IsEndStageNumber()
{
	return m_stageNum == m_currentStageNumber;
}

//------------------------------------------------------------------
/**
 * @brief �J�ڐ惂�[�h�̎擾
 *
 * @param  �Ȃ�
 * @return NextMode�F���݂̑J�ڐ惂�[�h
 */
ResultScene::NextMode ResultScene::GetNextMode() const
{
	return m_nextMode;
}