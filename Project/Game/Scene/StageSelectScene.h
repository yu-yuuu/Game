/**
 *
 * @file StageSelectScene.h
 *
 * @brief ステージ選択シーンを表すクラスのヘッダーファイル
 *
 * @author Kato Yuki
 *
 * @date 2023/11/8
 *
 */
#pragma once

#include <vector>
#include "Model.h"
#include "Game/Scene/IScene.h"
#include "Game/Scene/SceneManager.h"

class StageSelectCamera;
class SelectStage;
class StageSelectSceneUI;
class SkyDome;

class StageSelectScene : public IScene
{
//----------------------------------------------
// 定数
//----------------------------------------------
public:

	// カメラの回転速度
	const float CAMERA_ROTATION_SPEED = 0.01f;

//----------------------------------------------
// 列挙体
//----------------------------------------------
private:

	// シーンの状態
	enum class SceneState
	{
		SELECT, // ステージ選択状態
		MENU,   // メニュー状態
	};


//----------------------------------------------
// 変数
//----------------------------------------------
private:

	// シーンマネージャー
	SceneManager* m_sceneManager;

	// ステージ
	std::unique_ptr<SelectStage> m_stage;
	// カメラ
	std::unique_ptr<StageSelectCamera> m_camera;
	// UI
	std::unique_ptr<StageSelectSceneUI> m_ui;
	// スカイドーム
	std::unique_ptr<SkyDome> m_skyDome;

	// シーンの状態
	SceneState m_sceneState;
	// ステージの番号リスト
	std::vector<int> m_stageNumberList;	
	// 選択しているステージの要素番号
	int m_stageNumberIndex;
	// ステージの切替アニメーションが終わったか
	bool m_isSwitchFinished;

//----------------------------------------------
// 関数
//----------------------------------------------
public:

	// コンストラクタ
	StageSelectScene(SceneManager* sceneManager);
	// デストラクタ
	~StageSelectScene();
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

	// ステージ選択時の更新処理
	void SelectUpdate();
	// メニュー表示時の更新処理
	void MenuUpdate();
	// ステージ選択
	void StageSelect();

	// 現在選択しているステージの要素番号取得
	int GetSelectIndex();
	// ステージの数
	int GetStageNum();

	// ステージ切替完了時処理
	void StageSwitchComplete();

};