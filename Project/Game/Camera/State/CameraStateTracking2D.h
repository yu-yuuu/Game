/**
 *
 * @file CameraStateTracking2D.h
 *
 * @brief 2D追跡カメラのヘッダーファイル
 *
 * @author Kato Yuki
 *
 * @date 2024/2/12
 *
 */
#pragma once

#include "Game/Camera/State/ICameraState.h"

class GameCamera;

class CameraStateTracking2D : public ICameraState
{
//----------------------------------------------
// 変数
//----------------------------------------------
private:

	// ゲームカメラ
	GameCamera* m_gameCamera;
	// オフセット位置
	DirectX::SimpleMath::Vector3 m_offsetPosition;
	// 見下ろし切替前の注視点
	DirectX::SimpleMath::Vector3 m_beforeTarget;


//----------------------------------------------
// 関数
//----------------------------------------------
public:

	// コンストラクタ
	CameraStateTracking2D(GameCamera* gameCamera);
	// デストラクタ
	~CameraStateTracking2D();
	// 初期化
	void Initialize() override;
	// 更新
	void Update() override;
	// 切替中フラグ
	bool IsOperation() override;

	// 次元切り替え設定
	void ChangeDimensionSetting();
	// 見渡しカメラへ切り替えて良いか確認
	bool CheckChangeOverLooking();
	// 見渡しカメラ切替設定
	void ChangeOverLookingSetting();

	// オフセット位置取得
	const DirectX::SimpleMath::Vector3& GetEyePosition() const;
	// オフセット位置設定
	void SetEyePosition(const DirectX::SimpleMath::Vector3& eyeOffsetPosition);
	// 見下ろし切替前の注視点取得
	const DirectX::SimpleMath::Vector3& GetBeforeTarget() const;
	// 初期設定
	void InitSetting(const DirectX::SimpleMath::Vector3& eyePosition);
};