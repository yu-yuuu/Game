/**
 *
 * @file GameResource.cpp
 *
 * @brief ゲームで使用する共有リソースのソースファイル
 *
 * @author Kato Yuki
 *
 * @date 2023/11/11
 *
 */
#include "pch.h"
#include "GameResource.h"

//----------------------------------------------
// インスタンスの初期化
//----------------------------------------------
std::unique_ptr<GameResource> GameResource::m_gameResource = nullptr;

//------------------------------------------------------------------
/**
 * @brief コンストラクタ
 *
 * @param なし
 */
GameResource::GameResource()
	: m_deviceResources(nullptr)
	, m_stepTimer(nullptr)
	, m_commonStates(nullptr)
	, m_keyStateTracker(nullptr)
	, m_fade(nullptr)
	, m_inputManager(nullptr)
	, m_resourceManager(nullptr)
	, m_stageManager(nullptr)
	, m_uiManager(nullptr)
	, m_effectManager(nullptr)
	, m_debugFont(nullptr)
	, m_displayCollision(nullptr)
	, m_menuWindow(nullptr)
	, m_filePathList(nullptr)
{
}

//------------------------------------------------------------------
/**
 * @brief インスタンスの取得
 *
 * @param なし
 * @return GameResourceインスタンス
 */GameResource* const GameResource::GetInstance()
{
	// インスタンスがなければ生成する
	if (!m_gameResource)
	{
		m_gameResource.reset(new GameResource());
	}
	return m_gameResource.get();
}

 //------------------------------------------------------------------
 /**
  * @brief デバイスリソースの取得
  *
  * @param なし
  * @return DX::DeviceResources*：デバイスリソースのポインタ
  */
 DX::DeviceResources* GameResource::GetDeviceResources() const
{
	return m_deviceResources; 
}

 //------------------------------------------------------------------
 /**
  * @brief デバイスリソースの設定
  *
  * @param deviceResources：設定するデバイスリソースのポインタ
  * @return なし
  */
 void GameResource::SetDeviceResources(DX::DeviceResources* deviceResources)
{
	m_deviceResources = deviceResources;
}

 //------------------------------------------------------------------
 /**
  * @brief ステップタイマーの取得
  *
  * @param なし
  * @return DX::StepTimer*：ステップタイマーのポインタ
  */
 DX::StepTimer* GameResource::GetStepTimer() const
{
	return m_stepTimer;
}

 //------------------------------------------------------------------
 /**
  * @brief ステップタイマーの設定
  *
  * @param stepTimer：設定するステップタイマーのポインタ
  * @return なし
  */
 void GameResource::SetStepTimer(DX::StepTimer* stepTimer)
{
	m_stepTimer = stepTimer;
}

 //------------------------------------------------------------------
 /**
  * @brief コモンステートの取得
  *
  * @param なし
  * @return DirectX::CommonStates*：コモンステートのポインタ
  */
 DirectX::CommonStates* GameResource::GetCommonStates()
{
	return m_commonStates;
}

 //------------------------------------------------------------------
 /**
  * @brief コモンステートの設定
  *
  * @param commonStates：設定するコモンステートのポインタ
  * @return なし
  */
 void GameResource::SetCommonStates(DirectX::CommonStates* commonStates)
{
	m_commonStates = commonStates;
}

 //------------------------------------------------------------------
 /**
  * @brief キーボードステートトラッカーの取得
  *
  * @param なし
  * @return DirectX::Keyboard::KeyboardStateTracker*：キーボードステートトラッカーのポインタ
  */
 DirectX::Keyboard::KeyboardStateTracker* GameResource::GetKeyboardStateTracker() const
{
	return m_keyStateTracker;
}

 //------------------------------------------------------------------
 /**
  * @brief キーボードステートトラッカーの設定
  *
  * @param keyStateTracker：設定するキーボードステートトラッカー
  * @return なし
  */
 void GameResource::SetKeyboardStateTracker(DirectX::Keyboard::KeyboardStateTracker* keyStateTracker)
{
	m_keyStateTracker = keyStateTracker;
}

 //------------------------------------------------------------------
 /**
  * @brief フェードの取得
  *
  * @param なし
  * @return フェードのポインタ
  */
 Fade* GameResource::GetFade() const
{
	return m_fade;
}

 //------------------------------------------------------------------
 /**
  * @brief フェードの設定
  *
  * @param fade：設定するフェードのポインタ
  * @return なし
  */
 void GameResource::SetFade(Fade* fade)
{
	m_fade = fade;
}

 //------------------------------------------------------------------
 /**
  * @brief 入力マネージャー
  *
  * @param なし
  * @return 入力マネージャーのポインタ
  */
 InputManager* GameResource::GetInputManager() const
{
	return m_inputManager;
}

 //------------------------------------------------------------------
 /**
  * @brief 入力マネージャーの設定
  *
  * @param inputManager：登録する入力マネージャーのポインタ
  * @return なし
  */
 void GameResource::SetInputManager(InputManager* inputManager)
{
	m_inputManager = inputManager;
}

//------------------------------------------------------------------
/**
 * @brief リソースマネージャーの取得
 *
 * @param なし
 * @return ResourceManager*：リソースマネージャーのポインタ
 */
ResourceManager* GameResource::GetResourceManager() const
{
	return m_resourceManager;
}

//------------------------------------------------------------------
/**
 * @brief リソースマネージャーの設定
 *
 * @param  resourceManager：設定するリソースマネージャーのポインタ
 * @return なし
 */
void GameResource::SetResourceManager(ResourceManager* resourceManager)
{
	m_resourceManager = resourceManager;
}

//------------------------------------------------------------------
/**
 * @brief ステージマネージャーの取得
 *
 * @param  なし
 * @return ステージマネージャーのポインタ
 */
StageManager* GameResource::GetStageManager() const
{
	return m_stageManager;
}

//------------------------------------------------------------------
/**
 * @brief ステージマネージャーの設定
 *
 * @param  stageManager：設定するステージマネージャーのポインタ
 * @return なし
 */
void GameResource::SetStageManager(StageManager* stageManager)
{
	m_stageManager = stageManager;
}

//------------------------------------------------------------------
/**
 * @brief 当たり判定マネージャーの取得
 *
 * @param  なし
 * @return 当たり判定マネージャーのポインタ
 */
CollisionManager* GameResource::GetCollisionManager() const
{
	return m_collisionManager;
}

//------------------------------------------------------------------
/**
 * @brief 当たり判定マネージャーの設定
 *
 * @param  collisionManager：設定する当たり判定マネージャーのポインタ
 * @return なし
 */
void GameResource::SetCollisionManager(CollisionManager* collisionManager)
{
	m_collisionManager = collisionManager;
}

//------------------------------------------------------------------
/**
 * @brief UIマネージャーの取得
 *
 * @param  なし
 * @return UIマネージャーのポインタ
 */
UIManager* GameResource::GetUIManager() const
{
	return m_uiManager;
}

//------------------------------------------------------------------
/**
 * @brief UIマネージャーの設定
 *
 * @param  uiManager：設定するUIマネージャーのポインタ
 * @return なし
 */
void GameResource::SetUIManager(UIManager* uiManager)
{
	m_uiManager = uiManager;
}

//------------------------------------------------------------------
/**
 * @brief エフェクトマネージャーの取得
 *
 * @param  なし
 * @return エフェクトマネージャーのポインタ
 */
EffectManager* GameResource::GetEffectManager() const
{
	return m_effectManager;
}

//------------------------------------------------------------------
/**
 * @brief エフェクトマネージャーの設定
 *
 * @param  effectManager：設定するエフェクトマネージャーのポインタ
 * @return なし
 */
void GameResource::SetEffectManager(EffectManager* effectManager)
{
	m_effectManager = effectManager;
}

//------------------------------------------------------------------
/**
 * @brief メニューウィンドウの取得
 *
 * @param  なし
 * @return メニューウィンドウのポインタ
 */
MenuWindow* GameResource::GetMenuWindow() const
{
	return m_menuWindow;
}

//------------------------------------------------------------------
/**
 * @brief メニューウィンドウの設定
 *
 * @param  menuWindow：設定するメニューウィンドウのポインタ
 * @return なし
 */
void GameResource::SetMenuWindow(MenuWindow* menuWindow)
{
	m_menuWindow = menuWindow;
}
//------------------------------------------------------------------
/**
 * @brief ファイルパスリストの取得
 *
 * @param  なし
 * @return ファイルパスリストのポインタ
 */
FilePathList* GameResource::GetFilePathList() const
{
	return m_filePathList;
}

//------------------------------------------------------------------
/**
 * @brief ファイルパスリストの設定
 *
 * @param  filePathList：設定するファイルパスリストのポインタ
 * @return なし
 */
void GameResource::SetFilePathList(FilePathList* filePathList)
{
	m_filePathList = filePathList;
}

//------------------------------------------------------------------
/**
 * @brief デバッグ文字の取得
 *
 * @param なし
 * @return Imase::DebugFont*：デバッグ文字のポインタ
 */
Imase::DebugFont* GameResource::GetDebugFont() const
{
	return m_debugFont;
}

//------------------------------------------------------------------
/**
 * @brief デバッグ文字の設定
 *
 * @param  debugFont：設定するデバッグ文字のポインタ
 * @return なし
 */
void GameResource::SetDebugFont(Imase::DebugFont* debugFont)
{
	m_debugFont = debugFont;
}

//------------------------------------------------------------------
/**
 * @brief 当たり判定表示クラスの取得
 *
 * @param  なし
 * @return DisplayCollision：当たり判定表示クラスのポインタ
 */
Imase::DisplayCollision* GameResource::GetDisplayCollision()
{
	return m_displayCollision;
}

//------------------------------------------------------------------
/**
 * @brief 当たり判定表示クラスの設定
 *
 * @param  displayCollision：設定する当たり判定表示クラスのポインタ
 * @return なし
 */
void GameResource::SetDisplayCollision(Imase::DisplayCollision* displayCollision)
{
	m_displayCollision = displayCollision;
}
