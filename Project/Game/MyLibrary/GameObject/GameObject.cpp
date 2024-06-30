#include "pch.h"
#include "GameObject.h"

using namespace DirectX;

//------------------------------------------------------------------
/**
 * @brief �R���X�g���N�^
 *
 * @param �Ȃ�
 */
GameObject::GameObject()
    : m_world(SimpleMath::Matrix::Identity)
    , m_position(SimpleMath::Vector3::Zero)
    , m_rotation(SimpleMath::Quaternion::Identity)
    , m_scale(SimpleMath::Vector3::One)
    , m_isActive(true)
    , m_isChange(false)
{
}

//------------------------------------------------------------------
/**
 * @brief �ڐG�������i�P�́j
 *
 * @param gameObject�F���������I�u�W�F�N�g
 * @return �Ȃ�
 */
void GameObject::OnCollision(GameObject* gameObject)
{
    gameObject;
}

//------------------------------------------------------------------
/**
 * @brief ���[���h�s��擾
 *
 * @param  �Ȃ�
 * @return Matrix�F���[���h�s��
 */
const SimpleMath::Matrix& GameObject::GetWorldMatrix()
{
    // �I�u�W�F�N�g���ɕύX������Ȃ�s����Čv�Z����
    if (m_isChange)
    {
        // ������
        m_world = SimpleMath::Matrix::Identity;
        // �e�s����v�Z����
        m_world *= SimpleMath::Matrix::CreateScale(m_scale);             // �g��k��
        m_world *= SimpleMath::Matrix::CreateFromQuaternion(m_rotation); // ��]
        m_world *= SimpleMath::Matrix::CreateTranslation(m_position);    // �ʒu

        // �t���O������
        m_isChange = false;
    }

    return m_world;
}

//------------------------------------------------------------------
/**
 * @brief �ʒu�̎擾
 *
 * @param �Ȃ�
 * @return Vector3�F�ʒu
 */
const SimpleMath::Vector3& GameObject::GetPosition() const
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
void GameObject::SetPosition(const SimpleMath::Vector3& position)
{   
    // �Ⴄ�l��
    if (m_position != position)
    {
        // �l����
        m_position = position;
        // �t���O�𗧂Ă�
        m_isChange = true;
    }
}

//------------------------------------------------------------------
/**
 * @brief ��]�̎擾
 *
 * @param �Ȃ�
 * @return Quaternion�F��]�N�H�[�^�j�I��
 */
const SimpleMath::Quaternion& GameObject::GetRotation() const
{
    return m_rotation;
}

//------------------------------------------------------------------
/**
 * @brief ��]�̐ݒ�i�N�H�[�^�j�I�� ver�j
 *
 * @param  rotation�F�ݒ肷���]
 * @return �Ȃ�
 */
void GameObject::SetRotation(const SimpleMath::Quaternion& rotation)
{
    // �Ⴄ�l��
    if (m_rotation != rotation)
    {
        // �l����
        m_rotation = rotation;
        // �t���O�𗧂Ă�
        m_isChange = true;
    }
}

//------------------------------------------------------------------
/**
 * @brief ��]�̐ݒ�iVector3 ver�j
 *
 * @param rotation�F�ݒ肷���]
 * @return �Ȃ�
 */
void GameObject::SetRotation(const SimpleMath::Vector3& rotation)
{
    SetRotation(SimpleMath::Quaternion::CreateFromYawPitchRoll(rotation));
}

//------------------------------------------------------------------
/**
 * @brief �傫���̎擾
 *
 * @param  �Ȃ�
 * @return Vector3�F�傫��
 */
const SimpleMath::Vector3& GameObject::GetScale() const
{
    return m_scale;
}

//------------------------------------------------------------------
/**
 * @brief �傫���̐ݒ�
 *
 * @param  scale�F�ݒ肷��傫��
 * @return �Ȃ�
 */
void GameObject::SetScale(const SimpleMath::Vector3& scale)
{
    // �Ⴄ�l��
    if (m_scale != scale)
    {
        // �l����
        m_scale = scale;
        // �t���O�𗧂Ă�
        m_isChange = true;
    }
}

//------------------------------------------------------------------
/**
 * @brief �A�N�e�B�u��Ԃ�
 *
 * @param  �Ȃ�
 * @return true �F�A�N�e�B�u���
 * @return false�F��A�N�e�B�u���
 */
const bool GameObject::IsActive() const
{
    return m_isActive;
}

//------------------------------------------------------------------
/**
 * @brief �A�N�e�B�u��Ԑݒ�
 *
 * @param  isActive�F�ݒ肷����
 * @return �Ȃ�
 */
void GameObject::SetActive(bool isActive)
{
    m_isActive = isActive;
}


//------------------------------------------------------------------
/**
 * @brief �p���x�N�g���擾�i�O���j
 *
 * @param �Ȃ�
 * @return Vector3�F�p���x�N�g���i�O���j
 */
const DirectX::SimpleMath::Vector3 GameObject::Forward()
{
    return SimpleMath::Vector3::Transform(SimpleMath::Vector3::Forward, m_rotation);
}

//------------------------------------------------------------------
/**
 * @brief �p���x�N�g���擾�i����j
 *
 * @param �Ȃ�
 * @return Vector3�F�p���x�N�g���i����j
 */
const DirectX::SimpleMath::Vector3 GameObject::Back()
{
    return SimpleMath::Vector3::Transform(SimpleMath::Vector3::Backward, m_rotation);
}

//------------------------------------------------------------------
/**
 * @brief �p���x�N�g���擾�i�E�����j
 *
 * @param �Ȃ�
 * @return Vector3�F�p���x�N�g���i�E�����j
 */
const DirectX::SimpleMath::Vector3 GameObject::Right()
{
    return SimpleMath::Vector3::Transform(SimpleMath::Vector3::Right, m_rotation);
}

//------------------------------------------------------------------
/**
 * @brief �p���x�N�g���擾�i�������j
 *
 * @param �Ȃ�
 * @return Vector3�F�p���x�N�g���i�������j
 */
const DirectX::SimpleMath::Vector3 GameObject::Left()
{
    return SimpleMath::Vector3::Transform(SimpleMath::Vector3::Left, m_rotation);
}

//------------------------------------------------------------------
/**
 * @brief �p���x�N�g���擾�i������j
 *
 * @param �Ȃ�
 * @return Vector3�F�p���x�N�g���i������j
 */
const DirectX::SimpleMath::Vector3 GameObject::Up()
{
    return SimpleMath::Vector3::Transform(SimpleMath::Vector3::Up, m_rotation);
}

//------------------------------------------------------------------
/**
 * @brief �p���x�N�g���擾�i�������j
 *
 * @param �Ȃ�
 * @return Vector3�F�p���x�N�g���i�������j
 */
const DirectX::SimpleMath::Vector3 GameObject::Down()
{
    return SimpleMath::Vector3::Transform(SimpleMath::Vector3::Down, m_rotation);
}