/**
 *
 * @file Particle.cpp
 *
 * @brief �p�[�e�B�N���̗�1��\���N���X�̃\�[�X�t�@�C��
 *
 * @author Kato Yuki
 *
 * @date 2024/1/31
 *
 */
#include "pch.h"
#include "Particle.h"

using namespace DirectX;

//------------------------------------------------------------------
/**
 * @brief �R���X�g���N�^
 *
 * @param position    �F�`��ʒu
 * @param velocity    �F�ړ����x
 * @param startLife   �F�������̗̑�
 * @param acceleration�F�����x
 * @param startScale  �F�������̑傫��
 * @param endScale    �F���Ŏ��̑傫��
 * @param startColor  �F�������̐F
 * @param endColor    �F���Ŏ��̐F
 */
Particle::Particle(
	DirectX::SimpleMath::Vector3 position, 
	DirectX::SimpleMath::Vector3 velocity,
	float startLife, 
	DirectX::SimpleMath::Vector3 acceleration,
	DirectX::SimpleMath::Vector2 startScale,
	DirectX::SimpleMath::Vector2 endScale,
	DirectX::SimpleMath::Color startColor,
	DirectX::SimpleMath::Color endColor)
	: m_position(position)
	, m_velocity(velocity)
	, m_nowLife(startLife)
	, m_acceleration(acceleration)
	, m_startLife(startLife)
	, m_nowScale()
	, m_startScale(startScale)
	, m_endScale(endScale)
	, m_nowColor()
	, m_startColor(startColor)
	, m_endColor(endColor)
{
}

//------------------------------------------------------------------
/**
 * @brief �f�X�g���N�^
 *
 */
Particle::~Particle()
{
}

//------------------------------------------------------------------
/**
 * @brief �X�V
 *
 * @param  elapsedTime�F�o�ߎ���
 * @return �Ȃ�
 */
void Particle::Update(const float& elapsedTime)
{
	// ���x�v�Z
	m_velocity += m_acceleration;
	// ���x���ʒu�ɔ��f
	m_position += m_velocity;
	// �̗͌���
	m_nowLife -= elapsedTime;
	// �̗͂� 0 �ȉ��Ȃ�s�b�^�� 0 �ɍ��킹��
	if (m_nowLife <= 0.0f) m_nowLife = 0.0f;
	// �ő�̗͂̉��������߂�
	float rate = m_nowLife / m_startLife;
	// 0 -> 1 �ɂ������̂Ŕ��]������
	rate = 1.0f - rate;
	// ���݂̑傫���X�V
	m_nowScale = SimpleMath::Vector2::Lerp(m_startScale, m_endScale, rate);
	// ���݂̐F�����X�V
	m_nowColor = SimpleMath::Color::Lerp(m_startColor, m_endColor, rate);
}

//------------------------------------------------------------------
/**
 * @brief �ʒu�̎擾
 *
 * @param �Ȃ�
 * @return Vector3�F�ʒu
 */
const DirectX::SimpleMath::Vector3& Particle::GetPosition()
{
	return m_position;
}

//------------------------------------------------------------------
/**
 * @brief ���x�̎擾
 *
 * @param �Ȃ�
 * @return Vector3�F���x
 */
const DirectX::SimpleMath::Vector3& Particle::GetVelocity()
{
	return m_velocity;
}

//------------------------------------------------------------------
/**
 * @brief �傫���̎擾
 *
 * @param �Ȃ�
 * @return Vector3�F�傫��
 */
const DirectX::SimpleMath::Vector2& Particle::GetScale()
{
	return m_nowScale;
}

//------------------------------------------------------------------
/**
 * @brief �F�̎擾
 *
 * @param �Ȃ�
 * @return Vector3�F�F
 */
const DirectX::SimpleMath::Color& Particle::GetColor()
{
	return m_nowColor;
}

//------------------------------------------------------------------
/**
 * @brief �����Ă��邩�m�F
 *
 * @param �Ȃ�
 * @return true �F�����Ă���
 * @return false�F����ł���
 */
bool Particle::IsAlive()
{
	return m_nowLife > 0.0f;
}
