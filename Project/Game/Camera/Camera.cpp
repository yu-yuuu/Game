/**
 *
 * @file Camera.cpp
 *
 * @brief カメラクラスのソース
 *
 * @author Kato Yuki
 *
 * @date 2023/11/22
 *
 */
#include "pch.h"
#include "Camera.h"
#include "Game/MyLibrary/Utility/MyUtility.h"

using namespace DirectX;

//------------------------------------------------------------------
/**
 * @brief コンストラクタ
 *
 * @param aspectRatio：画面比
 */
Camera::Camera(const float& aspectRatio)
	: m_eye()
	, m_target()
	, m_up(DirectX::SimpleMath::Vector3::UnitY)
	, m_view()
	, m_projection()
	, m_rotation()
	, m_isChange(true)
	, m_aspectRatio(aspectRatio)
{
}

//------------------------------------------------------------------
/**
 * @brief デストラクタ
 */
Camera::~Camera()
{
}

//------------------------------------------------------------------
/**
 * @brief ビュー行列の更新
 *
 * @param  なし
 * @return なし
 */
void Camera::CreateViewMatrix()
{
	// 位置等に変更があるか
	if (!m_isChange) return;

	assert(m_eye != m_target && "カメラの位置と注視点が同じです");

	// カメラの位置を計算
	SimpleMath::Vector3 eye = m_target + SimpleMath::Vector3::Transform(m_eye, m_rotation);
	// 頭の向きを計算する
	m_up = SimpleMath::Vector3::Transform(SimpleMath::Vector3::UnitY, m_rotation);
	// ビュー行列作成
	m_view = DirectX::SimpleMath::Matrix::CreateLookAt(eye, m_target, m_up);
	// 変更フラグを折る
	m_isChange = false;
}

//------------------------------------------------------------------
/**
 * @brief 更新
 *
 * @param  elapsedTime：経過時間
 * @return なし
 */
void Camera::Update()
{
	// ビュー行列作成
	CreateViewMatrix();
}

//------------------------------------------------------------------
/**
 * @brief カメラ位置の取得
 *
 * @param  なし
 * @return Vector3：カメラ位置
 */
const DirectX::SimpleMath::Vector3& Camera::GetEyePosition() const
{
	return m_eye;
}

//------------------------------------------------------------------
/**
 * @brief カメラ位置の設定
 *
 * @param  eye：設定するカメラ位置
 * @return なし
 */
void Camera::SetEyePosition(const DirectX::SimpleMath::Vector3& eye)
{
	// 変更が無いなら終了
	if (m_eye == eye) return;

	m_eye = eye;
	m_isChange = true;
}

//------------------------------------------------------------------
/**
 * @brief 注視点の取得
 *
 * @param なし
 * @return Vector3：注視点
 */
const DirectX::SimpleMath::Vector3& Camera::GetTargetPosition() const
{
	return m_target;
}

//------------------------------------------------------------------
/**
 * @brief 注視点の設定
 *
 * @param  target：設定する注視点
 * @return なし
 */
void Camera::SetTargetPosition(const DirectX::SimpleMath::Vector3& target)
{
	// 変更が無いなら終了
	if (m_target == target) return;

	m_target = target;
	m_isChange = true;
}

//------------------------------------------------------------------
/**
 * @brief 頭の向きの取得
 *
 * @param なし
 * @return Vector3：頭の向き
 */
const DirectX::SimpleMath::Vector3& Camera::GetUpVector() const
{
	return m_up;
}

//------------------------------------------------------------------
/**
 * @brief 頭の向きの設定
 *
 * @param  up：設定する頭の向き
 * @return なし
 */
void Camera::SetUpVector(const DirectX::SimpleMath::Vector3& up)
{
	m_up = up;
}

//------------------------------------------------------------------
/**
 * @brief 回転の取得
 *
 * @param  なし
 * @return Quaternion：カメラの回転クォータニオン
 */
const DirectX::SimpleMath::Quaternion& Camera::GetRotation() const
{
	return m_rotation;
}

//------------------------------------------------------------------
/**
 * @brief 回転の設定( クォータニオン )
 *
 * @param  rotation：設定する回転クォータニオン
 * @return なし
 */
void Camera::SetRotation(const DirectX::SimpleMath::Quaternion& rotation)
{
	// 変更が無いなら終了
	if (m_rotation == rotation) return;

	m_rotation = rotation;
	m_isChange = true;
}

//------------------------------------------------------------------
/**
 * @brief 回転の設定( Vector3 )
 *
 * @param  rotation：設定する回転ベクトル( Yaw Pic )
 * @return なし
 */
void Camera::SetRotation(const DirectX::SimpleMath::Vector3& rotation)
{
	SetRotation(SimpleMath::Quaternion::CreateFromYawPitchRoll(rotation));
}

//------------------------------------------------------------------
/**
 * @brief ビュー行列の取得
 *
 * @param  なし
 * @return Matrix：ビュー行列
 */
const DirectX::SimpleMath::Matrix& Camera::GetViewMatrix() const
{
	return m_view;
}

//------------------------------------------------------------------
/**
 * @brief ビュー行列の設定
 *
 * @param  view：設定するビュー行列
 * @return なし
 */
void Camera::SetViewMatrix(const DirectX::SimpleMath::Matrix& view)
{
	m_view = view;
}

//------------------------------------------------------------------
/**
 * @brief 射影行列の取得
 *
 * @param  なし
 * @return Matrix：射影行列
 */
const DirectX::SimpleMath::Matrix& Camera::GetProjectionMatrix() const
{
	return m_projection;
}

//------------------------------------------------------------------
/**
 * @brief 射影行列の設定
 *
 * @param  projection：設定する射影行列
 * @return なし
 */
void Camera::SetProjectionMatrix(const DirectX::SimpleMath::Matrix& projection)
{
	m_projection = projection;
}

//------------------------------------------------------------------
/**
 * @brief 画面比の取得
 *
 * @param  なし
 * @return float：画面比
 * 
 */
const float& Camera::GetAspectRatio() const
{
	return m_aspectRatio;
}

//------------------------------------------------------------------
/**
 * @brief カメラの方向ベクトル取得
 *
 * @param  なし
 * @return Vector3：カメラの方向ベクトル
 */
DirectX::SimpleMath::Vector3 Camera::GetDirection()
{
	// 方向ベクトルを求める
	SimpleMath::Vector3 dir = SimpleMath::Vector3::Transform(SimpleMath::Vector3::Forward, m_rotation);
	// 誤差がある場合があるので綺麗にする
	return KT::MyUtility::EliminateDirectionError(dir);
}