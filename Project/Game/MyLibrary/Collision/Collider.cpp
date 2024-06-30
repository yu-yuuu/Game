#include "pch.h"
#include "Collider.h"

#include "Game/MyLibrary/GameObject/GameObject.h"

//------------------------------------------------------------------
/**
 * @brief �R���X�g���N�^
 *
 * @param type       �F�����蔻��Ɏg�p����}�`�^�C�v
 * @param position   �F�ʒu
 * @param isCollision�F���̃I�u�W�F�N�g�Ɣ�����s����
 */
Collider::Collider(Shape type, DirectX::SimpleMath::Vector3 position, bool isCollision)
	: m_type(type)
	, m_gameObject(nullptr)
	, m_position(position)
	, m_isCollision(isCollision)
{
}

//------------------------------------------------------------------
/**
 * @brief �}�`�^�C�v�̎擾
 *
 * @param  �Ȃ�
 * @return Type�F�}�`�^�C�v
 */
Collider::Shape Collider::GetType() const
{
	return m_type;
}

//------------------------------------------------------------------
/**
 * @brief �}�`�^�C�v�̐ݒ�
 *
 * @param  type�F�ݒ肷��}�`�^�C�v
 * @return �Ȃ�
 */
void Collider::SetType(Shape type)
{
	m_type = type;
}

//------------------------------------------------------------------
/**
 * @brief �ʒu�̎擾
 *
 * @param  �Ȃ�
 * @return Vector3�F�ʒu
 */
const DirectX::SimpleMath::Vector3& Collider::GetPosition() const
{
	return m_position;
}

//------------------------------------------------------------------
/**
 * @brief �ʒu�̐ݒ�
 *
 * @param  position�F�ݒ肷��ʒu
 * @return �Ȃ�
 */
void Collider::SetPosition(const DirectX::SimpleMath::Vector3& position)
{
	m_position = position;
}

//------------------------------------------------------------------
/**
 * @brief ���̃I�u�W�F�N�g�Ɣ������邩�m�F
 *
 * @param  �Ȃ�
 * @return true �F��������
 * @return false�F��������Ȃ�
 */
bool Collider::IsCollision() const
{
	return m_isCollision;
}

//------------------------------------------------------------------
/**
 * @brief ���̃I�u�W�F�N�g�Ɣ������邩�ݒ�
 *
 * @param  isCollision�F�������邩
 * @return �Ȃ�
 */
void Collider::SetIsCollision(bool isCollision)
{
	m_isCollision = isCollision;
}

//------------------------------------------------------------------
/**
 * @brief �Q�[���I�u�W�F�N�g�擾
 *
 * @param �Ȃ�
 * @return GameObject*�F�Q�[���I�u�W�F�N�g�̃|�C���^
 */
GameObject* Collider::GetGameObject() const
{
	return m_gameObject;
}

//------------------------------------------------------------------
/**
 * @brief �Q�[���I�u�W�F�N�g�ݒ�
 *
 * @param  gameObject�F�ݒ肷��Q�[���I�u�W�F�N�g
 * @return �Ȃ�
 */
void Collider::SetGameObject(GameObject* gameObject)
{
	m_gameObject = gameObject;
}

//------------------------------------------------------------------
/**
 * @brief �ڐG������
 *
 * @param collider�F�ڐG�����I�u�W�F�N�g
 * @return �Ȃ�
 */
void Collider::OnCollision(Collider* collider)
{
	m_gameObject->OnCollision(collider->GetGameObject());
}
