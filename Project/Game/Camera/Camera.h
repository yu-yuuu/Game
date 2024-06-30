/**
 *
 * @file Camera.h
 *
 * @brief カメラクラスのヘッダー
 *
 * @author Kato Yuki
 *
 * @date 2023/11/22
 *
 */
#pragma once

class Camera
{
//----------------------------------------------
// 定数
//----------------------------------------------
public:

	// 視野角（度数法）
	const float FOV = 45.0f;
	// 手前の表示距離
	const float NEAR_PLANE = 0.1f;
	// 奥の表示距離
	const float FAR_PLANE = 200.0f;	

//----------------------------------------------
// 変数
//----------------------------------------------
private:

	// 位置
	DirectX::SimpleMath::Vector3 m_eye;
	// 注視点
	DirectX::SimpleMath::Vector3 m_target;
	// 頭の向き
	DirectX::SimpleMath::Vector3 m_up;
	// ビュー行列
	DirectX::SimpleMath::Matrix m_view;
	// 射影行列
	DirectX::SimpleMath::Matrix m_projection;
	// 回転
	DirectX::SimpleMath::Quaternion m_rotation;
	// カメラの情報が変更されたか
	bool m_isChange;
	// 画面比
	float m_aspectRatio;

//----------------------------------------------
// 関数
//----------------------------------------------
public:

	// コンストラクタ
	Camera(const float& aspectRatio);
	// デストラクタ
	virtual ~Camera();
	// 更新
	virtual void Update();

	// ビュー行列の作成
	void CreateViewMatrix();

	// 位置の取得
	const DirectX::SimpleMath::Vector3& GetEyePosition()const;
	// 位置の設定
	void SetEyePosition(const DirectX::SimpleMath::Vector3& eye);
	// ターゲットの取得
	const DirectX::SimpleMath::Vector3& GetTargetPosition()const;
	// ターゲットの設定
	void SetTargetPosition(const DirectX::SimpleMath::Vector3& target);
	// 頭の向きの取得
	const DirectX::SimpleMath::Vector3& GetUpVector() const;
	// 頭の向きの設定
	void SetUpVector(const DirectX::SimpleMath::Vector3& up);
	// 回転の取得
	const DirectX::SimpleMath::Quaternion& GetRotation()const;
	// 回転の設定（ クォータニオン ）
	void SetRotation(const DirectX::SimpleMath::Quaternion& rotation);
	// 回転の設定（ Vector3 ）
	void SetRotation(const DirectX::SimpleMath::Vector3& rotation);
	// ビュー行列の取得
	const DirectX::SimpleMath::Matrix& GetViewMatrix()const;
	// ビュー行列の設定
	void SetViewMatrix(const DirectX::SimpleMath::Matrix& view);
	// 射影行列の取得
	const DirectX::SimpleMath::Matrix& GetProjectionMatrix()const;
	// 射影行列の設定
	void SetProjectionMatrix(const DirectX::SimpleMath::Matrix& projection);
	// 画面比の取得
	const float& GetAspectRatio()const;
	// カメラの方向ベクトル取得
	DirectX::SimpleMath::Vector3 GetDirection();
};