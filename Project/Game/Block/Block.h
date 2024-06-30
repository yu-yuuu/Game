/**
 *
 * @file Block.h
 *
 * @brief �X�e�[�W���`������u���b�N�̊��N���X�̃w�b�_�[�t�@�C��
 *
 * @author Kato Yuki
 *
 * @date 2023/12/28
 *
 */
#pragma once

#include "Model.h"
#include "Game/Block/IBlock.h"
#include "Game/MyLibrary/GameObject/GameObject.h"
#include "Game/MyLibrary/Collision/Collider.h"

class Block : public IBlock, public GameObject
{
//----------------------------------------------
// �ϐ�
//----------------------------------------------
private:

	// �u���b�N�̎��
	KT::Block::Type m_type;
	// �u���b�N�̓����蔻�胂�[�h
	KT::Block::CollisionMode m_collisionMode;
	// ���f��
	DirectX::Model* m_model;
	// �����蔻��}�`
	std::unique_ptr<Collider> m_collider;

//----------------------------------------------
// �֐�
//----------------------------------------------
public:

	// �R���X�g���N�^
	Block(
		KT::Block::Type type,
		KT::Block::CollisionMode collisionMode,
		const DirectX::SimpleMath::Vector3& position,
		DirectX::Model* model
	);
	// �f�X�g���N�^
	virtual ~Block();

	// ������
	virtual void Initialize(std::function<void(DirectX::IEffect* effect)> effect = nullptr) override;
	// �X�V
	virtual void Update() override;
	// �`��
	virtual void Render(
		DirectX::SimpleMath::Matrix view,
		DirectX::SimpleMath::Matrix projection,
		std::function<void()> custom = nullptr) override;
	// �㏈��
	void Finalize() override;

	// �u���b�N��ނ̎擾
	KT::Block::Type GetType() override;
	// �u���b�N��ނ̐ݒ�
	void SetType(KT::Block::Type type) override;
	// ���f���擾
	DirectX::Model* GetModel() const;
	// �����蔻�苫�E�}�`�擾
	Collider* GetCollider() const;
	// �����蔻�苫�E�}�`�ݒ�
	void SetCollider(std::unique_ptr<Collider> collider);
	// �����蔻�胂�[�h�擾
	KT::Block::CollisionMode GetCollisionMode() const;
};