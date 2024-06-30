/**
 *
 * @file TitleCamera.h
 *
 * @brief �^�C�g���V�[���Ŏg�p����J�����N���X�̃w�b�_�[�t�@�C��
 *
 * @author Kato Yuki
 *
 * @date 2024/1/23
 *
 */
#pragma once

#include "Game/Camera/SceneCamera/StateCamera .h"

class TitleScene;
template<typename ParentCamera>
class CameraStateLerpSwitch;
class CameraStateRotation;
class CameraStateFixed;

class TitleCamera : public StateCamera
{
//----------------------------------------------
// �萔
//----------------------------------------------
private:

	// �J�����̉�]���x
	const float CAMERA_ROTATION_SPEED = 0.01f;

//----------------------------------------------
// �ϐ�
//----------------------------------------------
private:

	// �^�C�g���V�[��
	TitleScene* m_titleScene;
	
	// �g�p����J����
	std::unique_ptr<CameraStateLerpSwitch<TitleCamera>> m_stateLerp; // �ؑփJ����
	std::unique_ptr<CameraStateRotation> m_stateRotation;            // ��]�J����
	std::unique_ptr<CameraStateFixed> m_stateFixed;                  // �Œ�J����

//----------------------------------------------
// �֐�
//----------------------------------------------
public:

	// �R���X�g���N�^
	TitleCamera(TitleScene* titleScene, float aspectRatio, DirectX::SimpleMath::Vector3 stageSize);
	// �f�X�g���N�^
	~TitleCamera();
	
	// �X�V
	void Update() override;
	// �����ؑ�
	void ChangeDimension();

	// �����J�����ݒ�
	void InitialCameraSetting();
	// ��ԃJ�����擾
	CameraStateLerpSwitch<TitleCamera>* GetStateLerp(); // �؂�ւ��J����
	CameraStateRotation* GetStateRotation();            // ��]�J����
	CameraStateFixed* GetStateFixed();                  // �Œ�J����
};