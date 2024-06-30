/**
 *
 * @file CameraStateOverLooking3D.h
 *
 * @brief 3D���n���J�����̃w�b�_�[�t�@�C��
 *
 * @author Kato Yuki
 *
 * @date 2024/2/26
 *
 */
#pragma once

#include "Game/Camera/State/ICameraState.h"

class GameCamera;

class CameraStateOverLooking3D : public ICameraState
{
//----------------------------------------------
// �萔
//----------------------------------------------
private:

	// �ړ����x
	const float MOVE_SPEED = 0.02f;

	// �c��]�p�x�����l
	const float VERTICAL_ANGLE_LIMIT = 45.0f * DirectX::XM_PI / 180.0f;

	// �J�����ʒu�̊��������l
	const DirectX::SimpleMath::Vector2 POSITION_RATIO_LIMIT = { 0.1f, 1.0f };

//----------------------------------------------
// �ϐ�
//----------------------------------------------
private:

	// �Q�[���J����
	GameCamera* m_gameCamera;
	// �O��ړ��̊�ʒu
	DirectX::SimpleMath::Vector3 m_basePosition;
	// �J�����̒����_
	DirectX::SimpleMath::Vector3 m_targetPosition;
	// ���݂̈ʒu����̂ǂ���ӂɂ���̂��̊���
	float m_positionRatio;
	// �J�����̉���]�p�x
	float m_horizontalAngle;
	// �J�����̏c��]�p�x
	float m_verticalAngle;

//----------------------------------------------
// �֐�
//----------------------------------------------
public:

	// �R���X�g���N�^
	CameraStateOverLooking3D(GameCamera* gameCamera);
	// �f�X�g���N�^
	~CameraStateOverLooking3D();
	// ������
	void Initialize() override;
	// �X�V
	void Update() override;
	// ���쒆�t���O
	bool IsOperation() override;

	// �J������]
	void Rotation();
	// �J�����O��ړ�
	void Move();
	// �ǐՃJ�����֐؂�ւ�
	void ChangeTrackSetting();
	
	// �����ݒ�
	void InitSetting(const DirectX::SimpleMath::Vector3& target, const DirectX::SimpleMath::Vector3& basePosition);

	// �����_�擾
	const DirectX::SimpleMath::Vector3& GetTargetPosition() const;
	// �J������ʒu�擾
	const DirectX::SimpleMath::Vector3& GetBasePosition() const;
	// ��ʒu�ݒ�
	void SetBasePosition(const DirectX::SimpleMath::Vector3& basePosition);

};