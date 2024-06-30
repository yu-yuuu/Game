/**
 *
 * @file UIManager.cpp
 *
 * @brief UIの管理クラスのソースファイル
 *
 * @author Kato Yuki
 *
 * @date 2024/1/14
 *
 *
 */
#include "pch.h"
#include "UIManager.h"

#include "Game/UI/UI.h"
#include "Game/MyLibrary/CommonResource/GameResource.h"
#include "Game/UI/SceneUI/SceneUI.h"
#include "Game/MyLibrary/Shader/Shader.h"

using namespace DirectX;

//----------------------------------------------
// 定数宣言
//----------------------------------------------

// 頂点データの情報
const D3D11_INPUT_ELEMENT_DESC UIManager::UIVertexData::InputElements[] =
{
	{ "SV_Position", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "COLOR",       0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "TEXCOORD",    0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "TEXCOORD",    1, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
};

//------------------------------------------------------------------
/**
 * @brief コンストラクタ
 *
 * @param なし
 */
UIManager::UIManager()
	: m_uiList()
	, m_sceneUI(nullptr)
	, m_uiConstantBuffer{}
{
}

//------------------------------------------------------------------
/**
 * @brief デストラクタ
 *
 */
UIManager::~UIManager()
{
}

//------------------------------------------------------------------
/**
 * @brief 初期化
 *
 * @param  なし
 * @return なし
 */
void UIManager::Initialize()
{
	// シェーダー作成
	m_shader = std::make_unique<Shader<UIVertexData>>();
	m_shader->CreateData(KT::Shader::UI);
	m_shader->CreateConstantBuffer<UIConstantBuffer>();
	// 定数バッファにウィンドウサイズを設定
	DX::DeviceResources*  deviceResources = GameResource::GetInstance()->GetDeviceResources();
	RECT window = deviceResources->GetOutputSize();
	m_uiConstantBuffer.windowSize.x = static_cast<float>(window.right);
	m_uiConstantBuffer.windowSize.y = static_cast<float>(window.bottom);
}

//------------------------------------------------------------------
/**
 * @brief 更新
 *
 * @param  なし
 * @return なし
 */
void UIManager::Update()
{
	// シーンUIの更新
	if(m_sceneUI) m_sceneUI->Update();

	// 登録されているUIの更新
	for (UI* ui : m_uiList)
	{
		ui->Update();
	}
}

//------------------------------------------------------------------
/**
 * @brief 描画
 *
 * @param  なし
 * @return なし
 */
void UIManager::Render()
{
	// 定数バッファの更新
	m_shader->UpdateConstantBuffer(m_uiConstantBuffer);
	// 登録されているUIの描画
	for (UI* ui : m_uiList)
	{
		ui->Render(this);
	}
}

//------------------------------------------------------------------
/**
 * @brief UIの追加
 *
 * @param  ui：追加するUIのポインタ
 * @return なし
 */
void UIManager::AddUI(UI* ui)
{
	if (std::find(m_uiList.begin(), m_uiList.end(), ui) == m_uiList.end())
	{
		m_uiList.push_back(ui);
	}
}

//------------------------------------------------------------------
/**
 * @brief UIの追加
 *
 * @param  list：追加するUIのリスト(initializerList)
 * @return なし
 */
void UIManager::AddUI(const std::initializer_list<UI*>& list)
{
	for (UI* ui : list)
	{
		AddUI(ui);
	}
}

//------------------------------------------------------------------
/**
 * @brief UIの追加
 *
 * @param  list：追加するUIのリスト(vector)
 * @return なし
 */
void UIManager::AddUI(const std::vector<UI*>& list)
{
	for (UI* ui : list)
	{
		AddUI(ui);
	}
}

//------------------------------------------------------------------
/**
 * @brief 登録UIの削除
 *
 * @param deleteUI：登録解除したいUIのポインタ
 * @return なし
 */
void UIManager::Delete(UI* deleteUI)
{
	// 削除するUIを探す
	std::vector<UI*>::iterator it = std::find(m_uiList.begin(), m_uiList.end(), deleteUI);
	
	// 見つかった
	if (it != m_uiList.end())
	{
		// 削除
		m_uiList.erase(it);
	}
}

//------------------------------------------------------------------
/**
 * @brief 登録UIの削除(一括)
 *
 * @param list：登録解除したいUIのリスト(initializerList)
 * @return なし
 */
void UIManager::Delete(const std::initializer_list<UI*>& list)
{
	for (UI* ui : list)
	{
		Delete(ui);
	}
}

//------------------------------------------------------------------
/**
 * @brief 登録UIの削除(一括)
 *
 * @param list：登録解除したいUIのリスト(vector)
 * @return なし
 */
void UIManager::Delete(const std::vector<UI*>& list)
{
	for (UI* ui : list)
	{
		Delete(ui);
	}
}

//------------------------------------------------------------------
/**
 * @brief シーンUIの登録
 *
 * @param  sceneUI：登録するシーンUI
 * @return なし
 */
void UIManager::SetSceneUI(SceneUI* sceneUI)
{
	m_sceneUI = sceneUI;
}

//------------------------------------------------------------------
/**
 * @brief シーンUIの削除
 *
 * @param  なし
 * @return なし
 */
void UIManager::DeleteSceneUI()
{
	m_sceneUI = nullptr;
}

//------------------------------------------------------------------
/**
 * @brief 登録UIの全削除
 *
 * @param  なし
 * @return なし
 */
void UIManager::Clear()
{
	m_uiList.clear();
	m_sceneUI = nullptr;
}

//------------------------------------------------------------------
/**
 * @brief シェーダーの取得
 *
 * @param  なし
 * @return Shader<Vertex>*：シェーダーのポインタ
 */
Shader<UIManager::UIVertexData>* UIManager::GetShader() const
{
	return m_shader.get();
}
