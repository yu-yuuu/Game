/**
 *
 * @file CameraStateTracking3D.cpp
 *
 * @brief 3D�ǐՃJ�����̃\�[�X�t�@�C��
 *
 * @author Kato Yuki
 *
 * @date 2024/2/11
 *
 */
#include "pch.h"
#include "CameraStateTracking3D.h"
#include "Game/Scene/PlayScene.h"
#include "Game/Camera/SceneCamera/GameCamera.h"
#include "Game/Camera/State/CameraStateTracking2D.h"
#include "Game/Camera/State/CameraStateOverLooking3D.h"
#include "Game/Camera/State/CameraStateLerpSwitch.h"
#include "Game/MyLibrary/CommonResource/GameResource.h"
#include "Game/MyLibrary/GameParameter/GameParameter.h"

using namespace DirectX;

//------------------------------------------------------------------
/**
 * @brief �R���X�g���N�^
 *
 * @param gameCamera�F�Q�[���J����
 */
CameraStateTracking3D::CameraStateTracking3D(GameCamera* gameCamera)
	: m_gameCamera(gameCamera)
	, m_beforeRotation()
{

}

//------------------------------------------------------------------
/**
 * @brief �f�X�g���N�^
 */
CameraStateTracking3D::~CameraStateTracking3D()
{
}

//------------------------------------------------------------------
/**
 * @brief ������
 *
 * @param  �Ȃ�
 * @return �Ȃ�
 */
void CameraStateTracking3D::Initialize()
{
	m_gameCamera->SetDimension(KT::GameParam::Dimension::_3D);
}

//------------------------------------------------------------------
/**
 * @brief �X�V
 *
 * @param  �Ȃ�
 * @return �Ȃ�
 */
void CameraStateTracking3D::Update()
{
	// �J�����ʒu�X�V
	m_gameCamera->SetEyePosition(GetEyePosition());

	// ��]�����ėǂ���
	if(CheckRotation())
	{
		// �J������]����
		RotationSetting();
	}
	// ���n���J�����ɐ؂�ւ��ėǂ���
	if (CheckChangeOverLooking())
	{
		// ���n���J�����ؑ֐ݒ�
		ChangeOverLookingSetting();
	}
}

//------------------------------------------------------------------
/**
 * @brief �����ؑ֐ݒ�
 *
 * @param  �Ȃ�
 * @return �Ȃ�
 */
void CameraStateTracking3D::ChangeDimensionSetting()
{
	// �⊮�J�����擾
	CameraStateLerpSwitch<GameCamera>* stateLerp = m_gameCamera->GetStateLerp();
	
	// �؂�ւ���J�����擾
	CameraStateTracking2D* state2D = m_gameCamera->GetStateTrack2D();

	// ���_�^�C�v�ɂ���ăJ�����̕`��͈͂�؂�ւ���
	RECT rect;
	if (m_gameCamera->CheckSightType(KT::GameParam::SightType::SIDE))
		rect = CameraProjection::SIDE_RECT;
	else
		rect = CameraProjection::TOPDOWN_RECT;

	// �⊮�ݒ�
	stateLerp->LerpSetting(state2D, KT::GameParam::LERP_TIME_DIMENSION);
	stateLerp->PositionSetting(m_gameCamera->GetEyePosition(), state2D->GetEyePosition());
	stateLerp->ProjectionSetting(m_gameCamera->GetProjectionMatrix(), 
		CameraProjection::CreateOrthographicProjection(m_gameCamera->GetAspectRatio(), rect));

	// ���̃J�����ݒ�
	m_gameCamera->SetNextCamera(stateLerp);
}

//------------------------------------------------------------------
/**
 * @brief ��]���Ă悢���m�F
 *
 * @param  �Ȃ�
 * @return �Ȃ�
 */
bool CameraStateTracking3D::CheckRotation()
{
	// �L�[�}�l�[�W���[�擾
	InputManager* inputManager = GameResource::GetInstance()->GetInputManager();

	// �v���C���[�����̏�ɋ��Ȃ��Ȃ��]�����Ȃ�
	if (!m_gameCamera->GetScene()->OnGroundPlayer()) return false;

	// ���͊m�F
	return
		// W�L�[�������ꂽ ���� �����_
		(inputManager->GetKey(Keyboard::Keys::W).press && m_gameCamera->CheckSightType(KT::GameParam::SightType::SIDE)) ||
		// S�L�[�������ꂽ ���� �����낵���_
		(inputManager->GetKey(Keyboard::Keys::S).press && m_gameCamera->CheckSightType(KT::GameParam::SightType::TOPDOWN)) ||
		// A�L�[�������ꂽ 
		inputManager->GetKey(Keyboard::Keys::A).press ||
		// D�L�[�������ꂽ 
		inputManager->GetKey(Keyboard::Keys::D).press;
}

//------------------------------------------------------------------
/**
 * @brief �J������]�ݒ�
 *
 * @param  �Ȃ�
 * @return �Ȃ�
 */
void CameraStateTracking3D::RotationSetting()
{
	// �e�탊�\�[�X�擾
	GameResource*    gameResource    = GameResource::GetInstance();
	InputManager*    inputManager    = gameResource->GetInputManager();
	ResourceManager* resourceManager = gameResource->GetResourceManager();

	// ���݂̉�]�N�H�[�^�j�I��
	SimpleMath::Quaternion rotation = m_gameCamera->GetRotation();

	// ��]������p�x
	float radian = XMConvertToRadians(GameCamera::ROTATION_ANGLE);

	// �����낵��
	if (inputManager->GetKey(Keyboard::Keys::W).press)
	{
		rotation = SimpleMath::Quaternion::CreateFromAxisAngle(
			SimpleMath::Vector3::UnitX, -radian) * rotation;
		// �����낵�֕ύX
		m_gameCamera->SetSightType(KT::GameParam::SightType::TOPDOWN);
	}
	// ����
	else if(inputManager->GetKey(Keyboard::Keys::S).press)
	{
		rotation = SimpleMath::Quaternion::CreateFromAxisAngle(
			SimpleMath::Vector3::UnitX, radian) * rotation;
		// ���֕ύX
		m_gameCamera->SetSightType(KT::GameParam::SightType::SIDE);
	}
	// ����]
	else if (inputManager->GetKey(Keyboard::Keys::A).press)
	{
		rotation = rotation * SimpleMath::Quaternion::CreateFromAxisAngle(
			SimpleMath::Vector3::UnitY, -radian);
	}
	// �E��]
	else if (inputManager->GetKey(Keyboard::Keys::D).press)
	{
		rotation = rotation * SimpleMath::Quaternion::CreateFromAxisAngle(
			SimpleMath::Vector3::UnitY, radian);
	}

	// �⊮�J�����擾
	CameraStateLerpSwitch<GameCamera>* stateLerp = m_gameCamera->GetStateLerp();
	
	// �J�����ʒu�擾
	SimpleMath::Vector3 eye = GetEyePosition();
	// �⊮�ݒ�
	stateLerp->LerpSetting(this, KT::GameParam::LERP_TIME_ROTATION);
	stateLerp->PositionSetting(m_gameCamera->GetEyePosition(), eye);
	stateLerp->RotationSetting(m_gameCamera->GetRotation(), rotation);
	// ��]��Ԃ��Z�b�g
	m_gameCamera->SetNextCamera(stateLerp);

	// SE�𗬂�
	resourceManager->PlaySound(KT::Sound::SE, KT::Sound::SENumber::XACT_WAVEBANK_SE_CAMERAROTATION);
}

//------------------------------------------------------------------
/**
 * @brief ���n���J�����ɐ؂�ւ��Ă悢���m�F
 *
 * @param  �Ȃ�
 * @return true�F�ؑ։�
 * @return true�F�ؑ֕s��
 */
bool CameraStateTracking3D::CheckChangeOverLooking()
{
	// �v���C���[�����̏�ɋ��Ȃ��Ȃ�ؑւ����Ȃ�
	if (!m_gameCamera->GetScene()->OnGroundPlayer()) return false;

	// �L�[�}�l�[�W���[�擾
	InputManager* inputManager = GameResource::GetInstance()->GetInputManager();

	return inputManager->GetKey(Keyboard::Keys::F).press;
}

//------------------------------------------------------------------
/**
 * @brief ���n���J�����ؑ֐ݒ�
 *
 * @param  �Ȃ�
 * @return �Ȃ�
 */
void CameraStateTracking3D::ChangeOverLookingSetting()
{
	// ���݂̉�]��ۑ����Ă���
	m_beforeRotation = m_gameCamera->GetRotation();

	// �⊮�J�����擾
	CameraStateLerpSwitch<GameCamera>* stateLerp = m_gameCamera->GetStateLerp();
	// ���n���J�����擾
	CameraStateOverLooking3D* overLooking3D = m_gameCamera->GetStateOverLooking3D();
	// �⊮�ݒ�
	stateLerp->LerpSetting(overLooking3D, KT::GameParam::LERP_TIME_OVERLOOKING);
	stateLerp->PositionSetting(m_gameCamera->GetEyePosition(), overLooking3D->GetBasePosition() * 0.5f);
	stateLerp->TargetSetting(m_gameCamera->GetTargetPosition(), overLooking3D->GetTargetPosition());
	stateLerp->RotationSetting(m_gameCamera->GetRotation(), SimpleMath::Quaternion::Identity);
	// �⊮�J�����ݒ�
	m_gameCamera->SetNextCamera(stateLerp);
	m_gameCamera->SetCameraState(KT::GameParam::CameraState::OPERATION);
}

//------------------------------------------------------------------
/**
 * @brief �J�����ʒu�擾
 *
 * @param �Ȃ�
 * @return Vector3�F�J�����ʒu
 */
const DirectX::SimpleMath::Vector3& CameraStateTracking3D::GetEyePosition() const
{
	// �����_
	if(m_gameCamera->CheckSightType(KT::GameParam::SightType::SIDE))
		return KT::GameParam::EYE_OFFSET_SIDE;

	// �����낵���_
	return KT::GameParam::EYE_OFFSET_TOPDOWN;
}

//------------------------------------------------------------------
/**
 * @brief �����낵�֑ؑO�̉�]�擾
 *
 * @param �Ȃ�
 * @return Quaternion�F��]
 */
const DirectX::SimpleMath::Quaternion& CameraStateTracking3D::GetBeforeRotation() const
{
	return m_beforeRotation;
}

//------------------------------------------------------------------
/**
 * @brief ���쒆�t���O
 *
 * @param �Ȃ�
 * @return false�F�����
 */
bool CameraStateTracking3D::IsOperation()
{
	return false;
}
