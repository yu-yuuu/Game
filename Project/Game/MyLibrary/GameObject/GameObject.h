/**
 *
 * @file GameObject.h
 *
 * @brief ゲームオブジェクトを表すクラスのヘッダーファイル
 *
 * @author Kato Yuki
 *
 * @date 2023/11/13
 *
 * @note 補足説明、メモ
 *
 */
#pragma once

#include <vector>
#include <functional>
#include <Effects.h>

class GameObject
{
//----------------------------------------------
// 変数
//----------------------------------------------
private:

	// ワールド行列
	DirectX::SimpleMath::Matrix m_world;
	// 位置
	DirectX::SimpleMath::Vector3 m_position;
	// 回転
	DirectX::SimpleMath::Quaternion m_rotation;
	// 大きさ
	DirectX::SimpleMath::Vector3 m_scale;

	// アクティブかどうか
	bool m_isActive;
	// オブジェクト情報が変更されたか
	bool m_isChange;

//----------------------------------------------
// 関数
//----------------------------------------------
public:

	// コンストラクタ
	GameObject();
	// デストラクタ
	virtual ~GameObject() = default;
	// 初期化
	virtual void Initialize(std::function<void(DirectX::IEffect* effect)> effect = nullptr) = 0;
	// 更新
	virtual void Update() = 0;
	// 描画
	virtual void Render(
		DirectX::SimpleMath::Matrix view, 
		DirectX::SimpleMath::Matrix projection,
		std::function<void()> custom = nullptr) = 0;
	// 後処理
	virtual void Finalize() = 0;

	// 接触時処理
	virtual void OnCollision(GameObject* gameObject);

	// ワールド行列の取得
	const DirectX::SimpleMath::Matrix& GetWorldMatrix();
	// 位置の取得、設定
	const DirectX::SimpleMath::Vector3& GetPosition() const;
	void SetPosition(const DirectX::SimpleMath::Vector3& position);
	// 回転の取得設定
	const DirectX::SimpleMath::Quaternion& GetRotation() const;
	void SetRotation(const DirectX::SimpleMath::Quaternion& rotation);
	void SetRotation(const DirectX::SimpleMath::Vector3& rotation);
	// 大きさの設定
	const DirectX::SimpleMath::Vector3& GetScale() const;
	void SetScale(const DirectX::SimpleMath::Vector3& scale);

	// アクティブ状態の取得、設定
	const bool IsActive()const;
	void SetActive(bool isActive);

	// 姿勢ベクトル取得
	const DirectX::SimpleMath::Vector3 Forward(); // 正面
	const DirectX::SimpleMath::Vector3 Back();    // 後方
	const DirectX::SimpleMath::Vector3 Right();   // 右
	const DirectX::SimpleMath::Vector3 Left();    // 左
	const DirectX::SimpleMath::Vector3 Up();      // 上
	const DirectX::SimpleMath::Vector3 Down();    // 下
};