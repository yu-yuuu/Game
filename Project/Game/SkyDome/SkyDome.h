/**
 *
 * @file SkyDome.h
 *
 * @brief �X�J�C�h�[����\���N���X�̃w�b�_�[�t�@�C��
 *
 * @author Kato Yuki
 *
 * @date 2024/4/7
 *
 */
#pragma once

#include "Model.h"

class SkyDome
{
//----------------------------------------------
// �ϐ�
//----------------------------------------------
private:

	// �X�J�C�h�[�����f��
	DirectX::Model* m_model;
	// �ʒu
	DirectX::SimpleMath::Vector3 m_position;
	// ��]
	DirectX::SimpleMath::Quaternion m_rotation;
	// ��]���x
	float m_rotationSpeed;

//----------------------------------------------
// �֐�
//----------------------------------------------
public:

	// �R���X�g���N�^
	SkyDome(DirectX::SimpleMath::Vector3 position);
	// �f�X�g���N�^
	~SkyDome();

	// �X�V
	void Update();
	// �`��
	void Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection);

	// �ʒu�̐ݒ�
	void SetPosition(const DirectX::SimpleMath::Vector3& position);
	// ��]���x�̐ݒ�
	void SetRotationSpeed(const float& rotationSpeed);
};