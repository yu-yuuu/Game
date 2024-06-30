/**
 *
 * @file Fade.h
 *
 * @brief フェード処理を行うクラスのヘッダーファイル
 *
 * @author Kato Yuki
 *
 * @date 2023/9/12
 *
 */
#pragma once
#include "VertexTypes.h"

template<typename Vertex>
class Shader;

class Fade
{
//----------------------------------------------
// 構造体、列挙体
//----------------------------------------------
public:
	
	// フェードの状態
	enum class FadeState
	{
		FADE_IN,		// フェードイン
		FADE_IN_WAIT,	// フェードイン待ち
		FADE_OUT,		// フェードアウト
		STAY,			// 待機
	};

private:

	// フェードに使用する定数バッファ
	struct FadeConstantBuffer
	{
		DirectX::SimpleMath::Vector4 rate;// フェードの割合
	};

//----------------------------------------------
// 定数
//----------------------------------------------
private:

	// フェードにかかる時間
	const float FADE_TIMER = 1.0f;
	// 描画に使用する板ポリゴン
	const DirectX::VertexPosition VERTICES[4] =
	{
		DirectX::VertexPosition(DirectX::SimpleMath::Vector3(-1.0f,  1.0f, 0.0f)), // 左上
		DirectX::VertexPosition(DirectX::SimpleMath::Vector3(1.0f,  1.0f, 0.0f)),  // 右上
		DirectX::VertexPosition(DirectX::SimpleMath::Vector3(1.0f, -1.0f, 0.0f)),  // 右下
		DirectX::VertexPosition(DirectX::SimpleMath::Vector3(-1.0f, -1.0f, 0.0f))  // 左下
	};

//----------------------------------------------
// 変数
//----------------------------------------------
private:

	// フェード状態
	FadeState m_fadeState;
	// １フレーム前のフェード状態
	FadeState m_prevFadeState;
  	// 現在のフェード時間
  	// ( 0 ～ FADE_TIMER )
	float m_currentTime;
	// シェーダー
	std::unique_ptr<Shader<DirectX::VertexPosition>> m_shader;

//----------------------------------------------
// 関数
//----------------------------------------------
public:

	// コンストラクタ
	Fade();
	// デストラクタ
	~Fade();

	// 初期化
	void Initialize();
	// 更新
	void Update(const float& elapsedTime);
	// 描画
	void Render();

	// フェードイン開始
	void StartFadeIn();
	// フェードアウト開始
	void StartFadeOut();

	// フェード状態の確認
	bool CheckFadeState(FadeState state);
	// フェード状態かどうか確認
	bool IsFade();
	// フェードインが終了した瞬間か
	bool IsFadeInFinish();
};