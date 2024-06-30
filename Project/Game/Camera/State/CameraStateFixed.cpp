/**
 *
 * @file CameraStateFixed.cpp
 *
 * @brief �Œ�ʒu�J�����̃\�[�X�t�@�C��
 *
 * @author Kato Yuki
 *
 * @date 2024/3/2
 *
 */
#include "pch.h"
#include "CameraStateFixed.h"
#include "Game/Camera/SceneCamera/StateCamera .h"

//------------------------------------------------------------------
/**
 * @brief �R���X�g���N�^
 *
 * @param stateCamera�F�X�e�[�g�J�����̃|�C���^
 */
CameraStateFixed::CameraStateFixed(StateCamera* stateCamera)
	: m_stateCamera(stateCamera)
{
}

//------------------------------------------------------------------
/**
 * @brief �f�X�g���N�^
 */
CameraStateFixed::~CameraStateFixed()
{
}

//------------------------------------------------------------------
/**
 * @brief ������
 *
 * @param  �Ȃ�
 * @return �Ȃ�
 */
void CameraStateFixed::Initialize()
{
}

//------------------------------------------------------------------
/**
 * @brief �X�V
 *
 * @param  �Ȃ�
 * @return �Ȃ�
 */
void CameraStateFixed::Update()
{
}

//------------------------------------------------------------------
/**
 * @brief ���쒆�t���O
 *
 * @param  �Ȃ�
 * @return false�F����\
 */
bool CameraStateFixed::IsOperation()
{
	return false;
}
