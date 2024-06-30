#include "pch.h"
#include "Collider.h"

#include "Game/MyLibrary/GameObject/GameObject.h"

//------------------------------------------------------------------
/**
 * @brief コンストラクタ
 *
 * @param type       ：当たり判定に使用する図形タイプ
 * @param position   ：位置
 * @param isCollision：他のオブジェクトと判定を行うか
 */
Collider::Collider(Shape type, DirectX::SimpleMath::Vector3 position, bool isCollision)
	: m_type(type)
	, m_gameObject(nullptr)
	, m_position(position)
	, m_isCollision(isCollision)
{
}

//------------------------------------------------------------------
/**
 * @brief 図形タイプの取得
 *
 * @param  なし
 * @return Type：図形タイプ
 */
Collider::Shape Collider::GetType() const
{
	return m_type;
}

//------------------------------------------------------------------
/**
 * @brief 図形タイプの設定
 *
 * @param  type：設定する図形タイプ
 * @return なし
 */
void Collider::SetType(Shape type)
{
	m_type = type;
}

//------------------------------------------------------------------
/**
 * @brief 位置の取得
 *
 * @param  なし
 * @return Vector3：位置
 */
const DirectX::SimpleMath::Vector3& Collider::GetPosition() const
{
	return m_position;
}

//------------------------------------------------------------------
/**
 * @brief 位置の設定
 *
 * @param  position：設定する位置
 * @return なし
 */
void Collider::SetPosition(const DirectX::SimpleMath::Vector3& position)
{
	m_position = position;
}

//------------------------------------------------------------------
/**
 * @brief 他のオブジェクトと判定を取るか確認
 *
 * @param  なし
 * @return true ：判定を取る
 * @return false：判定を取らない
 */
bool Collider::IsCollision() const
{
	return m_isCollision;
}

//------------------------------------------------------------------
/**
 * @brief 他のオブジェクトと判定を取るか設定
 *
 * @param  isCollision：判定を取るか
 * @return なし
 */
void Collider::SetIsCollision(bool isCollision)
{
	m_isCollision = isCollision;
}

//------------------------------------------------------------------
/**
 * @brief ゲームオブジェクト取得
 *
 * @param なし
 * @return GameObject*：ゲームオブジェクトのポインタ
 */
GameObject* Collider::GetGameObject() const
{
	return m_gameObject;
}

//------------------------------------------------------------------
/**
 * @brief ゲームオブジェクト設定
 *
 * @param  gameObject：設定するゲームオブジェクト
 * @return なし
 */
void Collider::SetGameObject(GameObject* gameObject)
{
	m_gameObject = gameObject;
}

//------------------------------------------------------------------
/**
 * @brief 接触時処理
 *
 * @param collider：接触したオブジェクト
 * @return なし
 */
void Collider::OnCollision(Collider* collider)
{
	m_gameObject->OnCollision(collider->GetGameObject());
}
