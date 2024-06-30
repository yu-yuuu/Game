/**
 *
 * @file StageManager.cpp
 *
 * @brief ステージのデータ、生成を管理するマネージャークラスのソースファイル
 *
 * @author Kato Yuki
 *
 * @date 2023/12/31
 *
 */
#include "pch.h"
#include "StageManager.h"
#include "Game/Stage/StageFactory.h"

 //------------------------------------------------------------------
 /**
  * @brief コンストラクタ
  *
  * @param allStage：全ステージの生成前データ
  */
StageManager::StageManager(const KT::Stage::AllStage& allStage)
	: m_allStage(allStage)
{
}

//------------------------------------------------------------------
/**
 * @brief デストラクタ
 */
StageManager::~StageManager()
{
}

//----------------------------------------F--------------------------
/**
 * @brief ステージサイズ取得
 *
 * @param stageNumber：サイズを取得したいステージ番号
 * @return Size：ステージサイズ
 */
const KT::Stage::Size& StageManager::GetStageSize(const int& stageNumber)
{
	// ステージ存在確認
	assert(CheckStageNumber(stageNumber) && "ステージ番号のステージが存在しません");

	return m_allStage.at(stageNumber).first;
}

//------------------------------------------------------------------
/**
 * @brief 3Dステージデータ作成
 *
 * @param stageNumber：作成するステージの番号
 * @param basePosition ：作成するステージの基準位置
 * @return StageData：作成したステージデータ
 */
KT::Stage::StageData StageManager::CreateStage3D(const int& stageNumber, const DirectX::SimpleMath::Vector3& basePosition)
{
	// ステージ存在確認
	assert(CheckStageNumber(stageNumber) && "ステージ番号のステージが存在しません");

	return std::move(StageFactory::Create3DStageData(m_allStage.at(stageNumber), basePosition));
}

//------------------------------------------------------------------
/**
 * @brief 2Dステージへ切り替える
 *
 * @param stageSize：ステージサイズ
 * @param stageData：3Dステージデータ
 * @param cameraDirection：カメラの向き
 * @return なし
 */
void StageManager::Switch3DTo2DStageData(
	const DirectX::SimpleMath::Vector3& stageSize,
	KT::Stage::StageData* stageData,
	const DirectX::SimpleMath::Vector3& cameraDirection)
{
	StageFactory::Switch3DTo2DStageData(stageSize, stageData, cameraDirection);
}

//------------------------------------------------------------------
/**
 * @brief ステージ番号リスト取得
 *
 * @param なし
 * @return なし
 */
std::vector<int> StageManager::GetStageNumberList()
{
	std::vector<int> stageNumberList;

	for (const std::pair<int, KT::Stage::SingleStage> stage : m_allStage)
	{
		// 1000番以降は遊べないステージなので追加しない
		if (stage.first >= 1000) continue;

		// ステージ番号を格納
		stageNumberList.push_back(stage.first);
	}

	return stageNumberList;
}

//------------------------------------------------------------------
/**
 * @brief ステージ番号のステージが存在するか確認
 *
 * @param stageNumber：確認したいステージ番号
 * @return true ：存在する
 * @return false：存在しない
 */
bool StageManager::CheckStageNumber(const int& stageNumber)
{
	auto count = std::count_if(m_allStage.begin(), m_allStage.end(),
		[&](std::pair<int, KT::Stage::SingleStage> stage)
		{ return stage.first == stageNumber; } );

	return count == 1;
}

//------------------------------------------------------------------
/**
 * @brief ステージ数取得
 *
 * @param  なし
 * @return int：ステージ数
 */
int StageManager::GetStageNum()
{
	std::vector<int> stage = GetStageNumberList();

	return static_cast<int>(stage.size());
}
