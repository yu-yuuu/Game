/**
 *
 * @file CollisionManager.h
 *
 * @brief �����蔻�菈�����ꊇ���čs���}�l�[�W���[�N���X�̃w�b�_�[�t�@�C��
 *
 * @author Kato Yuki
 *
 * @date 2024/1/4
 *
 */
#pragma once

#include <vector>

class Collider;

class CollisionManager
{
//----------------------------------------------
// �\����
//----------------------------------------------
private:

	// �ړ��I�u�W�F�N�g
	struct MoveObject
	{
		// �����蔻��
		Collider* collider;
		// �Փˉ������܂Ƃ߂čs����
		bool isLater;
		// ���������I�u�W�F�N�g���X�g
		std::vector<Collider*> hitCollider;
	
	};

//----------------------------------------------
// �ϐ�
//----------------------------------------------
private:

	// �X�e�[�W�u���b�N
	std::vector<Collider*> m_stageBlock;

	// �X�e�[�W�Ɠ����蔻�����肽���I�u�W�F�N�g
	std::vector<MoveObject> m_collider;

//----------------------------------------------
// �֐�
//----------------------------------------------
public:

	// �R���X�g���N�^
	CollisionManager();
	// �f�X�g���N�^
	~CollisionManager();
	
	// �X�e�[�W�ƃ��C�̓����蔻����s
	std::vector<std::pair<Collider*, float>> HitRayStage(
		const DirectX::SimpleMath::Ray& ray,
		const std::vector<Collider*>& stageBlock);
	
	// �S�폜
	void Clear();
};