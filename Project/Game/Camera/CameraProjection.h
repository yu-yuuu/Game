/**
 *
 * @file CameraProjection.h
 *
 * @brief �J�����Ɏg�p����ˉe�s����쐬����N���X�̃w�b�_�[�t�@�C��
 *
 * @author Kato Yuki
 *
 * @date 2023/11/23
 *
 */
#pragma once


class CameraProjection
{
//----------------------------------------------
// �萔
//----------------------------------------------
private:

	// ����p�i�x���@�j
	static const float FOV;
	// ��O�̕\������
	static const float NEAR_PLANE;
	// ���̕\������
	static const float FAR_PLANE;
	
public:

	// �����_���̃J�����͈�
	static const RECT SIDE_RECT;
	// �����낵���_���̃J�����͈�
	static const RECT TOPDOWN_RECT;
	// ���n����Ԃ̃J�����͈�
	static const RECT OVER_LOOKING_RECT;

//----------------------------------------------
// �֐�
//----------------------------------------------
public:

	// �������e�i 3D �j�̎ˉe�s����쐬
	static DirectX::SimpleMath::Matrix CreatePerspectiveProjection(const float& aspectRatio);
	// ���s���e�i 2D �j�̎ˉe�s����쐬
	static DirectX::SimpleMath::Matrix CreateOrthographicProjection(const float& aspectRatio, const RECT& rect);
};