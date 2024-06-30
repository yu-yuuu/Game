/**
 *
 * @file StageSelectScene.cpp
 *
 * @brief ステージ選択シーンを表すクラスのソースファイル
 *
 * @author Kato Yuki
 *
 * @date 2023/11/8
 *
 */
#include "pch.h"
#include "StageSelectScene.h"
#include "Game/MyLibrary/CommonResource/GameResource.h"
#include "Game/Camera/SceneCamera/StageSelectCamera.h"
#include "Game/Camera/CameraProjection.h"
#include "Game/Camera/State/CameraStateLerpSwitch.h"
#include "Game/Stage/SelectStage.h"
#include "Game/Scene/PlayScene.h"
#include "Game/UI/SceneUI/StageSelectSceneUI.h"
#include "Game/Window/MenuWindow.h"
#include "Game/Scene/SceneShareData.h"
#include "Game/SkyDome/SkyDome.h"

using namespace DirectX;

//------------------------------------------------------------------
/**
 * @brief コンストラクタ
 *
 * @param sceneManager：シーンマネージャーのポインタ
 */
StageSelectScene::StageSelectScene(SceneManager* sceneManager)
	: m_sceneManager(sceneManager)
	, m_stage(nullptr)
	, m_camera(nullptr)
	, m_ui(nullptr)
	, m_skyDome(nullptr)
	, m_sceneState(SceneState::SELECT)
	, m_stageNumberList()
	, m_stageNumberIndex(0)
	, m_isSwitchFinished(false)
{
}

//------------------------------------------------------------------
/**
 * @brief デストラクタ
 *
 */
StageSelectScene::~StageSelectScene()
{
}

//------------------------------------------------------------------
/**
 * @brief 初期化
 *
 * @param  なし
 * @return なし
 */
void StageSelectScene::Initialize()
{
	// 各種リソース取得
	GameResource*        gameResource    = GameResource::GetInstance();
	StageManager*        stageManager    = gameResource->GetStageManager();
	DX::DeviceResources* deviceResources = gameResource->GetDeviceResources();
	InputManager*        inputManager    = gameResource->GetInputManager();
	ResourceManager*     resourceManager = gameResource->GetResourceManager();

	// 使用するキーの登録
	inputManager->AddKey(
		{
			Keyboard::Keys::Up,    Keyboard::Keys::Down,
			Keyboard::Keys::Right, Keyboard::Keys::Left,
			Keyboard::Keys::Enter, Keyboard::Keys::Escape
		}
	);
	
	// 画面比を計算
	RECT rect = deviceResources->GetOutputSize();
	float aspectRatio = static_cast<float>(rect.right) / static_cast<float>(rect.bottom);

	// 選択しているステージ番号を取得
	int stageNum = m_sceneManager->GetSceneShareData()->GetSelectStageNumber();
	// 取得したステージ番号を要素番号へ変換
	m_stageNumberIndex = std::max(stageNum - 1, 0);
	// ステージ作成
	m_stageNumberList = stageManager->GetStageNumberList();
	KT::Stage::Size stageSize = stageManager->GetStageSize(m_stageNumberList[m_stageNumberIndex]);
	m_stage = std::make_unique<SelectStage>(m_stageNumberList[m_stageNumberIndex], stageSize);
	m_stage->Initialize();
	// カメラ作成
	m_camera = std::make_unique<StageSelectCamera>(this, aspectRatio, stageSize.GetVector3());
	m_camera->InitialCameraSetting();
	// UI作成
	m_ui = std::make_unique<StageSelectSceneUI>(this);
	m_ui->Initialize();
	m_ui->SelectTriangleRenderSetting(m_stageNumberIndex == 0, m_stageNumberIndex == m_stageNumberList.size() - 1);
	// スカイドーム作成 
	// ステージの中心を位置に設定
	m_skyDome = std::make_unique<SkyDome>(stageSize.GetVector3() * 0.5f);

	// ステージ選択状態
	m_sceneState = SceneState::SELECT;
	// BGMを流す
	resourceManager->PlaySound(KT::Sound::BGM, KT::Sound::BGMNumber::XACT_WAVEBANK_BGM_SELECT);
}

//------------------------------------------------------------------
/**
 * @brief 更新
 *
 * @param なし
 * @return なし
 */
void StageSelectScene::Update()
{
	// 更新処理
	switch (m_sceneState)
	{
	// ステージ選択
	case StageSelectScene::SceneState::SELECT: SelectUpdate(); break;
	// メニュー
	case StageSelectScene::SceneState::MENU:   MenuUpdate();   break;
	// 例外
	default: assert(false && "ステージセレクトシーンのsceneStateが無効の値です");break;
	}
}

//------------------------------------------------------------------
/**
 * @brief 描画
 *
 * @param  なし
 * @return なし
 */
void StageSelectScene::Render()
{
	// 各種リソース受け取り
	GameResource*     gameResource  = GameResource::GetInstance();
	EffectManager*    effectManager = gameResource->GetEffectManager();

	// ビュー、射影行列受け取り
	SimpleMath::Matrix view, projection;
	view       = m_camera->GetViewMatrix();
	projection = m_camera->GetProjectionMatrix();
	// スカイドーム描画
	m_skyDome->Render(view, projection);
	// ステージ描画
	m_stage->Render(view, projection);
	// カメラ位置、注視点、頭の向き取得
	SimpleMath::Vector3 eye, target, up;
	eye    = m_camera->GetTargetPosition() + SimpleMath::Vector3::Transform(m_camera->GetEyePosition(), m_camera->GetRotation());
	target = m_camera->GetTargetPosition();
	up     = m_camera->GetUpVector();
	// エフェクト描画
	effectManager->Render(view, projection, eye, target, up);
	// メニューウィンドウ描画
	m_sceneManager->GetSceneShareData()->GetMenuWindow()->Render();
}

//------------------------------------------------------------------
/**
 * @brief 後処理
 *
 * @param  なし
 * @return なし
 */
void StageSelectScene::Finalize()
{
}

//------------------------------------------------------------------
/**
 * @brief シーン切り替え
 *
 * @param  なし
 * @return なし
 */
void StageSelectScene::ChangeScene()
{
	// 共有データに選択したステージ番号を設定する
	// ( 要素番号からステージ番号に直すため + 1 )
	m_sceneManager->GetSceneShareData()->SetSelectStageNumber(m_stageNumberIndex + 1);
	// 次のシーンにプレイシーンをセット
	m_sceneManager->SetNextScene<PlayScene>();
}

//------------------------------------------------------------------
/**
 * @brief ステージ選択時の更新処理
 *
 * @param  keyList：入力されたキーリスト
 * @return なし
 */
void StageSelectScene::SelectUpdate()
{
	// 各種リソース取得
	GameResource*    gameResource    = GameResource::GetInstance();
	InputManager*    inputManager    = gameResource->GetInputManager();
	ResourceManager* resourceManager = gameResource->GetResourceManager();

	// ステージ選択
	if(!m_camera->IsOperation()) StageSelect();

	// シーン遷移
	if (inputManager->GetKey(Keyboard::Keys::Enter).press)
	{
		// SEを流す
		resourceManager->PlaySound(KT::Sound::SE, KT::Sound::SENumber::XACT_WAVEBANK_SE_DECISION);
		ChangeScene();
	}
	// メニュー画面を開く
	if (inputManager->GetKey(Keyboard::Keys::Escape).press)
	{
		m_sceneManager->GetSceneShareData()->GetMenuWindow()->Open(MenuWindow::OpenScene::SELECT);
		m_sceneState = SceneState::MENU;
		m_ui->DeleteUIManagerAll();
	}

	// 更新
	m_camera->Update();
	m_stage->Update();
	GameResource::GetInstance()->GetEffectManager()->Update();
	m_skyDome->SetPosition(m_camera->GetTargetPosition());
}

//------------------------------------------------------------------
/**
 * @brief メニュー表示時の更新処理
 *
 * @param  keyList：入力されたキーリスト
 * @return なし
 */
void StageSelectScene::MenuUpdate()
{
	// キーマネージャー取得
	InputManager* inputManager = GameResource::GetInstance()->GetInputManager();

	// メニュー画面
	if (inputManager->GetKey(Keyboard::Keys::Escape).press)
	{
		m_sceneManager->GetSceneShareData()->GetMenuWindow()->Close();
		m_sceneState = SceneState::SELECT;
		m_ui->AddUIManagerAll();
		m_ui->SelectTriangleRenderSetting(m_stageNumberIndex == 0, m_stageNumberIndex == m_stageNumberList.size() - 1);
	}

	// メニューの更新
	m_sceneManager->GetSceneShareData()->GetMenuWindow()->Update();
}

//------------------------------------------------------------------
/**
 * @brief ステージ選択
 *
 * @param  key：入力されたキー
 * @return なし
 */
void StageSelectScene::StageSelect()
{
	// 各種リソース取得
	GameResource*    gameResource    = GameResource::GetInstance();
	InputManager*    inputManager    = gameResource->GetInputManager();

	// 切替完了時処理
	if (m_isSwitchFinished) 
	{
		StageSwitchComplete();
		m_isSwitchFinished = false;
	}

	// 入力前状態を保存
	int afterIndex = m_stageNumberIndex;

	// 上下キー入力で切り替え
	if      (inputManager->GetKey(Keyboard::Keys::Up).press)   m_stageNumberIndex--;
	else if (inputManager->GetKey(Keyboard::Keys::Down).press) m_stageNumberIndex++;
	// 範囲外に行かないようにクランプ
	m_stageNumberIndex = std::max(0, std::min(m_stageNumberIndex, 
		static_cast<int>(m_stageNumberList.size() - 1)));

	// 切替してい無いなら終了
	if (m_stageNumberIndex == afterIndex) return;

	// SEを流す
	gameResource->GetResourceManager()->PlaySound(KT::Sound::SE, KT::Sound::SENumber::XACT_WAVEBANK_SE_MOVECURSOL);	
	// 表示するステージを更新
	m_stage->ChangeStageSetting(m_stageNumberIndex);
	// UIを更新
	m_ui->SelectTriangleRenderSetting(m_stageNumberIndex == 0, m_stageNumberIndex == m_stageNumberList.size() - 1);
	// カメラの設定
	SimpleMath::Vector3 stageSize = m_stage->GetNextStageSize().GetVector3();
	SimpleMath::Vector3 basePosition = m_stage->GetNextBasePosition();	
	m_camera->StageSelectSetting(basePosition + stageSize * 0.5f, stageSize);
	// フラグを立てる
	m_isSwitchFinished = true;
}

//------------------------------------------------------------------
/**
 * @brief 現在選択しているステージの要素番号取得
 *
 * @param  なし
 * @return なし
 */
int StageSelectScene::GetSelectIndex()
{
	return m_stageNumberIndex;
}

//------------------------------------------------------------------
/**
 * @brief ステージの数
 *
 * @param  なし
 * @return なし
 */
int StageSelectScene::GetStageNum()
{
	return static_cast<int>(m_stageNumberList.size());
}

//------------------------------------------------------------------
/**
 * @brief ステージ切替完了時処理
 *
 * @param  なし
 * @return なし
 */
void StageSelectScene::StageSwitchComplete()
{
	m_stage->StageSwitchComplete();
}
