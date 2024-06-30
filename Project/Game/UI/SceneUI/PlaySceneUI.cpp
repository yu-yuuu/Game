/**
 *
 * @file PlaySceneUI.cpp
 *
 * @brief プレイシーンで使用するUI、画像クラスのソースファイル
 *
 * @author Kato Yuki
 *
 * @date 2024/1/16
 *
 */
#include "pch.h"
#include "PlaySceneUI.h"

#include "Game/MyLibrary/CommonResource/GameResource.h"
#include "Game/Scene//PlayScene.h"
#include "Game/Player/Player.h"
#include "Game/Camera/SceneCamera/GameCamera.h"
#include "Game/UI/OperatableUI.h"

using namespace DirectX;

//------------------------------------------------------------------
/**
 * @brief コンストラクタ
 *
 * @param playScene：プレイシーンのポインタ
 * @param player   ：プレイヤーのポインタ
 * @param camera   ：カメラのポインタ
 */
PlaySceneUI::PlaySceneUI(PlayScene* playScene, Player* player, GameCamera* camera)
	: m_playScene(playScene)
	, m_player(player)
	, m_camera(camera)
	, m_moveButtonUp(nullptr)
	, m_moveButtonDown(nullptr)
	, m_moveButtonRight(nullptr)
	, m_moveButtonLeft(nullptr)
	, m_jumpButton(nullptr)
	, m_camRotButtonW(nullptr)
	, m_camRotButtonS(nullptr)
	, m_camRotButtonA(nullptr)
	, m_camRotButtonD(nullptr)
	, m_dimensionButton(nullptr)
	, m_overLookingButton(nullptr)
{
}

//------------------------------------------------------------------
/**
 * @brief デストラクタ
 */
PlaySceneUI::~PlaySceneUI()
{
}

//------------------------------------------------------------------
/**
 * @brief 初期化
 *
 * @param  なし
 * @return なし
 */
void PlaySceneUI::Initialize()
{
	// UI作成
	CreateUI(KT::UI::PROPERTIE_PLAY);
	// 操作UI取得
	m_moveButtonUp      = GetUI(KT::UI::PLAY_MOVE_BUTTON_UP);
	m_moveButtonDown    = GetUI(KT::UI::PLAY_MOVE_BUTTON_DOWN);
	m_moveButtonRight   = GetUI(KT::UI::PLAY_MOVE_BUTTON_RIGHT);
	m_moveButtonLeft    = GetUI(KT::UI::PLAY_MOVE_BUTTON_LEFT);
	m_jumpButton        = GetUI(KT::UI::PLAY_JUMP_BUTTON);
	m_camRotButtonW     = GetUI(KT::UI::PLAY_CAMROT_BUTTON_W);
	m_camRotButtonS     = GetUI(KT::UI::PLAY_CAMROT_BUTTON_S);
	m_camRotButtonA     = GetUI(KT::UI::PLAY_CAMROT_BUTTON_A);
	m_camRotButtonD     = GetUI(KT::UI::PLAY_CAMROT_BUTTON_D);
	m_dimensionButton   = GetUI(KT::UI::PLAY_DIMESION_BUTTON);
	m_overLookingButton = GetUI(KT::UI::PLAY_OVERLOOKING_BUTTON);

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
void PlaySceneUI::Update()
{
	// プレイシーンの状態取得
	PlayScene::GameState state = m_playScene->GetGameState();

	// 状態ごとに更新処理を切り替え
	if (state == PlayScene::GameState::PLAY)
	{
		PlayUpdate();
	}
	else if (state == PlayScene::GameState::OVER_LOOK)
	{
		OverLookingUpdate();
	}
}

//------------------------------------------------------------------
/**
 * @brief プレイ時の更新処理
 *
 * @param  なし
 * @return なし
 */
void PlaySceneUI::PlayUpdate()
{
	using namespace KT::UI;

	// フェード取得
	Fade* fade = GameResource::GetInstance()->GetFade();

	// 設定に必要な情報取得
	bool is2D        = m_playScene->Is2D();              // 2D状態か
	bool is3D        = !is2D;                            // 3D状態か
	bool isTopDown   = m_playScene->IsTopDown();         // 見下ろし視点か
	bool is2DTopDown = is2D && isTopDown;                // 2D見下ろし視点か
	bool is3DTopDown = is3D && isTopDown;                // 3D見下ろし視点か
	bool is3DSide    = is3D && !isTopDown;               // 3D横視点か
	bool isJump      = m_player->IsJump();               // ジャンプ可能か
	bool onGround    = m_player->OnGround();             // 床の上にいるか
	bool isOperation = m_playScene->IsOperationCamera(); // カメラ切り替え、操作中か
	bool isFade      = fade->IsFade();                   // フェード中か

	// 移動ボタン
	m_moveButtonUp->ActiveStateUpdate(!isFade && (is3D || is2DTopDown) && !isOperation);
	m_moveButtonDown->ActiveStateUpdate(!isFade && (is3D || is2DTopDown) && !isOperation);
	m_moveButtonRight->ActiveStateUpdate(!isFade && !isOperation);
	m_moveButtonLeft->ActiveStateUpdate(!isFade && !isOperation);
	// ジャンプボタン
	m_jumpButton->ActiveStateUpdate(!isFade && (isJump && !isOperation));
	// カメラ回転ボタン
	m_camRotButtonW->ActiveStateUpdate(!isFade && (is3DSide && onGround && !isOperation));
	m_camRotButtonS->ActiveStateUpdate(!isFade && (is3DTopDown && onGround && !isOperation));
	m_camRotButtonA->ActiveStateUpdate(!isFade && (is3D && onGround && !isOperation));
	m_camRotButtonD->ActiveStateUpdate(!isFade && (is3D && onGround && !isOperation));
	// 次元切り替えボタン
	m_dimensionButton->ActiveStateUpdate(!isFade && (onGround && !isOperation));
	// 見渡しボタン
	m_overLookingButton->ActiveStateUpdate(!isFade && (onGround && !isOperation));

	// 入力状態の更新
	m_moveButtonUp->PushStateUpdate();
	m_moveButtonDown->PushStateUpdate();
	m_moveButtonRight->PushStateUpdate();
	m_moveButtonLeft->PushStateUpdate();
}

//------------------------------------------------------------------
/**
 * @brief 見渡し時の更新処理
 *
 * @param  なし
 * @return なし
 */
void PlaySceneUI::OverLookingUpdate()
{
	using namespace KT::UI;

	// 設定に必要な情報取得
	bool is3D = !m_playScene->Is2D();                    // 2D状態か
	bool isOperation = m_playScene->IsOperationCamera(); // カメラ切り替え、操作中か

	// 回転ボタン
	m_camRotButtonW->ActiveStateUpdate(!isOperation);
	m_camRotButtonS->ActiveStateUpdate(!isOperation);
	m_camRotButtonA->ActiveStateUpdate(!isOperation);
	m_camRotButtonD->ActiveStateUpdate(!isOperation);
	m_camRotButtonW->PushStateUpdate();
	m_camRotButtonS->PushStateUpdate();
	m_camRotButtonA->PushStateUpdate();
	m_camRotButtonD->PushStateUpdate();
	// 見渡しボタン
	m_overLookingButton->ActiveStateUpdate(!isOperation);
	// カメラ移動ボタンの更新
	if(is3D)
	{
		m_moveButtonUp->ActiveStateUpdate(!isOperation);
		m_moveButtonDown->ActiveStateUpdate(!isOperation);
		m_moveButtonUp->PushStateUpdate();
		m_moveButtonDown->PushStateUpdate();
	}
}

//------------------------------------------------------------------
/**
 * @brief 開始時アニメーションスキップUI表示
 *
 * @param  なし
 * @return なし
 */
void PlaySceneUI::ShowSkipUI()
{
	// プレイ状態のUIを登録
	AddUIManager(TAG_START_ANIMATION);
}

//------------------------------------------------------------------
/**
 * @brief 開始時アニメーションからプレイ状態へ
 *
 * @param  なし
 * @return なし
 */
void PlaySceneUI::ChangeStateAnimationToPlay()
{
	DeleteUIManager(TAG_START_ANIMATION);
	AddUIManager(TAG_PLAY_ALWAYS);
	AddUIManager(TAG_PLAY_STATE);
}

//------------------------------------------------------------------
/**
 * @brief メニューからプレイ状態へ切替
 *
 * @param  なし
 * @return なし
 */
void PlaySceneUI::ChangeStateMenuToPlay()
{
	// プレイ状態のUIを登録
	AddUIManager(TAG_PLAY_ALWAYS);
	AddUIManager(TAG_PLAY_STATE);
}

//------------------------------------------------------------------
/**
 * @brief メニューから見渡し状態へ切替
 *
 * @param  なし
 * @return なし
 */
void PlaySceneUI::ChangeStateMenuToOverLooking()
{
	// プレイ状態のUIを登録
	AddUIManager(TAG_PLAY_ALWAYS);
	AddUIManager(GetOverLookingKey(m_playScene->Is2D()));
}

 //------------------------------------------------------------------
 /**
  * @brief プレイから見渡し状態へ切替
  *
  * @param  なし
  * @return なし
  */
void PlaySceneUI::ChangeStatePlayToOverLooking()
{
	// プレイ状態のUIの登録を解除
	DeleteUIManager(TAG_PLAY_STATE);
	// 見渡し状態のUIを登録
	AddUIManager(GetOverLookingKey(m_playScene->Is2D()));
}

 //------------------------------------------------------------------
 /**
  * @brief 見渡しからプレイ状態へ切替
  *
  * @param  なし
  * @return なし
  */
void PlaySceneUI::ChangeStateOverLookingToPlay()
{
	// 見渡し状態のUIの登録を解除
	DeleteUIManager(GetOverLookingKey(m_playScene->Is2D()));
	// プレイ状態のUIを登録
	AddUIManager(TAG_PLAY_STATE);
}

//------------------------------------------------------------------
/**
 * @brief 見渡し状態のキーを取得する
 *
 * @param  is2D  ：2D状態か
 * @return string：見渡し状態UIの登録用キー
 */
std::string PlaySceneUI::GetOverLookingKey(bool is2D)
{
	// 次元を確認
	std::string key;
	if (is2D) key = TAG_OVER_LOOKING_STATE_2D;
	else      key = TAG_OVER_LOOKING_STATE_3D;

	return key;
}