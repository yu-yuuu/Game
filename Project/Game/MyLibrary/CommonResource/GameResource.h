/**
 *
 * @file GameResource.h
 *
 * @brief ゲームで使用する共有リソースのヘッダーファイル
 *
 * @author Kato Yuki
 *
 * @date 2023/11/11
 *
 */
#pragma once

#include "Game/Fade/Fade.h"
#include "Game/MyLibrary/InputManager/InputManager.h"
#include "Game/MyLibrary/ResourceManager/ResourceManager.h"
#include "Game/Stage/StageManager.h"
#include "Game/MyLibrary/Collision/CollisionManager.h"
#include "Game/UI/UIManager.h"
#include "Game/Effect/EffectManager.h"
#include "Game/Window/MenuWindow.h"
#include "Game/MyLibrary/File/FilePathList.h"

#include "Library/ImaseLib/DebugFont.h"
#include "Library/ImaseLib/DisplayCollision.h"

class GameResource
{
//----------------------------------------------
// 変数
//----------------------------------------------
private:

	// ゲームリソースインスタンス
	static std::unique_ptr<GameResource> m_gameResource;

private:

	// デバイスリソース
	DX::DeviceResources* m_deviceResources;
	// ステップタイマー
	DX::StepTimer* m_stepTimer;
	// コモンステート
	DirectX::CommonStates* m_commonStates;
	// キーボードステートトラッカー
	DirectX::Keyboard::KeyboardStateTracker* m_keyStateTracker;
	// フェード
	Fade* m_fade;
	// 入力マネージャー
	InputManager* m_inputManager;
	// リソースマネージャー
	ResourceManager* m_resourceManager;
	// ステージマネージャー
	StageManager* m_stageManager;
	// 当たり判定マネージャー
	CollisionManager* m_collisionManager;
	// UIマネージャー
	UIManager* m_uiManager;
	// エフェクトマネージャー
	EffectManager* m_effectManager;
	// メニューウィンドウ
	MenuWindow* m_menuWindow;
	// ファイルパスリスト
	FilePathList* m_filePathList;
	// デバッグフォント
	Imase::DebugFont* m_debugFont;
	// 当たり判定表示
	Imase::DisplayCollision* m_displayCollision;


//----------------------------------------------
// 関数
//----------------------------------------------
private:

	// コンストラクタ
	GameResource();
	// コピーコンストラクタ禁止
	GameResource(const GameResource& gameResource) = delete;
	// 代入禁止
	void operator=(const GameResource& gameResource) = delete;

public:

	// デストラクタ
	~GameResource() = default;

	// インスタンスの取得
	static GameResource* const GetInstance();

	//デバイスリソースの取得
	DX::DeviceResources* GetDeviceResources()const;
	// デバイスリソースの設定
	void SetDeviceResources(DX::DeviceResources* deviceResources);
	// ステップタイマーの取得
	DX::StepTimer* GetStepTimer()const;
	// ステップタイマーの設定
	void SetStepTimer(DX::StepTimer* stepTimer);
	// コモンステートの取得
	DirectX::CommonStates* GetCommonStates();
	// コモンステートの設定
	void SetCommonStates(DirectX::CommonStates* commonStates);
	// キーボードステートトラッカーの取得
	DirectX::Keyboard::KeyboardStateTracker* GetKeyboardStateTracker()const;
	// キーボードステートトラッカーの設定
	void SetKeyboardStateTracker(DirectX::Keyboard::KeyboardStateTracker* keyStateTracker);
	// フェードの取得
	Fade* GetFade() const;
	// フェードの設定
	void SetFade(Fade* fade);
	// 入力マネージャー
	InputManager* GetInputManager()const;
	//  入力マネージャーの設定
	void SetInputManager(InputManager* inputManager);
	// リソースマネージャーの取得
	ResourceManager* GetResourceManager() const;
	// リソースマネージャーの取得
	void SetResourceManager(ResourceManager* resourceManager);
	// ステージマネージャーの取得
	StageManager* GetStageManager() const;
	// ステージマネージャーの取得
	void SetStageManager(StageManager* stageManager);
	// 当たり判定マネージャーの取得
	CollisionManager* GetCollisionManager() const;
	// 当たり判定マネージャーの設定
	void SetCollisionManager(CollisionManager* collisionManager);
	// UIマネージャーの取得
	UIManager* GetUIManager() const;
	// UIマネージャーの設定
	void SetUIManager(UIManager* uiManager);
	// エフェクトマネージャーの取得
	EffectManager* GetEffectManager() const;
	// エフェクトマネージャーの設定
	void SetEffectManager(EffectManager* effectManager);
	// メニューウィンドウの取得
	MenuWindow* GetMenuWindow() const;
	// メニューウィンドウの設定
	void SetMenuWindow(MenuWindow* menuWindow);
	// ファイルパスリストの取得
	FilePathList* GetFilePathList() const;
	// ファイルパスリストの設定
	void SetFilePathList(FilePathList* filePathList);
	// デバッグ文字の取得
	Imase::DebugFont* GetDebugFont() const;
	// デバッグ文字の設定
	void SetDebugFont(Imase::DebugFont* debugFont);
	// 当たり判定表示の取得
	Imase::DisplayCollision* GetDisplayCollision();
	void SetDisplayCollision(Imase::DisplayCollision* displayCollision);

};