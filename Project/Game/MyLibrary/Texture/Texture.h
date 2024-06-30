/**
 *
 * @file Texture.h
 *
 * @brief 画像クラスのヘッダーファイル
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
// 列挙体
//----------------------------------------------
public:

	// 画像のアンカーポイント
	enum class AnchorPoint
	{
		TOP_LEFT,       // 左上
		TOP_CENTER,     // 中央上
		TOP_RIGHT,      // 右上
		CENTER_LEFT,    // 中央左
		CENTER,         // 中央
		CENTER_RIGHT,   // 中央右
		BOTTOM_LEFT,    // 左下
		BOTTOM_CENTER,  // 中央下
		BOTTOM_RIGHT,	// 右下
	};

//----------------------------------------------
// 変数
//----------------------------------------------
private:

	// 画像データ
	KT::Texture::TextureData m_texture;
	// アンカーポイント
	AnchorPoint m_anchor;
	// スケール
	DirectX::SimpleMath::Vector2 m_scale;
	// テクスチャの色合い
	DirectX::SimpleMath::Color m_color;

//----------------------------------------------
// 関数
//----------------------------------------------
public:

	// コンストラクタ
	Texture(
		KT::Texture::TextureData texture,
		AnchorPoint anchor = AnchorPoint::CENTER,
		DirectX::SimpleMath::Vector2 scale = DirectX::SimpleMath::Vector2::One,
		DirectX::SimpleMath::Color color = DirectX::SimpleMath::Color(1.0f, 1.0f, 1.0f, 1.0f)
	);
	// デストラクタ
	~Texture();

	// テクスチャデータの取得、設定
	KT::Texture::TextureData GetTexture() const;
	void SetTexture(KT::Texture::TextureData texture);
	// ShaderResourceViewの取得
	const Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>& GetShaderResourceView() const;
	// テクスチャサイズの取得
	const DirectX::SimpleMath::Vector2& GetTextureSize() const;
	// アンカーポイントの取得、設定
	AnchorPoint GetAnchor() const;
	void SetAnchor(AnchorPoint anchor);
	// スケールの取得、設定
	const DirectX::SimpleMath::Vector2& GetScale() const;
	void SetScale(const DirectX::SimpleMath::Vector2& scale);
	// 色の取得、設定
	const DirectX::SimpleMath::Color& GetColor() const;
	void SetColor(const DirectX::SimpleMath::Color& color);
	void SetColor(const DirectX::SimpleMath::Vector3& color);
	void SetColor(const float& r, const float& g, const float& b, const float& a);
	void SetColor(const float& r, const float& g, const float& b);
};