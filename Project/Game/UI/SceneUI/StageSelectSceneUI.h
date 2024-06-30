/**
 *
 * @file StageSelectSceneUI.h
 *
 * @brief �X�e�[�W�Z���N�g�V�[���Ŏg�p����UI�A�摜�N���X�̃w�b�_�[�t�@�C��
 *
 * @author Kato Yuki
 *
 * @date 2024/1/22
 *
 */
#pragma once

#include <string>
#include "Game/UI/SceneUI/SceneUI.h"

class StageSelectScene;
class OperatableUI;

class StageSelectSceneUI : public SceneUI
{
//----------------------------------------------
// �萔
//----------------------------------------------
private:

	// ��ɕ`�悷��UI�̃^�O
	const std::string TAG_ALWAYS     = "Always";
	// �X�e�[�W�ؑ֕\�����UI�̃^�O
	const std::string TAG_ARROW_UP   = "StageSelectArrowUp";
	const std::string TAG_ARROW_DOWN = "StageSelectArrowDown";
	// �X�e�[�W�ؑ֕\�����̈ړ����x
	const float STAGE_SELECT_ARROW_MOVE_SPEED = 2.0f;
	// �X�e�[�W�ؑ֕\�����̈ړ���
	const float STAGE_SELECT_ARROW_MOVE_WIDTH = 0.25f;

//----------------------------------------------
// �ϐ�
//----------------------------------------------
private:

	// �v���C�V�[��
	StageSelectScene* m_stageSelectScene;
	// �I��\���p�̖��
	OperatableUI* m_selectArrowUp;
	OperatableUI* m_selectArrowDown;

//----------------------------------------------
// �֐�
//----------------------------------------------
public:

	// �R���X�g���N�^
	StageSelectSceneUI(StageSelectScene* stageSelectScene);
	// �f�X�g���N�^
	~StageSelectSceneUI();

	// ������
	void Initialize() override;
	// �X�V
	void Update() override;

	// ���̕`��ݒ�
	void SelectTriangleRenderSetting(bool isStart, bool isEnd);
};