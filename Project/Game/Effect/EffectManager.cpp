/**
 *
 * @file Particle.cpp
 *
 * @brief �p�[�e�B�N���G�t�F�N�g�N���X�̃\�[�X�t�@�C��
 *
 * @author Kato Yuki
 *
 * @date 2024/1/25
 *
 */
#include "pch.h"
#include "EffectManager.h"

#include "Game/MyLibrary/CommonResource/GameResource.h"
#include "Game/MyLibrary/Shader/Shader.h"

using namespace DirectX;

//------------------------------------------------------------------
/**
 * @brief �R���X�g���N�^
 *
 * @param  �Ȃ�
 */
EffectManager::EffectManager()
	: m_list()
	, m_shader(nullptr)
{
}

//------------------------------------------------------------------
/**
 * @brief �f�X�g���N�^
 */
EffectManager::~EffectManager()
{
}

//------------------------------------------------------------------
/**
 * @brief ������
 *
 * @param  �Ȃ�
 * @return �Ȃ�
 */
void EffectManager::Initialize()
{
	// �V�F�[�_�[�̍쐬
	m_shader = std::make_unique<Shader<VertexPositionColorTexture>>();
	m_shader->CreateData(KT::Shader::EFFECT);
	m_shader->CreateConstantBuffer<EffectConstantBuffer>();
}

//------------------------------------------------------------------
/**
 * @brief �X�V
 *
 * @param  �Ȃ�
 * @return �Ȃ�
 */
void EffectManager::Update()
{
	for (KT::IEffect* effect : m_list)
	{
		effect->Update();
	}
}

//------------------------------------------------------------------
/**
 * @brief �`��
 *
 * @param  view      �F�r���[�s��
 * @param  projection�F�ˉe�s��
 * @param  eye       �F�J�����ʒu
 * @param  target    �F�����_
 * @param  up        �F�J�����̓��̌���
 * @return �Ȃ�
 */
void EffectManager::Render(const DirectX::SimpleMath::Matrix& view,
	const DirectX::SimpleMath::Matrix& projection,
	const DirectX::SimpleMath::Vector3 eye,
	const DirectX::SimpleMath::Vector3 target,
	const DirectX::SimpleMath::Vector3 up)
{
	for (KT::IEffect* effect : m_list)
	{
		effect->Render(view, projection, eye, target, up);
	}
}

//------------------------------------------------------------------
/**
 * @brief �V�F�[�_�[�̎擾
 *
 * @param  �Ȃ�
 * @return Shader<Vertex>*�F�V�F�[�_�[�̃|�C���^
 */
Shader<DirectX::VertexPositionColorTexture>* EffectManager::GetShader() const
{
	return m_shader.get();
}

//------------------------------------------------------------------
/**
 * @brief �G�t�F�N�g�̒ǉ�
 *
 * @param  effect�F�ǉ�����G�t�F�N�g
 * @return �Ȃ�
 */
void EffectManager::AddEffect(KT::IEffect* effect)
{
	m_list.push_back(effect);
}

//------------------------------------------------------------------
/**
 * @brief �G�t�F�N�g�̍폜
 *
 * @param  effect�F�폜����G�t�F�N�g
 * @return �Ȃ�
 */
void EffectManager::DeleteEffect(KT::IEffect* effect)
{
	if (m_list.empty()) return;
	std::vector<KT::IEffect*>::iterator it = std::find(m_list.begin(), m_list.end(), effect);
	if(it != m_list.end()) m_list.erase(it);
}

//------------------------------------------------------------------
/**
 * @brief �G�t�F�N�g�S�폜
 *
 * @param  �Ȃ�
 * @return �Ȃ�
 */
void EffectManager::Clear()
{
	m_list.clear();
}