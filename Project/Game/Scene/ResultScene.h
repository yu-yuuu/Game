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
#pragma once
#include "Game/Scene/IScene.h"
#include "Game/Scene/SceneManager.h"

class Camera;
class SkyDome;
class Stage;
class Player;
class Block;
class ResultSceneUI;

class ResultScene : public IScene
{
//----------------------------------------------
// 列挙体
//----------------------------------------------
public:

	// 遷移先モード
	enum class NextMode
	{
		NEXT = 0,     // 次のステージへ
		STAGE_SELECT, // ステージ選択

		COUNT,        // モードの数
	};


//----------------------------------------------
// 定数
//----------------------------------------------
private:

	// カメラの注視点位置
	const DirectX::SimpleMath::Vector3 CAMERA_TARGET_POSITION = DirectX::SimpleMath::Vector3(2.5f, 1.5f, 0.5f);
	// カメラ位置
	const DirectX::SimpleMath::Vector3 CAMERA_EYE_POSITION = DirectX::SimpleMath::Vector3(0.0f, -1.0f, 3.0f);
	// ゴールブロックの位置
	const DirectX::SimpleMath::Vector3 GOAL_BLOCK_POSITION = DirectX::SimpleMath::Vector3(5.0f, 0.0f, 0.0f);
	// プレイヤーの位置
	const DirectX::SimpleMath::Vector3 PLAYER_POSITION = DirectX::SimpleMath::Vector3(0.0f, -0.5f, 0.0f);
	// スカイドームの回転速度
	const float SKY_DOME_ROTATION_SPEED = 0.005f;

//----------------------------------------------
// 変数
//----------------------------------------------
private:

	// シーンマネージャー
	SceneManager* m_sceneManager;

	// カメラ
	std::unique_ptr<Camera> m_camera;
	// ゴールブロック
	std::unique_ptr<Block> m_block;
	// スカイドーム
	std::unique_ptr<SkyDome> m_skyDome;
	// プレイヤー
	std::unique_ptr<Player> m_player;
	// UI
	std::unique_ptr<ResultSceneUI> m_ui;

	// 遷移先モード
	NextMode m_nextMode;
	// ステージ数
	int m_stageNum;
	// 現在のステージ番号
	int m_currentStageNumber;

//----------------------------------------------
// 関数
//----------------------------------------------
public:

	// コンストラクタ
	ResultScene(SceneManager* sceneManager);
	// デストラクタ
	~ResultScene();
	// 初期化
	void Initialize() override;
	// 更新
	void Update() override;
	// 描画
	void Render() override;
	// 後処理
	void Finalize() override;
	// シーン切り替え
	void ChangeScene() override;

	// 最後のステージかどうか
	bool IsEndStageNumber();
	// 現在選択している遷移先モード取得
	NextMode GetNextMode() const;
};