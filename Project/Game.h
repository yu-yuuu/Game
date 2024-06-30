//
// Game.h
//

#pragma once

#include "Audio.h"

#include "Game/Scene/SceneManager.h"
#include "Game/Fade/Fade.h"
#include "Game/MyLibrary/InputManager/InputManager.h"
#include "Game/MyLibrary/ResourceManager/ResourceManager.h"
#include "Game/Stage/StageManager.h"
#include "Game/MyLibrary/Collision/CollisionManager.h"
#include "Game/UI/UIManager.h"
#include "Game/Effect/EffectManager.h"
#include "Game/MyLibrary/File/FilePathList.h"

#include "Library/ImaseLib/DebugFont.h"
#include "Library/ImaseLib/DisplayCollision.h"
// A basic game implementation that creates a D3D11 device and
// provides a game loop.
class Game final : public DX::IDeviceNotify
{
public:

    Game() noexcept(false);
    ~Game() = default;

    Game(Game&&) = default;
    Game& operator= (Game&&) = default;

    Game(Game const&) = delete;
    Game& operator= (Game const&) = delete;

    // Initialization and management
    void Initialize(HWND window, int width, int height);

    // Basic game loop
    void Tick();

    // IDeviceNotify
    void OnDeviceLost() override;
    void OnDeviceRestored() override;

    // Messages
    void OnActivated();
    void OnDeactivated();
    void OnSuspending();
    void OnResuming();
    void OnWindowMoved();
    void OnDisplayChange();
    void OnWindowSizeChanged(int width, int height);

    // Properties
    void GetDefaultSize( int& width, int& height ) const noexcept;
public:

    // 画面モードを設定する関数（TRUE：フルスクリーン）
    void SetFullscreenState(BOOL value);

private:

    void Update(DX::StepTimer const& timer);
    void Render();

    void Clear();

    void CreateDeviceDependentResources();
    void CreateWindowSizeDependentResources();

    // Device resources.
    std::unique_ptr<DX::DeviceResources>    m_deviceResources;

    // Rendering loop timer.
    DX::StepTimer                           m_timer;

private:
    
    // 画面モード（TRUE：フルスクリーン）
    BOOL m_fullscreen;

    // コモンステート
    std::unique_ptr<DirectX::CommonStates> m_commonStates;
    // キーボードステートトラッカー
    std::unique_ptr<DirectX::Keyboard::KeyboardStateTracker> m_keyStateTracker;
    // オーディオエンジン
    std::unique_ptr<DirectX::AudioEngine> m_audioEngine;
    // シーンマネージャー
    std::unique_ptr<SceneManager> m_sceneManager;
    // フェード
    std::unique_ptr<Fade> m_fade;
    // 入力マネージャー
    std::unique_ptr<InputManager> m_inputManager;
    // リソースマネージャー
    std::unique_ptr<ResourceManager> m_resourceManager;
    // ステージマネージャー
    std::unique_ptr<StageManager> m_stageManager;
    // 当たり判定マネージャー
    std::unique_ptr<CollisionManager> m_collisionManager;
    // UIマネージャー
    std::unique_ptr<UIManager> m_uiManager;
    // エフェクトマネージャー
    std::unique_ptr<EffectManager> m_effectManager;
    // ファイルパスリスト
    std::unique_ptr<FilePathList> m_filePathList;

 // ImaseLib
private:

    // デバッグ文字
    std::unique_ptr<Imase::DebugFont> m_debugFont;
    // 当たり判定表示
    std::unique_ptr<Imase::DisplayCollision> m_dispCol;
    
};
