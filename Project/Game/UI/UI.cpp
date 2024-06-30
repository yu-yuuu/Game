/**
 *
 * @file UI.cpp
 *
 * @brief UI��\���N���X�̃\�[�X�t�@�C��
 *
 * @author Kato Yuki
 *
 * @date 2024/1/14
 *
 */
#include "pch.h"
#include "UI.h"
#include "Game/MyLibrary/Shader/Shader.h"

using namespace DirectX;

//------------------------------------------------------------------
/**
 * @brief �R���X�g���N�^
 *
 * @param tagList �F�^�O���X�g
 * @param texture �FUI�Ɏg�p����摜
 * @param position�FUI�̈ʒu
 * @param reverseX�F���𔽓]�\�������邩
 * @param reverseY�F�c�𔽓]�\�������邩
 */
UI::UI(
	const std::vector<std::string>& tagList,
	std::unique_ptr<Texture> texture,
	const DirectX::SimpleMath::Vector2& position, 
	bool reverseX, 
	bool reverseY
)
	: m_tagList(tagList)
	, m_texture(std::move(texture))
	, m_position(position)
	, m_reverseX(reverseX)
	, m_reverseY(reverseY)
{
}

//------------------------------------------------------------------
/**
 * @brief �f�X�g���N�^
 */
UI::~UI()
{
}

//------------------------------------------------------------------
/**
 * @brief �X�V
 *
 * @param  �Ȃ�
 * @return �Ȃ�
 */
void UI::Update()
{
}

//------------------------------------------------------------------
/**
 * @brief �`��
 *
 * @param  uiManager�FUI�}�l�[�W���[�̃|�C���g
 * @return �Ȃ�
 */
void UI::Render(UIManager* uiManager)
{
	// �摜����f�[�^��Ⴄ
	KT::Texture::TextureData texture = m_texture->GetTexture();                  // �摜�f�[�^
	SimpleMath::Vector2      scale   = m_texture->GetScale();                    // �摜�Ɋ|����X�P�[��
	SimpleMath::Color        color   = m_texture->GetColor();                    // �F����
	int                      anchor  = static_cast<int>(m_texture->GetAnchor()); // �A���J�[�|�C���g
	// ���_�쐬
	// position xy  �F�`��ʒu, z�F�A���J�[�|�C���g, w�F���g�p
	// color    xyzw�F�摜�̐F����
	// size     xy  �F�摜�T�C�Y, zw�F�摜�̃X�P�[��
	// reverse  x   �F���𔽓]�����邩, y�F�c�𔽓]�����邩, zw�F���g�p
	UIManager::UIVertexData vertex
	{
		SimpleMath::Vector4(m_position.x, m_position.y, static_cast<float>(anchor), 0.0f),
		SimpleMath::Vector4(color),
		SimpleMath::Vector4(scale.x, scale.y, texture.size.x, texture.size.y),
		SimpleMath::Vector4(static_cast<float>(m_reverseX), static_cast<float>(m_reverseY), 0.0f, 0.0f)
	};
	// �V�F�[�_�[�󂯎��
	Shader<UIManager::UIVertexData>* shader = uiManager->GetShader();
	shader->RegisterTexture(texture.texture.GetAddressOf());
	// �`��
	shader->Render(&vertex);
}

//------------------------------------------------------------------
/**
 * @brief �^�O���X�g�̎擾
 *
 * @param  �Ȃ�
 * @return vector<string>�F�^�O���X�g
 */
std::vector<std::string> UI::GetTagList() const
{
	return m_tagList;
}

//------------------------------------------------------------------
/**
 * @brief �e�N�X�`���f�[�^�̎擾
 *
 * @param  �Ȃ�
 * @return Texture�F�e�N�X�`���f�[�^�̃|�C���^
 */
Texture* UI::GetTexture() const
{
	return m_texture.get();
}

//------------------------------------------------------------------
/**
 * @brief �e�N�X�`���f�[�^�̐ݒ�
 *
 * @param  texture�F�ݒ肷��e�N�X�`���f�[�^
 * @return �Ȃ�
 */
void UI::SetTexture(std::unique_ptr<Texture> texture)
{
	m_texture = std::move(texture);
}

//------------------------------------------------------------------
/**
 * @brief �ʒu�̎擾
 *
 * @param  �Ȃ�
 * @return Vector2�F�ʒu
 */
DirectX::SimpleMath::Vector2 UI::GetPosition() const
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
void UI::SetPosition(const DirectX::SimpleMath::Vector2& position)
{
	m_position = position;
}