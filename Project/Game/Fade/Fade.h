/**
 *
 * @file Fade.h
 *
 * @brief �t�F�[�h�������s���N���X�̃w�b�_�[�t�@�C��
 *
 * @author Kato Yuki
 *
 * @date 2023/9/12
 *
 */
#pragma once
#include "VertexTypes.h"

template<typename Vertex>
class Shader;

class Fade
{
//----------------------------------------------
// �\���́A�񋓑�
//----------------------------------------------
public:
	
	// �t�F�[�h�̏��
	enum class FadeState
	{
		FADE_IN,		// �t�F�[�h�C��
		FADE_IN_WAIT,	// �t�F�[�h�C���҂�
		FADE_OUT,		// �t�F�[�h�A�E�g
		STAY,			// �ҋ@
	};

private:

	// �t�F�[�h�Ɏg�p����萔�o�b�t�@
	struct FadeConstantBuffer
	{
		DirectX::SimpleMath::Vector4 rate;// �t�F�[�h�̊���
	};

//----------------------------------------------
// �萔
//----------------------------------------------
private:

	// �t�F�[�h�ɂ����鎞��
	const float FADE_TIMER = 1.0f;
	// �`��Ɏg�p����|���S��
	const DirectX::VertexPosition VERTICES[4] =
	{
		DirectX::VertexPosition(DirectX::SimpleMath::Vector3(-1.0f,  1.0f, 0.0f)), // ����
		DirectX::VertexPosition(DirectX::SimpleMath::Vector3(1.0f,  1.0f, 0.0f)),  // �E��
		DirectX::VertexPosition(DirectX::SimpleMath::Vector3(1.0f, -1.0f, 0.0f)),  // �E��
		DirectX::VertexPosition(DirectX::SimpleMath::Vector3(-1.0f, -1.0f, 0.0f))  // ����
	};

//----------------------------------------------
// �ϐ�
//----------------------------------------------
private:

	// �t�F�[�h���
	FadeState m_fadeState;
	// �P�t���[���O�̃t�F�[�h���
	FadeState m_prevFadeState;
  	// ���݂̃t�F�[�h����
  	// ( 0 �` FADE_TIMER )
	float m_currentTime;
	// �V�F�[�_�[
	std::unique_ptr<Shader<DirectX::VertexPosition>> m_shader;

//----------------------------------------------
// �֐�
//----------------------------------------------
public:

	// �R���X�g���N�^
	Fade();
	// �f�X�g���N�^
	~Fade();

	// ������
	void Initialize();
	// �X�V
	void Update(const float& elapsedTime);
	// �`��
	void Render();

	// �t�F�[�h�C���J�n
	void StartFadeIn();
	// �t�F�[�h�A�E�g�J�n
	void StartFadeOut();

	// �t�F�[�h��Ԃ̊m�F
	bool CheckFadeState(FadeState state);
	// �t�F�[�h��Ԃ��ǂ����m�F
	bool IsFade();
	// �t�F�[�h�C�����I�������u�Ԃ�
	bool IsFadeInFinish();
};