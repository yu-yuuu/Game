/**
 *
 * @file ICameraState.h
 *
 * @brief 状態カメラのインターフェースクラス
 *
 * @author Kato Yuki
 *
 * @date 2024/2/11
 *
 */
#pragma once

class ICameraState
{
//----------------------------------------------
// 関数
//----------------------------------------------
public:

	// デストラクタ
	virtual ~ICameraState() = default;
	// 初期化
	virtual void Initialize() = 0;
	// 更新
	virtual void Update() = 0;
	// 操作中フラグ
	virtual bool IsOperation() = 0;
};