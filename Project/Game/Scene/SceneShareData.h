/**
 *
 * @file SceneShareData.h
 *
 * @brief �e�V�[���ŋ��L����f�[�^�̃w�b�_�[�t�@�C��
 *
 * @author Kato Yuki
 *
 * @date 2024/1/21
 *
 */
#pragma once

class SceneManager;
class MenuWindow;

class SceneShareData
{
//----------------------------------------------
// �萔
//----------------------------------------------
private:



//----------------------------------------------
// �ϐ�
//----------------------------------------------
private:

	// �V�[���}�l�[�W���[
	SceneManager* m_sceneManager;
	// ���j���[�E�B���h�E
	std::unique_ptr<MenuWindow> m_menuWindow;
	// �I�������X�e�[�W�ԍ�
	int m_selectStageNumber;

//----------------------------------------------
// �֐�
//----------------------------------------------
public:

	// �R���X�g���N�^
	SceneShareData(SceneManager* sceneManager);
	// �f�X�g���N�^
	~SceneShareData();

	// ���j���[�E�B���h�E�擾
	MenuWindow* GetMenuWindow();
	// �I�������X�e�[�W�ԍ��̐ݒ�
	void SetSelectStageNumber(const int& selectStageNumber);
	// �I�������X�e�[�W�ԍ��̎擾
	const int& GetSelectStageNumber() const;
};