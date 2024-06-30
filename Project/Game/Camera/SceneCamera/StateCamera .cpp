/**
 *
 * @file StateCamera.cpp
 *
 * @brief 状態カメラを使用するカメラクラスのソースファイル
 *
 * @author Kato Yuki
 *
 * @date 2024/1/18
 *
 */
#include "pch.h"
#include "StateCamera .h"
#include "Game/Camera/State/ICameraState.h"

//------------------------------------------------------------------
/**
 * @brief コンストラクタ
 *
 * @param aspectRatio：画面比
 */
StateCamera::StateCamera(float aspectRatio)
	: Camera(aspectRatio)
	, m_currentCamera(nullptr)
	, m_nextCamera(nullptr)
{
}

//------------------------------------------------------------------
/**
 * @brief デストラクタ
 */
StateCamera ::~StateCamera()
{
}

//------------------------------------------------------------------
/**
 * @brief 更新
 *
 * @param  なし
 * @return なし
 */
void StateCamera::Update()
{
	// カメラ切り替え
	if (IsChange()) ChangeState();
	// 現在のカメラ更新
	m_currentCamera->Update();
	// 基底クラスの更新
	Camera::Update();
}

//------------------------------------------------------------------
/**
 * @brief 状態切り替え
 *
 * @param  なし
 * @return なし
 */
void StateCamera ::ChangeState()
{
	// 現在の状態を更新
	m_currentCamera = m_nextCamera;
	// 初期化
	m_currentCamera->Initialize();
	// 次の状態をリセット
	m_nextCamera = nullptr;
}

//------------------------------------------------------------------
/**
 * @brief 状態切り替え可能状態か確認
 *
 * @param  なし
 * @return true ：切替可
 * @return false：切替不可
 */
bool StateCamera::IsChange()
{
	// 次のカメラがセットされていたら切り替え可能
	return m_nextCamera != nullptr;
}

//------------------------------------------------------------------
/**
 * @brief 現在の状態取得
 *
 * @param なし
 * @return ICameraState*：現在のカメラ状態
 */
ICameraState* StateCamera::GetCurrentCameraState()
{
	return m_currentCamera;
}

//------------------------------------------------------------------
/**
 * @brief 初期状態設定
 *
 * @param  initialCamera：最初のカメラ状態
 * @return なし
 */
void StateCamera::SetInitialCamera(ICameraState* initialCamera)
{
	// 次のカメラに設定
	SetNextCamera(initialCamera);
	// 状態切り替え
	ChangeState();
}

//------------------------------------------------------------------
/**
 * @brief 次のカメラ設定
 *
 * @param nextCamera：次のカメラ
 * @return なし
 */
void StateCamera::SetNextCamera(ICameraState* nextCamera)
{
	m_nextCamera = nextCamera;
}

//------------------------------------------------------------------
/**
 * @brief 切替中フラグ
 *
 * @param なし
 * @return true ：操作不可
 * @return false：操作可
 */
bool StateCamera::IsOperation()
{
	return m_currentCamera->IsOperation();
}
