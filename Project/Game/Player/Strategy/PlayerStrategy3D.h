/**
 *
 * @file PlayerStrategy3D.h
 *
 * @brief プレイヤーの3D機能クラスのヘッダーファイル
 *
 * @author Kato Yuki
 *
 * @date 2023/12/11
 *
 */
#pragma once

#include "Game/Player/Strategy/IPlayerStrategy.h"

class Player;

class PlayerStrategy3D : public IPlayerStrategy
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
	PlayerStrategy3D(Player* player);
	// デストラクタ
	~PlayerStrategy3D();
	// 更新
	void Update() override;
	// 移動
	void Move() override;
	// ジャンプ入力
	void Jump() override;
};