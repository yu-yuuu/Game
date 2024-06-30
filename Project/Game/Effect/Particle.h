/**
 *
 * @file Particle.h
 *
 * @brief パーティクルの粒1つを表すクラスのヘッダーファイル
 *
 * @author Kato Yuki
 *
 * @date 2024/1/31
 *
 */
#pragma once

class Particle
{
//----------------------------------------------
// 変数
//----------------------------------------------
private:

	// 位置
	DirectX::SimpleMath::Vector3 m_position;   
	// 速度
	DirectX::SimpleMath::Vector3 m_velocity;   	
	// 加速度
	DirectX::SimpleMath::Vector3 m_acceleration;

	// 現在の体力
	float m_nowLife;  
	// 生成時の体力
	float m_startLife;

	// 現在の大きさ
	DirectX::SimpleMath::Vector2 m_nowScale;
	// 生成時の大きさ
	DirectX::SimpleMath::Vector2 m_startScale;
	// 消滅時の大きさ
	DirectX::SimpleMath::Vector2 m_endScale;   
	
	// 現在の色	
	DirectX::SimpleMath::Color m_nowColor; 
	// 生成時の色
	DirectX::SimpleMath::Color m_startColor; 
	// 消滅時の色
	DirectX::SimpleMath::Color m_endColor; 

	
//----------------------------------------------
// 関数
//----------------------------------------------
public:

	// コンストラクタ
	Particle(
		DirectX::SimpleMath::Vector3 position,
		DirectX::SimpleMath::Vector3 velocity,
		float                        startLife,
		DirectX::SimpleMath::Vector3 acceleration = DirectX::SimpleMath::Vector3::Zero,
		DirectX::SimpleMath::Vector2 startScale   = DirectX::SimpleMath::Vector2::One,
		DirectX::SimpleMath::Vector2 endScale     = DirectX::SimpleMath::Vector2::Zero,
		DirectX::SimpleMath::Color   startColor   = DirectX::SimpleMath::Color(1.0f, 1.0f, 1.0f, 1.0f),
		DirectX::SimpleMath::Color   endColor     = DirectX::SimpleMath::Vector4(1.0f, 1.0f, 1.0f, 0.0f)
	);
	// デストラクタ
	~Particle();

	// 更新
	void Update(const float& elapsedTime);

	// 位置の取得
	const DirectX::SimpleMath::Vector3& GetPosition();
	// 速度の取得
	const DirectX::SimpleMath::Vector3& GetVelocity();
	// 大きさの取得
	const DirectX::SimpleMath::Vector2& GetScale();
	// 色の取得
	const DirectX::SimpleMath::Color& GetColor();
	// 生きているか
	bool IsAlive();
};