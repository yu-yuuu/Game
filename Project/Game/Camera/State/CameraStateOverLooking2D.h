/**
 *
 * @file CameraStateOverLooking2D.h
 *
 * @brief 2D���n���J�����̃w�b�_�[�t�@�C��
 *
 * @author Kato Yuki
 *
 * @date 2024/2/28
 *
 */
#pragma once

#include "Game/Camera/State/ICameraState.h"

class GameCamera;

class CameraStateOverLooking2D : public ICameraState
{
//----------------------------------------------
// �萔
//----------------------------------------------
private:

	// �ړ����x
	const float MOVE_SPEED = 0.1f;

//----------------------------------------------
// �ϐ�
//----------------------------------------------
private:

	// �Q�[���J����
	GameCamera* m_gameCamera;
	// �ړ������ʒu
	DirectX::SimpleMath::Vector3 m_limitPosition;

//----------------------------------------------
// �֐�
//----------------------------------------------
public:

	// �R���X�g���N�^
	CameraStateOverLooking2D(GameCamera* gameCamera);
	// �f�X�g���N�^
	~CameraStateOverLooking2D();

	// ������
	void Initialize() override;
	// �X�V
	void Update() override;
	// ���쒆�t���O
	bool IsOperation() override;

	// �J�����O��ړ�
	void Move();
	// �ǐՃJ�����֐؂�ւ��ݒ�
	void ChangeTrackSetting();
	
	// �ړ������ʒu�ݒ�
	void SetLimitPosition(const DirectX::SimpleMath::Vector3& limitPosition);
	// �����ݒ�
	void InitSetting(const DirectX::SimpleMath::Vector3& limit);
};