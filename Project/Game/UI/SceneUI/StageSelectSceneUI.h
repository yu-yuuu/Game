/**
 *
 * @file StageSelectSceneUI.h
 *
 * @brief ステージセレクトシーンで使用するUI、画像クラスのヘッダーファイル
 *
 * @author Kato Yuki
 *
 * @date 2024/1/22
 *
 */
#pragma once

#include <string>
#include "Game/UI/SceneUI/SceneUI.h"

class StageSelectScene;
class OperatableUI;

class StageSelectSceneUI : public SceneUI
{
//----------------------------------------------
// 定数
//----------------------------------------------
private:

	// 常に描画するUIのタグ
	const std::string TAG_ALWAYS     = "Always";
	// ステージ切替表示矢印UIのタグ
	const std::string TAG_ARROW_UP   = "StageSelectArrowUp";
	const std::string TAG_ARROW_DOWN = "StageSelectArrowDown";
	// ステージ切替表示矢印の移動速度
	const float STAGE_SELECT_ARROW_MOVE_SPEED = 2.0f;
	// ステージ切替表示矢印の移動幅
	const float STAGE_SELECT_ARROW_MOVE_WIDTH = 0.25f;

//----------------------------------------------
// 変数
//----------------------------------------------
private:

	// プレイシーン
	StageSelectScene* m_stageSelectScene;
	// 選択表示用の矢印
	OperatableUI* m_selectArrowUp;
	OperatableUI* m_selectArrowDown;

//----------------------------------------------
// 関数
//----------------------------------------------
public:

	// コンストラクタ
	StageSelectSceneUI(StageSelectScene* stageSelectScene);
	// デストラクタ
	~StageSelectSceneUI();

	// 初期化
	void Initialize() override;
	// 更新
	void Update() override;

	// 矢印の描画設定
	void SelectTriangleRenderSetting(bool isStart, bool isEnd);
};