/**
 *
 * @file ModelComposite.h
 *
 * @brief モデルの親子構造を表すクラスのヘッダーファイル
 *
 * @author Kato Yuki
 *
 * @date 2024/1/29
 *
 */
#pragma once

#include <vector>
#include <functional>
#include "Model.h"
#include "Effects.h"

class ModelComposite
{
//----------------------------------------------
// 変数
//----------------------------------------------
private:

	// モデル
	DirectX::Model* m_model;
	// 初期位置行列
	DirectX::SimpleMath::Matrix m_initial;
	// 変換行列
	DirectX::SimpleMath::Matrix m_transform;
	// ワールド行列
	DirectX::SimpleMath::Matrix m_world;
	// 子
	std::vector<ModelComposite*> m_child;

//----------------------------------------------
// 関数
//----------------------------------------------
public:

	// コンストラクタ
	ModelComposite(DirectX::Model* model, DirectX::SimpleMath::Vector3 localPosition);
	// デストラクタ
	~ModelComposite();
	// 更新
	void Update(const DirectX::SimpleMath::Matrix& worldMatrix);
	// 描画
	void Render(
		DirectX::SimpleMath::Matrix view,
		DirectX::SimpleMath::Matrix projection,
		std::function<void()> custom = nullptr);

	// モデルに適応させるエフェクト更新
	void UpdateEffects(std::function<void(DirectX::IEffect*)> setEffect);
	// 変換行列設定
	void SetTransformMatrix(const DirectX::SimpleMath::Matrix& transformMatrix);
	// 子設定
	void SetChild(ModelComposite* child);
};