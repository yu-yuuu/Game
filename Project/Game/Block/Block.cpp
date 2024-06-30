/**
 *
 * @file Block.cpp
 *
 * @brief �X�e�[�W���`������u���b�N�̊��N���X�̃\�[�X�t�@�C��
 *
 * @author Kato Yuki
 *
 * @date 2023/12/28
 *
 */
#include "pch.h"
#include "Block.h"
#include "Game/MyLibrary/CommonResource/GameResource.h"
#include "Game/MyLibrary/ResourceManager/ResourceType.h"

using namespace DirectX;

//------------------------------------------------------------------
/**
 * @brief �R���X�g���N�^
 *
 * @param  type         �F�u���b�N�̎��
 * @param  collisionMode�F�����蔻�胂�[�h
 * @param  position     �F�����ʒu
 * @param  model        �F�u���b�N���f��
 */
Block::Block(
	KT::Block::Type type,
	KT::Block::CollisionMode collisionMode,
	const DirectX::SimpleMath::Vector3& position,
	DirectX::Model* model
)
	: m_type(type)
	, m_collisionMode(collisionMode)
	, m_model(model)
	, m_collider(nullptr)
{
	// �����ʒu�ݒ�
	SetPosition(position);
}

//------------------------------------------------------------------
/**
 * @brief �f�X�g���N�^
 */
Block::~Block()
{
}

//------------------------------------------------------------------
/**
 * @brief ������
 *
 * @param  effect�F���f���ɓK��������G�t�F�N�g
 * @return �Ȃ�
 */
void Block::Initialize(std::function<void(DirectX::IEffect* effect)> effect)
{
	if(effect) m_model->UpdateEffects(effect);
}

//------------------------------------------------------------------
/**
 * @brief �X�V
 *
 * @param  �Ȃ�
 * @return �Ȃ�
 */
void Block::Update()
{
}

//------------------------------------------------------------------
/**
 * @brief �`��
 *
 * @param  view      �F�r���[�s��
 * @param  projection�F�ˉe�s��
 * @param  custom    �F�u���b�N�ɓK�������郉���_��
 * @return �Ȃ�
 */
void Block::Render(
	DirectX::SimpleMath::Matrix view, 
	DirectX::SimpleMath::Matrix projection,
	std::function<void()> custom)
{
	// ���f�����ݒ肳��Ă��Ȃ�����
	// �A�N�e�B�u��ԂłȂ����͕`�悵�Ȃ�
	if (m_model == nullptr || !IsActive()) return;
	
	// �e�탊�\�[�X�擾
	GameResource*         gameResource = GameResource::GetInstance();
	ID3D11DeviceContext1* context      = gameResource->GetDeviceResources()->GetD3DDeviceContext();
	CommonStates*         commonStates = gameResource->GetCommonStates();

	// ���[���h�s��擾
	SimpleMath::Matrix world = GetWorldMatrix();

	// ���f���`��
	m_model->Draw(context, *commonStates, world, view, projection, false, custom);
}

//------------------------------------------------------------------
/**
 * @brief �㏈��
 *
 * @param  �Ȃ�
 * @return �Ȃ�
 */
void Block::Finalize()
{
}

//------------------------------------------------------------------
/**
 * @brief ��ނ̎擾
 *
 * @param �Ȃ�
 * @return Type�F�u���b�N�̎��
 */
KT::Block::Type Block::GetType()
{
	return m_type;
}

//------------------------------------------------------------------
/**
 * @brief ��ނ̐ݒ�
 *
 * @param  type�F�ݒ肷��u���b�N�̎��
 * @return �Ȃ�
 */
void Block::SetType(KT::Block::Type type)
{
	m_type = type;
}

//------------------------------------------------------------------
/**
 * @brief ���f���擾
 *
 * @param  �Ȃ�
 * @return Model*�F���f���̃|�C���^
 */
DirectX::Model* Block::GetModel() const
{
	return m_model;
}

//------------------------------------------------------------------
/**
 * @brief �����蔻�苫�E�}�`�擾
 *
 * @param �Ȃ�
 * @return CollisionShape*�F�����蔻�苫�E�}�`�ւ̃|�C���^
 */
Collider* Block::GetCollider() const
{
	return m_collider.get();
}

//------------------------------------------------------------------
/**
 * @brief �����蔻�苫�E�}�`�ݒ�
 *
 * @param  collider�F�ݒ肷�鋫�E�}�`
 * @return �Ȃ�
 */
void Block::SetCollider(std::unique_ptr<Collider> collider)
{
	m_collider = std::move(collider);
	m_collider->SetGameObject(this);
}

//------------------------------------------------------------------
/**
 * @brief �����蔻�胂�[�h�擾
 *
 * @param �Ȃ�
 * @return CollisionMode�F�����蔻�胂�[�h
 */
KT::Block::CollisionMode Block::GetCollisionMode() const
{
	return m_collisionMode;
}