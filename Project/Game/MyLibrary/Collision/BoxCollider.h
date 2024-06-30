/**
 *
 * @file BoxCollider.h
 *
 * @brief �����蔻��Ɏg�p���锠��\���N���X�̃w�b�_�[�t�@�C��
 *
 * @author Kato Yuki
 *
 * @date 2024/1/5
 *
 */
#pragma once

#include"Collider.h"

class BoxCollider : public Collider
{
//----------------------------------------------
// �ϐ�
//----------------------------------------------
private:

	// ���S����e�ʂ܂ł̋���
	DirectX::SimpleMath::Vector3 m_extents;
	// DirectX�o�E���f�B���O�{�b�N�X
	DirectX::BoundingBox m_boundingBox;

//----------------------------------------------
// �֐�
//----------------------------------------------
public:

	// �R���X�g���N�^
	BoxCollider(DirectX::SimpleMath::Vector3 position, DirectX::SimpleMath::Vector3 extents, bool isCollision = false);
	// �f�X�g���N�^
	~BoxCollider();
	
	// �ʒu�̐ݒ�
	void SetPosition(const DirectX::SimpleMath::Vector3& position);
	// �����蔻��{�b�N�X�̎擾
	const BoxCollider& GetCollisionBox() const;
	// �e�ʂ܂ł̋����擾
	const DirectX::SimpleMath::Vector3& GetExtents() const;
	// DirectX�o�E���f�B���O�{�b�N�X�̎擾
	const DirectX::BoundingBox& GetBoundingBox() const;
	// ���̒��_�擾
	void GetCorners(DirectX::SimpleMath::Vector3& min, DirectX::SimpleMath::Vector3& max);
};