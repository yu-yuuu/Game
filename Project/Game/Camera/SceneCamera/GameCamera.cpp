/**
 *
 * @file GameCamera.cpp
 *
 * @brief �Q�[���Ɏg�p����J�����̃\�[�X�t�@�C��
 *
 * @author Kato Yuki
 *
 * @date 2024/2/11
 *
 */
#include "pch.h"
#include "GameCamera.h"

#include "Game/MyLibrary/CommonResource/GameResource.h"
#include "Game/Scene/PlayScene.h"
#include "Game/Camera/CameraProjection.h"
#include "Game/Camera/State/CameraStateTracking2D.h"
#include "Game/Camera/State/CameraStateTracking3D.h"
#include "Game/Camera/State/CameraStateLerpSwitch.h"
#include "Game/Camera/State/CameraStateOverLooking3D.h"
#include "Game/Camera/State/CameraStateOverLooking2D.h"

using namespace DirectX;

//----------------------------------------------
// �萔�錾
//----------------------------------------------

// �J�����̉�]�p�x
const float GameCamera::ROTATION_ANGLE = 90.0f;

//------------------------------------------------------------------
/**
 * @brief �R���X�g���N�^
 *
 * @param playScene  �F�v���C�V�[���ւ̃|�C���^
 * @param aspectRatio�F��ʔ�
 * @param stageSize  �F�X�e�[�W�T�C�Y
 */
GameCamera::GameCamera(PlayScene* playScene, float aspectRatio, DirectX::SimpleMath::Vector3 stageSize)
	: StateCamera(aspectRatio)
	, m_playScene(playScene)
	, m_dimension(KT::GameParam::Dimension::_3D)
	, m_sightType(KT::GameParam::SightType::SIDE)
	, m_cameraState(KT::GameParam::CameraState::NONE)
	, m_playerPosition()
{
	// �e�J�����쐬
	m_stateTrack3D       = std::make_unique<CameraStateTracking3D>(this);
	m_stateTrack2D       = std::make_unique<CameraStateTracking2D>(this);
	m_stateLerp          = std::make_unique<CameraStateLerpSwitch<GameCamera>>(this);
	m_stateOverLooking3D = std::make_unique<CameraStateOverLooking3D>(this);
	m_stateOverLooking2D = std::make_unique<CameraStateOverLooking2D>(this);	

	// �ʒu�ݒ�p
	SimpleMath::Vector3 pos = stageSize * 2.0f;

	// �����ݒ�
	m_stateTrack2D->InitSetting(SimpleMath::Vector3(0.0f, 0.0f, pos.z));
	m_stateOverLooking3D->InitSetting(stageSize * 0.5f, SimpleMath::Vector3(0.0f, stageSize.y, stageSize.z));
	m_stateOverLooking2D->InitSetting(stageSize);
	
	// �ˉe�s��ݒ�
	SetProjectionMatrix(CameraProjection::CreatePerspectiveProjection(GetAspectRatio()));
}

//------------------------------------------------------------------
/**
 * @brief �R���X�g���N�^
 */
GameCamera::~GameCamera()
{

}

//------------------------------------------------------------------
/**
 * @brief �X�V
 *
 * @param  �Ȃ�
 * @return �Ȃ�
 */
void GameCamera::Update()
{
	// ���݂̃J�����X�V�A�؂�ւ�
	StateCamera::Update();

	// ���̃J�������ݒ肳��Ă����珈�����I��
	if (IsChange()) return;

	// �J�����̏�Ԑ؂�ւ�
	switch (m_cameraState)
	{
	case KT::GameParam::CameraState::NONE:
		if (IsOperation()) m_cameraState = KT::GameParam::CameraState::OPERATION;
		break;
	case KT::GameParam::CameraState::OPERATION:
		if (!IsOperation()) m_cameraState = KT::GameParam::CameraState::OPERATION_COMPLETE;
		break;
	case KT::GameParam::CameraState::OPERATION_COMPLETE:
		m_cameraState = KT::GameParam::CameraState::NONE;
		break;
	default:
		break;
	}
}

//------------------------------------------------------------------
/**
 * @brief �����؂�ւ��ݒ�
 *
 * @param  �Ȃ�
 * @return �Ȃ�
 */
void GameCamera::ChangeDimensionSetting()
{
	// ���݂̎������m�F
	if (CheckDimension(KT::GameParam::Dimension::_2D))
	{
		GetStateTrack2D()->ChangeDimensionSetting();
	}
	else
	{
		GetStateTrack3D()->ChangeDimensionSetting();
	}
	m_cameraState = KT::GameParam::CameraState::OPERATION;
}

//------------------------------------------------------------------
/**
 * @brief �����J�����ݒ�
 *
 * @param  lerpTimer   �F�⊮�Ɋ|���鎞��
 * @param  beforeEye   �F�֑ؑO�̈ʒu
 * @param  afterEye    �F�ؑ֌�̈ʒu
 * @param  beforeTarget�F�֑ؑO�̒����_
 * @param  afterTarget �F�ؑ֌�̒����_
 * @return �Ȃ�
 */
void GameCamera::InitialCameraSetting(const float& lerpTimer, const DirectX::SimpleMath::Vector3& beforeEye, const DirectX::SimpleMath::Vector3& afterEye, const DirectX::SimpleMath::Vector3& beforeTarget, const DirectX::SimpleMath::Vector3& afterTarget)
{
	// �؂�ւ��J�����̐ݒ�
	m_stateLerp->LerpSetting(GetStateTrack3D(),lerpTimer );
	m_stateLerp->PositionSetting(beforeEye, afterEye);
	m_stateLerp->TargetSetting(beforeTarget, afterTarget);
	// ���̃J�����ɐݒ�
	SetInitialCamera(GetStateLerp());
}

//------------------------------------------------------------------
/**
 * @brief ���݂̎����m�F
 *
 * @param  dimension�F�m�F���鎟��
 * @return true     �F��v
 * @return false    �F�s��v
 */
bool GameCamera::CheckDimension(KT::GameParam::Dimension dimension)
{
	return m_dimension == dimension;
}

//------------------------------------------------------------------
/**
 * @brief ���݂̎����擾
 *
 * @param �Ȃ�
 * @return Dimension�F���݂̎���
 */
KT::GameParam::Dimension GameCamera::GetDimension()
{
	return m_dimension;
}

//------------------------------------------------------------------
/**
 * @brief ���݂̎����ݒ�
 *
 * @param dimension�F�ݒ肷�鎟��
 * @return �Ȃ�
 */
void GameCamera::SetDimension(KT::GameParam::Dimension dimension)
{
	m_dimension = dimension;
}

//------------------------------------------------------------------
/**
 * @brief ���݂̎��_�^�C�v�m�F
 *
 * @param  type  �F�m�F���鎋�_�^�C�v
 * @return true  �F��v
 * @return false �F�s��v
 */bool GameCamera::CheckSightType(KT::GameParam::SightType type)
{
	return m_sightType == type;
}

//------------------------------------------------------------------
/**
 * @brief ���݂̎��_�^�C�v�擾
 *
 * @param �Ȃ�
 * @return SightType�F���݂̎��_�^�C�v
 */
KT::GameParam::SightType GameCamera::GetSightType()
{
	return m_sightType;
}

//------------------------------------------------------------------
/**
 * @brief ���݂̎��_�^�C�v�ݒ�
 *
 * @param type�F�ݒ肷�鎋�_�^�C�v
 * @return �Ȃ�
 */
void GameCamera::SetSightType(KT::GameParam::SightType type)
{
	m_sightType = type;
}

//------------------------------------------------------------------
/**
 * @brief �J�����̏�Ԏ擾
 *
 * @param  �Ȃ�
 * @return CameraState�F���݂̃J�����̓�����
 */
KT::GameParam::CameraState GameCamera::GetCameraState()
{
	return m_cameraState;
}

//------------------------------------------------------------------
/**
 * @brief �J�����̏�Ԑݒ�
 *
 * @param  state�F�ݒ肷��J�������
 * @return �Ȃ�
 */
void GameCamera::SetCameraState(KT::GameParam::CameraState state)
{
	m_cameraState = state;
}

//------------------------------------------------------------------
/**
 * @brief �J�����̏�Ԋm�F
 *
 * @param  state�F�m�F����J�������
 * @return true �F��v
 * @return false�F�s��v
 */
bool GameCamera::CheckCameraState(KT::GameParam::CameraState state)
{
	return m_cameraState == state;
}

//------------------------------------------------------------------
/**
 * @brief �v���C�V�[���̎擾
 *
 * @param  �Ȃ�
 * @return PlayScene�F�v���C�V�[���̃|�C���^
 */
PlayScene* GameCamera::GetScene() const
{
	return m_playScene;
}

//------------------------------------------------------------------
/**
 * @brief �v���C���[�̈ʒu�擾
 *
 * @param  �Ȃ�
 * @return Vector3�F�v���C���[�̈ʒu
 */
const DirectX::SimpleMath::Vector3& GameCamera::GetPlayerPosition() const
{
	return m_playerPosition;
}

//------------------------------------------------------------------
/**
 * @brief �v���C���[�̈ʒu�ݒ�
 *
 * @param  playerPosition�F�ݒ肷��v���C���[�̈ʒu
 * @return �Ȃ�
 */
void GameCamera::SetPlayerPosition(const DirectX::SimpleMath::Vector3& playerPosition)
{
	m_playerPosition = playerPosition;
}

//------------------------------------------------------------------
/**
 * @brief �ǐՃJ�����i3D�j�擾
 *
 * @param  �Ȃ�
 * @return CameraStateTracking3D�F�ǐՃJ�����i3D�j�̃|�C���^
 */
CameraStateTracking3D* GameCamera::GetStateTrack3D()
{
	return m_stateTrack3D.get();
}

//------------------------------------------------------------------
/**
 * @brief �ǐՃJ�����i2D�j�擾
 *
 * @param  �Ȃ�
 * @return CameraStateTracking2D�F�ǐՃJ�����i2D�j�̃|�C���^
 */
CameraStateTracking2D* GameCamera::GetStateTrack2D()
{
	return m_stateTrack2D.get();
}

//------------------------------------------------------------------
/**
 * @brief �؂�ւ��J�����擾
 *
 * @param  �Ȃ�
 * @return CameraStateLerpSwitch<T>�F�؂�ւ��J�����̃|�C���^
 */
CameraStateLerpSwitch<GameCamera>* GameCamera::GetStateLerp()
{
	return m_stateLerp.get();
}

//------------------------------------------------------------------
/**
 * @brief ���n���J�����i3D�j�擾
 *
 * @param  �Ȃ�
 * @return CameraStateOverLooking3D�F���n���J�����i3D�j�̃|�C���^
 */
CameraStateOverLooking3D* GameCamera::GetStateOverLooking3D()
{
	return m_stateOverLooking3D.get();
}

//------------------------------------------------------------------
/**
 * @brief ���n���J�����i2D�j�擾
 *
 * @param  �Ȃ�
 * @return CameraStateOverLooking2D�F���n���J�����i2D�j�̃|�C���^
 */
CameraStateOverLooking2D* GameCamera::GetStateOverLooking2D()
{
	return m_stateOverLooking2D.get();
}