/**
 *
 * @file StageSelectSceneUI.cpp
 *
 * @brief ステージセレクトシーンで使用するUI、画像クラスのソースファイル
 *
 * @author Kato Yuki
 *
 * @date 2024/1/22
 *
 */
#include "pch.h"
#include "StageSelectSceneUI.h"

#include "Game/MyLibrary/CommonResource/GameResource.h"
#include "Game/Scene/StageSelectScene.h"
#include "Game/UI/OperatableUI.h"

using namespace DirectX;

//------------------------------------------------------------------
/**
 * @brief コンストラクタ
 *
 * @param stageSelectScene：セレクトシーンのポインタ
 */
StageSelectSceneUI::StageSelectSceneUI(StageSelectScene* stageSelectScene)
	: m_stageSelectScene(stageSelectScene)
	, m_selectArrowUp(nullptr)
	, m_selectArrowDown(nullptr)
{
}

//------------------------------------------------------------------
/**
 * @brief デストラクタ
 */
StageSelectSceneUI::~StageSelectSceneUI()
{
}

//------------------------------------------------------------------
/**
 * @brief 初期化
 *
 * @param  なし
 * @return なし
 */
void StageSelectSceneUI::Initialize()
{
	// UI作成
	CreateUI(KT::UI::PROPERTIE_STAGESELECT);
	// 操作UI取得
	m_selectArrowUp   = GetUI(KT::UI::STAGE_SELECT_ARROW_UP);
	m_selectArrowDown = GetUI(KT::UI::STAGE_SELECT_ARROW_DOWN);

	// 基底クラスの全てのUIをUIマネージャーに登録
	AddUIManagerAll();
	// UIマネージャーに自身を設定する
	SetUIManagerSceneUI();
}

//------------------------------------------------------------------
/**
 * @brief 更新
 *
 * @param  なし
 * @return なし
 */
void StageSelectSceneUI::Update()
{
	// ステップタイマー取得
	DX::StepTimer* stepTimer = GameResource::GetInstance()->GetStepTimer();
	float totalTime = static_cast<float>(stepTimer->GetTotalSeconds());

	// 矢印の位置取得
	SimpleMath::Vector2 upPos   = m_selectArrowUp->GetPosition();
	SimpleMath::Vector2 downPos = m_selectArrowDown->GetPosition();
	// 矢印の移動量
	float move = std::sinf(totalTime * STAGE_SELECT_ARROW_MOVE_SPEED) * STAGE_SELECT_ARROW_MOVE_WIDTH;
	// 矢印を動かす
	upPos.y += move;
	downPos.y -= move;
	// 矢印の位置設定
	m_selectArrowUp->SetPosition(upPos);
	m_selectArrowDown->SetPosition(downPos);
}

//------------------------------------------------------------------
/**
 * @brief 矢印の描画設定
 *
 * @param  isStart：先頭のステージを選択しているか
 * @param  isEnd  ：最後のステージを選択しているか
 * @return なし
 */
void StageSelectSceneUI::SelectTriangleRenderSetting(bool isStart, bool isEnd)
{
	// 1ステージ目を選択している
	if (isStart)
	{
		DeleteUIManager(TAG_ARROW_UP);
	}
	// 最後のステージを選択している
	else if (isEnd)
	{
		DeleteUIManager(TAG_ARROW_DOWN);
	}
	// 上記以外
	else
	{
		AddUIManager(TAG_ARROW_UP);
		AddUIManager(TAG_ARROW_DOWN);
	}
}