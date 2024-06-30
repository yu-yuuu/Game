/**
 *
 * @file CollisionManager.h
 *
 * @brief 当たり判定処理を一括して行うマネージャークラスのソースファイル
 *
 * @author Kato Yuki
 *
 * @date 2024/1/4
 *
 */
#include "pch.h"
#include "CollisionManager.h"

#include "Game/MyLibrary/CommonResource/GameResource.h"

#include "Game/MyLibrary/Collision/Collider.h"
#include "Game/MyLibrary/Collision/BoxCollider.h"
#include "Game/MyLibrary/Collision/Collision.h"
#include "Game/MyLibrary/Utility/MyUtility.h"

using namespace DirectX;

//------------------------------------------------------------------
/**
 * @brief コンストラクタ
 */
CollisionManager::CollisionManager()
	: m_stageBlock()
	, m_collider()
{
}

//------------------------------------------------------------------
/**
 * @brief デストラクタ
 */
CollisionManager::~CollisionManager()
{
}

//------------------------------------------------------------------
/**
 * @brief ステージとレイの当たり判定実行
 *
 * @param  ray       ：ステージに当てるレイ
 * @param  stageBlock：判定を取るステージ
 * @return なし
 */
std::vector<std::pair<Collider*, float>> CollisionManager::HitRayStage(
	const DirectX::SimpleMath::Ray& ray,
	const std::vector<Collider*>& stageBlock)
{
	// 当たったオブジェクト削除
	std::vector<std::pair<Collider*, float>> rayHitObj;

	for (Collider* collider : stageBlock)
	{
		// 当たり判定取得
		BoxCollider* blockBox = dynamic_cast<BoxCollider*>(collider);
		// DirectXの当たり判定取得
		BoundingBox bb = blockBox->GetBoundingBox();
		// レイの当たった長さ取得用
		float distance = 0.0f;
		// 判定を取る
		if (!ray.Intersects(bb, distance)) continue;

		// 当たったオブジェクトと長さを保存
		rayHitObj.push_back({ blockBox, distance });
	}

	return rayHitObj;
}

//------------------------------------------------------------------
/**
 * @brief リスト初期化
 *
 * @param  なし
 * @return なし
 */
void CollisionManager::Clear()
{
	m_stageBlock.clear();
	m_collider.clear();
}