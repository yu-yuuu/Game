/**
 *
 * @file BoxCollider.h
 *
 * @brief 当たり判定に使用する箱を表すクラスのヘッダーファイル
 *
 * @author Kato Yuki
 *
 * @date 2024/1/5
 *
 */
#pragma once

#include"Collider.h"

class BoxCollider : public Collider
{
//----------------------------------------------
// 変数
//----------------------------------------------
private:

	// 中心から各面までの距離
	DirectX::SimpleMath::Vector3 m_extents;
	// DirectXバウンディングボックス
	DirectX::BoundingBox m_boundingBox;

//----------------------------------------------
// 関数
//----------------------------------------------
public:

	// コンストラクタ
	BoxCollider(DirectX::SimpleMath::Vector3 position, DirectX::SimpleMath::Vector3 extents, bool isCollision = false);
	// デストラクタ
	~BoxCollider();
	
	// 位置の設定
	void SetPosition(const DirectX::SimpleMath::Vector3& position);
	// 当たり判定ボックスの取得
	const BoxCollider& GetCollisionBox() const;
	// 各面までの距離取得
	const DirectX::SimpleMath::Vector3& GetExtents() const;
	// DirectXバウンディングボックスの取得
	const DirectX::BoundingBox& GetBoundingBox() const;
	// 箱の頂点取得
	void GetCorners(DirectX::SimpleMath::Vector3& min, DirectX::SimpleMath::Vector3& max);
};