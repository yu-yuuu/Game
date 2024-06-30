/**
 *
 * @file IBlock.h
 *
 * @brief �u���b�N�Ɏg�p����C���^�[�t�F�[�X�N���X
 *
 * @author Kato Yuki
 *
 * @date Kato Yuki
 *
 * @note �⑫�����A����
 *
 */
#pragma once

#include "Game/Block/BlockType.h"

class IBlock
{
//----------------------------------------------
// �֐�
//----------------------------------------------
public:

	// �f�X�g���N�^
	virtual ~IBlock() = default;
	// �u���b�N��ނ̎擾
	virtual KT::Block::Type GetType() = 0;
	// �u���b�N��ނ̐ݒ�
	virtual void SetType(KT::Block::Type type) = 0;
};
