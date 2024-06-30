/**
 *
 * @file PlayScene.cpp
 *
 * @brief �v���C�V�[����\���N���X�̃\�[�X�t�@�C��
 *
 * @author Kato Yuki
 *
 * @date 2023/11/8
 *
 */
#include "pch.h"
#include "PlayScene.h"
#include "Game/Scene/SceneManager.h"
#include "Game/Scene/ResultScene.h"

#include "Game/MyLibrary/CommonResource/GameResource.h"
#include "Game/MyLibrary/ResourceManager/ResourceType.h"
#include "Game/MyLibrary/GameParameter/GameParameter.h"
#include "Game/MyLibrary/Utility/MyUtility.h"
#include "Game/Scene/SceneShareData.h"
#include "Game/Stage/PlayStage.h"
#include "Game/Player/Player.h"
#include "Game/UI/SceneUI/PlaySceneUI.h"
#include "Game/SkyDome/SkyDome.h"
#include "Game/Camera/SceneCamera/GameCamera.h"
#include "Game/Camera/State/CameraStateLerpSwitch.h"
#include "Game/MyLibrary/Collision/Collision.h"
#include "Game/MyLibrary/Collision/BoxCollider.h"
#include "Game/MyLibrary/Shader/Shader.h"

using namespace DirectX;

//------------------------------------------------------------------
/**
 * @brief �R���X�g���N�^
 *
 * @param sceneManager�F�X�e�[�W�}�l�[�W���[�ւ̃|�C���^
 */
PlayScene::PlayScene(SceneManager* sceneManager)
	: m_sceneManager(sceneManager)
	, m_stage(nullptr)
	, m_camera(nullptr)
	, m_player(nullptr)
	, m_ui(nullptr)
	, m_skyDome(nullptr)
	, m_gameState(GameState::START)
	, m_beforeMenuState(GameState::START)
	, m_dssStage(nullptr)
	, m_dssPlayerSilhouette(nullptr)
	, m_animationSkipTimer(0.0f)
	, m_isDispSkipUI(false)
	, m_isSwitchFail(false)
{
}

//------------------------------------------------------------------
/**
 * @brief �f�X�g���N�^
 */
PlayScene::~PlayScene()
{
}

//------------------------------------------------------------------
/**
 * @brief ������
 *
 * @param  �Ȃ�
 * @return �Ȃ�
 */
void PlayScene::Initialize()
{
	// �e�탊�\�[�X�擾
	GameResource*         gameResource    = GameResource::GetInstance();
	InputManager*         inputManager    = gameResource->GetInputManager();
	ResourceManager*      resourceManager = gameResource->GetResourceManager();

	// �g�p����L�[�̓o�^
	inputManager->AddKey(
		{
			Keyboard::Keys::Up,    Keyboard::Keys::Down,  Keyboard::Keys::Right, Keyboard::Keys::Left,
			Keyboard::Keys::W,     Keyboard::Keys::A,     Keyboard::Keys::S,     Keyboard::Keys::D,
			Keyboard::Keys::E,     Keyboard::Keys::Space, Keyboard::Keys::Enter, Keyboard::Keys::Escape,
			Keyboard::Keys::F
		}
	);

	// ��ʔ�v�Z
	RECT  screen      = gameResource->GetDeviceResources()->GetOutputSize();
	float aspectRatio = static_cast<float>(screen.right) / static_cast<float>(screen.bottom);
	// �X�e�[�W�쐬�A������
	StageManager* stageManager = GameResource::GetInstance()->GetStageManager();
	int stageNum = m_sceneManager->GetSceneShareData()->GetSelectStageNumber();
	KT::Stage::Size stageSize = stageManager->GetStageSize(stageNum);	
	m_stage = std::make_unique<PlayStage>(stageNum, stageSize);
	m_stage->Initialize();
	// �v���C���[�쐬�A������
	m_player = std::make_unique<Player>(this, m_stage->GetStartPosition());
	m_player->Initialize();
	// �J�����쐬�A�����ݒ�
	m_camera = std::make_unique<GameCamera>(this, aspectRatio, stageSize.GetVector3());
	m_camera->SetPlayerPosition(m_player->GetPosition());
	m_camera->InitialCameraSetting(
		KT::GameParam::LERP_TIME_GAMESTART, 
		SimpleMath::Vector3(0.0f, 5.0f, 0.0f), KT::GameParam::EYE_OFFSET_SIDE,
		m_stage->GetGoalPosition(), m_player->GetPosition()
	);
	// UI�E�摜�쐬
	m_ui = std::make_unique<PlaySceneUI>(this, m_player.get(), m_camera.get());
	// UI��������
	m_ui->Initialize();
	// �X�J�C�h�[���쐬 
	// �X�e�[�W�̒��S���ʒu�ɐݒ�
	m_skyDome = std::make_unique<SkyDome>(stageSize.GetVector3() * 0.5f);
	// �f�v�X�X�e���V���̍쐬
	CreateDepthStancil();
	// �V�F�[�_�[�쐬
	m_playerSilhouetteShader = std::make_unique<Shader<DirectX::VertexPosition>>();
	m_playerSilhouetteShader->CreateData(KT::Shader::PLAYER_SILHOUETTE);
	m_gameStartShader = std::make_unique<Shader<DirectX::VertexPositionTexture>>();
	m_gameStartShader->CreateData(KT::Shader::GAME_START_MASK);

	// BGM�𗬂�
	resourceManager->PlaySound(KT::Sound::BGM, KT::Sound::BGMNumber::XACT_WAVEBANK_BGM_PLAY);
}

//------------------------------------------------------------------
/**
 * @brief �X�V
 *
 * @param  �Ȃ�
 * @return �Ȃ�
 */
void PlayScene::Update()
{
	// �X�V����
	switch (m_gameState)
	{
		// �Q�[���J�n��Ԃ̍X�V����
		case PlayScene::GameState::START:     GameStartUpdate();       break;
		// �Q�[���v���C���̍X�V����
		case PlayScene::GameState::PLAY:      GamePlayUpdate();        break;
		// �X�e�[�W���n�����̍X�V����
		case PlayScene::GameState::OVER_LOOK: GameOverLookingUpdate(); break;
		// ���j���[���̍X�V����
		case PlayScene::GameState::MENU:      GameMenuUpdate();        break;
		
		default:break;
	}
}

//------------------------------------------------------------------
/**
 * @brief �`��
 *
 * @param  �Ȃ�
 * @return �Ȃ�
 */
void PlayScene::Render()
{
	// �e�탊�\�[�X�擾
	GameResource*         gameResource  = GameResource::GetInstance();
	ID3D11DeviceContext1* context       = gameResource->GetDeviceResources()->GetD3DDeviceContext();
	CommonStates*         commonStates  = gameResource->GetCommonStates();
	EffectManager*        effectManager = gameResource->GetEffectManager();

	// �J��������r���[�A�ˉe�s��A�J�����ʒu���擾
	SimpleMath::Matrix  view       = m_camera->GetViewMatrix();
	SimpleMath::Matrix  projection = m_camera->GetProjectionMatrix();
	SimpleMath::Vector3 eye        = m_camera->GetTargetPosition() + SimpleMath::Vector3::Transform(m_camera->GetEyePosition(), m_camera->GetRotation());

	// �X�J�C�h�[���̕`��
	m_skyDome->Render(view, projection);
	// �X�e�[�W�`��
	m_stage->Render(view, projection, eye,
		[&]()
		{
			// �[�x�X�e���V���X�e�[�g�̐ݒ�
			context->OMSetDepthStencilState(m_dssStage.Get(), 0);
		}
	);
	// �G�t�F�N�g�̕`��
	effectManager->Render(view, projection, eye, m_camera->GetTargetPosition(), m_camera->GetUpVector());
	// �v���C���[�̃V���G�b�g�`��
	m_player->RenderSilhouette(view, projection,
		[&]()
		{
			// �[�x�X�e���V���X�e�[�g�̐ݒ�
			context->OMSetDepthStencilState(m_dssPlayerSilhouette.Get(), 1);
			// �s�N�Z���V�F�[�_�[�ݒ�
			context->PSSetShader(m_playerSilhouetteShader->GetPixelShader(), nullptr, 0);
		}
	);
	// �v���C���[�`��
	m_player->Render(view, projection,
		[&]()
		{
			// 3D��
			if (Is3D()) return;
			// �؂�ւ����ȊO��
			if (IsOperationCamera()) return;
			if (IsOperationCompeteCamera()) return;
			// �u���b�N�ɉB���̂Ő[�x�o�b�t�@���g�p���Ȃ�
			context->OMSetDepthStencilState(commonStates->DepthNone(), NULL);
		}
	);
	// �Q�[���J�n���ɂ̓}�X�N���|����
	if(m_gameState == GameState::START) RenderMask();	
	// ���j���[�\��
	m_sceneManager->GetSceneShareData()->GetMenuWindow()->Render();
}

//------------------------------------------------------------------
/**
 * @brief �㏈��
 *
 * @param  �Ȃ�
 * @return �Ȃ�
 */
void PlayScene::Finalize()
{
	m_ui.reset();
	m_player.reset();
	m_camera.reset();
	m_stage.reset();
}

//------------------------------------------------------------------
/**
 * @brief �V�[���̐؂�ւ�
 *
 * @param  �Ȃ�
 * @return �Ȃ�
 */
void PlayScene::ChangeScene()
{
	m_sceneManager->SetNextScene<ResultScene>();
}

//------------------------------------------------------------------
/**
 * @brief �Q�[���J�n���̍X�V����
 *
 * @param  �Ȃ�
 * @return �Ȃ�
 */
void PlayScene::GameStartUpdate()
{	
	// �e�탊�\�[�X�擾
	GameResource*  gameResource = GameResource::GetInstance();
	DX::StepTimer* stepTimer    = gameResource->GetStepTimer();
	InputManager*  inputManager = gameResource->GetInputManager();

	// �J�����X�V
	m_camera->Update();
	// �A�j���[�V�����X�L�b�v�^�C�}�[�X�V
	double elapsedTime = stepTimer->GetElapsedSeconds();
	m_animationSkipTimer += static_cast<float>(elapsedTime);

	// �A�j���[�V�����X�L�b�v
	if (m_animationSkipTimer > ANIMETION_SKIP_TIME)
	{
		// UI���}�l�[�W���[�ɒǉ�
		if (!m_isDispSkipUI)
		{
			m_ui->ShowSkipUI();
			m_isDispSkipUI = true;
		}
		// �A�j���[�V�������X�L�b�v
		if(inputManager->GetKey(Keyboard::Keys::Enter).press)
			m_camera->GetStateLerp()->Skip();
	}

	// �J����������\��
	if (!m_camera->IsOperation())
	{
		// �v���C��Ԃ�
		m_gameState = GameState::PLAY;
		// UI�X�V
		m_ui->ChangeStateAnimationToPlay();
	}
}

//------------------------------------------------------------------
/**
 * @brief �Q�[���v���C���̍X�V����
 *
 * @param  �Ȃ�
 * @return �Ȃ�
 */
void PlayScene::GamePlayUpdate()
{
	// �e�탊�\�[�X�擾
	GameResource*  gameResource  = GameResource::GetInstance();
	EffectManager* effectManager = gameResource->GetEffectManager();
	InputManager*  inputManager  = gameResource->GetInputManager();

	// �؂�ւ�������
	if (IsOperationCompeteCamera())
	{
		// ���s�t���O�������Ă��邩
		if (m_isSwitchFail)
		{
			// ������؂�ւ���
			ChangeDimension(false);
			// ���s�t���O��܂�
			m_isSwitchFail = false;
		}
	}

	// �X�e�[�W�X�V
	m_stage->Update(IsOperationCamera());

	// �J�������؂�ւ������Ă��Ȃ���
	if (!IsOperationCamera())
	{
		// �v���C���[�̈ړ������쐬
		m_player->CreateMoveDirection(m_camera->GetDirection(), m_camera->GetUpVector());
		// �v���C���[�X�V
		m_player->Update();
		// �����蔻��
		CollisionDetection();
	}

	// �v���C���[�̈ʒu���J�����ɓn���A�����_�ɐݒ�
	m_camera->SetPlayerPosition(m_player->GetPosition());
	m_camera->SetTargetPosition(m_player->GetPosition());

	// �J�����X�V
	m_camera->Update();
	// �G�t�F�N�g�X�V
	effectManager->Update();
	
	// �����؂�ւ�
	if (inputManager->GetKey(Keyboard::Keys::E).press) ChangeDimension();
	// �X�e�[�W���n��
	if (inputManager->GetKey(Keyboard::Keys::F).press)
	{
		// ���n����Ԃ�
		m_gameState = GameState::OVER_LOOK;
		m_ui->ChangeStatePlayToOverLooking();
	}
	// ���j���[�\��
	if (inputManager->GetKey(Keyboard::Keys::Escape).press)
	{
		m_sceneManager->GetSceneShareData()->GetMenuWindow()->Open(MenuWindow::OpenScene::PLAY);
		m_beforeMenuState = m_gameState;
		m_gameState = GameState::MENU;
		m_ui->DeleteUIManagerAll();
	}
}

//------------------------------------------------------------------
/**
 * @brief ���n�����̍X�V����
 *
 * @param  �Ȃ�
 * @return �Ȃ�
 */
void PlayScene::GameOverLookingUpdate()
{
	// �L�[�}�l�[�W���[�擾
	InputManager* inputManager = GameResource::GetInstance()->GetInputManager();

	// �v���C��Ԃ�
	if (inputManager->GetKey(Keyboard::Keys::F).press)
	{
		m_gameState = GameState::PLAY;
		m_ui->ChangeStateOverLookingToPlay();
	}
	// ���j���[�\��
	if (inputManager->GetKey(Keyboard::Keys::Escape).press)
	{
		m_sceneManager->GetSceneShareData()->GetMenuWindow()->Open(MenuWindow::OpenScene::PLAY);
		m_beforeMenuState = m_gameState;
		m_gameState = GameState::MENU;
		m_ui->DeleteUIManagerAll();
	}

	// �J�����X�V
	m_camera->Update();
}

//------------------------------------------------------------------
/**
 * @brief ���j���[���̍X�V����
 *
 * @param  �Ȃ�
 * @return �Ȃ�
 */
void PlayScene::GameMenuUpdate()
{
	// �L�[�}�l�[�W���[�擾
	InputManager* inputManager = GameResource::GetInstance()->GetInputManager();

	// ���j���[�\��
	if (inputManager->GetKey(Keyboard::Keys::Escape).press)
	{
		// ���j���[�����
		m_sceneManager->GetSceneShareData()->GetMenuWindow()->Close();
		m_gameState = m_beforeMenuState;
		if      (m_gameState == GameState::PLAY)      m_ui->ChangeStateMenuToPlay();
		else if (m_gameState == GameState::OVER_LOOK) m_ui->ChangeStateMenuToOverLooking();
	}

	// �E�B���h�E�̍X�V
	m_sceneManager->GetSceneShareData()->GetMenuWindow()->Update();
}

//------------------------------------------------------------------
/**
 * @brief �����蔻��
 *
 * @param  �Ȃ�
 * @return �Ȃ�
 */
void PlayScene::CollisionDetection()
{
	// �J�����̕������擾����
	SimpleMath::Vector3 cameraDirection = m_camera->GetDirection();
	// �v���C���[�̃R���C�_�[���擾����
	BoxCollider* playerBox = m_player->GetBoxCollider();
	// ���������u���b�N�擾�p�z��
	std::vector<BoxCollider*> hitObj;

	// ���݂̃X�e�[�W���󂯎��
	KT::Stage::StageData* stage = m_stage->GetStageData();
	for (std::unique_ptr<Block>& block : *stage)
	{
		// �A�N�e�B�u��ԂłȂ��Ȃ��΂�
		if (!block->IsActive()) continue;
		// �����蔻������Ȃ��u���b�N�Ȃ��΂�
		if (block->GetCollisionMode() == KT::Block::CollisionMode::NONE) continue;

		// �u���b�N�ƃv���C���[�̋����𑪂�
		SimpleMath::Vector3 distance = block->GetPosition() - m_player->GetPosition();
		// ���_��������g�p��������̃t���O���쐬����
		SimpleMath::Vector3 flag = KT::MyUtility::InverseFlag(cameraDirection);
		// 2D�Ȃ�K�v�ȕ����݂̂ɂ���
		if (Is2D()) distance *= flag;

		// �u���b�N�Ƃ̋��������ʒu�ȓ��ɂ��邩�m�F����
		if (distance.LengthSquared() > KT::GameParam::COLLISION_RAMGE) continue;

		// �X�e�[�W�u���b�N�̃R���C�_�[���擾
		BoxCollider* blockBox = dynamic_cast<BoxCollider*>(block->GetCollider());

		// �v���C���[�ƃX�e�[�W�u���b�N�œ����蔻������
		if(!Collision::AABBCheck(Is2D(), cameraDirection, *blockBox, *playerBox)) continue;

		// �z��ɕۑ�
		hitObj.push_back(blockBox);
	}

	// ���������I�u�W�F�N�g���v���C���[�ɋ߂����Ń\�[�g
	std::sort(hitObj.begin(), hitObj.end(),
		[&](BoxCollider* lhs, BoxCollider* rhs)
		{
			// �v���C���[�Ƃ̋������v�Z
			SimpleMath::Vector3 distL = lhs->GetPosition() - playerBox->GetPosition();
			SimpleMath::Vector3 distR = rhs->GetPosition() - playerBox->GetPosition();
			// 2D�Ȃ�g��Ȃ�������0�ɂ���
			if (Is2D())
			{
				SimpleMath::Vector3 dir = SimpleMath::Vector3::One - KT::MyUtility::AbsVector(cameraDirection);
				distL *= dir;
				distR *= dir;
			}
			return distL.LengthSquared() < distR.LengthSquared();
		}
	);

	// �Փˎ��������s��
	for(BoxCollider* box : hitObj)
	{
		playerBox->OnCollision(box);
	}
	// �����蔻���̍X�V����
	m_player->CollisionAfterUpdate();
}

//------------------------------------------------------------------
/**
 * @brief ��ʃ}�X�N�`��
 *
 * @param  �Ȃ�
 * @return �Ȃ�
 */
void PlayScene::RenderMask()
{
	// �`��
	m_gameStartShader->RenderQuad(VERTICES[0], VERTICES[1], VERTICES[2], VERTICES[3]);
}

//------------------------------------------------------------------
/**
 * @brief �����̐؂�ւ�
 *
 * @param  isOwnOperation�F�v���C���[�̑��삩
 * @return �Ȃ�
 */
void PlayScene::ChangeDimension(bool isOwnOperation)
{
	// �J�������쒆�Ȃ珈�����s��Ȃ�
	if (IsOperationCamera()) return;
	// �v���C���[���n�ʂ̏�ɂ��Ȃ��Ȃ�s��Ȃ�
	if (!OnGroundPlayer()) return;

	// �J�����̌����擾
	SimpleMath::Vector3 camDir = m_camera->GetDirection();
	// �X�e�[�W�ؑ�
	m_stage->ChangeDimension(m_camera->GetDimension(), camDir);
	// �v���C���[�ؑ�
	m_player->ChangeDimension(m_camera->GetDimension(), !isOwnOperation);
	// �J�����ؑ�
	m_camera->ChangeDimensionSetting();

	// �v���C���[���쎞
	if (isOwnOperation)
	{
		// �ؑւ��������邩�m�F����
		if      (Is3D()) m_isSwitchFail = !CheckChangeTo2DSuccessful(camDir);
		else if (Is2D()) m_isSwitchFail = !CheckChangeTo3DSuccessful();

		// SE�𗬂�
		GameResource::GetInstance()->GetResourceManager()
			->PlaySound(KT::Sound::SE, KT::Sound::SENumber::XACT_WAVEBANK_SE_DIMENSIONCHANGE);
	}
}

//------------------------------------------------------------------
/**
 * @brief �S�[���ɓ���
 *
 * @param  �Ȃ�
 * @return �Ȃ�
 */
void PlayScene::ArrivalGoal()
{
	// �V�[���؂�ւ�
	ChangeScene();
}

//------------------------------------------------------------------
/**
 * @brief �[�x�X�e���V���̍쐬
 *
 * @param  �Ȃ�
 * @return �Ȃ�
 */
void PlayScene::CreateDepthStancil()
{
	// �e�탊�\�[�X�擾
	GameResource*  gameResource = GameResource::GetInstance();
	ID3D11Device1* device       = gameResource->GetDeviceResources()->GetD3DDevice();

	//----------------------------------------------
	// �X�e�[�W�p�̐[�x�X�e���V���̍쐬
	//----------------------------------------------
	D3D11_DEPTH_STENCIL_DESC stageDesc = {};

	stageDesc.DepthEnable                  = TRUE;                             // �[�x�e�X�g���s��
	stageDesc.DepthWriteMask               = D3D11_DEPTH_WRITE_MASK_ALL;
	stageDesc.DepthFunc                    = D3D11_COMPARISON_LESS_EQUAL;
	stageDesc.StencilEnable                = TRUE;                             // �X�e���V���e�X�g���s��
	stageDesc.StencilReadMask              = D3D11_DEFAULT_STENCIL_READ_MASK;
	stageDesc.StencilWriteMask             = D3D11_DEFAULT_STENCIL_WRITE_MASK;
	stageDesc.FrontFace.StencilFunc        = D3D11_COMPARISON_EQUAL;           // �f�[�^ == �Q�ƒl
	stageDesc.FrontFace.StencilPassOp      = D3D11_STENCIL_OP_INCR_SAT;        // �X�e���V���A�[�x�e�X�g�������C���N�������g
	stageDesc.FrontFace.StencilFailOp      = D3D11_STENCIL_OP_KEEP;            // �X�e���V���e�X�g���s���@�������Ȃ�
	stageDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_KEEP;            // �X�e���V���A�[�x�e�X�g���s���@�������Ȃ�
	stageDesc.BackFace                     = stageDesc.FrontFace;              // ���ʂ������ݒ��

	device->CreateDepthStencilState(&stageDesc, m_dssStage.ReleaseAndGetAddressOf());

	//----------------------------------------------
	// �v���C���[�V���G�b�g�̃X�e���V���e�X�g�̐ݒ�
	//----------------------------------------------
	D3D11_DEPTH_STENCIL_DESC silhouetteDesc = {};
	
	silhouetteDesc.DepthEnable                  = FALSE;                            // �[�x�e�X�g���s��Ȃ�
	silhouetteDesc.StencilEnable                = TRUE;                             // �X�e���V���e�X�g���s��
	silhouetteDesc.StencilReadMask              = D3D11_DEFAULT_STENCIL_READ_MASK;
	silhouetteDesc.StencilWriteMask             = D3D11_DEFAULT_STENCIL_WRITE_MASK;
	silhouetteDesc.FrontFace.StencilFunc        = D3D11_COMPARISON_EQUAL;           // �f�[�^ == �Q�ƒl
	silhouetteDesc.FrontFace.StencilPassOp      = D3D11_STENCIL_OP_INCR_SAT;        // �X�e���V���A�[�x�e�X�g�������C���N�������g
	silhouetteDesc.FrontFace.StencilFailOp      = D3D11_STENCIL_OP_KEEP;            // �X�e���V���e�X�g���s���@�������Ȃ�
	silhouetteDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_KEEP;            // �X�e���V���A�[�x�e�X�g���s���@�������Ȃ�
	silhouetteDesc.BackFace                     = silhouetteDesc.FrontFace;         // ���ʂ������ݒ��

	device->CreateDepthStencilState(&silhouetteDesc, m_dssPlayerSilhouette.ReleaseAndGetAddressOf());
}

//------------------------------------------------------------------
/**
 * @brief ���j���[�̕\���E��\��
 *
 * @param  �Ȃ�
 * @return �Ȃ�
 */
void PlayScene::OpenCloseMenu()
{
	m_sceneManager->GetSceneShareData()->
		GetMenuWindow()->OpenClose(MenuWindow::OpenScene::SELECT);
}

//------------------------------------------------------------------
/**
 * @brief 2D��Ԃ�
 *
 * @param  �Ȃ�
 * @return true �F2D���
 * @return false�F2D��Ԃł͂Ȃ�
 */
bool PlayScene::Is2D()
{
	return m_camera->CheckDimension(KT::GameParam::Dimension::_2D);
}

//------------------------------------------------------------------
/**
 * @brief 3D��Ԃ�
 *
 * @param  �Ȃ�
 * @return true �F3D���
 * @return false�F3D��Ԃł͂Ȃ�
 */
bool PlayScene::Is3D()
{
	return m_camera->CheckDimension(KT::GameParam::Dimension::_3D);
}

//------------------------------------------------------------------
/**
 * @brief 2D�ւ̐ؑւ��������邩�m�F
 *
 * @param  camDir�F�J�����̎��_����
 * @return true  �F����
 * @return false �F���s
 */
bool PlayScene::CheckChangeTo2DSuccessful(const DirectX::SimpleMath::Vector3& camDir)
{
	// �G�C���A�X�錾
	using RayHitCol = std::pair<Collider*, float>; // ���C�ɓ��������R���C�_�[

	// �v���C���[�̈ʒu�擾
	SimpleMath::Vector3 playerPos = m_player->GetPosition();
	// �X�e�[�W�T�C�Y�擾
	SimpleMath::Vector3 stageSize = m_stage->GetStageSize().GetVector3();
	// �J�������ǂ̕����Ɍ����Ă��邩�m�F
	SimpleMath::Vector3 sightFlag = KT::MyUtility::AbsVector(camDir);
	bool dirX = sightFlag.x >= 1.0f;
	bool dirY = sightFlag.y >= 1.0f;
	bool dirZ = sightFlag.z >= 1.0f;
	// �v���C���[�̂S���ɑ΂��Ĕ�΂����C���쐬
	SimpleMath::Ray ray[4] = { {camDir, SimpleMath::Vector3::Zero} };
	// ���_�����̃��C�̈ʒu���쐬
	SimpleMath::Vector3 rayPos = playerPos * KT::MyUtility::InverseFlag(camDir) + stageSize * -camDir;
	// �v���C���[�̂S���v�Z�p�̈ʒu
	SimpleMath::Vector3 offset = m_player->GetBoxCollider()->GetExtents() * KT::MyUtility::InverseFlag(camDir);
	// �ʒu���s�b�^���߂���ƃv���C�����炢�̂Ŕ�����
	offset *= 0.5f;

	// ���C�̈ʒu�̍ŏ��ƍő�
	SimpleMath::Vector3 rayPosMin = rayPos - offset;
	SimpleMath::Vector3 rayPosMax = rayPos + offset;
	// ���C�̕����ݒ�
	ray[0].direction = ray[1].direction = ray[2].direction = ray[3].direction = camDir;
	// ���C���΂��ʒu�ݒ�
	if (dirX)
	{
		ray[0].position = { rayPos.x, rayPosMax.y, rayPosMax.z };
		ray[1].position = { rayPos.x, rayPosMax.y, rayPosMin.z };
		ray[2].position = { rayPos.x, rayPosMin.y, rayPosMax.z };
		ray[3].position = { rayPos.x, rayPosMin.y, rayPosMin.z };
	}
	else if (dirY)
	{
		ray[0].position = { rayPosMax.x, rayPos.y, rayPosMax.z };
		ray[1].position = { rayPosMax.x, rayPos.y, rayPosMin.z };
		ray[2].position = { rayPosMin.x, rayPos.y, rayPosMax.z };
		ray[3].position = { rayPosMin.x, rayPos.y, rayPosMin.z };
	}
	else if (dirZ)
	{
		ray[0].position = { rayPosMax.x, rayPosMax.y, rayPos.z };
		ray[1].position = { rayPosMax.x, rayPosMin.y, rayPos.z };
		ray[2].position = { rayPosMin.x, rayPosMax.y, rayPos.z };
		ray[3].position = { rayPosMin.x, rayPosMin.y, rayPos.z };
	}

	// �X�e�[�W�ƃ��C�̔���
	CollisionManager* colManager = GameResource::GetInstance()->GetCollisionManager();	
	// ���������u���b�N�擾�p�z��
	std::vector<RayHitCol> hitRay[4];

	for (int i = 0; i < 4; i++)
	{
		// ���C�ƃu���b�N�̔�����s�����������u���b�N���擾����
		hitRay[i] = colManager->HitRayStage(ray[i], m_stage->GetCollisionStage());

		// ���C�ɃR���C�_�[���������Ă��Ȃ��Ȃ玟��
		if (hitRay[i].empty()) continue;

		// �v���C���[����̋������Z�����Ń\�[�g����
		std::sort(hitRay[i].begin(), hitRay[i].end(),
			[](const RayHitCol& lhs, const RayHitCol& rhs)
			{
				return lhs.second < rhs.second;
			}
		);
		// �v���C���[�ƃ��C�̋��������߂�
		float distance = std::fabsf((playerPos - ray[i].position).Length());
		// ��ԋ߂��u���b�N���擾
		Block* block = dynamic_cast<Block*>(hitRay[i][0].first->GetGameObject());
		// �v���C���[�����߂��ʒu���邩�@����
		// �����K�u���b�N�ɏd�Ȃ��Ă��邩
		if (distance > hitRay[i][0].second || block->GetType() == KT::Block::Type::BRICK)
		{
			// �؂�ւ����s
			return false;
		}
	}
	
	// �؂�ւ�����
	return true;
}

//------------------------------------------------------------------
/**
 * @brief 3D�ւ̐ؑւ��������邩�m�F
 *
 * @param  �Ȃ�
 * @return true �F����
 * @return false�F���s
 */
bool PlayScene::CheckChangeTo3DSuccessful()
{
	return !m_player->IsFailWarp();
}

//------------------------------------------------------------------
/**
 * @brief �����낵���_��
 *
 * @param  �Ȃ�
 * @return true �F�����낵���_
 * @return false�F�����낵���_�ł͂Ȃ�
 */
bool PlayScene::IsTopDown() const
{
	return m_camera->CheckSightType(KT::GameParam::SightType::TOPDOWN);
}

//------------------------------------------------------------------
/**
 * @brief �J�����ؑ֒���
 *
 * @param  �Ȃ�
 * @return true �F�ؑ֒�
 * @return false�F�ؑ֒��ł͂Ȃ�
 */
bool PlayScene::IsOperationCamera() const
{
	return m_camera->CheckCameraState(KT::GameParam::CameraState::OPERATION);
}

//------------------------------------------------------------------
/**
 * @brief �J�����ؑ֊���������
 *
 * @param  �Ȃ�
 * @return true �F�ؑ֊���
 * @return false�F�ؑ֒�
 */
bool PlayScene::IsOperationCompeteCamera() const
{
	return m_camera->CheckCameraState(KT::GameParam::CameraState::OPERATION_COMPLETE);
}

//------------------------------------------------------------------
/**
 * @brief �v���C���[���n�ʂɂ��邩
 *
 * @param  �Ȃ�
 * @return true �F�n�ʂɂ���
 * @return false�F�󒆂ɂ���
 */
bool PlayScene::OnGroundPlayer()
{
	return m_player->OnGround();
}

//------------------------------------------------------------------
/**
 * @brief �Q�[���̏�Ԃ��擾
 *
 * @param  �Ȃ�
 * @return GameState�F���݂̃Q�[���̏��
 */
PlayScene::GameState PlayScene::GetGameState() const
{
	return m_gameState;
}
