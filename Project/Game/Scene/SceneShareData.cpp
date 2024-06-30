/**
 *
 * @file SceneShareData.cpp
 *
 * @brief 各シーンで共有するデータのソースファイル
 *
 * @author Kato Yuki
 *
 * @date 2024/1/21
 *
 */
#include "pch.h"
#include "SceneShareData.h"
#include "Game/MyLibrary/CommonResource/GameResource.h"

using namespace DirectX;

//------------------------------------------------------------------
/**
 * @brief コンストラクタ
 *
 * @param sceneManager：シーンマネージャーのポインタ
 */
SceneShareData::SceneShareData(SceneManager* sceneManager)
	: m_sceneManager(sceneManager)
	, m_selectStageNumber(0)
{
	// リソースマネージャー取得
	ResourceManager* resourceManager = GameResource::GetInstance()->GetResourceManager();

	// メニューウィンドウ作成
	m_menuWindow = std::make_unique<MenuWindow>(m_sceneManager, SimpleMath::Vector2(470, 500), resourceManager->GetTexture(KT::Texture::WINDOW_FRAME), SimpleMath::Vector2(640.0f, 360.0f));
	m_menuWindow->Initialize();
}

//------------------------------------------------------------------
/**
 * @brief コンストラクタ
 */
SceneShareData::~SceneShareData()
{
}

//------------------------------------------------------------------
/**
 * @brief メニューウィンドウ取得
 *
 * @param  なし
 * @return MenuWindow：メニューウィンドウのポインタ
 */
MenuWindow* SceneShareData::GetMenuWindow()
{
	return m_menuWindow.get();
}

//------------------------------------------------------------------
/**
 * @brief 選択したステージ番号の設定
 *
 * @param  selectStageNumber：選択したステージ番号
 * @return なし
 */
void SceneShareData::SetSelectStageNumber(const int& selectStageNumber)
{
	m_selectStageNumber = selectStageNumber;
}

//------------------------------------------------------------------
/**
 * @brief 選択したステージ番号の取得
 *
 * @param  なし
 * @return int：選択したステージ番号
 */
const int& SceneShareData::GetSelectStageNumber() const
{
	return m_selectStageNumber;
}