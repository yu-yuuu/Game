/**
 *
 * @file CameraStateOverLooking3D.h
 *
 * @brief 3D見渡しカメラのヘッダーファイル
 *
 * @author Kato Yuki
 *
 * @date 2024/2/26
 *
 */
#pragma once

#include "Game/Camera/State/ICameraState.h"

class GameCamera;

class CameraStateOverLooking3D : public ICameraState
{
//----------------------------------------------
// 定数
//----------------------------------------------
private:

	// 移動速度
	const float MOVE_SPEED = 0.02f;

	// 縦回転角度制限値
	const float VERTICAL_ANGLE_LIMIT = 45.0f * DirectX::XM_PI / 180.0f;

	// カメラ位置の割合制限値
	const DirectX::SimpleMath::Vector2 POSITION_RATIO_LIMIT = { 0.1f, 1.0f };

//----------------------------------------------
// 変数
//----------------------------------------------
private:

	// ゲームカメラ
	GameCamera* m_gameCamera;
	// 前後移動の基準位置
	DirectX::SimpleMath::Vector3 m_basePosition;
	// カメラの注視点
	DirectX::SimpleMath::Vector3 m_targetPosition;
	// 現在の位置が基準のどこら辺にいるのかの割合
	float m_positionRatio;
	// カメラの横回転角度
	float m_horizontalAngle;
	// カメラの縦回転角度
	float m_verticalAngle;

//----------------------------------------------
// 関数
//----------------------------------------------
public:

	// コンストラクタ
	CameraStateOverLooking3D(GameCamera* gameCamera);
	// デストラクタ
	~CameraStateOverLooking3D();
	// 初期化
	void Initialize() override;
	// 更新
	void Update() override;
	// 操作中フラグ
	bool IsOperation() override;

	// カメラ回転
	void Rotation();
	// カメラ前後移動
	void Move();
	// 追跡カメラへ切り替え
	void ChangeTrackSetting();
	
	// 初期設定
	void InitSetting(const DirectX::SimpleMath::Vector3& target, const DirectX::SimpleMath::Vector3& basePosition);

	// 注視点取得
	const DirectX::SimpleMath::Vector3& GetTargetPosition() const;
	// カメラ基準位置取得
	const DirectX::SimpleMath::Vector3& GetBasePosition() const;
	// 基準位置設定
	void SetBasePosition(const DirectX::SimpleMath::Vector3& basePosition);

};