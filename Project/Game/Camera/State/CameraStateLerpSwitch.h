/**
 *
 * @file CameraStateLerpSwitch.h
 *
 * @brief �J�����̈ʒu�A��]�A�ˉe�s�����`�⊮�Ő؂�ւ���N���X
 *
 * @author Kato Yuki
 *
 * @date 20242/14
 *
 */
#pragma once

#include <vector>
#include "Game/Camera/State/ICameraState.h"
#include "Game/Camera/CameraProjection.h"
#include "Game/MyLibrary/CommonResource/GameResource.h"

template<typename ParentCamera>
class CameraStateLerpSwitch : public ICameraState
{
//----------------------------------------------
// �ϐ�
//----------------------------------------------
private:

	// ���̏�Ԃ��g�p����J����
	ParentCamera* m_camera;
	// �⊮��ɐ؂�ւ���J�������
	ICameraState* m_nextCamera;

	// �⊮�O�̃J�����ʒu
	DirectX::SimpleMath::Vector3 m_beforeEye;
	// �⊮��̃J�����ʒu
	DirectX::SimpleMath::Vector3 m_afterEye;
	// �⊮�O�̒����_�ʒu
	DirectX::SimpleMath::Vector3 m_beforeTarget;
	// �⊮��̒����_�ʒu
	DirectX::SimpleMath::Vector3 m_afterTarget;
	// �⊮�O�̉�]
	DirectX::SimpleMath::Quaternion m_beforeRotation;
	// �⊮��̉�]
	DirectX::SimpleMath::Quaternion m_afterRotation;
	// �⊮�O�̎ˉe�s��
	DirectX::SimpleMath::Matrix m_beforeProjection;
	// �⊮��̎ˉe�s��
	DirectX::SimpleMath::Matrix m_afterProjection;

	// �⊮�Ɋ|���鎞��
	float m_lerpTime;
	// �⊮�^�C�}�[
	float m_switchTimer;

//----------------------------------------------
// �֐�
//----------------------------------------------
public:

	// �R���X�g���N�^
	CameraStateLerpSwitch(ParentCamera* camera);
	// �f�X�g���N�^
	~CameraStateLerpSwitch();

	// ������
	void Initialize() override;
	// �X�V
	void Update() override;
	// ���쒆�t���O
	bool IsOperation() override;
	
	// �⊮�̃X�L�b�v
	void Skip();

	// �⊮�ݒ�
	void LerpSetting(ICameraState* nextCamera, const float& lerpTime);
	// �ʒu�ݒ�
	void PositionSetting(const DirectX::SimpleMath::Vector3& beforeEye, const DirectX::SimpleMath::Vector3& afterEye);
	// �����_�ݒ�
	void TargetSetting(const DirectX::SimpleMath::Vector3& beforeTarget, const DirectX::SimpleMath::Vector3& afterTarget);
	// ��]�ݒ�
	void RotationSetting(const DirectX::SimpleMath::Quaternion& beforeRotation, const DirectX::SimpleMath::Quaternion& afterRotation);
	// �ˉe�s��ݒ�
	void ProjectionSetting(const DirectX::SimpleMath::Matrix& beforeProjection, const DirectX::SimpleMath::Matrix& afterProjection);

private:

	// �⊮���J�n���Ă悢��
	bool IsStart();
	// �⊮
	bool Lerp();

	// �ړ��⊮
	void LerpMovement(const float& lerpRatio);
	// �����_�⊮
	void LerpTarget(const float& lerpRatio);
	// ��]�⊮
	void LerpRotation(const float& lerpRatio);
	// �ˉe�s��⊮
	void LerpProjection(const float& lerpRatio);
	// �p�����[�^���Z�b�g
	void Reset();
};


//-------------------------------------------------------------------------------------------
// �֐���`
//-------------------------------------------------------------------------------------------

//------------------------------------------------------------------
/**
 * @brief �R���X�g���N�^
 *
 * @param camera�F���̏�Ԃ��g�p����J�����̃|�C���^
 */
template<typename ParentCamera>
inline CameraStateLerpSwitch<ParentCamera>::CameraStateLerpSwitch(ParentCamera* camera)
	: m_camera(camera)
	, m_nextCamera(nullptr)
	, m_beforeEye()
	, m_afterEye()
	, m_beforeRotation()
	, m_afterRotation()
	, m_beforeProjection()
	, m_afterProjection()
	, m_lerpTime(0.0f)
	, m_switchTimer(0.0f)
{
}

//------------------------------------------------------------------
/**
 * @brief �f�X�g���N�^
 *
 */
template<typename ParentCamera>
inline CameraStateLerpSwitch<ParentCamera>::~CameraStateLerpSwitch()
{
}

//------------------------------------------------------------------
/**
 * @brief ������
 *
 * @param  �Ȃ�
 * @return �Ȃ�
 */
template<typename ParentCamera>
inline void CameraStateLerpSwitch<ParentCamera>::Initialize()
{

}

//------------------------------------------------------------------
/**
 * @brief �X�V
 *
 * @param  �Ȃ�
 * @return �Ȃ�
 */
template<typename ParentCamera>
inline void CameraStateLerpSwitch<ParentCamera>::Update()
{
	// �⊮�J�n�\�łȂ��Ȃ�I��
	if (!IsStart()) return;
	// �⊮�����������玟�̏�����
	if (!Lerp()) return;

	// ���̏�Ԃ̃J������ݒ�
	m_camera->SetNextCamera(m_nextCamera);
	// �p�����[�^�[�����Z�b�g
	Reset();
}

//------------------------------------------------------------------
/**
 * @brief ���쒆��
 *
 * @param  �Ȃ�
 * @return true�F���쒆
 */
template<typename ParentCamera>
inline bool CameraStateLerpSwitch<ParentCamera>::IsOperation()
{
	return true;
}

//------------------------------------------------------------------
/**
 * @brief �⊮�̃X�L�b�v
 *
 * @param  �Ȃ�
 * @return �Ȃ�
 */
template<typename ParentCamera>
inline void CameraStateLerpSwitch<ParentCamera>::Skip()
{
	m_switchTimer = m_lerpTime;
}

//------------------------------------------------------------------
/**
 * @brief �⊮�ݒ�
 *
 * @param  nextCamera�F�⊮��ɐ؂�ւ���J����
 * @param  lerpTime  �F�⊮�Ɋ|���鎞��
 * @return �Ȃ�
 */
template<typename ParentCamera>
inline void CameraStateLerpSwitch<ParentCamera>::LerpSetting(ICameraState* nextCamera, const float& lerpTime)
{
	m_nextCamera = nextCamera;
	m_lerpTime = lerpTime;
}

//------------------------------------------------------------------
/**
 * @brief �ʒu�⊮�̐ݒ�
 *
 * @param  beforeEye�F�⊮�O�̈ʒu
 * @param  afterEye �F�⊮��̈ʒu
 * @return �Ȃ�
 */
template<typename ParentCamera>
inline void CameraStateLerpSwitch<ParentCamera>::PositionSetting(const DirectX::SimpleMath::Vector3& beforeEye, const DirectX::SimpleMath::Vector3& afterEye)
{
	m_beforeEye = beforeEye;
	m_afterEye = afterEye;
}

//------------------------------------------------------------------
/**
 * @brief �����_�⊮�̐ݒ�
 *
 * @param  beforeTarget�F�⊮�O�̈ʒu
 * @param  afterTarget �F�⊮��̈ʒu
 * @return �Ȃ�
 */
template<typename ParentCamera>
inline void CameraStateLerpSwitch<ParentCamera>::TargetSetting(const DirectX::SimpleMath::Vector3& beforeTarget, const DirectX::SimpleMath::Vector3& afterTarget)
{
	m_beforeTarget = beforeTarget;
	m_afterTarget = afterTarget;
}

//------------------------------------------------------------------
/**
 * @brief ��]�⊮�̐ݒ�
 *
 * @param  beforeRotation�F�⊮�O�̉�]
 * @param  afterRotation �F�⊮��̉�]
 * @return �Ȃ�
 */
template<typename ParentCamera>
inline void CameraStateLerpSwitch<ParentCamera>::RotationSetting(const DirectX::SimpleMath::Quaternion& beforeRotation, const DirectX::SimpleMath::Quaternion& afterRotation)
{
	m_beforeRotation = beforeRotation;
	m_afterRotation = afterRotation;
}

//------------------------------------------------------------------
/**
 * @brief �ˉe�s��⊮�̐ݒ�
 *
 * @param  beforeProjection�F�⊮�O�̎ˉe�s��
 * @param  afterProjection �F�⊮��̎ˉe�s��
 * @return �Ȃ�
 */
template<typename ParentCamera>
inline void CameraStateLerpSwitch<ParentCamera>::ProjectionSetting(const DirectX::SimpleMath::Matrix& beforeProjection, const DirectX::SimpleMath::Matrix& afterProjection)
{
	m_beforeProjection = beforeProjection;
	m_afterProjection = afterProjection;
}


//------------------------------------------------------------------
/**
 * @brief �⊮���J�n���Ă悢��
 *
 * @param  �Ȃ�
 * @return true �F�J�n�\
 * @return false�F�J�n�s��
 */
template<typename ParentCamera>
inline bool CameraStateLerpSwitch<ParentCamera>::IsStart()
{
	return m_nextCamera != nullptr;
}

//------------------------------------------------------------------
/**
 * @brief �⊮����
 *
 * @param  �Ȃ�
 * @return true �F�⊮�I��
 * @return false�F�⊮��
 */
template<typename ParentCamera>
inline bool CameraStateLerpSwitch<ParentCamera>::Lerp()
{

	// �i�s���Ԏ擾
	DX::StepTimer* stepTimer = GameResource::GetInstance()->GetStepTimer();	
	// �^�C�}�[�i�s
	m_switchTimer += static_cast<float>(stepTimer->GetElapsedSeconds());	
	// ���݂̊������v�Z
	float ratio = m_switchTimer / m_lerpTime;
	// ������100%���z���Ȃ��悤�ɂ���
	ratio = std::min(ratio, 1.0f);

	// ������100���i1.0f�j��菬�����Ȃ�؂�ւ��������s��
	if (ratio < 1.0f)
	{
		// �⊮
		if (m_beforeEye        != m_afterEye)        LerpMovement(ratio);
		if (m_beforeTarget     != m_afterTarget)     LerpTarget(ratio);
		if (m_beforeRotation   != m_afterRotation)   LerpRotation(ratio);
		if (m_beforeProjection != m_afterProjection) LerpProjection(ratio);

		// �⊮��
		return false;
	}

	// �⊮�I��
	return true;
}

//------------------------------------------------------------------
/**
 * @brief �ʒu�⊮����
 *
 * @param  lerpRatio�F�⊮�̊���
 * @return �Ȃ�
 */
template<typename ParentCamera>
inline void CameraStateLerpSwitch<ParentCamera>::LerpMovement(const float& lerpRatio)
{
	m_camera->SetEyePosition
	(
		DirectX::SimpleMath::Vector3::Lerp
		(
			m_beforeEye,
			m_afterEye,
			lerpRatio
		)
	);
}

//------------------------------------------------------------------
/**
 * @brief �����_�⊮����
 *
 * @param  lerpRatio�F�⊮�̊���
 * @return �Ȃ�
 */template<typename ParentCamera>
inline void CameraStateLerpSwitch<ParentCamera>::LerpTarget(const float& lerpRatio)
{
	m_camera->SetTargetPosition
	(
		DirectX::SimpleMath::Vector3::Lerp
		(
			m_beforeTarget,
			m_afterTarget,
			lerpRatio
		)
	);
}

//------------------------------------------------------------------
/**
 * @brief ��]�⊮����
 *
 * @param  lerpRatio�F�⊮�̊���
 * @return �Ȃ�
 */
template<typename ParentCamera>
inline void CameraStateLerpSwitch<ParentCamera>::LerpRotation(const float& lerpRatio)
{
	m_camera->SetRotation
	(
		DirectX::SimpleMath::Quaternion::Lerp
		(
			m_beforeRotation,
			m_afterRotation,
			lerpRatio
		)
	);
}

//------------------------------------------------------------------
/**
 * @brief �ˉe�s��⊮
 *
 * @param  lerpRatio�F�⊮�̊���
 * @return �Ȃ�
 */
template<typename ParentCamera>
inline void CameraStateLerpSwitch<ParentCamera>::LerpProjection(const float& lerpRatio)
{
	m_camera->SetProjectionMatrix
	(
		DirectX::SimpleMath::Matrix::Lerp
		(
			m_beforeProjection,
			m_afterProjection,
			lerpRatio
		)
	);
}

//------------------------------------------------------------------
/**
 * @brief �p�����[�^�[���Z�b�g
 *
 * @param  �Ȃ�
 * @return �Ȃ�
 */
template<typename ParentCamera>
inline void CameraStateLerpSwitch<ParentCamera>::Reset()
{
	m_beforeEye        = m_afterEye        = DirectX::SimpleMath::Vector3::Zero;
	m_beforeTarget     = m_afterTarget     = DirectX::SimpleMath::Vector3::Zero;
	m_beforeRotation   = m_afterRotation   = DirectX::SimpleMath::Quaternion::Identity;
	m_beforeProjection = m_afterProjection = DirectX::SimpleMath::Matrix::Identity;
	m_lerpTime         = m_switchTimer     = 0.0f;
	m_nextCamera       = nullptr;
}