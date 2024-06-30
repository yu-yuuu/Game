/**
 *
 * @file CameraProjection.cpp
 *
 * @brief �J�����Ɏg�p����ˉe�s����쐬����N���X�̃\�[�X�t�@�C��
 *
 * @author Kato Yuki
 *
 * @date 2023/11/23
 *
 */
#include "pch.h"
#include "CameraProjection.h"

//----------------------------------------------
// �萔��`
//----------------------------------------------

// ����p�i�x���@�j
const float CameraProjection::FOV = 45.0f;
//��O�̕\������
const float CameraProjection::NEAR_PLANE = 0.1f;
// ���̕\������
const float CameraProjection::FAR_PLANE = 200.0f;

// �����_���̃J�����͈�
const RECT CameraProjection::SIDE_RECT = { -8, 12, 8, -4 };
// �����낵���_���̃J�����͈�
const RECT CameraProjection::TOPDOWN_RECT = { -6, 6, 6, -6 };
// ���n����Ԃ̃J�����͈�
const RECT CameraProjection::OVER_LOOKING_RECT = { -8, 8, 8, -8 };


//------------------------------------------------------------------
/**
 * @brief �������e�i 3D �j�̎ˉe�s����쐬
 *
 * @param  aspectRatio�F��ʔ�
 * @return Matrix     �F�������e�s��
 */
DirectX::SimpleMath::Matrix CameraProjection::CreatePerspectiveProjection(const float& aspectRatio)
{
	return DirectX::SimpleMath::Matrix::CreatePerspectiveFieldOfView
	(
		FOV,
		aspectRatio,
		NEAR_PLANE,
		FAR_PLANE
	);
}

//------------------------------------------------------------------
/**
 * @brief ���s���e�i 2D �j�̎ˉe�s����쐬
 *
 * @param  aspectRatio�F��ʔ�
 * @param  rect       �F�J�����͈�
 * @return Matrix     �F���s���e�s��
 */
DirectX::SimpleMath::Matrix CameraProjection::CreateOrthographicProjection(const float& aspectRatio, const RECT& rect)
{
	return DirectX::SimpleMath::Matrix::CreateOrthographicOffCenter
	(
		static_cast<float>(rect.left)  * aspectRatio,
		static_cast<float>(rect.right) * aspectRatio,
		static_cast<float>(rect.bottom),
		static_cast<float>(rect.top),
		NEAR_PLANE, // ��O�̕\������
		FAR_PLANE	// ���̕\������
	);
}