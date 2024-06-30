/**
 *
 * @file GoalEffect.h
 *
 * @brief ゴールエフェクトを表すクラスのヘッダーファイル
 *
 * @author Kato Yuki
 *
 * @date 2024/2/1
 *
 */
#pragma once

#include "Game/Effect/ParticleEffect.h"

class GoalEffect : public ParticleEffect
{
//----------------------------------------------
// 定数
//----------------------------------------------
private:

	// 生成位置の幅
	const float RANDOM_POSITION = 0.1f;
	// 加速度の幅
	const float RANDOM_ACCELERATION = 0.0001f;
	// 速度
	const DirectX::SimpleMath::Vector3 VELOCITY = DirectX::SimpleMath::Vector3(0.0f, 0.1f, 0.0f);
	// 生成時の体力
	const float START_LIFE = 1.0f;
	// 生成、消滅時の大きさ
	DirectX::SimpleMath::Vector2 START_SCALE = DirectX::SimpleMath::Vector2(0.5f, 0.5f);
	DirectX::SimpleMath::Vector2 END_SCALE   = DirectX::SimpleMath::Vector2(0.0f, 0.0f);
	// 生成、消滅時の色
	DirectX::SimpleMath::Color START_COLOR = DirectX::SimpleMath::Color(1.0f, 0.0780f, 0.570f, 1.0f);
	DirectX::SimpleMath::Color END_COLOR   = START_COLOR;


//----------------------------------------------
// 変数
//----------------------------------------------
private:

	// タイマー
	float m_timer;

//----------------------------------------------
// 関数
//----------------------------------------------
public:

	// コンストラクタ
	GoalEffect(
		EffectManager* effectManager,
		DirectX::SimpleMath::Vector3 position, 
		std::string textureName, 
		float generateInterval = 0.0f);
	// デストラクタ
	~GoalEffect();

	// 更新
	void Update() override;
	// 描画
	void Render(
		DirectX::SimpleMath::Matrix view,
		DirectX::SimpleMath::Matrix projection,
		DirectX::SimpleMath::Vector3 eye,
		DirectX::SimpleMath::Vector3 target,
		DirectX::SimpleMath::Vector3 up ) override;
};