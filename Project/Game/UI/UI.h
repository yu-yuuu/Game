/**
 *
 * @file UI.h
 *
 * @brief UIを表すクラスのヘッダーファイル
 *
 * @author Kato Yuki
 *
 * @date 2024/1/14
 *
 */
#pragma once

#include "Game/MyLibrary/ResourceManager/ResourceType.h"
#include "Game/MyLibrary/Texture/Texture.h"
#include "Game/UI/UIManager.h"

class UI
{
//----------------------------------------------
// 変数
//----------------------------------------------
private:

	// タグ
	std::vector<std::string> m_tagList;
	// テクスチャデータ
	std::unique_ptr<Texture> m_texture;
	// 描画位置
	DirectX::SimpleMath::Vector2 m_position;
	// 反転表示させるか
	bool m_reverseX; // 横
	bool m_reverseY; // 縦

//----------------------------------------------
//  関数
//----------------------------------------------
public:

	// コンストラクタ
	UI(
		const std::vector<std::string>& tagList,
		std::unique_ptr<Texture> texture, 
		const DirectX::SimpleMath::Vector2& position, 
		bool reverseX = false, 
		bool reverseY = false);
	// デストラクタ
	~UI();

	// 更新
	virtual void Update();
	// 描画
	void Render(UIManager* uiManager);

	// タグリストの取得
	std::vector<std::string> GetTagList() const;
	// テクスチャデータの取得、設定
	Texture* GetTexture() const;
	void SetTexture(std::unique_ptr<Texture> texture);
	// 位置の取得、設定
	DirectX::SimpleMath::Vector2 GetPosition() const;
	void SetPosition(const DirectX::SimpleMath::Vector2& position);
};