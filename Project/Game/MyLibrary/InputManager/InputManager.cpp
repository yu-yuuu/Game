/**
 *
 * @file InputManager.cpp
 *
 * @brief �L�[���͂��Ǘ�����}�l�[�W���[�N���X�̃\�[�X�t�@�C��
 *
 * @author Kato Yuki
 *
 * @date 2023/11/21
 *
 */
#include "pch.h"
#include "InputManager.h"
#include <algorithm>

using namespace DirectX;

//------------------------------------------------------------------
/**
 * @brief �R���X�g���N�^
 *
 * @param keyTracker�F�L�[�{�[�h�X�e�[�g�g���b�J�[
 */
InputManager::InputManager(DirectX::Keyboard::KeyboardStateTracker* keyTracker)
	: m_keyTracker(keyTracker)
{
}

//------------------------------------------------------------------
/**
 * @brief �f�X�g���N�^
 */
InputManager::~InputManager()
{
	Clear();
}

//------------------------------------------------------------------
/**
 * @brief �X�V
 *
 * @param  �Ȃ�
 * @return �Ȃ�
 */
void InputManager::Update()
{
	// �L�[�{�[�h�擾
	Keyboard::State keyState = Keyboard::Get().GetState();

	// �L�[�{�[�h�������ꂽ���m�F
	if (IsPushKey(keyState))
	{
		// �o�^���ꂽ�L�[�����͂���Ă��邩�m�F
		CheckKey(keyState);
	}
}

//------------------------------------------------------------------
/**
 * @brief �L�[�̒ǉ� ( ��� )
 *
 * @param  keys�F�ǉ�����L�[
 * @return �Ȃ�
 */
void InputManager::AddKey(const DirectX::Keyboard::Keys& keys)
{
	// ���łɒǉ����Ă��邩�m�F
	if (m_keyList.count(keys) != 0) return;

	// �L�[��ǉ�
	m_keyList[keys] = PushState{};
}

//------------------------------------------------------------------
/**
 * @brief �L�[�̒ǉ� ( ���� )
 *
 * @param  list�F�ǉ�����L�[���X�g
 * @return �Ȃ�
 */
void InputManager::AddKey(const std::initializer_list<DirectX::Keyboard::Keys>& list)
{
	for (DirectX::Keyboard::Keys keys : list)
	{
		AddKey(keys);
	}
}

//------------------------------------------------------------------
/**
 * @brief �L�[�̍폜 ( ��� )
 *
 * @param  keys�F�폜����L�[
 * @return �Ȃ�
 */
void InputManager::DeleteKey(const DirectX::Keyboard::Keys& keys)
{
	// �G�C���A�X�錾
	using List = std::unordered_map<DirectX::Keyboard::Keys, PushState>;

	// �폜�Ώۂ̃L�[��T��
	List::iterator findKey = std::find_if(m_keyList.begin(), m_keyList.end(), 
		[&](const std::pair<DirectX::Keyboard::Keys, PushState>& pair)
		{
			return pair.first == keys;
		}
	);

	// ������Ȃ��Ȃ�I��
	assert(findKey != m_keyList.end() && "�폜�Ώۂ̃L�[���o�^����Ă��܂���");
	// �L�[�폜
	m_keyList.erase(findKey);
}

//------------------------------------------------------------------
/**
 * @brief �L�[�̍폜 ( ���� )
 *
 * @param  list�F�폜����L�[���X�g
 * @return �Ȃ�
 */
void InputManager::DeleteKey(const std::initializer_list<DirectX::Keyboard::Keys>& list)
{
	for (const DirectX::Keyboard::Keys& keys : list)
	{
		DeleteKey(keys);
	}
}

//------------------------------------------------------------------
/**
 * @brief �L�[�̉������ݏ�Ԃ̎擾
 *
 * @param  keys     �F�������ݏ�Ԃ��m�M�������L�[
 * @return PushState�F�L�[�̉������ݏ��
 */
InputManager::PushState InputManager::GetKey(const DirectX::Keyboard::Keys& keys)
{
	// �L�[���o�^����Ă��Ȃ���Ή�����Ă��Ȃ���Ԃ�Ԃ�
	if (m_keyList.count(keys) == 0) return PushState{ false, false, false };

	// �L�[�̉������ݏ�Ԃ�Ԃ�
	return m_keyList[keys];
}

//------------------------------------------------------------------
/**
 * @brief �L�[�̑S�폜
 *
 * @param �Ȃ�
 * @return �Ȃ�
 */
void InputManager::Clear()
{
	m_keyList.clear();
}

//------------------------------------------------------------------
/**
 * @brief �L�[�̓��͏�ԏ�����
 *
 * @param  �Ȃ�
 * @return �Ȃ�
 */
void InputManager::Reset()
{
	std::for_each(m_keyList.begin(), m_keyList.end(),
		[&](std::pair<const DirectX::Keyboard::Keys, PushState>& data)
		{
			// ���͏�Ԏ擾
			PushState& state = data.second;
			// ���͏�Ԃ����Z�b�g
			state.down = state.press = state.release = false;
		}
	);
}

//------------------------------------------------------------------
/**
 * @brief �L�[�{�[�h�ɓ��͂����ꂽ���m�F
 *
 * @param  keyState�F�L�[�{�[�h�X�e�[�g
 * @return �Ȃ�
 */
bool InputManager::IsPushKey(DirectX::Keyboard::State keyState)
{
	auto ptr = reinterpret_cast<uint32_t*>(&keyState);
	for (int key = 0; key < 0xff; key++)
	{
		const unsigned int bf = 1u << (key & 0x1f);
		if (ptr[(key >> 5)] && bf)
			// �L�[����������ꂽ
			return true;
	}

	// �L�[�������������Ă��Ȃ�
	return false;
}

//------------------------------------------------------------------
/**
 * @brief �L�[���X�g�̃L�[��������Ă��邩�m�F
 *
 * @param  keyState�F�L�[�̏��
 * @return �Ȃ�
 */
void InputManager::CheckKey(const DirectX::Keyboard::State& keyState)
{
	std::for_each(m_keyList.begin(), m_keyList.end(),
		[&](std::pair<const DirectX::Keyboard::Keys, PushState>& data)
		{
			// �L�[�擾
			DirectX::Keyboard::Keys keys = data.first;
			// ���͏�Ԏ擾
			PushState& state = data.second;
			// �L�[�����͂���Ă��邩����
			state.down    = keyState.IsKeyDown(keys);
			state.press   = m_keyTracker->IsKeyPressed(keys);
			state.release = m_keyTracker->IsKeyReleased(keys);
		}
	);
}