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
#include "pch.h"
#include "PlayerStrategy2D.h"

#include "Game/MyLibrary/CommonResource/GameResource.h"
#include "Game/Player/Player.h"
#include "Game/MyLibrary/Collision/BoxCollider.h"
#include "Game/MyLibrary/Utility/MyUtility.h"

using namespace DirectX;

//------------------------------------------------------------------
/**
 * @brief コンストラクタ
 *
 * @param player：プレイヤーへのポインタ
 */
PlayerStrategy2D::PlayerStrategy2D(Player* player)
	: m_player(player)
{
}

//------------------------------------------------------------------
/**
 * @brief デストラクタ
 */
PlayerStrategy2D::~PlayerStrategy2D()
{
}

//------------------------------------------------------------------
/**
 * @brief 更新
 *
 * @param  なし
 * @return なし
 */
void PlayerStrategy2D::Update()
{
	// 移動入力
	Move();
	// ジャンプ入力
	Jump();
}

//------------------------------------------------------------------
/**
 * @brief 移動
 *
 * @param  なし
 * @return なし
 */
void PlayerStrategy2D::Move()
{
	// キーマネージャー取得
	InputManager* inputManager = GameResource::GetInstance()->GetInputManager();
	// 入力フラグ取得用
	int moveInput = 0;

	// 見下ろし視点の時のみ入力可
	if(m_player->GetScene()->IsTopDown())
	{
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
 * @brief ジャンプ
 *
 * @param  なし
 * @return なし
 */
void PlayerStrategy2D::Jump()
{
	// 見下ろし視点ならジャンプさせない
	if (m_player->GetScene()->IsTopDown()) return;

	// キーマネージャー取得
	InputManager* inputManager = GameResource::GetInstance()->GetInputManager();

	// スペースが押されたらジャンプ
	if (inputManager->GetKey(Keyboard::Keys::Space).press)
	{
		m_player->Jump();
	}
}