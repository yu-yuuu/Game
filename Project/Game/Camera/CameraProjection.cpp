/**
 *
 * @file CameraProjection.cpp
 *
 * @brief カメラに使用する射影行列を作成するクラスのソースファイル
 *
 * @author Kato Yuki
 *
 * @date 2023/11/23
 *
 */
#include "pch.h"
#include "CameraProjection.h"

//----------------------------------------------
// 定数定義
//----------------------------------------------

// 視野角（度数法）
const float CameraProjection::FOV = 45.0f;
//手前の表示距離
const float CameraProjection::NEAR_PLANE = 0.1f;
// 奥の表示距離
const float CameraProjection::FAR_PLANE = 200.0f;

// 横視点時のカメラ範囲
const RECT CameraProjection::SIDE_RECT = { -8, 12, 8, -4 };
// 見下ろし視点時のカメラ範囲
const RECT CameraProjection::TOPDOWN_RECT = { -6, 6, 6, -6 };
// 見渡し状態のカメラ範囲
const RECT CameraProjection::OVER_LOOKING_RECT = { -8, 8, 8, -8 };


//------------------------------------------------------------------
/**
 * @brief 透視投影（ 3D ）の射影行列を作成
 *
 * @param  aspectRatio：画面比
 * @return Matrix     ：透視投影行列
 */
DirectX::SimpleMath::Matrix CameraProjection::CreatePerspectiveProjection(const float& aspectRatio)
{
	return DirectX::SimpleMath::Matrix::CreatePerspectiveFieldOfView
	(
		FOV,
		aspectRatio,
		NEAR_PLANE,
		FAR_PLANE
	);
}

//------------------------------------------------------------------
/**
 * @brief 並行投影（ 2D ）の射影行列を作成
 *
 * @param  aspectRatio：画面比
 * @param  rect       ：カメラ範囲
 * @return Matrix     ：並行投影行列
 */
DirectX::SimpleMath::Matrix CameraProjection::CreateOrthographicProjection(const float& aspectRatio, const RECT& rect)
{
	return DirectX::SimpleMath::Matrix::CreateOrthographicOffCenter
	(
		static_cast<float>(rect.left)  * aspectRatio,
		static_cast<float>(rect.right) * aspectRatio,
		static_cast<float>(rect.bottom),
		static_cast<float>(rect.top),
		NEAR_PLANE, // 手前の表示距離
		FAR_PLANE	// 奥の表示距離
	);
}