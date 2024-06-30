/**
 *
 * @file CameraStateRotation.h
 *
 * @brief �����_�Œ�ŉ�]������J�����̃w�b�_�[�t�@�C��
 *
 * @author Kato Yuki
 *
 * @date 2024/2/12
 *
 */
#pragma once

#include "Game/Camera/State/ICameraState.h"

class StateCamera;

class CameraStateRotation : public ICameraState
{
//----------------------------------------------
// �ϐ�
//----------------------------------------------
private:

	// �X�e�[�g�J����
	StateCamera* m_camera;
	// ��]���x
	float m_rotationSpeed;
	// ��]��
	DirectX::SimpleMath::Vector3 m_axisOfRotation;

//----------------------------------------------
// �֐�
//----------------------------------------------
public:

	// �R���X�g���N�^
	CameraStateRotation(StateCamera* stateCamera);
	// �f�X�g���N�^
	~CameraStateRotation();
	// ������
	void Initialize() override;
	// �X�V
	void Update() override;
	// ���쒆�t���O
	bool IsOperation() override;
	// ��]�ݒ�
	void RotationSetting(const float& rotationSpeed, const DirectX::SimpleMath::Vector3& axisOfRotation);
};
