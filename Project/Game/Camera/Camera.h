/**
 *
 * @file Camera.h
 *
 * @brief �J�����N���X�̃w�b�_�[
 *
 * @author Kato Yuki
 *
 * @date 2023/11/22
 *
 */
#pragma once

class Camera
{
//----------------------------------------------
// �萔
//----------------------------------------------
public:

	// ����p�i�x���@�j
	const float FOV = 45.0f;
	// ��O�̕\������
	const float NEAR_PLANE = 0.1f;
	// ���̕\������
	const float FAR_PLANE = 200.0f;	

//----------------------------------------------
// �ϐ�
//----------------------------------------------
private:

	// �ʒu
	DirectX::SimpleMath::Vector3 m_eye;
	// �����_
	DirectX::SimpleMath::Vector3 m_target;
	// ���̌���
	DirectX::SimpleMath::Vector3 m_up;
	// �r���[�s��
	DirectX::SimpleMath::Matrix m_view;
	// �ˉe�s��
	DirectX::SimpleMath::Matrix m_projection;
	// ��]
	DirectX::SimpleMath::Quaternion m_rotation;
	// �J�����̏�񂪕ύX���ꂽ��
	bool m_isChange;
	// ��ʔ�
	float m_aspectRatio;

//----------------------------------------------
// �֐�
//----------------------------------------------
public:

	// �R���X�g���N�^
	Camera(const float& aspectRatio);
	// �f�X�g���N�^
	virtual ~Camera();
	// �X�V
	virtual void Update();

	// �r���[�s��̍쐬
	void CreateViewMatrix();

	// �ʒu�̎擾
	const DirectX::SimpleMath::Vector3& GetEyePosition()const;
	// �ʒu�̐ݒ�
	void SetEyePosition(const DirectX::SimpleMath::Vector3& eye);
	// �^�[�Q�b�g�̎擾
	const DirectX::SimpleMath::Vector3& GetTargetPosition()const;
	// �^�[�Q�b�g�̐ݒ�
	void SetTargetPosition(const DirectX::SimpleMath::Vector3& target);
	// ���̌����̎擾
	const DirectX::SimpleMath::Vector3& GetUpVector() const;
	// ���̌����̐ݒ�
	void SetUpVector(const DirectX::SimpleMath::Vector3& up);
	// ��]�̎擾
	const DirectX::SimpleMath::Quaternion& GetRotation()const;
	// ��]�̐ݒ�i �N�H�[�^�j�I�� �j
	void SetRotation(const DirectX::SimpleMath::Quaternion& rotation);
	// ��]�̐ݒ�i Vector3 �j
	void SetRotation(const DirectX::SimpleMath::Vector3& rotation);
	// �r���[�s��̎擾
	const DirectX::SimpleMath::Matrix& GetViewMatrix()const;
	// �r���[�s��̐ݒ�
	void SetViewMatrix(const DirectX::SimpleMath::Matrix& view);
	// �ˉe�s��̎擾
	const DirectX::SimpleMath::Matrix& GetProjectionMatrix()const;
	// �ˉe�s��̐ݒ�
	void SetProjectionMatrix(const DirectX::SimpleMath::Matrix& projection);
	// ��ʔ�̎擾
	const float& GetAspectRatio()const;
	// �J�����̕����x�N�g���擾
	DirectX::SimpleMath::Vector3 GetDirection();
};