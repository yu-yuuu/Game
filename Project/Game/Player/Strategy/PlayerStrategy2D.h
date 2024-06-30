/**
 *
 * @file PlayerStrategy2D.h
 *
 * @brief プレイヤーの3D機能クラス
 *
 * @author Kato Yuki
 *
 * @date 2023/12/11
 *
 */
#pragma once

#include "Game/Player/Strategy/IPlayerStrategy.h"

class Player;

class PlayerStrategy2D : public IPlayerStrategy
{
//----------------------------------------------
// 変数
//----------------------------------------------
private:

	// プレイヤー
	Player* m_player;

//----------------------------------------------
// 関数
//----------------------------------------------
public:

	// コンストラクタ
	PlayerStrategy2D(Player* player);
	// デストラクタ
	~PlayerStrategy2D();
	// 更新
	void Update() override;
	// 移動入力
	void Move() override;
	// ジャンプ入力
	void Jump() override;
};
