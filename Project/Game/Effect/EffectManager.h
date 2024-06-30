/**
 *
 * @file Particle.h
 *
 * @brief �p�[�e�B�N���G�t�F�N�g�N���X�̃w�b�_�[�t�@�C��
 *
 * @author Kato Yuki
 *
 * @date 2024/1/25
 *
 */
#pragma once
#include <vector>
#include "VertexTypes.h"
#include "Game/Effect/IEffect.h"

template<typename Vertex>
class Shader;

class EffectManager
{
//----------------------------------------------
// �\����
//----------------------------------------------
public:

	// �G�t�F�N�g�Ɏg�p����萔�o�b�t�@
	struct EffectConstantBuffer
	{
		DirectX::SimpleMath::Matrix world;
		DirectX::SimpleMath::Matrix view;
		DirectX::SimpleMath::Matrix projection;
	};

//----------------------------------------------
// �ϐ�
//----------------------------------------------
private:

	// �G�t�F�N�g���X�g
	std::vector<KT::IEffect*> m_list;
	// �V�F�[�_�[
	std::unique_ptr<Shader<DirectX::VertexPositionColorTexture>> m_shader;

//----------------------------------------------
// �֐�
//----------------------------------------------
public:

	// �R���X�g���N�^
	EffectManager();
	// �f�X�g���N�^
	~EffectManager();

	// ������
	void Initialize();
	// �X�V
	void Update();
	// �`��
	void Render(
		const DirectX::SimpleMath::Matrix& view,
		const DirectX::SimpleMath::Matrix& projection,
		const DirectX::SimpleMath::Vector3 eye,
		const DirectX::SimpleMath::Vector3 target,
		const DirectX::SimpleMath::Vector3 up);

	// �V�F�[�_�[�̎擾
	Shader<DirectX::VertexPositionColorTexture>* GetShader() const;
	// �G�t�F�N�g�̒ǉ�
	void AddEffect(KT::IEffect* effect);
	// �G�t�F�N�g�̍폜
	void DeleteEffect(KT::IEffect* effect);
	// �G�t�F�N�g�S�폜
	void Clear();
};