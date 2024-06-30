/**
 *
 * @file CollisionManager.h
 *
 * @brief �����蔻�菈�����ꊇ���čs���}�l�[�W���[�N���X�̃\�[�X�t�@�C��
 *
 * @author Kato Yuki
 *
 * @date 2024/1/4
 *
 */
#include "pch.h"
#include "CollisionManager.h"

#include "Game/MyLibrary/CommonResource/GameResource.h"

#include "Game/MyLibrary/Collision/Collider.h"
#include "Game/MyLibrary/Collision/BoxCollider.h"
#include "Game/MyLibrary/Collision/Collision.h"
#include "Game/MyLibrary/Utility/MyUtility.h"

using namespace DirectX;

//------------------------------------------------------------------
/**
 * @brief �R���X�g���N�^
 */
CollisionManager::CollisionManager()
	: m_stageBlock()
	, m_collider()
{
}

//------------------------------------------------------------------
/**
 * @brief �f�X�g���N�^
 */
CollisionManager::~CollisionManager()
{
}

//------------------------------------------------------------------
/**
 * @brief �X�e�[�W�ƃ��C�̓����蔻����s
 *
 * @param  ray       �F�X�e�[�W�ɓ��Ă郌�C
 * @param  stageBlock�F��������X�e�[�W
 * @return �Ȃ�
 */
std::vector<std::pair<Collider*, float>> CollisionManager::HitRayStage(
	const DirectX::SimpleMath::Ray& ray,
	const std::vector<Collider*>& stageBlock)
{
	// ���������I�u�W�F�N�g�폜
	std::vector<std::pair<Collider*, float>> rayHitObj;

	for (Collider* collider : stageBlock)
	{
		// �����蔻��擾
		BoxCollider* blockBox = dynamic_cast<BoxCollider*>(collider);
		// DirectX�̓����蔻��擾
		BoundingBox bb = blockBox->GetBoundingBox();
		// ���C�̓������������擾�p
		float distance = 0.0f;
		// ��������
		if (!ray.Intersects(bb, distance)) continue;

		// ���������I�u�W�F�N�g�ƒ�����ۑ�
		rayHitObj.push_back({ blockBox, distance });
	}

	return rayHitObj;
}

//------------------------------------------------------------------
/**
 * @brief ���X�g������
 *
 * @param  �Ȃ�
 * @return �Ȃ�
 */
void CollisionManager::Clear()
{
	m_stageBlock.clear();
	m_collider.clear();
}