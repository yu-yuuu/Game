/**
 *
 * @file TitleScene.h
 *
 * @brief �^�C�g���V�[����\���N���X�̃w�b�_�[�t�@�C��
 *
 * @author Kato Yuki
 *
 * @date 2023/11/8
 *
 */
#pragma once

#include "Model.h"
#include "Game/Scene/IScene.h"
#include "Game/Scene/SceneManager.h"

class TitleCamera;
class TitleStage;
class TitleSceneUI;
class SkyDome;

class TitleScene : public IScene
{
//----------------------------------------------
// �񋓑�
//----------------------------------------------
public:

	// �^�C�g���V�[���̏��
	enum class TitleState
	{
		PUSH_ENTER,  // �G���^�[�������Ă�������
		SWITCHING,   // �ؑ֒�
		MODE_SELECT, // ���[�h�I��
	};

	// �J�ڐ惂�[�h
	enum class NextMode
	{
		PLAY = 0,  // �Q�[���J�n
		EXIT,      // �Q�[���I��

		COUNT,     // ���[�h�̐�
	};

//----------------------------------------------
// �ϐ�
//----------------------------------------------
private:

	// �V�[���}�l�[�W���[
	SceneManager* m_sceneManager;

	// �X�e�[�W
	std::unique_ptr<TitleStage> m_stage;
	// �J����
	std::unique_ptr<TitleCamera> m_camera;
	// UI
	std::unique_ptr<TitleSceneUI> m_ui;
	// �X�J�C�h�[��
	std::unique_ptr<SkyDome> m_skyDome;

	// �^�C�g���V�[���̏��
	TitleState m_titleState;
	// �I�����Ă��郂�[�h
	NextMode m_nextMode;

//----------------------------------------------
// �֐�
//----------------------------------------------
public:

	// �R���X�g���N�^
	TitleScene(SceneManager* sceneManager);
	// �f�X�g���N�^
	~TitleScene();
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

	// �^�C�g���V�[���̏�Ԑ؂�ւ�
	void ChangeState();
	// �^�C�g���V�[���̏�Ԏ擾
	TitleState GetTitleState() const;
	// �J�ڐ�̃��[�h�擾
	NextMode GetMode() const;
};