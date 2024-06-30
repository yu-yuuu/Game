/**
 *
 * @file PlayStage.cpp
 *
 * @brief プレイシーンで使用するステージのソースファイル
 *
 * @author Kato Yuki
 *
 * @date 2023/12/31
 *
 */
#include "pch.h"
#include "PlayStage.h"
#include "Game/Block/BlockType.h"
#include "Game/Block/Block.h"
#include "Game/MyLibrary/Collision/BoxCollider.h"
#include "Game/MyLibrary/CommonResource/GameResource.h"

using namespace DirectX;

//------------------------------------------------------------------
/**
 * @brief コンストラクタ
 *
 * @param  stageNumber ：ステージ番号
 * @param  size        ：ステージサイズ
 */
PlayStage::PlayStage(int stageNumber, KT::Stage::Size size)
	: Stage(stageNumber, size)
	//, m_stage()
	, m_isChange2D(false)
	, m_cameraDirection()
	, m_dimension()
{
}

//------------------------------------------------------------------
/**
 * @brief デストラクタ
 */
PlayStage::~PlayStage()
{
}

//------------------------------------------------------------------
/**
 * @brief 初期化
 *
 * @param  なし
 * @return なし
 */
void PlayStage::Initialize()
{
	// ステージマネージャー取得
	StageManager* manager = GameResource::GetInstance()->GetStageManager();
	// ステージ作成
	SetStageData(manager->CreateStage3D(GetStageNumber()));
	// 基底クラスの初期化
	Stage::Initialize();
}

//------------------------------------------------------------------
/**
 * @brief 更新
 *
 * @param  IsSwitching：次元切替中か
 * @return なし
 */
void PlayStage::Update(bool IsSwitching)
{
	// 3D → 2D 切替
	if (IsChange2DStage(IsSwitching))
	{
		SetStageActive(false);
		StageManager* manager = GameResource::GetInstance()->GetStageManager();
		manager->Switch3DTo2DStageData(GetStageSize().GetVector3(), GetStageData(), m_cameraDirection);
		m_isChange2D = false;
	}
	// 2D → 3D 切替
	else if (IsChange3DStage(IsSwitching))
	{
		SetStageActive(true);
		m_isChange2D = false;
	}
	// ステージブロックの更新
	Stage::Update();
}

//------------------------------------------------------------------
/**
 * @brief 描画
 *
 * @param view      ：ビュー行列
 * @param projection：射影行列
 * @param eye       ：カメラ位置
 * @param custom    ：ステージに適応させるエフェクト
 * @return なし
 */
void PlayStage::Render(DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix projection, DirectX::SimpleMath::Vector3 eye, std::function<void()> custom)
{
	// ステージデータ取得
	KT::Stage::StageData* stage = GetStageData();
	// ブロックをカメラに近い順にソートする
	std::sort(stage->begin(), stage->end(),
		[&](std::unique_ptr<Block>& lhs, std::unique_ptr<Block>& rhs)
		{
			auto l = lhs->GetPosition() - eye;
			auto r = rhs->GetPosition() - eye;

			return l.LengthSquared() < r.LengthSquared();
		}
	);
	// ステージブロックの描画
	for (std::unique_ptr<Block>& block : *stage)
	{
		block->Render(view, projection, custom);
	}
}

//------------------------------------------------------------------
/**
 * @brief 次元切り替え
 *
 * @param  dimension：現在の次元
 * @param  cameraDirection：カメラの視点方向
 * @return なし
 */
void PlayStage::ChangeDimension(
	KT::GameParam::Dimension dimension,
	const DirectX::SimpleMath::Vector3& cameraDirection)
{
	m_isChange2D = true;
	m_dimension = dimension;
	m_cameraDirection = cameraDirection;
}

//------------------------------------------------------------------
/**
 * @brief スタート位置取得
 *
 * @param  なし
 * @return Vector3：スタート位置
 */
const DirectX::SimpleMath::Vector3& PlayStage::GetStartPosition()
{
	KT::Stage::StageData* stage = GetStageData();
	for (std::unique_ptr<Block>& block : *stage)
	{
		// スタートブロック以外は飛ばす
		if (block->GetType() != KT::Block::Type::START) continue;
	
		// 位置を返す
		return block->GetPosition();
	}

	return SimpleMath::Vector3::Zero;
}

//------------------------------------------------------------------
/**
 * @brief ゴール位置の取得
 *
 * @param  なし
 * @return なし
 */
const DirectX::SimpleMath::Vector3& PlayStage::GetGoalPosition()
{
	KT::Stage::StageData* stage = GetStageData();
	for (std::unique_ptr<Block>& block : *stage)
	{
		// スタートブロック以外は飛ばす
		if (block->GetType() != KT::Block::Type::GOAL) continue;
		// 位置を返す
		return block->GetPosition();
	}

	return SimpleMath::Vector3::Zero;
}

//------------------------------------------------------------------
/**
 * @brief ステージの当たり判定を取得
 *
 * @param  なし
 * @return vector<Collider*>：ステージの当たり判定リスト
 */
std::vector<Collider*> PlayStage::GetCollisionStage()
{
	// 現在のステージデータ
	KT::Stage::StageData* stage = GetStageData();
	// 返却用
	std::vector<Collider*> ret;
	// あらかじめメモリ領域を確保しておく
	ret.reserve(stage->size());
	
	for (std::unique_ptr<Block>& block : *stage)
	{
		// 当たり判定を取らないブロックなら飛ばす
		if (block->GetCollisionMode() == KT::Block::CollisionMode::NONE) continue;
		// 返却用に追加
		ret.push_back(block->GetCollider());
	}
	// メモリサイズを要素サイズに合わせる
	ret.shrink_to_fit();
	return ret;
}

//------------------------------------------------------------------
/**
 * @brief 2Dに切り替えてよいか
 *
 * @param IsSwitching：次元切替中か
 * @return true ：切替可
 * @return false：切替不可
 */
bool PlayStage::IsChange2DStage(bool IsSwitching)
{
	return m_isChange2D && !IsSwitching && m_dimension == KT::GameParam::Dimension::_3D;
}
//------------------------------------------------------------------
/**
 * @brief 3Dに切り替えてよいか
 *
 * @param IsSwitching：次元切替中か
 * @return true ：切替可
 * @return false：切替不可
 */
bool PlayStage::IsChange3DStage(bool IsSwitching)
{
	return m_isChange2D && IsSwitching && m_dimension == KT::GameParam::Dimension::_2D;
}