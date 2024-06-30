/**
 *
 * @file Particle.h
 *
 * @brief �p�[�e�B�N���̗�1��\���N���X�̃w�b�_�[�t�@�C��
 *
 * @author Kato Yuki
 *
 * @date 2024/1/31
 *
 */
#pragma once

class Particle
{
//----------------------------------------------
// �ϐ�
//----------------------------------------------
private:

	// �ʒu
	DirectX::SimpleMath::Vector3 m_position;   
	// ���x
	DirectX::SimpleMath::Vector3 m_velocity;   	
	// �����x
	DirectX::SimpleMath::Vector3 m_acceleration;

	// ���݂̗̑�
	float m_nowLife;  
	// �������̗̑�
	float m_startLife;

	// ���݂̑傫��
	DirectX::SimpleMath::Vector2 m_nowScale;
	// �������̑傫��
	DirectX::SimpleMath::Vector2 m_startScale;
	// ���Ŏ��̑傫��
	DirectX::SimpleMath::Vector2 m_endScale;   
	
	// ���݂̐F	
	DirectX::SimpleMath::Color m_nowColor; 
	// �������̐F
	DirectX::SimpleMath::Color m_startColor; 
	// ���Ŏ��̐F
	DirectX::SimpleMath::Color m_endColor; 

	
//----------------------------------------------
// �֐�
//----------------------------------------------
public:

	// �R���X�g���N�^
	Particle(
		DirectX::SimpleMath::Vector3 position,
		DirectX::SimpleMath::Vector3 velocity,
		float                        startLife,
		DirectX::SimpleMath::Vector3 acceleration = DirectX::SimpleMath::Vector3::Zero,
		DirectX::SimpleMath::Vector2 startScale   = DirectX::SimpleMath::Vector2::One,
		DirectX::SimpleMath::Vector2 endScale     = DirectX::SimpleMath::Vector2::Zero,
		DirectX::SimpleMath::Color   startColor   = DirectX::SimpleMath::Color(1.0f, 1.0f, 1.0f, 1.0f),
		DirectX::SimpleMath::Color   endColor     = DirectX::SimpleMath::Vector4(1.0f, 1.0f, 1.0f, 0.0f)
	);
	// �f�X�g���N�^
	~Particle();

	// �X�V
	void Update(const float& elapsedTime);

	// �ʒu�̎擾
	const DirectX::SimpleMath::Vector3& GetPosition();
	// ���x�̎擾
	const DirectX::SimpleMath::Vector3& GetVelocity();
	// �傫���̎擾
	const DirectX::SimpleMath::Vector2& GetScale();
	// �F�̎擾
	const DirectX::SimpleMath::Color& GetColor();
	// �����Ă��邩
	bool IsAlive();
};