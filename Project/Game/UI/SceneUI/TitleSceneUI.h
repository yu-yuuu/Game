/**
 *
 * @file TitleSceneUI.h
 *
 * @brief タイトルシーンシーンで使用するUI、画像クラスのヘッダーファイル
 *
 * @author Kato Yuki
 *
 * @date 2024/1/22
 *
 */
#pragma once

#include <vector>
#include <string>
#include "Game/UI/SceneUI/SceneUI.h"

class TitleScene;
class OperatableUI;

class TitleSceneUI : public SceneUI
{
//----------------------------------------------
// 定数
//----------------------------------------------
private:

	// 常に描画するUIのタグ
	const std::string TAG_ALWAYS = "Always";
	// エンターキー入力待機中UIのタグ
	const std::string TAG_PUSH_ENTER = "PushEnter";
	// モード選択UIのタグ
	const std::string TAG_MODE_SELECT = "ModeSelect";
	// 点滅の調整値
	const float FLASH_ADJUSTMENT = 0.5f;

//----------------------------------------------
// 変数
//----------------------------------------------
private:

	// プレイシーン
	TitleScene* m_titleScene;
	// エンターを押してくださいテキスト
	OperatableUI* m_pushEnterText;

//----------------------------------------------
// 関数
//----------------------------------------------
public:

	// コンストラクタ
	TitleSceneUI(TitleScene* titleScene);
	// デストラクタ
	~TitleSceneUI();

	// 初期化
	void Initialize() override;
	// 更新
	void Update() override;

	// 次元切替状態に切り替え
	void ChangeStateSwitching();
	// モード選択状態に切り替え
	void ChangeStateModeSelect();
};