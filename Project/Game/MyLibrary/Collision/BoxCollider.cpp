/**
 *
 * @file BoxCollider.cpp
 *
 * @brief 当たり判定に使用する箱を表すクラスのソースファイル
 *
 * @author Kato Yuki
 *
 * @date 2024/1/5
 *
 */
#include "pch.h"
#include "BoxCollider.h"

using namespace DirectX;

//------------------------------------------------------------------
/**
 * @brief コンストラクタ
 *
 * @param position   ：位置
 * @param extents    ：中心から各面までの距離
 * @param isCollision：他のオブジェクトと判定を取るか
 */
BoxCollider::BoxCollider(
	DirectX::SimpleMath::Vector3 position, 
	DirectX::SimpleMath::Vector3 extents, 
	bool isCollision
)
	: Collider(Collider::Shape::BOX, position, isCollision)
	, m_extents(extents)
	, m_boundingBox{ position, extents }
{
}

//------------------------------------------------------------------
/**
 * @brief デストラクタ
 */
BoxCollider::~BoxCollider()
{
}

//------------------------------------------------------------------
/**
 * @brief 位置の設定
 *
 * @param  position：設定する位置
 * @return なし
 */
void BoxCollider::SetPosition(const DirectX::SimpleMath::Vector3& position)
{
	Collider::SetPosition(position);
	m_boundingBox.Center = position;
}

//------------------------------------------------------------------
/**
 * @brief  当たり判定ボックスの取得
 *
 * @param  なし
 * @return CollisionBox：当たり判定ボックス
 */
const BoxCollider& BoxCollider::GetCollisionBox() const
{
	return *this;
}

//------------------------------------------------------------------
/**
 * @brief  各面までの距離取得
 *
 * @param なし
 * @return Vector3：各面までの距離
 */
const DirectX::SimpleMath::Vector3& BoxCollider::GetExtents() const
{
	return m_extents;
}

//------------------------------------------------------------------
/**
 * @brief DirectXバウンディングボックスの取得
 *
 * @param なし
 * @return BoundingBox：DirectXバウンディングボックス
 */
const DirectX::BoundingBox& BoxCollider::GetBoundingBox() const
{
	return m_boundingBox;
}

//------------------------------------------------------------------
/**
 * @brief 箱の頂点取得
 *
 * @param  max：座標が大きい方の頂点
 * @param  min：座標が小さい方の頂点
 * @return なし
 */
void BoxCollider::GetCorners(DirectX::SimpleMath::Vector3& min, DirectX::SimpleMath::Vector3& max)
{
	min = GetPosition() - m_extents;
	max = GetPosition() + m_extents;
}