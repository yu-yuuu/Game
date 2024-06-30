/**
 *
 * @file Camera.cpp
 *
 * @brief �J�����N���X�̃\�[�X
 *
 * @author Kato Yuki
 *
 * @date 2023/11/22
 *
 */
#include "pch.h"
#include "Camera.h"
#include "Game/MyLibrary/Utility/MyUtility.h"

using namespace DirectX;

//------------------------------------------------------------------
/**
 * @brief �R���X�g���N�^
 *
 * @param aspectRatio�F��ʔ�
 */
Camera::Camera(const float& aspectRatio)
	: m_eye()
	, m_target()
	, m_up(DirectX::SimpleMath::Vector3::UnitY)
	, m_view()
	, m_projection()
	, m_rotation()
	, m_isChange(true)
	, m_aspectRatio(aspectRatio)
{
}

//------------------------------------------------------------------
/**
 * @brief �f�X�g���N�^
 */
Camera::~Camera()
{
}

//------------------------------------------------------------------
/**
 * @brief �r���[�s��̍X�V
 *
 * @param  �Ȃ�
 * @return �Ȃ�
 */
void Camera::CreateViewMatrix()
{
	// �ʒu���ɕύX�����邩
	if (!m_isChange) return;

	assert(m_eye != m_target && "�J�����̈ʒu�ƒ����_�������ł�");

	// �J�����̈ʒu���v�Z
	SimpleMath::Vector3 eye = m_target + SimpleMath::Vector3::Transform(m_eye, m_rotation);
	// ���̌������v�Z����
	m_up = SimpleMath::Vector3::Transform(SimpleMath::Vector3::UnitY, m_rotation);
	// �r���[�s��쐬
	m_view = DirectX::SimpleMath::Matrix::CreateLookAt(eye, m_target, m_up);
	// �ύX�t���O��܂�
	m_isChange = false;
}

//------------------------------------------------------------------
/**
 * @brief �X�V
 *
 * @param  elapsedTime�F�o�ߎ���
 * @return �Ȃ�
 */
void Camera::Update()
{
	// �r���[�s��쐬
	CreateViewMatrix();
}

//------------------------------------------------------------------
/**
 * @brief �J�����ʒu�̎擾
 *
 * @param  �Ȃ�
 * @return Vector3�F�J�����ʒu
 */
const DirectX::SimpleMath::Vector3& Camera::GetEyePosition() const
{
	return m_eye;
}

//------------------------------------------------------------------
/**
 * @brief �J�����ʒu�̐ݒ�
 *
 * @param  eye�F�ݒ肷��J�����ʒu
 * @return �Ȃ�
 */
void Camera::SetEyePosition(const DirectX::SimpleMath::Vector3& eye)
{
	// �ύX�������Ȃ�I��
	if (m_eye == eye) return;

	m_eye = eye;
	m_isChange = true;
}

//------------------------------------------------------------------
/**
 * @brief �����_�̎擾
 *
 * @param �Ȃ�
 * @return Vector3�F�����_
 */
const DirectX::SimpleMath::Vector3& Camera::GetTargetPosition() const
{
	return m_target;
}

//------------------------------------------------------------------
/**
 * @brief �����_�̐ݒ�
 *
 * @param  target�F�ݒ肷�钍���_
 * @return �Ȃ�
 */
void Camera::SetTargetPosition(const DirectX::SimpleMath::Vector3& target)
{
	// �ύX�������Ȃ�I��
	if (m_target == target) return;

	m_target = target;
	m_isChange = true;
}

//------------------------------------------------------------------
/**
 * @brief ���̌����̎擾
 *
 * @param �Ȃ�
 * @return Vector3�F���̌���
 */
const DirectX::SimpleMath::Vector3& Camera::GetUpVector() const
{
	return m_up;
}

//------------------------------------------------------------------
/**
 * @brief ���̌����̐ݒ�
 *
 * @param  up�F�ݒ肷�铪�̌���
 * @return �Ȃ�
 */
void Camera::SetUpVector(const DirectX::SimpleMath::Vector3& up)
{
	m_up = up;
}

//------------------------------------------------------------------
/**
 * @brief ��]�̎擾
 *
 * @param  �Ȃ�
 * @return Quaternion�F�J�����̉�]�N�H�[�^�j�I��
 */
const DirectX::SimpleMath::Quaternion& Camera::GetRotation() const
{
	return m_rotation;
}

//------------------------------------------------------------------
/**
 * @brief ��]�̐ݒ�( �N�H�[�^�j�I�� )
 *
 * @param  rotation�F�ݒ肷���]�N�H�[�^�j�I��
 * @return �Ȃ�
 */
void Camera::SetRotation(const DirectX::SimpleMath::Quaternion& rotation)
{
	// �ύX�������Ȃ�I��
	if (m_rotation == rotation) return;

	m_rotation = rotation;
	m_isChange = true;
}

//------------------------------------------------------------------
/**
 * @brief ��]�̐ݒ�( Vector3 )
 *
 * @param  rotation�F�ݒ肷���]�x�N�g��( Yaw Pic )
 * @return �Ȃ�
 */
void Camera::SetRotation(const DirectX::SimpleMath::Vector3& rotation)
{
	SetRotation(SimpleMath::Quaternion::CreateFromYawPitchRoll(rotation));
}

//------------------------------------------------------------------
/**
 * @brief �r���[�s��̎擾
 *
 * @param  �Ȃ�
 * @return Matrix�F�r���[�s��
 */
const DirectX::SimpleMath::Matrix& Camera::GetViewMatrix() const
{
	return m_view;
}

//------------------------------------------------------------------
/**
 * @brief �r���[�s��̐ݒ�
 *
 * @param  view�F�ݒ肷��r���[�s��
 * @return �Ȃ�
 */
void Camera::SetViewMatrix(const DirectX::SimpleMath::Matrix& view)
{
	m_view = view;
}

//------------------------------------------------------------------
/**
 * @brief �ˉe�s��̎擾
 *
 * @param  �Ȃ�
 * @return Matrix�F�ˉe�s��
 */
const DirectX::SimpleMath::Matrix& Camera::GetProjectionMatrix() const
{
	return m_projection;
}

//------------------------------------------------------------------
/**
 * @brief �ˉe�s��̐ݒ�
 *
 * @param  projection�F�ݒ肷��ˉe�s��
 * @return �Ȃ�
 */
void Camera::SetProjectionMatrix(const DirectX::SimpleMath::Matrix& projection)
{
	m_projection = projection;
}

//------------------------------------------------------------------
/**
 * @brief ��ʔ�̎擾
 *
 * @param  �Ȃ�
 * @return float�F��ʔ�
 * 
 */
const float& Camera::GetAspectRatio() const
{
	return m_aspectRatio;
}

//------------------------------------------------------------------
/**
 * @brief �J�����̕����x�N�g���擾
 *
 * @param  �Ȃ�
 * @return Vector3�F�J�����̕����x�N�g��
 */
DirectX::SimpleMath::Vector3 Camera::GetDirection()
{
	// �����x�N�g�������߂�
	SimpleMath::Vector3 dir = SimpleMath::Vector3::Transform(SimpleMath::Vector3::Forward, m_rotation);
	// �덷������ꍇ������̂��Y��ɂ���
	return KT::MyUtility::EliminateDirectionError(dir);
}