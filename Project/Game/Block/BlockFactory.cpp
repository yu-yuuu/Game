/**
 *
 * @file BlockFactory.cpp
 *
 * @brief �u���b�N�̐���������N���X�̃\�[�X�t�@�C��
 *
 * @author Kato Yuki
 *
 * @date 2023/12/28
 *
 */
#include "pch.h"
#include "BlockFactory.h"
#include "Game/MyLibrary/CommonResource/GameResource.h"
#include "Game/Block/Blocks.h"
#include "Game/MyLibrary/Collision/BoxCollider.h"

//------------------------------------------------------------------
/**
 * @brief �u���b�N�̍쐬
 *
 * @param  type                   �F�u���b�N�̎��
 * @param  position               �F�����ʒu
 * @return std::unique_ptr<Block>�F���������u���b�N
 */
std::unique_ptr<Block> BlockFactory::CreateBlock(KT::Block::Type type, const DirectX::SimpleMath::Vector3& position)
{
	namespace ModelName = KT::Model;


    // ���\�[�X�}�l�[�W���[�擾
    ResourceManager* rm = GameResource::GetInstance()->GetResourceManager();

	// �ԋp�p
	std::unique_ptr<Block> block;

	// �u���b�N����
	switch (type)
	{
	// ��
	case KT::Block::Type::GRASS:
	{
		block = CreateBlock<GrassBlock>(
			type,
			KT::Block::CollisionMode::BOTH,
			position,
			rm->GetModel(ModelName::GRASS_BLOCK)
		);
		break;
	}
	// �S�[�X�g
	case KT::Block::Type::GHOST:
	{
		block = CreateBlock<GhostBlock>(
			type,
			KT::Block::CollisionMode::_3D,
			position,
			rm->GetModel(ModelName::GHOST_BLOCK)
		);
		break;
	}
	// �S�[�X�g��
	case KT::Block::Type::GHOST_FLOOR:
	{
		block = CreateBlock<GhostFloorBlock>(
			type,
			KT::Block::CollisionMode::BOTH,
			position,
			rm->GetModel(ModelName::GHOST_FLOOR_BLOCK)
		);
		break;
	}
	// �����K
	case KT::Block::Type::BRICK:
	{
		block = CreateBlock<BrickBlock>(
			type,
			KT::Block::CollisionMode::BOTH, position,
			rm->GetModel(ModelName::BRICK_BLOCK)
		);
		break;
	}
	// �X�^�[�g
	case KT::Block::Type::START:
	{
		block = CreateBlock<StartBlock>(
			type,
			KT::Block::CollisionMode::NONE,
			position,
			nullptr
		);
		break;
	}
	// �S�[��
	case KT::Block::Type::GOAL:
	{
		block = CreateBlock<GoalBlock>(
			type,
			KT::Block::CollisionMode::BOTH,
			position,
			rm->GetModel(ModelName::GOAL_BLOCK)
		);
		break;
	}
	// �n�߂�{�^��
	case KT::Block::Type::GAME_START:
	case KT::Block::Type::GAME_START_A:
	case KT::Block::Type::GAME_START_SO:
	case KT::Block::Type::GAME_START_BU:
	{
		// �ԍ������߂�
		int typeNum = static_cast<int>(type) - static_cast<int>(KT::Block::Type::GAME_START);
		// �ԍ��ɂ���ă��f���̖��O�����߂�
		std::string name = ModelName::GAME_START_BLOCK + std::to_string(typeNum);

		block = CreateBlock<GameStartEndBlock>(
			type,
			KT::Block::CollisionMode::BOTH,
			position,
			rm->GetModel(name)
		);
		break;
	}
	// �I���{�^��
	case KT::Block::Type::GAME_END:
	case KT::Block::Type::GAME_END_O:
	case KT::Block::Type::GAME_END_WA:
	case KT::Block::Type::GAME_END_RU:
	{
		// �ԍ������߂�
		int typeNum = static_cast<int>(type) - static_cast<int>(KT::Block::Type::GAME_END);
		// �ԍ��ɂ���ă��f���̖��O�����߂�
		std::string name = ModelName::GAME_END_BLOCK + std::to_string(typeNum);

		block = CreateBlock<GameStartEndBlock>(
			type,
			KT::Block::CollisionMode::BOTH,
			position,
			rm->GetModel(name)
		);
		break;
	}
	// ���ݒ�
	case KT::Block::Type::NONE:
	default:
		break;
	}

    return std::move(block);
}

//------------------------------------------------------------------
/**
 * @brief �u���b�N�̓����蔻�苫�E�}�`�쐬
 *
 * @param �@shape                         �F�쐬���铖���蔻�苫�E�}�`
 * @param �@position                      �F�ʒu
 * @param �@model                         �F�u���b�N���f��
 * @param �@isCollision                   �F���̃I�u�W�F�N�g�Ɣ������邩
 * @return std::unique_ptr<CollisionShape>�F�쐬��������}�`�̃��j�[�N�|�C���^
 */
std::unique_ptr<Collider> BlockFactory::CreateCollision(
	Collider::Shape shape, 
	const DirectX::SimpleMath::Vector3& position, 
	DirectX::Model* model,
	bool isCollision)
{
	std::unique_ptr<Collider> collisionShape;

	// ���E�}�`����
	switch (shape)
	{
	// ��
	case Collider::Shape::BOX:
		collisionShape = std::make_unique<BoxCollider>(
			position, model->meshes[0]->boundingBox.Extents, isCollision);
		break;
	// ��
	case Collider::Shape::SPHERE:
		collisionShape = nullptr;
		break;
	// ���ݒ�
	case Collider::Shape::NONE:
	default:
		collisionShape = nullptr;
		break;
	}

	return std::move(collisionShape);
}