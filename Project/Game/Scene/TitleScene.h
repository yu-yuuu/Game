/**
 *
 * @file TitleScene.h
 *
 * @brief タイトルシーンを表すクラスのヘッダーファイル
 *
 * @author Kato Yuki
 *
 * @date 2023/11/8
 *
 */
#pragma once

#include "Model.h"
#include "Game/Scene/IScene.h"
#include "Game/Scene/SceneManager.h"

class TitleCamera;
class TitleStage;
class TitleSceneUI;
class SkyDome;

class TitleScene : public IScene
{
//----------------------------------------------
// 列挙体
//----------------------------------------------
public:

	// タイトルシーンの状態
	enum class TitleState
	{
		PUSH_ENTER,  // エンターを押してください
		SWITCHING,   // 切替中
		MODE_SELECT, // モード選択
	};

	// 遷移先モード
	enum class NextMode
	{
		PLAY = 0,  // ゲーム開始
		EXIT,      // ゲーム終了

		COUNT,     // モードの数
	};

//----------------------------------------------
// 変数
//----------------------------------------------
private:

	// シーンマネージャー
	SceneManager* m_sceneManager;

	// ステージ
	std::unique_ptr<TitleStage> m_stage;
	// カメラ
	std::unique_ptr<TitleCamera> m_camera;
	// UI
	std::unique_ptr<TitleSceneUI> m_ui;
	// スカイドーム
	std::unique_ptr<SkyDome> m_skyDome;

	// タイトルシーンの状態
	TitleState m_titleState;
	// 選択しているモード
	NextMode m_nextMode;

//----------------------------------------------
// 関数
//----------------------------------------------
public:

	// コンストラクタ
	TitleScene(SceneManager* sceneManager);
	// デストラクタ
	~TitleScene();
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

	// タイトルシーンの状態切り替え
	void ChangeState();
	// タイトルシーンの状態取得
	TitleState GetTitleState() const;
	// 遷移先のモード取得
	NextMode GetMode() const;
};