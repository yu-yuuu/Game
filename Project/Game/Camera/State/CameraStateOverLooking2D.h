/**
 *
 * @file CameraStateOverLooking2D.h
 *
 * @brief 2D見渡しカメラのヘッダーファイル
 *
 * @author Kato Yuki
 *
 * @date 2024/2/28
 *
 */
#pragma once

#include "Game/Camera/State/ICameraState.h"

class GameCamera;

class CameraStateOverLooking2D : public ICameraState
{
//----------------------------------------------
// 定数
//----------------------------------------------
private:

	// 移動速度
	const float MOVE_SPEED = 0.1f;

//----------------------------------------------
// 変数
//----------------------------------------------
private:

	// ゲームカメラ
	GameCamera* m_gameCamera;
	// 移動制限位置
	DirectX::SimpleMath::Vector3 m_limitPosition;

//----------------------------------------------
// 関数
//----------------------------------------------
public:

	// コンストラクタ
	CameraStateOverLooking2D(GameCamera* gameCamera);
	// デストラクタ
	~CameraStateOverLooking2D();

	// 初期化
	void Initialize() override;
	// 更新
	void Update() override;
	// 操作中フラグ
	bool IsOperation() override;

	// カメラ前後移動
	void Move();
	// 追跡カメラへ切り替え設定
	void ChangeTrackSetting();
	
	// 移動制限位置設定
	void SetLimitPosition(const DirectX::SimpleMath::Vector3& limitPosition);
	// 初期設定
	void InitSetting(const DirectX::SimpleMath::Vector3& limit);
};