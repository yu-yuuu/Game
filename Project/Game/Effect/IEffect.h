/**
 *
 * @file IEffect.h
 *
 * @brief エフェクトのインターフェースクラス
 *
 * @author Kato Yuki
 *
 * @date 2024/1/31
 *
 */
#pragma once
namespace KT
{
	class IEffect
	{
	public:

		// デストラクタ
		virtual ~IEffect() = default;
		// 更新
		virtual void Update() = 0;
		// 描画
		virtual void Render(
			DirectX::SimpleMath::Matrix view,
			DirectX::SimpleMath::Matrix projection,
			DirectX::SimpleMath::Vector3 eye,
			DirectX::SimpleMath::Vector3 target,
			DirectX::SimpleMath::Vector3 up
		) = 0;

	};
}
