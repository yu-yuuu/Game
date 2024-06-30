/**
 *
 * @file Texture.cpp
 *
 * @brief �摜�N���X�̃\�[�X�t�@�C��
 *
 * @author Kato Yuki
 *
 * @date 2024/1/16
 *
 */
#include "pch.h"
#include "Texture.h"

using namespace DirectX;

//------------------------------------------------------------------
/**
 * @brief �R���X�g���N�^
 *
 * @param texture�F�e�N�X�`���f�[�^
 * @param anchor �F�A���J�[�|�C���g
 * @param scale  �F�X�P�[��
 * @param color  �F�e�N�X�`���̐F����
 */
Texture::Texture(
	KT::Texture::TextureData texture,
	AnchorPoint anchor,
	DirectX::SimpleMath::Vector2 scale,
	DirectX::SimpleMath::Color color
)
	: m_texture(texture)
	, m_anchor(anchor)
	, m_scale(scale)
	, m_color(color)
{
}

//------------------------------------------------------------------
/**
 * @brief �f�X�g���N�^
 */
Texture::~Texture()
{
}

//------------------------------------------------------------------
/**
 * @brief �e�N�X�`���f�[�^�擾
 *
 * @param �Ȃ�
 * @return TextureData�F�e�N�X�`���f�[�^
 */
KT::Texture::TextureData Texture::GetTexture() const
{
	return m_texture;
}

//------------------------------------------------------------------
/**
 * @brief �e�N�X�`���f�[�^�̐ݒ�
 *
 * @param  texture�F�ݒ肷��e�N�X�`���f�[�^
 * @return �Ȃ�
 */
void Texture::SetTexture(KT::Texture::TextureData texture)
{
	m_texture = texture;
}

//------------------------------------------------------------------
/**
 * @brief �V�F�[�_�[���\�[�X�r���[�̎擾
 *
 * @param �Ȃ�
 * @return ComPtr<ID3D11ShaderResourceView>�F�e�N�X�`���̃V�F�[�_�[���\�[�X�r���[
 */
const Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>& Texture::GetShaderResourceView() const
{
	return m_texture.texture;
}

//------------------------------------------------------------------
/**
 * @brief �e�N�X�`���̃T�C�Y�擾
 *
 * @param �Ȃ�
 * @return Vector2�F�e�N�X�`���̃T�C�Y
 */
const DirectX::SimpleMath::Vector2& Texture::GetTextureSize() const
{
	return m_texture.size;
}

//------------------------------------------------------------------
/**
 * @brief �A���J�[�|�C���g�擾
 *
 * @param �Ȃ�
 * @return AnchorPoint�F�A���J�[�|�C���g
 */
Texture::AnchorPoint Texture::GetAnchor() const
{
	return m_anchor;
}

//------------------------------------------------------------------
/**
 * @brief �A���J�[�|�C���g�ݒ�
 *
 * @param  anchor�F�ݒ肷��A���J�[�|�C���g
 * @return �Ȃ�
 */
void Texture::SetAnchor(AnchorPoint anchor)
{
	m_anchor = anchor;
}

//------------------------------------------------------------------
/**
 * @brief �X�P�[���̎擾
 *
 * @param  �Ȃ�
 * @return Vector2�F�摜�̃X�P�[��
 */
const DirectX::SimpleMath::Vector2& Texture::GetScale() const
{
	return m_scale;
}

//------------------------------------------------------------------
/**
 * @brief �X�P�[���̐ݒ�
 *
 * @param  scale�F�ݒ肷��X�P�[��
 * @return �Ȃ�
 */
void Texture::SetScale(const DirectX::SimpleMath::Vector2& scale)
{
	m_scale = scale;
}

//------------------------------------------------------------------
/**
 * @brief �e�N�X�`���Ɋ|����F�����擾
 *
 * @param  �Ȃ�
 * @return Color�F�e�N�X�`���Ɋ|����F����
 */
const DirectX::SimpleMath::Color& Texture::GetColor() const
{
	return m_color;
}

//------------------------------------------------------------------
/**
 * @brief �e�N�X�`���Ɋ|����F�����ݒ�(SimpleMath::Color)
 *
 * @param  color�F�ݒ肷��F����
 * @return �Ȃ�
 */
void Texture::SetColor(const DirectX::SimpleMath::Color& color)
{
	m_color = color;
}

 //------------------------------------------------------------------
 /**
  * @brief �e�N�X�`���Ɋ|����F�����ݒ�(SimpleMath::Vector3)
  *
  * @param  color�F�ݒ肷��F����
  * @return �Ȃ�
  */
void Texture::SetColor(const DirectX::SimpleMath::Vector3& color)
{
	  SetColor(color.x, color.y, color.z);
}

//------------------------------------------------------------------
/**
 * @brief �e�N�X�`���Ɋ|����F�����ݒ�
 *
 * @param  r�F�ݒ肷��F�̐Ԑ���
 * @param  g�F�ݒ肷��F�̗ΐ���
 * @param  b�F�ݒ肷��F�̐���
 * @param  a�F�ݒ肷��F�̓����x
 * @return �Ȃ�
 */
void Texture::SetColor(const float& r, const float& g, const float& b, const float& a)
{
	 SetColor(SimpleMath::Color(r, g, b, a));
}

//------------------------------------------------------------------
/**
 * @brief �e�N�X�`���Ɋ|����F�����ݒ�
 *
 * @param  r�F�ݒ肷��F�̐Ԑ���
 * @param  g�F�ݒ肷��F�̗ΐ���
 * @param  b�F�ݒ肷��F�̐���
 * @return �Ȃ�
 */
void Texture::SetColor(const float& r, const float& g, const float& b)
{
	SetColor(SimpleMath::Color(r, g, b, m_color.w));
}