/**
 *
 * @file BlockFactory.h
 *
 * @brief �u���b�N�̐���������N���X�̃w�b�_�[�t�@�C��
 *
 * @author Kato Yuki
 *
 * @date 2023/12/28
 *
 */
#pragma once

#include "Model.h"
#include "Game/Block/Block.h"
#include "Game/Block/BlockType.h"
#include "Game/MyLibrary/Collision/Collider.h"

class BlockFactory
{
//----------------------------------------------
// �֐�
//----------------------------------------------
public:

	// �u���b�N�̐���
	static std::unique_ptr<Block> CreateBlock(
		KT::Block::Type type, 
		const DirectX::SimpleMath::Vector3& position
	);

private:

	// �u���b�N�̍쐬
	template <typename T>
	static std::unique_ptr<Block> CreateBlock(
		KT::Block::Type type,
		KT::Block::CollisionMode collisionMode,
		const DirectX::SimpleMath::Vector3& position,
		DirectX::Model* model,
		Collider::Shape shape = Collider::Shape::BOX,
		bool isCollision = false
	);
	// �u���b�N�̓����蔻�苫�E�}�`�쐬
	static std::unique_ptr<Collider> CreateCollision(
		Collider::Shape shape,
		const DirectX::SimpleMath::Vector3& position,
		DirectX::Model* model,
		bool isCollision
	);
};

//----------------------------------------------
// �e���v���[�g�֐��̒�`
//----------------------------------------------

//------------------------------------------------------------------
/**
 * @brief �u���b�N�̐���
 *
 * @param  type                  �F�u���b�N�̎��
 * @param  collisionMode         �F�����蔻�胂�[�h
 * @param  position              �F�����ʒu
 * @param  model                 �F�u���b�N���f��
 * @param  shape                 �F�����蔻�苫�E�}�`
 * @param  isCollision           �F�����蔻�����邩�ǂ���
 * @return std::unique_ptr<Block>�F���������u���b�N
 */
template<typename T>
inline std::unique_ptr<Block> BlockFactory::CreateBlock(
	KT::Block::Type type,
	KT::Block::CollisionMode collisionMode,
	const DirectX::SimpleMath::Vector3& position,
	DirectX::Model* model,
	Collider::Shape shape,
	bool isCollision
)
{
	// �u���b�N����
	std::unique_ptr<Block> block;
	block.reset(new T(type, collisionMode, position, model));

	// �����蔻�����郂�[�h�Ȃ瓖���蔻��𐶐�
	if(collisionMode != KT::Block::CollisionMode::NONE)
	{
		std::unique_ptr<Collider> col = CreateCollision(shape, position, model, isCollision);
		block->SetCollider(std::move(col));
	}

	return std::move(block);
}
