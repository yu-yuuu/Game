/**
 *
 * @file SceneUI.h
 *
 * @brief シーンに配置するUIをまとめるクラスのヘッダーファイル
 *
 * @author Kato Yuki
 *
 * @date 2024/1/22
 *
 */
#pragma once

#include <vector>
#include <initializer_list>
#include <string>
#include <unordered_map>
#include "Game/MyLibrary/Texture/Texture.h"
#include "Game/MyLibrary/File/FileManager.h"
#include "Game/MyLibrary/CommonResource/GameResource.h"

class UI;
class OperatableUI;

class SceneUI
{
//----------------------------------------------
// 変数
//----------------------------------------------
private:

	// UIリスト
	std::unordered_map<std::string, std::unique_ptr<UI>> m_newList;

//----------------------------------------------
// 関数
//----------------------------------------------
public:

	// コンストラクタ
	SceneUI();
	// デストラクタ
	virtual ~SceneUI();
	// 初期化
	virtual void Initialize() = 0;
	// 更新
	virtual void Update();

	// UIマネージャーへ登録
	void AddUIManager(const std::string& tag);
	// UIマネージャーへリスト内全てのUIを登録
	void AddUIManagerAll();
	// UIマネージャーから削除
	void DeleteUIManager(const std::string& tag);
	// UIマネージャーへリスト内全てのUIを削除
	void DeleteUIManagerAll();
	// シーンUIをマネージャーに設定
	void SetUIManagerSceneUI();
	// シーンUIをマネージャーから削除
	void DeleteUIManagerSceneUI();

	// UI作成（呼び出し用）
	void CreateUI(const std::string& sceneName);
	// 操作UI取得
	OperatableUI* GetUI(const std::string& name);

private:

	// 通常UI作成
	std::unique_ptr<UI> CreateUI(
		const std::vector<std::string>& tagList,
		const std::string& texName,
		const Texture::AnchorPoint& anchor,
		const DirectX::SimpleMath::Vector2& position,
		const DirectX::SimpleMath::Vector2& scale,
		const DirectX::SimpleMath::Color& color,
		const bool& reverseX,
		const bool& reverseY
	);
	// 操作UI作成
	std::unique_ptr<OperatableUI> CreateOperatableUI(
		const std::vector<std::string>& tagList,
		const std::string& texName,
		const Texture::AnchorPoint& anchor,
		const DirectX::SimpleMath::Vector2& position,
		const DirectX::SimpleMath::Vector2& scale,
		const DirectX::SimpleMath::Color& color,
		const DirectX::Keyboard::Keys& key,
		const bool& reverseX,
		const bool& reverseY
	);
};