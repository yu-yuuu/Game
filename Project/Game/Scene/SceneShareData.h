/**
 *
 * @file SceneShareData.h
 *
 * @brief 各シーンで共有するデータのヘッダーファイル
 *
 * @author Kato Yuki
 *
 * @date 2024/1/21
 *
 */
#pragma once

class SceneManager;
class MenuWindow;

class SceneShareData
{
//----------------------------------------------
// 定数
//----------------------------------------------
private:



//----------------------------------------------
// 変数
//----------------------------------------------
private:

	// シーンマネージャー
	SceneManager* m_sceneManager;
	// メニューウィンドウ
	std::unique_ptr<MenuWindow> m_menuWindow;
	// 選択したステージ番号
	int m_selectStageNumber;

//----------------------------------------------
// 関数
//----------------------------------------------
public:

	// コンストラクタ
	SceneShareData(SceneManager* sceneManager);
	// デストラクタ
	~SceneShareData();

	// メニューウィンドウ取得
	MenuWindow* GetMenuWindow();
	// 選択したステージ番号の設定
	void SetSelectStageNumber(const int& selectStageNumber);
	// 選択したステージ番号の取得
	const int& GetSelectStageNumber() const;
};