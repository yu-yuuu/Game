/**
 *
 * @file MenuWindowUI.cpp
 *
 * @brief メニューウィンドウのUIをまとめるクラスのソースファイル
 *
 * @author Kato Yuki
 *
 * @date 2024/2/2
 *
 */
#include "pch.h"
#include "MenuWindowUI.h"

#include "Game/MyLibrary/CommonResource/GameResource.h"
#include "Game/UI/OperatableUI.h"

using namespace DirectX;

//------------------------------------------------------------------
/**
 * @brief コンストラクタ
 *
 * @param menuWindow：メニューウィンドウのポインタ
 */
MenuWindowUI::MenuWindowUI(MenuWindow* menuWindow)
	: m_menuWindow(menuWindow)
	, m_toTitleScene(nullptr)
	, m_toStageSelectScene(nullptr)
	, m_selectUIHome()
	, m_bgmKnob(nullptr)
	, m_seKnob(nullptr)
	, m_toHomeMenu(nullptr)
	, m_bgmKnobRange()
	, m_seKnobRange()
	, m_selectUIOption()
{
}

//------------------------------------------------------------------
/**
 * @brief デストラクタ
 */
MenuWindowUI::~MenuWindowUI()
{
}

//------------------------------------------------------------------
/**
 * @brief 初期化
 *
 * @param  なし
 * @return なし
 */
void MenuWindowUI::Initialize()
{
	// エイリアス宣言
	using Home = MenuWindow::SelectHomeMenu;
	using Option = MenuWindow::SelectOptionMenu;

	// UI作成
	CreateUI(KT::UI::PROPERTIE_MEMU);

	// ホームウィンドウの選択するUIの設定
	m_selectUIHome.resize(static_cast<int>(Home::COUNT));
	m_selectUIHome[static_cast<int>(Home::OPTION)]       = GetUI(KT::UI::MENU_OPTION_MENU_TEXT);
	m_selectUIHome[static_cast<int>(Home::RETURN_SCENE)] = nullptr;
	m_toTitleScene       = GetUI(KT::UI::MENU_TO_TITLE_SCENE_TEXT);
	m_toStageSelectScene = GetUI(KT::UI::MENU_TO_SELECT_SCENE_TEXT);
	// 設定ウィンドウの選択するUIの設定
	m_selectUIOption.resize(static_cast<int>(Option::COUNT));
	m_selectUIOption[static_cast<int>(Option::BGM)]    = GetUI(KT::UI::MENU_BGM_KNOB);
	m_selectUIOption[static_cast<int>(Option::SE)]     = GetUI(KT::UI::MENU_SE_KNOB);
	m_selectUIOption[static_cast<int>(Option::RETURN)] = GetUI(KT::UI::MENU_TO_HOME_MENU);
	// 〇〇シーンへ戻るテキストの有効無効時の状態設定
	OperatableUI::UIState activeState =
	{
		SimpleMath::Vector2::One, SimpleMath::Vector2::One,
		SimpleMath::Vector4::One, SimpleMath::Vector4::Zero
	};
	m_toTitleScene->SetState(OperatableUI::UIStateType::ACTIVE, activeState);
	m_toStageSelectScene->SetState(OperatableUI::UIStateType::ACTIVE, activeState);

	// 音量調節つまみの可動範囲設定
	ResourceManager* resourceManager = GameResource::GetInstance()->GetResourceManager();
	float barSizeX   = resourceManager->GetTexture(KT::Texture::UI_ADJUST_BAR).size.x;
	// バーの位置を起点に画像サイズの半分ずつに設定する
	float bgmBarPosX = m_selectUIOption[static_cast<int>(Option::BGM)]->GetPosition().x;
	m_bgmKnobRange   = SimpleMath::Vector2(bgmBarPosX - barSizeX * 0.5f, bgmBarPosX + barSizeX * 0.5f);
	float seBarPosX  = m_selectUIOption[static_cast<int>(Option::SE)]->GetPosition().x;
	m_seKnobRange    = SimpleMath::Vector2(seBarPosX - barSizeX * 0.5f, seBarPosX + barSizeX * 0.5f);
}

//------------------------------------------------------------------
/**
 * @brief メニューを開く
 *
 * @param  なし
 * @return なし
 */
void MenuWindowUI::OpenMenu()
{
	// ウィンドウUIを登録
	AddUIManager(TAG_ALWAYS);
	// ホーム画面UIを登録
	AddUIManager(TAG_MENU_HOME);
}

//------------------------------------------------------------------
/**
 * @brief ホーム画面を開く
 *
 * @param  なし
 * @return なし
 */
void MenuWindowUI::OpenHome()
{
	// 設定画面UIの登録解除
	DeleteUIManager(TAG_MENU_OPTION);
	// ホーム画面UIを登録
	AddUIManager(TAG_MENU_HOME);
}

//------------------------------------------------------------------
/**
 * @brief 設定画面を開く
 *
 * @param  なし
 * @return なし
 */
void MenuWindowUI::OpenOption()
{
	// ホーム画面UIの登録解除
	DeleteUIManager(TAG_MENU_HOME);
	// 設定画面UIの登録
	AddUIManager(TAG_MENU_OPTION);
}

//------------------------------------------------------------------
/**
 * @brief メニューを閉じる
 *
 * @param  なし
 * @return なし
 */
void MenuWindowUI::CloseMenu()
{
	// 全てのUIの登録解除
	DeleteUIManagerAll();
}

//------------------------------------------------------------------
/**
 * @brief ホーム画面の選択処理
 *
 * @param  type：選択しているメニューの番号
 * @return なし
 */
void MenuWindowUI::SelectHome(const int& type)
{
	// 選択処理
	Select(type, m_selectUIHome);
}

//------------------------------------------------------------------
/**
 * @brief 設定画面の選択処理
 *
 * @param  type：選択しているメニューの番号
 * @return なし
 */
void MenuWindowUI::SelectOption(const int& type)
{
	// 選択処理
	Select(type, m_selectUIOption);
}

//------------------------------------------------------------------
/**
 * @brief メニューの選択処理
 *
 * @param  type：選択しているメニューの番号
 * @return なし
 */
void MenuWindowUI::Select(const int& selectType, const std::vector<OperatableUI*>& changeColorList)
{
	for (int i = 0; i < changeColorList.size(); i++)
	{
		changeColorList[i]->SelectStateUpdate(i == selectType);
	}
}

//------------------------------------------------------------------
/**
 * @brief BGMの調整
 *
 * @param  volume：音量
 * @return なし
 */
void MenuWindowUI::BGMAdjustment(const float& volume)
{
	using Option = MenuWindow::SelectOptionMenu;

	OptionAdjustment(volume, m_selectUIOption[static_cast<int>(Option::BGM)], m_bgmKnobRange);
}

//------------------------------------------------------------------
/**
 * @brief SEの調整
 *
 * @param  volume：音量
 * @return なし
 */
void MenuWindowUI::SEAdjustment(const float& volume)
{
	using Option = MenuWindow::SelectOptionMenu;
	
	OptionAdjustment(volume, m_selectUIOption[static_cast<int>(Option::SE)], m_seKnobRange);
}

//------------------------------------------------------------------
/**
 * @brief 調整処理
 *
 * @param  volume   ：音量
 * @param  knob     ：つまみUI
 * @param  knobRange：つまみの移動範囲
 * @return なし
 */
void MenuWindowUI::OptionAdjustment(const float& volume, OperatableUI* knob, const DirectX::SimpleMath::Vector2& knobRange)
{
	// つまみの位置
	SimpleMath::Vector2 knobPos = knob->GetPosition();
	// 音量の値からつまみの位置を計算する
	knobPos.x = knobRange.x + (knobRange.y - knobRange.x) * volume;	
	// つまみの位置反映
	knob->SetPosition(knobPos);
}

//------------------------------------------------------------------
/**
 * @brief シーンへ戻るボタンの設定
 *
 * @param  openScene：メニューを開いているシーン
 * @return なし
 */
void MenuWindowUI::ReturnSceneButtonSetting(MenuWindow::OpenScene openScene)
{
	using Home = MenuWindow::SelectHomeMenu;

	// メニューを開いたシーンによって処理を分ける
	switch (openScene)
	{
	// ステージセレクト
	case MenuWindow::OpenScene::SELECT:
		m_selectUIHome[static_cast<int>(Home::RETURN_SCENE)] = m_toTitleScene;
		m_toTitleScene->ActiveStateUpdate(true);
		m_toStageSelectScene->ActiveStateUpdate(false);
		break;
	// プレイ
	case MenuWindow::OpenScene::PLAY:
		m_selectUIHome[static_cast<int>(Home::RETURN_SCENE)] = m_toStageSelectScene;
		m_toTitleScene->ActiveStateUpdate(false);
		m_toStageSelectScene->ActiveStateUpdate(true);
		break;
	// 例外
	case MenuWindow::OpenScene::NONE:
	default:
		assert(false && "OpenSceneが無効の値です");
		break;
	}
}