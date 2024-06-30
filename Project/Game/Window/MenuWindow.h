/**
 *
 * @file MenuWindow.h
 *
 * @brief 画面上に表示するウィンドウの基底クラスのヘッダーファイル
 *
 * @author Kato Yuki
 *
 * @date 2024/2/5
 *
 */
#pragma once
#undef ChangeMenu

#include "Game/Window/Window.h"

class Texture;
class MenuWindowUI;
class SceneManager;

class MenuWindow : public Window
{
//----------------------------------------------
// 列挙体
//----------------------------------------------
public:

	// ウィンドウを開いたシーン
	enum class OpenScene
	{
		SELECT, // セレクトシーン
		PLAY,   // プレイシーン
		NONE    // 設定なし
	};
	// 現在開いているメニュー
	enum class MenuType
	{
		HOME,   // ホーム
		OPTION, // 設定
	};
	// ホームで選択しているメニュー
	enum class SelectHomeMenu
	{
		OPTION,       // 設定
		RETURN_SCENE, // ○○シーンへ戻る
		COUNT,        // モードの数（未選択、未設定）
	};	
	// ホームで選択しているメニュー
	enum class SelectOptionMenu
	{
		BGM,    // BGM
		SE,     // SE
		RETURN, // 戻る
		COUNT   // モードの数（未選択、未設定）
	};

//----------------------------------------------
// 定数
//----------------------------------------------
private:

	// 音量調整つまみの速度
	const float KNOB_SPEED = 0.025f;
	// 音量の最大値
	const float MAX_VOLUME = 1.0f;

//----------------------------------------------
// 変数
//----------------------------------------------
private:

	// シーンマネージャー
	SceneManager* m_sceneManager;

	// UI
	std::unique_ptr<MenuWindowUI> m_ui;
	// メニューウィンドを開いたシーン
	OpenScene m_openScene;
	// 現在開いているメニュー画面
	MenuType m_currentMenu;
	// ホーム画面で選択しているメニュー
	SelectHomeMenu m_selectHomeMenu;
	// 設定画面で選択しているメニュー
	SelectOptionMenu m_selectOptionMenu;

//----------------------------------------------
// 関数
//----------------------------------------------
public:

	// コンストラクタ
	MenuWindow(SceneManager* sceneManager, DirectX::SimpleMath::Vector2 windowSize, KT::Texture::TextureData texture, DirectX::SimpleMath::Vector2 position);
	// デストラクタ
	~MenuWindow();

	// 初期化
	void Initialize();
	// 更新
	void Update();

	// ホーム画面の更新処理
	void UpdateHome();
	// 設定画面の更新
	void UpdateOption();

	// ウィンドウの表示切替
	void OpenClose(OpenScene openScene);
	// ウィンドウを開く
	void Open(OpenScene openScene);
	// ウィンドウを閉じる
	void Close();

	// ホーム画面で決定時の処理
	void OnEnterHome();
	// 設定画面で決定時の処理
	void OnEnterOption();
	// 音の設定
	void SoundSetting();
	// 音量調整
	void AdjustmentVolume(float& speed, const std::string& type);
	// メニュー画面切り替え
	void ChangeMenu(MenuType nextMenu);
};