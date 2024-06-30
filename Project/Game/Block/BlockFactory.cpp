/**
 *
 * @file BlockFactory.cpp
 *
 * @brief ブロックの生成をするクラスのソースファイル
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
 * @brief ブロックの作成
 *
 * @param  type                   ：ブロックの種類
 * @param  position               ：生成位置
 * @return std::unique_ptr<Block>：生成したブロック
 */
std::unique_ptr<Block> BlockFactory::CreateBlock(KT::Block::Type type, const DirectX::SimpleMath::Vector3& position)
{
	namespace ModelName = KT::Model;


    // リソースマネージャー取得
    ResourceManager* rm = GameResource::GetInstance()->GetResourceManager();

	// 返却用
	std::unique_ptr<Block> block;

	// ブロック生成
	switch (type)
	{
	// 草
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
	// ゴースト
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
	// ゴースト床
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
	// レンガ
	case KT::Block::Type::BRICK:
	{
		block = CreateBlock<BrickBlock>(
			type,
			KT::Block::CollisionMode::BOTH, position,
			rm->GetModel(ModelName::BRICK_BLOCK)
		);
		break;
	}
	// スタート
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
	// ゴール
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
	// 始めるボタン
	case KT::Block::Type::GAME_START:
	case KT::Block::Type::GAME_START_A:
	case KT::Block::Type::GAME_START_SO:
	case KT::Block::Type::GAME_START_BU:
	{
		// 番号を求める
		int typeNum = static_cast<int>(type) - static_cast<int>(KT::Block::Type::GAME_START);
		// 番号によってモデルの名前を決める
		std::string name = ModelName::GAME_START_BLOCK + std::to_string(typeNum);

		block = CreateBlock<GameStartEndBlock>(
			type,
			KT::Block::CollisionMode::BOTH,
			position,
			rm->GetModel(name)
		);
		break;
	}
	// 終わるボタン
	case KT::Block::Type::GAME_END:
	case KT::Block::Type::GAME_END_O:
	case KT::Block::Type::GAME_END_WA:
	case KT::Block::Type::GAME_END_RU:
	{
		// 番号を求める
		int typeNum = static_cast<int>(type) - static_cast<int>(KT::Block::Type::GAME_END);
		// 番号によってモデルの名前を決める
		std::string name = ModelName::GAME_END_BLOCK + std::to_string(typeNum);

		block = CreateBlock<GameStartEndBlock>(
			type,
			KT::Block::CollisionMode::BOTH,
			position,
			rm->GetModel(name)
		);
		break;
	}
	// 未設定
	case KT::Block::Type::NONE:
	default:
		break;
	}

    return std::move(block);
}

//------------------------------------------------------------------
/**
 * @brief ブロックの当たり判定境界図形作成
 *
 * @param 　shape                         ：作成する当たり判定境界図形
 * @param 　position                      ：位置
 * @param 　model                         ：ブロックモデル
 * @param 　isCollision                   ：他のオブジェクトと判定を取るか
 * @return std::unique_ptr<CollisionShape>：作成した判定図形のユニークポインタ
 */
std::unique_ptr<Collider> BlockFactory::CreateCollision(
	Collider::Shape shape, 
	const DirectX::SimpleMath::Vector3& position, 
	DirectX::Model* model,
	bool isCollision)
{
	std::unique_ptr<Collider> collisionShape;

	// 境界図形生成
	switch (shape)
	{
	// 箱
	case Collider::Shape::BOX:
		collisionShape = std::make_unique<BoxCollider>(
			position, model->meshes[0]->boundingBox.Extents, isCollision);
		break;
	// 球
	case Collider::Shape::SPHERE:
		collisionShape = nullptr;
		break;
	// 未設定
	case Collider::Shape::NONE:
	default:
		collisionShape = nullptr;
		break;
	}

	return std::move(collisionShape);
}