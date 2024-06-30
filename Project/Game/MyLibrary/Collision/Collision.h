/**
 *
 * @file Collision.h
 *
 * @brief 当たり判定処理を行うクラスのヘッダーファイル
 *
 * @author Kato Yuki
 *
 * @date 2024/1/3
 *
 */
#pragma once

#include <functional>

class Collider;
class BoxCollider;

class Collision
{

//----------------------------------------------
// 列挙体
//----------------------------------------------
public:

	// 当たった方向(Front方向視点基準)
	enum HitDirection
	{
		None   = 0,			// 当たっていない
		Top    = 1 << 0,	// 上に当たった
		Bottom = 1 << 1,	// 下に当たった
		Right  = 1 << 2,	// 右に当たった
		Left   = 1 << 3,	// 左に当たった
		Front  = 1 << 4,	// 奥に当たった
		Back   = 1 << 5,	// 手前に当たった
	};

//----------------------------------------------
// 関数
//----------------------------------------------
public:

	// AABB判定
	static bool AABBCheck(
		bool is2D,
		const DirectX::SimpleMath::Vector3& cameraDirection, 
		const BoxCollider& box1, 
		const BoxCollider& box2
	);

	// AABBの当たった方向を求める
	static HitDirection GetHitDirection(
		bool is2D,
		const DirectX::SimpleMath::Vector3& cameraDirection,
		BoxCollider box1,
		BoxCollider box2
	);
};