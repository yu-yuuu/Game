/**
 *
 * @file Particle.cpp
 *
 * @brief パーティクルエフェクトクラスのソースファイル
 *
 * @author Kato Yuki
 *
 * @date 2024/1/25
 *
 */
#include "pch.h"
#include "EffectManager.h"

#include "Game/MyLibrary/CommonResource/GameResource.h"
#include "Game/MyLibrary/Shader/Shader.h"

using namespace DirectX;

//------------------------------------------------------------------
/**
 * @brief コンストラクタ
 *
 * @param  なし
 */
EffectManager::EffectManager()
	: m_list()
	, m_shader(nullptr)
{
}

//------------------------------------------------------------------
/**
 * @brief デストラクタ
 */
EffectManager::~EffectManager()
{
}

//------------------------------------------------------------------
/**
 * @brief 初期化
 *
 * @param  なし
 * @return なし
 */
void EffectManager::Initialize()
{
	// シェーダーの作成
	m_shader = std::make_unique<Shader<VertexPositionColorTexture>>();
	m_shader->CreateData(KT::Shader::EFFECT);
	m_shader->CreateConstantBuffer<EffectConstantBuffer>();
}

//------------------------------------------------------------------
/**
 * @brief 更新
 *
 * @param  なし
 * @return なし
 */
void EffectManager::Update()
{
	for (KT::IEffect* effect : m_list)
	{
		effect->Update();
	}
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
void EffectManager::Render(const DirectX::SimpleMath::Matrix& view,
	const DirectX::SimpleMath::Matrix& projection,
	const DirectX::SimpleMath::Vector3 eye,
	const DirectX::SimpleMath::Vector3 target,
	const DirectX::SimpleMath::Vector3 up)
{
	for (KT::IEffect* effect : m_list)
	{
		effect->Render(view, projection, eye, target, up);
	}
}

//------------------------------------------------------------------
/**
 * @brief シェーダーの取得
 *
 * @param  なし
 * @return Shader<Vertex>*：シェーダーのポインタ
 */
Shader<DirectX::VertexPositionColorTexture>* EffectManager::GetShader() const
{
	return m_shader.get();
}

//------------------------------------------------------------------
/**
 * @brief エフェクトの追加
 *
 * @param  effect：追加するエフェクト
 * @return なし
 */
void EffectManager::AddEffect(KT::IEffect* effect)
{
	m_list.push_back(effect);
}

//------------------------------------------------------------------
/**
 * @brief エフェクトの削除
 *
 * @param  effect：削除するエフェクト
 * @return なし
 */
void EffectManager::DeleteEffect(KT::IEffect* effect)
{
	if (m_list.empty()) return;
	std::vector<KT::IEffect*>::iterator it = std::find(m_list.begin(), m_list.end(), effect);
	if(it != m_list.end()) m_list.erase(it);
}

//------------------------------------------------------------------
/**
 * @brief エフェクト全削除
 *
 * @param  なし
 * @return なし
 */
void EffectManager::Clear()
{
	m_list.clear();
}