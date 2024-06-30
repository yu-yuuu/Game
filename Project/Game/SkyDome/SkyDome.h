/**
 *
 * @file SkyDome.h
 *
 * @brief スカイドームを表すクラスのヘッダーファイル
 *
 * @author Kato Yuki
 *
 * @date 2024/4/7
 *
 */
#pragma once

#include "Model.h"

class SkyDome
{
//----------------------------------------------
// 変数
//----------------------------------------------
private:

	// スカイドームモデル
	DirectX::Model* m_model;
	// 位置
	DirectX::SimpleMath::Vector3 m_position;
	// 回転
	DirectX::SimpleMath::Quaternion m_rotation;
	// 回転速度
	float m_rotationSpeed;

//----------------------------------------------
// 関数
//----------------------------------------------
public:

	// コンストラクタ
	SkyDome(DirectX::SimpleMath::Vector3 position);
	// デストラクタ
	~SkyDome();

	// 更新
	void Update();
	// 描画
	void Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection);

	// 位置の設定
	void SetPosition(const DirectX::SimpleMath::Vector3& position);
	// 回転速度の設定
	void SetRotationSpeed(const float& rotationSpeed);
};