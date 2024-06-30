/**
 *
 * @file TitleCamera.cpp
 *
 * @brief タイトルシーンで使用するカメラクラスのソースファイル
 *
 * @author Kato Yuki
 *
 * @date 2024/1/23
 *
 */
#include "pch.h"
#include "TitleCamera.h"
#include "Game/Scene/TitleScene.h"

#include "Game/MyLibrary/CommonResource/GameResource.h"
#include "Game/MyLibrary/GameParameter/GameParameter.h"

#include "Game/Camera/CameraProjection.h"
#include "Game/Camera/State/CameraStateLerpSwitch.h"
#include "Game/Camera/State/CameraStateRotation.h"
#include "Game/Camera/State/CameraStateFixed.h"


using namespace DirectX;

//------------------------------------------------------------------
/**
 * @brief コンストラクタ
 *
 * @param titleScene ：タイトルシーンのポインタ
 * @param aspectRatio：画面比
 * @param stageSize  ：ステージの大きさ
 */
TitleCamera::TitleCamera(TitleScene* titleScene, float aspectRatio, DirectX::SimpleMath::Vector3 stageSize)
	: StateCamera(aspectRatio)
	, m_titleScene(titleScene)
	, m_stateLerp(nullptr)
	, m_stateRotation(nullptr)
	, m_stateFixed(nullptr)
{
	// 各カメラ作成
	m_stateLerp     = std::make_unique<CameraStateLerpSwitch<TitleCamera>>(this);
	m_stateRotation = std::make_unique<CameraStateRotation>(this);
	m_stateFixed    = std::make_unique<CameraStateFixed>(this);

	// カメラ位置、注視点、射影行列設定	
	SetEyePosition(stageSize);
	SetTargetPosition(stageSize * 0.5f);// ステージの真ん中
	SetProjectionMatrix(CameraProjection::CreatePerspectiveProjection(aspectRatio));
}

//------------------------------------------------------------------
/**
 * @brief デストラクタ
 */
TitleCamera::~TitleCamera()
{
}

//------------------------------------------------------------------
/**
 * @brief 更新
 *
 * @param  なし
 * @return なし
 */
void TitleCamera::Update()
{
	// 基底クラスの更新処理
	StateCamera::Update();
}

//------------------------------------------------------------------
/**
 * @brief 次元の切り替え
 *
 * @param  なし
 * @return なし
 */
void TitleCamera::ChangeDimension()
{
	// カメラ位置取得
	SimpleMath::Vector3 eye = GetEyePosition();

	// 切り替えカメラ設定
	m_stateLerp->LerpSetting(GetStateFixed(), KT::GameParam::LERP_TIME_DIMENSION);
	m_stateLerp->PositionSetting(eye, SimpleMath::Vector3(0.0f, 0.0f, eye.z));
	m_stateLerp->ProjectionSetting(GetProjectionMatrix(), CameraProjection::CreateOrthographicProjection(GetAspectRatio(), CameraProjection::SIDE_RECT));
	m_stateLerp->RotationSetting(GetRotation(), SimpleMath::Quaternion::Identity);

	// 次のカメラに設定
	SetNextCamera(m_stateLerp.get());
}

//------------------------------------------------------------------
/**
 * @brief 初期カメラ設定
 *
 * @param  なし
 * @return なし
 */
void TitleCamera::InitialCameraSetting()
{
	// 回転カメラの初期設定
	m_stateRotation->RotationSetting(CAMERA_ROTATION_SPEED, SimpleMath::Vector3::UnitY);
	// 回転カメラを初期カメラに設定
	SetInitialCamera(GetStateRotation());
}

//------------------------------------------------------------------
/**
 * @brief 切替カメラ取得
 *
 * @param  なし
 * @return CameraStateLerpSwitch<TitleCamera>*：切替カメラのポインタ
 */
CameraStateLerpSwitch<TitleCamera>* TitleCamera::GetStateLerp()
{
	return m_stateLerp.get();
}

//------------------------------------------------------------------
/**
 * @brief 回転カメラ取得
 *
 * @param  なし
 * @return CameraStateRotation*：回転カメラのポインタ
 */
CameraStateRotation* TitleCamera::GetStateRotation()
{
	return m_stateRotation.get();
}

//------------------------------------------------------------------
/**
 * @brief 固定カメラ取得
 *
 * @param  なし
 * @return CameraStateFixed*：固定カメラのポインタ
 */
CameraStateFixed* TitleCamera::GetStateFixed()
{
	return m_stateFixed.get();
}