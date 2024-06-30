/**
 *
 * @file CameraStateOverLooking2D.cpp
 *
 * @brief 2D���n���J�����̃\�[�X�t�@�C��
 *
 * @author Kato Yuki
 *
 * @date 2024/2/28
 *
 */
#include "pch.h"
#include "CameraStateOverLooking2D.h"
#include "Game/Camera/SceneCamera/GameCamera.h"
#include "Game/Camera/State/CameraStateTracking2D.h"
#include "Game/Camera/State/CameraStateLerpSwitch.h"
#include "Game/MyLibrary/CommonResource/GameResource.h"
#include "Game/MyLibrary/GameParameter/GameParameter.h"
#include "Game/MyLibrary/Utility/MyUtility.h"

using namespace DirectX;

//------------------------------------------------------------------
/**
 * @brief �R���X�g���N�^
 *
 * @param gameCamera�F�Q�[���J�����̃|�C���^
 */
CameraStateOverLooking2D::CameraStateOverLooking2D(GameCamera* gameCamera)
	: m_gameCamera(gameCamera)
	, m_limitPosition()
{

}

//------------------------------------------------------------------
/**
 * @brief �f�X�g���N�^
 */
CameraStateOverLooking2D::~CameraStateOverLooking2D()
{
}

//------------------------------------------------------------------
/**
 * @brief ������
 *
 * @param  �Ȃ�
 * @return �Ȃ�
 */
void CameraStateOverLooking2D::Initialize()
{

}

//------------------------------------------------------------------
/**
 * @brief �X�V
 *
 * @param  �Ȃ�
 * @return �Ȃ�
 */
void CameraStateOverLooking2D::Update()
{
	// �e�탊�\�[�X�擾
	GameResource* gameResource = GameResource::GetInstance();
	InputManager* inputManager = gameResource->GetInputManager();

	// �ǐՃJ�����֐؂�ւ�
	if (inputManager->GetKey(Keyboard::Keys::F).press)
	{
		ChangeTrackSetting();
	}

	// �ړ�
	Move();
}

//------------------------------------------------------------------
/**
 * @brief ���쒆�t���O
 *
 * @param  �Ȃ�
 * @return false�F����\
 */
bool CameraStateOverLooking2D::IsOperation()
{
	return false;
}

//------------------------------------------------------------------
/**
 * @brief �J�����O��ړ�
 *
 * @param  �Ȃ�
 * @return �Ȃ�
 */
void CameraStateOverLooking2D::Move()
{
	// �L�[�}�l�[�W���[�擾
	InputManager* inputManager = GameResource::GetInstance()->GetInputManager();

	// �J�����̌����擾
	SimpleMath::Vector3 dir = m_gameCamera->GetDirection();
	// �J�����̓��̌����擾
	SimpleMath::Vector3 up = m_gameCamera->GetUpVector();
	// �E�����x�N�g���v�Z
	SimpleMath::Vector3 moveRight = dir.Cross(up);
	
	// �ړ���
	SimpleMath::Vector3 move;

	// ���
	if      (inputManager->GetKey(Keyboard::Keys::W).down) move += up * MOVE_SPEED;
	// ����
	else if (inputManager->GetKey(Keyboard::Keys::S).down) move -= up * MOVE_SPEED;

	// ����
	if      (inputManager->GetKey(Keyboard::Keys::A).down) move -= moveRight * MOVE_SPEED;
	// �E��
	else if (inputManager->GetKey(Keyboard::Keys::D).down) move += moveRight * MOVE_SPEED;

	// �X�e�[�W���痣��Ȃ��悤�ɐ������|���Ĉړ��ʂ𔽉f������
	m_gameCamera->SetTargetPosition(
		KT::MyUtility::Clamp(
			m_gameCamera->GetTargetPosition() + move,
			SimpleMath::Vector3::Zero, 
			m_limitPosition)
	);
}

//------------------------------------------------------------------
/**
 * @brief �ǐՃJ�����֐؂�ւ��ݒ�
 *
 * @param  �Ȃ�
 * @return �Ȃ�
 */
void CameraStateOverLooking2D::ChangeTrackSetting()
{
	// �ǐՃJ�����擾
	CameraStateTracking2D* track2D = m_gameCamera->GetStateTrack2D();
	// �⊮�J�����擾
	CameraStateLerpSwitch<GameCamera>* stateLerp = m_gameCamera->GetStateLerp();

	// ���_�^�C�v�ɂ���ăJ�����̕`��͈͂�؂�ւ���
	RECT rect;
	if (m_gameCamera->CheckSightType(KT::GameParam::SightType::SIDE))
		rect = CameraProjection::SIDE_RECT;
	else
		rect = CameraProjection::TOPDOWN_RECT;

	// �⊮�ݒ�
	stateLerp->LerpSetting(track2D, KT::GameParam::LERP_TIME_OVERLOOKING);
	stateLerp->TargetSetting(m_gameCamera->GetTargetPosition(), track2D->GetBeforeTarget());
	stateLerp->ProjectionSetting(m_gameCamera->GetProjectionMatrix(),
		CameraProjection::CreateOrthographicProjection(m_gameCamera->GetAspectRatio(), rect));

	// �ǐՃJ�����ݒ�
	m_gameCamera->SetNextCamera(stateLerp);
	m_gameCamera->SetCameraState(KT::GameParam::CameraState::OPERATION);
}

//------------------------------------------------------------------
/**
 * @brief �ړ������ݒ�
 *
 * @param limitPosition�F�ړ������l
 * @return �Ȃ�
 */
void CameraStateOverLooking2D::SetLimitPosition(const DirectX::SimpleMath::Vector3& limitPosition)
{
	m_limitPosition = limitPosition;
}

//------------------------------------------------------------------
/**
 * @brief �����ݒ�
 *
 * @param limit�F�ړ������l
 * @return �Ȃ�
 */
void CameraStateOverLooking2D::InitSetting(const DirectX::SimpleMath::Vector3& limit)
{
	SetLimitPosition(limit);
}
