/**
 *
 * @file MenuWindowUI.h
 *
 * @brief メニューウィンドウのUIをまとめるクラスのヘッダーファイル
 *
 * @author Kato Yuki
 *
 * @date 2024/2/2
 *
 */
#pragma once

#include <vector>
#include <string>
#include "Game/UI/SceneUI/SceneUI.h"
#include "Game/Window/MenuWindow.h"

class OperatableUI;

class MenuWindowUI : public SceneUI
{
//----------------------------------------------
// 定数
//----------------------------------------------
private:

	// 常に描画するUIのタグ
	const std::string TAG_ALWAYS = "Always";
	// ホーム画面UIのタグ
	const std::string TAG_MENU_HOME = "MenuHome";
	// 設定画面UIのタグ
	const std::string TAG_MENU_OPTION = "MenuOption";

//----------------------------------------------
// 変数
//----------------------------------------------
private:

	// メニューウィンドウ
	MenuWindow* m_menuWindow;

	// タイトルへ戻るボタン
	OperatableUI* m_toTitleScene;
	// ステージセレクトへ戻るボタン
	OperatableUI* m_toStageSelectScene;
	// 選択するUI
	std::vector<OperatableUI*> m_selectUIHome;

	// BGM音量つまみUI
	OperatableUI* m_bgmKnob;
	// SE音量つまみUI
	OperatableUI* m_seKnob;
	// 戻るボタン
	OperatableUI* m_toHomeMenu;
	// BGMつまみの移動範囲
	DirectX::SimpleMath::Vector2 m_bgmKnobRange;
	// SEつまみの移動範囲
	DirectX::SimpleMath::Vector2 m_seKnobRange;
	// 選択するUI
	std::vector<OperatableUI*> m_selectUIOption;

//----------------------------------------------
// 関数
//----------------------------------------------
public:

	// コンストラクタ
	MenuWindowUI(MenuWindow* menuWindow);
	// デストラクタ
	~MenuWindowUI();
	// 初期化
	void Initialize() override;

	// メニューを開く
	void OpenMenu();
	// ホーム画面を開く
	void OpenHome();
	// 設定画面を開く
	void OpenOption();
	// メニューを閉じる時の処理
	void CloseMenu();

	// ホーム画面の選択
	void SelectHome(const int& type);
	// 設定画面の選択
	void SelectOption(const int& type);
	// 選択処理
	void Select(const int& selectType, const std::vector<OperatableUI*>& changeColorList);

	// BGMの調整
	void BGMAdjustment(const float& volume);
	// SEの調整
	void SEAdjustment(const float& volume);
	// 調整処理
	void OptionAdjustment(const float& volume, OperatableUI* knob, const DirectX::SimpleMath::Vector2& knobRange);

	// シーンへ戻るボタンの設定
	void ReturnSceneButtonSetting(MenuWindow::OpenScene openScene);

};