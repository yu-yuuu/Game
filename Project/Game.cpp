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

    // �I�[�f�B�I�G���W���̍쐬
    AUDIO_ENGINE_FLAGS eflags = AudioEngine_Default;
#ifdef _DEBUG
    eflags |= AudioEngine_Debug;
#endif
    m_audioEngine = std::make_unique<AudioEngine>(eflags);


    // �t�@�C���p�X���X�g�쐬
    m_filePathList = std::make_unique<FilePathList>();
    // �t�@�C���p�X���X�g�ǂݍ���
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
    
    // 60FPS�Œ�
    m_timer.SetFixedTimeStep(true);
    m_timer.SetTargetElapsedSeconds(1.0 / 60);
    
    
    // �t�F�[�h�̏�����
    m_fade->Initialize();
    
    // ���\�[�X�̓ǂݍ��݁A�쐬
    m_resourceManager->CreateModelList(FileManager::LoadCSV(m_filePathList->GetPath(KT::File::MODEL)));
    m_resourceManager->CreateTextureList(FileManager::LoadCSV(m_filePathList->GetPath(KT::File::TEXTURE)));
    m_resourceManager->CreateSoundList(m_audioEngine.get(), FileManager::LoadCSV(m_filePathList->GetPath(KT::File::SOUND)));
    // �V�[���̐����A������
    m_sceneManager = std::make_unique<SceneManager>();
    m_sceneManager->Initialize();

    // UI�}�l�[�W���[�̏�����
    m_uiManager->Initialize();

    // �G�t�F�N�g�}�l�[�W���[������
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
   
    // �I�[�f�B�I�G���W���̍X�V
    if (!m_audioEngine->Update())
    {
        // No audio device is active
        if (m_audioEngine->IsCriticalError())
        {
            OutputDebugString(L"AudioEngine Error!\n");
        }
    }

    // �L�[�̍X�V
    Keyboard::State key = Keyboard::Get().GetState();
    m_keyStateTracker->Update(key);

    // �t�F�[�h���͓��͂��󂯕t���Ȃ�
    if(!m_fade->IsFade())
    {
        // ���̓}�l�[�W���[�̍X�V
        m_inputManager->Update();
    }
    
    // �V�[���̍X�V
    m_sceneManager->Update();
    
    // UI�̍X�V
    m_uiManager->Update();

    // �t�F�[�h�̍X�V
    m_fade->Update(elapsedTime);

    // �L�[���͏�ԃ��Z�b�g
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

    // �V�[���̕`��
    m_sceneManager->Render();

    // UI�̕`��
    m_uiManager->Render();

    // �t�F�[�h�̕`��
    m_fade->Render();


    // �f�o�b�O�����̕\��
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
    
    // �t���X�N���[�������ׂ�
    BOOL fullscreen = FALSE;
    m_deviceResources->GetSwapChain()->GetFullscreenState(&fullscreen, nullptr);
    // �t���X�N���[������������Ă��܂������̏���
    if (m_fullscreen != fullscreen)
    {
        m_fullscreen = fullscreen;
        // ResizeBuffers�֐����Ăяo��
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

    // ���\�[�X�̍쐬�A������ //

    // �R�����X�e�[�g
    m_commonStates = std::make_unique<CommonStates>(device);
    // �L�[�{�[�h�X�e�[�g
    m_keyStateTracker = std::make_unique<Keyboard::KeyboardStateTracker>();
    // �t�F�[�h
    m_fade = std::make_unique<Fade>();
    // ���̓}�l�[�W���[
    m_inputManager = std::make_unique<InputManager>(m_keyStateTracker.get());
    // ���\�[�X�}�l�[�W���[
    m_resourceManager = std::make_unique<ResourceManager>();
    // �X�e�[�W�}�l�[�W���[
    m_stageManager = std::make_unique<StageManager>(StageFactory::CreateStageList(FileManager::OpenLoadFile(m_filePathList->GetPath(KT::File::STAGE))));
    // �����蔻��}�l�[�W���[
    m_collisionManager = std::make_unique<CollisionManager>();
    // UI�}�l�[�W���[
    m_uiManager = std::make_unique<UIManager>();
    // �G�t�F�N�g�}�l�[�W���[
    m_effectManager = std::make_unique<EffectManager>();
    // �f�o�b�O����
    m_debugFont = std::make_unique<Imase::DebugFont>(device, context, KT::MyUtility::StringToWide(m_filePathList->GetPath(KT::File::DEBUG_FONT)).c_str());
    // �����蔻��\��
    m_dispCol = std::make_unique<Imase::DisplayCollision>(device, context, true, false);
    // �Q�[�����\�[�X�̃C���X�^���X���擾
    GameResource* gameResource = GameResource::GetInstance();

    // �Q�[�����\�[�X�Ŏg�p������̂�ݒ肵�Ă���
    gameResource->SetDeviceResources(m_deviceResources.get());      // �f�o�C�X���\�[�X
    gameResource->SetStepTimer(&m_timer);                           // �X�e�b�v�^�C�}-
    gameResource->SetCommonStates(m_commonStates.get());            // �R�����X�e�[�g
    gameResource->SetKeyboardStateTracker(m_keyStateTracker.get()); // �L�[�{�[�h�X�e�[�g�g���b�J�[
    gameResource->SetFade(m_fade.get());                            // �t�F�[�h
    gameResource->SetInputManager(m_inputManager.get());            // ���̓}�l�[�W���[
    gameResource->SetResourceManager(m_resourceManager.get());      // ���\�[�X�}�l�[�W���[
    gameResource->SetStageManager(m_stageManager.get());            // �X�e�[�W�}�l�[�W���[
    gameResource->SetCollisionManager(m_collisionManager.get());    // �����蔻��}�l�[�W���[
    gameResource->SetUIManager(m_uiManager.get());                  // UI�}�l�[�W���[
    gameResource->SetEffectManager(m_effectManager.get());          // �G�t�F�N�g�}�l�[�W���[
    gameResource->SetFilePathList(m_filePathList.get());            // �t�@�C���p�X���X�g
    gameResource->SetDebugFont(m_debugFont.get());                  // �f�o�b�O����
    gameResource->SetDisplayCollision(m_dispCol.get());             // �����蔻��\��
}

// Allocate all memory resources that change on a window SizeChanged event.
void Game::CreateWindowSizeDependentResources()
{
    // TODO: Initialize windows-size dependent objects here.
}

void Game::OnDeviceLost()
{
    // TODO: Add Direct3D resource cleanup here.

    // �㏈��
    m_sceneManager->Finalize();

}

void Game::OnDeviceRestored()
{
    CreateDeviceDependentResources();

    CreateWindowSizeDependentResources();
}
#pragma endregion
