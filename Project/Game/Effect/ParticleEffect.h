/**
 *
 * @file ParticleEffect.h
 *
 * @brief �p�[�e�B�N���G�t�F�N�g��\���N���X�̃w�b�_�[�t�@�C��
 *
 * @author Kato Yuki
 *
 * @date 2024/1/31
 *
 */
#pragma once

#include <string>
#include <vector>
#include <functional>
#include "VertexTypes.h"
#include "Game/Effect/IEffect.h"

class EffectManager;
class Particle;

class ParticleEffect : public KT::IEffect
{
//----------------------------------------------
// �G�C���A�X�錾
//----------------------------------------------
private:

	// �p�[�e�B�N�����X�g
	using ParticleList = std::vector<std::unique_ptr<Particle>>;

//----------------------------------------------
// �ϐ�
//----------------------------------------------
private:

	// �G�t�F�N�g�}�l�[�W���[
	EffectManager* m_effectManager;
	// �p�[�e�B�N���̒��S�ʒu
	DirectX::SimpleMath::Vector3 m_position;
	// �g�p����e�N�X�`���̖��O
	std::string m_textureName;
	// �p�[�e�B�N�����X�g
	ParticleList m_particleList;
	// �`�撸�_���X�g
	std::vector<DirectX::VertexPositionColorTexture> m_vertices;
	// �p�[�e�B�N�������Ԋu
	float m_generateInterval;
	// �p�[�e�B�N�������^�C�}�[
	float m_generateTimer;
	// �p�[�e�B�N�������֐�
	std::function<std::unique_ptr<Particle>()> m_generateFunction;

//----------------------------------------------
// �֐�
//----------------------------------------------
public:

	// �R���X�g���N�^
	ParticleEffect(
		EffectManager* effectManager, 
		DirectX::SimpleMath::Vector3 position, 
		std::string textureName, 
		float generateInterval = 0.0f
	);
	// �f�X�g���N�^
	virtual ~ParticleEffect();

	// �X�V
	virtual void Update() override;
	// �`��
	virtual void Render(
		DirectX::SimpleMath::Matrix view,
		DirectX::SimpleMath::Matrix projection,
		DirectX::SimpleMath::Vector3 eye,
		DirectX::SimpleMath::Vector3 target,
		DirectX::SimpleMath::Vector3 up
	) override;

	// �r���{�[�h�s��쐬
	DirectX::SimpleMath::Matrix CreateBillboard(
		DirectX::SimpleMath::Vector3 eye,
		DirectX::SimpleMath::Vector3 up
	);
	// �����Ԋu�ݒ�
	void SetGenerateInterval(const float& generateInterval);
	// �p�[�e�B�N�������֐��ݒ�
	void SetGenerateFunction(const std::function<std::unique_ptr<Particle>()>& function);
	// �ʒu�擾
	DirectX::SimpleMath::Vector3 GetPosition() const;
};