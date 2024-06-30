/**
 *
 * @file MenuWindow.cpp
 *
 * @brief ��ʏ�ɕ\������E�B���h�E�̊��N���X�̃\�[�X�t�@�C��
 *
 * @author Kato Yuki
 *
 * @date 2024/2/5
 *
 */
#include "pch.h"
#include "MenuWindow.h"

#include "Game/MyLibrary/CommonResource/GameResource.h"
#include "Game/Scene/SceneManager.h"
#include "Game/Scene/TitleScene.h"
#include "Game/Scene/StageSelectScene.h"
#include "Game/Window/MenuWindowUI.h"
#include "Game/MyLibrary/Utility/MyUtility.h"
#include "Game/MyLibrary/File/FileManager.h"
#include "Library/nlohmann/json.hpp"

using namespace DirectX;

//------------------------------------------------------------------
/**
 * @brief �R���X�g���N�^
 *
 * @param sceneManager�F�V�[���}�l�[�W���[�̃|�C���^
 * @param windowSize  �F�E�B���h�E�̃T�C�Y
 * @param texture     �F�E�B���h�E�Ɏg�p����e�N�X�`��
 * @param position    �F�E�B���h�E�̕`��ʒu
 */
MenuWindow::MenuWindow(SceneManager* sceneManager, DirectX::SimpleMath::Vector2 windowSize, KT::Texture::TextureData texture, DirectX::SimpleMath::Vector2 position)
	: Window(windowSize, texture, position)
	, m_sceneManager(sceneManager)
	, m_ui(nullptr)
	, m_openScene(OpenScene::NONE)
	, m_currentMenu(MenuType::HOME)
	, m_selectHomeMenu(SelectHomeMenu::OPTION)
	, m_selectOptionMenu(SelectOptionMenu::BGM)
{
}

//------------------------------------------------------------------
/**
 * @brief �f�X�g���N�^
 */
MenuWindow::~MenuWindow()
{
}

//------------------------------------------------------------------
/**
 * @brief ������
 *
 * @param  �Ȃ�
 * @return �Ȃ�
 */
void MenuWindow::Initialize()
{
	// ���N���X�̏�����
	Window::Initialize();

	// UI�쐬�A������
	m_ui = std::make_unique<MenuWindowUI>(this);
	m_ui->Initialize();

	// �f�[�^�擾
	FilePathList* filePathList = GameResource::GetInstance()->GetFilePathList();
	nlohmann::json data = FileManager::LoadJSON(filePathList->GetPath(KT::File::OPTION));
	// ���ʂ܂݂̈ʒu����
	m_ui->BGMAdjustment(data[KT::Sound::PROPERTIE_SOUND][KT::Sound::BGM]);
	m_ui->SEAdjustment(data[KT::Sound::PROPERTIE_SOUND][KT::Sound::SE]);
 }

//------------------------------------------------------------------
/**
 * @brief �X�V
 *
 * @param  �Ȃ�
 * @return �Ȃ�
 */
void MenuWindow::Update()
{
	// �t���O�������Ă��Ȃ��Ȃ�I��
	if (!IsOpen()) return;

	// �J���Ă��郁�j���[�̍X�V
	switch (m_currentMenu)
	{
	// �z�[��
	case MenuWindow::MenuType::HOME:
		UpdateHome();
		break;
	// �ݒ�
	case MenuWindow::MenuType::OPTION:
		UpdateOption();
		break;
	// ��O
	default:
		assert(false && "���j���[�������̒l�ł�");
		break;
	}
}

//------------------------------------------------------------------
/**
 * @brief �z�[����ʂ̍X�V����
 *
 * @param  �Ȃ�
 * @return �Ȃ�
 */
void MenuWindow::UpdateHome()
{
	// �L�[�}�l�[�W���[�擾
	InputManager* inputManager = GameResource::GetInstance()->GetInputManager();

	// �I��
	KT::MyUtility::MenuSelect(
		inputManager->GetKey(Keyboard::Keys::Up).press, 
		inputManager->GetKey(Keyboard::Keys::Down).press, 
		m_selectHomeMenu);
	// ����
	if (inputManager->GetKey(Keyboard::Keys::Enter).press) OnEnterHome();
	// UI�̑I������
	m_ui->SelectHome(static_cast<int>(m_selectHomeMenu));
}

//------------------------------------------------------------------
/**
 * @brief �ݒ��ʂ̍X�V
 *
 * @param  �Ȃ�
 * @return �Ȃ�
 */
void MenuWindow::UpdateOption()
{
	// �L�[�}�l�[�W���[�擾
	InputManager* inputManager = GameResource::GetInstance()->GetInputManager();
	
	// �I��
	KT::MyUtility::MenuSelect(
		inputManager->GetKey(Keyboard::Keys::Up).press,
		inputManager->GetKey(Keyboard::Keys::Down).press,
		m_selectOptionMenu);
	// ���ʒ���
	SoundSetting();
	// ����
	if (inputManager->GetKey(DirectX::Keyboard::Keys::Enter).press) OnEnterOption();
	// UI�̑I������
	m_ui->SelectOption(static_cast<int>(m_selectOptionMenu));
}

//------------------------------------------------------------------
/**
 * @brief �E�B���h�E�̕\���ؑ�
 *
 * @param  openScene�F�E�B���h�E���J�����V�[��
 * @return �Ȃ�
 */
void MenuWindow::OpenClose(OpenScene openScene)
{
	// �J����
	if (IsOpen()) Open(openScene);
	// ����
	else Close();
}

//------------------------------------------------------------------
/**
 * @brief �E�B���h�E���J��
 *
 * @param  �Ȃ�
 * @return �Ȃ�
 */
void MenuWindow::Open(OpenScene openScene)
{
	// �E�B���h�E���J��
	Window::Open();
	// ���j���[���J�����V�[���ݒ�
	m_openScene = openScene;
	// �����V�[���֖߂�{�^���̐ݒ�
	m_ui->ReturnSceneButtonSetting(openScene);
	// ���݂̃��j���[���z�[���ɐݒ�
	m_currentMenu = MenuType::HOME;
	// ���j���[��UI��\��
	m_ui->OpenMenu();
}

//------------------------------------------------------------------
/**
 * @brief �E�B���h�E�����
 *
 * @param  �Ȃ�
 * @return �Ȃ�
 */
void MenuWindow::Close()
{
	// �E�B���h�E�����
	Window::Close();
	// ���j���[UI���\��
	m_ui->CloseMenu();
}

//------------------------------------------------------------------
/**
 * @brief �z�[����ʂŌ��莞�̏���
 *
 * @param  �Ȃ�
 * @return �Ȃ�
 */
void MenuWindow::OnEnterHome()
{
	// �I�����Ă��郁�j���[���̏���
	switch (m_selectHomeMenu)
	{
	// �ݒ�
	case MenuWindow::SelectHomeMenu::OPTION:
		ChangeMenu(MenuType::OPTION);
		break;
	// �V�[���ɖ߂�
	case MenuWindow::SelectHomeMenu::RETURN_SCENE:
		if      (m_openScene == OpenScene::SELECT) m_sceneManager->SetNextScene<TitleScene>();
		else if (m_openScene == OpenScene::PLAY)   m_sceneManager->SetNextScene<StageSelectScene>();	
		break;
	// ��O
	case MenuWindow::SelectHomeMenu::COUNT:
	default:
		assert(false && "�z�[�����j���[�������̒l�ł�");
		break;
	}

	// SE�𗬂�
	GameResource::GetInstance()->GetResourceManager()->PlaySound(
		KT::Sound::SE, KT::Sound::SENumber::XACT_WAVEBANK_SE_DECISION);
}

//------------------------------------------------------------------
/**
 * @brief �ݒ��ʂŌ��莞�̏���
 *
 * @param  �Ȃ�
 * @return �Ȃ�
 */
void MenuWindow::OnEnterOption()
{
	switch (m_selectOptionMenu)
	{
	// BGM��SE�̎��͈���֓�����
	case MenuWindow::SelectOptionMenu::BGM:
		m_selectOptionMenu = SelectOptionMenu::SE;
		break;
	case MenuWindow::SelectOptionMenu::SE:
		m_selectOptionMenu = SelectOptionMenu::RETURN;
		break;
	// �z�[����ʂɖ߂�
	case MenuWindow::SelectOptionMenu::RETURN:
		// SE�𗬂�
		GameResource::GetInstance()->GetResourceManager()->PlaySound(
			KT::Sound::SE, KT::Sound::SENumber::XACT_WAVEBANK_SE_DECISION);
		ChangeMenu(MenuType::HOME);
		break;
	// ��O
	case MenuWindow::SelectOptionMenu::COUNT:
	default:
		assert(false && "�ݒ胁�j���[�������̒l�ł�");
		break;
	}
}

//------------------------------------------------------------------
/**
 * @brief ���̐ݒ�
 *
 * @param  �Ȃ�
 * @return �Ȃ�
 */
void MenuWindow::SoundSetting()
{
	// �����}�l�[�W���[�擾
	InputManager* inputManager = GameResource::GetInstance()->GetInputManager();

	// �܂݂̈ړ����x
	float speed = 0.0f;
	// ���ʂ��グ��
	if      (inputManager->GetKey(Keyboard::Keys::Right).down) speed = KNOB_SPEED;
	// ���ʂ�������
	else if (inputManager->GetKey(Keyboard::Keys::Left).down)  speed = -KNOB_SPEED;
	else     return;

	// ���ʒ���
	switch (m_selectOptionMenu)
	{
	// BGM
	case MenuWindow::SelectOptionMenu::BGM:
		AdjustmentVolume(speed, KT::Sound::BGM);
		break;
	// SE
	case MenuWindow::SelectOptionMenu::SE:
		AdjustmentVolume(speed, KT::Sound::SE);
		break;
	// �߂�{�^���͉������Ȃ�
	case MenuWindow::SelectOptionMenu::RETURN:
		break;
	// ��O
	case MenuWindow::SelectOptionMenu::COUNT:
	default:
		assert(false && "���j���[�������Ȓl�ł�");
		break;
	}
}

//------------------------------------------------------------------
/**
 * @brief ���ʒ���
 *
 * @param  speed�F�܂݂̈ړ���
 * @param  type �F�������鉹�̎��
 * @return �Ȃ�
 */
void MenuWindow::AdjustmentVolume(float& speed, const std::string& type)
{
	// �e�탊�\�[�X�擾
	GameResource*    gameResource    = GameResource::GetInstance();
	ResourceManager* resourceManager = gameResource->GetResourceManager();
	FilePathList*    filePathList    = gameResource->GetFilePathList();
	// ���ʃf�[�^��ǂݍ���
	nlohmann::json data = FileManager::LoadJSON(filePathList->GetPath(KT::File::OPTION));
	// ���ʎ擾
	float volume = data[KT::File::SOUND][type];

	// ���ʒ���
	volume += speed;
	volume = std::min(std::max(volume, 0.0f), MAX_VOLUME);
	resourceManager->VolumeSetting(type, volume);
	// ��ނɂ���Đ؂�ւ���
	if     (type == KT::Sound::BGM) m_ui->BGMAdjustment(volume);
	else if(type == KT::Sound::SE)  m_ui->SEAdjustment(volume);

	// �f�[�^�X�V
	data[KT::File::SOUND][type] = volume;
	FileManager::ReadJSON(filePathList->GetPath(KT::File::OPTION), data);
}

//------------------------------------------------------------------
/**
 * @brief �ݒ��ʂ̍X�V
 *
 * @param  �Ȃ�
 * @return �Ȃ�
 */
void MenuWindow::ChangeMenu(MenuType nextMenu)
{
	switch (nextMenu)
	{
	// �z�[�����
	case MenuWindow::MenuType::HOME:
		m_currentMenu = MenuType::HOME;
		m_ui->OpenHome();
		break;
	// �ݒ���
	case MenuWindow::MenuType::OPTION:
		m_currentMenu = MenuType::OPTION;
		m_ui->OpenOption();
		break;
	// ��O
	default:
		assert(false && "���j���[�������Ȓl�ł�");
		break;
	}
}