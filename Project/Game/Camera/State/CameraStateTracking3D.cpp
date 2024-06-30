/**
 *
 * @file CameraStateTracking3D.cpp
 *
 * @brief 3D追跡カメラのソースファイル
 *
 * @author Kato Yuki
 *
 * @date 2024/2/11
 *
 */
#include "pch.h"
#include "CameraStateTracking3D.h"
#include "Game/Scene/PlayScene.h"
#include "Game/Camera/SceneCamera/GameCamera.h"
#include "Game/Camera/State/CameraStateTracking2D.h"
#include "Game/Camera/State/CameraStateOverLooking3D.h"
#include "Game/Camera/State/CameraStateLerpSwitch.h"
#include "Game/MyLibrary/CommonResource/GameResource.h"
#include "Game/MyLibrary/GameParameter/GameParameter.h"

using namespace DirectX;

//------------------------------------------------------------------
/**
 * @brief コンストラクタ
 *
 * @param gameCamera：ゲームカメラ
 */
CameraStateTracking3D::CameraStateTracking3D(GameCamera* gameCamera)
	: m_gameCamera(gameCamera)
	, m_beforeRotation()
{

}

//------------------------------------------------------------------
/**
 * @brief デストラクタ
 */
CameraStateTracking3D::~CameraStateTracking3D()
{
}

//------------------------------------------------------------------
/**
 * @brief 初期化
 *
 * @param  なし
 * @return なし
 */
void CameraStateTracking3D::Initialize()
{
	m_gameCamera->SetDimension(KT::GameParam::Dimension::_3D);
}

//------------------------------------------------------------------
/**
 * @brief 更新
 *
 * @param  なし
 * @return なし
 */
void CameraStateTracking3D::Update()
{
	// カメラ位置更新
	m_gameCamera->SetEyePosition(GetEyePosition());

	// 回転させて良いか
	if(CheckRotation())
	{
		// カメラ回転処理
		RotationSetting();
	}
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
void CameraStateTracking3D::ChangeDimensionSetting()
{
	// 補完カメラ取得
	CameraStateLerpSwitch<GameCamera>* stateLerp = m_gameCamera->GetStateLerp();
	
	// 切り替え先カメラ取得
	CameraStateTracking2D* state2D = m_gameCamera->GetStateTrack2D();

	// 視点タイプによってカメラの描画範囲を切り替える
	RECT rect;
	if (m_gameCamera->CheckSightType(KT::GameParam::SightType::SIDE))
		rect = CameraProjection::SIDE_RECT;
	else
		rect = CameraProjection::TOPDOWN_RECT;

	// 補完設定
	stateLerp->LerpSetting(state2D, KT::GameParam::LERP_TIME_DIMENSION);
	stateLerp->PositionSetting(m_gameCamera->GetEyePosition(), state2D->GetEyePosition());
	stateLerp->ProjectionSetting(m_gameCamera->GetProjectionMatrix(), 
		CameraProjection::CreateOrthographicProjection(m_gameCamera->GetAspectRatio(), rect));

	// 次のカメラ設定
	m_gameCamera->SetNextCamera(stateLerp);
}

//------------------------------------------------------------------
/**
 * @brief 回転してよいか確認
 *
 * @param  なし
 * @return なし
 */
bool CameraStateTracking3D::CheckRotation()
{
	// キーマネージャー取得
	InputManager* inputManager = GameResource::GetInstance()->GetInputManager();

	// プレイヤーが床の上に居ないなら回転させない
	if (!m_gameCamera->GetScene()->OnGroundPlayer()) return false;

	// 入力確認
	return
		// Wキーが押された かつ 横視点
		(inputManager->GetKey(Keyboard::Keys::W).press && m_gameCamera->CheckSightType(KT::GameParam::SightType::SIDE)) ||
		// Sキーが押された かつ 見下ろし視点
		(inputManager->GetKey(Keyboard::Keys::S).press && m_gameCamera->CheckSightType(KT::GameParam::SightType::TOPDOWN)) ||
		// Aキーが押された 
		inputManager->GetKey(Keyboard::Keys::A).press ||
		// Dキーが押された 
		inputManager->GetKey(Keyboard::Keys::D).press;
}

//------------------------------------------------------------------
/**
 * @brief カメラ回転設定
 *
 * @param  なし
 * @return なし
 */
void CameraStateTracking3D::RotationSetting()
{
	// 各種リソース取得
	GameResource*    gameResource    = GameResource::GetInstance();
	InputManager*    inputManager    = gameResource->GetInputManager();
	ResourceManager* resourceManager = gameResource->GetResourceManager();

	// 現在の回転クォータニオン
	SimpleMath::Quaternion rotation = m_gameCamera->GetRotation();

	// 回転させる角度
	float radian = XMConvertToRadians(GameCamera::ROTATION_ANGLE);

	// 見下ろしへ
	if (inputManager->GetKey(Keyboard::Keys::W).press)
	{
		rotation = SimpleMath::Quaternion::CreateFromAxisAngle(
			SimpleMath::Vector3::UnitX, -radian) * rotation;
		// 見下ろしへ変更
		m_gameCamera->SetSightType(KT::GameParam::SightType::TOPDOWN);
	}
	// 横へ
	else if(inputManager->GetKey(Keyboard::Keys::S).press)
	{
		rotation = SimpleMath::Quaternion::CreateFromAxisAngle(
			SimpleMath::Vector3::UnitX, radian) * rotation;
		// 横へ変更
		m_gameCamera->SetSightType(KT::GameParam::SightType::SIDE);
	}
	// 左回転
	else if (inputManager->GetKey(Keyboard::Keys::A).press)
	{
		rotation = rotation * SimpleMath::Quaternion::CreateFromAxisAngle(
			SimpleMath::Vector3::UnitY, -radian);
	}
	// 右回転
	else if (inputManager->GetKey(Keyboard::Keys::D).press)
	{
		rotation = rotation * SimpleMath::Quaternion::CreateFromAxisAngle(
			SimpleMath::Vector3::UnitY, radian);
	}

	// 補完カメラ取得
	CameraStateLerpSwitch<GameCamera>* stateLerp = m_gameCamera->GetStateLerp();
	
	// カメラ位置取得
	SimpleMath::Vector3 eye = GetEyePosition();
	// 補完設定
	stateLerp->LerpSetting(this, KT::GameParam::LERP_TIME_ROTATION);
	stateLerp->PositionSetting(m_gameCamera->GetEyePosition(), eye);
	stateLerp->RotationSetting(m_gameCamera->GetRotation(), rotation);
	// 回転状態をセット
	m_gameCamera->SetNextCamera(stateLerp);

	// SEを流す
	resourceManager->PlaySound(KT::Sound::SE, KT::Sound::SENumber::XACT_WAVEBANK_SE_CAMERAROTATION);
}

//------------------------------------------------------------------
/**
 * @brief 見渡しカメラに切り替えてよいか確認
 *
 * @param  なし
 * @return true：切替可
 * @return true：切替不可
 */
bool CameraStateTracking3D::CheckChangeOverLooking()
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
void CameraStateTracking3D::ChangeOverLookingSetting()
{
	// 現在の回転を保存しておく
	m_beforeRotation = m_gameCamera->GetRotation();

	// 補完カメラ取得
	CameraStateLerpSwitch<GameCamera>* stateLerp = m_gameCamera->GetStateLerp();
	// 見渡しカメラ取得
	CameraStateOverLooking3D* overLooking3D = m_gameCamera->GetStateOverLooking3D();
	// 補完設定
	stateLerp->LerpSetting(overLooking3D, KT::GameParam::LERP_TIME_OVERLOOKING);
	stateLerp->PositionSetting(m_gameCamera->GetEyePosition(), overLooking3D->GetBasePosition() * 0.5f);
	stateLerp->TargetSetting(m_gameCamera->GetTargetPosition(), overLooking3D->GetTargetPosition());
	stateLerp->RotationSetting(m_gameCamera->GetRotation(), SimpleMath::Quaternion::Identity);
	// 補完カメラ設定
	m_gameCamera->SetNextCamera(stateLerp);
	m_gameCamera->SetCameraState(KT::GameParam::CameraState::OPERATION);
}

//------------------------------------------------------------------
/**
 * @brief カメラ位置取得
 *
 * @param なし
 * @return Vector3：カメラ位置
 */
const DirectX::SimpleMath::Vector3& CameraStateTracking3D::GetEyePosition() const
{
	// 横視点
	if(m_gameCamera->CheckSightType(KT::GameParam::SightType::SIDE))
		return KT::GameParam::EYE_OFFSET_SIDE;

	// 見下ろし視点
	return KT::GameParam::EYE_OFFSET_TOPDOWN;
}

//------------------------------------------------------------------
/**
 * @brief 見下ろし切替前の回転取得
 *
 * @param なし
 * @return Quaternion：回転
 */
const DirectX::SimpleMath::Quaternion& CameraStateTracking3D::GetBeforeRotation() const
{
	return m_beforeRotation;
}

//------------------------------------------------------------------
/**
 * @brief 操作中フラグ
 *
 * @param なし
 * @return false：操作可
 */
bool CameraStateTracking3D::IsOperation()
{
	return false;
}
