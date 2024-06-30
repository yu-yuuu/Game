/**
 *
 * @file GoalEffect.h
 *
 * @brief �S�[���G�t�F�N�g��\���N���X�̃\�[�X�t�@�C��
 *
 * @author Kato Yuki
 *
 * @date 2024/2/1
 *
 */
#include "pch.h"
#include "GoalEffect.h"
#include <random>
#include "Game/MyLibrary/CommonResource/GameResource.h"
#include "Game/Effect/Particle.h"

using namespace DirectX;

//------------------------------------------------------------------
/**
 * @brief �R���X�g���N�^
 *
 * @param effectManager   �F�G�t�F�N�g�}�l�[�W���[�̃|�C���^
 * @param position        �F�ʒu
 * @param textureName     �F�g�p����摜�̖��O
 * @param generateInterval�F�����Ԋu
 */
GoalEffect::GoalEffect(EffectManager* effectManager, DirectX::SimpleMath::Vector3 position, std::string textureName, float generateInterval)
	: ParticleEffect(effectManager, position, textureName, generateInterval)
	, m_timer(0.0f)
{
}

//------------------------------------------------------------------
/**
 * @brief �f�X�g���N�^
 */
GoalEffect::~GoalEffect()
{
}

//------------------------------------------------------------------
/**
 * @brief �X�V
 *
 * @param  �Ȃ�
 * @return �Ȃ�
 */
void GoalEffect::Update()
{
	// �X�e�b�v�^�C�}�[�擾
	DX::StepTimer* stepTimer = GameResource::GetInstance()->GetStepTimer();
	// �^�C�}�[�i�s
	double elapsedTime = stepTimer->GetElapsedSeconds();
	m_timer += static_cast<float>(elapsedTime);

	// �p�[�e�B�N�������֐��쐬
	std::function<std::unique_ptr<Particle>()> function = 
		[&]()
	{
		// ��������
		std::random_device rd;
		std::mt19937 mt(rd());
		std::uniform_real_distribution<float> posRand(-RANDOM_POSITION, RANDOM_POSITION);
		std::uniform_real_distribution<float> accelRand(-RANDOM_ACCELERATION, RANDOM_ACCELERATION);
		// �����ʒu
		SimpleMath::Vector3 position =  SimpleMath::Vector3(posRand(rd), 0.0f, posRand(rd));
		// ���x
		SimpleMath::Vector3 velocity = SimpleMath::Vector3(0.0f, 0.1f, 0.0f);
		// �����x
		SimpleMath::Vector3 acceleration = SimpleMath::Vector3(accelRand(mt), 0.0f, accelRand(mt));
		// �p�[�e�B�N������
		return std::make_unique<Particle>(
			position + GetPosition(),
			VELOCITY,
			START_LIFE,
			acceleration,
			START_SCALE, END_SCALE,
			START_COLOR, END_COLOR
		);
	};

	// �����֐��ݒ�
	SetGenerateFunction(function);
	// ���N���X�̍X�V
	ParticleEffect::Update();
}

//------------------------------------------------------------------
/**
 * @brief �`��
 *
 * @param  view      �F�r���[�s��
 * @param  projection�F�ˉe�s��
 * @param  eye       �F�J�����ʒu
 * @param  target    �F�����_
 * @param  up        �F�J�����̓��̌���
 * @return �Ȃ�
 */
void GoalEffect::Render(DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix projection, DirectX::SimpleMath::Vector3 eye, DirectX::SimpleMath::Vector3 target, DirectX::SimpleMath::Vector3 up)
{
	ParticleEffect::Render(view, projection, eye, target, up);
}