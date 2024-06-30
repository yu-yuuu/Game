/**
 *
 * @file CameraStateTracking3D.h
 *
 * @brief 3D追跡カメラのヘッダーファイル
 *
 * @author Kato Yuki
 *
 * @date 2024/2/11
 *
 */
#pragma once

#include "Game/Camera/State/ICameraState.h"

class GameCamera;

class CameraStateTracking3D : public ICameraState
{
//----------------------------------------------
// 変数
//----------------------------------------------
private:

	// ゲームカメラ
	GameCamera* m_gameCamera;
	// 見下ろし切替前の回転
	DirectX::SimpleMath::Quaternion m_beforeRotation;

//----------------------------------------------
// 関数
//----------------------------------------------
public:

	// コンストラクタ
	CameraStateTracking3D(GameCamera* gameCamera);
	// デストラクタ
	~CameraStateTracking3D();
	// 初期化
	void Initialize() override;
	// 更新
	void Update() override;
	// 操作中フラグ
	bool IsOperation() override;
	
	// 次元切り替え設定
	void ChangeDimensionSetting();
	// カメラを回転させて良いか確認
	bool CheckRotation();
	// カメラ回転設定
	void RotationSetting();
	// 見渡しカメラへ切り替えて良いか確認
	bool CheckChangeOverLooking();
	// 見渡しカメラ切替設定
	void ChangeOverLookingSetting();
	// カメラ位置取得
	const DirectX::SimpleMath::Vector3& GetEyePosition() const;
	// 見下ろし切替前の回転取得
	const DirectX::SimpleMath::Quaternion& GetBeforeRotation() const;
};