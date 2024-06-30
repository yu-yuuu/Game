/**
 *
 * @file GoalEffect.h
 *
 * @brief ゴールエフェクトを表すクラスのソースファイル
 *
 * @author Kato Yuki
 *
 * @date 2024/2/1
 *
 */
#include "pch.h"
#include "GoalEffect.h"
#include <random>
#include "Game/MyLibrary/CommonResource/GameResource.h"
#include "Game/Effect/Particle.h"

using namespace DirectX;

//------------------------------------------------------------------
/**
 * @brief コンストラクタ
 *
 * @param effectManager   ：エフェクトマネージャーのポインタ
 * @param position        ：位置
 * @param textureName     ：使用する画像の名前
 * @param generateInterval：生成間隔
 */
GoalEffect::GoalEffect(EffectManager* effectManager, DirectX::SimpleMath::Vector3 position, std::string textureName, float generateInterval)
	: ParticleEffect(effectManager, position, textureName, generateInterval)
	, m_timer(0.0f)
{
}

//------------------------------------------------------------------
/**
 * @brief デストラクタ
 */
GoalEffect::~GoalEffect()
{
}

//------------------------------------------------------------------
/**
 * @brief 更新
 *
 * @param  なし
 * @return なし
 */
void GoalEffect::Update()
{
	// ステップタイマー取得
	DX::StepTimer* stepTimer = GameResource::GetInstance()->GetStepTimer();
	// タイマー進行
	double elapsedTime = stepTimer->GetElapsedSeconds();
	m_timer += static_cast<float>(elapsedTime);

	// パーティクル生成関数作成
	std::function<std::unique_ptr<Particle>()> function = 
		[&]()
	{
		// 乱数生成
		std::random_device rd;
		std::mt19937 mt(rd());
		std::uniform_real_distribution<float> posRand(-RANDOM_POSITION, RANDOM_POSITION);
		std::uniform_real_distribution<float> accelRand(-RANDOM_ACCELERATION, RANDOM_ACCELERATION);
		// 生成位置
		SimpleMath::Vector3 position =  SimpleMath::Vector3(posRand(rd), 0.0f, posRand(rd));
		// 速度
		SimpleMath::Vector3 velocity = SimpleMath::Vector3(0.0f, 0.1f, 0.0f);
		// 加速度
		SimpleMath::Vector3 acceleration = SimpleMath::Vector3(accelRand(mt), 0.0f, accelRand(mt));
		// パーティクル生成
		return std::make_unique<Particle>(
			position + GetPosition(),
			VELOCITY,
			START_LIFE,
			acceleration,
			START_SCALE, END_SCALE,
			START_COLOR, END_COLOR
		);
	};

	// 生成関数設定
	SetGenerateFunction(function);
	// 基底クラスの更新
	ParticleEffect::Update();
}

//------------------------------------------------------------------
/**
 * @brief 描画
 *
 * @param  view      ：ビュー行列
 * @param  projection：射影行列
 * @param  eye       ：カメラ位置
 * @param  target    ：注視点
 * @param  up        ：カメラの頭の向き
 * @return なし
 */
void GoalEffect::Render(DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix projection, DirectX::SimpleMath::Vector3 eye, DirectX::SimpleMath::Vector3 target, DirectX::SimpleMath::Vector3 up)
{
	ParticleEffect::Render(view, projection, eye, target, up);
}