/**
 *
 * @file SceneManager.cpp
 *
 * @brief シーン管理クラスのソースファイル
 *
 * @author Kato Yuki
 *
 * @date 2023/11/8
 *
 */
#include "pch.h"
#include "SceneManager.h"
#include "Game/Scene/IScene.h"
#include "Game/Scene/TitleScene.h"
#include "Game/Scene/StageSelectScene.h"
#include "Game/Scene/PlayScene.h"
#include "Game/Scene/ResultScene.h"
#include "Game/MyLibrary/CommonResource/GameResource.h"
#include "Game/Scene/SceneShareData.h"


//------------------------------------------------------------------
/**
 * @brief コンストラクタ
 *
 * @param なし
 */
SceneManager::SceneManager()
	: m_currentScene(nullptr)
	, m_nextScene(nullptr)
	, m_fade(nullptr)
	, m_sceneShareData(nullptr)
{
}

//------------------------------------------------------------------
/**
 * @brief デストラクタ
 */
SceneManager::~SceneManager()
{
	Finalize();
}

//------------------------------------------------------------------
/**
 * @brief 初期化
 *
 * @param  なし
 * @return なし
 */
void SceneManager::Initialize()
{
	// ゲームリソース取得
	GameResource* gameResource = GameResource::GetInstance();
	// フェード取得
	m_fade = gameResource->GetFade();
	// 起動シーンの設定、初期化
	m_currentScene = std::make_unique<TitleScene>(this);
	m_currentScene->Initialize();
	// シーン共有データ作成
	m_sceneShareData = std::make_unique<SceneShareData>(this);
}

//------------------------------------------------------------------
/**
 * @brief 更新
 *
 * @param  なし
 * @return なし
 */
void SceneManager::Update()
{
	// シーンを切り替えてもよいか
	if (IsChangeScene())
	{
		// 切り替えが完了
		if (ChangeScene())
		{
			// メニューが開いているかもしれないので閉じておく
			m_sceneShareData->GetMenuWindow()->Close();
			// フェードインスタート
			m_fade->StartFadeIn();
		}
	}

	// 現在シーンの更新
	m_currentScene->Update();

	// 次のシーンが設定されていたら
	if (m_nextScene)
	{
		// フェードアウトスタート
		m_fade->StartFadeOut();
	}
}

//------------------------------------------------------------------
/**
 * @brief 描画
 *
 * @param  なし
 * @return なし
 */
void SceneManager::Render()
{
	// 現在シーンの描画
	m_currentScene->Render();
}

//------------------------------------------------------------------
/**
 * @brief 後処理
 *
 * @param  なし
 * @return なし
 */
void SceneManager::Finalize()
{
	m_currentScene.reset();
	m_nextScene.reset();
}

//------------------------------------------------------------------
/**
 * @brief シーンの切り替え
 *
 * @param  なし
 * @return true：切り替え完了
 * @return false：切り替え中
 */
bool SceneManager::ChangeScene()
{
	assert(m_nextScene && "次のシーンが設定されていません");

	// 現在シーン削除
	DeleteCurrentScene();
	// シーンの切り替え
	m_currentScene = std::move(m_nextScene);
	// 新しいシーンの初期化
	m_currentScene->Initialize();
	// 次のシーンを初期化
	m_nextScene = nullptr;

	return true;
}

//------------------------------------------------------------------
/**
 * @brief 現在シーンの削除
 *
 * @param  なし
 * @return なし
 */
void SceneManager::DeleteCurrentScene()
{
	if (m_currentScene)
	{
		// 後処理
		m_currentScene->Finalize();
		// 現在シーンのユニークポインタを解放
		m_currentScene.reset();
		// 空にする
		m_currentScene = nullptr;

		// ゲームリソース取得
		GameResource* gameResource = GameResource::GetInstance();
		// UI登録解除
		gameResource->GetUIManager()->Clear();
		// エフェクト登録解除
		gameResource->GetEffectManager()->Clear();	
		// キー登録解除
		gameResource->GetInputManager()->Clear();
		// BGM停止
		gameResource->GetResourceManager()->StopSound(KT::Sound::BGM);
	}
}

//------------------------------------------------------------------
/**
 * @brief シーンを切り替えてよいか
 *
 * @param  なし
 * @return true：切り替え出来る
 * @return false：切り替え出来ない
 */
bool SceneManager::IsChangeScene()
{
	// 次のシーンが設定されているかつフェードイン待機状態か
	return m_nextScene && m_fade->CheckFadeState(Fade::FadeState::FADE_IN_WAIT);
}

//------------------------------------------------------------------
/**
 * @brief シーン共有データの取得
 *
 * @param  なし
 * @return SceneShareData：シーン共有データのポインタ
 */
SceneShareData* SceneManager::GetSceneShareData() const
{
	return m_sceneShareData.get();
}