/**
 *
 * @file Texture.cpp
 *
 * @brief 画像クラスのソースファイル
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
 * @brief コンストラクタ
 *
 * @param texture：テクスチャデータ
 * @param anchor ：アンカーポイント
 * @param scale  ：スケール
 * @param color  ：テクスチャの色合い
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
 * @brief デストラクタ
 */
Texture::~Texture()
{
}

//------------------------------------------------------------------
/**
 * @brief テクスチャデータ取得
 *
 * @param なし
 * @return TextureData：テクスチャデータ
 */
KT::Texture::TextureData Texture::GetTexture() const
{
	return m_texture;
}

//------------------------------------------------------------------
/**
 * @brief テクスチャデータの設定
 *
 * @param  texture：設定するテクスチャデータ
 * @return なし
 */
void Texture::SetTexture(KT::Texture::TextureData texture)
{
	m_texture = texture;
}

//------------------------------------------------------------------
/**
 * @brief シェーダーリソースビューの取得
 *
 * @param なし
 * @return ComPtr<ID3D11ShaderResourceView>：テクスチャのシェーダーリソースビュー
 */
const Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>& Texture::GetShaderResourceView() const
{
	return m_texture.texture;
}

//------------------------------------------------------------------
/**
 * @brief テクスチャのサイズ取得
 *
 * @param なし
 * @return Vector2：テクスチャのサイズ
 */
const DirectX::SimpleMath::Vector2& Texture::GetTextureSize() const
{
	return m_texture.size;
}

//------------------------------------------------------------------
/**
 * @brief アンカーポイント取得
 *
 * @param なし
 * @return AnchorPoint：アンカーポイント
 */
Texture::AnchorPoint Texture::GetAnchor() const
{
	return m_anchor;
}

//------------------------------------------------------------------
/**
 * @brief アンカーポイント設定
 *
 * @param  anchor：設定するアンカーポイント
 * @return なし
 */
void Texture::SetAnchor(AnchorPoint anchor)
{
	m_anchor = anchor;
}

//------------------------------------------------------------------
/**
 * @brief スケールの取得
 *
 * @param  なし
 * @return Vector2：画像のスケール
 */
const DirectX::SimpleMath::Vector2& Texture::GetScale() const
{
	return m_scale;
}

//------------------------------------------------------------------
/**
 * @brief スケールの設定
 *
 * @param  scale：設定するスケール
 * @return なし
 */
void Texture::SetScale(const DirectX::SimpleMath::Vector2& scale)
{
	m_scale = scale;
}

//------------------------------------------------------------------
/**
 * @brief テクスチャに掛ける色合い取得
 *
 * @param  なし
 * @return Color：テクスチャに掛ける色合い
 */
const DirectX::SimpleMath::Color& Texture::GetColor() const
{
	return m_color;
}

//------------------------------------------------------------------
/**
 * @brief テクスチャに掛ける色合い設定(SimpleMath::Color)
 *
 * @param  color：設定する色合い
 * @return なし
 */
void Texture::SetColor(const DirectX::SimpleMath::Color& color)
{
	m_color = color;
}

 //------------------------------------------------------------------
 /**
  * @brief テクスチャに掛ける色合い設定(SimpleMath::Vector3)
  *
  * @param  color：設定する色合い
  * @return なし
  */
void Texture::SetColor(const DirectX::SimpleMath::Vector3& color)
{
	  SetColor(color.x, color.y, color.z);
}

//------------------------------------------------------------------
/**
 * @brief テクスチャに掛ける色合い設定
 *
 * @param  r：設定する色の赤成分
 * @param  g：設定する色の緑成分
 * @param  b：設定する色の青成分
 * @param  a：設定する色の透明度
 * @return なし
 */
void Texture::SetColor(const float& r, const float& g, const float& b, const float& a)
{
	 SetColor(SimpleMath::Color(r, g, b, a));
}

//------------------------------------------------------------------
/**
 * @brief テクスチャに掛ける色合い設定
 *
 * @param  r：設定する色の赤成分
 * @param  g：設定する色の緑成分
 * @param  b：設定する色の青成分
 * @return なし
 */
void Texture::SetColor(const float& r, const float& g, const float& b)
{
	SetColor(SimpleMath::Color(r, g, b, m_color.w));
}