/**
 *
 * @file ParticleEffect.cpp
 *
 * @brief �p�[�e�B�N���G�t�F�N�g��\���N���X�̃\�[�X�t�@�C��
 *
 * @author Kato Yuki
 *
 * @date 2024/1/31
 *
 */
#include "pch.h"
#include "ParticleEffect.h"

#include "Game/MyLibrary/CommonResource/GameResource.h"
#include "Game/Effect/Particle.h"
#include "Game/Effect/EffectManager.h"
#include "Game/MyLibrary/Shader/Shader.h"

using namespace DirectX;

//------------------------------------------------------------------
/**
 * @brief �R���X�g���N�^
 *
 * @param effectManager   �F�G�t�F�N�g�}�l�[�W���[�̃|�C���^
 * @param position        �F�ʒu
 * @param textureName     �F�g�p����摜�̖��O
 * @param generateInterval�F�����Ԋu
 */
ParticleEffect::ParticleEffect(EffectManager* effectManager, DirectX::SimpleMath::Vector3 position, std::string textureName, float generateInterval)
	:m_effectManager(effectManager)
	, m_position(position)
	, m_textureName(textureName)
	, m_particleList()
	, m_vertices()
	, m_generateInterval(generateInterval)
	, m_generateTimer(0.0f)
{
}

//------------------------------------------------------------------
/**
 * @brief �f�X�g���N�^
 */
ParticleEffect::~ParticleEffect()
{
}

//------------------------------------------------------------------
/**
 * @brief �X�V
 *
 * @param  �Ȃ�
 * @return �Ȃ�
 */
void ParticleEffect::Update()
{
	// �X�e�b�v�^�C�}�[�擾
	DX::StepTimer* stepTimer = GameResource::GetInstance()->GetStepTimer();
	// �^�C�}�[�i�s
	float elapsedTime = static_cast<float>(stepTimer->GetElapsedSeconds());
	m_generateTimer += elapsedTime;
	
	// ��������Ԋu�̎��Ԃ���������
	if (m_generateInterval < m_generateTimer)
	{
		// �^�C�}�[���Z�b�g
		m_generateTimer = 0.0f;
		std::unique_ptr<Particle> particle = std::move(m_generateFunction());
		// �p�[�e�B�N���ǉ�
		m_particleList.push_back(std::move(m_generateFunction()));
	}
	// �p�[�e�B�N���̍X�V
	for (ParticleList::iterator it = m_particleList.begin(); it != m_particleList.end();)
	{
		// �X�V
		(*it)->Update(elapsedTime);
		// ����ł�����폜����
		if ((*it)->IsAlive()) it++;
		else it = m_particleList.erase(it);
	}
}

//------------------------------------------------------------------
/**
 * @brief �`��
 *
 * @param view          �F�r���[�s��
 * @param projection    �F�ˉe�s��
 * @param eye           �F�J�����ʒu
 * @param target        �F�����_
 * @param up            �F�J�����̓��̌���
 * @return �Ȃ�
 */
void ParticleEffect::Render(DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix projection, DirectX::SimpleMath::Vector3 eye, DirectX::SimpleMath::Vector3 target, DirectX::SimpleMath::Vector3 up)
{
	// �J�����̕����x�N�g���v�Z
	SimpleMath::Vector3 cameraDir = target - eye;
	// �J�����̐��ʂŃ\�[�g���|����
	std::sort(m_particleList.begin(), m_particleList.end(),
		[&](std::unique_ptr<Particle>& lhs, std::unique_ptr<Particle>& rhs)
		{
			return cameraDir.Dot(lhs->GetPosition() - eye) > cameraDir.Dot(rhs->GetPosition() - eye);
		}
	);

	// �`�撸�_���X�g���Z�b�g
	m_vertices.clear();

	for (std::unique_ptr<Particle>& particle : m_particleList)
	{
		// �}�C�i�X�Ȃ�J�����̌��Ȃ̂ŕ`�悵�Ȃ�
		if (cameraDir.Dot(particle->GetPosition() - eye) < 0.0f) continue;

		// ���_�쐬
		VertexPositionColorTexture vertex;
		vertex.position          = particle->GetPosition(); // �ʒu
		vertex.color             = particle->GetColor();    // �F
		vertex.textureCoordinate = particle->GetScale();    // �傫��
		// ���_�ǉ�
		m_vertices.push_back(vertex);
	}

	// �`�悷�钸�_�������Ȃ�I��
	if (m_vertices.empty()) return;

	// �V�F�[�_�[�擾
	Shader<VertexPositionColorTexture>* shader = m_effectManager->GetShader();
	// �萔�o�b�t�@�̍X�V
	EffectManager::EffectConstantBuffer ecb;
	ecb.world      = CreateBillboard(eye, up).Transpose();
	ecb.view       = view.Transpose();
	ecb.projection = projection.Transpose();	
	shader->UpdateConstantBuffer(ecb);
	// �V�F�[�_�[�ɉ摜��ݒ肷��
	ResourceManager* resourceManager = GameResource::GetInstance()->GetResourceManager();
	shader->RegisterTexture(resourceManager->GetTexture(m_textureName).texture.GetAddressOf());

	// �`��
	shader->Render(&m_vertices[0], static_cast<int>(m_vertices.size()));
}

//------------------------------------------------------------------
/**
 * @brief �r���{�[�h�s��쐬
 *
 * @param eye�F�J�����ʒu
 * @param up �F�J�����̓��̌���
 * @return Matrix�F�쐬�����r���{�[�h�s��
 */
DirectX::SimpleMath::Matrix ParticleEffect::CreateBillboard(DirectX::SimpleMath::Vector3 eye, DirectX::SimpleMath::Vector3 up)
{
	// �r���{�[�h�s����쐬
	DirectX::SimpleMath::Matrix billboard = SimpleMath::Matrix::CreateBillboard(m_position, eye, up);

	// DirectX��TK�̍��W�n���Ⴄ�̂�Y����180�x��]
	SimpleMath::Matrix rot;
	rot._11 = rot._33 = -1.0f;

	return rot * billboard;
}

//------------------------------------------------------------------
/**
 * @brief �����Ԋu�ݒ�
 *
 * @param  generateInterval�F�ݒ肷�鐶���Ԋu
 * @return �Ȃ�
 */
void ParticleEffect::SetGenerateInterval(const float& generateInterval)
{
	m_generateInterval = generateInterval;
}

//------------------------------------------------------------------
/**
 * @brief �p�[�e�B�N�������֐��ݒ�
 *
 * @param  function�F�ݒ肷�鐶���֐�
 * @return �Ȃ�
 */
void ParticleEffect::SetGenerateFunction(const std::function<std::unique_ptr<Particle>()>& function)
{
	m_generateFunction = function;
}

//------------------------------------------------------------------
/**
 * @brief �ʒu�擾
 *
 * @param  �Ȃ�
 * @return Vector3�F�p�[�e�B�N���̈ʒu
 */
DirectX::SimpleMath::Vector3 ParticleEffect::GetPosition() const
{
	return m_position;
}