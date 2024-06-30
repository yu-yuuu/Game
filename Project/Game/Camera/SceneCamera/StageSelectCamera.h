/**
 *
 * @file StageSelectCamera.h
 *
 * @brief ステージ選択シーンに使用するカメラクラスのヘッダーファイル
 *
 * @author Kato Yuki
 *
 * @date 2024/5/26
 *
 */
#pragma once
#include "Game/Camera/SceneCamera/StateCamera .h"

class StageSelectScene;
template<typename ParentCamera>
class CameraStateLerpSwitch;
class CameraStateRotation;

class StageSelectCamera : public StateCamera
{
//----------------------------------------------
// 定数
//----------------------------------------------
private:

	// カメラの回転速度
	const float CAMERA_ROTATION_SPEED = 0.01f;

	// ステージを切り替える際のスピード
	const float STAGE_SWITCH_SPEED = 0.5f;

//----------------------------------------------
// 変数
//----------------------------------------------
private:

	// ステージセレクトシーン
	StageSelectScene* m_stageSelectScene;

	// 使用するカメラ
	std::unique_ptr<CameraStateLerpSwitch<StageSelectCamera>> m_stateLerp; // 切替カメラ
	std::unique_ptr<CameraStateRotation> m_stateRotation;            // 回転カメラ


//----------------------------------------------
// 関数
//----------------------------------------------
public:

	// コンストラクタ
	StageSelectCamera(StageSelectScene* stageSelectScene, float aspectRatio, DirectX::SimpleMath::Vector3 stageSize);
	// デストラクタ
	~StageSelectCamera();

	// 更新
	void Update() override;

	// ステージ選択
	void StageSelectSetting(const DirectX::SimpleMath::Vector3& nextStageBasePosition, const DirectX::SimpleMath::Vector3& nextStageSize);

	// 初期カメラ設定
	void InitialCameraSetting();
	// 状態カメラ取得
	CameraStateLerpSwitch<StageSelectCamera>* GetStateLerp(); // 切り替えカメラ
	CameraStateRotation* GetStateRotation();            // 回転カメラ

	

};