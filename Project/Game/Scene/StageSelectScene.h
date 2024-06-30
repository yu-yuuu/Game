/**
 *
 * @file StageSelectScene.h
 *
 * @brief �X�e�[�W�I���V�[����\���N���X�̃w�b�_�[�t�@�C��
 *
 * @author Kato Yuki
 *
 * @date 2023/11/8
 *
 */
#pragma once

#include <vector>
#include "Model.h"
#include "Game/Scene/IScene.h"
#include "Game/Scene/SceneManager.h"

class StageSelectCamera;
class SelectStage;
class StageSelectSceneUI;
class SkyDome;

class StageSelectScene : public IScene
{
//----------------------------------------------
// �萔
//----------------------------------------------
public:

	// �J�����̉�]���x
	const float CAMERA_ROTATION_SPEED = 0.01f;

//----------------------------------------------
// �񋓑�
//----------------------------------------------
private:

	// �V�[���̏��
	enum class SceneState
	{
		SELECT, // �X�e�[�W�I�����
		MENU,   // ���j���[���
	};


//----------------------------------------------
// �ϐ�
//----------------------------------------------
private:

	// �V�[���}�l�[�W���[
	SceneManager* m_sceneManager;

	// �X�e�[�W
	std::unique_ptr<SelectStage> m_stage;
	// �J����
	std::unique_ptr<StageSelectCamera> m_camera;
	// UI
	std::unique_ptr<StageSelectSceneUI> m_ui;
	// �X�J�C�h�[��
	std::unique_ptr<SkyDome> m_skyDome;

	// �V�[���̏��
	SceneState m_sceneState;
	// �X�e�[�W�̔ԍ����X�g
	std::vector<int> m_stageNumberList;	
	// �I�����Ă���X�e�[�W�̗v�f�ԍ�
	int m_stageNumberIndex;
	// �X�e�[�W�̐ؑփA�j���[�V�������I�������
	bool m_isSwitchFinished;

//----------------------------------------------
// �֐�
//----------------------------------------------
public:

	// �R���X�g���N�^
	StageSelectScene(SceneManager* sceneManager);
	// �f�X�g���N�^
	~StageSelectScene();
	// ������
	void Initialize() override;
	// �X�V
	void Update() override;
	// �`��
	void Render() override;
	// �㏈��
	void Finalize() override;
	// �V�[���؂�ւ�
	void ChangeScene() override;

	// �X�e�[�W�I�����̍X�V����
	void SelectUpdate();
	// ���j���[�\�����̍X�V����
	void MenuUpdate();
	// �X�e�[�W�I��
	void StageSelect();

	// ���ݑI�����Ă���X�e�[�W�̗v�f�ԍ��擾
	int GetSelectIndex();
	// �X�e�[�W�̐�
	int GetStageNum();

	// �X�e�[�W�ؑ֊���������
	void StageSwitchComplete();

};