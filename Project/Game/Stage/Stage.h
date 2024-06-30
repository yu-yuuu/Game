/**
 *
 * @file Stage.h
 *
 * @brief ステージ一つを表すクラスのヘッダーファイル
 *
 * @author Kato Yuki
 *
 * @date 2023/12/28
 *
 */
#pragma once

#include <vector>
#include <unordered_map>
#include <functional>
#include "Game/Stage/StageData.h"

class IBlock;

class Stage
{
//----------------------------------------------
// 変数
//----------------------------------------------
private:

	// ステージ番号
	int m_stageNumber;
	// ステージサイズ
	KT::Stage::Size m_size;
	// ステージデータ
	KT::Stage::StageData m_stage;

//----------------------------------------------
// 関数
//----------------------------------------------
public:

	// コンストラクタ
	Stage(int stageNumber, KT::Stage::Size size);
	// デストラクタ
	~Stage();

	// 初期化
	void Initialize(std::function<void(DirectX::IEffect* effect)> effect = nullptr);
	// 更新
	void Update();
	// 描画
	void Render(
		DirectX::SimpleMath::Matrix view,
		DirectX::SimpleMath::Matrix projection,
		std::function<void()> custom = nullptr
	);
	// 後処理
	void Finalize();
	
	// ステージデータ取得
	KT::Stage::StageData* GetStageData();
	// ステージデータ設定
	void SetStageData(KT::Stage::StageData stage);
	// ステージ番号取得
	const int GetStageNumber() const;
	// ステージサイズ取得、設定
	KT::Stage::Size GetStageSize() const;
	void SetStageSize(const KT::Stage::Size& size);
	// ステージを削除する
	void ClearStage();
	// ステージのアクティブ状態を設定する
	void SetStageActive(bool isActive);
};
