/**
 *
 * @file SelectStage.cpp
 *
 * @brief セレクトシーンのステージクラスのソースファイル
 *
 * @author Kato Yuki
 *
 * @date 2024/1/21
 *
 */
#include "pch.h"
#include "SelectStage.h"
#include "Game/MyLibrary/CommonResource/GameResource.h"

 //------------------------------------------------------------------
 /**
  * @brief コンストラクタ)
  *
  * @param stageNumber：選択されているステージ番号
  * @param size：ステージサイズ
  */
SelectStage::SelectStage(int stageNumber, KT::Stage::Size size)
	: Stage(stageNumber, size)
	, m_stageList()
	, m_stageNumberList()
	, m_selectStageNumber(stageNumber)
	, m_nextStage(nullptr)
	, m_nextBasePosition()
{
}

//------------------------------------------------------------------
/**
 * @brief デストラクタ
 */
SelectStage::~SelectStage()
{
}

//------------------------------------------------------------------
/**
 * @brief 初期化
 *
 * @param  なし
 * @return なし
 */
void SelectStage::Initialize()
{
	// ステージマネージャー取得
	StageManager* stageManager = GameResource::GetInstance()->GetStageManager();
	// タイトルシーン用ステージを設定
	SetStageData(stageManager->CreateStage3D(GetStageNumber()));
	// ステージの初期化
	Stage::Initialize();
}

//------------------------------------------------------------------
/**
 * @brief 更新
 *
 * @param  なし
 * @return なし
 */
void SelectStage::Update()
{
	if (m_nextStage) m_nextStage->Update();

	Stage::Update();
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
void SelectStage::Render(DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix projection, std::function<void()> custom)
{
	if (m_nextStage) m_nextStage->Render(view, projection, custom);
	Stage::Render(view, projection, custom);
}

//------------------------------------------------------------------
/**
 * @brief 選択しているステージの番号取得
 *
 * @param なし
 * @return int：選択しているステージ番号
 */
const int& SelectStage::GetSelectStageNumber() const
{
	return m_selectStageNumber;
}

//------------------------------------------------------------------
/**
 * @brief ステージ切替完了時処理
 *
 * @param  なし
 * @return なし
 */
void SelectStage::StageSwitchComplete()
{
	// 切り替え先のステージを現在のステージに設定
	SetStageData(std::move(*m_nextStage->GetStageData()));
	// 切り替え先のステージリセット
	m_nextStage.reset();
	m_nextStage = nullptr;
}

//------------------------------------------------------------------
/**
 * @brief 切り替えるステージの用意
 *
 * @param  selectStageIndex：選択したステージの要素番号
 * @return なし
 */
void SelectStage::ChangeStageSetting(const int& selectStageIndex)
{
	using namespace DirectX;

	// ステージマネージャー取得
	StageManager* stageManager = GameResource::GetInstance()->GetStageManager();
	// ステージ番号リストを受け取る
	std::vector<int> numberList = stageManager->GetStageNumberList();
	// ステージ作成
	m_nextBasePosition = SimpleMath::Vector3(0.0f, -STAGE_HEIGHT_OFFSET * selectStageIndex, 0.0f);
	m_nextStage = std::make_unique<Stage>(numberList[selectStageIndex], stageManager->GetStageSize(numberList[selectStageIndex]));
	m_nextStage->SetStageData(stageManager->CreateStage3D(numberList[selectStageIndex], m_nextBasePosition));
	m_nextStage->Initialize();
}

//------------------------------------------------------------------
/**
 * @brief 切り替え先のステージの基準位置を取得
 *
 * @param なし
 * @return Vector3：基準位置
 */
DirectX::SimpleMath::Vector3 SelectStage::GetNextBasePosition() const
{
	return m_nextBasePosition;
}

//------------------------------------------------------------------
/**
 * @brief ステージサイズの取得
 *
 * @param  なし
 * @return Size：ステージサイズ
 */
KT::Stage::Size SelectStage::GetNextStageSize() const
{
	return m_nextStage->GetStageSize();
}
