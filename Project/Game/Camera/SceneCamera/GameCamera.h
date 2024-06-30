/**
 *
 * @file GameCamera.h
 *
 * @brief �Q�[���Ɏg�p����J�����̃w�b�_�[�t�@�C��
 *
 * @author Kato Yuki
 *
 * @date 2024/2/11
 *
 */
#pragma once

#include "Game/Camera/SceneCamera/StateCamera .h"
#include "Game/MyLibrary/GameParameter/GameParameter.h"

class PlayScene;
class CameraStateTracking3D;
class CameraStateTracking2D;
template<typename ParentCamera>
class CameraStateLerpSwitch;
class CameraStateOverLooking3D;
class CameraStateOverLooking2D;

class GameCamera : public StateCamera
{
//----------------------------------------------
// �萔
//----------------------------------------------
public:

	// ��]�p�x
	static const float ROTATION_ANGLE;

//----------------------------------------------
// �ϐ�
//----------------------------------------------
private:

	// �v���C�V�[��
	PlayScene* m_playScene;

	// ����
	KT::GameParam::Dimension m_dimension;
	// ���_�^�C�v
	KT::GameParam::SightType m_sightType;
	// �J�����̏��
	KT::GameParam::CameraState m_cameraState;

	// �J�����̎��
	std::unique_ptr<CameraStateTracking3D> m_stateTrack3D;
	std::unique_ptr<CameraStateTracking2D> m_stateTrack2D;
	std::unique_ptr<CameraStateLerpSwitch<GameCamera>> m_stateLerp;
	std::unique_ptr<CameraStateOverLooking3D> m_stateOverLooking3D;
	std::unique_ptr<CameraStateOverLooking2D> m_stateOverLooking2D;

	// �v���C���[�̈ʒu
	DirectX::SimpleMath::Vector3 m_playerPosition;

//----------------------------------------------
// �֐�
//----------------------------------------------
public:

	// �R���X�g���N�^
	GameCamera(PlayScene* playScene, float aspectRatio, DirectX::SimpleMath::Vector3 stageSize);
	// �f�X�g���N�^
	~GameCamera();

	// �X�V
	void Update() override;
	// �����؂�ւ��ݒ�
	void ChangeDimensionSetting();
	// �����J�����ݒ�
	void InitialCameraSetting(
		const float& lerpTimer, 
		const DirectX::SimpleMath::Vector3& beforeEye,
		const DirectX::SimpleMath::Vector3& afterEye,
		const DirectX::SimpleMath::Vector3& beforeTarget,
		const DirectX::SimpleMath::Vector3& afterTarget
		);

	// ���݂̎����m�F
	bool CheckDimension(KT::GameParam::Dimension dimension);
	// ���݂̎����擾
	KT::GameParam::Dimension GetDimension();
	// ���݂̎����ݒ�
	void SetDimension(KT::GameParam::Dimension dimension);
	// ���݂̎��_�^�C�v�m�F
	bool CheckSightType(KT::GameParam::SightType type);
	// ���݂̎��_�^�C�v�擾
	KT::GameParam::SightType GetSightType();
	// ���݂̎��_�^�C�v�ݒ�
	void SetSightType(KT::GameParam::SightType type);
	// �J�����̏�Ԏ擾
	KT::GameParam::CameraState GetCameraState();
	// �J�����̏�Ԑݒ�
	void SetCameraState(KT::GameParam::CameraState state);
	// �J�����̏�Ԋm�F
	bool CheckCameraState(KT::GameParam::CameraState state);
	// �v���C�V�[���̎擾
	PlayScene* GetScene() const;
	// �v���C���[�̈ʒu�擾
	const DirectX::SimpleMath::Vector3& GetPlayerPosition() const;
	// �v���C���[�̈ʒu�ݒ�
	void SetPlayerPosition(const DirectX::SimpleMath::Vector3& playerPosition);
	// ��ԃJ�����擾
	CameraStateTracking3D* GetStateTrack3D();
	CameraStateTracking2D* GetStateTrack2D();
	CameraStateLerpSwitch<GameCamera>* GetStateLerp();
	CameraStateOverLooking3D* GetStateOverLooking3D();
	CameraStateOverLooking2D* GetStateOverLooking2D();
};