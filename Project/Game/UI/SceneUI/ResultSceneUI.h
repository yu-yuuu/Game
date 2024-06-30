/**
 *
 * @file ResultSceneUI.h
 *
 * @brief ���U���g�V�[����UI���܂Ƃ߂�N���X�̃w�b�_�[�t�@�C��
 *
 * @author Kato Yuki
 *
 * @date 2024/3/13
 *
 */
#pragma once

#include <string>
#include "Game/UI/SceneUI/SceneUI.h"

class ResultScene;
class OperatableUI;

class ResultSceneUI : public SceneUI
{
//----------------------------------------------
// �萔
//----------------------------------------------
private:

	// ��ɕ`�悷��UI�̃^�O
	const std::string TAG_ALWAYS = "Always";

//----------------------------------------------
// �ϐ�
//----------------------------------------------
private:

	// ���U���g�V�[��
	ResultScene* m_resultScene;
	// �I������UI
	std::vector<OperatableUI*> m_selectUI;

//----------------------------------------------
// �֐�
//----------------------------------------------
public:

	// �R���X�g���N�^
	ResultSceneUI(ResultScene* resultScene);
	// �f�X�g���N�^
	~ResultSceneUI();
	// ������
	void Initialize() override;
	// �I��
	void Select(const int& type);
};