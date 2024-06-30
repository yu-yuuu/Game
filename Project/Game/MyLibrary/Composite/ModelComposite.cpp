/**
 *
 * @file ModelComposite.cpp
 *
 * @brief ���f���̐e�q�\����\���N���X�̃\�[�X�t�@�C��
 *
 * @author Kato Yuki
 *
 * @date 2024/1/29
 *
 */
#include "pch.h"
#include "ModelComposite.h"
#include "Game/MyLibrary/CommonResource/GameResource.h"

using namespace DirectX;

//------------------------------------------------------------------
/**
 * @brief �R���X�g���N�^
 *
 * @param model�F���[�J�����W
 */
ModelComposite::ModelComposite(DirectX::Model* model, DirectX::SimpleMath::Vector3 localPosition)
	: m_model(model)
	, m_transform()
	, m_world()
	, m_child()
{
	// �����ʒu�̍s����v�Z
	m_initial = SimpleMath::Matrix::CreateTranslation(localPosition);
}

//------------------------------------------------------------------
/**
 * @brief �f�X�g���N�^
 */
ModelComposite::~ModelComposite()
{
}

//------------------------------------------------------------------
/**
 * @brief �X�V
 *
 * @param  worldMatrix�F���[���h�s��
 * @return �Ȃ�
 */
void ModelComposite::Update(const DirectX::SimpleMath::Matrix& worldMatrix)
{
	// ���g�̃��[�J���s����v�Z
	m_world = m_transform * m_initial;

	// ���g�̃��[�J���s��ƈ����̍s��Ń��[���h���W���v�Z����
	m_world *= worldMatrix;

	// �q�̃��[���h�s����X�V����
	for (ModelComposite* child : m_child)
	{
		child->Update(m_world);
	}
}

//------------------------------------------------------------------
/**
 * @brief �`��
 *
 * @param  view      �F�r���[�s��
 * @param  projection�F�ˉe�s��
 * @param  custom    �F���f���ɓK�������郉���_��
 * @return �Ȃ�
 */
void ModelComposite::Render(DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix projection, std::function<void()> custom)
{
	// �e�탊�\�[�X�擾
	GameResource*         gameResource = GameResource::GetInstance();
	ID3D11DeviceContext1* context      = gameResource->GetDeviceResources()->GetD3DDeviceContext();
	CommonStates*         commonStates = gameResource->GetCommonStates();

	// �o�^����Ă��郂�f����`��
	if(m_model) m_model->Draw(context, *commonStates, m_world, view, projection, false, custom);

	// �q�̃��f����`��
	for (ModelComposite* child : m_child)
	{
		child->Render(view, projection, custom);
	}
}

//------------------------------------------------------------------
/**
 * @brief ���f���ɓK��������G�t�F�N�g�X�V
 *
 * @param  setEffect�F���f���ɓK��������G�t�F�N�g
 * @return �Ȃ�
 */
void ModelComposite::UpdateEffects(std::function<void(IEffect*)> setEffect)
{
	// �G�t�F�N�g�X�V
	if(m_model) m_model->UpdateEffects(setEffect);

	// ���g�̎q�ɂ��K��������
	for (ModelComposite* child : m_child)
	{
		child->UpdateEffects(setEffect);
	}
}

//------------------------------------------------------------------
/**
 * @brief �ϊ��s��ݒ�
 *
 * @param  transformMatrix�F�ϊ��s��
 * @return �Ȃ�
 */
void ModelComposite::SetTransformMatrix(const DirectX::SimpleMath::Matrix& transformMatrix)
{
	m_transform = transformMatrix;
}

//------------------------------------------------------------------
/**
 * @brief �q��ݒ�
 *
 * @param  child�F�ݒ肷��q
 * @return �Ȃ�
 */
void ModelComposite::SetChild(ModelComposite* child)
{
	// �q��ǉ�
	m_child.push_back(child);
}