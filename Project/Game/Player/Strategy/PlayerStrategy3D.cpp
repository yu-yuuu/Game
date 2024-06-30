/**
 *
 * @file PlayerStrategy3D.cpp
 *
 * @brief プレイヤーの3D機能クラスのソースファイル
 *
 * @author Kato Yuki
 *
 * @date 2023/12/11
 *
 */
#include "pch.h"
#include "PlayerStrategy3D.h"

#include "Game/MyLibrary/CommonResource/GameResource.h"
#include "Game/MyLibrary/GameParameter/GameParameter.h"
#include "Game/Player/Player.h"

using namespace DirectX;

//------------------------------------------------------------------
/**
 * @brief コンストラクタ
 *
 * @param player：プレイヤーへのポインタ
 */
PlayerStrategy3D::PlayerStrategy3D(Player* player)
	: m_player(player)
{
}

//------------------------------------------------------------------
/**
 * @brief デストラクタ
 */
PlayerStrategy3D::~PlayerStrategy3D()
{
}

//------------------------------------------------------------------
/**
 * @brief 更新
 *
 * @param  なし
 * @return なし
 */
void PlayerStrategy3D::Update()
{
	// 移動入力
	Move();
	// ジャンプ入力
	Jump();
}

//------------------------------------------------------------------
/**
 * @brief 移動入力
 *
 * @param  なし
 * @return なし
 */
void PlayerStrategy3D::Move()
{
	// キーマネージャー取得
	InputManager* inputManager = GameResource::GetInstance()->GetInputManager();

	// 入力フラグ取得用
	int moveInput = 0;

	// 奥
	if (inputManager->GetKey(Keyboard::Keys::Up).down)
	{
		moveInput |= KT::GameParam::InputDirection::FORWARD;
	}
	// 手前
	else if (inputManager->GetKey(Keyboard::Keys::Down).down)
	{
		moveInput |= KT::GameParam::InputDirection::BACK;
	}

	// 右
	if (inputManager->GetKey(Keyboard::Keys::Right).down)
	{
		moveInput |= KT::GameParam::InputDirection::RIGHT;
	}
	// 左
	else if (inputManager->GetKey(Keyboard::Keys::Left).down)
	{
		moveInput |= KT::GameParam::InputDirection::LEFT;
	}

	// 移動フラグ設定
	m_player->SetMoveInputFlag(moveInput);
}

//------------------------------------------------------------------
/**
 * @brief ジャンプ入力
 *
 * @param  なし
 * @return なし
 */
void PlayerStrategy3D::Jump()
{
	// キーマネージャー取得
	InputManager* inputManager = GameResource::GetInstance()->GetInputManager();

	// スペースが押されたらジャンプ
	if (inputManager->GetKey(Keyboard::Keys::Space).press)
	{
		m_player->Jump();
	}
}