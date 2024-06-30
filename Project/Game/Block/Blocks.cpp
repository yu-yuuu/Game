/**
 *
 * @file Blocks.cpp
 *
 * @brief 各ブロッククラスを定義するソースファイル
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
 * @brief コンストラクタ（草ブロック）
 *
 * @param  type         ：ブロックの種類
 * @param  collisionMode：当たり判定モード
 * @param  position     ：生成位置
 * @param  model        ：ブロックモデル
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
 * @brief コンストラクタ（ゴーストブロック）
 *
 * @param  type         ：ブロックの種類
 * @param  collisionMode：当たり判定モード
 * @param  position     ：生成位置
 * @param  model        ：ブロックモデル
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
 * @brief コンストラクタ（ゴースト床ブロック）
 *
 * @param  type         ：ブロックの種類
 * @param  collisionMode：当たり判定モード
 * @param  position     ：生成位置
 * @param  model        ：ブロックモデル
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
 * @brief コンストラクタ（レンガブロック）
 *
 * @param  type         ：ブロックの種類
 * @param  collisionMode：当たり判定モード
 * @param  position     ：生成位置
 * @param  model        ：ブロックモデル
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
 * @brief コンストラクタ（スタートブロック）
 *
 * @param  type         ：ブロックの種類
 * @param  collisionMode：当たり判定モード
 * @param  position     ：生成位置
 * @param  model        ：ブロックモデル
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
 * @brief コンストラクタ（ゴールブロック）
 *
 * @param  type         ：ブロックの種類
 * @param  collisionMode：当たり判定モード
 * @param  position     ：生成位置
 * @param  model        ：ブロックモデル
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
 * @brief デストラクタ
 */
GoalBlock::~GoalBlock()
{
	// ゴールエフェクトを削除
	EffectManager* effectManager = GameResource::GetInstance()->GetEffectManager();
	effectManager->DeleteEffect(m_goalEffect.get());
}

//------------------------------------------------------------------
/**
 * @brief 初期化
 *
 * @param  effect：モデルに適応させるエフェクト
 * @return なし
 */
void GoalBlock::Initialize(std::function<void(DirectX::IEffect* effect)> effect)
{
	// ゴールエフェクトを登録
	EffectManager* effectManager = GameResource::GetInstance()->GetEffectManager();
	m_goalEffect = std::make_unique<GoalEffect>(
		effectManager,
		GetPosition(),
		KT::Texture::PARTICLE_DUST,
		EFFECT_GENERATE_INTERVAL
	);
	effectManager->AddEffect(m_goalEffect.get());

	// 基底クラスの初期化
	Block::Initialize(effect);
}

//------------------------------------------------------------------
/**
 * @brief コンストラクタ（ゲームスタート、エンドブロック）
 *
 * @param  type         ：ブロックの種類
 * @param  collisionMode：当たり判定モード
 * @param  position     ：生成位置
 * @param  model        ：ブロックモデル
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