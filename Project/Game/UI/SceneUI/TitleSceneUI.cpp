/**
 *
 * @file TitleSceneUI.cpp
 *
 * @brief タイトルシーンシーンで使用するUI、画像クラスのソースファイル
 *
 * @author Kato Yuki
 *
 * @date 2024/1/22
 *
 */
#include "pch.h"
#include "TitleSceneUI.h"

#include "Game/MyLibrary/CommonResource/GameResource.h"
#include "Game/Scene/TitleScene.h"
#include "Game/UI/OperatableUI.h"

using namespace DirectX;

//------------------------------------------------------------------
/**
 * @brief コンストラクタ
 *
 * @param titleScene：タイトルシーンのポインタ
 */
TitleSceneUI::TitleSceneUI(TitleScene* titleScene)
	: m_titleScene(titleScene)
	, m_pushEnterText()
{
}

//------------------------------------------------------------------
/**
 * @brief デストラクタ
 */
TitleSceneUI::~TitleSceneUI()
{
}

//------------------------------------------------------------------
/**
 * @brief 初期化
 *
 * @param  なし
 * @return なし
 */
void TitleSceneUI::Initialize()
{
	namespace TextureName = KT::Texture;

	// UI作成
	CreateUI(KT::UI::PROPERTIE_TITLE);
	// 操作UI取得
	m_pushEnterText = GetUI(KT::UI::TITLE_PUSH_ENTER_TEXT);

	// UIマネージャーに登録
	AddUIManager(TAG_ALWAYS);
	AddUIManager(TAG_PUSH_ENTER);
	// 自身をUIマネージャーへ登録
	SetUIManagerSceneUI();
}

//------------------------------------------------------------------
/**
 * @brief 更新
 *
 * @param  なし
 * @return なし
 */
void TitleSceneUI::Update()
{
	// ステップタイマー取得
	DX::StepTimer* stepTimer = GameResource::GetInstance()->GetStepTimer();
	// sinで点滅
	float alpha = std::sinf(static_cast<float>(stepTimer->GetTotalSeconds()));
	// -1 ～ 1 を 0 ～ 1 の範囲に収める
	alpha = alpha * FLASH_ADJUSTMENT + FLASH_ADJUSTMENT;
	// 透明度を設定
	SimpleMath::Color color = m_pushEnterText->GetTexture()->GetColor();
	m_pushEnterText->GetTexture()->SetColor(SimpleMath::Color(color.R(), color.G(), color.B(), alpha));
}

//------------------------------------------------------------------
/**
 * @brief 次元切替状態に切り替え
 *
 * @param  なし
 * @return なし
 */
void TitleSceneUI::ChangeStateSwitching()
{
	// エンターキー入力待機状態のUIの登録解除
	DeleteUIManager(TAG_PUSH_ENTER);
	// UIの更新処理は無いのでシーンUI登録解除
	DeleteUIManagerSceneUI();
}

//------------------------------------------------------------------
/**
 * @brief モード選択状態に切り替え
 *
 * @param  なし
 * @return なし
 */
void TitleSceneUI::ChangeStateModeSelect()
{
	// モード選択状態のUIを登録
	AddUIManager(TAG_MODE_SELECT);
}