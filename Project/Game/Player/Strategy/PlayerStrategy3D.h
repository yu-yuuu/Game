/**
 *
 * @file PlayerStrategy3D.h
 *
 * @brief �v���C���[��3D�@�\�N���X�̃w�b�_�[�t�@�C��
 *
 * @author Kato Yuki
 *
 * @date 2023/12/11
 *
 */
#pragma once

#include "Game/Player/Strategy/IPlayerStrategy.h"

class Player;

class PlayerStrategy3D : public IPlayerStrategy
{
//----------------------------------------------
// �ϐ�
//----------------------------------------------
private:

	// �v���C���[
	Player* m_player;

//----------------------------------------------
// �֐�
//----------------------------------------------
public:

	// �R���X�g���N�^
	PlayerStrategy3D(Player* player);
	// �f�X�g���N�^
	~PlayerStrategy3D();
	// �X�V
	void Update() override;
	// �ړ�
	void Move() override;
	// �W�����v����
	void Jump() override;
};