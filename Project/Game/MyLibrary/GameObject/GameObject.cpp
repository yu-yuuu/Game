#include "pch.h"
#include "GameObject.h"

using namespace DirectX;

//------------------------------------------------------------------
/**
 * @brief コンストラクタ
 *
 * @param なし
 */
GameObject::GameObject()
    : m_world(SimpleMath::Matrix::Identity)
    , m_position(SimpleMath::Vector3::Zero)
    , m_rotation(SimpleMath::Quaternion::Identity)
    , m_scale(SimpleMath::Vector3::One)
    , m_isActive(true)
    , m_isChange(false)
{
}

//------------------------------------------------------------------
/**
 * @brief 接触時処理（単体）
 *
 * @param gameObject：当たったオブジェクト
 * @return なし
 */
void GameObject::OnCollision(GameObject* gameObject)
{
    gameObject;
}

//------------------------------------------------------------------
/**
 * @brief ワールド行列取得
 *
 * @param  なし
 * @return Matrix：ワールド行列
 */
const SimpleMath::Matrix& GameObject::GetWorldMatrix()
{
    // オブジェクト情報に変更があるなら行列を再計算する
    if (m_isChange)
    {
        // 初期化
        m_world = SimpleMath::Matrix::Identity;
        // 各行列を計算する
        m_world *= SimpleMath::Matrix::CreateScale(m_scale);             // 拡大縮小
        m_world *= SimpleMath::Matrix::CreateFromQuaternion(m_rotation); // 回転
        m_world *= SimpleMath::Matrix::CreateTranslation(m_position);    // 位置

        // フラグ初期化
        m_isChange = false;
    }

    return m_world;
}

//------------------------------------------------------------------
/**
 * @brief 位置の取得
 *
 * @param なし
 * @return Vector3：位置
 */
const SimpleMath::Vector3& GameObject::GetPosition() const
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
void GameObject::SetPosition(const SimpleMath::Vector3& position)
{   
    // 違う値か
    if (m_position != position)
    {
        // 値を代入
        m_position = position;
        // フラグを立てる
        m_isChange = true;
    }
}

//------------------------------------------------------------------
/**
 * @brief 回転の取得
 *
 * @param なし
 * @return Quaternion：回転クォータニオン
 */
const SimpleMath::Quaternion& GameObject::GetRotation() const
{
    return m_rotation;
}

//------------------------------------------------------------------
/**
 * @brief 回転の設定（クォータニオン ver）
 *
 * @param  rotation：設定する回転
 * @return なし
 */
void GameObject::SetRotation(const SimpleMath::Quaternion& rotation)
{
    // 違う値か
    if (m_rotation != rotation)
    {
        // 値を代入
        m_rotation = rotation;
        // フラグを立てる
        m_isChange = true;
    }
}

//------------------------------------------------------------------
/**
 * @brief 回転の設定（Vector3 ver）
 *
 * @param rotation：設定する回転
 * @return なし
 */
void GameObject::SetRotation(const SimpleMath::Vector3& rotation)
{
    SetRotation(SimpleMath::Quaternion::CreateFromYawPitchRoll(rotation));
}

//------------------------------------------------------------------
/**
 * @brief 大きさの取得
 *
 * @param  なし
 * @return Vector3：大きさ
 */
const SimpleMath::Vector3& GameObject::GetScale() const
{
    return m_scale;
}

//------------------------------------------------------------------
/**
 * @brief 大きさの設定
 *
 * @param  scale：設定する大きさ
 * @return なし
 */
void GameObject::SetScale(const SimpleMath::Vector3& scale)
{
    // 違う値か
    if (m_scale != scale)
    {
        // 値を代入
        m_scale = scale;
        // フラグを立てる
        m_isChange = true;
    }
}

//------------------------------------------------------------------
/**
 * @brief アクティブ状態か
 *
 * @param  なし
 * @return true ：アクティブ状態
 * @return false：非アクティブ状態
 */
const bool GameObject::IsActive() const
{
    return m_isActive;
}

//------------------------------------------------------------------
/**
 * @brief アクティブ状態設定
 *
 * @param  isActive：設定する状態
 * @return なし
 */
void GameObject::SetActive(bool isActive)
{
    m_isActive = isActive;
}


//------------------------------------------------------------------
/**
 * @brief 姿勢ベクトル取得（前方）
 *
 * @param なし
 * @return Vector3：姿勢ベクトル（前方）
 */
const DirectX::SimpleMath::Vector3 GameObject::Forward()
{
    return SimpleMath::Vector3::Transform(SimpleMath::Vector3::Forward, m_rotation);
}

//------------------------------------------------------------------
/**
 * @brief 姿勢ベクトル取得（後方）
 *
 * @param なし
 * @return Vector3：姿勢ベクトル（後方）
 */
const DirectX::SimpleMath::Vector3 GameObject::Back()
{
    return SimpleMath::Vector3::Transform(SimpleMath::Vector3::Backward, m_rotation);
}

//------------------------------------------------------------------
/**
 * @brief 姿勢ベクトル取得（右方向）
 *
 * @param なし
 * @return Vector3：姿勢ベクトル（右方向）
 */
const DirectX::SimpleMath::Vector3 GameObject::Right()
{
    return SimpleMath::Vector3::Transform(SimpleMath::Vector3::Right, m_rotation);
}

//------------------------------------------------------------------
/**
 * @brief 姿勢ベクトル取得（左方向）
 *
 * @param なし
 * @return Vector3：姿勢ベクトル（左方向）
 */
const DirectX::SimpleMath::Vector3 GameObject::Left()
{
    return SimpleMath::Vector3::Transform(SimpleMath::Vector3::Left, m_rotation);
}

//------------------------------------------------------------------
/**
 * @brief 姿勢ベクトル取得（上方向）
 *
 * @param なし
 * @return Vector3：姿勢ベクトル（上方向）
 */
const DirectX::SimpleMath::Vector3 GameObject::Up()
{
    return SimpleMath::Vector3::Transform(SimpleMath::Vector3::Up, m_rotation);
}

//------------------------------------------------------------------
/**
 * @brief 姿勢ベクトル取得（下方向）
 *
 * @param なし
 * @return Vector3：姿勢ベクトル（下方向）
 */
const DirectX::SimpleMath::Vector3 GameObject::Down()
{
    return SimpleMath::Vector3::Transform(SimpleMath::Vector3::Down, m_rotation);
}