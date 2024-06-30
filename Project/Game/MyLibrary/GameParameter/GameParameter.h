/**
 *
 * @file ファイル名.h
 *
 * @brief 簡単な説明
 *
 * @author 書いた人
 *
 * @date 2024/2/11
 *
 * @note 補足説明、メモ
 *
 */
#pragma once

namespace KT
{
	// ゲーム内で扱うパラメーターを宣言する名前空間
	namespace GameParam
	{
		// 次元
		enum class Dimension
		{
			_2D,
			_3D,
		};

		// 視点タイプ
		enum class SightType
		{
			TOPDOWN,
			SIDE,
		};

		// カメラの状態
		enum class CameraState
		{
			NONE,               // 通常
			OPERATION,          // 操作中
			OPERATION_COMPLETE, // 操作終了
		};

		// 移動方向入力フラグ
		enum InputDirection : int
		{
			RIGHT   = 1 << 0,	// 右
			LEFT    = 1 << 1,	// 左
			FORWARD = 1 << 2,	// 奥
			BACK    = 1 << 3,	// 手前

			NONE    = 0,		// 停止
		};

		// タイトル用ステージの番号
		static const int TITLE_STAGE_NUM = 1100;
		// 次元切り替え時の補完時間
		static const float LERP_TIME_DIMENSION = 0.5f;
		// カメラ回転時の補完時間
		static const float LERP_TIME_ROTATION = 0.3f;
		// ゲーム開始時アニメーションの補完時間
		static const float LERP_TIME_GAMESTART = 5.0f;
		// 見渡しカメラ切替時の補完時間
		static const float LERP_TIME_OVERLOOKING = 1.0f;
		// 3D見下ろし視点のカメラ位置オフセット
		static const DirectX::SimpleMath::Vector3 EYE_OFFSET_TOPDOWN = { 0.0f, -1.5f, 6.0f };
		// 3D横視点のカメラ位置オフセット
		static const DirectX::SimpleMath::Vector3 EYE_OFFSET_SIDE = { 0.0f, 3.0f, 5.0f };
		// 当たり判定を取るブロックの検索範囲
		static float COLLISION_RAMGE = 2.0f;
		// ゴースト床の2D時足場判定の高さ
		static float GHOST_FLOOR_CHECK_HEIGHT = 0.2f;
	}
}