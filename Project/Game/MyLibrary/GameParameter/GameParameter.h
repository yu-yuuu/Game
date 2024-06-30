/**
 *
 * @file �t�@�C����.h
 *
 * @brief �ȒP�Ȑ���
 *
 * @author �������l
 *
 * @date 2024/2/11
 *
 * @note �⑫�����A����
 *
 */
#pragma once

namespace KT
{
	// �Q�[�����ň����p�����[�^�[��錾���閼�O���
	namespace GameParam
	{
		// ����
		enum class Dimension
		{
			_2D,
			_3D,
		};

		// ���_�^�C�v
		enum class SightType
		{
			TOPDOWN,
			SIDE,
		};

		// �J�����̏��
		enum class CameraState
		{
			NONE,               // �ʏ�
			OPERATION,          // ���쒆
			OPERATION_COMPLETE, // ����I��
		};

		// �ړ��������̓t���O
		enum InputDirection : int
		{
			RIGHT   = 1 << 0,	// �E
			LEFT    = 1 << 1,	// ��
			FORWARD = 1 << 2,	// ��
			BACK    = 1 << 3,	// ��O

			NONE    = 0,		// ��~
		};

		// �^�C�g���p�X�e�[�W�̔ԍ�
		static const int TITLE_STAGE_NUM = 1100;
		// �����؂�ւ����̕⊮����
		static const float LERP_TIME_DIMENSION = 0.5f;
		// �J������]���̕⊮����
		static const float LERP_TIME_ROTATION = 0.3f;
		// �Q�[���J�n���A�j���[�V�����̕⊮����
		static const float LERP_TIME_GAMESTART = 5.0f;
		// ���n���J�����ؑ֎��̕⊮����
		static const float LERP_TIME_OVERLOOKING = 1.0f;
		// 3D�����낵���_�̃J�����ʒu�I�t�Z�b�g
		static const DirectX::SimpleMath::Vector3 EYE_OFFSET_TOPDOWN = { 0.0f, -1.5f, 6.0f };
		// 3D�����_�̃J�����ʒu�I�t�Z�b�g
		static const DirectX::SimpleMath::Vector3 EYE_OFFSET_SIDE = { 0.0f, 3.0f, 5.0f };
		// �����蔻������u���b�N�̌����͈�
		static float COLLISION_RAMGE = 2.0f;
		// �S�[�X�g����2D�����ꔻ��̍���
		static float GHOST_FLOOR_CHECK_HEIGHT = 0.2f;
	}
}