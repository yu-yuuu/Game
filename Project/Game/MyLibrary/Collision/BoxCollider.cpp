/**
 *
 * @file BoxCollider.cpp
 *
 * @brief �����蔻��Ɏg�p���锠��\���N���X�̃\�[�X�t�@�C��
 *
 * @author Kato Yuki
 *
 * @date 2024/1/5
 *
 */
#include "pch.h"
#include "BoxCollider.h"

using namespace DirectX;

//------------------------------------------------------------------
/**
 * @brief �R���X�g���N�^
 *
 * @param position   �F�ʒu
 * @param extents    �F���S����e�ʂ܂ł̋���
 * @param isCollision�F���̃I�u�W�F�N�g�Ɣ������邩
 */
BoxCollider::BoxCollider(
	DirectX::SimpleMath::Vector3 position, 
	DirectX::SimpleMath::Vector3 extents, 
	bool isCollision
)
	: Collider(Collider::Shape::BOX, position, isCollision)
	, m_extents(extents)
	, m_boundingBox{ position, extents }
{
}

//------------------------------------------------------------------
/**
 * @brief �f�X�g���N�^
 */
BoxCollider::~BoxCollider()
{
}

//------------------------------------------------------------------
/**
 * @brief �ʒu�̐ݒ�
 *
 * @param  position�F�ݒ肷��ʒu
 * @return �Ȃ�
 */
void BoxCollider::SetPosition(const DirectX::SimpleMath::Vector3& position)
{
	Collider::SetPosition(position);
	m_boundingBox.Center = position;
}

//------------------------------------------------------------------
/**
 * @brief  �����蔻��{�b�N�X�̎擾
 *
 * @param  �Ȃ�
 * @return CollisionBox�F�����蔻��{�b�N�X
 */
const BoxCollider& BoxCollider::GetCollisionBox() const
{
	return *this;
}

//------------------------------------------------------------------
/**
 * @brief  �e�ʂ܂ł̋����擾
 *
 * @param �Ȃ�
 * @return Vector3�F�e�ʂ܂ł̋���
 */
const DirectX::SimpleMath::Vector3& BoxCollider::GetExtents() const
{
	return m_extents;
}

//------------------------------------------------------------------
/**
 * @brief DirectX�o�E���f�B���O�{�b�N�X�̎擾
 *
 * @param �Ȃ�
 * @return BoundingBox�FDirectX�o�E���f�B���O�{�b�N�X
 */
const DirectX::BoundingBox& BoxCollider::GetBoundingBox() const
{
	return m_boundingBox;
}

//------------------------------------------------------------------
/**
 * @brief ���̒��_�擾
 *
 * @param  max�F���W���傫�����̒��_
 * @param  min�F���W�����������̒��_
 * @return �Ȃ�
 */
void BoxCollider::GetCorners(DirectX::SimpleMath::Vector3& min, DirectX::SimpleMath::Vector3& max)
{
	min = GetPosition() - m_extents;
	max = GetPosition() + m_extents;
}