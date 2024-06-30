/**
 *
 * @file InputManager.h
 *
 * @brief �L�[���͂��Ǘ�����}�l�[�W���[�N���X�̃w�b�_�[�t�@�C��
 *
 * @author Kato Yuki
 *
 * @date 2023/11/21
 *
 */
#pragma once
#include <unordered_map>
#include <initializer_list>

class InputManager
{
//----------------------------------------------
// �\����
//----------------------------------------------
public:
	
	// �L�[�̉����������
	struct PushState
	{
		bool down;    // ������
		bool press;   // �������u��
		bool release; // �����Ă���
	};

//----------------------------------------------
// �ϐ�
//----------------------------------------------
private:

	// �L�[�{�[�h�X�e�[�g�g���b�J�[
	DirectX::Keyboard::KeyboardStateTracker* m_keyTracker;
	// �L�[���X�g
	std::unordered_map<DirectX::Keyboard::Keys, PushState> m_keyList;

//----------------------------------------------
// �֐�
//----------------------------------------------
public:

	// �R���X�g���N�^
	InputManager(DirectX::Keyboard::KeyboardStateTracker* keyTracker);
	// �f�X�g���N�^
	~InputManager();
	// �X�V
	void Update();
	// �L�[�̒ǉ� ( ��� )
	void AddKey(const DirectX::Keyboard::Keys& keys);
	// �L�[�̒ǉ� ( ���� )
	void AddKey(const std::initializer_list<DirectX::Keyboard::Keys>& list);
	// �L�[�̍폜 ( ��� )
	void DeleteKey(const DirectX::Keyboard::Keys& keys);
	// �L�[�̍폜 ( ���� )
	void DeleteKey(const std::initializer_list<DirectX::Keyboard::Keys>& list);

	// �L�[�̉������ݏ�Ԃ̎擾
	PushState GetKey(const DirectX::Keyboard::Keys& keys);
	// �L�[�̑S�폜
	void Clear();
	// �L�[�̓��͏�ԏ�����
	void Reset();

private:

	// �L�[�{�[�h�ɓ��͂����ꂽ���m�F
	bool IsPushKey(DirectX::Keyboard::State keyState);
	// �L�[���X�g�̃L�[��������Ă��邩�m�F
	void CheckKey(const DirectX::Keyboard::State& keyState);
};

