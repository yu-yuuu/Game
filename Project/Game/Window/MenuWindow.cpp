/**
 *
 * @file MenuWindow.cpp
 *
 * @brief 画面上に表示するウィンドウの基底クラスのソースファイル
 *
 * @author Kato Yuki
 *
 * @date 2024/2/5
 *
 */
#include "pch.h"
#include "MenuWindow.h"

#include "Game/MyLibrary/CommonResource/GameResource.h"
#include "Game/Scene/SceneManager.h"
#include "Game/Scene/TitleScene.h"
#include "Game/Scene/StageSelectScene.h"
#include "Game/Window/MenuWindowUI.h"
#include "Game/MyLibrary/Utility/MyUtility.h"
#include "Game/MyLibrary/File/FileManager.h"
#include "Library/nlohmann/json.hpp"

using namespace DirectX;

//------------------------------------------------------------------
/**
 * @brief コンストラクタ
 *
 * @param sceneManager：シーンマネージャーのポインタ
 * @param windowSize  ：ウィンドウのサイズ
 * @param texture     ：ウィンドウに使用するテクスチャ
 * @param position    ：ウィンドウの描画位置
 */
MenuWindow::MenuWindow(SceneManager* sceneManager, DirectX::SimpleMath::Vector2 windowSize, KT::Texture::TextureData texture, DirectX::SimpleMath::Vector2 position)
	: Window(windowSize, texture, position)
	, m_sceneManager(sceneManager)
	, m_ui(nullptr)
	, m_openScene(OpenScene::NONE)
	, m_currentMenu(MenuType::HOME)
	, m_selectHomeMenu(SelectHomeMenu::OPTION)
	, m_selectOptionMenu(SelectOptionMenu::BGM)
{
}

//------------------------------------------------------------------
/**
 * @brief デストラクタ
 */
MenuWindow::~MenuWindow()
{
}

//------------------------------------------------------------------
/**
 * @brief 初期化
 *
 * @param  なし
 * @return なし
 */
void MenuWindow::Initialize()
{
	// 基底クラスの初期化
	Window::Initialize();

	// UI作成、初期化
	m_ui = std::make_unique<MenuWindowUI>(this);
	m_ui->Initialize();

	// データ取得
	FilePathList* filePathList = GameResource::GetInstance()->GetFilePathList();
	nlohmann::json data = FileManager::LoadJSON(filePathList->GetPath(KT::File::OPTION));
	// 音量つまみの位置調節
	m_ui->BGMAdjustment(data[KT::Sound::PROPERTIE_SOUND][KT::Sound::BGM]);
	m_ui->SEAdjustment(data[KT::Sound::PROPERTIE_SOUND][KT::Sound::SE]);
 }

//------------------------------------------------------------------
/**
 * @brief 更新
 *
 * @param  なし
 * @return なし
 */
void MenuWindow::Update()
{
	// フラグが立っていないなら終了
	if (!IsOpen()) return;

	// 開いているメニューの更新
	switch (m_currentMenu)
	{
	// ホーム
	case MenuWindow::MenuType::HOME:
		UpdateHome();
		break;
	// 設定
	case MenuWindow::MenuType::OPTION:
		UpdateOption();
		break;
	// 例外
	default:
		assert(false && "メニューが無効の値です");
		break;
	}
}

//------------------------------------------------------------------
/**
 * @brief ホーム画面の更新処理
 *
 * @param  なし
 * @return なし
 */
void MenuWindow::UpdateHome()
{
	// キーマネージャー取得
	InputManager* inputManager = GameResource::GetInstance()->GetInputManager();

	// 選択
	KT::MyUtility::MenuSelect(
		inputManager->GetKey(Keyboard::Keys::Up).press, 
		inputManager->GetKey(Keyboard::Keys::Down).press, 
		m_selectHomeMenu);
	// 決定
	if (inputManager->GetKey(Keyboard::Keys::Enter).press) OnEnterHome();
	// UIの選択処理
	m_ui->SelectHome(static_cast<int>(m_selectHomeMenu));
}

//------------------------------------------------------------------
/**
 * @brief 設定画面の更新
 *
 * @param  なし
 * @return なし
 */
void MenuWindow::UpdateOption()
{
	// キーマネージャー取得
	InputManager* inputManager = GameResource::GetInstance()->GetInputManager();
	
	// 選択
	KT::MyUtility::MenuSelect(
		inputManager->GetKey(Keyboard::Keys::Up).press,
		inputManager->GetKey(Keyboard::Keys::Down).press,
		m_selectOptionMenu);
	// 音量調整
	SoundSetting();
	// 決定
	if (inputManager->GetKey(DirectX::Keyboard::Keys::Enter).press) OnEnterOption();
	// UIの選択処理
	m_ui->SelectOption(static_cast<int>(m_selectOptionMenu));
}

//------------------------------------------------------------------
/**
 * @brief ウィンドウの表示切替
 *
 * @param  openScene：ウィンドウを開いたシーン
 * @return なし
 */
void MenuWindow::OpenClose(OpenScene openScene)
{
	// 開いた
	if (IsOpen()) Open(openScene);
	// 閉じた
	else Close();
}

//------------------------------------------------------------------
/**
 * @brief ウィンドウを開く
 *
 * @param  なし
 * @return なし
 */
void MenuWindow::Open(OpenScene openScene)
{
	// ウィンドウを開く
	Window::Open();
	// メニューを開いたシーン設定
	m_openScene = openScene;
	// ○○シーンへ戻るボタンの設定
	m_ui->ReturnSceneButtonSetting(openScene);
	// 現在のメニューをホームに設定
	m_currentMenu = MenuType::HOME;
	// メニューのUIを表示
	m_ui->OpenMenu();
}

//------------------------------------------------------------------
/**
 * @brief ウィンドウを閉じる
 *
 * @param  なし
 * @return なし
 */
void MenuWindow::Close()
{
	// ウィンドウを閉じる
	Window::Close();
	// メニューUIを非表示
	m_ui->CloseMenu();
}

//------------------------------------------------------------------
/**
 * @brief ホーム画面で決定時の処理
 *
 * @param  なし
 * @return なし
 */
void MenuWindow::OnEnterHome()
{
	// 選択しているメニュー毎の処理
	switch (m_selectHomeMenu)
	{
	// 設定
	case MenuWindow::SelectHomeMenu::OPTION:
		ChangeMenu(MenuType::OPTION);
		break;
	// シーンに戻る
	case MenuWindow::SelectHomeMenu::RETURN_SCENE:
		if      (m_openScene == OpenScene::SELECT) m_sceneManager->SetNextScene<TitleScene>();
		else if (m_openScene == OpenScene::PLAY)   m_sceneManager->SetNextScene<StageSelectScene>();	
		break;
	// 例外
	case MenuWindow::SelectHomeMenu::COUNT:
	default:
		assert(false && "ホームメニューが無効の値です");
		break;
	}

	// SEを流す
	GameResource::GetInstance()->GetResourceManager()->PlaySound(
		KT::Sound::SE, KT::Sound::SENumber::XACT_WAVEBANK_SE_DECISION);
}

//------------------------------------------------------------------
/**
 * @brief 設定画面で決定時の処理
 *
 * @param  なし
 * @return なし
 */
void MenuWindow::OnEnterOption()
{
	switch (m_selectOptionMenu)
	{
	// BGMとSEの時は一つ下へ動かす
	case MenuWindow::SelectOptionMenu::BGM:
		m_selectOptionMenu = SelectOptionMenu::SE;
		break;
	case MenuWindow::SelectOptionMenu::SE:
		m_selectOptionMenu = SelectOptionMenu::RETURN;
		break;
	// ホーム画面に戻る
	case MenuWindow::SelectOptionMenu::RETURN:
		// SEを流す
		GameResource::GetInstance()->GetResourceManager()->PlaySound(
			KT::Sound::SE, KT::Sound::SENumber::XACT_WAVEBANK_SE_DECISION);
		ChangeMenu(MenuType::HOME);
		break;
	// 例外
	case MenuWindow::SelectOptionMenu::COUNT:
	default:
		assert(false && "設定メニューが無効の値です");
		break;
	}
}

//------------------------------------------------------------------
/**
 * @brief 音の設定
 *
 * @param  なし
 * @return なし
 */
void MenuWindow::SoundSetting()
{
	// 乳慮マネージャー取得
	InputManager* inputManager = GameResource::GetInstance()->GetInputManager();

	// つまみの移動速度
	float speed = 0.0f;
	// 音量を上げる
	if      (inputManager->GetKey(Keyboard::Keys::Right).down) speed = KNOB_SPEED;
	// 音量を下げる
	else if (inputManager->GetKey(Keyboard::Keys::Left).down)  speed = -KNOB_SPEED;
	else     return;

	// 音量調整
	switch (m_selectOptionMenu)
	{
	// BGM
	case MenuWindow::SelectOptionMenu::BGM:
		AdjustmentVolume(speed, KT::Sound::BGM);
		break;
	// SE
	case MenuWindow::SelectOptionMenu::SE:
		AdjustmentVolume(speed, KT::Sound::SE);
		break;
	// 戻るボタンは何もしない
	case MenuWindow::SelectOptionMenu::RETURN:
		break;
	// 例外
	case MenuWindow::SelectOptionMenu::COUNT:
	default:
		assert(false && "メニューが無効な値です");
		break;
	}
}

//------------------------------------------------------------------
/**
 * @brief 音量調節
 *
 * @param  speed：つまみの移動量
 * @param  type ：調整する音の種類
 * @return なし
 */
void MenuWindow::AdjustmentVolume(float& speed, const std::string& type)
{
	// 各種リソース取得
	GameResource*    gameResource    = GameResource::GetInstance();
	ResourceManager* resourceManager = gameResource->GetResourceManager();
	FilePathList*    filePathList    = gameResource->GetFilePathList();
	// 音量データを読み込む
	nlohmann::json data = FileManager::LoadJSON(filePathList->GetPath(KT::File::OPTION));
	// 音量取得
	float volume = data[KT::File::SOUND][type];

	// 音量調整
	volume += speed;
	volume = std::min(std::max(volume, 0.0f), MAX_VOLUME);
	resourceManager->VolumeSetting(type, volume);
	// 種類によって切り替える
	if     (type == KT::Sound::BGM) m_ui->BGMAdjustment(volume);
	else if(type == KT::Sound::SE)  m_ui->SEAdjustment(volume);

	// データ更新
	data[KT::File::SOUND][type] = volume;
	FileManager::ReadJSON(filePathList->GetPath(KT::File::OPTION), data);
}

//------------------------------------------------------------------
/**
 * @brief 設定画面の更新
 *
 * @param  なし
 * @return なし
 */
void MenuWindow::ChangeMenu(MenuType nextMenu)
{
	switch (nextMenu)
	{
	// ホーム画面
	case MenuWindow::MenuType::HOME:
		m_currentMenu = MenuType::HOME;
		m_ui->OpenHome();
		break;
	// 設定画面
	case MenuWindow::MenuType::OPTION:
		m_currentMenu = MenuType::OPTION;
		m_ui->OpenOption();
		break;
	// 例外
	default:
		assert(false && "メニューが無効な値です");
		break;
	}
}