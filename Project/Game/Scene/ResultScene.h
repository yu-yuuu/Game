/**
 *
 * @file ResultScene.h
 *
 * @brief ���U���g�V�[����\���N���X�̃w�b�_�[�t�@�C��
 *
 * @author Kato Yuki
 *
 * @date 2023/11/8
 *
 */
#pragma once
#include "Game/Scene/IScene.h"
#include "Game/Scene/SceneManager.h"

class Camera;
class SkyDome;
class Stage;
class Player;
class Block;
class ResultSceneUI;

class ResultScene : public IScene
{
//----------------------------------------------
// �񋓑�
//----------------------------------------------
public:

	// �J�ڐ惂�[�h
	enum class NextMode
	{
		NEXT = 0,     // ���̃X�e�[�W��
		STAGE_SELECT, // �X�e�[�W�I��

		COUNT,        // ���[�h�̐�
	};


//----------------------------------------------
// �萔
//----------------------------------------------
private:

	// �J�����̒����_�ʒu
	const DirectX::SimpleMath::Vector3 CAMERA_TARGET_POSITION = DirectX::SimpleMath::Vector3(2.5f, 1.5f, 0.5f);
	// �J�����ʒu
	const DirectX::SimpleMath::Vector3 CAMERA_EYE_POSITION = DirectX::SimpleMath::Vector3(0.0f, -1.0f, 3.0f);
	// �S�[���u���b�N�̈ʒu
	const DirectX::SimpleMath::Vector3 GOAL_BLOCK_POSITION = DirectX::SimpleMath::Vector3(5.0f, 0.0f, 0.0f);
	// �v���C���[�̈ʒu
	const DirectX::SimpleMath::Vector3 PLAYER_POSITION = DirectX::SimpleMath::Vector3(0.0f, -0.5f, 0.0f);
	// �X�J�C�h�[���̉�]���x
	const float SKY_DOME_ROTATION_SPEED = 0.005f;

//----------------------------------------------
// �ϐ�
//----------------------------------------------
private:

	// �V�[���}�l�[�W���[
	SceneManager* m_sceneManager;

	// �J����
	std::unique_ptr<Camera> m_camera;
	// �S�[���u���b�N
	std::unique_ptr<Block> m_block;
	// �X�J�C�h�[��
	std::unique_ptr<SkyDome> m_skyDome;
	// �v���C���[
	std::unique_ptr<Player> m_player;
	// UI
	std::unique_ptr<ResultSceneUI> m_ui;

	// �J�ڐ惂�[�h
	NextMode m_nextMode;
	// �X�e�[�W��
	int m_stageNum;
	// ���݂̃X�e�[�W�ԍ�
	int m_currentStageNumber;

//----------------------------------------------
// �֐�
//----------------------------------------------
public:

	// �R���X�g���N�^
	ResultScene(SceneManager* sceneManager);
	// �f�X�g���N�^
	~ResultScene();
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

	// �Ō�̃X�e�[�W���ǂ���
	bool IsEndStageNumber();
	// ���ݑI�����Ă���J�ڐ惂�[�h�擾
	NextMode GetNextMode() const;
};