/**
 *
 * @file UI.cpp
 *
 * @brief UIを表すクラスのソースファイル
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
 * @brief コンストラクタ
 *
 * @param tagList ：タグリスト
 * @param texture ：UIに使用する画像
 * @param position：UIの位置
 * @param reverseX：横を反転表示させるか
 * @param reverseY：縦を反転表示させるか
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
 * @brief デストラクタ
 */
UI::~UI()
{
}

//------------------------------------------------------------------
/**
 * @brief 更新
 *
 * @param  なし
 * @return なし
 */
void UI::Update()
{
}

//------------------------------------------------------------------
/**
 * @brief 描画
 *
 * @param  uiManager：UIマネージャーのポイント
 * @return なし
 */
void UI::Render(UIManager* uiManager)
{
	// 画像からデータを貰う
	KT::Texture::TextureData texture = m_texture->GetTexture();                  // 画像データ
	SimpleMath::Vector2      scale   = m_texture->GetScale();                    // 画像に掛けるスケール
	SimpleMath::Color        color   = m_texture->GetColor();                    // 色合い
	int                      anchor  = static_cast<int>(m_texture->GetAnchor()); // アンカーポイント
	// 頂点作成
	// position xy  ：描画位置, z：アンカーポイント, w：未使用
	// color    xyzw：画像の色合い
	// size     xy  ：画像サイズ, zw：画像のスケール
	// reverse  x   ：横を反転させるか, y：縦を反転させるか, zw：未使用
	UIManager::UIVertexData vertex
	{
		SimpleMath::Vector4(m_position.x, m_position.y, static_cast<float>(anchor), 0.0f),
		SimpleMath::Vector4(color),
		SimpleMath::Vector4(scale.x, scale.y, texture.size.x, texture.size.y),
		SimpleMath::Vector4(static_cast<float>(m_reverseX), static_cast<float>(m_reverseY), 0.0f, 0.0f)
	};
	// シェーダー受け取り
	Shader<UIManager::UIVertexData>* shader = uiManager->GetShader();
	shader->RegisterTexture(texture.texture.GetAddressOf());
	// 描画
	shader->Render(&vertex);
}

//------------------------------------------------------------------
/**
 * @brief タグリストの取得
 *
 * @param  なし
 * @return vector<string>：タグリスト
 */
std::vector<std::string> UI::GetTagList() const
{
	return m_tagList;
}

//------------------------------------------------------------------
/**
 * @brief テクスチャデータの取得
 *
 * @param  なし
 * @return Texture：テクスチャデータのポインタ
 */
Texture* UI::GetTexture() const
{
	return m_texture.get();
}

//------------------------------------------------------------------
/**
 * @brief テクスチャデータの設定
 *
 * @param  texture：設定するテクスチャデータ
 * @return なし
 */
void UI::SetTexture(std::unique_ptr<Texture> texture)
{
	m_texture = std::move(texture);
}

//------------------------------------------------------------------
/**
 * @brief 位置の取得
 *
 * @param  なし
 * @return Vector2：位置
 */
DirectX::SimpleMath::Vector2 UI::GetPosition() const
{
	return m_position;
}

//------------------------------------------------------------------
/**
 * @brief 位置の設定
 *
 * @param  position：設定する位置
 * @return なし
 */
void UI::SetPosition(const DirectX::SimpleMath::Vector2& position)
{
	m_position = position;
}