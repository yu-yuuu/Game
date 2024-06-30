/**
 *
 * @file MenuWindowUI.h
 *
 * @brief ���j���[�E�B���h�E��UI���܂Ƃ߂�N���X�̃w�b�_�[�t�@�C��
 *
 * @author Kato Yuki
 *
 * @date 2024/2/2
 *
 */
#pragma once

#include <vector>
#include <string>
#include "Game/UI/SceneUI/SceneUI.h"
#include "Game/Window/MenuWindow.h"

class OperatableUI;

class MenuWindowUI : public SceneUI
{
//----------------------------------------------
// �萔
//----------------------------------------------
private:

	// ��ɕ`�悷��UI�̃^�O
	const std::string TAG_ALWAYS = "Always";
	// �z�[�����UI�̃^�O
	const std::string TAG_MENU_HOME = "MenuHome";
	// �ݒ���UI�̃^�O
	const std::string TAG_MENU_OPTION = "MenuOption";

//----------------------------------------------
// �ϐ�
//----------------------------------------------
private:

	// ���j���[�E�B���h�E
	MenuWindow* m_menuWindow;

	// �^�C�g���֖߂�{�^��
	OperatableUI* m_toTitleScene;
	// �X�e�[�W�Z���N�g�֖߂�{�^��
	OperatableUI* m_toStageSelectScene;
	// �I������UI
	std::vector<OperatableUI*> m_selectUIHome;

	// BGM���ʂ܂�UI
	OperatableUI* m_bgmKnob;
	// SE���ʂ܂�UI
	OperatableUI* m_seKnob;
	// �߂�{�^��
	OperatableUI* m_toHomeMenu;
	// BGM�܂݂̈ړ��͈�
	DirectX::SimpleMath::Vector2 m_bgmKnobRange;
	// SE�܂݂̈ړ��͈�
	DirectX::SimpleMath::Vector2 m_seKnobRange;
	// �I������UI
	std::vector<OperatableUI*> m_selectUIOption;

//----------------------------------------------
// �֐�
//----------------------------------------------
public:

	// �R���X�g���N�^
	MenuWindowUI(MenuWindow* menuWindow);
	// �f�X�g���N�^
	~MenuWindowUI();
	// ������
	void Initialize() override;

	// ���j���[���J��
	void OpenMenu();
	// �z�[����ʂ��J��
	void OpenHome();
	// �ݒ��ʂ��J��
	void OpenOption();
	// ���j���[����鎞�̏���
	void CloseMenu();

	// �z�[����ʂ̑I��
	void SelectHome(const int& type);
	// �ݒ��ʂ̑I��
	void SelectOption(const int& type);
	// �I������
	void Select(const int& selectType, const std::vector<OperatableUI*>& changeColorList);

	// BGM�̒���
	void BGMAdjustment(const float& volume);
	// SE�̒���
	void SEAdjustment(const float& volume);
	// ��������
	void OptionAdjustment(const float& volume, OperatableUI* knob, const DirectX::SimpleMath::Vector2& knobRange);

	// �V�[���֖߂�{�^���̐ݒ�
	void ReturnSceneButtonSetting(MenuWindow::OpenScene openScene);

};