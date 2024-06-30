/**
 *
 * @file ResultScene.h
 *
 * @brief リザルトシーンを表すクラスのヘッダーファイル
 *
 * @author Kato Yuki
 *
 * @date 2023/11/8
 *
 */
#include "pch.h"
#include "ResultScene.h"
#include "Game/MyLibrary/CommonResource/GameResource.h"
#include "Game/MyLibrary/GameParameter/GameParameter.h"
#include "Game/MyLibrary/Utility/MyUtility.h"
#include "Game/Scene/SceneShareData.h"
#include "Game/Scene/StageSelectScene.h"
#include "Game/Camera/Camera.h"
#include "Game/Camera/CameraProjection.h"
#include "Game/Stage/Stage.h"
#include "Game/Stage/StageData.h"
#include "Game/SkyDome/SkyDome.h"
#include "Game/Player/Player.h"
#include "Game/Block/BlockFactory.h"
#include "Game/Block/Block.h"
#include "Game/UI/SceneUI/ResultSceneUI.h"

using namespace DirectX;

//------------------------------------------------------------------
/**
 * @brief コンストラクタ
 *
 * @param sceneManager：シーンマネージャーのポインタ
 */
ResultScene::ResultScene(SceneManager* sceneManager)
	: m_sceneManager(sceneManager)
	, m_camera(nullptr)
	, m_block(nullptr)
	, m_skyDome(nullptr)
	, m_player(nullptr)
	, m_ui(nullptr)
	, m_nextMode(NextMode::NEXT)
	, m_stageNum(0)
	, m_currentStageNumber(0)
{
}

//------------------------------------------------------------------
/**
 * @brief デストラクタ
 */
ResultScene::~ResultScene()
{
}

//------------------------------------------------------------------
/**
 * @brief 初期化
 *
 * @param  なし
 * @return なし
 */
void ResultScene::Initialize()
{
	// 各種リソース取得
	GameResource*    gameResource    = GameResource::GetInstance();
	InputManager*    inputManager    = gameResource->GetInputManager();
	StageManager*    stageManager    = gameResource->GetStageManager();
	ResourceManager* resourceManager = gameResource->GetResourceManager();

	// ステージ数取得
	m_stageNum = stageManager->GetStageNum();
	// 現在のステージ番号取得
	m_currentStageNumber = m_sceneManager->GetSceneShareData()->GetSelectStageNumber();
	// 使用するキーの登録
	inputManager->AddKey({ Keyboard::Keys::Up, Keyboard::Keys::Down, Keyboard::Keys::Enter });

	// 画面比計算
	RECT  screen = gameResource->GetDeviceResources()->GetOutputSize();
	float aspectRatio = static_cast<float>(screen.right) / static_cast<float>(screen.bottom);
	// カメラ作成
	m_camera = std::make_unique<Camera>(aspectRatio);
	m_camera->SetTargetPosition(CAMERA_TARGET_POSITION);
	m_camera->SetEyePosition(CAMERA_EYE_POSITION);
	m_camera->CreateViewMatrix();
	m_camera->SetProjectionMatrix(CameraProjection::CreatePerspectiveProjection(aspectRatio));
	// ブロック作成
	m_block = BlockFactory::CreateBlock(KT::Block::Type::GOAL, GOAL_BLOCK_POSITION);
	m_block->Initialize();
	// スカイドーム作成 
	// ステージの中心を位置に設定
	m_skyDome = std::make_unique<SkyDome>(SimpleMath::Vector3::Zero);
	m_skyDome->SetRotationSpeed(SKY_DOME_ROTATION_SPEED);
	// プレイヤー作成
	m_player = std::make_unique<Player>(PLAYER_POSITION);
	m_player->Initialize();
	m_player->TurnHeading(m_camera->GetTargetPosition() + SimpleMath::Vector3::Transform(m_camera->GetEyePosition(), m_camera->GetRotation()) - m_player->GetPosition());
	// UI作成
	m_ui = std::make_unique<ResultSceneUI>(this);
	m_ui->Initialize();

	// 最後のステージなら最初に選択されているメニューを変える
	if (IsEndStageNumber()) m_nextMode = NextMode::STAGE_SELECT;

	// BGMを流す
	resourceManager->PlaySound(KT::Sound::BGM, KT::Sound::BGMNumber::XACT_WAVEBANK_BGM_RESULT);
}

//------------------------------------------------------------------
/**
 * @brief 更新
 *
 * @param  なし
 * @return なし
 */
void ResultScene::Update()
{
	// 各種リソース取得
	GameResource*    gameResource    = GameResource::GetInstance();
	InputManager*    inputManager    = gameResource->GetInputManager();
	ResourceManager* resourceManager = gameResource->GetResourceManager();
	EffectManager*   effectManager   = gameResource->GetEffectManager();

	// エンターキーが押されたら
	if (inputManager->GetKey(Keyboard::Keys::Enter).press)
	{
		// SEを流す
		resourceManager->PlaySound(KT::Sound::SE, KT::Sound::SENumber::XACT_WAVEBANK_SE_DECISION);
		// シーン遷移
		ChangeScene();
	}

	// 最後のステージ以外か
	if (!IsEndStageNumber())
	{
		// メニュー選択
		KT::MyUtility::MenuSelect(
			inputManager->GetKey(Keyboard::Keys::Up).press, 
			inputManager->GetKey(Keyboard::Keys::Down).press,
			m_nextMode);
		// UIの選択処理
		m_ui->Select(static_cast<int>(m_nextMode));
	}

	// スカイドーム更新
	m_skyDome->Update();
	// プレイヤー更新
	m_player->Update();
	// エフェクト更新
	effectManager->Update();
}

//------------------------------------------------------------------
/**
 * @brief 描画
 *
 * @param  なし
 * @return なし
 */
void ResultScene::Render()
{
	// 各種リソース受け取り
	GameResource*     gameResource  = GameResource::GetInstance();
	EffectManager*    effectManager = gameResource->GetEffectManager();
	Imase::DebugFont* debugFont     = gameResource->GetDebugFont();

	debugFont->AddString(0, L"リザルトシーン");

	// ビュー、射影行列受け取り
	SimpleMath::Matrix view, projection;
	view       = m_camera->GetViewMatrix();
	projection = m_camera->GetProjectionMatrix();

	// スカイドーム描画
	m_skyDome->Render(view, projection);
	// ブロック描画
	m_block->Render(view, projection);
	// プレイヤー描画
	m_player->Render(view, projection);

	// カメラ位置、注視点、頭の向き取得
	SimpleMath::Vector3 eye, target, up;
	eye    = m_camera->GetTargetPosition() + SimpleMath::Vector3::Transform(m_camera->GetEyePosition(), m_camera->GetRotation());
	target = m_camera->GetTargetPosition();
	up     = m_camera->GetUpVector();

	// エフェクト描画
	effectManager->Render(view, projection, eye, target, up);

	// デバッグ
	int num = static_cast<int>(m_nextMode);
	if     (num == 0) debugFont->AddString(0, L"NEXT");
	else if(num == 1) debugFont->AddString(0, L"STAGE_SELECT");
}

//------------------------------------------------------------------
/**
 * @brief 後処理
 *
 * @param  なし
 * @return なし
 */
void ResultScene::Finalize()
{
}

//------------------------------------------------------------------
/**
 * @brief シーン切り替え
 *
 * @param  なし
 * @return なし
 */
void ResultScene::ChangeScene()
{
	switch (m_nextMode)
	{
	// 次のステージへ
	case ResultScene::NextMode::NEXT:
	{		
		// ステージ番号を一つ進める
		m_currentStageNumber++;
		// ステージ番号を設定
		m_sceneManager->GetSceneShareData()->SetSelectStageNumber(m_currentStageNumber);
		// 次のシーンをプレイシーンに
		m_sceneManager->SetNextScene<PlayScene>();
		break;
	}
	// セレクトシーンへ
	case ResultScene::NextMode::STAGE_SELECT:
		m_sceneManager->SetNextScene<StageSelectScene>();
		break;
	// 例外
	case ResultScene::NextMode::COUNT:
	default:
		assert(false && "リザルトシーンの遷移先モードが無効です");
		break;
	}
}

//------------------------------------------------------------------
/**
 * @brief 最後のステージかどうか
 *
 * @param なし
 * @return true ：最後のステージ
 * @return false：最後のステージでない
 */
bool ResultScene::IsEndStageNumber()
{
	return m_stageNum == m_currentStageNumber;
}

//------------------------------------------------------------------
/**
 * @brief 遷移先モードの取得
 *
 * @param  なし
 * @return NextMode：現在の遷移先モード
 */
ResultScene::NextMode ResultScene::GetNextMode() const
{
	return m_nextMode;
}