/**
 *
 * @file SelectStage.h
 *
 * @brief セレクトシーンのステージクラスのヘッダー－ファイル
 *
 * @author Kato Yuki
 *
 * @date 2024/1/21
 *
 */
#pragma once

#include <vector>
#include <unordered_map>
#include "Game/Stage/Stage.h"
#include "Game/Stage/StageData.h"

class SelectStage : public Stage
{
//----------------------------------------------
// 定数
//----------------------------------------------
private:

	// ステージの生成位置の間隔
	const float STAGE_HEIGHT_OFFSET = 100.0f;

//----------------------------------------------
// 変数
//----------------------------------------------
private:

	// ステージデータリスト
	std::unordered_map<int, KT::Stage::StageData> m_stageList;
	// ステージ番号リスト
	std::vector<int> m_stageNumberList;
	// 選択中のステージ番号
	int m_selectStageNumber;
	// 切り替え先のステージ
	std::unique_ptr<Stage> m_nextStage;
	// 切り替え先のステージの基準位置
	DirectX::SimpleMath::Vector3 m_nextBasePosition;


//----------------------------------------------
// 関数
//----------------------------------------------
public:

	// コンストラクタ
	SelectStage(int stageNumber, KT::Stage::Size size);
	// デストラクタ
	~SelectStage();
	// 初期化
	void Initialize();
	// 更新
	void Update();
	// 描画
	void Render(
		DirectX::SimpleMath::Matrix view,
		DirectX::SimpleMath::Matrix projection,
		std::function<void()> custom = nullptr
	);

	// 選択しているステージの番号取得
	const int& GetSelectStageNumber() const;
	// ステージ切替完了時処理
	void StageSwitchComplete();

	// 切り替えるステージの用意
	void ChangeStageSetting(const int& selectStageIndex);
	// 切り替え先のステージの基準位置取得
	DirectX::SimpleMath::Vector3 GetNextBasePosition() const;
	// 切り替え先のステージのサイズ取得
	KT::Stage::Size GetNextStageSize() const;

};