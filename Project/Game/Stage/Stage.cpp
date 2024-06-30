/**
 *
 * @file Stage.cpp
 *
 * @brief ステージ一つを表すクラスのソースファイル
 *
 * @author Kato Yuki
 *
 * @date 2023/12/28
 *
 */#include "pch.h"
#include "Stage.h"

#include "Game/MyLibrary/CommonResource/GameResource.h"
#include "Game/Block/IBlock.h"

using namespace DirectX;

//------------------------------------------------------------------
/**
 * @brief コンストラクタ
 *
 * @param  stageNumber：ステージの番号
 * @param  size       ：ステージサイズ
 */
Stage::Stage(int stageNumber, KT::Stage::Size size)
	: m_stageNumber(stageNumber)
	, m_size(size)
	, m_stage()
{
}

//------------------------------------------------------------------
/**
 * @brief デストラクタ
 */
Stage::~Stage()
{
}

//------------------------------------------------------------------
/**
 * @brief 初期化
 *
 * @param  effect：モデルに適応させるエフェクト
 * @return なし
 */
void Stage::Initialize(std::function<void(DirectX::IEffect* effect)> effect)
{
	// ステージデータが設定されていなかったら強制終了
	assert(!m_stage.empty() && "ステージデータが設定されていません");

	// ステージブロックの初期化
	for (std::unique_ptr<Block>& block : m_stage)
	{
		block->Initialize(effect);
	}
}

//------------------------------------------------------------------
/**
 * @brief 更新
 *
 * @param  なし
 * @return なし
 */
void Stage::Update()
{
	// ステージブロックの更新
	for (std::unique_ptr<Block>& block : m_stage)
	{
		block->Update();
	}
}

//------------------------------------------------------------------
/**
 * @brief 描画
 *
 * @param  view      ：ビュー行列
 * @param  projection：射影行列
 * @param  custom    ：ブロックに適応させるラムダ式
 * @return なし
 */
void Stage::Render(
	DirectX::SimpleMath::Matrix view,
	DirectX::SimpleMath::Matrix projection,
	std::function<void()> custom
)
{
	// ステージブロックの描画
	for (std::unique_ptr<Block>& block : m_stage)
	{
		block->Render(view, projection, custom);
	}
}

//------------------------------------------------------------------
/**
 * @brief 後処理
 *
 * @param  なし
 * @return なし
 */
void Stage::Finalize()
{
	// ステージブロックの初期化
	for (std::unique_ptr<Block>& block : m_stage)
	{
		block->Finalize();
	}
}

//------------------------------------------------------------------
/**
 * @brief ステージデータ取得
 *
 * @param なし
 * @return StageData：ステージデータ
 */
KT::Stage::StageData* Stage::GetStageData()
{
	return &m_stage;
}

//------------------------------------------------------------------
/**
 * @brief ステージデータ設定
 *
 * @param  stage：設定するステージデータ
 * @return なし
 */
void Stage::SetStageData(KT::Stage::StageData stage)
{
	m_stage = std::move(stage);
}

//------------------------------------------------------------------
/**
 * @brief ステージ番号の取得
 *
 * @param  なし
 * @return int：ステージ番号
 */
const int Stage::GetStageNumber() const
{
	return m_stageNumber;
}

//------------------------------------------------------------------
/**
 * @brief ステージサイズの取得
 *
 * @param  なし
 * @return Size：ステージサイズ
 */
KT::Stage::Size Stage::GetStageSize() const
{
	return m_size;
}

//------------------------------------------------------------------
/**
 * @brief ステージサイズの設定
 *
 * @param  size：設定するサイズ
 * @return なし
 */
void Stage::SetStageSize(const KT::Stage::Size& size)
{
	m_size = size;
}

//------------------------------------------------------------------
/**
 * @brief ステージを削除する
 *
 * @param  なし
 * @return なし
 */
void Stage::ClearStage()
{
	m_stage.clear();
}

//------------------------------------------------------------------
/**
 * @brief ステージのアクティブ状態を設定する
 *
 * @param  isActive：アクティブ状態
 * @return なし
 */
void Stage::SetStageActive(bool isActive)
{
	for (std::unique_ptr<Block>& block : m_stage)
	{
		block->SetActive(isActive);
	}
}
