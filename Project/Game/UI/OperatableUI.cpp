/**
 *
 * @file OperatableUI.cpp
 *
 * @brief ���삷��UI��\���N���X�̃\�[�X�t�@�C��
 *
 * @author Kato Yuki
 *
 * @date 2024/5/2
 *
 */
#include "pch.h"
#include "OperatableUI.h"
#include "Game/MyLibrary/CommonResource/GameResource.h"

//------------------------------------------------------------------
/**
 * @brief �R���X�g���N�^
 *
 * @param  tagList �F�^�O���X�g
 * @param  texture �F�g�p����e�N�X�`���f�[�^
 * @param  position�F�`��ʒu�i�X�N���[���j
 * @param  key     �F�Ή�������L�[
 * @param  reverseX�F�e�N�X�`�������ɔ��]�����邩
 * @param  reverseY�F�e�N�X�`�����c�ɔ��]�����邩
 */
OperatableUI::OperatableUI(
	const std::vector<std::string>& tagList,
	std::unique_ptr<Texture> texture,
	const DirectX::SimpleMath::Vector2& position, 
	DirectX::Keyboard::Keys key,
	bool reverseX,
	bool reverseY
)
	: UI(tagList, std::move(texture), position, reverseX, reverseY)
	, m_key(key)
	, m_isActive(true)
{
	// �e��Ԃ̏����ݒ�
	m_selectState = { NORMAL_SCALE , NORMAL_SCALE, RED, WHITE };
	m_activeState = { NORMAL_SCALE , DISABLE_SCALE, WHITE, GRAY };
	m_pushState   = { NORMAL_SCALE , NORMAL_SCALE, RED, WHITE };
}

//------------------------------------------------------------------
/**
 * @brief �f�X�g���N�^
 */
OperatableUI::~OperatableUI()
{
}

//------------------------------------------------------------------
/**
 * @brief ��Ԃ̐ݒ�
 *
 * @param  type   �F�ݒ肷���ԃ^�C�v
 * @param  uiState�F�ݒ肷����
 * @return �Ȃ�
 */
void OperatableUI::SetState(UIStateType type, const UIState& uiState)
{
	switch (type)
	{
	// �I�����
	case OperatableUI::UIStateType::SELECT:
		m_selectState = uiState;
		break;
	// �L�����
	case OperatableUI::UIStateType::ACTIVE:
		m_activeState = uiState;
		break;
	// ���͏��
	case OperatableUI::UIStateType::PUSH:
		m_pushState = uiState;
		break;
	// ��O
	default:
		assert(false && "OperatableUI�̏�Ԃ������ł�");
		break;
	}
}

//------------------------------------------------------------------
/**
 * @brief �I����Ԃ̍X�V
 *
 * @param  isSelect�F�I������Ă��邩
 * @return �Ȃ�
 */
void OperatableUI::SelectStateUpdate(bool isSelect)
{
	// �L����ԂłȂ���Ώ������s��Ȃ�
	if (!m_isActive) return;

	// ��ԍX�V
	StateUpdate(isSelect, m_selectState);
}

//------------------------------------------------------------------
/**
 * @brief �L����Ԃ̍X�V
 *
 * @param  isActive�F�I������Ă��邩
 * @return �Ȃ�
 */
void OperatableUI::ActiveStateUpdate(bool isActive)
{
	// �t���O�ݒ�
	m_isActive = isActive;
	// ��ԍX�V
	StateUpdate(isActive, m_activeState);
}

//------------------------------------------------------------------
/**
 * @brief ���͏�Ԃ̍X�V
 *
 * @param  �Ȃ�
 * @return �Ȃ�
 */
void OperatableUI::PushStateUpdate()
{
	// �L����ԂłȂ���Ώ������s��Ȃ�
	if (!m_isActive) return;

	// ���̓}�l�[�W���[�擾
	InputManager* inputManager = GameResource::GetInstance()->GetInputManager();
	// ��ԍX�V
	StateUpdate(inputManager->GetKey(m_key).down, m_pushState);
}

//------------------------------------------------------------------
/**
 * @brief �L�[�̎擾
 *
 * @param  �Ȃ�
 * @return Keys�F�o�^���Ă���L�[
 */
DirectX::Keyboard::Keys OperatableUI::GetKey() const
{
	return m_key;
}

//------------------------------------------------------------------
/**
 * @brief ��Ԃ̍X�V
 *
 * @param  flag   �F��ԍX�V�t���O
 * @param  uiState�F�ݒ肷����
 * @return �Ȃ�
 */
void OperatableUI::StateUpdate(bool flag, const UIState& uiState)
{
	// ��ԍX�V
	Texture* texture = GetTexture();
	if (flag)
	{
		texture->SetScale(uiState.enableScale);
		texture->SetColor(uiState.enableColor);
	}
	else
	{
		texture->SetScale(uiState.disableScale);
		texture->SetColor(uiState.disableColor);
	}
}