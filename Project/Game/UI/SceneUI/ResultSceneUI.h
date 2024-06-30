/**
 *
 * @file ResultSceneUI.h
 *
 * @brief リザルトシーンのUIをまとめるクラスのヘッダーファイル
 *
 * @author Kato Yuki
 *
 * @date 2024/3/13
 *
 */
#pragma once

#include <string>
#include "Game/UI/SceneUI/SceneUI.h"

class ResultScene;
class OperatableUI;

class ResultSceneUI : public SceneUI
{
//----------------------------------------------
// 定数
//----------------------------------------------
private:

	// 常に描画するUIのタグ
	const std::string TAG_ALWAYS = "Always";

//----------------------------------------------
// 変数
//----------------------------------------------
private:

	// リザルトシーン
	ResultScene* m_resultScene;
	// 選択するUI
	std::vector<OperatableUI*> m_selectUI;

//----------------------------------------------
// 関数
//----------------------------------------------
public:

	// コンストラクタ
	ResultSceneUI(ResultScene* resultScene);
	// デストラクタ
	~ResultSceneUI();
	// 初期化
	void Initialize() override;
	// 選択
	void Select(const int& type);
};