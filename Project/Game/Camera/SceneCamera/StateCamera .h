/**
 *
 * @file StateCamera.h
 *
 * @brief ��ԃJ�������g�p����J�����N���X�̃w�b�_�[�t�@�C��
 *
 * @author Kato Yuki
 *
 * @date 2024/1/18
 *
 */
#pragma once

#include "Game/Camera/Camera.h"

class ICameraState;

class StateCamera : public Camera
{
//----------------------------------------------
// �ϐ�
//----------------------------------------------
private:

	// ���݂̏��
	ICameraState* m_currentCamera;
	// ���̏��
	ICameraState* m_nextCamera;

//----------------------------------------------
// �֐�
//----------------------------------------------
public:

	// �R���X�g���N�^
	StateCamera(float aspectRatio);
	// �f�X�g���N�^
	virtual ~StateCamera();
	// �X�V
	virtual void Update();
	// ��Ԑ؂�ւ�
	void ChangeState();
	// ��Ԑ؂�ւ��\��Ԃ��m�F
	bool IsChange();

	// ���݂̏�Ԏ擾
	ICameraState* GetCurrentCameraState();
	// ������Ԑݒ�
	void SetInitialCamera(ICameraState* initialCamera);
	// ���̃J�����ݒ�
	void SetNextCamera(ICameraState* nextCamera);

	// �ؑ֒��t���O
	bool IsOperation();

};