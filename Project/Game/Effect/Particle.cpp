/**
 *
 * @file Particle.cpp
 *
 * @brief パーティクルの粒1つを表すクラスのソースファイル
 *
 * @author Kato Yuki
 *
 * @date 2024/1/31
 *
 */
#include "pch.h"
#include "Particle.h"

using namespace DirectX;

//------------------------------------------------------------------
/**
 * @brief コンストラクタ
 *
 * @param position    ：描画位置
 * @param velocity    ：移動速度
 * @param startLife   ：生成時の体力
 * @param acceleration：加速度
 * @param startScale  ：生成時の大きさ
 * @param endScale    ：消滅時の大きさ
 * @param startColor  ：生成時の色
 * @param endColor    ：消滅時の色
 */
Particle::Particle(
	DirectX::SimpleMath::Vector3 position, 
	DirectX::SimpleMath::Vector3 velocity,
	float startLife, 
	DirectX::SimpleMath::Vector3 acceleration,
	DirectX::SimpleMath::Vector2 startScale,
	DirectX::SimpleMath::Vector2 endScale,
	DirectX::SimpleMath::Color startColor,
	DirectX::SimpleMath::Color endColor)
	: m_position(position)
	, m_velocity(velocity)
	, m_nowLife(startLife)
	, m_acceleration(acceleration)
	, m_startLife(startLife)
	, m_nowScale()
	, m_startScale(startScale)
	, m_endScale(endScale)
	, m_nowColor()
	, m_startColor(startColor)
	, m_endColor(endColor)
{
}

//------------------------------------------------------------------
/**
 * @brief デストラクタ
 *
 */
Particle::~Particle()
{
}

//------------------------------------------------------------------
/**
 * @brief 更新
 *
 * @param  elapsedTime：経過時間
 * @return なし
 */
void Particle::Update(const float& elapsedTime)
{
	// 速度計算
	m_velocity += m_acceleration;
	// 速度を位置に反映
	m_position += m_velocity;
	// 体力減少
	m_nowLife -= elapsedTime;
	// 体力が 0 以下ならピッタリ 0 に合わせる
	if (m_nowLife <= 0.0f) m_nowLife = 0.0f;
	// 最大体力の何割か求める
	float rate = m_nowLife / m_startLife;
	// 0 -> 1 にしたいので反転させる
	rate = 1.0f - rate;
	// 現在の大きさ更新
	m_nowScale = SimpleMath::Vector2::Lerp(m_startScale, m_endScale, rate);
	// 現在の色合い更新
	m_nowColor = SimpleMath::Color::Lerp(m_startColor, m_endColor, rate);
}

//------------------------------------------------------------------
/**
 * @brief 位置の取得
 *
 * @param なし
 * @return Vector3：位置
 */
const DirectX::SimpleMath::Vector3& Particle::GetPosition()
{
	return m_position;
}

//------------------------------------------------------------------
/**
 * @brief 速度の取得
 *
 * @param なし
 * @return Vector3：速度
 */
const DirectX::SimpleMath::Vector3& Particle::GetVelocity()
{
	return m_velocity;
}

//------------------------------------------------------------------
/**
 * @brief 大きさの取得
 *
 * @param なし
 * @return Vector3：大きさ
 */
const DirectX::SimpleMath::Vector2& Particle::GetScale()
{
	return m_nowScale;
}

//------------------------------------------------------------------
/**
 * @brief 色の取得
 *
 * @param なし
 * @return Vector3：色
 */
const DirectX::SimpleMath::Color& Particle::GetColor()
{
	return m_nowColor;
}

//------------------------------------------------------------------
/**
 * @brief 生きているか確認
 *
 * @param なし
 * @return true ：生きている
 * @return false：死んでいる
 */
bool Particle::IsAlive()
{
	return m_nowLife > 0.0f;
}
