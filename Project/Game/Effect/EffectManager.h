/**
 *
 * @file Particle.h
 *
 * @brief パーティクルエフェクトクラスのヘッダーファイル
 *
 * @author Kato Yuki
 *
 * @date 2024/1/25
 *
 */
#pragma once
#include <vector>
#include "VertexTypes.h"
#include "Game/Effect/IEffect.h"

template<typename Vertex>
class Shader;

class EffectManager
{
//----------------------------------------------
// 構造体
//----------------------------------------------
public:

	// エフェクトに使用する定数バッファ
	struct EffectConstantBuffer
	{
		DirectX::SimpleMath::Matrix world;
		DirectX::SimpleMath::Matrix view;
		DirectX::SimpleMath::Matrix projection;
	};

//----------------------------------------------
// 変数
//----------------------------------------------
private:

	// エフェクトリスト
	std::vector<KT::IEffect*> m_list;
	// シェーダー
	std::unique_ptr<Shader<DirectX::VertexPositionColorTexture>> m_shader;

//----------------------------------------------
// 関数
//----------------------------------------------
public:

	// コンストラクタ
	EffectManager();
	// デストラクタ
	~EffectManager();

	// 初期化
	void Initialize();
	// 更新
	void Update();
	// 描画
	void Render(
		const DirectX::SimpleMath::Matrix& view,
		const DirectX::SimpleMath::Matrix& projection,
		const DirectX::SimpleMath::Vector3 eye,
		const DirectX::SimpleMath::Vector3 target,
		const DirectX::SimpleMath::Vector3 up);

	// シェーダーの取得
	Shader<DirectX::VertexPositionColorTexture>* GetShader() const;
	// エフェクトの追加
	void AddEffect(KT::IEffect* effect);
	// エフェクトの削除
	void DeleteEffect(KT::IEffect* effect);
	// エフェクト全削除
	void Clear();
};