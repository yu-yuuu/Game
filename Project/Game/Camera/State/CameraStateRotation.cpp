#include "pch.h"
#include "CameraStateRotation.h"
#include "Game/Camera/SceneCamera/StateCamera .h"

using namespace DirectX;

//------------------------------------------------------------------
/**
 * @brief コンストラクタ
 *
 * @param stateCamera：状態カメラ
 */
CameraStateRotation::CameraStateRotation(StateCamera* stateCamera)
	: m_camera(stateCamera)
	, m_rotationSpeed(0.0f)
{
}

//------------------------------------------------------------------
/**
 * @brief デストラクタ
 */
CameraStateRotation::~CameraStateRotation()
{
}

//------------------------------------------------------------------
/**
 * @brief 初期化
 *
 * @param  なし
 * @return なし
 */
void CameraStateRotation::Initialize()
{
}

//------------------------------------------------------------------
/**
 * @brief 更新
 *
 * @param  なし
 * @return なし
 */
void CameraStateRotation::Update()
{
	// 設定されている数値で回転クォータニオンを計算
	SimpleMath::Quaternion rotation = SimpleMath::Quaternion::CreateFromAxisAngle(m_axisOfRotation, m_rotationSpeed);
	// 現在の回転に計算した回転を加える
	m_camera->SetRotation(m_camera->GetRotation() * rotation);
}

//------------------------------------------------------------------
/**
 * @brief 操作中フラグ
 *
 * @param  なし
 * @return false：操作可能
 */
bool CameraStateRotation::IsOperation()
{
	return false;
}

//------------------------------------------------------------------
/**
 * @brief 回転設定
 *
 * @param  rotationSpeed ：回転速度
 * @param  axisOfRotation：回転の軸
 * @return なし
 */
void CameraStateRotation::RotationSetting(const float& rotationSpeed, const DirectX::SimpleMath::Vector3& axisOfRotation)
{
	m_rotationSpeed = rotationSpeed;
	m_axisOfRotation = axisOfRotation;
}
