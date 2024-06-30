/**
 *
 * @file GameResource.h
 *
 * @brief �Q�[���Ŏg�p���鋤�L���\�[�X�̃w�b�_�[�t�@�C��
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
// �ϐ�
//----------------------------------------------
private:

	// �Q�[�����\�[�X�C���X�^���X
	static std::unique_ptr<GameResource> m_gameResource;

private:

	// �f�o�C�X���\�[�X
	DX::DeviceResources* m_deviceResources;
	// �X�e�b�v�^�C�}�[
	DX::StepTimer* m_stepTimer;
	// �R�����X�e�[�g
	DirectX::CommonStates* m_commonStates;
	// �L�[�{�[�h�X�e�[�g�g���b�J�[
	DirectX::Keyboard::KeyboardStateTracker* m_keyStateTracker;
	// �t�F�[�h
	Fade* m_fade;
	// ���̓}�l�[�W���[
	InputManager* m_inputManager;
	// ���\�[�X�}�l�[�W���[
	ResourceManager* m_resourceManager;
	// �X�e�[�W�}�l�[�W���[
	StageManager* m_stageManager;
	// �����蔻��}�l�[�W���[
	CollisionManager* m_collisionManager;
	// UI�}�l�[�W���[
	UIManager* m_uiManager;
	// �G�t�F�N�g�}�l�[�W���[
	EffectManager* m_effectManager;
	// ���j���[�E�B���h�E
	MenuWindow* m_menuWindow;
	// �t�@�C���p�X���X�g
	FilePathList* m_filePathList;
	// �f�o�b�O�t�H���g
	Imase::DebugFont* m_debugFont;
	// �����蔻��\��
	Imase::DisplayCollision* m_displayCollision;


//----------------------------------------------
// �֐�
//----------------------------------------------
private:

	// �R���X�g���N�^
	GameResource();
	// �R�s�[�R���X�g���N�^�֎~
	GameResource(const GameResource& gameResource) = delete;
	// ����֎~
	void operator=(const GameResource& gameResource) = delete;

public:

	// �f�X�g���N�^
	~GameResource() = default;

	// �C���X�^���X�̎擾
	static GameResource* const GetInstance();

	//�f�o�C�X���\�[�X�̎擾
	DX::DeviceResources* GetDeviceResources()const;
	// �f�o�C�X���\�[�X�̐ݒ�
	void SetDeviceResources(DX::DeviceResources* deviceResources);
	// �X�e�b�v�^�C�}�[�̎擾
	DX::StepTimer* GetStepTimer()const;
	// �X�e�b�v�^�C�}�[�̐ݒ�
	void SetStepTimer(DX::StepTimer* stepTimer);
	// �R�����X�e�[�g�̎擾
	DirectX::CommonStates* GetCommonStates();
	// �R�����X�e�[�g�̐ݒ�
	void SetCommonStates(DirectX::CommonStates* commonStates);
	// �L�[�{�[�h�X�e�[�g�g���b�J�[�̎擾
	DirectX::Keyboard::KeyboardStateTracker* GetKeyboardStateTracker()const;
	// �L�[�{�[�h�X�e�[�g�g���b�J�[�̐ݒ�
	void SetKeyboardStateTracker(DirectX::Keyboard::KeyboardStateTracker* keyStateTracker);
	// �t�F�[�h�̎擾
	Fade* GetFade() const;
	// �t�F�[�h�̐ݒ�
	void SetFade(Fade* fade);
	// ���̓}�l�[�W���[
	InputManager* GetInputManager()const;
	//  ���̓}�l�[�W���[�̐ݒ�
	void SetInputManager(InputManager* inputManager);
	// ���\�[�X�}�l�[�W���[�̎擾
	ResourceManager* GetResourceManager() const;
	// ���\�[�X�}�l�[�W���[�̎擾
	void SetResourceManager(ResourceManager* resourceManager);
	// �X�e�[�W�}�l�[�W���[�̎擾
	StageManager* GetStageManager() const;
	// �X�e�[�W�}�l�[�W���[�̎擾
	void SetStageManager(StageManager* stageManager);
	// �����蔻��}�l�[�W���[�̎擾
	CollisionManager* GetCollisionManager() const;
	// �����蔻��}�l�[�W���[�̐ݒ�
	void SetCollisionManager(CollisionManager* collisionManager);
	// UI�}�l�[�W���[�̎擾
	UIManager* GetUIManager() const;
	// UI�}�l�[�W���[�̐ݒ�
	void SetUIManager(UIManager* uiManager);
	// �G�t�F�N�g�}�l�[�W���[�̎擾
	EffectManager* GetEffectManager() const;
	// �G�t�F�N�g�}�l�[�W���[�̐ݒ�
	void SetEffectManager(EffectManager* effectManager);
	// ���j���[�E�B���h�E�̎擾
	MenuWindow* GetMenuWindow() const;
	// ���j���[�E�B���h�E�̐ݒ�
	void SetMenuWindow(MenuWindow* menuWindow);
	// �t�@�C���p�X���X�g�̎擾
	FilePathList* GetFilePathList() const;
	// �t�@�C���p�X���X�g�̐ݒ�
	void SetFilePathList(FilePathList* filePathList);
	// �f�o�b�O�����̎擾
	Imase::DebugFont* GetDebugFont() const;
	// �f�o�b�O�����̐ݒ�
	void SetDebugFont(Imase::DebugFont* debugFont);
	// �����蔻��\���̎擾
	Imase::DisplayCollision* GetDisplayCollision();
	void SetDisplayCollision(Imase::DisplayCollision* displayCollision);

};