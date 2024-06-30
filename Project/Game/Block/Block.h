/**
 *
 * @file Block.h
 *
 * @brief ステージを形成するブロックの基底クラスのヘッダーファイル
 *
 * @author Kato Yuki
 *
 * @date 2023/12/28
 *
 */
#pragma once

#include "Model.h"
#include "Game/Block/IBlock.h"
#include "Game/MyLibrary/GameObject/GameObject.h"
#include "Game/MyLibrary/Collision/Collider.h"

class Block : public IBlock, public GameObject
{
//----------------------------------------------
// 変数
//----------------------------------------------
private:

	// ブロックの種類
	KT::Block::Type m_type;
	// ブロックの当たり判定モード
	KT::Block::CollisionMode m_collisionMode;
	// モデル
	DirectX::Model* m_model;
	// 当たり判定図形
	std::unique_ptr<Collider> m_collider;

//----------------------------------------------
// 関数
//----------------------------------------------
public:

	// コンストラクタ
	Block(
		KT::Block::Type type,
		KT::Block::CollisionMode collisionMode,
		const DirectX::SimpleMath::Vector3& position,
		DirectX::Model* model
	);
	// デストラクタ
	virtual ~Block();

	// 初期化
	virtual void Initialize(std::function<void(DirectX::IEffect* effect)> effect = nullptr) override;
	// 更新
	virtual void Update() override;
	// 描画
	virtual void Render(
		DirectX::SimpleMath::Matrix view,
		DirectX::SimpleMath::Matrix projection,
		std::function<void()> custom = nullptr) override;
	// 後処理
	void Finalize() override;

	// ブロック種類の取得
	KT::Block::Type GetType() override;
	// ブロック種類の設定
	void SetType(KT::Block::Type type) override;
	// モデル取得
	DirectX::Model* GetModel() const;
	// 当たり判定境界図形取得
	Collider* GetCollider() const;
	// 当たり判定境界図形設定
	void SetCollider(std::unique_ptr<Collider> collider);
	// 当たり判定モード取得
	KT::Block::CollisionMode GetCollisionMode() const;
};