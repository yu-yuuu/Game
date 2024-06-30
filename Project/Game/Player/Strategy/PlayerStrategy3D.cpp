/**
 *
 * @file PlayerStrategy3D.cpp
 *
 * @brief �v���C���[��3D�@�\�N���X�̃\�[�X�t�@�C��
 *
 * @author Kato Yuki
 *
 * @date 2023/12/11
 *
 */
#include "pch.h"
#include "PlayerStrategy3D.h"

#include "Game/MyLibrary/CommonResource/GameResource.h"
#include "Game/MyLibrary/GameParameter/GameParameter.h"
#include "Game/Player/Player.h"

using namespace DirectX;

//------------------------------------------------------------------
/**
 * @brief �R���X�g���N�^
 *
 * @param player�F�v���C���[�ւ̃|�C���^
 */
PlayerStrategy3D::PlayerStrategy3D(Player* player)
	: m_player(player)
{
}

//------------------------------------------------------------------
/**
 * @brief �f�X�g���N�^
 */
PlayerStrategy3D::~PlayerStrategy3D()
{
}

//------------------------------------------------------------------
/**
 * @brief �X�V
 *
 * @param  �Ȃ�
 * @return �Ȃ�
 */
void PlayerStrategy3D::Update()
{
	// �ړ�����
	Move();
	// �W�����v����
	Jump();
}

//------------------------------------------------------------------
/**
 * @brief �ړ�����
 *
 * @param  �Ȃ�
 * @return �Ȃ�
 */
void PlayerStrategy3D::Move()
{
	// �L�[�}�l�[�W���[�擾
	InputManager* inputManager = GameResource::GetInstance()->GetInputManager();

	// ���̓t���O�擾�p
	int moveInput = 0;

	// ��
	if (inputManager->GetKey(Keyboard::Keys::Up).down)
	{
		moveInput |= KT::GameParam::InputDirection::FORWARD;
	}
	// ��O
	else if (inputManager->GetKey(Keyboard::Keys::Down).down)
	{
		moveInput |= KT::GameParam::InputDirection::BACK;
	}

	// �E
	if (inputManager->GetKey(Keyboard::Keys::Right).down)
	{
		moveInput |= KT::GameParam::InputDirection::RIGHT;
	}
	// ��
	else if (inputManager->GetKey(Keyboard::Keys::Left).down)
	{
		moveInput |= KT::GameParam::InputDirection::LEFT;
	}

	// �ړ��t���O�ݒ�
	m_player->SetMoveInputFlag(moveInput);
}

//------------------------------------------------------------------
/**
 * @brief �W�����v����
 *
 * @param  �Ȃ�
 * @return �Ȃ�
 */
void PlayerStrategy3D::Jump()
{
	// �L�[�}�l�[�W���[�擾
	InputManager* inputManager = GameResource::GetInstance()->GetInputManager();

	// �X�y�[�X�������ꂽ��W�����v
	if (inputManager->GetKey(Keyboard::Keys::Space).press)
	{
		m_player->Jump();
	}
}