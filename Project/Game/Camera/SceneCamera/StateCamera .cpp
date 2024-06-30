/**
 *
 * @file StateCamera.cpp
 *
 * @brief ��ԃJ�������g�p����J�����N���X�̃\�[�X�t�@�C��
 *
 * @author Kato Yuki
 *
 * @date 2024/1/18
 *
 */
#include "pch.h"
#include "StateCamera .h"
#include "Game/Camera/State/ICameraState.h"

//------------------------------------------------------------------
/**
 * @brief �R���X�g���N�^
 *
 * @param aspectRatio�F��ʔ�
 */
StateCamera::StateCamera(float aspectRatio)
	: Camera(aspectRatio)
	, m_currentCamera(nullptr)
	, m_nextCamera(nullptr)
{
}

//------------------------------------------------------------------
/**
 * @brief �f�X�g���N�^
 */
StateCamera ::~StateCamera()
{
}

//------------------------------------------------------------------
/**
 * @brief �X�V
 *
 * @param  �Ȃ�
 * @return �Ȃ�
 */
void StateCamera::Update()
{
	// �J�����؂�ւ�
	if (IsChange()) ChangeState();
	// ���݂̃J�����X�V
	m_currentCamera->Update();
	// ���N���X�̍X�V
	Camera::Update();
}

//------------------------------------------------------------------
/**
 * @brief ��Ԑ؂�ւ�
 *
 * @param  �Ȃ�
 * @return �Ȃ�
 */
void StateCamera ::ChangeState()
{
	// ���݂̏�Ԃ��X�V
	m_currentCamera = m_nextCamera;
	// ������
	m_currentCamera->Initialize();
	// ���̏�Ԃ����Z�b�g
	m_nextCamera = nullptr;
}

//------------------------------------------------------------------
/**
 * @brief ��Ԑ؂�ւ��\��Ԃ��m�F
 *
 * @param  �Ȃ�
 * @return true �F�ؑ։�
 * @return false�F�ؑ֕s��
 */
bool StateCamera::IsChange()
{
	// ���̃J�������Z�b�g����Ă�����؂�ւ��\
	return m_nextCamera != nullptr;
}

//------------------------------------------------------------------
/**
 * @brief ���݂̏�Ԏ擾
 *
 * @param �Ȃ�
 * @return ICameraState*�F���݂̃J�������
 */
ICameraState* StateCamera::GetCurrentCameraState()
{
	return m_currentCamera;
}

//------------------------------------------------------------------
/**
 * @brief ������Ԑݒ�
 *
 * @param  initialCamera�F�ŏ��̃J�������
 * @return �Ȃ�
 */
void StateCamera::SetInitialCamera(ICameraState* initialCamera)
{
	// ���̃J�����ɐݒ�
	SetNextCamera(initialCamera);
	// ��Ԑ؂�ւ�
	ChangeState();
}

//------------------------------------------------------------------
/**
 * @brief ���̃J�����ݒ�
 *
 * @param nextCamera�F���̃J����
 * @return �Ȃ�
 */
void StateCamera::SetNextCamera(ICameraState* nextCamera)
{
	m_nextCamera = nextCamera;
}

//------------------------------------------------------------------
/**
 * @brief �ؑ֒��t���O
 *
 * @param �Ȃ�
 * @return true �F����s��
 * @return false�F�����
 */
bool StateCamera::IsOperation()
{
	return m_currentCamera->IsOperation();
}
