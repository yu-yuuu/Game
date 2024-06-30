/**
 *
 * @file UIManager.h
 *
 * @brief UIの管理クラスのヘッダーファイル
 *
 * @author Kato Yuki
 *
 * @date 2024/1/14
 *
 */
#pragma once

#include <vector>
#include <initializer_list>
#include "PrimitiveBatch.h"
#include "VertexTypes.h"

class UI;
class SceneUI;
template<typename Vertex>
class Shader;

class UIManager
{
//----------------------------------------------
// 構造体
//----------------------------------------------
private:

	// UIに使用する定数バッファ
	struct UIConstantBuffer
	{
		DirectX::SimpleMath::Vector4 windowSize; // ウィンドウサイズ
	};

public:

	// UIの頂点データ
	struct UIVertexData
	{
		DirectX::SimpleMath::Vector4 position;
		DirectX::SimpleMath::Vector4 color;
		DirectX::SimpleMath::Vector4 tex;
		DirectX::SimpleMath::Vector4 reverse;

		// 頂点データの数
		static const int InputElementCount = 4;
		// 頂点データの情報
		static const D3D11_INPUT_ELEMENT_DESC InputElements[InputElementCount];
	};

//----------------------------------------------
// 変数
//----------------------------------------------
private:

	// UIリスト
	std::vector<UI*> m_uiList;
	// シーンUI
	SceneUI* m_sceneUI;
	// シェーダー
	std::unique_ptr<Shader<UIVertexData>> m_shader;
	// UIの定数バッファ
	UIConstantBuffer m_uiConstantBuffer;

//----------------------------------------------
// 関数
//----------------------------------------------
public:

	// コンストラクタ
	UIManager();
	// デストラクタ
	~UIManager();

	// 初期化
	void Initialize();
	// 更新
	void Update();
	// 描画
	void Render();

	// UIの追加
	void AddUI(UI* ui);
	// UIの追加(一括)
	void AddUI(const std::initializer_list<UI*>& list);
	void AddUI(const std::vector<UI*>& list);
	// 登録UIの削除
	void Delete(UI* deleteUI);
	// 登録UIの削除(一括)
	void Delete(const std::initializer_list<UI*>& list);
	void Delete(const std::vector<UI*>& list);
	// シーンUIの登録
	void SetSceneUI(SceneUI* sceneUI);
	// シーンUIの削除
	void DeleteSceneUI();
	// 登録UIの全削除
	void Clear();

	// シェーダーの取得
	Shader<UIVertexData>* GetShader() const;
};