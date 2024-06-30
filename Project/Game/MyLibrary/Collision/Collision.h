/**
 *
 * @file Collision.h
 *
 * @brief �����蔻�菈�����s���N���X�̃w�b�_�[�t�@�C��
 *
 * @author Kato Yuki
 *
 * @date 2024/1/3
 *
 */
#pragma once

#include <functional>

class Collider;
class BoxCollider;

class Collision
{

//----------------------------------------------
// �񋓑�
//----------------------------------------------
public:

	// ������������(Front�������_�)
	enum HitDirection
	{
		None   = 0,			// �������Ă��Ȃ�
		Top    = 1 << 0,	// ��ɓ�������
		Bottom = 1 << 1,	// ���ɓ�������
		Right  = 1 << 2,	// �E�ɓ�������
		Left   = 1 << 3,	// ���ɓ�������
		Front  = 1 << 4,	// ���ɓ�������
		Back   = 1 << 5,	// ��O�ɓ�������
	};

//----------------------------------------------
// �֐�
//----------------------------------------------
public:

	// AABB����
	static bool AABBCheck(
		bool is2D,
		const DirectX::SimpleMath::Vector3& cameraDirection, 
		const BoxCollider& box1, 
		const BoxCollider& box2
	);

	// AABB�̓����������������߂�
	static HitDirection GetHitDirection(
		bool is2D,
		const DirectX::SimpleMath::Vector3& cameraDirection,
		BoxCollider box1,
		BoxCollider box2
	);
};