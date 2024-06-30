/**
 *
 * @file CameraStateOverLooking3D.cpp
 *
 * @brief 3D���n���J�����̃\�[�X�t�@�C��
 *
 * @author Kato Yuki
 *
 * @date 2024/2/26
 *
 */
#include "pch.h"
#include "CameraStateOverLooking3D.h"
#include "Game/Camera/SceneCamera/GameCamera.h"
#include "Game/Camera/State/CameraStateTracking3D.h"
#include "Game/Camera/State/CameraStateLerpSwitch.h"
#include "Game/MyLibrary/CommonResource/GameResource.h"
#include "Game/MyLibrary/GameParameter/GameParameter.h"
#include "Game/MyLibrary/Utility/MyUtility.h"

using namespace DirectX;

//------------------------------------------------------------------
/**
 * @brief �R���X�g���N�^
 *
 * @param gameCamera�F�Q�[���J����
 */
CameraStateOverLooking3D::CameraStateOverLooking3D(GameCamera* gameCamera)
	: m_gameCamera(gameCamera)
	, m_basePosition()
	, m_positionRatio(0.0f)
	, m_horizontalAngle(0.0f)
	, m_verticalAngle(0.0f)
{

}

//------------------------------------------------------------------
/**
 * @brief �f�X�g���N�^
 */
CameraStateOverLooking3D::~CameraStateOverLooking3D()
{
}

//------------------------------------------------------------------
/**
 * @brief ������
 *
 * @param  �Ȃ�
 * @return �Ȃ�
 */
void CameraStateOverLooking3D::Initialize()
{
	// �ʒu�̊������v�Z
	m_positionRatio = m_gameCamera->GetEyePosition().Length() / m_basePosition.Length();
	// �����_�ݒ�
	m_gameCamera->SetTargetPosition(m_targetPosition);
	// ��]�p�x������
	m_horizontalAngle = 0.0f;
	m_verticalAngle = 0.0f;
}

//------------------------------------------------------------------
/**
 * @brief �X�V
 *
 * @param  �Ȃ�
 * @return �Ȃ�
 */
void CameraStateOverLooking3D::Update()
{
	// �e�탊�\�[�X�擾
	GameResource* gameResource = GameResource::GetInstance();
	InputManager* inputManager = gameResource->GetInputManager();

	// �ǐՃJ�����֐؂�ւ�
	if (inputManager->GetKey(Keyboard::Keys::F).press)
	{
		ChangeTrackSetting();
	}

	// �J������]
	Rotation();
	// �J�����O��ړ�
	Move();
}

//------------------------------------------------------------------
/**
 * @brief ���쒆�t���O
 *
 * @param  �Ȃ�
 * @return false�F����\
 */
bool CameraStateOverLooking3D::IsOperation()
{
	return false;
}

//------------------------------------------------------------------
/**
 * @brief�J������]
 *
 * @param  �Ȃ�
 * @return �Ȃ�
 */
void CameraStateOverLooking3D::Rotation()
{
	// �L�[�}�l�[�W���[�擾
	InputManager* inputManager = GameResource::GetInstance()->GetInputManager();
	
	// �ꎞ�ۑ��p
	float vertical   = m_verticalAngle;
	float horizontal = m_horizontalAngle;

	// �����낵��
	if      (inputManager->GetKey(Keyboard::Keys::W).down) m_verticalAngle -= MOVE_SPEED;
	// ����
	else if (inputManager->GetKey(Keyboard::Keys::S).down) m_verticalAngle += MOVE_SPEED;
	
	// ����]
	if      (inputManager->GetKey(Keyboard::Keys::A).down) m_horizontalAngle -= MOVE_SPEED;
	// �E��]
	else if (inputManager->GetKey(Keyboard::Keys::D).down) m_horizontalAngle += MOVE_SPEED;

	// ���͂�������ΏI��
	if (KT::MyUtility::FloatPresqueEqual(vertical, m_verticalAngle) &&
		KT::MyUtility::FloatPresqueEqual(horizontal, m_horizontalAngle))
		return;


	// �����ʒu����45�x���ɐ���
	m_verticalAngle = std::min(std::max(-VERTICAL_ANGLE_LIMIT, m_verticalAngle), VERTICAL_ANGLE_LIMIT);
	
	// ��]�v�Z
	m_gameCamera->SetRotation(
		SimpleMath::Quaternion::CreateFromAxisAngle(SimpleMath::Vector3::UnitX, m_verticalAngle) * 
		SimpleMath::Quaternion::CreateFromAxisAngle(SimpleMath::Vector3::UnitY, m_horizontalAngle));
}

//------------------------------------------------------------------
/**
 * @brief �J�����O��ړ�
 *
 * @param  �Ȃ�
 * @return �Ȃ�
 */
void CameraStateOverLooking3D::Move()
{
	// �L�[�}�l�[�W���[�擾
	InputManager* inputManager = GameResource::GetInstance()->GetInputManager();

	// �߂Â��i �g�� �j
	if      (inputManager->GetKey(Keyboard::Keys::Up).down)   m_positionRatio -= MOVE_SPEED;
	// ��������i �k�� �j
	else if (inputManager->GetKey(Keyboard::Keys::Down).down) m_positionRatio += MOVE_SPEED;
	// ���͂�������ΏI��
	else return;
	
	// �ʒu�̊�����␳
	m_positionRatio = std::min(std::max(POSITION_RATIO_LIMIT.x, m_positionRatio), POSITION_RATIO_LIMIT.y);

	// ���`�⊮�𗘗p���Ĉʒu�𓮂���
	m_gameCamera->SetEyePosition(SimpleMath::Vector3::Lerp(
		SimpleMath::Vector3::Zero, m_basePosition, m_positionRatio));
}

//------------------------------------------------------------------
/**
 * @brief �ǐՃJ�����֐؂�ւ�
 *
 * @param  �Ȃ�
 * @return �Ȃ�
 */
void CameraStateOverLooking3D::ChangeTrackSetting()
{
	// �ǐՃJ�����擾
	CameraStateTracking3D* track3D = m_gameCamera->GetStateTrack3D();
	// �⊮�J�����擾
	CameraStateLerpSwitch<GameCamera>* stateLerp = m_gameCamera->GetStateLerp();

	// �⊮�ݒ�
	stateLerp->LerpSetting(track3D, KT::GameParam::LERP_TIME_OVERLOOKING);
	stateLerp->PositionSetting(m_gameCamera->GetEyePosition(), track3D->GetEyePosition());
	stateLerp->TargetSetting(m_gameCamera->GetTargetPosition(), m_gameCamera->GetPlayerPosition());
	stateLerp->RotationSetting(m_gameCamera->GetRotation(), track3D->GetBeforeRotation());

	// �⊮�J�����ݒ�
	m_gameCamera->SetNextCamera(stateLerp);
	m_gameCamera->SetCameraState(KT::GameParam::CameraState::OPERATION);
}

//------------------------------------------------------------------
/**
 * @brief �����ݒ�
 *
 * @param  target      �F�����_�ʒu
 * @param  basePosition�F��ʒu
 * @return �Ȃ�
 */
void CameraStateOverLooking3D::InitSetting(const DirectX::SimpleMath::Vector3& target, const DirectX::SimpleMath::Vector3& basePosition)
{
	m_targetPosition = target;
	SetBasePosition(basePosition);
}

//------------------------------------------------------------------
/**
 * @brief �����_�擾
 *
 * @param  �Ȃ�
 * @return Vector3�F�����_�ʒu
 */
const DirectX::SimpleMath::Vector3& CameraStateOverLooking3D::GetTargetPosition() const
{
	return m_targetPosition;
}

//------------------------------------------------------------------
/**
 * @brief �J������ʒu�擾
 *
 * @param  �Ȃ�
 * @return Vector3�F��ʒu
 */
const DirectX::SimpleMath::Vector3& CameraStateOverLooking3D::GetBasePosition() const
{
	return m_basePosition;
}

//------------------------------------------------------------------
/**
 * @brief ��ʒu�ݒ�
 *
 * @param  basePosition�F��ʒu
 * @return �Ȃ�
 */
void CameraStateOverLooking3D::SetBasePosition(const DirectX::SimpleMath::Vector3& basePosition)
{
	m_basePosition = basePosition;
}