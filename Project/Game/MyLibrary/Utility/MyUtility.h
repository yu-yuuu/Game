/**
 *
 * @file MyUtility.h
 *
 * @brief 自作の汎用関数を集めたクラスのヘッダーファイル
 *
 * @author Kato Yuki
 *
 * @date 2023/12/12
 *
 */
#pragma once
#include <string>
#include "Game/MyLibrary/CommonResource/GameResource.h"

namespace KT
{
	class MyUtility
	{
	//----------------------------------------------
	// 関数
	//----------------------------------------------
	public:

		// ベクトルの絶対値を求める
		static DirectX::SimpleMath::Vector3 AbsVector(const DirectX::SimpleMath::Vector3& vec);

		// ベクトルの整数部のみ求める
		static DirectX::SimpleMath::Vector3 ModVector(const DirectX::SimpleMath::Vector3& vec);
		// ベクトルフラグを反転
		static DirectX::SimpleMath::Vector3 InverseFlag(const DirectX::SimpleMath::Vector3& vec);
		// ベクトルのクランプ処理
		static DirectX::SimpleMath::Vector3 Clamp(
			const DirectX::SimpleMath::Vector3& value,
			const DirectX::SimpleMath::Vector3& min,
			const DirectX::SimpleMath::Vector3& max
		);
		// 6方向ベクトルの誤差をなくす
		// ( 上下 左右 奥手前の0と1のみのベクトル )
		static DirectX::SimpleMath::Vector3 EliminateDirectionError(const DirectX::SimpleMath::Vector3& vec);
		// 2つのfloat型変数がほぼ同じか確認する
		static bool FloatPresqueEqual(const float& f1, const float& f2);

		// メニュー選択
		template<typename ENUM>
		static void MenuSelect(bool countUpKey, bool countDownKey, ENUM& enumMenu, bool playSE = true);
		// string から wstring へ変換
		static std::wstring  StringToWide(const std::string& str);
		// string から 16進数の数値へ変換
		static int ConvertToHexadecimal(const std::string& str);
	};

	//----------------------------------------------
	// テンプレート関数定義
	//----------------------------------------------

   //------------------------------------------------------------------
   /**
	* @brief メニュー選択
	* @brief ※注　ENUMには数を表すCOUNTを追加してください
	*
	* @tparam ENUM        ：メニューに使用している列挙体
	* @param  countUpKey  ：メニュー番号をカウントアップさせるキーの入力状況
	* @param  countDownKey：メニュー番号をカウントダウンさせるキーの入力状況
	* @param  enumMenu    ：現在選択しているメニュー
	* @param  playSE      ：SEを再生するか
	* @return なし
	*/
	template<typename ENUM>
	inline void MyUtility::MenuSelect(bool countUpKey, bool countDownKey, ENUM& enumMenu, bool playSE)
	{
		// メニューの最大数を取得
		int max = static_cast<int>(ENUM::COUNT);

		// 現在選択しているメニューを取得
		int current = static_cast<int>(enumMenu);

		// カウントアップ
		if (countUpKey)
		{
			current--;

			// マイナスなら
			if (current < 0)
			{
				// 末尾のメニューを設定
				current = max - 1;
			}
		}
		// カウントダウン
		else if (countDownKey)
		{
			current++;

			// メニューの数と同じなら
			if (current == max)
			{
				// 先頭のメニューを設定
				current = 0;
			}
		}

		// 数値を列挙体に直す
		enumMenu = static_cast<ENUM>(current);

		// 選択時SEを流す
		if ((countUpKey || countDownKey) && playSE)
		{
			GameResource::GetInstance()->GetResourceManager()->PlaySound(KT::Sound::SE, KT::Sound::SENumber::XACT_WAVEBANK_SE_MOVECURSOL);
		}
	}
}