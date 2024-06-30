/**
 *
 * @file GameResource.cpp
 *
 * @brief �Q�[���Ŏg�p���鋤�L���\�[�X�̃\�[�X�t�@�C��
 *
 * @author Kato Yuki
 *
 * @date 2023/11/11
 *
 */
#include "pch.h"
#include "GameResource.h"

//----------------------------------------------
// �C���X�^���X�̏�����
//----------------------------------------------
std::unique_ptr<GameResource> GameResource::m_gameResource = nullptr;

//------------------------------------------------------------------
/**
 * @brief �R���X�g���N�^
 *
 * @param �Ȃ�
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
 * @brief �C���X�^���X�̎擾
 *
 * @param �Ȃ�
 * @return GameResource�C���X�^���X
 */GameResource* const GameResource::GetInstance()
{
	// �C���X�^���X���Ȃ���ΐ�������
	if (!m_gameResource)
	{
		m_gameResource.reset(new GameResource());
	}
	return m_gameResource.get();
}

 //------------------------------------------------------------------
 /**
  * @brief �f�o�C�X���\�[�X�̎擾
  *
  * @param �Ȃ�
  * @return DX::DeviceResources*�F�f�o�C�X���\�[�X�̃|�C���^
  */
 DX::DeviceResources* GameResource::GetDeviceResources() const
{
	return m_deviceResources; 
}

 //------------------------------------------------------------------
 /**
  * @brief �f�o�C�X���\�[�X�̐ݒ�
  *
  * @param deviceResources�F�ݒ肷��f�o�C�X���\�[�X�̃|�C���^
  * @return �Ȃ�
  */
 void GameResource::SetDeviceResources(DX::DeviceResources* deviceResources)
{
	m_deviceResources = deviceResources;
}

 //------------------------------------------------------------------
 /**
  * @brief �X�e�b�v�^�C�}�[�̎擾
  *
  * @param �Ȃ�
  * @return DX::StepTimer*�F�X�e�b�v�^�C�}�[�̃|�C���^
  */
 DX::StepTimer* GameResource::GetStepTimer() const
{
	return m_stepTimer;
}

 //------------------------------------------------------------------
 /**
  * @brief �X�e�b�v�^�C�}�[�̐ݒ�
  *
  * @param stepTimer�F�ݒ肷��X�e�b�v�^�C�}�[�̃|�C���^
  * @return �Ȃ�
  */
 void GameResource::SetStepTimer(DX::StepTimer* stepTimer)
{
	m_stepTimer = stepTimer;
}

 //------------------------------------------------------------------
 /**
  * @brief �R�����X�e�[�g�̎擾
  *
  * @param �Ȃ�
  * @return DirectX::CommonStates*�F�R�����X�e�[�g�̃|�C���^
  */
 DirectX::CommonStates* GameResource::GetCommonStates()
{
	return m_commonStates;
}

 //------------------------------------------------------------------
 /**
  * @brief �R�����X�e�[�g�̐ݒ�
  *
  * @param commonStates�F�ݒ肷��R�����X�e�[�g�̃|�C���^
  * @return �Ȃ�
  */
 void GameResource::SetCommonStates(DirectX::CommonStates* commonStates)
{
	m_commonStates = commonStates;
}

 //------------------------------------------------------------------
 /**
  * @brief �L�[�{�[�h�X�e�[�g�g���b�J�[�̎擾
  *
  * @param �Ȃ�
  * @return DirectX::Keyboard::KeyboardStateTracker*�F�L�[�{�[�h�X�e�[�g�g���b�J�[�̃|�C���^
  */
 DirectX::Keyboard::KeyboardStateTracker* GameResource::GetKeyboardStateTracker() const
{
	return m_keyStateTracker;
}

 //------------------------------------------------------------------
 /**
  * @brief �L�[�{�[�h�X�e�[�g�g���b�J�[�̐ݒ�
  *
  * @param keyStateTracker�F�ݒ肷��L�[�{�[�h�X�e�[�g�g���b�J�[
  * @return �Ȃ�
  */
 void GameResource::SetKeyboardStateTracker(DirectX::Keyboard::KeyboardStateTracker* keyStateTracker)
{
	m_keyStateTracker = keyStateTracker;
}

 //------------------------------------------------------------------
 /**
  * @brief �t�F�[�h�̎擾
  *
  * @param �Ȃ�
  * @return �t�F�[�h�̃|�C���^
  */
 Fade* GameResource::GetFade() const
{
	return m_fade;
}

 //------------------------------------------------------------------
 /**
  * @brief �t�F�[�h�̐ݒ�
  *
  * @param fade�F�ݒ肷��t�F�[�h�̃|�C���^
  * @return �Ȃ�
  */
 void GameResource::SetFade(Fade* fade)
{
	m_fade = fade;
}

 //------------------------------------------------------------------
 /**
  * @brief ���̓}�l�[�W���[
  *
  * @param �Ȃ�
  * @return ���̓}�l�[�W���[�̃|�C���^
  */
 InputManager* GameResource::GetInputManager() const
{
	return m_inputManager;
}

 //------------------------------------------------------------------
 /**
  * @brief ���̓}�l�[�W���[�̐ݒ�
  *
  * @param inputManager�F�o�^������̓}�l�[�W���[�̃|�C���^
  * @return �Ȃ�
  */
 void GameResource::SetInputManager(InputManager* inputManager)
{
	m_inputManager = inputManager;
}

//------------------------------------------------------------------
/**
 * @brief ���\�[�X�}�l�[�W���[�̎擾
 *
 * @param �Ȃ�
 * @return ResourceManager*�F���\�[�X�}�l�[�W���[�̃|�C���^
 */
ResourceManager* GameResource::GetResourceManager() const
{
	return m_resourceManager;
}

//------------------------------------------------------------------
/**
 * @brief ���\�[�X�}�l�[�W���[�̐ݒ�
 *
 * @param  resourceManager�F�ݒ肷�郊�\�[�X�}�l�[�W���[�̃|�C���^
 * @return �Ȃ�
 */
void GameResource::SetResourceManager(ResourceManager* resourceManager)
{
	m_resourceManager = resourceManager;
}

//------------------------------------------------------------------
/**
 * @brief �X�e�[�W�}�l�[�W���[�̎擾
 *
 * @param  �Ȃ�
 * @return �X�e�[�W�}�l�[�W���[�̃|�C���^
 */
StageManager* GameResource::GetStageManager() const
{
	return m_stageManager;
}

//------------------------------------------------------------------
/**
 * @brief �X�e�[�W�}�l�[�W���[�̐ݒ�
 *
 * @param  stageManager�F�ݒ肷��X�e�[�W�}�l�[�W���[�̃|�C���^
 * @return �Ȃ�
 */
void GameResource::SetStageManager(StageManager* stageManager)
{
	m_stageManager = stageManager;
}

//------------------------------------------------------------------
/**
 * @brief �����蔻��}�l�[�W���[�̎擾
 *
 * @param  �Ȃ�
 * @return �����蔻��}�l�[�W���[�̃|�C���^
 */
CollisionManager* GameResource::GetCollisionManager() const
{
	return m_collisionManager;
}

//------------------------------------------------------------------
/**
 * @brief �����蔻��}�l�[�W���[�̐ݒ�
 *
 * @param  collisionManager�F�ݒ肷�铖���蔻��}�l�[�W���[�̃|�C���^
 * @return �Ȃ�
 */
void GameResource::SetCollisionManager(CollisionManager* collisionManager)
{
	m_collisionManager = collisionManager;
}

//------------------------------------------------------------------
/**
 * @brief UI�}�l�[�W���[�̎擾
 *
 * @param  �Ȃ�
 * @return UI�}�l�[�W���[�̃|�C���^
 */
UIManager* GameResource::GetUIManager() const
{
	return m_uiManager;
}

//------------------------------------------------------------------
/**
 * @brief UI�}�l�[�W���[�̐ݒ�
 *
 * @param  uiManager�F�ݒ肷��UI�}�l�[�W���[�̃|�C���^
 * @return �Ȃ�
 */
void GameResource::SetUIManager(UIManager* uiManager)
{
	m_uiManager = uiManager;
}

//------------------------------------------------------------------
/**
 * @brief �G�t�F�N�g�}�l�[�W���[�̎擾
 *
 * @param  �Ȃ�
 * @return �G�t�F�N�g�}�l�[�W���[�̃|�C���^
 */
EffectManager* GameResource::GetEffectManager() const
{
	return m_effectManager;
}

//------------------------------------------------------------------
/**
 * @brief �G�t�F�N�g�}�l�[�W���[�̐ݒ�
 *
 * @param  effectManager�F�ݒ肷��G�t�F�N�g�}�l�[�W���[�̃|�C���^
 * @return �Ȃ�
 */
void GameResource::SetEffectManager(EffectManager* effectManager)
{
	m_effectManager = effectManager;
}

//------------------------------------------------------------------
/**
 * @brief ���j���[�E�B���h�E�̎擾
 *
 * @param  �Ȃ�
 * @return ���j���[�E�B���h�E�̃|�C���^
 */
MenuWindow* GameResource::GetMenuWindow() const
{
	return m_menuWindow;
}

//------------------------------------------------------------------
/**
 * @brief ���j���[�E�B���h�E�̐ݒ�
 *
 * @param  menuWindow�F�ݒ肷�郁�j���[�E�B���h�E�̃|�C���^
 * @return �Ȃ�
 */
void GameResource::SetMenuWindow(MenuWindow* menuWindow)
{
	m_menuWindow = menuWindow;
}
//------------------------------------------------------------------
/**
 * @brief �t�@�C���p�X���X�g�̎擾
 *
 * @param  �Ȃ�
 * @return �t�@�C���p�X���X�g�̃|�C���^
 */
FilePathList* GameResource::GetFilePathList() const
{
	return m_filePathList;
}

//------------------------------------------------------------------
/**
 * @brief �t�@�C���p�X���X�g�̐ݒ�
 *
 * @param  filePathList�F�ݒ肷��t�@�C���p�X���X�g�̃|�C���^
 * @return �Ȃ�
 */
void GameResource::SetFilePathList(FilePathList* filePathList)
{
	m_filePathList = filePathList;
}

//------------------------------------------------------------------
/**
 * @brief �f�o�b�O�����̎擾
 *
 * @param �Ȃ�
 * @return Imase::DebugFont*�F�f�o�b�O�����̃|�C���^
 */
Imase::DebugFont* GameResource::GetDebugFont() const
{
	return m_debugFont;
}

//------------------------------------------------------------------
/**
 * @brief �f�o�b�O�����̐ݒ�
 *
 * @param  debugFont�F�ݒ肷��f�o�b�O�����̃|�C���^
 * @return �Ȃ�
 */
void GameResource::SetDebugFont(Imase::DebugFont* debugFont)
{
	m_debugFont = debugFont;
}

//------------------------------------------------------------------
/**
 * @brief �����蔻��\���N���X�̎擾
 *
 * @param  �Ȃ�
 * @return DisplayCollision�F�����蔻��\���N���X�̃|�C���^
 */
Imase::DisplayCollision* GameResource::GetDisplayCollision()
{
	return m_displayCollision;
}

//------------------------------------------------------------------
/**
 * @brief �����蔻��\���N���X�̐ݒ�
 *
 * @param  displayCollision�F�ݒ肷�铖���蔻��\���N���X�̃|�C���^
 * @return �Ȃ�
 */
void GameResource::SetDisplayCollision(Imase::DisplayCollision* displayCollision)
{
	m_displayCollision = displayCollision;
}
