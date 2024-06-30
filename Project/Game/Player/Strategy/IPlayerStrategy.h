/**
 *
 * @file IPlayerStrategy.h
 *
 * @brief プレイヤー機能クラスのインターフェース
 *
 * @author Kato Yuki
 *
 * @date 2023/12/11
 *
 */
#pragma once

class IPlayerStrategy
{
//----------------------------------------------
// 関数
//----------------------------------------------
public:

	// デストラクタ
	virtual ~IPlayerStrategy() = default;
	// 更新
	virtual void Update() = 0;
	// 移動入力
	virtual void Move() = 0;
	// ジャンプ入力
	virtual void Jump() = 0;
};
