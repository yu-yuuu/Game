/**
 *
 * @file CameraStateTracking2D.cpp
 *
 * @brief 2D�ǐՃJ�����̃\�[�X�t�@�C��
 *
 * @author Kato Yuki
 *
 * @date 2024/2/12
 *
 */
#include "pch.h"
#include "CameraStateTracking2D.h"
#include "Game/Scene/PlayScene.h"
#include "Game/Camera/SceneCamera/GameCamera.h"
#include "Game/Camera/State/CameraStateTracking3D.h"
#include "Game/Camera/State/CameraStateLerpSwitch.h"
#include "Game/Camera/State/CameraStateOverLooking2D.h"
#include "Game/MyLibrary/CommonResource/GameResource.h"
#include "Game/MyLibrary/GameParameter/GameParameter.h"

using namespace DirectX;

//------------------------------------------------------------------
/**
 * @brief �R���X�g���N�^
 *
 * @param sceneCamera�F�Q�[���J����
 */
CameraStateTracking2D::CameraStateTracking2D(GameCamera* gameCamera)
	: m_gameCamera(gameCamera)
	, m_offsetPosition()
	, m_beforeTarget()
{
}

//------------------------------------------------------------------
/**
 * @brief �f�X�g���N�^
 */
CameraStateTracking2D::~CameraStateTracking2D()
{
}

//------------------------------------------------------------------
/**
 * @brief ������
 *
 * @param  �Ȃ�
 * @return �Ȃ�
 */
void CameraStateTracking2D::Initialize()
{
	m_gameCamera->SetDimension(KT::GameParam::Dimension::_2D);
}

//------------------------------------------------------------------
/**
 * @brief �X�V
 *
 * @param  �Ȃ�
 * @return �Ȃ�
 */
void CameraStateTracking2D::Update()
{
	// �ʒu�X�V
	m_gameCamera->SetEyePosition(m_offsetPosition);

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
void CameraStateTracking2D::ChangeDimensionSetting()
{
	// �⊮�J�����擾
	CameraStateLerpSwitch<GameCamera>* stateLerp = m_gameCamera->GetStateLerp();
	// �؂�ւ���J�����擾
	CameraStateTracking3D* state3D = m_gameCamera->GetStateTrack3D();
	// �⊮�ݒ�
	stateLerp->LerpSetting(state3D, KT::GameParam::LERP_TIME_DIMENSION);
	stateLerp->PositionSetting(m_gameCamera->GetEyePosition(), state3D->GetEyePosition());
	stateLerp->ProjectionSetting(m_gameCamera->GetProjectionMatrix(), CameraProjection::CreatePerspectiveProjection(m_gameCamera->GetAspectRatio()));
	// ���̃J�����ݒ�
	m_gameCamera->SetNextCamera(stateLerp);
}

//------------------------------------------------------------------
/**
 * @brief ���n���J�����֐؂�ւ��ėǂ����m�F
 *
 * @param  �Ȃ�
 * @return true �F�؂�ւ���
 * @return false�F�؂�ւ��s��
 */
bool CameraStateTracking2D::CheckChangeOverLooking()
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
void CameraStateTracking2D::ChangeOverLookingSetting()
{
	// ���݂̒����_��ۑ����Ă���
	m_beforeTarget = m_gameCamera->GetTargetPosition();
	// �⊮�J�����擾
	CameraStateLerpSwitch<GameCamera>* stateLerp = m_gameCamera->GetStateLerp();
	// �⊮�ݒ�
	stateLerp->LerpSetting(m_gameCamera->GetStateOverLooking2D(), KT::GameParam::LERP_TIME_OVERLOOKING);
	stateLerp->ProjectionSetting(m_gameCamera->GetProjectionMatrix(),
		CameraProjection::CreateOrthographicProjection(m_gameCamera->GetAspectRatio(), 
			CameraProjection::OVER_LOOKING_RECT)
	);
	// ���̃J�������Z�b�g
	m_gameCamera->SetNextCamera(stateLerp);
	m_gameCamera->SetCameraState(KT::GameParam::CameraState::OPERATION);
}

//------------------------------------------------------------------
/**
 * @brief �J�����ʒu�擾
 *
 * @param  �Ȃ�
 * @return Vector3�F�J�����ʒu
 */
const DirectX::SimpleMath::Vector3& CameraStateTracking2D::GetEyePosition() const
{
	return m_offsetPosition;
}

//------------------------------------------------------------------
/**
 * @brief �J�����ʒu�ݒ�
 *
 * @param eyeOffsetPosition�F�ݒ肷��J�����ʒu
 * @return �Ȃ�
 */
void CameraStateTracking2D::SetEyePosition(const DirectX::SimpleMath::Vector3& eyeOffsetPosition)
{
	m_offsetPosition = eyeOffsetPosition;
}

//------------------------------------------------------------------
/**
 * @brief �ۑ����Ă��钍���_�擾
 *
 * @param �Ȃ�
 * @return Vector3�F�����_
 */
const DirectX::SimpleMath::Vector3& CameraStateTracking2D::GetBeforeTarget() const
{
	return m_beforeTarget;
}

//------------------------------------------------------------------
/**
 * @brief ���쒆�t���O
 *
 * @param �Ȃ�
 * @return false�F����\
 */
bool CameraStateTracking2D::IsOperation()
{
	return false;
}

//------------------------------------------------------------------
/**
 * @brief �����ݒ�
 *
 * @param  eyePosition�F�ݒ肷��J�����ʒu
 * @return �Ȃ�
 */
void CameraStateTracking2D::InitSetting(const DirectX::SimpleMath::Vector3& eyePosition)
{
	SetEyePosition(eyePosition);
}