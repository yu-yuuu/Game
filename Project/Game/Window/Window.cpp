/**
 *
 * @file Window.cpp
 *
 * @brief ウィンドウのを表すクラスのソースファイル
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
 * @brief コンストラクタ
 *
 * @param windowSize：ウィンドウの大きさ
 * @param texture   ：ウィンドウに使用するテクスチャ
 * @param position  ：描画位置
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
 * @brief デストラクタ
 */
Window::~Window()
{
}

//------------------------------------------------------------------
/**
 * @brief 初期化
 *
 * @param  なし
 * @return なし
 */
void Window::Initialize()
{
	// シェーダー作成
	m_menuWindowShader = std::make_unique<Shader<VertexPositionTexture>>();
	m_menuWindowShader->CreateData(KT::Shader::WINDOW);
	m_menuWindowShader->CreateConstantBuffer<WindowConstantBuffer>();
	m_menuBackGroundShader = std::make_unique<Shader<VertexPositionTexture>>();
	m_menuBackGroundShader->CreateData(KT::Shader::MENU_BACKGROUND);
	m_menuBackGroundShader->CreateConstantBuffer<WindowConstantBuffer>();
	// 定数バッファにウィンドウサイズを設定
	DX::DeviceResources* deviceResources = GameResource::GetInstance()->GetDeviceResources();
	RECT window = deviceResources->GetOutputSize();
	m_windowConstantBuffer.windowSize.x = static_cast<float>(window.right);
	m_windowConstantBuffer.windowSize.y = static_cast<float>(window.bottom);
}

//------------------------------------------------------------------
/**
 * @brief 描画
 *
 * @param  なし
 * @return なし
 */
void Window::Render()
{
	// ウィンドウが開いてないなら終了
	if (!m_isOpen) return;

	// 背景の描画
	RenderBackGround();
	// ウィンドウの描画
	RenderWindow();
}

//------------------------------------------------------------------
/**
 * @brief ウィンドウの背景
 *
 * @param  なし
 * @return なし
 */
void Window::RenderWindow()
{
	// 頂点作成
	VertexPositionTexture vertex = VertexPositionTexture
	(
		SimpleMath::Vector3(m_position.x, m_position.y, static_cast<float>(m_texture->GetAnchor())),
		SimpleMath::Vector2(m_windowSize)
	);
	// 定数バッファ更新
	m_menuWindowShader->UpdateConstantBuffer(m_windowConstantBuffer);
	// ピクセルシェーダーに画像を設定
	CommonStates* commonStates = GameResource::GetInstance()->GetCommonStates();
	std::vector<ID3D11SamplerState*> sampler = { commonStates->PointWrap() };
	m_menuWindowShader->RegisterTexture(m_texture->GetTexture().texture.GetAddressOf(), sampler);

	// 描画
	m_menuWindowShader->Render(&vertex);
}

//------------------------------------------------------------------
/**
 * @brief 背景描画
 *
 * @param  なし
 * @return なし
 */
void Window::RenderBackGround()
{
	// 描画
	m_menuBackGroundShader->RenderQuad(VERTICES[0], VERTICES[1], VERTICES[2], VERTICES[3]);
}

//------------------------------------------------------------------
/**
 * @brief ウィンドウが開いているか確認
 *
 * @param なし
 * @return true ：開いている
 * @return false：閉じている
 */
bool Window::IsOpen()
{
	return m_isOpen;
}

//------------------------------------------------------------------
/**
 * @brief ウィンドウを開く
 *
 * @param  なし
 * @return なし
 */
void Window::Open()
{
	m_isOpen = true;
}

//------------------------------------------------------------------
/**
 * @brief ウィンドウを閉じる
 *
 * @param  なし
 * @return なし
 */
void Window::Close()
{
	m_isOpen = false;
}

//------------------------------------------------------------------
/**
 * @brief ウィンドウの開閉
 *
 * @param  なし
 * @return なし
 */
void Window::OpenClose()
{
	m_isOpen = !m_isOpen;
}

//------------------------------------------------------------------
/**
 * @brief ウィンドウの位置取得
 *
 * @param  なし
 * @return Vector2：描画位置
 */
const DirectX::SimpleMath::Vector2& Window::GetPosition() const
{
	return m_position;
}