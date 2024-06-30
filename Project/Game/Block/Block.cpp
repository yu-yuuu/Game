/**
 *
 * @file Block.cpp
 *
 * @brief ステージを形成するブロックの基底クラスのソースファイル
 *
 * @author Kato Yuki
 *
 * @date 2023/12/28
 *
 */
#include "pch.h"
#include "Block.h"
#include "Game/MyLibrary/CommonResource/GameResource.h"
#include "Game/MyLibrary/ResourceManager/ResourceType.h"

using namespace DirectX;

//------------------------------------------------------------------
/**
 * @brief コンストラクタ
 *
 * @param  type         ：ブロックの種類
 * @param  collisionMode：当たり判定モード
 * @param  position     ：生成位置
 * @param  model        ：ブロックモデル
 */
Block::Block(
	KT::Block::Type type,
	KT::Block::CollisionMode collisionMode,
	const DirectX::SimpleMath::Vector3& position,
	DirectX::Model* model
)
	: m_type(type)
	, m_collisionMode(collisionMode)
	, m_model(model)
	, m_collider(nullptr)
{
	// 初期位置設定
	SetPosition(position);
}

//------------------------------------------------------------------
/**
 * @brief デストラクタ
 */
Block::~Block()
{
}

//------------------------------------------------------------------
/**
 * @brief 初期化
 *
 * @param  effect：モデルに適応させるエフェクト
 * @return なし
 */
void Block::Initialize(std::function<void(DirectX::IEffect* effect)> effect)
{
	if(effect) m_model->UpdateEffects(effect);
}

//------------------------------------------------------------------
/**
 * @brief 更新
 *
 * @param  なし
 * @return なし
 */
void Block::Update()
{
}

//------------------------------------------------------------------
/**
 * @brief 描画
 *
 * @param  view      ：ビュー行列
 * @param  projection：射影行列
 * @param  custom    ：ブロックに適応させるラムダ式
 * @return なし
 */
void Block::Render(
	DirectX::SimpleMath::Matrix view, 
	DirectX::SimpleMath::Matrix projection,
	std::function<void()> custom)
{
	// モデルが設定されていない又は
	// アクティブ状態でない時は描画しない
	if (m_model == nullptr || !IsActive()) return;
	
	// 各種リソース取得
	GameResource*         gameResource = GameResource::GetInstance();
	ID3D11DeviceContext1* context      = gameResource->GetDeviceResources()->GetD3DDeviceContext();
	CommonStates*         commonStates = gameResource->GetCommonStates();

	// ワールド行列取得
	SimpleMath::Matrix world = GetWorldMatrix();

	// モデル描画
	m_model->Draw(context, *commonStates, world, view, projection, false, custom);
}

//------------------------------------------------------------------
/**
 * @brief 後処理
 *
 * @param  なし
 * @return なし
 */
void Block::Finalize()
{
}

//------------------------------------------------------------------
/**
 * @brief 種類の取得
 *
 * @param なし
 * @return Type：ブロックの種類
 */
KT::Block::Type Block::GetType()
{
	return m_type;
}

//------------------------------------------------------------------
/**
 * @brief 種類の設定
 *
 * @param  type：設定するブロックの種類
 * @return なし
 */
void Block::SetType(KT::Block::Type type)
{
	m_type = type;
}

//------------------------------------------------------------------
/**
 * @brief モデル取得
 *
 * @param  なし
 * @return Model*：モデルのポインタ
 */
DirectX::Model* Block::GetModel() const
{
	return m_model;
}

//------------------------------------------------------------------
/**
 * @brief 当たり判定境界図形取得
 *
 * @param なし
 * @return CollisionShape*：当たり判定境界図形へのポインタ
 */
Collider* Block::GetCollider() const
{
	return m_collider.get();
}

//------------------------------------------------------------------
/**
 * @brief 当たり判定境界図形設定
 *
 * @param  collider：設定する境界図形
 * @return なし
 */
void Block::SetCollider(std::unique_ptr<Collider> collider)
{
	m_collider = std::move(collider);
	m_collider->SetGameObject(this);
}

//------------------------------------------------------------------
/**
 * @brief 当たり判定モード取得
 *
 * @param なし
 * @return CollisionMode：当たり判定モード
 */
KT::Block::CollisionMode Block::GetCollisionMode() const
{
	return m_collisionMode;
}