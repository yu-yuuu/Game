/**
 *
 * @file MenuWindow.h
 *
 * @brief ��ʏ�ɕ\������E�B���h�E�̊��N���X�̃w�b�_�[�t�@�C��
 *
 * @author Kato Yuki
 *
 * @date 2024/2/5
 *
 */
#pragma once
#undef ChangeMenu

#include "Game/Window/Window.h"

class Texture;
class MenuWindowUI;
class SceneManager;

class MenuWindow : public Window
{
//----------------------------------------------
// �񋓑�
//----------------------------------------------
public:

	// �E�B���h�E���J�����V�[��
	enum class OpenScene
	{
		SELECT, // �Z���N�g�V�[��
		PLAY,   // �v���C�V�[��
		NONE    // �ݒ�Ȃ�
	};
	// ���݊J���Ă��郁�j���[
	enum class MenuType
	{
		HOME,   // �z�[��
		OPTION, // �ݒ�
	};
	// �z�[���őI�����Ă��郁�j���[
	enum class SelectHomeMenu
	{
		OPTION,       // �ݒ�
		RETURN_SCENE, // �����V�[���֖߂�
		COUNT,        // ���[�h�̐��i���I���A���ݒ�j
	};	
	// �z�[���őI�����Ă��郁�j���[
	enum class SelectOptionMenu
	{
		BGM,    // BGM
		SE,     // SE
		RETURN, // �߂�
		COUNT   // ���[�h�̐��i���I���A���ݒ�j
	};

//----------------------------------------------
// �萔
//----------------------------------------------
private:

	// ���ʒ����܂݂̑��x
	const float KNOB_SPEED = 0.025f;
	// ���ʂ̍ő�l
	const float MAX_VOLUME = 1.0f;

//----------------------------------------------
// �ϐ�
//----------------------------------------------
private:

	// �V�[���}�l�[�W���[
	SceneManager* m_sceneManager;

	// UI
	std::unique_ptr<MenuWindowUI> m_ui;
	// ���j���[�E�B���h���J�����V�[��
	OpenScene m_openScene;
	// ���݊J���Ă��郁�j���[���
	MenuType m_currentMenu;
	// �z�[����ʂőI�����Ă��郁�j���[
	SelectHomeMenu m_selectHomeMenu;
	// �ݒ��ʂőI�����Ă��郁�j���[
	SelectOptionMenu m_selectOptionMenu;

//----------------------------------------------
// �֐�
//----------------------------------------------
public:

	// �R���X�g���N�^
	MenuWindow(SceneManager* sceneManager, DirectX::SimpleMath::Vector2 windowSize, KT::Texture::TextureData texture, DirectX::SimpleMath::Vector2 position);
	// �f�X�g���N�^
	~MenuWindow();

	// ������
	void Initialize();
	// �X�V
	void Update();

	// �z�[����ʂ̍X�V����
	void UpdateHome();
	// �ݒ��ʂ̍X�V
	void UpdateOption();

	// �E�B���h�E�̕\���ؑ�
	void OpenClose(OpenScene openScene);
	// �E�B���h�E���J��
	void Open(OpenScene openScene);
	// �E�B���h�E�����
	void Close();

	// �z�[����ʂŌ��莞�̏���
	void OnEnterHome();
	// �ݒ��ʂŌ��莞�̏���
	void OnEnterOption();
	// ���̐ݒ�
	void SoundSetting();
	// ���ʒ���
	void AdjustmentVolume(float& speed, const std::string& type);
	// ���j���[��ʐ؂�ւ�
	void ChangeMenu(MenuType nextMenu);
};