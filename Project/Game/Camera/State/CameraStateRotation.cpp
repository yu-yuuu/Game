#include "pch.h"
#include "CameraStateRotation.h"
#include "Game/Camera/SceneCamera/StateCamera .h"

using namespace DirectX;

//------------------------------------------------------------------
/**
 * @brief �R���X�g���N�^
 *
 * @param stateCamera�F��ԃJ����
 */
CameraStateRotation::CameraStateRotation(StateCamera* stateCamera)
	: m_camera(stateCamera)
	, m_rotationSpeed(0.0f)
{
}

//------------------------------------------------------------------
/**
 * @brief �f�X�g���N�^
 */
CameraStateRotation::~CameraStateRotation()
{
}

//------------------------------------------------------------------
/**
 * @brief ������
 *
 * @param  �Ȃ�
 * @return �Ȃ�
 */
void CameraStateRotation::Initialize()
{
}

//------------------------------------------------------------------
/**
 * @brief �X�V
 *
 * @param  �Ȃ�
 * @return �Ȃ�
 */
void CameraStateRotation::Update()
{
	// �ݒ肳��Ă��鐔�l�ŉ�]�N�H�[�^�j�I�����v�Z
	SimpleMath::Quaternion rotation = SimpleMath::Quaternion::CreateFromAxisAngle(m_axisOfRotation, m_rotationSpeed);
	// ���݂̉�]�Ɍv�Z������]��������
	m_camera->SetRotation(m_camera->GetRotation() * rotation);
}

//------------------------------------------------------------------
/**
 * @brief ���쒆�t���O
 *
 * @param  �Ȃ�
 * @return false�F����\
 */
bool CameraStateRotation::IsOperation()
{
	return false;
}

//------------------------------------------------------------------
/**
 * @brief ��]�ݒ�
 *
 * @param  rotationSpeed �F��]���x
 * @param  axisOfRotation�F��]�̎�
 * @return �Ȃ�
 */
void CameraStateRotation::RotationSetting(const float& rotationSpeed, const DirectX::SimpleMath::Vector3& axisOfRotation)
{
	m_rotationSpeed = rotationSpeed;
	m_axisOfRotation = axisOfRotation;
}
