/**
 *
 * @file StageSelectCamera.cpp
 *
 * @brief �X�e�[�W�I���V�[���Ɏg�p����J�����N���X�̃\�[�X�t�@�C��
 *
 * @author Kato Yuki
 *
 * @date 2024/5/26
 *
 */
#include "pch.h"
#include "StageSelectCamera.h"
#include "Game/Scene/StageSelectScene.h"

#include "Game/MyLibrary/CommonResource/GameResource.h"
#include "Game/MyLibrary/GameParameter/GameParameter.h"

#include "Game/Camera/CameraProjection.h"
#include "Game/Camera/State/CameraStateLerpSwitch.h"
#include "Game/Camera/State/CameraStateRotation.h"

using namespace DirectX;

//------------------------------------------------------------------
/**
 * @brief �R���X�g���N�^
 *
 * @param stageSelectScene �F�X�e�[�W�Z���N�g�V�[���̃|�C���^
 * @param aspectRatio�F��ʔ�
 * @param stageSize  �F�X�e�[�W�̑傫��
 */
StageSelectCamera::StageSelectCamera(StageSelectScene* stageSelectScene, float aspectRatio, DirectX::SimpleMath::Vector3 stageSize)
	: StateCamera(aspectRatio)
	, m_stageSelectScene(stageSelectScene)
	, m_stateLerp(nullptr)
	, m_stateRotation(nullptr)
{
	// �e�J�����쐬
	m_stateLerp     = std::make_unique<CameraStateLerpSwitch<StageSelectCamera>>(this);
	m_stateRotation = std::make_unique<CameraStateRotation>(this);

	// �J�����ʒu�A�����_�A�ˉe�s��ݒ�	
	SetEyePosition(stageSize);
	SetTargetPosition(stageSize * 0.5f);// �X�e�[�W�̐^��
	SetProjectionMatrix(CameraProjection::CreatePerspectiveProjection(aspectRatio));
}

//------------------------------------------------------------------
/**
 * @brief �f�X�g���N�^
 */
StageSelectCamera::~StageSelectCamera()
{
}

//------------------------------------------------------------------
/**
 * @brief �X�V
 *
 * @param  �Ȃ�
 * @return �Ȃ�
 */
void StageSelectCamera::Update()
{
	// ���N���X�̍X�V����
	StateCamera::Update();
}

//------------------------------------------------------------------
/**
 * @brief �X�e�[�W�I��
 *
 * @param nextStageBasePosition�F�؂�ւ���X�e�[�W�̊�ʒu
 * @param nextStageSize�F�؂�ւ���X�e�[�W�̃T�C�Y
 * @return �Ȃ�
 */
void StageSelectCamera::StageSelectSetting(const DirectX::SimpleMath::Vector3& nextStageBasePosition, const DirectX::SimpleMath::Vector3& nextStageSize)
{
	// �ړ��J�n�ʒu�擾
	SimpleMath::Vector3 startPosition = GetTargetPosition();
	//  �؂�ւ���X�e�[�W�̃J�����ʒu�v�Z
	SimpleMath::Vector3 nextEye = nextStageSize;

	// �؂�ւ��J�����ݒ�
	m_stateLerp->LerpSetting(GetStateRotation(), STAGE_SWITCH_SPEED);
	m_stateLerp->TargetSetting(startPosition, nextStageBasePosition);
	m_stateLerp->PositionSetting(GetEyePosition(), nextEye);
	SetNextCamera(GetStateLerp());
}

//------------------------------------------------------------------
/**
 * @brief �����J�����ݒ�
 *
 * @param  �Ȃ�
 * @return �Ȃ�
 */
void StageSelectCamera::InitialCameraSetting()
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
 * @return CameraStateLerpSwitch<StageSelectScene>*�F�ؑփJ�����̃|�C���^
 */
CameraStateLerpSwitch<StageSelectCamera>* StageSelectCamera::GetStateLerp()
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
CameraStateRotation* StageSelectCamera::GetStateRotation()
{
	return m_stateRotation.get();
}