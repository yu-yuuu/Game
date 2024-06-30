/**
 *
 * @file PlayScene.h
 *
 * @brief プレイシーンを表すクラスのヘッダーファイル
 *
 * @author Kato Yuki
 *
 * @date 2023/11/8
 *
 */
#pragma once

#include "Model.h"
#include "PrimitiveBatch.h"
#include "VertexTypes.h"

#include "Game/Scene/IScene.h"

class SceneManager;
class PlayStage;
class GameCamera;
class Player;
class PlaySceneUI;
class SkyDome;
template<typename Vertex>
class Shader;

class PlayScene : public IScene
{
//----------------------------------------------
// 列挙体
//----------------------------------------------
public:

	// ゲームの状態
	enum class GameState
	{
		START,     // ゲーム開始時
		PLAY,      // プレイ中
		OVER_LOOK, // ステージ見渡し
		GOAL,      // ゴール
		MENU,      // メニュー
	};

//----------------------------------------------
// 定数
//----------------------------------------------
public:

	// アニメーションスキップが出来る様になる時間
	const float ANIMETION_SKIP_TIME = 1.0f;

	// ゲーム開始マスク描画用板ポリゴン
	const DirectX::VertexPositionTexture VERTICES[4] =
	{
		DirectX::VertexPositionTexture(DirectX::SimpleMath::Vector3(-1.0f,  1.0f, 0.0f), DirectX::SimpleMath::Vector2(0.0f, 0.0f)), // 左上
		DirectX::VertexPositionTexture(DirectX::SimpleMath::Vector3( 1.0f,  1.0f, 0.0f), DirectX::SimpleMath::Vector2(1.0f, 0.0f)), // 右上
		DirectX::VertexPositionTexture(DirectX::SimpleMath::Vector3( 1.0f, -1.0f, 0.0f), DirectX::SimpleMath::Vector2(1.0f, 1.0f)), // 右下
		DirectX::VertexPositionTexture(DirectX::SimpleMath::Vector3(-1.0f, -1.0f, 0.0f), DirectX::SimpleMath::Vector2(0.0f, 1.0f))  // 左下
	};

//----------------------------------------------
// 変数
//----------------------------------------------
private:

	// シーンマネージャー
	SceneManager* m_sceneManager;
	
	// ステージ
	std::unique_ptr<PlayStage> m_stage;
	// カメラ
	std::unique_ptr<GameCamera> m_camera;
	// プレイヤー
	std::unique_ptr<Player> m_player;
	// プレイシーンのUI、画像
	std::unique_ptr<PlaySceneUI> m_ui;
	// スカイドーム
	std::unique_ptr<SkyDome> m_skyDome;

	// ゲームの状態
	GameState m_gameState;
	// メニュー表示時に開いた状態保存用
	GameState m_beforeMenuState;

	// ステージに使用する深度ステンシルステート
	Microsoft::WRL::ComPtr<ID3D11DepthStencilState> m_dssStage;
	// プレイヤーのシルエットに使用する深度ステンシルステート
	Microsoft::WRL::ComPtr<ID3D11DepthStencilState> m_dssPlayerSilhouette;
	// プレイヤーシルエット用シェーダー
	std::unique_ptr<Shader<DirectX::VertexPosition>> m_playerSilhouetteShader;
	// ゲーム開始時画面マスク用シェーダー
	std::unique_ptr<Shader<DirectX::VertexPositionTexture>> m_gameStartShader;

	// アニメーションスキップ用タイマー
	float m_animationSkipTimer;
	// アニメーションスキップのUIを表示したか
	bool m_isDispSkipUI;
	// 次元切り替え失敗フラグ
	bool m_isSwitchFail;

//----------------------------------------------
// 関数
//----------------------------------------------
public:

	// コンストラクタ
	PlayScene(SceneManager* sceneManager);
	// デストラクタ
	~PlayScene();

	// 初期化
	void Initialize() override;
	// 更新
	void Update() override;
	// 描画
	void Render() override;
	// 後処理
	void Finalize() override;

	// シーンの切り替え
	void ChangeScene() override;

	// ゲーム開始時の更新処理
	void GameStartUpdate();
	// ゲームプレイ時の更新処理
	void GamePlayUpdate();
	// ステージ見渡し時の更新処理
	void GameOverLookingUpdate();
	// メニュー時の更新処理
	void GameMenuUpdate();

	// 当たり判定
	void CollisionDetection();

	// 画面マスク描画
	void RenderMask();

	// 次元切り替え
	void ChangeDimension(bool isOwnOperation = true);
	// ゴールに到着
	void ArrivalGoal();
	// 深度ステンシルの作成
	void CreateDepthStancil();

	// メニューの表示・非表示
	void OpenCloseMenu();

	// 2Dかどうか
	bool Is2D();
	// 3Dかどうか
	bool Is3D();
	// 次元切り替えが成功するか確認
	bool CheckChangeTo2DSuccessful(const DirectX::SimpleMath::Vector3& camDir);
	bool CheckChangeTo3DSuccessful();
	// 見下ろし視点か
	bool IsTopDown() const;
	// カメラ操作中か
	bool IsOperationCamera() const;
	// カメラ操作完了したか
	bool IsOperationCompeteCamera() const;
	// プレイヤーが地面にいるか
	bool OnGroundPlayer();
	// ゲームの状態取得
	GameState GetGameState() const;
};