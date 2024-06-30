/**
 *
 * @file BlockType.h
 *
 * @brief �u���b�N�̎�ނ��`����w�b�_�[�t�@�C��
 *
 * @author Kato Yuki
 *
 * @date 2023/12/28
 *
 */
#pragma once

//----------------------------------------------
// ����̋��ʒ�`���������O���
//----------------------------------------------
namespace KT
{
	//----------------------------------------------
	//�@�u���b�N�̃^�C�v���������O���
	//----------------------------------------------
	namespace Block
	{
		// �u���b�N�̎��
		enum class Type
		{
			NONE,           // 0�F���ݒ�
			GRASS,          // 1�F��
			GHOST,          // 2�F�S�[�X�g
			GHOST_FLOOR,    // 3�F�S�[�X�g��
			BRICK,          // 4�F�����K
			START,          // 5�F�X�^�[�g�u���b�N
			GOAL,           // 6�F�S�[���u���b�N
			GAME_START,     // 7�F�����ԃ{�^���̔w�i
			GAME_START_A,   // 8�F�����ԃ{�^���̂�
			GAME_START_SO,  // 9�F�����ԃ{�^���̂�
			GAME_START_BU,  // 10�F�����ԃ{�^���̂�
			GAME_END,       // 11�F�����{�^���̔w�i
			GAME_END_O,     // 12�F�����{�^���̂�
			GAME_END_WA,    // 13�F�����{�^���̂�
			GAME_END_RU,    // 14�F�����{�^���̂�
		};

		// �u���b�N�̓����蔻�胂�[�h
		enum class CollisionMode
		{
			_2D,	// 2D�̂�
			_3D,	// 3D�̂�
			BOTH,	// ����
			NONE,   // ��������Ȃ�
		};
	}
}