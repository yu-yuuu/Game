/**
 *
 * @file Window.h
 *
 * @brief ウィンドウのを表すクラスのヘッダーファイル
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
// 構造体
//----------------------------------------------
private:

	// 定数バッファ
	struct WindowConstantBuffer
	{
		DirectX::SimpleMath::Vector4 windowSize;
	};

//----------------------------------------------
// 定数
//----------------------------------------------
private:

	// 背景用板ポリゴン
	DirectX::VertexPositionTexture VERTICES[4]
	{
		DirectX::VertexPositionTexture(DirectX::SimpleMath::Vector3(-1.0f,  1.0f, 0.0f), DirectX::SimpleMath::Vector2(0.0f, 0.0f)),
		DirectX::VertexPositionTexture(DirectX::SimpleMath::Vector3( 1.0f,  1.0f, 0.0f), DirectX::SimpleMath::Vector2(1.0f, 0.0f)),
		DirectX::VertexPositionTexture(DirectX::SimpleMath::Vector3( 1.0f, -1.0f, 0.0f), DirectX::SimpleMath::Vector2(1.0f, 1.0f)),
		DirectX::VertexPositionTexture(DirectX::SimpleMath::Vector3(-1.0f, -1.0f, 0.0f), DirectX::SimpleMath::Vector2(0.0f, 1.0f))
	};

//----------------------------------------------
// 変数
//----------------------------------------------
private:

	// ウィンドウの枠画像
	std::unique_ptr<Texture> m_texture;
	// ウィンドウサイズ
	DirectX::SimpleMath::Vector2 m_windowSize;
	// 描画位置
	DirectX::SimpleMath::Vector2 m_position;

	// 定数バッファ
	WindowConstantBuffer m_windowConstantBuffer;
	// メニューウィンドウ用シェーダー
	std::unique_ptr<Shader<DirectX::VertexPositionTexture>> m_menuWindowShader;
	// 背景用シェーダー
	std::unique_ptr<Shader<DirectX::VertexPositionTexture>> m_menuBackGroundShader;

	// ウィンドウの表示フラグ
	bool m_isOpen;

//----------------------------------------------
// 関数
//----------------------------------------------
public:

	// コンストラクタ
	Window(DirectX::SimpleMath::Vector2 windowSize, KT::Texture::TextureData texture, DirectX::SimpleMath::Vector2 position);
	// デストラクタ
	~Window();

	// 初期化
	void Initialize();
	// 描画
	void Render();
	// ウィンドウ描画
	void RenderWindow();
	// 背景描画
	void RenderBackGround();

	// ウィンドウが開いているか確認
	bool IsOpen();
	// ウィンドウを開く
	void Open();
	// ウィンドウを閉じる
	void Close();
	// ウィンドウの開閉
	void OpenClose();

	// ウィンドウの位置取得
	const DirectX::SimpleMath::Vector2& GetPosition() const;
};