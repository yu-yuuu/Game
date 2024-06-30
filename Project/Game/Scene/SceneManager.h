/**
 *
 * @file SceneManager.h
 *
 * @brief �V�[���Ǘ��N���X�̃w�b�_�[�t�@�C��
 *
 * @author Kato Yuki
 *
 * @date 2023/11/8
 *
 */
#pragma once

class IScene;
class Fade;
class SceneShareData;

class SceneManager
{
//----------------------------------------------
// �ϐ�
//----------------------------------------------
private:
	
	// ���݂̃V�[��
	std::unique_ptr<IScene> m_currentScene;
	// �؂�ւ���̃V�[��
	std::unique_ptr<IScene> m_nextScene;
	// �t�F�[�h
	Fade* m_fade;
	// �e�V�[���ŋ��L����f�[�^
	std::unique_ptr<SceneShareData> m_sceneShareData;

//----------------------------------------------
// �֐�
//----------------------------------------------
public:

	// �R���X�g���N�^
	SceneManager();
	// �f�X�g���N�^
	~SceneManager();
	// ������
	void Initialize();
	// �X�V
	void Update();
	// �`��
	void Render();
	// �㏈��
	void Finalize();

	// �V�[���̐ؑ�
	bool ChangeScene();
	// ���̃V�[���̐ݒ�
	template<typename T>
	void SetNextScene();
	// ���݃V�[���̍폜
	void DeleteCurrentScene();
	// �V�[����؂�ւ��Ă悢��
	bool IsChangeScene();
	
	// �V�[�����L�f�[�^�̎擾
	SceneShareData* GetSceneShareData() const;
};

//----------------------------------------------
// �e���v���[�g�֐���`
//----------------------------------------------

//------------------------------------------------------------------
/**
 * @brief ���̃V�[���̐ݒ�
 *
 * @tparam T�F���̃V�[���̃N���X
 * @return �Ȃ�
 */
template<typename T>
inline void SceneManager::SetNextScene()
{
	m_nextScene.reset(new T(this));
}