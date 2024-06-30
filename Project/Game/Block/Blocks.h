/**
 *
 * @file Blocks.h
 *
 * @brief 各ブロッククラスを定義するヘッダーファイル
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
// 草ブロック
//----------------------------------------------
class GrassBlock : public Block
{
public:

	// コンストラクタ
	GrassBlock(
		KT::Block::Type						type,
		KT::Block::CollisionMode			collisionMode,
		const DirectX::SimpleMath::Vector3& position,
		DirectX::Model*						model
	);

};

//----------------------------------------------
// ゴーストブロック
//----------------------------------------------
class GhostBlock : public Block
{
public:

	// コンストラクタ
	GhostBlock(
		KT::Block::Type						type,
		KT::Block::CollisionMode			collisionMode,
		const DirectX::SimpleMath::Vector3& position,
		DirectX::Model* model
	);
}; 

//----------------------------------------------
// ゴースト床ブロック
//----------------------------------------------
class GhostFloorBlock : public Block
{
public:

	// コンストラクタ
	GhostFloorBlock(
		KT::Block::Type						type,
		KT::Block::CollisionMode			collisionMode,
		const DirectX::SimpleMath::Vector3& position,
		DirectX::Model* model
	);
};

//----------------------------------------------
// レンガブロック
//----------------------------------------------
class BrickBlock : public Block
{
public:

	// コンストラクタ
	BrickBlock(
		KT::Block::Type						type,
		KT::Block::CollisionMode			collisionMode,
		const DirectX::SimpleMath::Vector3& position,
		DirectX::Model* model
	);
};

//----------------------------------------------
// スタートブロック
//----------------------------------------------
class StartBlock : public Block
{
public:

	// コンストラクタ
	StartBlock(
		KT::Block::Type						type,
		KT::Block::CollisionMode			collisionMode,
		const DirectX::SimpleMath::Vector3& position,
		DirectX::Model* model
	);
};

//----------------------------------------------
// ゴールブロック
//----------------------------------------------
class GoalBlock : public Block
{
private:

	// エフェクトの生成感間隔
	const float EFFECT_GENERATE_INTERVAL = 0.1f;

	// エフェクト
	std::unique_ptr<GoalEffect> m_goalEffect;

public:

	// コンストラクタ
	GoalBlock(
		KT::Block::Type						type,
		KT::Block::CollisionMode			collisionMode,
		const DirectX::SimpleMath::Vector3& position,
		DirectX::Model* model
	);
	// デストラクタ
	~GoalBlock();
	// 初期化
	void Initialize(std::function<void(DirectX::IEffect* effect)> effect = nullptr) override;

};

//----------------------------------------------
// ゲームスタート、エンドブロック
//----------------------------------------------
class GameStartEndBlock : public Block
{
public:

	// コンストラクタ
	GameStartEndBlock(
		KT::Block::Type						type,
		KT::Block::CollisionMode			collisionMode,
		const DirectX::SimpleMath::Vector3& position,
		DirectX::Model* model
	);
};