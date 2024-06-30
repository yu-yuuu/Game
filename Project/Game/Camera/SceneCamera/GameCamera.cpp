/**
 *
 * @file GameCamera.cpp
 *
 * @brief ゲームに使用するカメラのソースファイル
 *
 * @author Kato Yuki
 *
 * @date 2024/2/11
 *
 */
#include "pch.h"
#include "GameCamera.h"

#include "Game/MyLibrary/CommonResource/GameResource.h"
#include "Game/Scene/PlayScene.h"
#include "Game/Camera/CameraProjection.h"
#include "Game/Camera/State/CameraStateTracking2D.h"
#include "Game/Camera/State/CameraStateTracking3D.h"
#include "Game/Camera/State/CameraStateLerpSwitch.h"
#include "Game/Camera/State/CameraStateOverLooking3D.h"
#include "Game/Camera/State/CameraStateOverLooking2D.h"

using namespace DirectX;

//----------------------------------------------
// 定数宣言
//----------------------------------------------

// カメラの回転角度
const float GameCamera::ROTATION_ANGLE = 90.0f;

//------------------------------------------------------------------
/**
 * @brief コンストラクタ
 *
 * @param playScene  ：プレイシーンへのポインタ
 * @param aspectRatio：画面比
 * @param stageSize  ：ステージサイズ
 */
GameCamera::GameCamera(PlayScene* playScene, float aspectRatio, DirectX::SimpleMath::Vector3 stageSize)
	: StateCamera(aspectRatio)
	, m_playScene(playScene)
	, m_dimension(KT::GameParam::Dimension::_3D)
	, m_sightType(KT::GameParam::SightType::SIDE)
	, m_cameraState(KT::GameParam::CameraState::NONE)
	, m_playerPosition()
{
	// 各カメラ作成
	m_stateTrack3D       = std::make_unique<CameraStateTracking3D>(this);
	m_stateTrack2D       = std::make_unique<CameraStateTracking2D>(this);
	m_stateLerp          = std::make_unique<CameraStateLerpSwitch<GameCamera>>(this);
	m_stateOverLooking3D = std::make_unique<CameraStateOverLooking3D>(this);
	m_stateOverLooking2D = std::make_unique<CameraStateOverLooking2D>(this);	

	// 位置設定用
	SimpleMath::Vector3 pos = stageSize * 2.0f;

	// 初期設定
	m_stateTrack2D->InitSetting(SimpleMath::Vector3(0.0f, 0.0f, pos.z));
	m_stateOverLooking3D->InitSetting(stageSize * 0.5f, SimpleMath::Vector3(0.0f, stageSize.y, stageSize.z));
	m_stateOverLooking2D->InitSetting(stageSize);
	
	// 射影行列設定
	SetProjectionMatrix(CameraProjection::CreatePerspectiveProjection(GetAspectRatio()));
}

//------------------------------------------------------------------
/**
 * @brief コンストラクタ
 */
GameCamera::~GameCamera()
{

}

//------------------------------------------------------------------
/**
 * @brief 更新
 *
 * @param  なし
 * @return なし
 */
void GameCamera::Update()
{
	// 現在のカメラ更新、切り替え
	StateCamera::Update();

	// 次のカメラが設定されていたら処理を終了
	if (IsChange()) return;

	// カメラの状態切り替え
	switch (m_cameraState)
	{
	case KT::GameParam::CameraState::NONE:
		if (IsOperation()) m_cameraState = KT::GameParam::CameraState::OPERATION;
		break;
	case KT::GameParam::CameraState::OPERATION:
		if (!IsOperation()) m_cameraState = KT::GameParam::CameraState::OPERATION_COMPLETE;
		break;
	case KT::GameParam::CameraState::OPERATION_COMPLETE:
		m_cameraState = KT::GameParam::CameraState::NONE;
		break;
	default:
		break;
	}
}

//------------------------------------------------------------------
/**
 * @brief 次元切り替え設定
 *
 * @param  なし
 * @return なし
 */
void GameCamera::ChangeDimensionSetting()
{
	// 現在の次元を確認
	if (CheckDimension(KT::GameParam::Dimension::_2D))
	{
		GetStateTrack2D()->ChangeDimensionSetting();
	}
	else
	{
		GetStateTrack3D()->ChangeDimensionSetting();
	}
	m_cameraState = KT::GameParam::CameraState::OPERATION;
}

//------------------------------------------------------------------
/**
 * @brief 初期カメラ設定
 *
 * @param  lerpTimer   ：補完に掛ける時間
 * @param  beforeEye   ：切替前の位置
 * @param  afterEye    ：切替後の位置
 * @param  beforeTarget：切替前の注視点
 * @param  afterTarget ：切替後の注視点
 * @return なし
 */
void GameCamera::InitialCameraSetting(const float& lerpTimer, const DirectX::SimpleMath::Vector3& beforeEye, const DirectX::SimpleMath::Vector3& afterEye, const DirectX::SimpleMath::Vector3& beforeTarget, const DirectX::SimpleMath::Vector3& afterTarget)
{
	// 切り替えカメラの設定
	m_stateLerp->LerpSetting(GetStateTrack3D(),lerpTimer );
	m_stateLerp->PositionSetting(beforeEye, afterEye);
	m_stateLerp->TargetSetting(beforeTarget, afterTarget);
	// 次のカメラに設定
	SetInitialCamera(GetStateLerp());
}

//------------------------------------------------------------------
/**
 * @brief 現在の次元確認
 *
 * @param  dimension：確認する次元
 * @return true     ：一致
 * @return false    ：不一致
 */
bool GameCamera::CheckDimension(KT::GameParam::Dimension dimension)
{
	return m_dimension == dimension;
}

//------------------------------------------------------------------
/**
 * @brief 現在の次元取得
 *
 * @param なし
 * @return Dimension：現在の次元
 */
KT::GameParam::Dimension GameCamera::GetDimension()
{
	return m_dimension;
}

//------------------------------------------------------------------
/**
 * @brief 現在の次元設定
 *
 * @param dimension：設定する次元
 * @return なし
 */
void GameCamera::SetDimension(KT::GameParam::Dimension dimension)
{
	m_dimension = dimension;
}

//------------------------------------------------------------------
/**
 * @brief 現在の視点タイプ確認
 *
 * @param  type  ：確認する視点タイプ
 * @return true  ：一致
 * @return false ：不一致
 */bool GameCamera::CheckSightType(KT::GameParam::SightType type)
{
	return m_sightType == type;
}

//------------------------------------------------------------------
/**
 * @brief 現在の視点タイプ取得
 *
 * @param なし
 * @return SightType：現在の視点タイプ
 */
KT::GameParam::SightType GameCamera::GetSightType()
{
	return m_sightType;
}

//------------------------------------------------------------------
/**
 * @brief 現在の視点タイプ設定
 *
 * @param type：設定する視点タイプ
 * @return なし
 */
void GameCamera::SetSightType(KT::GameParam::SightType type)
{
	m_sightType = type;
}

//------------------------------------------------------------------
/**
 * @brief カメラの状態取得
 *
 * @param  なし
 * @return CameraState：現在のカメラの動作状態
 */
KT::GameParam::CameraState GameCamera::GetCameraState()
{
	return m_cameraState;
}

//------------------------------------------------------------------
/**
 * @brief カメラの状態設定
 *
 * @param  state：設定するカメラ状態
 * @return なし
 */
void GameCamera::SetCameraState(KT::GameParam::CameraState state)
{
	m_cameraState = state;
}

//------------------------------------------------------------------
/**
 * @brief カメラの状態確認
 *
 * @param  state：確認するカメラ状態
 * @return true ：一致
 * @return false：不一致
 */
bool GameCamera::CheckCameraState(KT::GameParam::CameraState state)
{
	return m_cameraState == state;
}

//------------------------------------------------------------------
/**
 * @brief プレイシーンの取得
 *
 * @param  なし
 * @return PlayScene：プレイシーンのポインタ
 */
PlayScene* GameCamera::GetScene() const
{
	return m_playScene;
}

//------------------------------------------------------------------
/**
 * @brief プレイヤーの位置取得
 *
 * @param  なし
 * @return Vector3：プレイヤーの位置
 */
const DirectX::SimpleMath::Vector3& GameCamera::GetPlayerPosition() const
{
	return m_playerPosition;
}

//------------------------------------------------------------------
/**
 * @brief プレイヤーの位置設定
 *
 * @param  playerPosition：設定するプレイヤーの位置
 * @return なし
 */
void GameCamera::SetPlayerPosition(const DirectX::SimpleMath::Vector3& playerPosition)
{
	m_playerPosition = playerPosition;
}

//------------------------------------------------------------------
/**
 * @brief 追跡カメラ（3D）取得
 *
 * @param  なし
 * @return CameraStateTracking3D：追跡カメラ（3D）のポインタ
 */
CameraStateTracking3D* GameCamera::GetStateTrack3D()
{
	return m_stateTrack3D.get();
}

//------------------------------------------------------------------
/**
 * @brief 追跡カメラ（2D）取得
 *
 * @param  なし
 * @return CameraStateTracking2D：追跡カメラ（2D）のポインタ
 */
CameraStateTracking2D* GameCamera::GetStateTrack2D()
{
	return m_stateTrack2D.get();
}

//------------------------------------------------------------------
/**
 * @brief 切り替えカメラ取得
 *
 * @param  なし
 * @return CameraStateLerpSwitch<T>：切り替えカメラのポインタ
 */
CameraStateLerpSwitch<GameCamera>* GameCamera::GetStateLerp()
{
	return m_stateLerp.get();
}

//------------------------------------------------------------------
/**
 * @brief 見渡しカメラ（3D）取得
 *
 * @param  なし
 * @return CameraStateOverLooking3D：見渡しカメラ（3D）のポインタ
 */
CameraStateOverLooking3D* GameCamera::GetStateOverLooking3D()
{
	return m_stateOverLooking3D.get();
}

//------------------------------------------------------------------
/**
 * @brief 見渡しカメラ（2D）取得
 *
 * @param  なし
 * @return CameraStateOverLooking2D：見渡しカメラ（2D）のポインタ
 */
CameraStateOverLooking2D* GameCamera::GetStateOverLooking2D()
{
	return m_stateOverLooking2D.get();
}