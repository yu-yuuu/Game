/**
 *
 * @file CameraStateRotation.h
 *
 * @brief 注視点固定で回転をするカメラのヘッダーファイル
 *
 * @author Kato Yuki
 *
 * @date 2024/2/12
 *
 */
#pragma once

#include "Game/Camera/State/ICameraState.h"

class StateCamera;

class CameraStateRotation : public ICameraState
{
//----------------------------------------------
// 変数
//----------------------------------------------
private:

	// ステートカメラ
	StateCamera* m_camera;
	// 回転速度
	float m_rotationSpeed;
	// 回転軸
	DirectX::SimpleMath::Vector3 m_axisOfRotation;

//----------------------------------------------
// 関数
//----------------------------------------------
public:

	// コンストラクタ
	CameraStateRotation(StateCamera* stateCamera);
	// デストラクタ
	~CameraStateRotation();
	// 初期化
	void Initialize() override;
	// 更新
	void Update() override;
	// 操作中フラグ
	bool IsOperation() override;
	// 回転設定
	void RotationSetting(const float& rotationSpeed, const DirectX::SimpleMath::Vector3& axisOfRotation);
};
