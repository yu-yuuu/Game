/**
 *
 * @file TitleCamera.cpp
 *
 * @brief �^�C�g���V�[���Ŏg�p����J�����N���X�̃\�[�X�t�@�C��
 *
 * @author Kato Yuki
 *
 * @date 2024/1/23
 *
 */
#include "pch.h"
#include "TitleCamera.h"
#include "Game/Scene/TitleScene.h"

#include "Game/MyLibrary/CommonResource/GameResource.h"
#include "Game/MyLibrary/GameParameter/GameParameter.h"

#include "Game/Camera/CameraProjection.h"
#include "Game/Camera/State/CameraStateLerpSwitch.h"
#include "Game/Camera/State/CameraStateRotation.h"
#include "Game/Camera/State/CameraStateFixed.h"


using namespace DirectX;

//------------------------------------------------------------------
/**
 * @brief �R���X�g���N�^
 *
 * @param titleScene �F�^�C�g���V�[���̃|�C���^
 * @param aspectRatio�F��ʔ�
 * @param stageSize  �F�X�e�[�W�̑傫��
 */
TitleCamera::TitleCamera(TitleScene* titleScene, float aspectRatio, DirectX::SimpleMath::Vector3 stageSize)
	: StateCamera(aspectRatio)
	, m_titleScene(titleScene)
	, m_stateLerp(nullptr)
	, m_stateRotation(nullptr)
	, m_stateFixed(nullptr)
{
	// �e�J�����쐬
	m_stateLerp     = std::make_unique<CameraStateLerpSwitch<TitleCamera>>(this);
	m_stateRotation = std::make_unique<CameraStateRotation>(this);
	m_stateFixed    = std::make_unique<CameraStateFixed>(this);

	// �J�����ʒu�A�����_�A�ˉe�s��ݒ�	
	SetEyePosition(stageSize);
	SetTargetPosition(stageSize * 0.5f);// �X�e�[�W�̐^��
	SetProjectionMatrix(CameraProjection::CreatePerspectiveProjection(aspectRatio));
}

//------------------------------------------------------------------
/**
 * @brief �f�X�g���N�^
 */
TitleCamera::~TitleCamera()
{
}

//------------------------------------------------------------------
/**
 * @brief �X�V
 *
 * @param  �Ȃ�
 * @return �Ȃ�
 */
void TitleCamera::Update()
{
	// ���N���X�̍X�V����
	StateCamera::Update();
}

//------------------------------------------------------------------
/**
 * @brief �����̐؂�ւ�
 *
 * @param  �Ȃ�
 * @return �Ȃ�
 */
void TitleCamera::ChangeDimension()
{
	// �J�����ʒu�擾
	SimpleMath::Vector3 eye = GetEyePosition();

	// �؂�ւ��J�����ݒ�
	m_stateLerp->LerpSetting(GetStateFixed(), KT::GameParam::LERP_TIME_DIMENSION);
	m_stateLerp->PositionSetting(eye, SimpleMath::Vector3(0.0f, 0.0f, eye.z));
	m_stateLerp->ProjectionSetting(GetProjectionMatrix(), CameraProjection::CreateOrthographicProjection(GetAspectRatio(), CameraProjection::SIDE_RECT));
	m_stateLerp->RotationSetting(GetRotation(), SimpleMath::Quaternion::Identity);

	// ���̃J�����ɐݒ�
	SetNextCamera(m_stateLerp.get());
}

//------------------------------------------------------------------
/**
 * @brief �����J�����ݒ�
 *
 * @param  �Ȃ�
 * @return �Ȃ�
 */
void TitleCamera::InitialCameraSetting()
{
	// ��]�J�����̏����ݒ�
	m_stateRotation->RotationSetting(CAMERA_ROTATION_SPEED, SimpleMath::Vector3::UnitY);
	// ��]�J�����������J�����ɐݒ�
	SetInitialCamera(GetStateRotation());
}

//------------------------------------------------------------------
/**
 * @brief �ؑփJ�����擾
 *
 * @param  �Ȃ�
 * @return CameraStateLerpSwitch<TitleCamera>*�F�ؑփJ�����̃|�C���^
 */
CameraStateLerpSwitch<TitleCamera>* TitleCamera::GetStateLerp()
{
	return m_stateLerp.get();
}

//------------------------------------------------------------------
/**
 * @brief ��]�J�����擾
 *
 * @param  �Ȃ�
 * @return CameraStateRotation*�F��]�J�����̃|�C���^
 */
CameraStateRotation* TitleCamera::GetStateRotation()
{
	return m_stateRotation.get();
}

//------------------------------------------------------------------
/**
 * @brief �Œ�J�����擾
 *
 * @param  �Ȃ�
 * @return CameraStateFixed*�F�Œ�J�����̃|�C���^
 */
CameraStateFixed* TitleCamera::GetStateFixed()
{
	return m_stateFixed.get();
}