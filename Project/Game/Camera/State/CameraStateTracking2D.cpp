/**
 *
 * @file CameraStateTracking2D.cpp
 *
 * @brief 2D追跡カメラのソースファイル
 *
 * @author Kato Yuki
 *
 * @date 2024/2/12
 *
 */
#include "pch.h"
#include "CameraStateTracking2D.h"
#include "Game/Scene/PlayScene.h"
#include "Game/Camera/SceneCamera/GameCamera.h"
#include "Game/Camera/State/CameraStateTracking3D.h"
#include "Game/Camera/State/CameraStateLerpSwitch.h"
#include "Game/Camera/State/CameraStateOverLooking2D.h"
#include "Game/MyLibrary/CommonResource/GameResource.h"
#include "Game/MyLibrary/GameParameter/GameParameter.h"

using namespace DirectX;

//------------------------------------------------------------------
/**
 * @brief コンストラクタ
 *
 * @param sceneCamera：ゲームカメラ
 */
CameraStateTracking2D::CameraStateTracking2D(GameCamera* gameCamera)
	: m_gameCamera(gameCamera)
	, m_offsetPosition()
	, m_beforeTarget()
{
}

//------------------------------------------------------------------
/**
 * @brief デストラクタ
 */
CameraStateTracking2D::~CameraStateTracking2D()
{
}

//------------------------------------------------------------------
/**
 * @brief 初期化
 *
 * @param  なし
 * @return なし
 */
void CameraStateTracking2D::Initialize()
{
	m_gameCamera->SetDimension(KT::GameParam::Dimension::_2D);
}

//------------------------------------------------------------------
/**
 * @brief 更新
 *
 * @param  なし
 * @return なし
 */
void CameraStateTracking2D::Update()
{
	// 位置更新
	m_gameCamera->SetEyePosition(m_offsetPosition);

	// 見渡しカメラに切り替えて良いか
	if (CheckChangeOverLooking())
	{
		// 見渡しカメラ切替設定
		ChangeOverLookingSetting();
	}
}

//------------------------------------------------------------------
/**
 * @brief 次元切替設定
 *
 * @param  なし
 * @return なし
 */
void CameraStateTracking2D::ChangeDimensionSetting()
{
	// 補完カメラ取得
	CameraStateLerpSwitch<GameCamera>* stateLerp = m_gameCamera->GetStateLerp();
	// 切り替え先カメラ取得
	CameraStateTracking3D* state3D = m_gameCamera->GetStateTrack3D();
	// 補完設定
	stateLerp->LerpSetting(state3D, KT::GameParam::LERP_TIME_DIMENSION);
	stateLerp->PositionSetting(m_gameCamera->GetEyePosition(), state3D->GetEyePosition());
	stateLerp->ProjectionSetting(m_gameCamera->GetProjectionMatrix(), CameraProjection::CreatePerspectiveProjection(m_gameCamera->GetAspectRatio()));
	// 次のカメラ設定
	m_gameCamera->SetNextCamera(stateLerp);
}

//------------------------------------------------------------------
/**
 * @brief 見渡しカメラへ切り替えて良いか確認
 *
 * @param  なし
 * @return true ：切り替え可
 * @return false：切り替え不可
 */
bool CameraStateTracking2D::CheckChangeOverLooking()
{
	// プレイヤーが床の上に居ないなら切替させない
	if (!m_gameCamera->GetScene()->OnGroundPlayer()) return false;

	// キーマネージャー取得
	InputManager* inputManager = GameResource::GetInstance()->GetInputManager();

	return inputManager->GetKey(Keyboard::Keys::F).press;
}

//------------------------------------------------------------------
/**
 * @brief 見渡しカメラ切替設定
 *
 * @param  なし
 * @return なし
 */
void CameraStateTracking2D::ChangeOverLookingSetting()
{
	// 現在の注視点を保存しておく
	m_beforeTarget = m_gameCamera->GetTargetPosition();
	// 補完カメラ取得
	CameraStateLerpSwitch<GameCamera>* stateLerp = m_gameCamera->GetStateLerp();
	// 補完設定
	stateLerp->LerpSetting(m_gameCamera->GetStateOverLooking2D(), KT::GameParam::LERP_TIME_OVERLOOKING);
	stateLerp->ProjectionSetting(m_gameCamera->GetProjectionMatrix(),
		CameraProjection::CreateOrthographicProjection(m_gameCamera->GetAspectRatio(), 
			CameraProjection::OVER_LOOKING_RECT)
	);
	// 次のカメラをセット
	m_gameCamera->SetNextCamera(stateLerp);
	m_gameCamera->SetCameraState(KT::GameParam::CameraState::OPERATION);
}

//------------------------------------------------------------------
/**
 * @brief カメラ位置取得
 *
 * @param  なし
 * @return Vector3：カメラ位置
 */
const DirectX::SimpleMath::Vector3& CameraStateTracking2D::GetEyePosition() const
{
	return m_offsetPosition;
}

//------------------------------------------------------------------
/**
 * @brief カメラ位置設定
 *
 * @param eyeOffsetPosition：設定するカメラ位置
 * @return なし
 */
void CameraStateTracking2D::SetEyePosition(const DirectX::SimpleMath::Vector3& eyeOffsetPosition)
{
	m_offsetPosition = eyeOffsetPosition;
}

//------------------------------------------------------------------
/**
 * @brief 保存している注視点取得
 *
 * @param なし
 * @return Vector3：注視点
 */
const DirectX::SimpleMath::Vector3& CameraStateTracking2D::GetBeforeTarget() const
{
	return m_beforeTarget;
}

//------------------------------------------------------------------
/**
 * @brief 操作中フラグ
 *
 * @param なし
 * @return false：操作可能
 */
bool CameraStateTracking2D::IsOperation()
{
	return false;
}

//------------------------------------------------------------------
/**
 * @brief 初期設定
 *
 * @param  eyePosition：設定するカメラ位置
 * @return なし
 */
void CameraStateTracking2D::InitSetting(const DirectX::SimpleMath::Vector3& eyePosition)
{
	SetEyePosition(eyePosition);
}