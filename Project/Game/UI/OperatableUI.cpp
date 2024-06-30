/**
 *
 * @file OperatableUI.cpp
 *
 * @brief 操作するUIを表すクラスのソースファイル
 *
 * @author Kato Yuki
 *
 * @date 2024/5/2
 *
 */
#include "pch.h"
#include "OperatableUI.h"
#include "Game/MyLibrary/CommonResource/GameResource.h"

//------------------------------------------------------------------
/**
 * @brief コンストラクタ
 *
 * @param  tagList ：タグリスト
 * @param  texture ：使用するテクスチャデータ
 * @param  position：描画位置（スクリーン）
 * @param  key     ：対応させるキー
 * @param  reverseX：テクスチャを横に反転させるか
 * @param  reverseY：テクスチャを縦に反転させるか
 */
OperatableUI::OperatableUI(
	const std::vector<std::string>& tagList,
	std::unique_ptr<Texture> texture,
	const DirectX::SimpleMath::Vector2& position, 
	DirectX::Keyboard::Keys key,
	bool reverseX,
	bool reverseY
)
	: UI(tagList, std::move(texture), position, reverseX, reverseY)
	, m_key(key)
	, m_isActive(true)
{
	// 各状態の初期設定
	m_selectState = { NORMAL_SCALE , NORMAL_SCALE, RED, WHITE };
	m_activeState = { NORMAL_SCALE , DISABLE_SCALE, WHITE, GRAY };
	m_pushState   = { NORMAL_SCALE , NORMAL_SCALE, RED, WHITE };
}

//------------------------------------------------------------------
/**
 * @brief デストラクタ
 */
OperatableUI::~OperatableUI()
{
}

//------------------------------------------------------------------
/**
 * @brief 状態の設定
 *
 * @param  type   ：設定する状態タイプ
 * @param  uiState：設定する状態
 * @return なし
 */
void OperatableUI::SetState(UIStateType type, const UIState& uiState)
{
	switch (type)
	{
	// 選択状態
	case OperatableUI::UIStateType::SELECT:
		m_selectState = uiState;
		break;
	// 有効状態
	case OperatableUI::UIStateType::ACTIVE:
		m_activeState = uiState;
		break;
	// 入力状態
	case OperatableUI::UIStateType::PUSH:
		m_pushState = uiState;
		break;
	// 例外
	default:
		assert(false && "OperatableUIの状態が無効です");
		break;
	}
}

//------------------------------------------------------------------
/**
 * @brief 選択状態の更新
 *
 * @param  isSelect：選択されているか
 * @return なし
 */
void OperatableUI::SelectStateUpdate(bool isSelect)
{
	// 有効状態でなければ処理を行わない
	if (!m_isActive) return;

	// 状態更新
	StateUpdate(isSelect, m_selectState);
}

//------------------------------------------------------------------
/**
 * @brief 有効状態の更新
 *
 * @param  isActive：選択されているか
 * @return なし
 */
void OperatableUI::ActiveStateUpdate(bool isActive)
{
	// フラグ設定
	m_isActive = isActive;
	// 状態更新
	StateUpdate(isActive, m_activeState);
}

//------------------------------------------------------------------
/**
 * @brief 入力状態の更新
 *
 * @param  なし
 * @return なし
 */
void OperatableUI::PushStateUpdate()
{
	// 有効状態でなければ処理を行わない
	if (!m_isActive) return;

	// 入力マネージャー取得
	InputManager* inputManager = GameResource::GetInstance()->GetInputManager();
	// 状態更新
	StateUpdate(inputManager->GetKey(m_key).down, m_pushState);
}

//------------------------------------------------------------------
/**
 * @brief キーの取得
 *
 * @param  なし
 * @return Keys：登録してあるキー
 */
DirectX::Keyboard::Keys OperatableUI::GetKey() const
{
	return m_key;
}

//------------------------------------------------------------------
/**
 * @brief 状態の更新
 *
 * @param  flag   ：状態更新フラグ
 * @param  uiState：設定する状態
 * @return なし
 */
void OperatableUI::StateUpdate(bool flag, const UIState& uiState)
{
	// 状態更新
	Texture* texture = GetTexture();
	if (flag)
	{
		texture->SetScale(uiState.enableScale);
		texture->SetColor(uiState.enableColor);
	}
	else
	{
		texture->SetScale(uiState.disableScale);
		texture->SetColor(uiState.disableColor);
	}
}