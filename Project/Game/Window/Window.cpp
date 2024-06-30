/**
 *
 * @file Window.cpp
 *
 * @brief �E�B���h�E�̂�\���N���X�̃\�[�X�t�@�C��
 *
 * @author Kato Yuki
 *
 * @date 2024/2/21
 *
 */
#include "pch.h"
#include "Window.h"
#include "Game/MyLibrary/CommonResource/GameResource.h"
#include "Game/MyLibrary/Texture/Texture.h"
#include "Game/MyLibrary/Shader/Shader.h"

using namespace DirectX;

//------------------------------------------------------------------
/**
 * @brief �R���X�g���N�^
 *
 * @param windowSize�F�E�B���h�E�̑傫��
 * @param texture   �F�E�B���h�E�Ɏg�p����e�N�X�`��
 * @param position  �F�`��ʒu
 */
Window::Window(
	DirectX::SimpleMath::Vector2 windowSize, 
	KT::Texture::TextureData texture, 
	DirectX::SimpleMath::Vector2 position)
	: m_texture(std::make_unique<Texture>(texture))
	, m_windowSize(windowSize)
	, m_position(position)
	, m_isOpen(false)
{
}

//------------------------------------------------------------------
/**
 * @brief �f�X�g���N�^
 */
Window::~Window()
{
}

//------------------------------------------------------------------
/**
 * @brief ������
 *
 * @param  �Ȃ�
 * @return �Ȃ�
 */
void Window::Initialize()
{
	// �V�F�[�_�[�쐬
	m_menuWindowShader = std::make_unique<Shader<VertexPositionTexture>>();
	m_menuWindowShader->CreateData(KT::Shader::WINDOW);
	m_menuWindowShader->CreateConstantBuffer<WindowConstantBuffer>();
	m_menuBackGroundShader = std::make_unique<Shader<VertexPositionTexture>>();
	m_menuBackGroundShader->CreateData(KT::Shader::MENU_BACKGROUND);
	m_menuBackGroundShader->CreateConstantBuffer<WindowConstantBuffer>();
	// �萔�o�b�t�@�ɃE�B���h�E�T�C�Y��ݒ�
	DX::DeviceResources* deviceResources = GameResource::GetInstance()->GetDeviceResources();
	RECT window = deviceResources->GetOutputSize();
	m_windowConstantBuffer.windowSize.x = static_cast<float>(window.right);
	m_windowConstantBuffer.windowSize.y = static_cast<float>(window.bottom);
}

//------------------------------------------------------------------
/**
 * @brief �`��
 *
 * @param  �Ȃ�
 * @return �Ȃ�
 */
void Window::Render()
{
	// �E�B���h�E���J���ĂȂ��Ȃ�I��
	if (!m_isOpen) return;

	// �w�i�̕`��
	RenderBackGround();
	// �E�B���h�E�̕`��
	RenderWindow();
}

//------------------------------------------------------------------
/**
 * @brief �E�B���h�E�̔w�i
 *
 * @param  �Ȃ�
 * @return �Ȃ�
 */
void Window::RenderWindow()
{
	// ���_�쐬
	VertexPositionTexture vertex = VertexPositionTexture
	(
		SimpleMath::Vector3(m_position.x, m_position.y, static_cast<float>(m_texture->GetAnchor())),
		SimpleMath::Vector2(m_windowSize)
	);
	// �萔�o�b�t�@�X�V
	m_menuWindowShader->UpdateConstantBuffer(m_windowConstantBuffer);
	// �s�N�Z���V�F�[�_�[�ɉ摜��ݒ�
	CommonStates* commonStates = GameResource::GetInstance()->GetCommonStates();
	std::vector<ID3D11SamplerState*> sampler = { commonStates->PointWrap() };
	m_menuWindowShader->RegisterTexture(m_texture->GetTexture().texture.GetAddressOf(), sampler);

	// �`��
	m_menuWindowShader->Render(&vertex);
}

//------------------------------------------------------------------
/**
 * @brief �w�i�`��
 *
 * @param  �Ȃ�
 * @return �Ȃ�
 */
void Window::RenderBackGround()
{
	// �`��
	m_menuBackGroundShader->RenderQuad(VERTICES[0], VERTICES[1], VERTICES[2], VERTICES[3]);
}

//------------------------------------------------------------------
/**
 * @brief �E�B���h�E���J���Ă��邩�m�F
 *
 * @param �Ȃ�
 * @return true �F�J���Ă���
 * @return false�F���Ă���
 */
bool Window::IsOpen()
{
	return m_isOpen;
}

//------------------------------------------------------------------
/**
 * @brief �E�B���h�E���J��
 *
 * @param  �Ȃ�
 * @return �Ȃ�
 */
void Window::Open()
{
	m_isOpen = true;
}

//------------------------------------------------------------------
/**
 * @brief �E�B���h�E�����
 *
 * @param  �Ȃ�
 * @return �Ȃ�
 */
void Window::Close()
{
	m_isOpen = false;
}

//------------------------------------------------------------------
/**
 * @brief �E�B���h�E�̊J��
 *
 * @param  �Ȃ�
 * @return �Ȃ�
 */
void Window::OpenClose()
{
	m_isOpen = !m_isOpen;
}

//------------------------------------------------------------------
/**
 * @brief �E�B���h�E�̈ʒu�擾
 *
 * @param  �Ȃ�
 * @return Vector2�F�`��ʒu
 */
const DirectX::SimpleMath::Vector2& Window::GetPosition() const
{
	return m_position;
}