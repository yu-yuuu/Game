/**
 *
 * @file SceneManager.h
 *
 * @brief シーン管理クラスのヘッダーファイル
 *
 * @author Kato Yuki
 *
 * @date 2023/11/8
 *
 */
#pragma once

class IScene;
class Fade;
class SceneShareData;

class SceneManager
{
//----------------------------------------------
// 変数
//----------------------------------------------
private:
	
	// 現在のシーン
	std::unique_ptr<IScene> m_currentScene;
	// 切り替え先のシーン
	std::unique_ptr<IScene> m_nextScene;
	// フェード
	Fade* m_fade;
	// 各シーンで共有するデータ
	std::unique_ptr<SceneShareData> m_sceneShareData;

//----------------------------------------------
// 関数
//----------------------------------------------
public:

	// コンストラクタ
	SceneManager();
	// デストラクタ
	~SceneManager();
	// 初期化
	void Initialize();
	// 更新
	void Update();
	// 描画
	void Render();
	// 後処理
	void Finalize();

	// シーンの切替
	bool ChangeScene();
	// 次のシーンの設定
	template<typename T>
	void SetNextScene();
	// 現在シーンの削除
	void DeleteCurrentScene();
	// シーンを切り替えてよいか
	bool IsChangeScene();
	
	// シーン共有データの取得
	SceneShareData* GetSceneShareData() const;
};

//----------------------------------------------
// テンプレート関数定義
//----------------------------------------------

//------------------------------------------------------------------
/**
 * @brief 次のシーンの設定
 *
 * @tparam T：次のシーンのクラス
 * @return なし
 */
template<typename T>
inline void SceneManager::SetNextScene()
{
	m_nextScene.reset(new T(this));
}