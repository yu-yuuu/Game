/**
 *
 * @file ParticleEffect.h
 *
 * @brief パーティクルエフェクトを表すクラスのヘッダーファイル
 *
 * @author Kato Yuki
 *
 * @date 2024/1/31
 *
 */
#pragma once

#include <string>
#include <vector>
#include <functional>
#include "VertexTypes.h"
#include "Game/Effect/IEffect.h"

class EffectManager;
class Particle;

class ParticleEffect : public KT::IEffect
{
//----------------------------------------------
// エイリアス宣言
//----------------------------------------------
private:

	// パーティクルリスト
	using ParticleList = std::vector<std::unique_ptr<Particle>>;

//----------------------------------------------
// 変数
//----------------------------------------------
private:

	// エフェクトマネージャー
	EffectManager* m_effectManager;
	// パーティクルの中心位置
	DirectX::SimpleMath::Vector3 m_position;
	// 使用するテクスチャの名前
	std::string m_textureName;
	// パーティクルリスト
	ParticleList m_particleList;
	// 描画頂点リスト
	std::vector<DirectX::VertexPositionColorTexture> m_vertices;
	// パーティクル生成間隔
	float m_generateInterval;
	// パーティクル生成タイマー
	float m_generateTimer;
	// パーティクル生成関数
	std::function<std::unique_ptr<Particle>()> m_generateFunction;

//----------------------------------------------
// 関数
//----------------------------------------------
public:

	// コンストラクタ
	ParticleEffect(
		EffectManager* effectManager, 
		DirectX::SimpleMath::Vector3 position, 
		std::string textureName, 
		float generateInterval = 0.0f
	);
	// デストラクタ
	virtual ~ParticleEffect();

	// 更新
	virtual void Update() override;
	// 描画
	virtual void Render(
		DirectX::SimpleMath::Matrix view,
		DirectX::SimpleMath::Matrix projection,
		DirectX::SimpleMath::Vector3 eye,
		DirectX::SimpleMath::Vector3 target,
		DirectX::SimpleMath::Vector3 up
	) override;

	// ビルボード行列作成
	DirectX::SimpleMath::Matrix CreateBillboard(
		DirectX::SimpleMath::Vector3 eye,
		DirectX::SimpleMath::Vector3 up
	);
	// 生成間隔設定
	void SetGenerateInterval(const float& generateInterval);
	// パーティクル生成関数設定
	void SetGenerateFunction(const std::function<std::unique_ptr<Particle>()>& function);
	// 位置取得
	DirectX::SimpleMath::Vector3 GetPosition() const;
};