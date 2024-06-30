/**
 *
 * @file StageManager.h
 *
 * @brief ステージのデータ、生成を管理するマネージャークラスのヘッダーファイル
 *
 * @author Kato Yuki
 *
 * @date 2023/12/31
 *
 */
#pragma once

#include "Game/Stage/StageData.h"

class StageManager
{
//----------------------------------------------
// 変数
//----------------------------------------------
private:

	// 全ステージデータ
	KT::Stage::AllStage m_allStage;

//----------------------------------------------
// 関数
//----------------------------------------------
public:

	// コンストラクタ
	StageManager(const KT::Stage::AllStage& allStage);
	// デストラクタ
	~StageManager();

	// ステージサイズ取得
	const KT::Stage::Size& GetStageSize(const int& stageNumber);
	// 3Dステージ作成
	KT::Stage::StageData CreateStage3D(const int& stageNumber, const DirectX::SimpleMath::Vector3& basePosition = DirectX::SimpleMath::Vector3::Zero);
	// 2Dステージ作成
	void Switch3DTo2DStageData(
		const DirectX::SimpleMath::Vector3& stageSize,
		KT::Stage::StageData* stageData,
		const DirectX::SimpleMath::Vector3& cameraDirection);
	// ステージ番号リスト取得
	std::vector<int> GetStageNumberList();
	// ステージ番号のステージが存在するか確認
	bool CheckStageNumber(const int& stageNumber);
	// ステージ数取得
	int GetStageNum();
};