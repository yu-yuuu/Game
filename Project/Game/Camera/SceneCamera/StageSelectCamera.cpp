/**
 *
 * @file StageSelectCamera.cpp
 *
 * @brief ステージ選択シーンに使用するカメラクラスのソースファイル
 *
 * @author Kato Yuki
 *
 * @date 2024/5/26
 *
 */
#include "pch.h"
#include "StageSelectCamera.h"
#include "Game/Scene/StageSelectScene.h"

#include "Game/MyLibrary/CommonResource/GameResource.h"
#include "Game/MyLibrary/GameParameter/GameParameter.h"

#include "Game/Camera/CameraProjection.h"
#include "Game/Camera/State/CameraStateLerpSwitch.h"
#include "Game/Camera/State/CameraStateRotation.h"

using namespace DirectX;

//------------------------------------------------------------------
/**
 * @brief コンストラクタ
 *
 * @param stageSelectScene ：ステージセレクトシーンのポインタ
 * @param aspectRatio：画面比
 * @param stageSize  ：ステージの大きさ
 */
StageSelectCamera::StageSelectCamera(StageSelectScene* stageSelectScene, float aspectRatio, DirectX::SimpleMath::Vector3 stageSize)
	: StateCamera(aspectRatio)
	, m_stageSelectScene(stageSelectScene)
	, m_stateLerp(nullptr)
	, m_stateRotation(nullptr)
{
	// 各カメラ作成
	m_stateLerp     = std::make_unique<CameraStateLerpSwitch<StageSelectCamera>>(this);
	m_stateRotation = std::make_unique<CameraStateRotation>(this);

	// カメラ位置、注視点、射影行列設定	
	SetEyePosition(stageSize);
	SetTargetPosition(stageSize * 0.5f);// ステージの真ん中
	SetProjectionMatrix(CameraProjection::CreatePerspectiveProjection(aspectRatio));
}

//------------------------------------------------------------------
/**
 * @brief デストラクタ
 */
StageSelectCamera::~StageSelectCamera()
{
}

//------------------------------------------------------------------
/**
 * @brief 更新
 *
 * @param  なし
 * @return なし
 */
void StageSelectCamera::Update()
{
	// 基底クラスの更新処理
	StateCamera::Update();
}

//------------------------------------------------------------------
/**
 * @brief ステージ選択
 *
 * @param nextStageBasePosition：切り替え先ステージの基準位置
 * @param nextStageSize：切り替え先ステージのサイズ
 * @return なし
 */
void StageSelectCamera::StageSelectSetting(const DirectX::SimpleMath::Vector3& nextStageBasePosition, const DirectX::SimpleMath::Vector3& nextStageSize)
{
	// 移動開始位置取得
	SimpleMath::Vector3 startPosition = GetTargetPosition();
	//  切り替え先ステージのカメラ位置計算
	SimpleMath::Vector3 nextEye = nextStageSize;

	// 切り替えカメラ設定
	m_stateLerp->LerpSetting(GetStateRotation(), STAGE_SWITCH_SPEED);
	m_stateLerp->TargetSetting(startPosition, nextStageBasePosition);
	m_stateLerp->PositionSetting(GetEyePosition(), nextEye);
	SetNextCamera(GetStateLerp());
}

//------------------------------------------------------------------
/**
 * @brief 初期カメラ設定
 *
 * @param  なし
 * @return なし
 */
void StageSelectCamera::InitialCameraSetting()
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
 * @return CameraStateLerpSwitch<StageSelectScene>*：切替カメラのポインタ
 */
CameraStateLerpSwitch<StageSelectCamera>* StageSelectCamera::GetStateLerp()
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
CameraStateRotation* StageSelectCamera::GetStateRotation()
{
	return m_stateRotation.get();
}