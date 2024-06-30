/**
 *
 * @file Fade.cpp
 *
 * @brief フェード処理を行うクラスのフォースファイル
 *
 * @author Kato Yuki
 *
 * @date 2023/9/12
 *
 */
#include "pch.h"
#include "Fade.h"
#include "Game/MyLibrary/CommonResource/GameResource.h"
#include "Game/MyLibrary/Shader/Shader.h"

using namespace DirectX;

//------------------------------------------------------------------
/**
 * @brief コンストラクタ
 *
 * @param なし
 */
Fade::Fade()
	: m_fadeState(FadeState::STAY)
	, m_prevFadeState(FadeState::STAY)
	, m_currentTime(0.0f)
	, m_shader(nullptr)
{
}

//------------------------------------------------------------------
/**
 * @brief デストラクタ
 */
Fade::~Fade()
{
	m_shader.reset();
}

//------------------------------------------------------------------
 /**
 * @brief 初期化
 *
 * @param  なし
 * @return なし
 */
void Fade::Initialize()
{
	// シェーダーの作成
	m_shader = std::make_unique<Shader<VertexPosition>>();
	m_shader->CreateData(KT::Shader::FADE);
	m_shader->CreateConstantBuffer<FadeConstantBuffer>();
}

//------------------------------------------------------------------
 /**
 * @brief 更新
 *
 * @param elapsedTime：１フレームにかかる秒数
 * @return なし
 */
void Fade::Update(const float& elapsedTime)
{
	// 現在のフェード状態を保存
	m_prevFadeState = m_fadeState;
	// フェード状態でなければ終了
	if (m_fadeState == FadeState::STAY) return;

	// フェードイン状態
	if (m_fadeState == FadeState::FADE_IN)
	{
		// フェード進行
		m_currentTime -= elapsedTime;	
		// フェードインが終了しているか確認
		if (m_currentTime > 0.0f) return;

		// タイマーの値がピッタリになるように調整
		m_currentTime = 0.0f;
		// 待機状態へ
		m_fadeState = FadeState::STAY;
	}
	// フェードアウト状態
	else
	{
		// フェード進行
		m_currentTime += elapsedTime;
		// フェードアウトが終了しているか確認
		if (m_currentTime <= FADE_TIMER) return;

		// タイマーの値がピッタリになるように調整
		m_currentTime = FADE_TIMER;
		// フェードイン待ち状態へ
		m_fadeState = FadeState::FADE_IN_WAIT;
	}
}

//------------------------------------------------------------------
 /**
 * @brief 描画
 *
 * @param  なし
 * @return なし
 */
void Fade::Render()
{
	// 定数バッファ更新
	FadeConstantBuffer cbuf;
	cbuf.rate = SimpleMath::Vector4(m_currentTime / FADE_TIMER, 0.0f, 0.0f, 0.0f);
	m_shader->UpdateConstantBuffer(cbuf);
	// 描画
	m_shader->RenderQuad(VERTICES[0], VERTICES[1], VERTICES[2], VERTICES[3]);
}

//------------------------------------------------------------------
 /**
 * @brief フェードイン開始
 *
 * @param  なし
 * @return なし
 */
void Fade::StartFadeIn()
{
	// フェードイン待ち以外なら処理を行わない
	if (!CheckFadeState(FadeState::FADE_IN_WAIT)) return;

	// フェードイン状態へ移行
	m_fadeState = FadeState::FADE_IN;
	m_currentTime = FADE_TIMER;
}

//------------------------------------------------------------------
 /**
 * @brief フェードアウト開始
 *
 * @param  なし
 * @return なし
 */
void Fade::StartFadeOut()
{
	// 待機中以外なら処理を行わない
	if (!CheckFadeState(FadeState::STAY)) return;

	// フェードアウト状態へ移行
	m_fadeState = FadeState::FADE_OUT;
	m_currentTime = 0.0f;
}

//------------------------------------------------------------------
 /**
 * @brief フェード状態の確認
 *
 * @param  state：確認したいフェード状態
 * @return true ：一致
 * @return false：不一致
 */
bool Fade::CheckFadeState(FadeState state)
{
	return m_fadeState == state;
}

//------------------------------------------------------------------
/**
 * @brief フェード状態かどうか確認
 *
 * @param  なし
 * @return true ：フェード中
 * @return false：フェードしていない
 */
bool Fade::IsFade()
{
	return m_fadeState != FadeState::STAY;
}

//------------------------------------------------------------------
/**
 * @brief フェードインが終了した瞬間か
 *
 * @param  なし
 * @return true ：終了した瞬間
 * @return false：瞬間でない
 */
bool Fade::IsFadeInFinish()
{
	return m_fadeState == FadeState::STAY && m_prevFadeState == FadeState::FADE_IN;
}