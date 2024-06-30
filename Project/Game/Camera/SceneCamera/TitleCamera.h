/**
 *
 * @file TitleCamera.h
 *
 * @brief タイトルシーンで使用するカメラクラスのヘッダーファイル
 *
 * @author Kato Yuki
 *
 * @date 2024/1/23
 *
 */
#pragma once

#include "Game/Camera/SceneCamera/StateCamera .h"

class TitleScene;
template<typename ParentCamera>
class CameraStateLerpSwitch;
class CameraStateRotation;
class CameraStateFixed;

class TitleCamera : public StateCamera
{
//----------------------------------------------
// 定数
//----------------------------------------------
private:

	// カメラの回転速度
	const float CAMERA_ROTATION_SPEED = 0.01f;

//----------------------------------------------
// 変数
//----------------------------------------------
private:

	// タイトルシーン
	TitleScene* m_titleScene;
	
	// 使用するカメラ
	std::unique_ptr<CameraStateLerpSwitch<TitleCamera>> m_stateLerp; // 切替カメラ
	std::unique_ptr<CameraStateRotation> m_stateRotation;            // 回転カメラ
	std::unique_ptr<CameraStateFixed> m_stateFixed;                  // 固定カメラ

//----------------------------------------------
// 関数
//----------------------------------------------
public:

	// コンストラクタ
	TitleCamera(TitleScene* titleScene, float aspectRatio, DirectX::SimpleMath::Vector3 stageSize);
	// デストラクタ
	~TitleCamera();
	
	// 更新
	void Update() override;
	// 次元切替
	void ChangeDimension();

	// 初期カメラ設定
	void InitialCameraSetting();
	// 状態カメラ取得
	CameraStateLerpSwitch<TitleCamera>* GetStateLerp(); // 切り替えカメラ
	CameraStateRotation* GetStateRotation();            // 回転カメラ
	CameraStateFixed* GetStateFixed();                  // 固定カメラ
};