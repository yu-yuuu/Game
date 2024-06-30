/**
 *
 * @file TitleStage.h
 *
 * @brief �^�C�g���V�[���X�e�[�W��\���N���X�̃w�b�_�|�t�@�C��
 *
 * @author Kato Yuki
 *
 * @date 2024/1/21
 *
 */
#pragma once

#include "Game/Stage/Stage.h"
#include "Game/Stage/StageData.h"

class TitleScene;

class TitleStage : public Stage
{
//----------------------------------------------
// �萔
//----------------------------------------------
private:

	// �_�ő��x
	const float FLASH_SPEED = 2.0f;
	// �I���{�^���̖��邳�̍ő�A�ŏ��l
	const float SELECT_BUTTON_BRIGHTNESS_MIN = 0.125f;
	const float SELECT_BUTTON_BRIGHTNESS_MAX = 0.875f;

//----------------------------------------------
// �ϐ�
//----------------------------------------------
private:

	// �^�C�g���V�[��
	TitleScene* m_titleScene;

//----------------------------------------------
// �֐�
//----------------------------------------------
public:

	// �R���X�g���N�^
	TitleStage(TitleScene* titleScene, int stageNumber, KT::Stage::Size size);
	// �f�X�g���N�^
	~TitleStage();
	// ������
	void Initialize();
	// �X�V
	void Update();
};