//
// Game.cpp
//

#include "pch.h"
#include "Game.h"
#include "Game/MyLibrary/CommonResource/GameResource.h"
#include "Game/Stage/StageFactory.h"
#include "Game/MyLibrary/File/FileManager.h"
#include "Game/MyLibrary/Utility/MyUtility.h"
#include "Game/MyLibrary/ResourceManager/ResourceType.h"


extern void ExitGame() noexcept;

using namespace DirectX;

using Microsoft::WRL::ComPtr;

Game::Game() noexcept(false)
{
    m_deviceResources = std::make_unique<DX::DeviceResources>();
    // TODO: Provide parameters for swapchain format, depth/stencil format, and backbuffer count.
    //   Add DX::DeviceResources::c_AllowTearing to opt-in to variable rate displays.
    //   Add DX::DeviceResources::c_EnableHDR for HDR10 display.
    m_deviceResources->RegisterDeviceNotify(this);

    // オーディオエンジンの作成
    AUDIO_ENGINE_FLAGS eflags = AudioEngine_Default;
#ifdef _DEBUG
    eflags |= AudioEngine_Debug;
#endif
    m_audioEngine = std::make_unique<AudioEngine>(eflags);


    // ファイルパスリスト作成
    m_filePathList = std::make_unique<FilePathList>();
    // ファイルパスリスト読み込み
    m_filePathList->CreatePathList(FileManager::LoadCSV(L"Resources/Data/FilePathList.csv"));


}

// Initialize the Direct3D resources required to run.
void Game::Initialize(HWND window, int width, int height)
{
    m_deviceResources->SetWindow(window, width, height);

    m_deviceResources->CreateDeviceResources();
    CreateDeviceDependentResources();

    m_deviceResources->CreateWindowSizeDependentResources();
    CreateWindowSizeDependentResources();

    // TODO: Change the timer settings if you want something other than the default variable timestep mode.
    // e.g. for 60 FPS fixed timestep update logic, call:
    
    // 60FPS固定
    m_timer.SetFixedTimeStep(true);
    m_timer.SetTargetElapsedSeconds(1.0 / 60);
    
    
    // フェードの初期化
    m_fade->Initialize();
    
    // リソースの読み込み、作成
    m_resourceManager->CreateModelList(FileManager::LoadCSV(m_filePathList->GetPath(KT::File::MODEL)));
    m_resourceManager->CreateTextureList(FileManager::LoadCSV(m_filePathList->GetPath(KT::File::TEXTURE)));
    m_resourceManager->CreateSoundList(m_audioEngine.get(), FileManager::LoadCSV(m_filePathList->GetPath(KT::File::SOUND)));
    // シーンの生成、初期化
    m_sceneManager = std::make_unique<SceneManager>();
    m_sceneManager->Initialize();

    // UIマネージャーの初期化
    m_uiManager->Initialize();

    // エフェクトマネージャー初期化
    m_effectManager->Initialize();
}

#pragma region Frame Update
// Executes the basic game loop.
void Game::Tick()
{
    m_timer.Tick([&]()
    {
        Update(m_timer);
    });

    Render();
}

// Updates the world.
void Game::Update(DX::StepTimer const& timer)
{
    float elapsedTime = float(timer.GetElapsedSeconds());

    // TODO: Add your game logic here.
   
    // オーディオエンジンの更新
    if (!m_audioEngine->Update())
    {
        // No audio device is active
        if (m_audioEngine->IsCriticalError())
        {
            OutputDebugString(L"AudioEngine Error!\n");
        }
    }

    // キーの更新
    Keyboard::State key = Keyboard::Get().GetState();
    m_keyStateTracker->Update(key);

    // フェード中は入力を受け付けない
    if(!m_fade->IsFade())
    {
        // 入力マネージャーの更新
        m_inputManager->Update();
    }
    
    // シーンの更新
    m_sceneManager->Update();
    
    // UIの更新
    m_uiManager->Update();

    // フェードの更新
    m_fade->Update(elapsedTime);

    // キー入力状態リセット
    m_inputManager->Reset();
}
#pragma endregion

#pragma region Frame Render
// Draws the scene.
void Game::Render()
{
    // Don't try to render anything before the first Update.
    if (m_timer.GetFrameCount() == 0)
    {
        return;
    }

    Clear();

    m_deviceResources->PIXBeginEvent(L"Render");
\
    // TODO: Add your rendering code here.

    // シーンの描画
    m_sceneManager->Render();

    // UIの描画
    m_uiManager->Render();

    // フェードの描画
    m_fade->Render();


    // デバッグ文字の表示
    //m_debugFont->Render(m_commonStates.get());
    m_debugFont->DebugClear();


    m_deviceResources->PIXEndEvent();

    // Show the new frame.
    m_deviceResources->Present();
}

// Helper method to clear the back buffers.
void Game::Clear()
{
    m_deviceResources->PIXBeginEvent(L"Clear");

    // Clear the views.
    auto context = m_deviceResources->GetD3DDeviceContext();
    auto renderTarget = m_deviceResources->GetRenderTargetView();
    auto depthStencil = m_deviceResources->GetDepthStencilView();

    context->ClearRenderTargetView(renderTarget, Colors::CornflowerBlue);
    context->ClearDepthStencilView(depthStencil, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
    context->OMSetRenderTargets(1, &renderTarget, depthStencil);

    // Set the viewport.
    auto const viewport = m_deviceResources->GetScreenViewport();
    context->RSSetViewports(1, &viewport);

    m_deviceResources->PIXEndEvent();
}
#pragma endregion

#pragma region Message Handlers
// Message handlers
void Game::OnActivated()
{
    // TODO: Game is becoming active window.
}

void Game::OnDeactivated()
{
    // TODO: Game is becoming background window.
}

void Game::OnSuspending()
{
    // TODO: Game is being power-suspended (or minimized).
}

void Game::OnResuming()
{
    m_timer.ResetElapsedTime();

    // TODO: Game is being power-resumed (or returning from minimize).
}

void Game::OnWindowMoved()
{
    auto const r = m_deviceResources->GetOutputSize();
    m_deviceResources->WindowSizeChanged(r.right, r.bottom);
    
    // フルスクリーンか調べる
    BOOL fullscreen = FALSE;
    m_deviceResources->GetSwapChain()->GetFullscreenState(&fullscreen, nullptr);
    // フルスクリーンが解除されてしまった時の処理
    if (m_fullscreen != fullscreen)
    {
        m_fullscreen = fullscreen;
        // ResizeBuffers関数を呼び出す
        m_deviceResources->CreateWindowSizeDependentResources();
    }
}

void Game::OnDisplayChange()
{
    m_deviceResources->UpdateColorSpace();
}

void Game::OnWindowSizeChanged(int width, int height)
{
    if (!m_deviceResources->WindowSizeChanged(width, height))
        return;

    CreateWindowSizeDependentResources();

    // TODO: Game window is being resized.
}

// Properties
void Game::GetDefaultSize(int& width, int& height) const noexcept
{
    // TODO: Change to desired default window size (note minimum size is 320x200).
    width = 1280;
    height = 720;
}
void Game::SetFullscreenState(BOOL value)
{
    m_fullscreen = value;
    m_deviceResources->GetSwapChain()->SetFullscreenState(m_fullscreen, nullptr);
    if (value) m_deviceResources->CreateWindowSizeDependentResources();
}
#pragma endregion

#pragma region Direct3D Resources
// These are the resources that depend on the device.
void Game::CreateDeviceDependentResources()
{
    auto device  = m_deviceResources->GetD3DDevice();
    auto context = m_deviceResources->GetD3DDeviceContext();

    // TODO: Initialize device dependent objects here (independent of window size).

    // リソースの作成、初期化 //

    // コモンステート
    m_commonStates = std::make_unique<CommonStates>(device);
    // キーボードステート
    m_keyStateTracker = std::make_unique<Keyboard::KeyboardStateTracker>();
    // フェード
    m_fade = std::make_unique<Fade>();
    // 入力マネージャー
    m_inputManager = std::make_unique<InputManager>(m_keyStateTracker.get());
    // リソースマネージャー
    m_resourceManager = std::make_unique<ResourceManager>();
    // ステージマネージャー
    m_stageManager = std::make_unique<StageManager>(StageFactory::CreateStageList(FileManager::OpenLoadFile(m_filePathList->GetPath(KT::File::STAGE))));
    // 当たり判定マネージャー
    m_collisionManager = std::make_unique<CollisionManager>();
    // UIマネージャー
    m_uiManager = std::make_unique<UIManager>();
    // エフェクトマネージャー
    m_effectManager = std::make_unique<EffectManager>();
    // デバッグ文字
    m_debugFont = std::make_unique<Imase::DebugFont>(device, context, KT::MyUtility::StringToWide(m_filePathList->GetPath(KT::File::DEBUG_FONT)).c_str());
    // 当たり判定表示
    m_dispCol = std::make_unique<Imase::DisplayCollision>(device, context, true, false);
    // ゲームリソースのインスタンスを取得
    GameResource* gameResource = GameResource::GetInstance();

    // ゲームリソースで使用するものを設定していく
    gameResource->SetDeviceResources(m_deviceResources.get());      // デバイスリソース
    gameResource->SetStepTimer(&m_timer);                           // ステップタイマ-
    gameResource->SetCommonStates(m_commonStates.get());            // コモンステート
    gameResource->SetKeyboardStateTracker(m_keyStateTracker.get()); // キーボードステートトラッカー
    gameResource->SetFade(m_fade.get());                            // フェード
    gameResource->SetInputManager(m_inputManager.get());            // 入力マネージャー
    gameResource->SetResourceManager(m_resourceManager.get());      // リソースマネージャー
    gameResource->SetStageManager(m_stageManager.get());            // ステージマネージャー
    gameResource->SetCollisionManager(m_collisionManager.get());    // 当たり判定マネージャー
    gameResource->SetUIManager(m_uiManager.get());                  // UIマネージャー
    gameResource->SetEffectManager(m_effectManager.get());          // エフェクトマネージャー
    gameResource->SetFilePathList(m_filePathList.get());            // ファイルパスリスト
    gameResource->SetDebugFont(m_debugFont.get());                  // デバッグ文字
    gameResource->SetDisplayCollision(m_dispCol.get());             // 当たり判定表示
}

// Allocate all memory resources that change on a window SizeChanged event.
void Game::CreateWindowSizeDependentResources()
{
    // TODO: Initialize windows-size dependent objects here.
}

void Game::OnDeviceLost()
{
    // TODO: Add Direct3D resource cleanup here.

    // 後処理
    m_sceneManager->Finalize();

}

void Game::OnDeviceRestored()
{
    CreateDeviceDependentResources();

    CreateWindowSizeDependentResources();
}
#pragma endregion
