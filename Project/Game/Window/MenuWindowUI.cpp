/**
 *
 * @file MenuWindowUI.cpp
 *
 * @brief ���j���[�E�B���h�E��UI���܂Ƃ߂�N���X�̃\�[�X�t�@�C��
 *
 * @author Kato Yuki
 *
 * @date 2024/2/2
 *
 */
#include "pch.h"
#include "MenuWindowUI.h"

#include "Game/MyLibrary/CommonResource/GameResource.h"
#include "Game/UI/OperatableUI.h"

using namespace DirectX;

//------------------------------------------------------------------
/**
 * @brief �R���X�g���N�^
 *
 * @param menuWindow�F���j���[�E�B���h�E�̃|�C���^
 */
MenuWindowUI::MenuWindowUI(MenuWindow* menuWindow)
	: m_menuWindow(menuWindow)
	, m_toTitleScene(nullptr)
	, m_toStageSelectScene(nullptr)
	, m_selectUIHome()
	, m_bgmKnob(nullptr)
	, m_seKnob(nullptr)
	, m_toHomeMenu(nullptr)
	, m_bgmKnobRange()
	, m_seKnobRange()
	, m_selectUIOption()
{
}

//------------------------------------------------------------------
/**
 * @brief �f�X�g���N�^
 */
MenuWindowUI::~MenuWindowUI()
{
}

//------------------------------------------------------------------
/**
 * @brief ������
 *
 * @param  �Ȃ�
 * @return �Ȃ�
 */
void MenuWindowUI::Initialize()
{
	// �G�C���A�X�錾
	using Home = MenuWindow::SelectHomeMenu;
	using Option = MenuWindow::SelectOptionMenu;

	// UI�쐬
	CreateUI(KT::UI::PROPERTIE_MEMU);

	// �z�[���E�B���h�E�̑I������UI�̐ݒ�
	m_selectUIHome.resize(static_cast<int>(Home::COUNT));
	m_selectUIHome[static_cast<int>(Home::OPTION)]       = GetUI(KT::UI::MENU_OPTION_MENU_TEXT);
	m_selectUIHome[static_cast<int>(Home::RETURN_SCENE)] = nullptr;
	m_toTitleScene       = GetUI(KT::UI::MENU_TO_TITLE_SCENE_TEXT);
	m_toStageSelectScene = GetUI(KT::UI::MENU_TO_SELECT_SCENE_TEXT);
	// �ݒ�E�B���h�E�̑I������UI�̐ݒ�
	m_selectUIOption.resize(static_cast<int>(Option::COUNT));
	m_selectUIOption[static_cast<int>(Option::BGM)]    = GetUI(KT::UI::MENU_BGM_KNOB);
	m_selectUIOption[static_cast<int>(Option::SE)]     = GetUI(KT::UI::MENU_SE_KNOB);
	m_selectUIOption[static_cast<int>(Option::RETURN)] = GetUI(KT::UI::MENU_TO_HOME_MENU);
	// �Z�Z�V�[���֖߂�e�L�X�g�̗L���������̏�Ԑݒ�
	OperatableUI::UIState activeState =
	{
		SimpleMath::Vector2::One, SimpleMath::Vector2::One,
		SimpleMath::Vector4::One, SimpleMath::Vector4::Zero
	};
	m_toTitleScene->SetState(OperatableUI::UIStateType::ACTIVE, activeState);
	m_toStageSelectScene->SetState(OperatableUI::UIStateType::ACTIVE, activeState);

	// ���ʒ��߂܂݂̉��͈͐ݒ�
	ResourceManager* resourceManager = GameResource::GetInstance()->GetResourceManager();
	float barSizeX   = resourceManager->GetTexture(KT::Texture::UI_ADJUST_BAR).size.x;
	// �o�[�̈ʒu���N�_�ɉ摜�T�C�Y�̔������ɐݒ肷��
	float bgmBarPosX = m_selectUIOption[static_cast<int>(Option::BGM)]->GetPosition().x;
	m_bgmKnobRange   = SimpleMath::Vector2(bgmBarPosX - barSizeX * 0.5f, bgmBarPosX + barSizeX * 0.5f);
	float seBarPosX  = m_selectUIOption[static_cast<int>(Option::SE)]->GetPosition().x;
	m_seKnobRange    = SimpleMath::Vector2(seBarPosX - barSizeX * 0.5f, seBarPosX + barSizeX * 0.5f);
}

//------------------------------------------------------------------
/**
 * @brief ���j���[���J��
 *
 * @param  �Ȃ�
 * @return �Ȃ�
 */
void MenuWindowUI::OpenMenu()
{
	// �E�B���h�EUI��o�^
	AddUIManager(TAG_ALWAYS);
	// �z�[�����UI��o�^
	AddUIManager(TAG_MENU_HOME);
}

//------------------------------------------------------------------
/**
 * @brief �z�[����ʂ��J��
 *
 * @param  �Ȃ�
 * @return �Ȃ�
 */
void MenuWindowUI::OpenHome()
{
	// �ݒ���UI�̓o�^����
	DeleteUIManager(TAG_MENU_OPTION);
	// �z�[�����UI��o�^
	AddUIManager(TAG_MENU_HOME);
}

//------------------------------------------------------------------
/**
 * @brief �ݒ��ʂ��J��
 *
 * @param  �Ȃ�
 * @return �Ȃ�
 */
void MenuWindowUI::OpenOption()
{
	// �z�[�����UI�̓o�^����
	DeleteUIManager(TAG_MENU_HOME);
	// �ݒ���UI�̓o�^
	AddUIManager(TAG_MENU_OPTION);
}

//------------------------------------------------------------------
/**
 * @brief ���j���[�����
 *
 * @param  �Ȃ�
 * @return �Ȃ�
 */
void MenuWindowUI::CloseMenu()
{
	// �S�Ă�UI�̓o�^����
	DeleteUIManagerAll();
}

//------------------------------------------------------------------
/**
 * @brief �z�[����ʂ̑I������
 *
 * @param  type�F�I�����Ă��郁�j���[�̔ԍ�
 * @return �Ȃ�
 */
void MenuWindowUI::SelectHome(const int& type)
{
	// �I������
	Select(type, m_selectUIHome);
}

//------------------------------------------------------------------
/**
 * @brief �ݒ��ʂ̑I������
 *
 * @param  type�F�I�����Ă��郁�j���[�̔ԍ�
 * @return �Ȃ�
 */
void MenuWindowUI::SelectOption(const int& type)
{
	// �I������
	Select(type, m_selectUIOption);
}

//------------------------------------------------------------------
/**
 * @brief ���j���[�̑I������
 *
 * @param  type�F�I�����Ă��郁�j���[�̔ԍ�
 * @return �Ȃ�
 */
void MenuWindowUI::Select(const int& selectType, const std::vector<OperatableUI*>& changeColorList)
{
	for (int i = 0; i < changeColorList.size(); i++)
	{
		changeColorList[i]->SelectStateUpdate(i == selectType);
	}
}

//------------------------------------------------------------------
/**
 * @brief BGM�̒���
 *
 * @param  volume�F����
 * @return �Ȃ�
 */
void MenuWindowUI::BGMAdjustment(const float& volume)
{
	using Option = MenuWindow::SelectOptionMenu;

	OptionAdjustment(volume, m_selectUIOption[static_cast<int>(Option::BGM)], m_bgmKnobRange);
}

//------------------------------------------------------------------
/**
 * @brief SE�̒���
 *
 * @param  volume�F����
 * @return �Ȃ�
 */
void MenuWindowUI::SEAdjustment(const float& volume)
{
	using Option = MenuWindow::SelectOptionMenu;
	
	OptionAdjustment(volume, m_selectUIOption[static_cast<int>(Option::SE)], m_seKnobRange);
}

//------------------------------------------------------------------
/**
 * @brief ��������
 *
 * @param  volume   �F����
 * @param  knob     �F�܂�UI
 * @param  knobRange�F�܂݂̈ړ��͈�
 * @return �Ȃ�
 */
void MenuWindowUI::OptionAdjustment(const float& volume, OperatableUI* knob, const DirectX::SimpleMath::Vector2& knobRange)
{
	// �܂݂̈ʒu
	SimpleMath::Vector2 knobPos = knob->GetPosition();
	// ���ʂ̒l����܂݂̈ʒu���v�Z����
	knobPos.x = knobRange.x + (knobRange.y - knobRange.x) * volume;	
	// �܂݂̈ʒu���f
	knob->SetPosition(knobPos);
}

//------------------------------------------------------------------
/**
 * @brief �V�[���֖߂�{�^���̐ݒ�
 *
 * @param  openScene�F���j���[���J���Ă���V�[��
 * @return �Ȃ�
 */
void MenuWindowUI::ReturnSceneButtonSetting(MenuWindow::OpenScene openScene)
{
	using Home = MenuWindow::SelectHomeMenu;

	// ���j���[���J�����V�[���ɂ���ď����𕪂���
	switch (openScene)
	{
	// �X�e�[�W�Z���N�g
	case MenuWindow::OpenScene::SELECT:
		m_selectUIHome[static_cast<int>(Home::RETURN_SCENE)] = m_toTitleScene;
		m_toTitleScene->ActiveStateUpdate(true);
		m_toStageSelectScene->ActiveStateUpdate(false);
		break;
	// �v���C
	case MenuWindow::OpenScene::PLAY:
		m_selectUIHome[static_cast<int>(Home::RETURN_SCENE)] = m_toStageSelectScene;
		m_toTitleScene->ActiveStateUpdate(false);
		m_toStageSelectScene->ActiveStateUpdate(true);
		break;
	// ��O
	case MenuWindow::OpenScene::NONE:
	default:
		assert(false && "OpenScene�������̒l�ł�");
		break;
	}
}