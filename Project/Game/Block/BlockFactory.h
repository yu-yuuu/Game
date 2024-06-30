/**
 *
 * @file BlockFactory.h
 *
 * @brief ブロックの生成をするクラスのヘッダーファイル
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
// 関数
//----------------------------------------------
public:

	// ブロックの生成
	static std::unique_ptr<Block> CreateBlock(
		KT::Block::Type type, 
		const DirectX::SimpleMath::Vector3& position
	);

private:

	// ブロックの作成
	template <typename T>
	static std::unique_ptr<Block> CreateBlock(
		KT::Block::Type type,
		KT::Block::CollisionMode collisionMode,
		const DirectX::SimpleMath::Vector3& position,
		DirectX::Model* model,
		Collider::Shape shape = Collider::Shape::BOX,
		bool isCollision = false
	);
	// ブロックの当たり判定境界図形作成
	static std::unique_ptr<Collider> CreateCollision(
		Collider::Shape shape,
		const DirectX::SimpleMath::Vector3& position,
		DirectX::Model* model,
		bool isCollision
	);
};

//----------------------------------------------
// テンプレート関数の定義
//----------------------------------------------

//------------------------------------------------------------------
/**
 * @brief ブロックの生成
 *
 * @param  type                  ：ブロックの種類
 * @param  collisionMode         ：当たり判定モード
 * @param  position              ：生成位置
 * @param  model                 ：ブロックモデル
 * @param  shape                 ：当たり判定境界図形
 * @param  isCollision           ：当たり判定を取るかどうか
 * @return std::unique_ptr<Block>：生成したブロック
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
	// ブロック生成
	std::unique_ptr<Block> block;
	block.reset(new T(type, collisionMode, position, model));

	// 当たり判定を取るモードなら当たり判定を生成
	if(collisionMode != KT::Block::CollisionMode::NONE)
	{
		std::unique_ptr<Collider> col = CreateCollision(shape, position, model, isCollision);
		block->SetCollider(std::move(col));
	}

	return std::move(block);
}
