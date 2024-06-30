/**
 *
 * @file GoalEffect.h
 *
 * @brief �S�[���G�t�F�N�g��\���N���X�̃w�b�_�[�t�@�C��
 *
 * @author Kato Yuki
 *
 * @date 2024/2/1
 *
 */
#pragma once

#include "Game/Effect/ParticleEffect.h"

class GoalEffect : public ParticleEffect
{
//----------------------------------------------
// �萔
//----------------------------------------------
private:

	// �����ʒu�̕�
	const float RANDOM_POSITION = 0.1f;
	// �����x�̕�
	const float RANDOM_ACCELERATION = 0.0001f;
	// ���x
	const DirectX::SimpleMath::Vector3 VELOCITY = DirectX::SimpleMath::Vector3(0.0f, 0.1f, 0.0f);
	// �������̗̑�
	const float START_LIFE = 1.0f;
	// �����A���Ŏ��̑傫��
	DirectX::SimpleMath::Vector2 START_SCALE = DirectX::SimpleMath::Vector2(0.5f, 0.5f);
	DirectX::SimpleMath::Vector2 END_SCALE   = DirectX::SimpleMath::Vector2(0.0f, 0.0f);
	// �����A���Ŏ��̐F
	DirectX::SimpleMath::Color START_COLOR = DirectX::SimpleMath::Color(1.0f, 0.0780f, 0.570f, 1.0f);
	DirectX::SimpleMath::Color END_COLOR   = START_COLOR;


//----------------------------------------------
// �ϐ�
//----------------------------------------------
private:

	// �^�C�}�[
	float m_timer;

//----------------------------------------------
// �֐�
//----------------------------------------------
public:

	// �R���X�g���N�^
	GoalEffect(
		EffectManager* effectManager,
		DirectX::SimpleMath::Vector3 position, 
		std::string textureName, 
		float generateInterval = 0.0f);
	// �f�X�g���N�^
	~GoalEffect();

	// �X�V
	void Update() override;
	// �`��
	void Render(
		DirectX::SimpleMath::Matrix view,
		DirectX::SimpleMath::Matrix projection,
		DirectX::SimpleMath::Vector3 eye,
		DirectX::SimpleMath::Vector3 target,
		DirectX::SimpleMath::Vector3 up ) override;
};