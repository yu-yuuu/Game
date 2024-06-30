/**
 *
 * @file SceneUI.cpp
 *
 * @brief シーンに配置するUIをまとめるクラスのソースファイル
 *
 * @author Kato Yuki
 *
 * @date 2024/1/22
 *
 */
#include "pch.h"
#include "SceneUI.h"

#include "Game/UI/OperatableUI.h"
#include "Game/MyLibrary/CommonResource/GameResource.h"
#include "Game/MyLibrary/Utility/MyUtility.h"

using namespace DirectX;

//------------------------------------------------------------------
/**
 * @brief コンストラクタ
 *
 * @param なし
 */
SceneUI::SceneUI()
	: m_newList()
{
}

//------------------------------------------------------------------
/**
 * @brief デストラクタ
 *
 */
SceneUI::~SceneUI()
{
}

//------------------------------------------------------------------
/**
 * @brief 更新
 *
 * @param  なし
 * @return なし
 */
void SceneUI::Update()
{
	// 継承先で処理があれば記述する
}

//------------------------------------------------------------------
/**
 * @brief UIマネージャーへ登録
 *
 * @param tag：登録するUIのキー
 * @return なし
 */
void SceneUI::AddUIManager(const std::string& tag)
{
	// UIマネージャー受け取り
	UIManager* uiManager = GameResource::GetInstance()->GetUIManager();

	for (auto& ui : m_newList)
	{
		// UIマネージャーへ登録
		std::vector<std::string> tagList = ui.second->GetTagList();
		for (const std::string& t : tagList)
		{
			if (tag != t) continue;

			uiManager->AddUI(ui.second.get());
		}
	}
}

//------------------------------------------------------------------
/**
 * @brief UIマネージャーへリスト内全てのUIを登録
 *
 * @param  なし
 * @return なし
 */
void SceneUI::AddUIManagerAll()
{
	for (auto& ui : m_newList)
	{
		// UIマネージャーへ登録
		std::vector<std::string> tagList = ui.second->GetTagList();
		for (const std::string& t : tagList)
		{
			AddUIManager(t);
		}
	}
}

//------------------------------------------------------------------
/**
 * @brief UIマネージャーから削除
 *
 * @param tag：
 * @return なし
 */
void SceneUI::DeleteUIManager(const std::string& tag)
{
	// UIマネージャー受け取り
	UIManager* uiManager = GameResource::GetInstance()->GetUIManager();
	for (auto& ui : m_newList)
	{
		// UIマネージャーへ登録
		std::vector<std::string> tagList = ui.second->GetTagList();
		for (const std::string& t : tagList)
		{
			if (tag != t) continue;

			uiManager->Delete(ui.second.get());
		}
	}
}

//------------------------------------------------------------------
/**
 * @brief UIマネージャーへリスト内全てのUIを削除
 *
 * @param  なし
 * @return なし
 */
void SceneUI::DeleteUIManagerAll()
{
	for (auto& ui : m_newList)
	{
		// UIマネージャーへ登録
		std::vector<std::string> tagList = ui.second->GetTagList();
		for (const std::string& t : tagList)
		{
			DeleteUIManager(t);
		}
	}
}

//------------------------------------------------------------------
/**
 * @brief シーンUIをマネージャーに設定
 *
 * @param  なし
 * @return なし
 */
void SceneUI::SetUIManagerSceneUI()
{
	// UIマネージャー受け取り
	UIManager* uiManager = GameResource::GetInstance()->GetUIManager();
	// シーンUIをマネージャーへ登録
	uiManager->SetSceneUI(this);
}

//------------------------------------------------------------------
/**
 * @brief シーンUIをマネージャーから削除
 *
 * @param  なし
 * @return なし
 */
void SceneUI::DeleteUIManagerSceneUI()
{
	// UIマネージャー受け取り
	UIManager* uiManager = GameResource::GetInstance()->GetUIManager();
	// シーンUIをマネージャーから削除
	uiManager->DeleteSceneUI();
}

//------------------------------------------------------------------
/**
 * @brief UI作成（呼び出し用）
 *
 * @param  sceneName：作成するシーンの名前
 * @return なし
 */
void SceneUI::CreateUI(const std::string& sceneName)
{
	using namespace KT::UI;

	// UIデータ取得
	FilePathList* filePathList = GameResource::GetInstance()->GetFilePathList();
	nlohmann::json uiData = FileManager::LoadJSON(filePathList->GetPath(KT::File::UI));
	nlohmann::json sceneUIData = uiData[sceneName];

	for (const nlohmann::json& data : sceneUIData)
	{
		// UIの名前
		std::string name = data[PROPERTIE_NAME];
		// 操作するか
		bool isOperate = data[PROPERTIE_IS_OPERATE];
		// 使用する画像の名前
		std::string texName = data[PROPERTIE_TEXTURE];
		// 描画位置
		SimpleMath::Vector2 position = SimpleMath::Vector2(data[PROPERTIE_POSITION][0], data[PROPERTIE_POSITION][1]);
		// アンカーポイント
		Texture::AnchorPoint anchorPoint = static_cast<Texture::AnchorPoint>(data[PROPERTIE_ANCHOR_POINT]);
		// 拡大率
		SimpleMath::Vector2 scale = SimpleMath::Vector2(data[PROPERTIE_SCALE][0], data[PROPERTIE_SCALE][1]);
		// UIの色合い
		SimpleMath::Color color = SimpleMath::Color(data[PROPERTIE_COLOR][0], data[PROPERTIE_COLOR][1], data[PROPERTIE_COLOR][2], data[PROPERTIE_COLOR][3]);
		// 縦、横を反転させるか
		bool reverseX = data[PROPERTIE_REVERSE_X];
		bool reverseY = data[PROPERTIE_REVERSE_Y];
		// 対応させるキー
		std::string keyStr = data[PROPERTIE_INPUT_KEY];
		Keyboard::Keys key = static_cast<Keyboard::Keys>(KT::MyUtility::ConvertToHexadecimal(keyStr));
		// タグ
		std::vector<std::string> tagList;
		for (const nlohmann::json& tag : data[PROPERTIE_TAG])
		{
			tagList.push_back(tag);
		}

		// UI作成
		if (isOperate) m_newList[name] = std::move(CreateOperatableUI(tagList, texName, anchorPoint, position, scale, color, key, reverseX, reverseY));
		else           m_newList[name] = std::move(CreateUI(tagList, texName, anchorPoint, position, scale, color, reverseX, reverseY));
	}
}

//------------------------------------------------------------------
/**
 * @brief 操作UIの取得
 *
 * @param name：取得したいUIの名前
 * @return OperatableUI*：操作UIのポインタ
 */
OperatableUI* SceneUI::GetUI(const std::string& name)
{
	for (auto& ui : m_newList)
	{
		// 取得したい名前でないなら飛ばす
		if (ui.first != name) continue;

		// UIを操作UIへキャスト
		OperatableUI* opUI = dynamic_cast<OperatableUI*>(ui.second.get());

		assert(opUI && "取得したいUIが操作UIではありません");

		return opUI;
	}
	// 存在しないなら強制終了
	assert(false && "取得したいUIが存在しません");
	return nullptr;
}

//------------------------------------------------------------------
/**
 * @brief 通常UI作成
 *
 * @param tagList        ：識別用タグリスト
 * @param texName        ：UIに使用するテクスチャの名前
 * @param anchor         ：アンカーポイント
 * @param position       ：描画位置
 * @param scale          ：スケール
 * @param color          ：テクスチャの色合い
 * @param reverseX       ：横を反転表示させるか
 * @param reverseY       ：縦を反転表示させるか
 * @return unique_ptr<UI>：作成したUI
 */
std::unique_ptr<UI> SceneUI::CreateUI(
	const std::vector<std::string>& tagList,
	const std::string& texName,
	const Texture::AnchorPoint& anchor,
	const DirectX::SimpleMath::Vector2& position,
	const DirectX::SimpleMath::Vector2& scale,
	const DirectX::SimpleMath::Color& color,
	const bool& reverseX,
	const bool& reverseY)
{
	// リソースマネージャー受け取り
	ResourceManager* resourceManager = GameResource::GetInstance()->GetResourceManager();
	// テクスチャ受け取り
	KT::Texture::TextureData data = resourceManager->GetTexture(texName);
	// テクスチャ作成
	std::unique_ptr<Texture> texture = std::make_unique<Texture>(data, anchor, scale, color);
	// UI作成
	std::unique_ptr<UI> ui = std::make_unique<UI>(tagList, std::move(texture), position, reverseX, reverseY);

	return std::move(ui);
}

//------------------------------------------------------------------
/**
 * @brief 操作UI作成
 *
 * @param tagList        ：識別用タグリスト
 * @param texName        ：UIに使用するテクスチャの名前
 * @param anchor         ：アンカーポイント
 * @param position       ：描画位置
 * @param scale          ：スケール
 * @param color          ：テクスチャの色合い
 * @param key            ：対応させるキー
 * @param reverseX       ：横を反転表示させるか
 * @param reverseY       ：縦を反転表示させるか
 * @return unique_ptr<UI>：作成したUI
 */
std::unique_ptr<OperatableUI> SceneUI::CreateOperatableUI(
	const std::vector<std::string>& tagList,
	const std::string& texName,
	const Texture::AnchorPoint& anchor,
	const DirectX::SimpleMath::Vector2& position,
	const DirectX::SimpleMath::Vector2& scale,
	const DirectX::SimpleMath::Color& color,
	const DirectX::Keyboard::Keys& key,
	const bool& reverseX,
	const bool& reverseY)
{
	// リソースマネージャー受け取り
	ResourceManager* resourceManager = GameResource::GetInstance()->GetResourceManager();
	// テクスチャ受け取り
	KT::Texture::TextureData data = resourceManager->GetTexture(texName);
	// テクスチャ作成
	std::unique_ptr<Texture> texture = std::make_unique<Texture>(data, anchor, scale, color);
	// 操作UI作成
	std::unique_ptr<OperatableUI> operatableUI = std::make_unique<OperatableUI>(tagList, std::move(texture), position, key, reverseX, reverseY);

	return operatableUI;
}