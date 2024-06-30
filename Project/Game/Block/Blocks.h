/**
 *
 * @file Blocks.h
 *
 * @brief �e�u���b�N�N���X���`����w�b�_�[�t�@�C��
 *
 * @author Kato Yuki
 *
 * @date 2023/12/28
 *
 */
#pragma once

#include "Game/Block/Block.h"

class GoalEffect;

//----------------------------------------------
// ���u���b�N
//----------------------------------------------
class GrassBlock : public Block
{
public:

	// �R���X�g���N�^
	GrassBlock(
		KT::Block::Type						type,
		KT::Block::CollisionMode			collisionMode,
		const DirectX::SimpleMath::Vector3& position,
		DirectX::Model*						model
	);

};

//----------------------------------------------
// �S�[�X�g�u���b�N
//----------------------------------------------
class GhostBlock : public Block
{
public:

	// �R���X�g���N�^
	GhostBlock(
		KT::Block::Type						type,
		KT::Block::CollisionMode			collisionMode,
		const DirectX::SimpleMath::Vector3& position,
		DirectX::Model* model
	);
}; 

//----------------------------------------------
// �S�[�X�g���u���b�N
//----------------------------------------------
class GhostFloorBlock : public Block
{
public:

	// �R���X�g���N�^
	GhostFloorBlock(
		KT::Block::Type						type,
		KT::Block::CollisionMode			collisionMode,
		const DirectX::SimpleMath::Vector3& position,
		DirectX::Model* model
	);
};

//----------------------------------------------
// �����K�u���b�N
//----------------------------------------------
class BrickBlock : public Block
{
public:

	// �R���X�g���N�^
	BrickBlock(
		KT::Block::Type						type,
		KT::Block::CollisionMode			collisionMode,
		const DirectX::SimpleMath::Vector3& position,
		DirectX::Model* model
	);
};

//----------------------------------------------
// �X�^�[�g�u���b�N
//----------------------------------------------
class StartBlock : public Block
{
public:

	// �R���X�g���N�^
	StartBlock(
		KT::Block::Type						type,
		KT::Block::CollisionMode			collisionMode,
		const DirectX::SimpleMath::Vector3& position,
		DirectX::Model* model
	);
};

//----------------------------------------------
// �S�[���u���b�N
//----------------------------------------------
class GoalBlock : public Block
{
private:

	// �G�t�F�N�g�̐������Ԋu
	const float EFFECT_GENERATE_INTERVAL = 0.1f;

	// �G�t�F�N�g
	std::unique_ptr<GoalEffect> m_goalEffect;

public:

	// �R���X�g���N�^
	GoalBlock(
		KT::Block::Type						type,
		KT::Block::CollisionMode			collisionMode,
		const DirectX::SimpleMath::Vector3& position,
		DirectX::Model* model
	);
	// �f�X�g���N�^
	~GoalBlock();
	// ������
	void Initialize(std::function<void(DirectX::IEffect* effect)> effect = nullptr) override;

};

//----------------------------------------------
// �Q�[���X�^�[�g�A�G���h�u���b�N
//----------------------------------------------
class GameStartEndBlock : public Block
{
public:

	// �R���X�g���N�^
	GameStartEndBlock(
		KT::Block::Type						type,
		KT::Block::CollisionMode			collisionMode,
		const DirectX::SimpleMath::Vector3& position,
		DirectX::Model* model
	);
};