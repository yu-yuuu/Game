/**
 *
 * @file GameObject.h
 *
 * @brief �Q�[���I�u�W�F�N�g��\���N���X�̃w�b�_�[�t�@�C��
 *
 * @author Kato Yuki
 *
 * @date 2023/11/13
 *
 * @note �⑫�����A����
 *
 */
#pragma once

#include <vector>
#include <functional>
#include <Effects.h>

class GameObject
{
//----------------------------------------------
// �ϐ�
//----------------------------------------------
private:

	// ���[���h�s��
	DirectX::SimpleMath::Matrix m_world;
	// �ʒu
	DirectX::SimpleMath::Vector3 m_position;
	// ��]
	DirectX::SimpleMath::Quaternion m_rotation;
	// �傫��
	DirectX::SimpleMath::Vector3 m_scale;

	// �A�N�e�B�u���ǂ���
	bool m_isActive;
	// �I�u�W�F�N�g��񂪕ύX���ꂽ��
	bool m_isChange;

//----------------------------------------------
// �֐�
//----------------------------------------------
public:

	// �R���X�g���N�^
	GameObject();
	// �f�X�g���N�^
	virtual ~GameObject() = default;
	// ������
	virtual void Initialize(std::function<void(DirectX::IEffect* effect)> effect = nullptr) = 0;
	// �X�V
	virtual void Update() = 0;
	// �`��
	virtual void Render(
		DirectX::SimpleMath::Matrix view, 
		DirectX::SimpleMath::Matrix projection,
		std::function<void()> custom = nullptr) = 0;
	// �㏈��
	virtual void Finalize() = 0;

	// �ڐG������
	virtual void OnCollision(GameObject* gameObject);

	// ���[���h�s��̎擾
	const DirectX::SimpleMath::Matrix& GetWorldMatrix();
	// �ʒu�̎擾�A�ݒ�
	const DirectX::SimpleMath::Vector3& GetPosition() const;
	void SetPosition(const DirectX::SimpleMath::Vector3& position);
	// ��]�̎擾�ݒ�
	const DirectX::SimpleMath::Quaternion& GetRotation() const;
	void SetRotation(const DirectX::SimpleMath::Quaternion& rotation);
	void SetRotation(const DirectX::SimpleMath::Vector3& rotation);
	// �傫���̐ݒ�
	const DirectX::SimpleMath::Vector3& GetScale() const;
	void SetScale(const DirectX::SimpleMath::Vector3& scale);

	// �A�N�e�B�u��Ԃ̎擾�A�ݒ�
	const bool IsActive()const;
	void SetActive(bool isActive);

	// �p���x�N�g���擾
	const DirectX::SimpleMath::Vector3 Forward(); // ����
	const DirectX::SimpleMath::Vector3 Back();    // ���
	const DirectX::SimpleMath::Vector3 Right();   // �E
	const DirectX::SimpleMath::Vector3 Left();    // ��
	const DirectX::SimpleMath::Vector3 Up();      // ��
	const DirectX::SimpleMath::Vector3 Down();    // ��
};