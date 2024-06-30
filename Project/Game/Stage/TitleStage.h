/**
 *
 * @file TitleStage.h
 *
 * @brief タイトルシーンステージを表すクラスのヘッダ－ファイル
 *
 * @author Kato Yuki
 *
 * @date 2024/1/21
 *
 */
#pragma once

#include "Game/Stage/Stage.h"
#include "Game/Stage/StageData.h"

class TitleScene;

class TitleStage : public Stage
{
//----------------------------------------------
// 定数
//----------------------------------------------
private:

	// 点滅速度
	const float FLASH_SPEED = 2.0f;
	// 選択ボタンの明るさの最大、最小値
	const float SELECT_BUTTON_BRIGHTNESS_MIN = 0.125f;
	const float SELECT_BUTTON_BRIGHTNESS_MAX = 0.875f;

//----------------------------------------------
// 変数
//----------------------------------------------
private:

	// タイトルシーン
	TitleScene* m_titleScene;

//----------------------------------------------
// 関数
//----------------------------------------------
public:

	// コンストラクタ
	TitleStage(TitleScene* titleScene, int stageNumber, KT::Stage::Size size);
	// デストラクタ
	~TitleStage();
	// 初期化
	void Initialize();
	// 更新
	void Update();
};