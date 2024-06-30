/**
 *
 * @file BlockType.h
 *
 * @brief ブロックの種類を定義するヘッダーファイル
 *
 * @author Kato Yuki
 *
 * @date 2023/12/28
 *
 */
#pragma once

//----------------------------------------------
// 自作の共通定義を扱う名前空間
//----------------------------------------------
namespace KT
{
	//----------------------------------------------
	//　ブロックのタイプを扱う名前空間
	//----------------------------------------------
	namespace Block
	{
		// ブロックの種類
		enum class Type
		{
			NONE,           // 0：未設定
			GRASS,          // 1：草
			GHOST,          // 2：ゴースト
			GHOST_FLOOR,    // 3：ゴースト床
			BRICK,          // 4：レンガ
			START,          // 5：スタートブロック
			GOAL,           // 6：ゴールブロック
			GAME_START,     // 7：あそぶボタンの背景
			GAME_START_A,   // 8：あそぶボタンのあ
			GAME_START_SO,  // 9：あそぶボタンのそ
			GAME_START_BU,  // 10：あそぶボタンのぶ
			GAME_END,       // 11：おわるボタンの背景
			GAME_END_O,     // 12：おわるボタンのお
			GAME_END_WA,    // 13：おわるボタンのわ
			GAME_END_RU,    // 14：おわるボタンのる
		};

		// ブロックの当たり判定モード
		enum class CollisionMode
		{
			_2D,	// 2Dのみ
			_3D,	// 3Dのみ
			BOTH,	// 両方
			NONE,   // 判定を取らない
		};
	}
}