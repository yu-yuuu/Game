/**
 *
 * @file Blocks.cpp
 *
 * @brief �e�u���b�N�N���X���`����\�[�X�t�@�C��
 *
 * @author Kato Yuki
 *
 * @date 2023/12/28
 *
 */
#include "pch.h"
#include "Blocks.h"
#include "Game/MyLibrary/CommonResource/GameResource.h"
#include "Game/Effect/GoalEffect.h"

//------------------------------------------------------------------
/**
 * @brief �R���X�g���N�^�i���u���b�N�j
 *
 * @param  type         �F�u���b�N�̎��
 * @param  collisionMode�F�����蔻�胂�[�h
 * @param  position     �F�����ʒu
 * @param  model        �F�u���b�N���f��
 */
GrassBlock::GrassBlock(
	KT::Block::Type						type,
	KT::Block::CollisionMode			collisionMode,
	const DirectX::SimpleMath::Vector3& position,
	DirectX::Model*						model
)
	: Block(type, collisionMode, position, model)
{
}

//------------------------------------------------------------------
/**
 * @brief �R���X�g���N�^�i�S�[�X�g�u���b�N�j
 *
 * @param  type         �F�u���b�N�̎��
 * @param  collisionMode�F�����蔻�胂�[�h
 * @param  position     �F�����ʒu
 * @param  model        �F�u���b�N���f��
 */
GhostBlock::GhostBlock(
	KT::Block::Type						type,
	KT::Block::CollisionMode			collisionMode,
	const DirectX::SimpleMath::Vector3& position,
	DirectX::Model* model
)
	: Block(type, collisionMode, position, model)
{
}

//------------------------------------------------------------------
/**
 * @brief �R���X�g���N�^�i�S�[�X�g���u���b�N�j
 *
 * @param  type         �F�u���b�N�̎��
 * @param  collisionMode�F�����蔻�胂�[�h
 * @param  position     �F�����ʒu
 * @param  model        �F�u���b�N���f��
 */
GhostFloorBlock::GhostFloorBlock(
	KT::Block::Type						type,
	KT::Block::CollisionMode			collisionMode,
	const DirectX::SimpleMath::Vector3& position,
	DirectX::Model* model
)
	: Block(type, collisionMode, position, model)
{
}

//------------------------------------------------------------------
/**
 * @brief �R���X�g���N�^�i�����K�u���b�N�j
 *
 * @param  type         �F�u���b�N�̎��
 * @param  collisionMode�F�����蔻�胂�[�h
 * @param  position     �F�����ʒu
 * @param  model        �F�u���b�N���f��
 */
BrickBlock::BrickBlock(
	KT::Block::Type						type,
	KT::Block::CollisionMode			collisionMode,
	const DirectX::SimpleMath::Vector3& position,
	DirectX::Model* model
)
	: Block(type, collisionMode, position, model)
{
}

//------------------------------------------------------------------
/**
 * @brief �R���X�g���N�^�i�X�^�[�g�u���b�N�j
 *
 * @param  type         �F�u���b�N�̎��
 * @param  collisionMode�F�����蔻�胂�[�h
 * @param  position     �F�����ʒu
 * @param  model        �F�u���b�N���f��
 */
StartBlock::StartBlock(
	KT::Block::Type						type,
	KT::Block::CollisionMode			collisionMode,
	const DirectX::SimpleMath::Vector3& position,
	DirectX::Model* model
)
	: Block(type, collisionMode, position, model)
{
}

//------------------------------------------------------------------
/**
 * @brief �R���X�g���N�^�i�S�[���u���b�N�j
 *
 * @param  type         �F�u���b�N�̎��
 * @param  collisionMode�F�����蔻�胂�[�h
 * @param  position     �F�����ʒu
 * @param  model        �F�u���b�N���f��
 */
GoalBlock::GoalBlock(
	KT::Block::Type						type,
	KT::Block::CollisionMode			collisionMode,
	const DirectX::SimpleMath::Vector3& position,
	DirectX::Model* model
)
	: Block(type, collisionMode, position, model)
	, m_goalEffect(nullptr)
{

}

//------------------------------------------------------------------
/**
 * @brief �f�X�g���N�^
 */
GoalBlock::~GoalBlock()
{
	// �S�[���G�t�F�N�g���폜
	EffectManager* effectManager = GameResource::GetInstance()->GetEffectManager();
	effectManager->DeleteEffect(m_goalEffect.get());
}

//------------------------------------------------------------------
/**
 * @brief ������
 *
 * @param  effect�F���f���ɓK��������G�t�F�N�g
 * @return �Ȃ�
 */
void GoalBlock::Initialize(std::function<void(DirectX::IEffect* effect)> effect)
{
	// �S�[���G�t�F�N�g��o�^
	EffectManager* effectManager = GameResource::GetInstance()->GetEffectManager();
	m_goalEffect = std::make_unique<GoalEffect>(
		effectManager,
		GetPosition(),
		KT::Texture::PARTICLE_DUST,
		EFFECT_GENERATE_INTERVAL
	);
	effectManager->AddEffect(m_goalEffect.get());

	// ���N���X�̏�����
	Block::Initialize(effect);
}

//------------------------------------------------------------------
/**
 * @brief �R���X�g���N�^�i�Q�[���X�^�[�g�A�G���h�u���b�N�j
 *
 * @param  type         �F�u���b�N�̎��
 * @param  collisionMode�F�����蔻�胂�[�h
 * @param  position     �F�����ʒu
 * @param  model        �F�u���b�N���f��
 */
GameStartEndBlock::GameStartEndBlock(
	KT::Block::Type					type,
	KT::Block::CollisionMode		collisionMode,
	const DirectX::SimpleMath::Vector3& position,
	DirectX::Model* model
)
	: Block(type, collisionMode, position, model)
{
}