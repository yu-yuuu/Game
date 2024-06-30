//--------------------------------------------------------------------------------------
// File: DebugFont.h
//
// デバッグ用文字フォント描画クラス
//
// Usage: DebugFontクラスは2D版、DebugFont3Dクラスは3D版です。
//        AddString関数で文字列を登録します。登録された情報は描画後クリアされます。
//        デバッグ用の文字列の表示などに使用してください。
//		  ※デバッグ用なので深度バッファはみていません。（必ず描画される）
//
// Date: 2023.3.13
// Author: Hideyasu Imase
//--------------------------------------------------------------------------------------
// 改造：2023/11/8 Kato Yuki

#pragma once

#include <vector>
#include <string>
#include <unordered_map>
#include "SimpleMath.h"
#include "CommonStates.h"
#include "Effects.h"
#include "SpriteBatch.h"
#include "SpriteFont.h"

namespace Imase
{

	class DebugFont
	{
	private:

		// 文字列情報
		struct String
		{
			// 位置
			DirectX::SimpleMath::Vector2 pos;

			// 文字列
			std::wstring string;

			// 色
			DirectX::SimpleMath::Color color;

			// スケール
			float scale = 1.0f;
		};
		// 表示文字列の配列
		std::vector<String> m_strings;

	private:

		// デバッグ文字のチャンネル		
		int m_viewChannel;

		// チャンネルの数
		const int CHANNEL_NUM = 10;

		// 表示リスト
		std::unordered_map<int, std::vector<std::wstring>> m_stringList;

	protected:

		// スプライトバッチ
		std::unique_ptr<DirectX::SpriteBatch> m_spriteBatch;

		// スプライトフォント
		std::unique_ptr<DirectX::SpriteFont> m_spriteFont;

		// フォントの縦サイズ
		float m_fontHeight;

	public:

		// コンストラクタ
		DebugFont(ID3D11Device* device, ID3D11DeviceContext* context, wchar_t const* fileName);

		// デストラクタ
		virtual ~DebugFont();

		// フォントの高さを取得する関数
		float GetFontHeight() {	return m_fontHeight; }

	public:



		// 文字列の登録
		void AddString(
			const int& channel,			// チャンネル番号
			const std::string& string	// 表示文字列
		);
		void AddString(
			const int& channel,			// チャンネル番号
			const wchar_t* str	// 表示文字列
		);
		void AddString(
			const int& channel,			// チャンネル番号
			const std::string& str,	// タイトル
			const DirectX::SimpleMath::Vector3& vec // 表示文字列
		);

		// 描画
		void Render(DirectX::CommonStates* states);

		// チャンネルの変更
		void ChannelChange();

		// チャンネルの設定
		void SetChannel(const int& channel) { m_viewChannel = channel; }
	
		// デバッグ用
		void DebugClear()
		{
			// 提出用で表示をさせないと配列が大きくなってしまうので
			// ココでリセット
			if (!m_stringList.empty())
				m_stringList.clear();
		}
	};

	class DebugFont3D : protected DebugFont
	{
	private:

		// 文字列情報
		struct String
		{
			// 位置
			DirectX::SimpleMath::Vector3 pos;

			// 文字列
			std::wstring string;

			// 色
			DirectX::SimpleMath::Color color;

			// スケール
			float scale = 1.0f;
		};

		// 表示文字列の配列
		std::vector<String> m_strings;

		// エフェクト
		std::unique_ptr<DirectX::BasicEffect> m_effect;

		// 入力レイアウト
		Microsoft::WRL::ComPtr<ID3D11InputLayout> m_inputLayout;

	public:

		// コンストラクタ
		DebugFont3D(
			ID3D11Device* device,
			ID3D11DeviceContext* context,
			wchar_t const* fileName);

		// デストラクタ
		~DebugFont3D();

		// 描画する文字列を登録する関数
		void AddString(
			const wchar_t* string,
			DirectX::SimpleMath::Vector3 pos,
			DirectX::FXMVECTOR color = DirectX::Colors::White,
			float scale = 1.0f);

		// 描画関数
		void Render(
			ID3D11DeviceContext* context,
			DirectX::CommonStates* states,
			const DirectX::SimpleMath::Matrix& view,
			const DirectX::SimpleMath::Matrix& proj);

		// フォントの高さを取得する関数
		float GetFontHeight() { return m_fontHeight; }
	};


}

