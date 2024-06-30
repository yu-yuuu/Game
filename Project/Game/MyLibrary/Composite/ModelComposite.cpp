/**
 *
 * @file ModelComposite.cpp
 *
 * @brief モデルの親子構造を表すクラスのソースファイル
 *
 * @author Kato Yuki
 *
 * @date 2024/1/29
 *
 */
#include "pch.h"
#include "ModelComposite.h"
#include "Game/MyLibrary/CommonResource/GameResource.h"

using namespace DirectX;

//------------------------------------------------------------------
/**
 * @brief コンストラクタ
 *
 * @param model：ローカル座標
 */
ModelComposite::ModelComposite(DirectX::Model* model, DirectX::SimpleMath::Vector3 localPosition)
	: m_model(model)
	, m_transform()
	, m_world()
	, m_child()
{
	// 初期位置の行列を計算
	m_initial = SimpleMath::Matrix::CreateTranslation(localPosition);
}

//------------------------------------------------------------------
/**
 * @brief デストラクタ
 */
ModelComposite::~ModelComposite()
{
}

//------------------------------------------------------------------
/**
 * @brief 更新
 *
 * @param  worldMatrix：ワールド行列
 * @return なし
 */
void ModelComposite::Update(const DirectX::SimpleMath::Matrix& worldMatrix)
{
	// 自身のローカル行列を計算
	m_world = m_transform * m_initial;

	// 自身のローカル行列と引数の行列でワールド座標を計算する
	m_world *= worldMatrix;

	// 子のワールド行列を更新する
	for (ModelComposite* child : m_child)
	{
		child->Update(m_world);
	}
}

//------------------------------------------------------------------
/**
 * @brief 描画
 *
 * @param  view      ：ビュー行列
 * @param  projection：射影行列
 * @param  custom    ：モデルに適応させるラムダ式
 * @return なし
 */
void ModelComposite::Render(DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix projection, std::function<void()> custom)
{
	// 各種リソース取得
	GameResource*         gameResource = GameResource::GetInstance();
	ID3D11DeviceContext1* context      = gameResource->GetDeviceResources()->GetD3DDeviceContext();
	CommonStates*         commonStates = gameResource->GetCommonStates();

	// 登録されているモデルを描画
	if(m_model) m_model->Draw(context, *commonStates, m_world, view, projection, false, custom);

	// 子のモデルを描画
	for (ModelComposite* child : m_child)
	{
		child->Render(view, projection, custom);
	}
}

//------------------------------------------------------------------
/**
 * @brief モデルに適応させるエフェクト更新
 *
 * @param  setEffect：モデルに適応させるエフェクト
 * @return なし
 */
void ModelComposite::UpdateEffects(std::function<void(IEffect*)> setEffect)
{
	// エフェクト更新
	if(m_model) m_model->UpdateEffects(setEffect);

	// 自身の子にも適応させる
	for (ModelComposite* child : m_child)
	{
		child->UpdateEffects(setEffect);
	}
}

//------------------------------------------------------------------
/**
 * @brief 変換行列設定
 *
 * @param  transformMatrix：変換行列
 * @return なし
 */
void ModelComposite::SetTransformMatrix(const DirectX::SimpleMath::Matrix& transformMatrix)
{
	m_transform = transformMatrix;
}

//------------------------------------------------------------------
/**
 * @brief 子を設定
 *
 * @param  child：設定する子
 * @return なし
 */
void ModelComposite::SetChild(ModelComposite* child)
{
	// 子を追加
	m_child.push_back(child);
}