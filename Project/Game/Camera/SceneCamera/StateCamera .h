/**
 *
 * @file StateCamera.h
 *
 * @brief 状態カメラを使用するカメラクラスのヘッダーファイル
 *
 * @author Kato Yuki
 *
 * @date 2024/1/18
 *
 */
#pragma once

#include "Game/Camera/Camera.h"

class ICameraState;

class StateCamera : public Camera
{
//----------------------------------------------
// 変数
//----------------------------------------------
private:

	// 現在の状態
	ICameraState* m_currentCamera;
	// 次の状態
	ICameraState* m_nextCamera;

//----------------------------------------------
// 関数
//----------------------------------------------
public:

	// コンストラクタ
	StateCamera(float aspectRatio);
	// デストラクタ
	virtual ~StateCamera();
	// 更新
	virtual void Update();
	// 状態切り替え
	void ChangeState();
	// 状態切り替え可能状態か確認
	bool IsChange();

	// 現在の状態取得
	ICameraState* GetCurrentCameraState();
	// 初期状態設定
	void SetInitialCamera(ICameraState* initialCamera);
	// 次のカメラ設定
	void SetNextCamera(ICameraState* nextCamera);

	// 切替中フラグ
	bool IsOperation();

};