/**
 *
 * @file IScene.h
 *
 * @brief �V�[����\���C���^�[�t�F�[�X�N���X
 *
 * @author Kato Yuki
 *
 * @date 2023/11/8
 *
 */
#pragma once

class IScene
{
//----------------------------------------------
// �֐�
//----------------------------------------------
public:

	// �f�X�g���N�^
	virtual ~IScene() = default;
	// ������
	virtual void Initialize() = 0;
	// �X�V
	virtual void Update() = 0;
	// �`��
	virtual void Render() = 0;
	// �㏈��
	virtual void Finalize() = 0;
	// �V�[���̐؂�ւ�
	virtual void ChangeScene() = 0;
};