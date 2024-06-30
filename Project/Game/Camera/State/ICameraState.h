/**
 *
 * @file ICameraState.h
 *
 * @brief ��ԃJ�����̃C���^�[�t�F�[�X�N���X
 *
 * @author Kato Yuki
 *
 * @date 2024/2/11
 *
 */
#pragma once

class ICameraState
{
//----------------------------------------------
// �֐�
//----------------------------------------------
public:

	// �f�X�g���N�^
	virtual ~ICameraState() = default;
	// ������
	virtual void Initialize() = 0;
	// �X�V
	virtual void Update() = 0;
	// ���쒆�t���O
	virtual bool IsOperation() = 0;
};