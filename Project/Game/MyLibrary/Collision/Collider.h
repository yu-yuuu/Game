/**
 *
 * @file Collider.h
 *
 * @brief �I�u�W�F�N�g�ɕt���铖���蔻���\���N���X�̃w�b�_�[
 *
 * @author Kato Yuki
 *
 * @date 2024/1/3
 *
 * @note �⑫�����A����
 *
 */
#pragma once

class GameObject;

class Collider
{
//----------------------------------------------
// �񋓑�
//----------------------------------------------
public:

	// �}�`�^�C�v
	enum class Shape
	{
		BOX,    // ��
		SPHERE, // ��
		NONE,   // ���ݒ�
	};

//----------------------------------------------
// �ϐ�
//----------------------------------------------
private:

	// �}�`���
	Shape m_type;
	// �t���Ă���Q�[���I�u�W�F�N�g
	GameObject* m_gameObject;
	// �ʒu
	DirectX::SimpleMath::Vector3 m_position;
	// ���̃I�u�W�F�N�g�Ɣ������邩
	bool m_isCollision;

//----------------------------------------------
// �֐�
//----------------------------------------------
public:

	// �R���X�g���N�^
	Collider(Shape type, DirectX::SimpleMath::Vector3 position, bool isCollision);
	// �f�X�g���N�^
	virtual ~Collider() = default;

	// �}�`�^�C�v�̎擾
	Shape GetType()const;
	// �}�`�^�C�v�̐ݒ�
	void SetType(Shape type);

	// �ʒu�̎擾
	virtual const DirectX::SimpleMath::Vector3& GetPosition() const;
	// �ʒu�̐ݒ�
	virtual void SetPosition(const DirectX::SimpleMath::Vector3& position);

	// ���I�u�W�F�N�g�Ɣ������邩�m�F
	bool IsCollision() const;
	// ���I�u�W�F�N�g�Ɣ������邩�ݒ�
	void SetIsCollision(bool isCollision);

	// �Q�[���I�u�W�F�N�g�擾
	GameObject* GetGameObject() const;
	// �Q�[���I�u�W�F�N�g�ݒ�
	void SetGameObject(GameObject* gameObject);

	// �ڐG������
	void OnCollision(Collider* collider);

};