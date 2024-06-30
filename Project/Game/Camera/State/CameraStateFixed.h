/**
 *
 * @file CameraStateFixed.h
 *
 * @brief 固定位置カメラのヘッダーファイル
 *
 * @author Kato Yuki
 *
 * @date 2024/3/2
 *
 */
#pragma once

#include "Game/Camera/State/ICameraState.h"

class StateCamera;

class CameraStateFixed : public ICameraState
{
//----------------------------------------------
// 変数
//----------------------------------------------
private:

	// カメラ
	StateCamera* m_stateCamera;

//----------------------------------------------
// 関数
//----------------------------------------------
public:

	// コンストラクタ
	CameraStateFixed(StateCamera* stateCamera);
	// デストラクタ
	~CameraStateFixed();
	
	// 初期化
	void Initialize() override;
	// 更新
	void Update() override;
	// 操作中フラグ
	bool IsOperation() override;

};