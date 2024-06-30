/**
 *
 * @file Window.h
 *
 * @brief �E�B���h�E�̂�\���N���X�̃w�b�_�[�t�@�C��
 *
 * @author Kato Yuki
 *
 * @date 2024/2/21
 *
 */
#pragma once

#include "PrimitiveBatch.h"
#include "VertexTypes.h"
#include "Game/MyLibrary/ResourceManager/ResourceType.h"

class Texture;
template<typename Vertex>
class Shader;

class Window
{
//----------------------------------------------
// �\����
//----------------------------------------------
private:

	// �萔�o�b�t�@
	struct WindowConstantBuffer
	{
		DirectX::SimpleMath::Vector4 windowSize;
	};

//----------------------------------------------
// �萔
//----------------------------------------------
private:

	// �w�i�p�|���S��
	DirectX::VertexPositionTexture VERTICES[4]
	{
		DirectX::VertexPositionTexture(DirectX::SimpleMath::Vector3(-1.0f,  1.0f, 0.0f), DirectX::SimpleMath::Vector2(0.0f, 0.0f)),
		DirectX::VertexPositionTexture(DirectX::SimpleMath::Vector3( 1.0f,  1.0f, 0.0f), DirectX::SimpleMath::Vector2(1.0f, 0.0f)),
		DirectX::VertexPositionTexture(DirectX::SimpleMath::Vector3( 1.0f, -1.0f, 0.0f), DirectX::SimpleMath::Vector2(1.0f, 1.0f)),
		DirectX::VertexPositionTexture(DirectX::SimpleMath::Vector3(-1.0f, -1.0f, 0.0f), DirectX::SimpleMath::Vector2(0.0f, 1.0f))
	};

//----------------------------------------------
// �ϐ�
//----------------------------------------------
private:

	// �E�B���h�E�̘g�摜
	std::unique_ptr<Texture> m_texture;
	// �E�B���h�E�T�C�Y
	DirectX::SimpleMath::Vector2 m_windowSize;
	// �`��ʒu
	DirectX::SimpleMath::Vector2 m_position;

	// �萔�o�b�t�@
	WindowConstantBuffer m_windowConstantBuffer;
	// ���j���[�E�B���h�E�p�V�F�[�_�[
	std::unique_ptr<Shader<DirectX::VertexPositionTexture>> m_menuWindowShader;
	// �w�i�p�V�F�[�_�[
	std::unique_ptr<Shader<DirectX::VertexPositionTexture>> m_menuBackGroundShader;

	// �E�B���h�E�̕\���t���O
	bool m_isOpen;

//----------------------------------------------
// �֐�
//----------------------------------------------
public:

	// �R���X�g���N�^
	Window(DirectX::SimpleMath::Vector2 windowSize, KT::Texture::TextureData texture, DirectX::SimpleMath::Vector2 position);
	// �f�X�g���N�^
	~Window();

	// ������
	void Initialize();
	// �`��
	void Render();
	// �E�B���h�E�`��
	void RenderWindow();
	// �w�i�`��
	void RenderBackGround();

	// �E�B���h�E���J���Ă��邩�m�F
	bool IsOpen();
	// �E�B���h�E���J��
	void Open();
	// �E�B���h�E�����
	void Close();
	// �E�B���h�E�̊J��
	void OpenClose();

	// �E�B���h�E�̈ʒu�擾
	const DirectX::SimpleMath::Vector2& GetPosition() const;
};