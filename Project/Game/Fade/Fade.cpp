/**
 *
 * @file Fade.cpp
 *
 * @brief �t�F�[�h�������s���N���X�̃t�H�[�X�t�@�C��
 *
 * @author Kato Yuki
 *
 * @date 2023/9/12
 *
 */
#include "pch.h"
#include "Fade.h"
#include "Game/MyLibrary/CommonResource/GameResource.h"
#include "Game/MyLibrary/Shader/Shader.h"

using namespace DirectX;

//------------------------------------------------------------------
/**
 * @brief �R���X�g���N�^
 *
 * @param �Ȃ�
 */
Fade::Fade()
	: m_fadeState(FadeState::STAY)
	, m_prevFadeState(FadeState::STAY)
	, m_currentTime(0.0f)
	, m_shader(nullptr)
{
}

//------------------------------------------------------------------
/**
 * @brief �f�X�g���N�^
 */
Fade::~Fade()
{
	m_shader.reset();
}

//------------------------------------------------------------------
 /**
 * @brief ������
 *
 * @param  �Ȃ�
 * @return �Ȃ�
 */
void Fade::Initialize()
{
	// �V�F�[�_�[�̍쐬
	m_shader = std::make_unique<Shader<VertexPosition>>();
	m_shader->CreateData(KT::Shader::FADE);
	m_shader->CreateConstantBuffer<FadeConstantBuffer>();
}

//------------------------------------------------------------------
 /**
 * @brief �X�V
 *
 * @param elapsedTime�F�P�t���[���ɂ�����b��
 * @return �Ȃ�
 */
void Fade::Update(const float& elapsedTime)
{
	// ���݂̃t�F�[�h��Ԃ�ۑ�
	m_prevFadeState = m_fadeState;
	// �t�F�[�h��ԂłȂ���ΏI��
	if (m_fadeState == FadeState::STAY) return;

	// �t�F�[�h�C�����
	if (m_fadeState == FadeState::FADE_IN)
	{
		// �t�F�[�h�i�s
		m_currentTime -= elapsedTime;	
		// �t�F�[�h�C�����I�����Ă��邩�m�F
		if (m_currentTime > 0.0f) return;

		// �^�C�}�[�̒l���s�b�^���ɂȂ�悤�ɒ���
		m_currentTime = 0.0f;
		// �ҋ@��Ԃ�
		m_fadeState = FadeState::STAY;
	}
	// �t�F�[�h�A�E�g���
	else
	{
		// �t�F�[�h�i�s
		m_currentTime += elapsedTime;
		// �t�F�[�h�A�E�g���I�����Ă��邩�m�F
		if (m_currentTime <= FADE_TIMER) return;

		// �^�C�}�[�̒l���s�b�^���ɂȂ�悤�ɒ���
		m_currentTime = FADE_TIMER;
		// �t�F�[�h�C���҂���Ԃ�
		m_fadeState = FadeState::FADE_IN_WAIT;
	}
}

//------------------------------------------------------------------
 /**
 * @brief �`��
 *
 * @param  �Ȃ�
 * @return �Ȃ�
 */
void Fade::Render()
{
	// �萔�o�b�t�@�X�V
	FadeConstantBuffer cbuf;
	cbuf.rate = SimpleMath::Vector4(m_currentTime / FADE_TIMER, 0.0f, 0.0f, 0.0f);
	m_shader->UpdateConstantBuffer(cbuf);
	// �`��
	m_shader->RenderQuad(VERTICES[0], VERTICES[1], VERTICES[2], VERTICES[3]);
}

//------------------------------------------------------------------
 /**
 * @brief �t�F�[�h�C���J�n
 *
 * @param  �Ȃ�
 * @return �Ȃ�
 */
void Fade::StartFadeIn()
{
	// �t�F�[�h�C���҂��ȊO�Ȃ珈�����s��Ȃ�
	if (!CheckFadeState(FadeState::FADE_IN_WAIT)) return;

	// �t�F�[�h�C����Ԃֈڍs
	m_fadeState = FadeState::FADE_IN;
	m_currentTime = FADE_TIMER;
}

//------------------------------------------------------------------
 /**
 * @brief �t�F�[�h�A�E�g�J�n
 *
 * @param  �Ȃ�
 * @return �Ȃ�
 */
void Fade::StartFadeOut()
{
	// �ҋ@���ȊO�Ȃ珈�����s��Ȃ�
	if (!CheckFadeState(FadeState::STAY)) return;

	// �t�F�[�h�A�E�g��Ԃֈڍs
	m_fadeState = FadeState::FADE_OUT;
	m_currentTime = 0.0f;
}

//------------------------------------------------------------------
 /**
 * @brief �t�F�[�h��Ԃ̊m�F
 *
 * @param  state�F�m�F�������t�F�[�h���
 * @return true �F��v
 * @return false�F�s��v
 */
bool Fade::CheckFadeState(FadeState state)
{
	return m_fadeState == state;
}

//------------------------------------------------------------------
/**
 * @brief �t�F�[�h��Ԃ��ǂ����m�F
 *
 * @param  �Ȃ�
 * @return true �F�t�F�[�h��
 * @return false�F�t�F�[�h���Ă��Ȃ�
 */
bool Fade::IsFade()
{
	return m_fadeState != FadeState::STAY;
}

//------------------------------------------------------------------
/**
 * @brief �t�F�[�h�C�����I�������u�Ԃ�
 *
 * @param  �Ȃ�
 * @return true �F�I�������u��
 * @return false�F�u�ԂłȂ�
 */
bool Fade::IsFadeInFinish()
{
	return m_fadeState == FadeState::STAY && m_prevFadeState == FadeState::FADE_IN;
}