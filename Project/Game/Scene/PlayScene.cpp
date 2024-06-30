/**
 *
 * @file PlayScene.cpp
 *
 * @brief プレイシーンを表すクラスのソースファイル
 *
 * @author Kato Yuki
 *
 * @date 2023/11/8
 *
 */
#include "pch.h"
#include "PlayScene.h"
#include "Game/Scene/SceneManager.h"
#include "Game/Scene/ResultScene.h"

#include "Game/MyLibrary/CommonResource/GameResource.h"
#include "Game/MyLibrary/ResourceManager/ResourceType.h"
#include "Game/MyLibrary/GameParameter/GameParameter.h"
#include "Game/MyLibrary/Utility/MyUtility.h"
#include "Game/Scene/SceneShareData.h"
#include "Game/Stage/PlayStage.h"
#include "Game/Player/Player.h"
#include "Game/UI/SceneUI/PlaySceneUI.h"
#include "Game/SkyDome/SkyDome.h"
#include "Game/Camera/SceneCamera/GameCamera.h"
#include "Game/Camera/State/CameraStateLerpSwitch.h"
#include "Game/MyLibrary/Collision/Collision.h"
#include "Game/MyLibrary/Collision/BoxCollider.h"
#include "Game/MyLibrary/Shader/Shader.h"

using namespace DirectX;

//------------------------------------------------------------------
/**
 * @brief コンストラクタ
 *
 * @param sceneManager：ステージマネージャーへのポインタ
 */
PlayScene::PlayScene(SceneManager* sceneManager)
	: m_sceneManager(sceneManager)
	, m_stage(nullptr)
	, m_camera(nullptr)
	, m_player(nullptr)
	, m_ui(nullptr)
	, m_skyDome(nullptr)
	, m_gameState(GameState::START)
	, m_beforeMenuState(GameState::START)
	, m_dssStage(nullptr)
	, m_dssPlayerSilhouette(nullptr)
	, m_animationSkipTimer(0.0f)
	, m_isDispSkipUI(false)
	, m_isSwitchFail(false)
{
}

//------------------------------------------------------------------
/**
 * @brief デストラクタ
 */
PlayScene::~PlayScene()
{
}

//------------------------------------------------------------------
/**
 * @brief 初期化
 *
 * @param  なし
 * @return なし
 */
void PlayScene::Initialize()
{
	// 各種リソース取得
	GameResource*         gameResource    = GameResource::GetInstance();
	InputManager*         inputManager    = gameResource->GetInputManager();
	ResourceManager*      resourceManager = gameResource->GetResourceManager();

	// 使用するキーの登録
	inputManager->AddKey(
		{
			Keyboard::Keys::Up,    Keyboard::Keys::Down,  Keyboard::Keys::Right, Keyboard::Keys::Left,
			Keyboard::Keys::W,     Keyboard::Keys::A,     Keyboard::Keys::S,     Keyboard::Keys::D,
			Keyboard::Keys::E,     Keyboard::Keys::Space, Keyboard::Keys::Enter, Keyboard::Keys::Escape,
			Keyboard::Keys::F
		}
	);

	// 画面比計算
	RECT  screen      = gameResource->GetDeviceResources()->GetOutputSize();
	float aspectRatio = static_cast<float>(screen.right) / static_cast<float>(screen.bottom);
	// ステージ作成、初期化
	StageManager* stageManager = GameResource::GetInstance()->GetStageManager();
	int stageNum = m_sceneManager->GetSceneShareData()->GetSelectStageNumber();
	KT::Stage::Size stageSize = stageManager->GetStageSize(stageNum);	
	m_stage = std::make_unique<PlayStage>(stageNum, stageSize);
	m_stage->Initialize();
	// プレイヤー作成、初期化
	m_player = std::make_unique<Player>(this, m_stage->GetStartPosition());
	m_player->Initialize();
	// カメラ作成、初期設定
	m_camera = std::make_unique<GameCamera>(this, aspectRatio, stageSize.GetVector3());
	m_camera->SetPlayerPosition(m_player->GetPosition());
	m_camera->InitialCameraSetting(
		KT::GameParam::LERP_TIME_GAMESTART, 
		SimpleMath::Vector3(0.0f, 5.0f, 0.0f), KT::GameParam::EYE_OFFSET_SIDE,
		m_stage->GetGoalPosition(), m_player->GetPosition()
	);
	// UI・画像作成
	m_ui = std::make_unique<PlaySceneUI>(this, m_player.get(), m_camera.get());
	// UIを初期化
	m_ui->Initialize();
	// スカイドーム作成 
	// ステージの中心を位置に設定
	m_skyDome = std::make_unique<SkyDome>(stageSize.GetVector3() * 0.5f);
	// デプスステンシルの作成
	CreateDepthStancil();
	// シェーダー作成
	m_playerSilhouetteShader = std::make_unique<Shader<DirectX::VertexPosition>>();
	m_playerSilhouetteShader->CreateData(KT::Shader::PLAYER_SILHOUETTE);
	m_gameStartShader = std::make_unique<Shader<DirectX::VertexPositionTexture>>();
	m_gameStartShader->CreateData(KT::Shader::GAME_START_MASK);

	// BGMを流す
	resourceManager->PlaySound(KT::Sound::BGM, KT::Sound::BGMNumber::XACT_WAVEBANK_BGM_PLAY);
}

//------------------------------------------------------------------
/**
 * @brief 更新
 *
 * @param  なし
 * @return なし
 */
void PlayScene::Update()
{
	// 更新処理
	switch (m_gameState)
	{
		// ゲーム開始状態の更新処理
		case PlayScene::GameState::START:     GameStartUpdate();       break;
		// ゲームプレイ時の更新処理
		case PlayScene::GameState::PLAY:      GamePlayUpdate();        break;
		// ステージ見渡し時の更新処理
		case PlayScene::GameState::OVER_LOOK: GameOverLookingUpdate(); break;
		// メニュー時の更新処理
		case PlayScene::GameState::MENU:      GameMenuUpdate();        break;
		
		default:break;
	}
}

//------------------------------------------------------------------
/**
 * @brief 描画
 *
 * @param  なし
 * @return なし
 */
void PlayScene::Render()
{
	// 各種リソース取得
	GameResource*         gameResource  = GameResource::GetInstance();
	ID3D11DeviceContext1* context       = gameResource->GetDeviceResources()->GetD3DDeviceContext();
	CommonStates*         commonStates  = gameResource->GetCommonStates();
	EffectManager*        effectManager = gameResource->GetEffectManager();

	// カメラからビュー、射影行列、カメラ位置を取得
	SimpleMath::Matrix  view       = m_camera->GetViewMatrix();
	SimpleMath::Matrix  projection = m_camera->GetProjectionMatrix();
	SimpleMath::Vector3 eye        = m_camera->GetTargetPosition() + SimpleMath::Vector3::Transform(m_camera->GetEyePosition(), m_camera->GetRotation());

	// スカイドームの描画
	m_skyDome->Render(view, projection);
	// ステージ描画
	m_stage->Render(view, projection, eye,
		[&]()
		{
			// 深度ステンシルステートの設定
			context->OMSetDepthStencilState(m_dssStage.Get(), 0);
		}
	);
	// エフェクトの描画
	effectManager->Render(view, projection, eye, m_camera->GetTargetPosition(), m_camera->GetUpVector());
	// プレイヤーのシルエット描画
	m_player->RenderSilhouette(view, projection,
		[&]()
		{
			// 深度ステンシルステートの設定
			context->OMSetDepthStencilState(m_dssPlayerSilhouette.Get(), 1);
			// ピクセルシェーダー設定
			context->PSSetShader(m_playerSilhouetteShader->GetPixelShader(), nullptr, 0);
		}
	);
	// プレイヤー描画
	m_player->Render(view, projection,
		[&]()
		{
			// 3Dか
			if (Is3D()) return;
			// 切り替え時以外か
			if (IsOperationCamera()) return;
			if (IsOperationCompeteCamera()) return;
			// ブロックに隠れるので深度バッファを使用しない
			context->OMSetDepthStencilState(commonStates->DepthNone(), NULL);
		}
	);
	// ゲーム開始時にはマスクを掛ける
	if(m_gameState == GameState::START) RenderMask();	
	// メニュー表示
	m_sceneManager->GetSceneShareData()->GetMenuWindow()->Render();
}

//------------------------------------------------------------------
/**
 * @brief 後処理
 *
 * @param  なし
 * @return なし
 */
void PlayScene::Finalize()
{
	m_ui.reset();
	m_player.reset();
	m_camera.reset();
	m_stage.reset();
}

//------------------------------------------------------------------
/**
 * @brief シーンの切り替え
 *
 * @param  なし
 * @return なし
 */
void PlayScene::ChangeScene()
{
	m_sceneManager->SetNextScene<ResultScene>();
}

//------------------------------------------------------------------
/**
 * @brief ゲーム開始時の更新処理
 *
 * @param  なし
 * @return なし
 */
void PlayScene::GameStartUpdate()
{	
	// 各種リソース取得
	GameResource*  gameResource = GameResource::GetInstance();
	DX::StepTimer* stepTimer    = gameResource->GetStepTimer();
	InputManager*  inputManager = gameResource->GetInputManager();

	// カメラ更新
	m_camera->Update();
	// アニメーションスキップタイマー更新
	double elapsedTime = stepTimer->GetElapsedSeconds();
	m_animationSkipTimer += static_cast<float>(elapsedTime);

	// アニメーションスキップ
	if (m_animationSkipTimer > ANIMETION_SKIP_TIME)
	{
		// UIをマネージャーに追加
		if (!m_isDispSkipUI)
		{
			m_ui->ShowSkipUI();
			m_isDispSkipUI = true;
		}
		// アニメーションをスキップ
		if(inputManager->GetKey(Keyboard::Keys::Enter).press)
			m_camera->GetStateLerp()->Skip();
	}

	// カメラが操作可能か
	if (!m_camera->IsOperation())
	{
		// プレイ状態へ
		m_gameState = GameState::PLAY;
		// UI更新
		m_ui->ChangeStateAnimationToPlay();
	}
}

//------------------------------------------------------------------
/**
 * @brief ゲームプレイ時の更新処理
 *
 * @param  なし
 * @return なし
 */
void PlayScene::GamePlayUpdate()
{
	// 各種リソース取得
	GameResource*  gameResource  = GameResource::GetInstance();
	EffectManager* effectManager = gameResource->GetEffectManager();
	InputManager*  inputManager  = gameResource->GetInputManager();

	// 切り替え完了時
	if (IsOperationCompeteCamera())
	{
		// 失敗フラグが立っているか
		if (m_isSwitchFail)
		{
			// 次元を切り替える
			ChangeDimension(false);
			// 失敗フラグを折る
			m_isSwitchFail = false;
		}
	}

	// ステージ更新
	m_stage->Update(IsOperationCamera());

	// カメラが切り替えをしていない時
	if (!IsOperationCamera())
	{
		// プレイヤーの移動方向作成
		m_player->CreateMoveDirection(m_camera->GetDirection(), m_camera->GetUpVector());
		// プレイヤー更新
		m_player->Update();
		// 当たり判定
		CollisionDetection();
	}

	// プレイヤーの位置をカメラに渡し、注視点に設定
	m_camera->SetPlayerPosition(m_player->GetPosition());
	m_camera->SetTargetPosition(m_player->GetPosition());

	// カメラ更新
	m_camera->Update();
	// エフェクト更新
	effectManager->Update();
	
	// 次元切り替え
	if (inputManager->GetKey(Keyboard::Keys::E).press) ChangeDimension();
	// ステージ見渡し
	if (inputManager->GetKey(Keyboard::Keys::F).press)
	{
		// 見渡し状態へ
		m_gameState = GameState::OVER_LOOK;
		m_ui->ChangeStatePlayToOverLooking();
	}
	// メニュー表示
	if (inputManager->GetKey(Keyboard::Keys::Escape).press)
	{
		m_sceneManager->GetSceneShareData()->GetMenuWindow()->Open(MenuWindow::OpenScene::PLAY);
		m_beforeMenuState = m_gameState;
		m_gameState = GameState::MENU;
		m_ui->DeleteUIManagerAll();
	}
}

//------------------------------------------------------------------
/**
 * @brief 見渡し時の更新処理
 *
 * @param  なし
 * @return なし
 */
void PlayScene::GameOverLookingUpdate()
{
	// キーマネージャー取得
	InputManager* inputManager = GameResource::GetInstance()->GetInputManager();

	// プレイ状態へ
	if (inputManager->GetKey(Keyboard::Keys::F).press)
	{
		m_gameState = GameState::PLAY;
		m_ui->ChangeStateOverLookingToPlay();
	}
	// メニュー表示
	if (inputManager->GetKey(Keyboard::Keys::Escape).press)
	{
		m_sceneManager->GetSceneShareData()->GetMenuWindow()->Open(MenuWindow::OpenScene::PLAY);
		m_beforeMenuState = m_gameState;
		m_gameState = GameState::MENU;
		m_ui->DeleteUIManagerAll();
	}

	// カメラ更新
	m_camera->Update();
}

//------------------------------------------------------------------
/**
 * @brief メニュー時の更新処理
 *
 * @param  なし
 * @return なし
 */
void PlayScene::GameMenuUpdate()
{
	// キーマネージャー取得
	InputManager* inputManager = GameResource::GetInstance()->GetInputManager();

	// メニュー表示
	if (inputManager->GetKey(Keyboard::Keys::Escape).press)
	{
		// メニューを閉じる
		m_sceneManager->GetSceneShareData()->GetMenuWindow()->Close();
		m_gameState = m_beforeMenuState;
		if      (m_gameState == GameState::PLAY)      m_ui->ChangeStateMenuToPlay();
		else if (m_gameState == GameState::OVER_LOOK) m_ui->ChangeStateMenuToOverLooking();
	}

	// ウィンドウの更新
	m_sceneManager->GetSceneShareData()->GetMenuWindow()->Update();
}

//------------------------------------------------------------------
/**
 * @brief 当たり判定
 *
 * @param  なし
 * @return なし
 */
void PlayScene::CollisionDetection()
{
	// カメラの方向を取得する
	SimpleMath::Vector3 cameraDirection = m_camera->GetDirection();
	// プレイヤーのコライダーを取得する
	BoxCollider* playerBox = m_player->GetBoxCollider();
	// 当たったブロック取得用配列
	std::vector<BoxCollider*> hitObj;

	// 現在のステージを受け取る
	KT::Stage::StageData* stage = m_stage->GetStageData();
	for (std::unique_ptr<Block>& block : *stage)
	{
		// アクティブ状態でないなら飛ばす
		if (!block->IsActive()) continue;
		// 当たり判定を取らないブロックなら飛ばす
		if (block->GetCollisionMode() == KT::Block::CollisionMode::NONE) continue;

		// ブロックとプレイヤーの距離を測る
		SimpleMath::Vector3 distance = block->GetPosition() - m_player->GetPosition();
		// 視点方向から使用する方向のフラグを作成する
		SimpleMath::Vector3 flag = KT::MyUtility::InverseFlag(cameraDirection);
		// 2Dなら必要な方向のみにする
		if (Is2D()) distance *= flag;

		// ブロックとの距離が一定位置以内にいるか確認する
		if (distance.LengthSquared() > KT::GameParam::COLLISION_RAMGE) continue;

		// ステージブロックのコライダーを取得
		BoxCollider* blockBox = dynamic_cast<BoxCollider*>(block->GetCollider());

		// プレイヤーとステージブロックで当たり判定を取る
		if(!Collision::AABBCheck(Is2D(), cameraDirection, *blockBox, *playerBox)) continue;

		// 配列に保存
		hitObj.push_back(blockBox);
	}

	// 当たったオブジェクトをプレイヤーに近い順でソート
	std::sort(hitObj.begin(), hitObj.end(),
		[&](BoxCollider* lhs, BoxCollider* rhs)
		{
			// プレイヤーとの距離を計算
			SimpleMath::Vector3 distL = lhs->GetPosition() - playerBox->GetPosition();
			SimpleMath::Vector3 distR = rhs->GetPosition() - playerBox->GetPosition();
			// 2Dなら使わない方向を0にする
			if (Is2D())
			{
				SimpleMath::Vector3 dir = SimpleMath::Vector3::One - KT::MyUtility::AbsVector(cameraDirection);
				distL *= dir;
				distR *= dir;
			}
			return distL.LengthSquared() < distR.LengthSquared();
		}
	);

	// 衝突時処理を行う
	for(BoxCollider* box : hitObj)
	{
		playerBox->OnCollision(box);
	}
	// 当たり判定後の更新処理
	m_player->CollisionAfterUpdate();
}

//------------------------------------------------------------------
/**
 * @brief 画面マスク描画
 *
 * @param  なし
 * @return なし
 */
void PlayScene::RenderMask()
{
	// 描画
	m_gameStartShader->RenderQuad(VERTICES[0], VERTICES[1], VERTICES[2], VERTICES[3]);
}

//------------------------------------------------------------------
/**
 * @brief 次元の切り替え
 *
 * @param  isOwnOperation：プレイヤーの操作か
 * @return なし
 */
void PlayScene::ChangeDimension(bool isOwnOperation)
{
	// カメラ操作中なら処理を行わない
	if (IsOperationCamera()) return;
	// プレイヤーが地面の上にいないなら行わない
	if (!OnGroundPlayer()) return;

	// カメラの向き取得
	SimpleMath::Vector3 camDir = m_camera->GetDirection();
	// ステージ切替
	m_stage->ChangeDimension(m_camera->GetDimension(), camDir);
	// プレイヤー切替
	m_player->ChangeDimension(m_camera->GetDimension(), !isOwnOperation);
	// カメラ切替
	m_camera->ChangeDimensionSetting();

	// プレイヤー操作時
	if (isOwnOperation)
	{
		// 切替が成功するか確認する
		if      (Is3D()) m_isSwitchFail = !CheckChangeTo2DSuccessful(camDir);
		else if (Is2D()) m_isSwitchFail = !CheckChangeTo3DSuccessful();

		// SEを流す
		GameResource::GetInstance()->GetResourceManager()
			->PlaySound(KT::Sound::SE, KT::Sound::SENumber::XACT_WAVEBANK_SE_DIMENSIONCHANGE);
	}
}

//------------------------------------------------------------------
/**
 * @brief ゴールに到着
 *
 * @param  なし
 * @return なし
 */
void PlayScene::ArrivalGoal()
{
	// シーン切り替え
	ChangeScene();
}

//------------------------------------------------------------------
/**
 * @brief 深度ステンシルの作成
 *
 * @param  なし
 * @return なし
 */
void PlayScene::CreateDepthStancil()
{
	// 各種リソース取得
	GameResource*  gameResource = GameResource::GetInstance();
	ID3D11Device1* device       = gameResource->GetDeviceResources()->GetD3DDevice();

	//----------------------------------------------
	// ステージ用の深度ステンシルの作成
	//----------------------------------------------
	D3D11_DEPTH_STENCIL_DESC stageDesc = {};

	stageDesc.DepthEnable                  = TRUE;                             // 深度テストを行う
	stageDesc.DepthWriteMask               = D3D11_DEPTH_WRITE_MASK_ALL;
	stageDesc.DepthFunc                    = D3D11_COMPARISON_LESS_EQUAL;
	stageDesc.StencilEnable                = TRUE;                             // ステンシルテストを行う
	stageDesc.StencilReadMask              = D3D11_DEFAULT_STENCIL_READ_MASK;
	stageDesc.StencilWriteMask             = D3D11_DEFAULT_STENCIL_WRITE_MASK;
	stageDesc.FrontFace.StencilFunc        = D3D11_COMPARISON_EQUAL;           // データ == 参照値
	stageDesc.FrontFace.StencilPassOp      = D3D11_STENCIL_OP_INCR_SAT;        // ステンシル、深度テスト成功時インクリメント
	stageDesc.FrontFace.StencilFailOp      = D3D11_STENCIL_OP_KEEP;            // ステンシルテスト失敗時　何もしない
	stageDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_KEEP;            // ステンシル、深度テスト失敗時　何もしない
	stageDesc.BackFace                     = stageDesc.FrontFace;              // 裏面も同じ設定に

	device->CreateDepthStencilState(&stageDesc, m_dssStage.ReleaseAndGetAddressOf());

	//----------------------------------------------
	// プレイヤーシルエットのステンシルテストの設定
	//----------------------------------------------
	D3D11_DEPTH_STENCIL_DESC silhouetteDesc = {};
	
	silhouetteDesc.DepthEnable                  = FALSE;                            // 深度テストを行わない
	silhouetteDesc.StencilEnable                = TRUE;                             // ステンシルテストを行う
	silhouetteDesc.StencilReadMask              = D3D11_DEFAULT_STENCIL_READ_MASK;
	silhouetteDesc.StencilWriteMask             = D3D11_DEFAULT_STENCIL_WRITE_MASK;
	silhouetteDesc.FrontFace.StencilFunc        = D3D11_COMPARISON_EQUAL;           // データ == 参照値
	silhouetteDesc.FrontFace.StencilPassOp      = D3D11_STENCIL_OP_INCR_SAT;        // ステンシル、深度テスト成功時インクリメント
	silhouetteDesc.FrontFace.StencilFailOp      = D3D11_STENCIL_OP_KEEP;            // ステンシルテスト失敗時　何もしない
	silhouetteDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_KEEP;            // ステンシル、深度テスト失敗時　何もしない
	silhouetteDesc.BackFace                     = silhouetteDesc.FrontFace;         // 裏面も同じ設定に

	device->CreateDepthStencilState(&silhouetteDesc, m_dssPlayerSilhouette.ReleaseAndGetAddressOf());
}

//------------------------------------------------------------------
/**
 * @brief メニューの表示・非表示
 *
 * @param  なし
 * @return なし
 */
void PlayScene::OpenCloseMenu()
{
	m_sceneManager->GetSceneShareData()->
		GetMenuWindow()->OpenClose(MenuWindow::OpenScene::SELECT);
}

//------------------------------------------------------------------
/**
 * @brief 2D状態か
 *
 * @param  なし
 * @return true ：2D状態
 * @return false：2D状態ではない
 */
bool PlayScene::Is2D()
{
	return m_camera->CheckDimension(KT::GameParam::Dimension::_2D);
}

//------------------------------------------------------------------
/**
 * @brief 3D状態か
 *
 * @param  なし
 * @return true ：3D状態
 * @return false：3D状態ではない
 */
bool PlayScene::Is3D()
{
	return m_camera->CheckDimension(KT::GameParam::Dimension::_3D);
}

//------------------------------------------------------------------
/**
 * @brief 2Dへの切替が成功するか確認
 *
 * @param  camDir：カメラの視点方向
 * @return true  ：成功
 * @return false ：失敗
 */
bool PlayScene::CheckChangeTo2DSuccessful(const DirectX::SimpleMath::Vector3& camDir)
{
	// エイリアス宣言
	using RayHitCol = std::pair<Collider*, float>; // レイに当たったコライダー

	// プレイヤーの位置取得
	SimpleMath::Vector3 playerPos = m_player->GetPosition();
	// ステージサイズ取得
	SimpleMath::Vector3 stageSize = m_stage->GetStageSize().GetVector3();
	// カメラがどの方向に向いているか確認
	SimpleMath::Vector3 sightFlag = KT::MyUtility::AbsVector(camDir);
	bool dirX = sightFlag.x >= 1.0f;
	bool dirY = sightFlag.y >= 1.0f;
	bool dirZ = sightFlag.z >= 1.0f;
	// プレイヤーの４隅に対して飛ばすレイを作成
	SimpleMath::Ray ray[4] = { {camDir, SimpleMath::Vector3::Zero} };
	// 視点方向のレイの位置を作成
	SimpleMath::Vector3 rayPos = playerPos * KT::MyUtility::InverseFlag(camDir) + stageSize * -camDir;
	// プレイヤーの４隅計算用の位置
	SimpleMath::Vector3 offset = m_player->GetBoxCollider()->GetExtents() * KT::MyUtility::InverseFlag(camDir);
	// 位置がピッタリ過ぎるとプレイしずらいので半分に
	offset *= 0.5f;

	// レイの位置の最小と最大
	SimpleMath::Vector3 rayPosMin = rayPos - offset;
	SimpleMath::Vector3 rayPosMax = rayPos + offset;
	// レイの方向設定
	ray[0].direction = ray[1].direction = ray[2].direction = ray[3].direction = camDir;
	// レイを飛ばす位置設定
	if (dirX)
	{
		ray[0].position = { rayPos.x, rayPosMax.y, rayPosMax.z };
		ray[1].position = { rayPos.x, rayPosMax.y, rayPosMin.z };
		ray[2].position = { rayPos.x, rayPosMin.y, rayPosMax.z };
		ray[3].position = { rayPos.x, rayPosMin.y, rayPosMin.z };
	}
	else if (dirY)
	{
		ray[0].position = { rayPosMax.x, rayPos.y, rayPosMax.z };
		ray[1].position = { rayPosMax.x, rayPos.y, rayPosMin.z };
		ray[2].position = { rayPosMin.x, rayPos.y, rayPosMax.z };
		ray[3].position = { rayPosMin.x, rayPos.y, rayPosMin.z };
	}
	else if (dirZ)
	{
		ray[0].position = { rayPosMax.x, rayPosMax.y, rayPos.z };
		ray[1].position = { rayPosMax.x, rayPosMin.y, rayPos.z };
		ray[2].position = { rayPosMin.x, rayPosMax.y, rayPos.z };
		ray[3].position = { rayPosMin.x, rayPosMin.y, rayPos.z };
	}

	// ステージとレイの判定
	CollisionManager* colManager = GameResource::GetInstance()->GetCollisionManager();	
	// 当たったブロック取得用配列
	std::vector<RayHitCol> hitRay[4];

	for (int i = 0; i < 4; i++)
	{
		// レイとブロックの判定を行い当たったブロックを取得する
		hitRay[i] = colManager->HitRayStage(ray[i], m_stage->GetCollisionStage());

		// レイにコライダーが当たっていないなら次へ
		if (hitRay[i].empty()) continue;

		// プレイヤーからの距離が短い順でソートする
		std::sort(hitRay[i].begin(), hitRay[i].end(),
			[](const RayHitCol& lhs, const RayHitCol& rhs)
			{
				return lhs.second < rhs.second;
			}
		);
		// プレイヤーとレイの距離を求める
		float distance = std::fabsf((playerPos - ray[i].position).Length());
		// 一番近いブロックを取得
		Block* block = dynamic_cast<Block*>(hitRay[i][0].first->GetGameObject());
		// プレイヤーよりも近い位置いるか　又は
		// レンガブロックに重なっているか
		if (distance > hitRay[i][0].second || block->GetType() == KT::Block::Type::BRICK)
		{
			// 切り替え失敗
			return false;
		}
	}
	
	// 切り替え成功
	return true;
}

//------------------------------------------------------------------
/**
 * @brief 3Dへの切替が成功するか確認
 *
 * @param  なし
 * @return true ：成功
 * @return false：失敗
 */
bool PlayScene::CheckChangeTo3DSuccessful()
{
	return !m_player->IsFailWarp();
}

//------------------------------------------------------------------
/**
 * @brief 見下ろし視点か
 *
 * @param  なし
 * @return true ：見下ろし視点
 * @return false：見下ろし視点ではない
 */
bool PlayScene::IsTopDown() const
{
	return m_camera->CheckSightType(KT::GameParam::SightType::TOPDOWN);
}

//------------------------------------------------------------------
/**
 * @brief カメラ切替中か
 *
 * @param  なし
 * @return true ：切替中
 * @return false：切替中ではない
 */
bool PlayScene::IsOperationCamera() const
{
	return m_camera->CheckCameraState(KT::GameParam::CameraState::OPERATION);
}

//------------------------------------------------------------------
/**
 * @brief カメラ切替完了したか
 *
 * @param  なし
 * @return true ：切替完了
 * @return false：切替中
 */
bool PlayScene::IsOperationCompeteCamera() const
{
	return m_camera->CheckCameraState(KT::GameParam::CameraState::OPERATION_COMPLETE);
}

//------------------------------------------------------------------
/**
 * @brief プレイヤーが地面にいるか
 *
 * @param  なし
 * @return true ：地面にいる
 * @return false：空中にいる
 */
bool PlayScene::OnGroundPlayer()
{
	return m_player->OnGround();
}

//------------------------------------------------------------------
/**
 * @brief ゲームの状態を取得
 *
 * @param  なし
 * @return GameState：現在のゲームの状態
 */
PlayScene::GameState PlayScene::GetGameState() const
{
	return m_gameState;
}
