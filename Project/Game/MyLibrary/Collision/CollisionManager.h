/**
 *
 * @file CollisionManager.h
 *
 * @brief 当たり判定処理を一括して行うマネージャークラスのヘッダーファイル
 *
 * @author Kato Yuki
 *
 * @date 2024/1/4
 *
 */
#pragma once

#include <vector>

class Collider;

class CollisionManager
{
//----------------------------------------------
// 構造体
//----------------------------------------------
private:

	// 移動オブジェクト
	struct MoveObject
	{
		// 当たり判定
		Collider* collider;
		// 衝突応答をまとめて行うか
		bool isLater;
		// 当たったオブジェクトリスト
		std::vector<Collider*> hitCollider;
	
	};

//----------------------------------------------
// 変数
//----------------------------------------------
private:

	// ステージブロック
	std::vector<Collider*> m_stageBlock;

	// ステージと当たり判定を取りたいオブジェクト
	std::vector<MoveObject> m_collider;

//----------------------------------------------
// 関数
//----------------------------------------------
public:

	// コンストラクタ
	CollisionManager();
	// デストラクタ
	~CollisionManager();
	
	// ステージとレイの当たり判定実行
	std::vector<std::pair<Collider*, float>> HitRayStage(
		const DirectX::SimpleMath::Ray& ray,
		const std::vector<Collider*>& stageBlock);
	
	// 全削除
	void Clear();
};