/**
 *
 * @file OperatableUI.h
 *
 * @brief 操作するUIを表すクラスのヘッダーファイル
 *
 * @author Kato Yuki
 *
 * @date 2024/5/2
 *
 */
#pragma once

#include "Game/UI/UI.h"
#include "Game/MyLibrary/Texture/Texture.h"

class OperatableUI : public UI
{
//----------------------------------------------
// 構造体
//----------------------------------------------
public:

	// UIの状態
	struct UIState
	{
		// 有効、無効時の拡大率
		DirectX::SimpleMath::Vector2 enableScale;
		DirectX::SimpleMath::Vector2 disableScale;
		// 有効、無効時の色合い
		DirectX::SimpleMath::Color enableColor;
		DirectX::SimpleMath::Color disableColor;
	};

	// 状態の種類
	enum class UIStateType
	{
		SELECT, // 選択状態
		ACTIVE, // 有効状態
		PUSH,   // 入力状態
	};

//----------------------------------------------
// 定数
//----------------------------------------------
private:

	// 有効、無効時の拡大率
	const DirectX::SimpleMath::Vector2 NORMAL_SCALE  = DirectX::SimpleMath::Vector2::One;
	const DirectX::SimpleMath::Vector2 DISABLE_SCALE = DirectX::SimpleMath::Vector2(0.9f, 0.9f);
	// 有効、無効、入力時の色合い
	const DirectX::SimpleMath::Color WHITE = DirectX::SimpleMath::Color(1.0f, 1.0f, 1.0f, 1.0f);
	const DirectX::SimpleMath::Color GRAY  = DirectX::SimpleMath::Color(0.5f, 0.5f, 0.5f, 1.0f);
	const DirectX::SimpleMath::Color RED   = DirectX::SimpleMath::Color(1.0f, 0.0f, 0.0f, 1.0f);

//----------------------------------------------
// 変数
//----------------------------------------------
private:
	
	// 選択状態
	UIState m_selectState;
	// 有効状態
	UIState m_activeState;
	// 入力状態
	UIState m_pushState;

	// 有効状態か
	bool m_isActive;
	// 対応させるキー
	DirectX::Keyboard::Keys m_key;

//----------------------------------------------
// 関数
//----------------------------------------------
public:

	// コンストラクタ
	OperatableUI(
		const std::vector<std::string>& tagList,
		std::unique_ptr<Texture> texture,
		const DirectX::SimpleMath::Vector2& position,
		DirectX::Keyboard::Keys key = DirectX::Keyboard::Keys::None,
		bool reverseX = false,
		bool reverseY = false
	);	
	// デストラクタ
	~OperatableUI();

	// 状態の設定
	void SetState(UIStateType type, const UIState& uiState);

	// 選択状態の更新
	void SelectStateUpdate(bool isSelect);
	// 有効状態の更新
	void ActiveStateUpdate(bool isActive);
	// 入力状態の更新
	void PushStateUpdate();

	// キーの取得
	DirectX::Keyboard::Keys GetKey() const;

private:

	// 状態の更新
	void StateUpdate(bool flag, const UIState& uiState);
};