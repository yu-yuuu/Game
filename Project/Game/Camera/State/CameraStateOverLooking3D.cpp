/**
 *
 * @file CameraStateOverLooking3D.cpp
 *
 * @brief 3D見渡しカメラのソースファイル
 *
 * @author Kato Yuki
 *
 * @date 2024/2/26
 *
 */
#include "pch.h"
#include "CameraStateOverLooking3D.h"
#include "Game/Camera/SceneCamera/GameCamera.h"
#include "Game/Camera/State/CameraStateTracking3D.h"
#include "Game/Camera/State/CameraStateLerpSwitch.h"
#include "Game/MyLibrary/CommonResource/GameResource.h"
#include "Game/MyLibrary/GameParameter/GameParameter.h"
#include "Game/MyLibrary/Utility/MyUtility.h"

using namespace DirectX;

//------------------------------------------------------------------
/**
 * @brief コンストラクタ
 *
 * @param gameCamera：ゲームカメラ
 */
CameraStateOverLooking3D::CameraStateOverLooking3D(GameCamera* gameCamera)
	: m_gameCamera(gameCamera)
	, m_basePosition()
	, m_positionRatio(0.0f)
	, m_horizontalAngle(0.0f)
	, m_verticalAngle(0.0f)
{

}

//------------------------------------------------------------------
/**
 * @brief デストラクタ
 */
CameraStateOverLooking3D::~CameraStateOverLooking3D()
{
}

//------------------------------------------------------------------
/**
 * @brief 初期化
 *
 * @param  なし
 * @return なし
 */
void CameraStateOverLooking3D::Initialize()
{
	// 位置の割合を計算
	m_positionRatio = m_gameCamera->GetEyePosition().Length() / m_basePosition.Length();
	// 注視点設定
	m_gameCamera->SetTargetPosition(m_targetPosition);
	// 回転角度初期化
	m_horizontalAngle = 0.0f;
	m_verticalAngle = 0.0f;
}

//------------------------------------------------------------------
/**
 * @brief 更新
 *
 * @param  なし
 * @return なし
 */
void CameraStateOverLooking3D::Update()
{
	// 各種リソース取得
	GameResource* gameResource = GameResource::GetInstance();
	InputManager* inputManager = gameResource->GetInputManager();

	// 追跡カメラへ切り替え
	if (inputManager->GetKey(Keyboard::Keys::F).press)
	{
		ChangeTrackSetting();
	}

	// カメラ回転
	Rotation();
	// カメラ前後移動
	Move();
}

//------------------------------------------------------------------
/**
 * @brief 操作中フラグ
 *
 * @param  なし
 * @return false：操作可能
 */
bool CameraStateOverLooking3D::IsOperation()
{
	return false;
}

//------------------------------------------------------------------
/**
 * @briefカメラ回転
 *
 * @param  なし
 * @return なし
 */
void CameraStateOverLooking3D::Rotation()
{
	// キーマネージャー取得
	InputManager* inputManager = GameResource::GetInstance()->GetInputManager();
	
	// 一時保存用
	float vertical   = m_verticalAngle;
	float horizontal = m_horizontalAngle;

	// 見下ろしへ
	if      (inputManager->GetKey(Keyboard::Keys::W).down) m_verticalAngle -= MOVE_SPEED;
	// 横へ
	else if (inputManager->GetKey(Keyboard::Keys::S).down) m_verticalAngle += MOVE_SPEED;
	
	// 左回転
	if      (inputManager->GetKey(Keyboard::Keys::A).down) m_horizontalAngle -= MOVE_SPEED;
	// 右回転
	else if (inputManager->GetKey(Keyboard::Keys::D).down) m_horizontalAngle += MOVE_SPEED;

	// 入力が無ければ終了
	if (KT::MyUtility::FloatPresqueEqual(vertical, m_verticalAngle) &&
		KT::MyUtility::FloatPresqueEqual(horizontal, m_horizontalAngle))
		return;


	// 初期位置から45度ずつに制限
	m_verticalAngle = std::min(std::max(-VERTICAL_ANGLE_LIMIT, m_verticalAngle), VERTICAL_ANGLE_LIMIT);
	
	// 回転計算
	m_gameCamera->SetRotation(
		SimpleMath::Quaternion::CreateFromAxisAngle(SimpleMath::Vector3::UnitX, m_verticalAngle) * 
		SimpleMath::Quaternion::CreateFromAxisAngle(SimpleMath::Vector3::UnitY, m_horizontalAngle));
}

//------------------------------------------------------------------
/**
 * @brief カメラ前後移動
 *
 * @param  なし
 * @return なし
 */
void CameraStateOverLooking3D::Move()
{
	// キーマネージャー取得
	InputManager* inputManager = GameResource::GetInstance()->GetInputManager();

	// 近づく（ 拡大 ）
	if      (inputManager->GetKey(Keyboard::Keys::Up).down)   m_positionRatio -= MOVE_SPEED;
	// 遠ざかる（ 縮小 ）
	else if (inputManager->GetKey(Keyboard::Keys::Down).down) m_positionRatio += MOVE_SPEED;
	// 入力が無ければ終了
	else return;
	
	// 位置の割合を補正
	m_positionRatio = std::min(std::max(POSITION_RATIO_LIMIT.x, m_positionRatio), POSITION_RATIO_LIMIT.y);

	// 線形補完を利用して位置を動かす
	m_gameCamera->SetEyePosition(SimpleMath::Vector3::Lerp(
		SimpleMath::Vector3::Zero, m_basePosition, m_positionRatio));
}

//------------------------------------------------------------------
/**
 * @brief 追跡カメラへ切り替え
 *
 * @param  なし
 * @return なし
 */
void CameraStateOverLooking3D::ChangeTrackSetting()
{
	// 追跡カメラ取得
	CameraStateTracking3D* track3D = m_gameCamera->GetStateTrack3D();
	// 補完カメラ取得
	CameraStateLerpSwitch<GameCamera>* stateLerp = m_gameCamera->GetStateLerp();

	// 補完設定
	stateLerp->LerpSetting(track3D, KT::GameParam::LERP_TIME_OVERLOOKING);
	stateLerp->PositionSetting(m_gameCamera->GetEyePosition(), track3D->GetEyePosition());
	stateLerp->TargetSetting(m_gameCamera->GetTargetPosition(), m_gameCamera->GetPlayerPosition());
	stateLerp->RotationSetting(m_gameCamera->GetRotation(), track3D->GetBeforeRotation());

	// 補完カメラ設定
	m_gameCamera->SetNextCamera(stateLerp);
	m_gameCamera->SetCameraState(KT::GameParam::CameraState::OPERATION);
}

//------------------------------------------------------------------
/**
 * @brief 初期設定
 *
 * @param  target      ：注視点位置
 * @param  basePosition：基準位置
 * @return なし
 */
void CameraStateOverLooking3D::InitSetting(const DirectX::SimpleMath::Vector3& target, const DirectX::SimpleMath::Vector3& basePosition)
{
	m_targetPosition = target;
	SetBasePosition(basePosition);
}

//------------------------------------------------------------------
/**
 * @brief 注視点取得
 *
 * @param  なし
 * @return Vector3：注視点位置
 */
const DirectX::SimpleMath::Vector3& CameraStateOverLooking3D::GetTargetPosition() const
{
	return m_targetPosition;
}

//------------------------------------------------------------------
/**
 * @brief カメラ基準位置取得
 *
 * @param  なし
 * @return Vector3：基準位置
 */
const DirectX::SimpleMath::Vector3& CameraStateOverLooking3D::GetBasePosition() const
{
	return m_basePosition;
}

//------------------------------------------------------------------
/**
 * @brief 基準位置設定
 *
 * @param  basePosition：基準位置
 * @return なし
 */
void CameraStateOverLooking3D::SetBasePosition(const DirectX::SimpleMath::Vector3& basePosition)
{
	m_basePosition = basePosition;
}