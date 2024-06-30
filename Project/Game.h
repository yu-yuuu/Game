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

    // ��ʃ��[�h��ݒ肷��֐��iTRUE�F�t���X�N���[���j
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
    
    // ��ʃ��[�h�iTRUE�F�t���X�N���[���j
    BOOL m_fullscreen;

    // �R�����X�e�[�g
    std::unique_ptr<DirectX::CommonStates> m_commonStates;
    // �L�[�{�[�h�X�e�[�g�g���b�J�[
    std::unique_ptr<DirectX::Keyboard::KeyboardStateTracker> m_keyStateTracker;
    // �I�[�f�B�I�G���W��
    std::unique_ptr<DirectX::AudioEngine> m_audioEngine;
    // �V�[���}�l�[�W���[
    std::unique_ptr<SceneManager> m_sceneManager;
    // �t�F�[�h
    std::unique_ptr<Fade> m_fade;
    // ���̓}�l�[�W���[
    std::unique_ptr<InputManager> m_inputManager;
    // ���\�[�X�}�l�[�W���[
    std::unique_ptr<ResourceManager> m_resourceManager;
    // �X�e�[�W�}�l�[�W���[
    std::unique_ptr<StageManager> m_stageManager;
    // �����蔻��}�l�[�W���[
    std::unique_ptr<CollisionManager> m_collisionManager;
    // UI�}�l�[�W���[
    std::unique_ptr<UIManager> m_uiManager;
    // �G�t�F�N�g�}�l�[�W���[
    std::unique_ptr<EffectManager> m_effectManager;
    // �t�@�C���p�X���X�g
    std::unique_ptr<FilePathList> m_filePathList;

 // ImaseLib
private:

    // �f�o�b�O����
    std::unique_ptr<Imase::DebugFont> m_debugFont;
    // �����蔻��\��
    std::unique_ptr<Imase::DisplayCollision> m_dispCol;
    
};
