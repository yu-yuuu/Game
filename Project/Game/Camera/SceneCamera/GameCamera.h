/**
 *
 * @file GameCamera.h
 *
 * @brief ゲームに使用するカメラのヘッダーファイル
 *
 * @author Kato Yuki
 *
 * @date 2024/2/11
 *
 */
#pragma once

#include "Game/Camera/SceneCamera/StateCamera .h"
#include "Game/MyLibrary/GameParameter/GameParameter.h"

class PlayScene;
class CameraStateTracking3D;
class CameraStateTracking2D;
template<typename ParentCamera>
class CameraStateLerpSwitch;
class CameraStateOverLooking3D;
class CameraStateOverLooking2D;

class GameCamera : public StateCamera
{
//----------------------------------------------
// 定数
//----------------------------------------------
public:

	// 回転角度
	static const float ROTATION_ANGLE;

//----------------------------------------------
// 変数
//----------------------------------------------
private:

	// プレイシーン
	PlayScene* m_playScene;

	// 次元
	KT::GameParam::Dimension m_dimension;
	// 視点タイプ
	KT::GameParam::SightType m_sightType;
	// カメラの状態
	KT::GameParam::CameraState m_cameraState;

	// カメラの種類
	std::unique_ptr<CameraStateTracking3D> m_stateTrack3D;
	std::unique_ptr<CameraStateTracking2D> m_stateTrack2D;
	std::unique_ptr<CameraStateLerpSwitch<GameCamera>> m_stateLerp;
	std::unique_ptr<CameraStateOverLooking3D> m_stateOverLooking3D;
	std::unique_ptr<CameraStateOverLooking2D> m_stateOverLooking2D;

	// プレイヤーの位置
	DirectX::SimpleMath::Vector3 m_playerPosition;

//----------------------------------------------
// 関数
//----------------------------------------------
public:

	// コンストラクタ
	GameCamera(PlayScene* playScene, float aspectRatio, DirectX::SimpleMath::Vector3 stageSize);
	// デストラクタ
	~GameCamera();

	// 更新
	void Update() override;
	// 次元切り替え設定
	void ChangeDimensionSetting();
	// 初期カメラ設定
	void InitialCameraSetting(
		const float& lerpTimer, 
		const DirectX::SimpleMath::Vector3& beforeEye,
		const DirectX::SimpleMath::Vector3& afterEye,
		const DirectX::SimpleMath::Vector3& beforeTarget,
		const DirectX::SimpleMath::Vector3& afterTarget
		);

	// 現在の次元確認
	bool CheckDimension(KT::GameParam::Dimension dimension);
	// 現在の次元取得
	KT::GameParam::Dimension GetDimension();
	// 現在の次元設定
	void SetDimension(KT::GameParam::Dimension dimension);
	// 現在の視点タイプ確認
	bool CheckSightType(KT::GameParam::SightType type);
	// 現在の視点タイプ取得
	KT::GameParam::SightType GetSightType();
	// 現在の視点タイプ設定
	void SetSightType(KT::GameParam::SightType type);
	// カメラの状態取得
	KT::GameParam::CameraState GetCameraState();
	// カメラの状態設定
	void SetCameraState(KT::GameParam::CameraState state);
	// カメラの状態確認
	bool CheckCameraState(KT::GameParam::CameraState state);
	// プレイシーンの取得
	PlayScene* GetScene() const;
	// プレイヤーの位置取得
	const DirectX::SimpleMath::Vector3& GetPlayerPosition() const;
	// プレイヤーの位置設定
	void SetPlayerPosition(const DirectX::SimpleMath::Vector3& playerPosition);
	// 状態カメラ取得
	CameraStateTracking3D* GetStateTrack3D();
	CameraStateTracking2D* GetStateTrack2D();
	CameraStateLerpSwitch<GameCamera>* GetStateLerp();
	CameraStateOverLooking3D* GetStateOverLooking3D();
	CameraStateOverLooking2D* GetStateOverLooking2D();
};