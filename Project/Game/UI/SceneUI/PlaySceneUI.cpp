/**
 *
 * @file PlaySceneUI.cpp
 *
 * @brief �v���C�V�[���Ŏg�p����UI�A�摜�N���X�̃\�[�X�t�@�C��
 *
 * @author Kato Yuki
 *
 * @date 2024/1/16
 *
 */
#include "pch.h"
#include "PlaySceneUI.h"

#include "Game/MyLibrary/CommonResource/GameResource.h"
#include "Game/Scene//PlayScene.h"
#include "Game/Player/Player.h"
#include "Game/Camera/SceneCamera/GameCamera.h"
#include "Game/UI/OperatableUI.h"

using namespace DirectX;

//------------------------------------------------------------------
/**
 * @brief �R���X�g���N�^
 *
 * @param playScene�F�v���C�V�[���̃|�C���^
 * @param player   �F�v���C���[�̃|�C���^
 * @param camera   �F�J�����̃|�C���^
 */
PlaySceneUI::PlaySceneUI(PlayScene* playScene, Player* player, GameCamera* camera)
	: m_playScene(playScene)
	, m_player(player)
	, m_camera(camera)
	, m_moveButtonUp(nullptr)
	, m_moveButtonDown(nullptr)
	, m_moveButtonRight(nullptr)
	, m_moveButtonLeft(nullptr)
	, m_jumpButton(nullptr)
	, m_camRotButtonW(nullptr)
	, m_camRotButtonS(nullptr)
	, m_camRotButtonA(nullptr)
	, m_camRotButtonD(nullptr)
	, m_dimensionButton(nullptr)
	, m_overLookingButton(nullptr)
{
}

//------------------------------------------------------------------
/**
 * @brief �f�X�g���N�^
 */
PlaySceneUI::~PlaySceneUI()
{
}

//------------------------------------------------------------------
/**
 * @brief ������
 *
 * @param  �Ȃ�
 * @return �Ȃ�
 */
void PlaySceneUI::Initialize()
{
	// UI�쐬
	CreateUI(KT::UI::PROPERTIE_PLAY);
	// ����UI�擾
	m_moveButtonUp      = GetUI(KT::UI::PLAY_MOVE_BUTTON_UP);
	m_moveButtonDown    = GetUI(KT::UI::PLAY_MOVE_BUTTON_DOWN);
	m_moveButtonRight   = GetUI(KT::UI::PLAY_MOVE_BUTTON_RIGHT);
	m_moveButtonLeft    = GetUI(KT::UI::PLAY_MOVE_BUTTON_LEFT);
	m_jumpButton        = GetUI(KT::UI::PLAY_JUMP_BUTTON);
	m_camRotButtonW     = GetUI(KT::UI::PLAY_CAMROT_BUTTON_W);
	m_camRotButtonS     = GetUI(KT::UI::PLAY_CAMROT_BUTTON_S);
	m_camRotButtonA     = GetUI(KT::UI::PLAY_CAMROT_BUTTON_A);
	m_camRotButtonD     = GetUI(KT::UI::PLAY_CAMROT_BUTTON_D);
	m_dimensionButton   = GetUI(KT::UI::PLAY_DIMESION_BUTTON);
	m_overLookingButton = GetUI(KT::UI::PLAY_OVERLOOKING_BUTTON);

	// ���g��UI�}�l�[�W���[�֓o�^
	SetUIManagerSceneUI();
}

//------------------------------------------------------------------
/**
 * @brief �X�V
 *
 * @param  �Ȃ�
 * @return �Ȃ�
 */
void PlaySceneUI::Update()
{
	// �v���C�V�[���̏�Ԏ擾
	PlayScene::GameState state = m_playScene->GetGameState();

	// ��Ԃ��ƂɍX�V������؂�ւ�
	if (state == PlayScene::GameState::PLAY)
	{
		PlayUpdate();
	}
	else if (state == PlayScene::GameState::OVER_LOOK)
	{
		OverLookingUpdate();
	}
}

//------------------------------------------------------------------
/**
 * @brief �v���C���̍X�V����
 *
 * @param  �Ȃ�
 * @return �Ȃ�
 */
void PlaySceneUI::PlayUpdate()
{
	using namespace KT::UI;

	// �t�F�[�h�擾
	Fade* fade = GameResource::GetInstance()->GetFade();

	// �ݒ�ɕK�v�ȏ��擾
	bool is2D        = m_playScene->Is2D();              // 2D��Ԃ�
	bool is3D        = !is2D;                            // 3D��Ԃ�
	bool isTopDown   = m_playScene->IsTopDown();         // �����낵���_��
	bool is2DTopDown = is2D && isTopDown;                // 2D�����낵���_��
	bool is3DTopDown = is3D && isTopDown;                // 3D�����낵���_��
	bool is3DSide    = is3D && !isTopDown;               // 3D�����_��
	bool isJump      = m_player->IsJump();               // �W�����v�\��
	bool onGround    = m_player->OnGround();             // ���̏�ɂ��邩
	bool isOperation = m_playScene->IsOperationCamera(); // �J�����؂�ւ��A���쒆��
	bool isFade      = fade->IsFade();                   // �t�F�[�h����

	// �ړ��{�^��
	m_moveButtonUp->ActiveStateUpdate(!isFade && (is3D || is2DTopDown) && !isOperation);
	m_moveButtonDown->ActiveStateUpdate(!isFade && (is3D || is2DTopDown) && !isOperation);
	m_moveButtonRight->ActiveStateUpdate(!isFade && !isOperation);
	m_moveButtonLeft->ActiveStateUpdate(!isFade && !isOperation);
	// �W�����v�{�^��
	m_jumpButton->ActiveStateUpdate(!isFade && (isJump && !isOperation));
	// �J������]�{�^��
	m_camRotButtonW->ActiveStateUpdate(!isFade && (is3DSide && onGround && !isOperation));
	m_camRotButtonS->ActiveStateUpdate(!isFade && (is3DTopDown && onGround && !isOperation));
	m_camRotButtonA->ActiveStateUpdate(!isFade && (is3D && onGround && !isOperation));
	m_camRotButtonD->ActiveStateUpdate(!isFade && (is3D && onGround && !isOperation));
	// �����؂�ւ��{�^��
	m_dimensionButton->ActiveStateUpdate(!isFade && (onGround && !isOperation));
	// ���n���{�^��
	m_overLookingButton->ActiveStateUpdate(!isFade && (onGround && !isOperation));

	// ���͏�Ԃ̍X�V
	m_moveButtonUp->PushStateUpdate();
	m_moveButtonDown->PushStateUpdate();
	m_moveButtonRight->PushStateUpdate();
	m_moveButtonLeft->PushStateUpdate();
}

//------------------------------------------------------------------
/**
 * @brief ���n�����̍X�V����
 *
 * @param  �Ȃ�
 * @return �Ȃ�
 */
void PlaySceneUI::OverLookingUpdate()
{
	using namespace KT::UI;

	// �ݒ�ɕK�v�ȏ��擾
	bool is3D = !m_playScene->Is2D();                    // 2D��Ԃ�
	bool isOperation = m_playScene->IsOperationCamera(); // �J�����؂�ւ��A���쒆��

	// ��]�{�^��
	m_camRotButtonW->ActiveStateUpdate(!isOperation);
	m_camRotButtonS->ActiveStateUpdate(!isOperation);
	m_camRotButtonA->ActiveStateUpdate(!isOperation);
	m_camRotButtonD->ActiveStateUpdate(!isOperation);
	m_camRotButtonW->PushStateUpdate();
	m_camRotButtonS->PushStateUpdate();
	m_camRotButtonA->PushStateUpdate();
	m_camRotButtonD->PushStateUpdate();
	// ���n���{�^��
	m_overLookingButton->ActiveStateUpdate(!isOperation);
	// �J�����ړ��{�^���̍X�V
	if(is3D)
	{
		m_moveButtonUp->ActiveStateUpdate(!isOperation);
		m_moveButtonDown->ActiveStateUpdate(!isOperation);
		m_moveButtonUp->PushStateUpdate();
		m_moveButtonDown->PushStateUpdate();
	}
}

//------------------------------------------------------------------
/**
 * @brief �J�n���A�j���[�V�����X�L�b�vUI�\��
 *
 * @param  �Ȃ�
 * @return �Ȃ�
 */
void PlaySceneUI::ShowSkipUI()
{
	// �v���C��Ԃ�UI��o�^
	AddUIManager(TAG_START_ANIMATION);
}

//------------------------------------------------------------------
/**
 * @brief �J�n���A�j���[�V��������v���C��Ԃ�
 *
 * @param  �Ȃ�
 * @return �Ȃ�
 */
void PlaySceneUI::ChangeStateAnimationToPlay()
{
	DeleteUIManager(TAG_START_ANIMATION);
	AddUIManager(TAG_PLAY_ALWAYS);
	AddUIManager(TAG_PLAY_STATE);
}

//------------------------------------------------------------------
/**
 * @brief ���j���[����v���C��Ԃ֐ؑ�
 *
 * @param  �Ȃ�
 * @return �Ȃ�
 */
void PlaySceneUI::ChangeStateMenuToPlay()
{
	// �v���C��Ԃ�UI��o�^
	AddUIManager(TAG_PLAY_ALWAYS);
	AddUIManager(TAG_PLAY_STATE);
}

//------------------------------------------------------------------
/**
 * @brief ���j���[���猩�n����Ԃ֐ؑ�
 *
 * @param  �Ȃ�
 * @return �Ȃ�
 */
void PlaySceneUI::ChangeStateMenuToOverLooking()
{
	// �v���C��Ԃ�UI��o�^
	AddUIManager(TAG_PLAY_ALWAYS);
	AddUIManager(GetOverLookingKey(m_playScene->Is2D()));
}

 //------------------------------------------------------------------
 /**
  * @brief �v���C���猩�n����Ԃ֐ؑ�
  *
  * @param  �Ȃ�
  * @return �Ȃ�
  */
void PlaySceneUI::ChangeStatePlayToOverLooking()
{
	// �v���C��Ԃ�UI�̓o�^������
	DeleteUIManager(TAG_PLAY_STATE);
	// ���n����Ԃ�UI��o�^
	AddUIManager(GetOverLookingKey(m_playScene->Is2D()));
}

 //------------------------------------------------------------------
 /**
  * @brief ���n������v���C��Ԃ֐ؑ�
  *
  * @param  �Ȃ�
  * @return �Ȃ�
  */
void PlaySceneUI::ChangeStateOverLookingToPlay()
{
	// ���n����Ԃ�UI�̓o�^������
	DeleteUIManager(GetOverLookingKey(m_playScene->Is2D()));
	// �v���C��Ԃ�UI��o�^
	AddUIManager(TAG_PLAY_STATE);
}

//------------------------------------------------------------------
/**
 * @brief ���n����Ԃ̃L�[���擾����
 *
 * @param  is2D  �F2D��Ԃ�
 * @return string�F���n�����UI�̓o�^�p�L�[
 */
std::string PlaySceneUI::GetOverLookingKey(bool is2D)
{
	// �������m�F
	std::string key;
	if (is2D) key = TAG_OVER_LOOKING_STATE_2D;
	else      key = TAG_OVER_LOOKING_STATE_3D;

	return key;
}