/**
 *
 * @file PlaySceneUI.h
 *
 * @brief プレイシーンで使用するUI、画像クラスのヘッダーファイル
 *
 * @author Kato Yuki
 *
 * @date 2024/1/16
 *
 */
#pragma once

#include <vector>
#include <string>
#include "Game/UI/SceneUI/SceneUI.h"

class PlayScene;
class Player;
class GameCamera;
class OperatableUI;

class PlaySceneUI : public SceneUI
{
//----------------------------------------------
// 定数
//----------------------------------------------
private:

	// プレイ状態で常に描画するUIのタグ
	const std::string TAG_PLAY_ALWAYS           = "Always";
	// 開始アニメーションUIのタグ
	const std::string TAG_START_ANIMATION       = "StartAnimation";
	// プレイ状態UIのタグ
	const std::string TAG_PLAY_STATE            = "PlayState";
	// 2D見渡し状態UIタグ
	const std::string TAG_OVER_LOOKING_STATE_2D = "OverLooking2D";
	// 3D見渡し状態UIのタグ
	const std::string TAG_OVER_LOOKING_STATE_3D = "OverLooking3D";

//----------------------------------------------
// 変数
//----------------------------------------------
private:

	// プレイシーン
	PlayScene* m_playScene;
	// プレイヤー
	Player* m_player;
	// カメラ
	GameCamera* m_camera;

	// 移動ボタン
	OperatableUI* m_moveButtonUp;
	OperatableUI* m_moveButtonDown;
	OperatableUI* m_moveButtonRight;
	OperatableUI* m_moveButtonLeft;
	// ジャンプボタン
	OperatableUI* m_jumpButton;
	// カメラの回転ボタン
	OperatableUI* m_camRotButtonW;
	OperatableUI* m_camRotButtonS;
	OperatableUI* m_camRotButtonA;
	OperatableUI* m_camRotButtonD;
	// 次元切り替えボタン
	OperatableUI* m_dimensionButton;
	// 見渡すボタン
	OperatableUI* m_overLookingButton;

//----------------------------------------------
// 関数
//----------------------------------------------
public:

	// コンストラクタ
	PlaySceneUI(PlayScene* playScene, Player* player, GameCamera* camera);
	// デストラクタ
	~PlaySceneUI();

	// 初期化
	void Initialize() override;
	// 更新
	void Update() override;

	// プレイ時更新
	void PlayUpdate();
	// 見渡し時更新
	void OverLookingUpdate();

	// 開始時アニメーションスキップUI表示
	void ShowSkipUI();
	// 開始時アニメーションからプレイ状態へ
	void ChangeStateAnimationToPlay();
	// メニューからプレイ状態へ切替
	void ChangeStateMenuToPlay();
	// メニューから見渡し状態へ切替
	void ChangeStateMenuToOverLooking();
	// プレイから見渡し状態へ切替
	void ChangeStatePlayToOverLooking();
	// 見渡しからプレイ状態へ切替
	void ChangeStateOverLookingToPlay();

	// 見渡し状態のキーを取得する
	std::string GetOverLookingKey(bool is2D);
};