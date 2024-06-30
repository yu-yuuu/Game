/**
 *
 * @file TitleSceneUI.h
 *
 * @brief �^�C�g���V�[���V�[���Ŏg�p����UI�A�摜�N���X�̃w�b�_�[�t�@�C��
 *
 * @author Kato Yuki
 *
 * @date 2024/1/22
 *
 */
#pragma once

#include <vector>
#include <string>
#include "Game/UI/SceneUI/SceneUI.h"

class TitleScene;
class OperatableUI;

class TitleSceneUI : public SceneUI
{
//----------------------------------------------
// �萔
//----------------------------------------------
private:

	// ��ɕ`�悷��UI�̃^�O
	const std::string TAG_ALWAYS = "Always";
	// �G���^�[�L�[���͑ҋ@��UI�̃^�O
	const std::string TAG_PUSH_ENTER = "PushEnter";
	// ���[�h�I��UI�̃^�O
	const std::string TAG_MODE_SELECT = "ModeSelect";
	// �_�ł̒����l
	const float FLASH_ADJUSTMENT = 0.5f;

//----------------------------------------------
// �ϐ�
//----------------------------------------------
private:

	// �v���C�V�[��
	TitleScene* m_titleScene;
	// �G���^�[�������Ă��������e�L�X�g
	OperatableUI* m_pushEnterText;

//----------------------------------------------
// �֐�
//----------------------------------------------
public:

	// �R���X�g���N�^
	TitleSceneUI(TitleScene* titleScene);
	// �f�X�g���N�^
	~TitleSceneUI();

	// ������
	void Initialize() override;
	// �X�V
	void Update() override;

	// �����ؑ֏�Ԃɐ؂�ւ�
	void ChangeStateSwitching();
	// ���[�h�I����Ԃɐ؂�ւ�
	void ChangeStateModeSelect();
};