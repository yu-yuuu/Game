/**
 *
 * @file CameraStateFixed.h
 *
 * @brief �Œ�ʒu�J�����̃w�b�_�[�t�@�C��
 *
 * @author Kato Yuki
 *
 * @date 2024/3/2
 *
 */
#pragma once

#include "Game/Camera/State/ICameraState.h"

class StateCamera;

class CameraStateFixed : public ICameraState
{
//----------------------------------------------
// �ϐ�
//----------------------------------------------
private:

	// �J����
	StateCamera* m_stateCamera;

//----------------------------------------------
// �֐�
//----------------------------------------------
public:

	// �R���X�g���N�^
	CameraStateFixed(StateCamera* stateCamera);
	// �f�X�g���N�^
	~CameraStateFixed();
	
	// ������
	void Initialize() override;
	// �X�V
	void Update() override;
	// ���쒆�t���O
	bool IsOperation() override;

};