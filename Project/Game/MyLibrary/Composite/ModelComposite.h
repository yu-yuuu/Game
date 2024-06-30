/**
 *
 * @file ModelComposite.h
 *
 * @brief ���f���̐e�q�\����\���N���X�̃w�b�_�[�t�@�C��
 *
 * @author Kato Yuki
 *
 * @date 2024/1/29
 *
 */
#pragma once

#include <vector>
#include <functional>
#include "Model.h"
#include "Effects.h"

class ModelComposite
{
//----------------------------------------------
// �ϐ�
//----------------------------------------------
private:

	// ���f��
	DirectX::Model* m_model;
	// �����ʒu�s��
	DirectX::SimpleMath::Matrix m_initial;
	// �ϊ��s��
	DirectX::SimpleMath::Matrix m_transform;
	// ���[���h�s��
	DirectX::SimpleMath::Matrix m_world;
	// �q
	std::vector<ModelComposite*> m_child;

//----------------------------------------------
// �֐�
//----------------------------------------------
public:

	// �R���X�g���N�^
	ModelComposite(DirectX::Model* model, DirectX::SimpleMath::Vector3 localPosition);
	// �f�X�g���N�^
	~ModelComposite();
	// �X�V
	void Update(const DirectX::SimpleMath::Matrix& worldMatrix);
	// �`��
	void Render(
		DirectX::SimpleMath::Matrix view,
		DirectX::SimpleMath::Matrix projection,
		std::function<void()> custom = nullptr);

	// ���f���ɓK��������G�t�F�N�g�X�V
	void UpdateEffects(std::function<void(DirectX::IEffect*)> setEffect);
	// �ϊ��s��ݒ�
	void SetTransformMatrix(const DirectX::SimpleMath::Matrix& transformMatrix);
	// �q�ݒ�
	void SetChild(ModelComposite* child);
};