//--------------------------------------------------------------------------------------
// File: DebugFont.cpp
//
// デバッグ用文字フォント描画クラス
//
// Date: 2023.3.13
// Author: Hideyasu Imase
//--------------------------------------------------------------------------------------
#include "pch.h"
#include "DebugFont.h"
#include "DirectXHelpers.h"
#include "VertexTypes.h"

using namespace DirectX;
using namespace Imase;

// コンストラクタ
DebugFont::DebugFont(ID3D11Device* device, ID3D11DeviceContext* context, wchar_t const* fileName)
	: m_fontHeight{}
{
	m_spriteBatch = std::make_unique<SpriteBatch>(context);
	m_spriteFont = std::make_unique<DirectX::SpriteFont>(device, fileName);

	// フォントの縦サイズを取得する
	SimpleMath::Vector2 textSize = m_spriteFont->MeasureString("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz");
	m_fontHeight = textSize.y;

	m_viewChannel = 0;
}

// デストラクタ
DebugFont::~DebugFont()
{
	m_spriteFont.reset();
	m_spriteBatch.reset();
}

void Imase::DebugFont::AddString(const int& channel, const std::string& string)
{
	// 文字の型変換
	std::wstring wide(string.begin(), string.end());

	m_stringList[channel].push_back(wide.c_str());
}

void Imase::DebugFont::AddString(const int& channel, const wchar_t* str)
{
	m_stringList[channel].push_back(str);
}

void Imase::DebugFont::AddString(const int& channel, const std::string& str, const DirectX::SimpleMath::Vector3& vec)
{
	std::string s =
		str +
		"( X : " + std::to_string(vec.x) + ", " +
		"Y : " + std::to_string(vec.y) + ", " +
		"Z : " + std::to_string(vec.z) + " )";

	std::wstring wide(s.begin(), s.end());
	m_stringList[channel].push_back(wide.c_str());
}



// 描画関数
void DebugFont::Render(DirectX::CommonStates* states)
{

	ChannelChange();

	// チャンネル番号を文字に変換する
	std::string str = "Channel : " + std::to_string(m_viewChannel);
	std::wstring wide(str.begin(), str.end());

	m_spriteBatch->Begin(SpriteSortMode_Deferred, nullptr, nullptr, states->DepthNone(), states->CullCounterClockwise());	

	// チャンネル番号表示
	m_spriteFont->DrawString(
		m_spriteBatch.get(),
		wide.c_str(),
		SimpleMath::Vector2(0.0f, 0.0f),
		DirectX::Colors::Yellow
	);

	// 登録されている文字を描画
	for (int i = 0; i < m_stringList[m_viewChannel].size(); i++)
	{
		m_spriteFont->DrawString(
			m_spriteBatch.get(),
			m_stringList[m_viewChannel][i].c_str(),
			SimpleMath::Vector2(0.0f, i * m_fontHeight + m_fontHeight),
			DirectX::Colors::Yellow
		);
	}

	m_spriteBatch->End();

	// 登録されている文字列をクリア
	m_strings.clear();
	m_stringList.clear();
}

void Imase::DebugFont::ChannelChange()
{
	Keyboard::State key = Keyboard::Get().GetState();

	if		(key.D0) m_viewChannel = 0;
	else if (key.D1) m_viewChannel = 1;
	else if (key.D2) m_viewChannel = 2;
	else if (key.D3) m_viewChannel = 3;
	else if (key.D4) m_viewChannel = 4;
	else if (key.D5) m_viewChannel = 5;
	else if (key.D6) m_viewChannel = 6;
	else if (key.D7) m_viewChannel = 7;
	else if (key.D8) m_viewChannel = 8;
	else if (key.D9) m_viewChannel = 9;
}

// コンストラクタ
DebugFont3D::DebugFont3D(ID3D11Device* device, ID3D11DeviceContext* context, wchar_t const* fileName)
	: DebugFont(device, context, fileName)
{	
	// エフェクトを作成
	m_effect = std::make_unique<BasicEffect>(device);
	m_effect->SetTextureEnabled(true);
	m_effect->SetVertexColorEnabled(true);
	m_effect->SetLightingEnabled(false);

	// 入力レイアウトを作成
	DX::ThrowIfFailed(
		CreateInputLayoutFromEffect(
			device,
			m_effect.get(),
			VertexPositionColorTexture::InputElements,
			VertexPositionColorTexture::InputElementCount,
			m_inputLayout.ReleaseAndGetAddressOf())
	);
}

// デストラクタ
Imase::DebugFont3D::~DebugFont3D()
{
	m_inputLayout.Reset();
	m_effect.reset();
}

// 描画する文字列を登録する関数（3D版）
void DebugFont3D::AddString(
	const wchar_t* string,
	DirectX::SimpleMath::Vector3 pos,
	DirectX::FXMVECTOR color,
	float scale)
{
	String str;

	str.string = std::wstring(string);
	str.pos = pos;
	str.color = color;
	// 文字の高さが3D空間内で１になるよう調整している（余白があるのできっちりではない）
	str.scale = scale / m_fontHeight;

	m_strings.push_back(str);
}

// 描画関数（3D版）
void DebugFont3D::Render(
	ID3D11DeviceContext* context,
	DirectX::CommonStates* states,
	const DirectX::SimpleMath::Matrix& view,
	const DirectX::SimpleMath::Matrix& proj)
{
	// スクリーン座標はY軸が＋－逆なので
	SimpleMath::Matrix invertY = SimpleMath::Matrix::CreateScale(1.0f, -1.0f, 1.0f);

	// ビュー行列の回転を打ち消す行列を作成する
	SimpleMath::Matrix invView = view.Invert();
	invView._41 = 0.0f;
	invView._42 = 0.0f;
	invView._43 = 0.0f;

	// エフェクトにビュー行列と射影行列を設定する
	m_effect->SetView(view);
	m_effect->SetProjection(proj);

	for (size_t i = 0; i < m_strings.size(); i++)
	{
		m_spriteBatch->Begin(SpriteSortMode_Deferred, nullptr, nullptr, states->DepthNone(), states->CullCounterClockwise(), [=]
			{
				// ワールド行列作成
				SimpleMath::Matrix world = invertY * invView * SimpleMath::Matrix::CreateTranslation(m_strings[i].pos);
				// エフェクトを適応する
				m_effect->SetWorld(world);
				m_effect->Apply(context);
				// 入力レイアウトを設定する
				context->IASetInputLayout(m_inputLayout.Get());
			}
		);

		// 文字列の中心が表示位置になるように設定
		SimpleMath::Vector2 textOrigin = m_spriteFont->MeasureString(m_strings[i].string.c_str()) / 2.0f;

		m_spriteFont->DrawString(
			m_spriteBatch.get(),
			m_strings[i].string.c_str(),
			SimpleMath::Vector2::Zero,
			m_strings[i].color,
			0.0f,
			textOrigin,
			m_strings[i].scale);

		m_spriteBatch->End();
	}

	// 登録されている文字列をクリア
	m_strings.clear();
}
