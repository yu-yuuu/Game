/**
 *
 * @file ParticleEffect.cpp
 *
 * @brief パーティクルエフェクトを表すクラスのソースファイル
 *
 * @author Kato Yuki
 *
 * @date 2024/1/31
 *
 */
#include "pch.h"
#include "ParticleEffect.h"

#include "Game/MyLibrary/CommonResource/GameResource.h"
#include "Game/Effect/Particle.h"
#include "Game/Effect/EffectManager.h"
#include "Game/MyLibrary/Shader/Shader.h"

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
ParticleEffect::ParticleEffect(EffectManager* effectManager, DirectX::SimpleMath::Vector3 position, std::string textureName, float generateInterval)
	:m_effectManager(effectManager)
	, m_position(position)
	, m_textureName(textureName)
	, m_particleList()
	, m_vertices()
	, m_generateInterval(generateInterval)
	, m_generateTimer(0.0f)
{
}

//------------------------------------------------------------------
/**
 * @brief デストラクタ
 */
ParticleEffect::~ParticleEffect()
{
}

//------------------------------------------------------------------
/**
 * @brief 更新
 *
 * @param  なし
 * @return なし
 */
void ParticleEffect::Update()
{
	// ステップタイマー取得
	DX::StepTimer* stepTimer = GameResource::GetInstance()->GetStepTimer();
	// タイマー進行
	float elapsedTime = static_cast<float>(stepTimer->GetElapsedSeconds());
	m_generateTimer += elapsedTime;
	
	// 生成する間隔の時間がたったか
	if (m_generateInterval < m_generateTimer)
	{
		// タイマーリセット
		m_generateTimer = 0.0f;
		std::unique_ptr<Particle> particle = std::move(m_generateFunction());
		// パーティクル追加
		m_particleList.push_back(std::move(m_generateFunction()));
	}
	// パーティクルの更新
	for (ParticleList::iterator it = m_particleList.begin(); it != m_particleList.end();)
	{
		// 更新
		(*it)->Update(elapsedTime);
		// 死んでいたら削除する
		if ((*it)->IsAlive()) it++;
		else it = m_particleList.erase(it);
	}
}

//------------------------------------------------------------------
/**
 * @brief 描画
 *
 * @param view          ：ビュー行列
 * @param projection    ：射影行列
 * @param eye           ：カメラ位置
 * @param target        ：注視点
 * @param up            ：カメラの頭の向き
 * @return なし
 */
void ParticleEffect::Render(DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix projection, DirectX::SimpleMath::Vector3 eye, DirectX::SimpleMath::Vector3 target, DirectX::SimpleMath::Vector3 up)
{
	// カメラの方向ベクトル計算
	SimpleMath::Vector3 cameraDir = target - eye;
	// カメラの正面でソートを掛ける
	std::sort(m_particleList.begin(), m_particleList.end(),
		[&](std::unique_ptr<Particle>& lhs, std::unique_ptr<Particle>& rhs)
		{
			return cameraDir.Dot(lhs->GetPosition() - eye) > cameraDir.Dot(rhs->GetPosition() - eye);
		}
	);

	// 描画頂点リストリセット
	m_vertices.clear();

	for (std::unique_ptr<Particle>& particle : m_particleList)
	{
		// マイナスならカメラの後ろなので描画しない
		if (cameraDir.Dot(particle->GetPosition() - eye) < 0.0f) continue;

		// 頂点作成
		VertexPositionColorTexture vertex;
		vertex.position          = particle->GetPosition(); // 位置
		vertex.color             = particle->GetColor();    // 色
		vertex.textureCoordinate = particle->GetScale();    // 大きさ
		// 頂点追加
		m_vertices.push_back(vertex);
	}

	// 描画する頂点が無いなら終了
	if (m_vertices.empty()) return;

	// シェーダー取得
	Shader<VertexPositionColorTexture>* shader = m_effectManager->GetShader();
	// 定数バッファの更新
	EffectManager::EffectConstantBuffer ecb;
	ecb.world      = CreateBillboard(eye, up).Transpose();
	ecb.view       = view.Transpose();
	ecb.projection = projection.Transpose();	
	shader->UpdateConstantBuffer(ecb);
	// シェーダーに画像を設定する
	ResourceManager* resourceManager = GameResource::GetInstance()->GetResourceManager();
	shader->RegisterTexture(resourceManager->GetTexture(m_textureName).texture.GetAddressOf());

	// 描画
	shader->Render(&m_vertices[0], static_cast<int>(m_vertices.size()));
}

//------------------------------------------------------------------
/**
 * @brief ビルボード行列作成
 *
 * @param eye：カメラ位置
 * @param up ：カメラの頭の向き
 * @return Matrix：作成したビルボード行列
 */
DirectX::SimpleMath::Matrix ParticleEffect::CreateBillboard(DirectX::SimpleMath::Vector3 eye, DirectX::SimpleMath::Vector3 up)
{
	// ビルボード行列を作成
	DirectX::SimpleMath::Matrix billboard = SimpleMath::Matrix::CreateBillboard(m_position, eye, up);

	// DirectXとTKの座標系が違うのでY軸で180度回転
	SimpleMath::Matrix rot;
	rot._11 = rot._33 = -1.0f;

	return rot * billboard;
}

//------------------------------------------------------------------
/**
 * @brief 生成間隔設定
 *
 * @param  generateInterval：設定する生成間隔
 * @return なし
 */
void ParticleEffect::SetGenerateInterval(const float& generateInterval)
{
	m_generateInterval = generateInterval;
}

//------------------------------------------------------------------
/**
 * @brief パーティクル生成関数設定
 *
 * @param  function：設定する生成関数
 * @return なし
 */
void ParticleEffect::SetGenerateFunction(const std::function<std::unique_ptr<Particle>()>& function)
{
	m_generateFunction = function;
}

//------------------------------------------------------------------
/**
 * @brief 位置取得
 *
 * @param  なし
 * @return Vector3：パーティクルの位置
 */
DirectX::SimpleMath::Vector3 ParticleEffect::GetPosition() const
{
	return m_position;
}