/**
 *
 * @file CameraStateOverLooking2D.cpp
 *
 * @brief 2D見渡しカメラのソースファイル
 *
 * @author Kato Yuki
 *
 * @date 2024/2/28
 *
 */
#include "pch.h"
#include "CameraStateOverLooking2D.h"
#include "Game/Camera/SceneCamera/GameCamera.h"
#include "Game/Camera/State/CameraStateTracking2D.h"
#include "Game/Camera/State/CameraStateLerpSwitch.h"
#include "Game/MyLibrary/CommonResource/GameResource.h"
#include "Game/MyLibrary/GameParameter/GameParameter.h"
#include "Game/MyLibrary/Utility/MyUtility.h"

using namespace DirectX;

//------------------------------------------------------------------
/**
 * @brief コンストラクタ
 *
 * @param gameCamera：ゲームカメラのポインタ
 */
CameraStateOverLooking2D::CameraStateOverLooking2D(GameCamera* gameCamera)
	: m_gameCamera(gameCamera)
	, m_limitPosition()
{

}

//------------------------------------------------------------------
/**
 * @brief デストラクタ
 */
CameraStateOverLooking2D::~CameraStateOverLooking2D()
{
}

//------------------------------------------------------------------
/**
 * @brief 初期化
 *
 * @param  なし
 * @return なし
 */
void CameraStateOverLooking2D::Initialize()
{

}

//------------------------------------------------------------------
/**
 * @brief 更新
 *
 * @param  なし
 * @return なし
 */
void CameraStateOverLooking2D::Update()
{
	// 各種リソース取得
	GameResource* gameResource = GameResource::GetInstance();
	InputManager* inputManager = gameResource->GetInputManager();

	// 追跡カメラへ切り替え
	if (inputManager->GetKey(Keyboard::Keys::F).press)
	{
		ChangeTrackSetting();
	}

	// 移動
	Move();
}

//------------------------------------------------------------------
/**
 * @brief 操作中フラグ
 *
 * @param  なし
 * @return false：操作可能
 */
bool CameraStateOverLooking2D::IsOperation()
{
	return false;
}

//------------------------------------------------------------------
/**
 * @brief カメラ前後移動
 *
 * @param  なし
 * @return なし
 */
void CameraStateOverLooking2D::Move()
{
	// キーマネージャー取得
	InputManager* inputManager = GameResource::GetInstance()->GetInputManager();

	// カメラの向き取得
	SimpleMath::Vector3 dir = m_gameCamera->GetDirection();
	// カメラの頭の向き取得
	SimpleMath::Vector3 up = m_gameCamera->GetUpVector();
	// 右方向ベクトル計算
	SimpleMath::Vector3 moveRight = dir.Cross(up);
	
	// 移動量
	SimpleMath::Vector3 move;

	// 上へ
	if      (inputManager->GetKey(Keyboard::Keys::W).down) move += up * MOVE_SPEED;
	// 下へ
	else if (inputManager->GetKey(Keyboard::Keys::S).down) move -= up * MOVE_SPEED;

	// 左へ
	if      (inputManager->GetKey(Keyboard::Keys::A).down) move -= moveRight * MOVE_SPEED;
	// 右へ
	else if (inputManager->GetKey(Keyboard::Keys::D).down) move += moveRight * MOVE_SPEED;

	// ステージから離れないように制限を掛けて移動量を反映させる
	m_gameCamera->SetTargetPosition(
		KT::MyUtility::Clamp(
			m_gameCamera->GetTargetPosition() + move,
			SimpleMath::Vector3::Zero, 
			m_limitPosition)
	);
}

//------------------------------------------------------------------
/**
 * @brief 追跡カメラへ切り替え設定
 *
 * @param  なし
 * @return なし
 */
void CameraStateOverLooking2D::ChangeTrackSetting()
{
	// 追跡カメラ取得
	CameraStateTracking2D* track2D = m_gameCamera->GetStateTrack2D();
	// 補完カメラ取得
	CameraStateLerpSwitch<GameCamera>* stateLerp = m_gameCamera->GetStateLerp();

	// 視点タイプによってカメラの描画範囲を切り替える
	RECT rect;
	if (m_gameCamera->CheckSightType(KT::GameParam::SightType::SIDE))
		rect = CameraProjection::SIDE_RECT;
	else
		rect = CameraProjection::TOPDOWN_RECT;

	// 補完設定
	stateLerp->LerpSetting(track2D, KT::GameParam::LERP_TIME_OVERLOOKING);
	stateLerp->TargetSetting(m_gameCamera->GetTargetPosition(), track2D->GetBeforeTarget());
	stateLerp->ProjectionSetting(m_gameCamera->GetProjectionMatrix(),
		CameraProjection::CreateOrthographicProjection(m_gameCamera->GetAspectRatio(), rect));

	// 追跡カメラ設定
	m_gameCamera->SetNextCamera(stateLerp);
	m_gameCamera->SetCameraState(KT::GameParam::CameraState::OPERATION);
}

//------------------------------------------------------------------
/**
 * @brief 移動制限設定
 *
 * @param limitPosition：移動制限値
 * @return なし
 */
void CameraStateOverLooking2D::SetLimitPosition(const DirectX::SimpleMath::Vector3& limitPosition)
{
	m_limitPosition = limitPosition;
}

//------------------------------------------------------------------
/**
 * @brief 初期設定
 *
 * @param limit：移動制限値
 * @return なし
 */
void CameraStateOverLooking2D::InitSetting(const DirectX::SimpleMath::Vector3& limit)
{
	SetLimitPosition(limit);
}
