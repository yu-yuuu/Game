/**
 *
 * @file StageFactory.h
 *
 * @brief ステージの生成を行うクラスのヘッダーファイル
 *
 * @author Kato Yuki
 *
 * @date 2023/12/17
 *
 */
#pragma once

#include <unordered_map>
#include <string>
#include <vector>
#include <array>
#include <fstream>

#include "Game/Stage/StageData.h"


class IBlock;


class StageFactory
{
//----------------------------------------------
// 定数
//----------------------------------------------

	// レイの位置調整用
	static const float RAY_POSITION_ADJUSTMENT;

//----------------------------------------------
// 関数
//----------------------------------------------
public:

	// ステージデータの読み込み
	static KT::Stage::AllStage CreateStageList(std::ifstream ifs);
	// ステージデータ作成
	static KT::Stage::BlockID CreateStageData(std::ifstream& ifs, const KT::Stage::Size& size);
	// 3Dステージの作成
	static KT::Stage::StageData Create3DStageData(const KT::Stage::SingleStage& stage, const DirectX::SimpleMath::Vector3& basePosition);
	// 2Dステージへ切り替える
	static void Switch3DTo2DStageData(
		const DirectX::SimpleMath::Vector3& stageSize,
		KT::Stage::StageData* stageData,
		const DirectX::SimpleMath::Vector3& cameraDirection);
	// レイに当たった一番近いブロックを取得する
	static Block* CheckRay(
		KT::Stage::StageData* stageData,
		const DirectX::SimpleMath::Ray& ray
	);
};

