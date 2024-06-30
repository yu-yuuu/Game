/**
 *
 * @file CameraProjection.h
 *
 * @brief カメラに使用する射影行列を作成するクラスのヘッダーファイル
 *
 * @author Kato Yuki
 *
 * @date 2023/11/23
 *
 */
#pragma once


class CameraProjection
{
//----------------------------------------------
// 定数
//----------------------------------------------
private:

	// 視野角（度数法）
	static const float FOV;
	// 手前の表示距離
	static const float NEAR_PLANE;
	// 奥の表示距離
	static const float FAR_PLANE;
	
public:

	// 横視点時のカメラ範囲
	static const RECT SIDE_RECT;
	// 見下ろし視点時のカメラ範囲
	static const RECT TOPDOWN_RECT;
	// 見渡し状態のカメラ範囲
	static const RECT OVER_LOOKING_RECT;

//----------------------------------------------
// 関数
//----------------------------------------------
public:

	// 透視投影（ 3D ）の射影行列を作成
	static DirectX::SimpleMath::Matrix CreatePerspectiveProjection(const float& aspectRatio);
	// 並行投影（ 2D ）の射影行列を作成
	static DirectX::SimpleMath::Matrix CreateOrthographicProjection(const float& aspectRatio, const RECT& rect);
};