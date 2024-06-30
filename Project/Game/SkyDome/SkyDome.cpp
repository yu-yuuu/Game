/**
 *
 * @file SkyDome.cpp
 *
 * @brief スカイドームを表すクラスのソースファイル
 *
 * @author Kato Yuki
 *
 * @date 2024/4/7
 *
 */
#include "pch.h"
#include "SkyDome.h"
#include "Effects.h"
#include "Game/MyLibrary/CommonResource/GameResource.h"

using namespace DirectX;

//------------------------------------------------------------------
/**
 * @brief コンストラクタ
 *
 * @param position：スカイドームの中心位置
 */
SkyDome::SkyDome(DirectX::SimpleMath::Vector3 position)
	: m_position(position)
	, m_rotation()
	, m_rotationSpeed(0.0f)
{
	// リソースマネージャー取得
	ResourceManager* resourceManager = GameResource::GetInstance()->GetResourceManager();
	
	// モデルを受け取る
	m_model = resourceManager->GetModel(KT::Model::SKY_DOME);

	// スカイドームのライト設定
	m_model->UpdateEffects([](IEffect* effect)
		{
			IEffectLights* lights = dynamic_cast<IEffectLights*>(effect);

			if (lights)
			{
				// ライトの影響をなくす
				lights->SetAmbientLightColor(SimpleMath::Vector3::Zero);
				lights->SetLightEnabled(0, false);
				lights->SetLightEnabled(1, false);
				lights->SetLightEnabled(2, false);
			}

			BasicEffect* basicEffect = dynamic_cast<BasicEffect*>(effect);
			if (basicEffect)
			{
				// 自己発光させる
				basicEffect->SetEmissiveColor(SimpleMath::Vector3::One);
			}
		}
	);
}

//------------------------------------------------------------------
/**
 * @brief デストラクタ
 */
SkyDome::~SkyDome()
{
}

//------------------------------------------------------------------
/**
 * @brief 更新
 *
 * @param  なし
 * @return なし
 */
void SkyDome::Update()
{
	// 回転速度が設定されているか
	if (std::fabsf(m_rotationSpeed) <= std::numeric_limits<float>::epsilon()) return;
	// 回転を掛ける
	m_rotation *= SimpleMath::Quaternion::CreateFromAxisAngle(SimpleMath::Vector3::UnitY, m_rotationSpeed);
}

//------------------------------------------------------------------
/**
 * @brief 描画
 *
 * @param  なし
 * @return なし
 */
void SkyDome::Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection)
{
	// 各種リソース取得
	GameResource*         gameResource = GameResource::GetInstance();
	ID3D11DeviceContext1* context      = gameResource->GetDeviceResources()->GetD3DDeviceContext();
	CommonStates*         commonStates = gameResource->GetCommonStates();

	// スカイドームの描画
	SimpleMath::Matrix skyWorld = SimpleMath::Matrix::CreateFromQuaternion(m_rotation) *
		SimpleMath::Matrix::CreateTranslation(m_position);
	m_model->Draw(context, *commonStates, skyWorld, view, projection);
}

//------------------------------------------------------------------
/**
 * @brief 位置の設定
 *
 * @param position：設定する位置
 * @return なし
 */
void SkyDome::SetPosition(const DirectX::SimpleMath::Vector3& position)
{
	m_position = position;
}

//------------------------------------------------------------------
/**
 * @brief 回転速度の設定
 *
 * @param  rotationSpeed：設定する回転速度
 * @return なし
 */
void SkyDome::SetRotationSpeed(const float& rotationSpeed)
{
	m_rotationSpeed = rotationSpeed;
}