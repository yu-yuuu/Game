/**
 *
 * @file StageSelectCamera.h
 *
 * @brief �X�e�[�W�I���V�[���Ɏg�p����J�����N���X�̃w�b�_�[�t�@�C��
 *
 * @author Kato Yuki
 *
 * @date 2024/5/26
 *
 */
#pragma once
#include "Game/Camera/SceneCamera/StateCamera .h"

class StageSelectScene;
template<typename ParentCamera>
class CameraStateLerpSwitch;
class CameraStateRotation;

class StageSelectCamera : public StateCamera
{
//----------------------------------------------
// �萔
//----------------------------------------------
private:

	// �J�����̉�]���x
	const float CAMERA_ROTATION_SPEED = 0.01f;

	// �X�e�[�W��؂�ւ���ۂ̃X�s�[�h
	const float STAGE_SWITCH_SPEED = 0.5f;

//----------------------------------------------
// �ϐ�
//----------------------------------------------
private:

	// �X�e�[�W�Z���N�g�V�[��
	StageSelectScene* m_stageSelectScene;

	// �g�p����J����
	std::unique_ptr<CameraStateLerpSwitch<StageSelectCamera>> m_stateLerp; // �ؑփJ����
	std::unique_ptr<CameraStateRotation> m_stateRotation;            // ��]�J����


//----------------------------------------------
// �֐�
//----------------------------------------------
public:

	// �R���X�g���N�^
	StageSelectCamera(StageSelectScene* stageSelectScene, float aspectRatio, DirectX::SimpleMath::Vector3 stageSize);
	// �f�X�g���N�^
	~StageSelectCamera();

	// �X�V
	void Update() override;

	// �X�e�[�W�I��
	void StageSelectSetting(const DirectX::SimpleMath::Vector3& nextStageBasePosition, const DirectX::SimpleMath::Vector3& nextStageSize);

	// �����J�����ݒ�
	void InitialCameraSetting();
	// ��ԃJ�����擾
	CameraStateLerpSwitch<StageSelectCamera>* GetStateLerp(); // �؂�ւ��J����
	CameraStateRotation* GetStateRotation();            // ��]�J����

	

};