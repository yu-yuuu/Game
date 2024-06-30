/**
 *
 * @file OperatableUI.h
 *
 * @brief ���삷��UI��\���N���X�̃w�b�_�[�t�@�C��
 *
 * @author Kato Yuki
 *
 * @date 2024/5/2
 *
 */
#pragma once

#include "Game/UI/UI.h"
#include "Game/MyLibrary/Texture/Texture.h"

class OperatableUI : public UI
{
//----------------------------------------------
// �\����
//----------------------------------------------
public:

	// UI�̏��
	struct UIState
	{
		// �L���A�������̊g�嗦
		DirectX::SimpleMath::Vector2 enableScale;
		DirectX::SimpleMath::Vector2 disableScale;
		// �L���A�������̐F����
		DirectX::SimpleMath::Color enableColor;
		DirectX::SimpleMath::Color disableColor;
	};

	// ��Ԃ̎��
	enum class UIStateType
	{
		SELECT, // �I�����
		ACTIVE, // �L�����
		PUSH,   // ���͏��
	};

//----------------------------------------------
// �萔
//----------------------------------------------
private:

	// �L���A�������̊g�嗦
	const DirectX::SimpleMath::Vector2 NORMAL_SCALE  = DirectX::SimpleMath::Vector2::One;
	const DirectX::SimpleMath::Vector2 DISABLE_SCALE = DirectX::SimpleMath::Vector2(0.9f, 0.9f);
	// �L���A�����A���͎��̐F����
	const DirectX::SimpleMath::Color WHITE = DirectX::SimpleMath::Color(1.0f, 1.0f, 1.0f, 1.0f);
	const DirectX::SimpleMath::Color GRAY  = DirectX::SimpleMath::Color(0.5f, 0.5f, 0.5f, 1.0f);
	const DirectX::SimpleMath::Color RED   = DirectX::SimpleMath::Color(1.0f, 0.0f, 0.0f, 1.0f);

//----------------------------------------------
// �ϐ�
//----------------------------------------------
private:
	
	// �I�����
	UIState m_selectState;
	// �L�����
	UIState m_activeState;
	// ���͏��
	UIState m_pushState;

	// �L����Ԃ�
	bool m_isActive;
	// �Ή�������L�[
	DirectX::Keyboard::Keys m_key;

//----------------------------------------------
// �֐�
//----------------------------------------------
public:

	// �R���X�g���N�^
	OperatableUI(
		const std::vector<std::string>& tagList,
		std::unique_ptr<Texture> texture,
		const DirectX::SimpleMath::Vector2& position,
		DirectX::Keyboard::Keys key = DirectX::Keyboard::Keys::None,
		bool reverseX = false,
		bool reverseY = false
	);	
	// �f�X�g���N�^
	~OperatableUI();

	// ��Ԃ̐ݒ�
	void SetState(UIStateType type, const UIState& uiState);

	// �I����Ԃ̍X�V
	void SelectStateUpdate(bool isSelect);
	// �L����Ԃ̍X�V
	void ActiveStateUpdate(bool isActive);
	// ���͏�Ԃ̍X�V
	void PushStateUpdate();

	// �L�[�̎擾
	DirectX::Keyboard::Keys GetKey() const;

private:

	// ��Ԃ̍X�V
	void StateUpdate(bool flag, const UIState& uiState);
};