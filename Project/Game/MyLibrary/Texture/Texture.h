/**
 *
 * @file Texture.h
 *
 * @brief �摜�N���X�̃w�b�_�[�t�@�C��
 *
 * @author Kato Yuki
 *
 * @date 2024/1/16
 *
 */
#pragma once

#include "Game/MyLibrary/ResourceManager/ResourceType.h"

class Texture
{
//----------------------------------------------
// �񋓑�
//----------------------------------------------
public:

	// �摜�̃A���J�[�|�C���g
	enum class AnchorPoint
	{
		TOP_LEFT,       // ����
		TOP_CENTER,     // ������
		TOP_RIGHT,      // �E��
		CENTER_LEFT,    // ������
		CENTER,         // ����
		CENTER_RIGHT,   // �����E
		BOTTOM_LEFT,    // ����
		BOTTOM_CENTER,  // ������
		BOTTOM_RIGHT,	// �E��
	};

//----------------------------------------------
// �ϐ�
//----------------------------------------------
private:

	// �摜�f�[�^
	KT::Texture::TextureData m_texture;
	// �A���J�[�|�C���g
	AnchorPoint m_anchor;
	// �X�P�[��
	DirectX::SimpleMath::Vector2 m_scale;
	// �e�N�X�`���̐F����
	DirectX::SimpleMath::Color m_color;

//----------------------------------------------
// �֐�
//----------------------------------------------
public:

	// �R���X�g���N�^
	Texture(
		KT::Texture::TextureData texture,
		AnchorPoint anchor = AnchorPoint::CENTER,
		DirectX::SimpleMath::Vector2 scale = DirectX::SimpleMath::Vector2::One,
		DirectX::SimpleMath::Color color = DirectX::SimpleMath::Color(1.0f, 1.0f, 1.0f, 1.0f)
	);
	// �f�X�g���N�^
	~Texture();

	// �e�N�X�`���f�[�^�̎擾�A�ݒ�
	KT::Texture::TextureData GetTexture() const;
	void SetTexture(KT::Texture::TextureData texture);
	// ShaderResourceView�̎擾
	const Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>& GetShaderResourceView() const;
	// �e�N�X�`���T�C�Y�̎擾
	const DirectX::SimpleMath::Vector2& GetTextureSize() const;
	// �A���J�[�|�C���g�̎擾�A�ݒ�
	AnchorPoint GetAnchor() const;
	void SetAnchor(AnchorPoint anchor);
	// �X�P�[���̎擾�A�ݒ�
	const DirectX::SimpleMath::Vector2& GetScale() const;
	void SetScale(const DirectX::SimpleMath::Vector2& scale);
	// �F�̎擾�A�ݒ�
	const DirectX::SimpleMath::Color& GetColor() const;
	void SetColor(const DirectX::SimpleMath::Color& color);
	void SetColor(const DirectX::SimpleMath::Vector3& color);
	void SetColor(const float& r, const float& g, const float& b, const float& a);
	void SetColor(const float& r, const float& g, const float& b);
};