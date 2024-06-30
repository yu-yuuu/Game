/**
 *
 * @file ResultSceneUI.cpp
 *
 * @brief リザルトシーンのUIをまとめるクラスのソースファイル
 *
 * @author Kato Yuki
 *
 * @date 2024/3/13
 *
 */
#include "pch.h"
#include "ResultSceneUI.h"

#include "Game/MyLibrary/CommonResource/GameResource.h"
#include "Game/Scene/ResultScene.h"
#include "Game/UI/OperatableUI.h"

using namespace DirectX;

//------------------------------------------------------------------
/**
 * @brief コンストラクタ
 *
 * @param resultScene：リザルトシーンのポインタ
 */
ResultSceneUI::ResultSceneUI(ResultScene* resultScene)
	: m_resultScene(resultScene)
	, m_selectUI()
{
}

//------------------------------------------------------------------
/**
 * @brief デストラクタ
 */
ResultSceneUI::~ResultSceneUI()
{
}

//------------------------------------------------------------------
/**
 * @brief 初期化
 *
 * @param  なし
 * @return なし
 */
void ResultSceneUI::Initialize()
{
	// エイリアス宣言
	using Mode = ResultScene::NextMode;

	// UI作成
	CreateUI(KT::UI::PROPERTIE_RESULT);
	// 選択するUIの設定
	m_selectUI.resize(static_cast<int>(Mode::COUNT));
	m_selectUI[static_cast<int>(Mode::NEXT)]         = GetUI(KT::UI::RESULT_NEXT_SCENE_TEXT);
	m_selectUI[static_cast<int>(Mode::STAGE_SELECT)] = GetUI(KT::UI::RESULT_TOSELECT_SCENE_TEXT);

	// 最後のステージか
	if (m_resultScene->IsEndStageNumber())
	{
		m_selectUI[static_cast<int>(Mode::NEXT)]->ActiveStateUpdate(false);
		m_selectUI[static_cast<int>(Mode::STAGE_SELECT)]->SelectStateUpdate(true);
	}

	// UIマネージャーに登録
	AddUIManagerAll();
}

//------------------------------------------------------------------
/**
 * @brief 選択処理
 *
 * @param  type：何番を選択しているか
 * @return なし
 */
void ResultSceneUI::Select(const int& type)
{
	for (int i = 0; i < m_selectUI.size(); i++)
	{
		// 選択していたらUIの色を変更
		m_selectUI[i]->SelectStateUpdate(i == type);
	}
}