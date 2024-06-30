/**
 *
 * @file IPlayerStrategy.h
 *
 * @brief �v���C���[�@�\�N���X�̃C���^�[�t�F�[�X
 *
 * @author Kato Yuki
 *
 * @date 2023/12/11
 *
 */
#pragma once

class IPlayerStrategy
{
//----------------------------------------------
// �֐�
//----------------------------------------------
public:

	// �f�X�g���N�^
	virtual ~IPlayerStrategy() = default;
	// �X�V
	virtual void Update() = 0;
	// �ړ�����
	virtual void Move() = 0;
	// �W�����v����
	virtual void Jump() = 0;
};
