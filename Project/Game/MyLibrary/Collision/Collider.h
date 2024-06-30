/**
 *
 * @file Collider.h
 *
 * @brief オブジェクトに付ける当たり判定を表すクラスのヘッダー
 *
 * @author Kato Yuki
 *
 * @date 2024/1/3
 *
 * @note 補足説明、メモ
 *
 */
#pragma once

class GameObject;

class Collider
{
//----------------------------------------------
// 列挙体
//----------------------------------------------
public:

	// 図形タイプ
	enum class Shape
	{
		BOX,    // 箱
		SPHERE, // 球
		NONE,   // 未設定
	};

//----------------------------------------------
// 変数
//----------------------------------------------
private:

	// 図形種類
	Shape m_type;
	// 付けているゲームオブジェクト
	GameObject* m_gameObject;
	// 位置
	DirectX::SimpleMath::Vector3 m_position;
	// 他のオブジェクトと判定を取るか
	bool m_isCollision;

//----------------------------------------------
// 関数
//----------------------------------------------
public:

	// コンストラクタ
	Collider(Shape type, DirectX::SimpleMath::Vector3 position, bool isCollision);
	// デストラクタ
	virtual ~Collider() = default;

	// 図形タイプの取得
	Shape GetType()const;
	// 図形タイプの設定
	void SetType(Shape type);

	// 位置の取得
	virtual const DirectX::SimpleMath::Vector3& GetPosition() const;
	// 位置の設定
	virtual void SetPosition(const DirectX::SimpleMath::Vector3& position);

	// 他オブジェクトと判定を取るか確認
	bool IsCollision() const;
	// 他オブジェクトと判定を取るか設定
	void SetIsCollision(bool isCollision);

	// ゲームオブジェクト取得
	GameObject* GetGameObject() const;
	// ゲームオブジェクト設定
	void SetGameObject(GameObject* gameObject);

	// 接触時処理
	void OnCollision(Collider* collider);

};