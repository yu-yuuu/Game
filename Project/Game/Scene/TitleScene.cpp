/**
 *
 * @file TitleScene.cpp
 *
 * @brief タイトルシーンを表すクラスのソースファイル
 *
 * @author Kato Yuki
 *
 * @date 2023/11/8
 *
 */
#include "pch.h"
#include "TitleScene.h"
#include "Game/MyLibrary/CommonResource/GameResource.h"
#include "Game/Scene/StageSelectScene.h"
#include "Game/UI/SceneUI/TitleSceneUI.h"
#include "Game/Stage/TitleStage.h"
#include "Game/Camera/SceneCamera/TitleCamera.h"
#include "Game/SkyDome/SkyDome.h"
#include "Game/MyLibrary/GameParameter/GameParameter.h"
#include "Game/MyLibrary/Utility/MyUtility.h"

using namespace DirectX;

//------------------------------------------------------------------
/**
 * @brief コンストラクタ
 *
 * @param sceneManager：シーンマネージャーのポインタ
 */
TitleScene::TitleScene(SceneManager* sceneManager)
	: m_sceneManager(sceneManager)
	, m_stage(nullptr)
	, m_camera(nullptr)
	, m_ui(nullptr)
	, m_skyDome(nullptr)
	, m_titleState(TitleState::PUSH_ENTER)
	, m_nextMode(NextMode::PLAY)
{
}

//------------------------------------------------------------------
/**
 * @brief デストラクタ
 *
 */
TitleScene::~TitleScene()
{
}

//------------------------------------------------------------------
/**
 * @brief 初期化
 *
 * @param  なし
 * @return なし
 */
void TitleScene::Initialize()
{
	// 各種リソース取得
	GameResource*        gameResource    = GameResource::GetInstance();
	DX::DeviceResources* deviceResources = gameResource->GetDeviceResources();
	StageManager*        stageManager    = gameResource->GetStageManager();
	InputManager*        inputManager    = gameResource->GetInputManager();
	ResourceManager*     resourceManager = gameResource->GetResourceManager();

	// 使用するキーの登録
	inputManager->AddKey({ Keyboard::Keys::Up, Keyboard::Keys::Down, Keyboard::Keys::Enter });

	// 画面比を計算
	RECT rect = deviceResources->GetOutputSize();
	float aspectRatio = static_cast<float>(rect.right) / static_cast<float>(rect.bottom);

	// ステージ作成
	int stageNumber = KT::GameParam::TITLE_STAGE_NUM;
	KT::Stage::Size stageSize = stageManager->GetStageSize(stageNumber);
	m_stage = std::make_unique<TitleStage>(this, stageNumber, stageSize);
	m_stage->Initialize();
	// カメラ作成
	m_camera = std::make_unique<TitleCamera>(this, aspectRatio, stageSize.GetVector3());
	m_camera->InitialCameraSetting();
	// UI作成
	m_ui = std::make_unique<TitleSceneUI>(this);
	m_ui->Initialize();
	// スカイドーム作成 
	// ステージの中心を位置に設定
	m_skyDome = std::make_unique<SkyDome>(stageSize.GetVector3() * 0.5f);

	// BGMを流す
	resourceManager->PlaySound(KT::Sound::BGM, KT::Sound::BGMNumber::XACT_WAVEBANK_BGM_TITLE);
}

//------------------------------------------------------------------
/**
 * @brief 更新
 *
 * @param なし
 * @return なし
 */
void TitleScene::Update()
{
	// 各種リソース取得
	GameResource*     gameResource    = GameResource::GetInstance();
	InputManager*     inputManager    = gameResource->GetInputManager();
	ResourceManager*  resourceManager = gameResource->GetResourceManager();
	Imase::DebugFont* debugFont       = gameResource->GetDebugFont();

	debugFont->AddString(0, L"タイトルシーン");


	// タイトルの状態が切り替え
	if (m_titleState == TitleState::SWITCHING)
	{
		// カメラが切り替えが終了したか
		if (!m_camera->IsOperation())
		{
			// タイトルの状態を切り替える
			ChangeState();
		}
	}
	// 切替状態以外の時に入力操作を行う
	else
	{
		// モード選択
		if (m_titleState == TitleState::MODE_SELECT)
		{
			KT::MyUtility::MenuSelect(
				inputManager->GetKey(Keyboard::Keys::Up).press,
				inputManager->GetKey(Keyboard::Keys::Down).press,
				m_nextMode);
		}
		// 状態遷移
		if (inputManager->GetKey(Keyboard::Keys::Enter).press)
		{
			// SEを流す
			resourceManager->PlaySound(KT::Sound::SE, KT::Sound::SENumber::XACT_WAVEBANK_SE_DECISION);
			ChangeState();
		}
	}
	// タイトルの状態がモードセレクト以外の時
	if (m_titleState != TitleState::MODE_SELECT)
	{
		// カメラ更新
		m_camera->Update();
	}

	// ステージ更新
	m_stage->Update();
}

//------------------------------------------------------------------
/**
 * @brief 描画
 *
 * @param なし
 * @return なし
 */
void TitleScene::Render()
{
	// 各種リソース取得
	GameResource*         gameResource    = GameResource::GetInstance();
	Imase::DebugFont*     debugFont       = gameResource->GetDebugFont();

	// ビュー、射影行列を受け取る
	SimpleMath::Matrix view, projection;
	view       = m_camera->GetViewMatrix();
	projection = m_camera->GetProjectionMatrix();

	// スカイドームの描画
	m_skyDome->Render(view, projection);
	// ステージの描画
	m_stage->Render(view, projection);



	//----------------------------------------------
	// デバッグ表示
	//----------------------------------------------
	switch (m_titleState)
	{
		// エンター
	case TitleScene::TitleState::PUSH_ENTER: debugFont->AddString(0, L"PushEnter"); break;
		// 終了ボタン選択
	case TitleScene::TitleState::MODE_SELECT: debugFont->AddString(0, L"ModeSelect"); break;
	default:
		break;
	}
	switch (m_nextMode)
	{
		// スタートボタン選択
	case TitleScene::NextMode::PLAY: debugFont->AddString(0, L"PlayMode"); break;
		// 終了ボタン選択
	case TitleScene::NextMode::EXIT: debugFont->AddString(0, L"ExitMode"); break;
	default:
		break;
	}
}

//------------------------------------------------------------------
/**
 * @brief 後処理
 *
 * @param  なし
 * @return なし
 */
void TitleScene::Finalize()
{
}

//------------------------------------------------------------------
/**
 * @brief シーン切り替え
 *
 * @param  なし
 * @return なし
 */
void TitleScene::ChangeScene()
{
	switch (m_nextMode)
	{
	// ステージセレクトシーンへ遷移
	case TitleScene::NextMode::PLAY:
		m_sceneManager->SetNextScene<StageSelectScene>();
		break;
	// ゲーム終了
	case TitleScene::NextMode::EXIT:
		PostQuitMessage(0);
		break;
	default:
		break;
	}
}

//------------------------------------------------------------------
/**
 * @brief タイトルシーンの状態切り替え
 *
 * @param  なし
 * @return なし
 */
void TitleScene::ChangeState()
{
	switch (m_titleState)
	{
	// 切替状態へ
	case TitleScene::TitleState::PUSH_ENTER:
		m_titleState = TitleState::SWITCHING;
		m_ui->ChangeStateSwitching();
		// カメラの次元切り替え
		m_camera->ChangeDimension();
		break;
	// モードセレクト状態へ
	case TitleScene::TitleState::SWITCHING:
		m_titleState = TitleState::MODE_SELECT;
		m_ui->ChangeStateModeSelect();
		break;
	// プレイシーンへ
	case TitleScene::TitleState::MODE_SELECT:
		ChangeScene();
		break;
	// 例外
	default:
		break;
	}
}

//------------------------------------------------------------------
/**
 * @brief タイトルシーンの状態取得
 *
 * @param  なし
 * @return なし
 */
TitleScene::TitleState TitleScene::GetTitleState() const
{
	return m_titleState;
}

//------------------------------------------------------------------
/**
 * @brief タイトルシーンの状態取得
 *
 * @param  なし
 * @return なし
 */
TitleScene::NextMode TitleScene::GetMode() const
{
	return m_nextMode;
}