/**
 *
 * @file CameraStateLerpSwitch.h
 *
 * @brief カメラの位置、回転、射影行列を線形補完で切り替えるクラス
 *
 * @author Kato Yuki
 *
 * @date 20242/14
 *
 */
#pragma once

#include <vector>
#include "Game/Camera/State/ICameraState.h"
#include "Game/Camera/CameraProjection.h"
#include "Game/MyLibrary/CommonResource/GameResource.h"

template<typename ParentCamera>
class CameraStateLerpSwitch : public ICameraState
{
//----------------------------------------------
// 変数
//----------------------------------------------
private:

	// この状態を使用するカメラ
	ParentCamera* m_camera;
	// 補完後に切り替えるカメラ状態
	ICameraState* m_nextCamera;

	// 補完前のカメラ位置
	DirectX::SimpleMath::Vector3 m_beforeEye;
	// 補完後のカメラ位置
	DirectX::SimpleMath::Vector3 m_afterEye;
	// 補完前の注視点位置
	DirectX::SimpleMath::Vector3 m_beforeTarget;
	// 補完後の注視点位置
	DirectX::SimpleMath::Vector3 m_afterTarget;
	// 補完前の回転
	DirectX::SimpleMath::Quaternion m_beforeRotation;
	// 補完後の回転
	DirectX::SimpleMath::Quaternion m_afterRotation;
	// 補完前の射影行列
	DirectX::SimpleMath::Matrix m_beforeProjection;
	// 補完後の射影行列
	DirectX::SimpleMath::Matrix m_afterProjection;

	// 補完に掛ける時間
	float m_lerpTime;
	// 補完タイマー
	float m_switchTimer;

//----------------------------------------------
// 関数
//----------------------------------------------
public:

	// コンストラクタ
	CameraStateLerpSwitch(ParentCamera* camera);
	// デストラクタ
	~CameraStateLerpSwitch();

	// 初期化
	void Initialize() override;
	// 更新
	void Update() override;
	// 操作中フラグ
	bool IsOperation() override;
	
	// 補完のスキップ
	void Skip();

	// 補完設定
	void LerpSetting(ICameraState* nextCamera, const float& lerpTime);
	// 位置設定
	void PositionSetting(const DirectX::SimpleMath::Vector3& beforeEye, const DirectX::SimpleMath::Vector3& afterEye);
	// 注視点設定
	void TargetSetting(const DirectX::SimpleMath::Vector3& beforeTarget, const DirectX::SimpleMath::Vector3& afterTarget);
	// 回転設定
	void RotationSetting(const DirectX::SimpleMath::Quaternion& beforeRotation, const DirectX::SimpleMath::Quaternion& afterRotation);
	// 射影行列設定
	void ProjectionSetting(const DirectX::SimpleMath::Matrix& beforeProjection, const DirectX::SimpleMath::Matrix& afterProjection);

private:

	// 補完を開始してよいか
	bool IsStart();
	// 補完
	bool Lerp();

	// 移動補完
	void LerpMovement(const float& lerpRatio);
	// 注視点補完
	void LerpTarget(const float& lerpRatio);
	// 回転補完
	void LerpRotation(const float& lerpRatio);
	// 射影行列補完
	void LerpProjection(const float& lerpRatio);
	// パラメータリセット
	void Reset();
};


//-------------------------------------------------------------------------------------------
// 関数定義
//-------------------------------------------------------------------------------------------

//------------------------------------------------------------------
/**
 * @brief コンストラクタ
 *
 * @param camera：この状態を使用するカメラのポインタ
 */
template<typename ParentCamera>
inline CameraStateLerpSwitch<ParentCamera>::CameraStateLerpSwitch(ParentCamera* camera)
	: m_camera(camera)
	, m_nextCamera(nullptr)
	, m_beforeEye()
	, m_afterEye()
	, m_beforeRotation()
	, m_afterRotation()
	, m_beforeProjection()
	, m_afterProjection()
	, m_lerpTime(0.0f)
	, m_switchTimer(0.0f)
{
}

//------------------------------------------------------------------
/**
 * @brief デストラクタ
 *
 */
template<typename ParentCamera>
inline CameraStateLerpSwitch<ParentCamera>::~CameraStateLerpSwitch()
{
}

//------------------------------------------------------------------
/**
 * @brief 初期化
 *
 * @param  なし
 * @return なし
 */
template<typename ParentCamera>
inline void CameraStateLerpSwitch<ParentCamera>::Initialize()
{

}

//------------------------------------------------------------------
/**
 * @brief 更新
 *
 * @param  なし
 * @return なし
 */
template<typename ParentCamera>
inline void CameraStateLerpSwitch<ParentCamera>::Update()
{
	// 補完開始可能でないなら終了
	if (!IsStart()) return;
	// 補完が完了したら次の処理へ
	if (!Lerp()) return;

	// 次の状態のカメラを設定
	m_camera->SetNextCamera(m_nextCamera);
	// パラメーターをリセット
	Reset();
}

//------------------------------------------------------------------
/**
 * @brief 操作中か
 *
 * @param  なし
 * @return true：操作中
 */
template<typename ParentCamera>
inline bool CameraStateLerpSwitch<ParentCamera>::IsOperation()
{
	return true;
}

//------------------------------------------------------------------
/**
 * @brief 補完のスキップ
 *
 * @param  なし
 * @return なし
 */
template<typename ParentCamera>
inline void CameraStateLerpSwitch<ParentCamera>::Skip()
{
	m_switchTimer = m_lerpTime;
}

//------------------------------------------------------------------
/**
 * @brief 補完設定
 *
 * @param  nextCamera：補完後に切り替えるカメラ
 * @param  lerpTime  ：補完に掛ける時間
 * @return なし
 */
template<typename ParentCamera>
inline void CameraStateLerpSwitch<ParentCamera>::LerpSetting(ICameraState* nextCamera, const float& lerpTime)
{
	m_nextCamera = nextCamera;
	m_lerpTime = lerpTime;
}

//------------------------------------------------------------------
/**
 * @brief 位置補完の設定
 *
 * @param  beforeEye：補完前の位置
 * @param  afterEye ：補完後の位置
 * @return なし
 */
template<typename ParentCamera>
inline void CameraStateLerpSwitch<ParentCamera>::PositionSetting(const DirectX::SimpleMath::Vector3& beforeEye, const DirectX::SimpleMath::Vector3& afterEye)
{
	m_beforeEye = beforeEye;
	m_afterEye = afterEye;
}

//------------------------------------------------------------------
/**
 * @brief 注視点補完の設定
 *
 * @param  beforeTarget：補完前の位置
 * @param  afterTarget ：補完後の位置
 * @return なし
 */
template<typename ParentCamera>
inline void CameraStateLerpSwitch<ParentCamera>::TargetSetting(const DirectX::SimpleMath::Vector3& beforeTarget, const DirectX::SimpleMath::Vector3& afterTarget)
{
	m_beforeTarget = beforeTarget;
	m_afterTarget = afterTarget;
}

//------------------------------------------------------------------
/**
 * @brief 回転補完の設定
 *
 * @param  beforeRotation：補完前の回転
 * @param  afterRotation ：補完後の回転
 * @return なし
 */
template<typename ParentCamera>
inline void CameraStateLerpSwitch<ParentCamera>::RotationSetting(const DirectX::SimpleMath::Quaternion& beforeRotation, const DirectX::SimpleMath::Quaternion& afterRotation)
{
	m_beforeRotation = beforeRotation;
	m_afterRotation = afterRotation;
}

//------------------------------------------------------------------
/**
 * @brief 射影行列補完の設定
 *
 * @param  beforeProjection：補完前の射影行列
 * @param  afterProjection ：補完後の射影行列
 * @return なし
 */
template<typename ParentCamera>
inline void CameraStateLerpSwitch<ParentCamera>::ProjectionSetting(const DirectX::SimpleMath::Matrix& beforeProjection, const DirectX::SimpleMath::Matrix& afterProjection)
{
	m_beforeProjection = beforeProjection;
	m_afterProjection = afterProjection;
}


//------------------------------------------------------------------
/**
 * @brief 補完を開始してよいか
 *
 * @param  なし
 * @return true ：開始可能
 * @return false：開始不可
 */
template<typename ParentCamera>
inline bool CameraStateLerpSwitch<ParentCamera>::IsStart()
{
	return m_nextCamera != nullptr;
}

//------------------------------------------------------------------
/**
 * @brief 補完処理
 *
 * @param  なし
 * @return true ：補完終了
 * @return false：補完中
 */
template<typename ParentCamera>
inline bool CameraStateLerpSwitch<ParentCamera>::Lerp()
{

	// 進行時間取得
	DX::StepTimer* stepTimer = GameResource::GetInstance()->GetStepTimer();	
	// タイマー進行
	m_switchTimer += static_cast<float>(stepTimer->GetElapsedSeconds());	
	// 現在の割合を計算
	float ratio = m_switchTimer / m_lerpTime;
	// 割合が100%を越えないようにする
	ratio = std::min(ratio, 1.0f);

	// 割合が100％（1.0f）より小さいなら切り替え処理を行う
	if (ratio < 1.0f)
	{
		// 補完
		if (m_beforeEye        != m_afterEye)        LerpMovement(ratio);
		if (m_beforeTarget     != m_afterTarget)     LerpTarget(ratio);
		if (m_beforeRotation   != m_afterRotation)   LerpRotation(ratio);
		if (m_beforeProjection != m_afterProjection) LerpProjection(ratio);

		// 補完中
		return false;
	}

	// 補完終了
	return true;
}

//------------------------------------------------------------------
/**
 * @brief 位置補完処理
 *
 * @param  lerpRatio：補完の割合
 * @return なし
 */
template<typename ParentCamera>
inline void CameraStateLerpSwitch<ParentCamera>::LerpMovement(const float& lerpRatio)
{
	m_camera->SetEyePosition
	(
		DirectX::SimpleMath::Vector3::Lerp
		(
			m_beforeEye,
			m_afterEye,
			lerpRatio
		)
	);
}

//------------------------------------------------------------------
/**
 * @brief 注視点補完処理
 *
 * @param  lerpRatio：補完の割合
 * @return なし
 */template<typename ParentCamera>
inline void CameraStateLerpSwitch<ParentCamera>::LerpTarget(const float& lerpRatio)
{
	m_camera->SetTargetPosition
	(
		DirectX::SimpleMath::Vector3::Lerp
		(
			m_beforeTarget,
			m_afterTarget,
			lerpRatio
		)
	);
}

//------------------------------------------------------------------
/**
 * @brief 回転補完処理
 *
 * @param  lerpRatio：補完の割合
 * @return なし
 */
template<typename ParentCamera>
inline void CameraStateLerpSwitch<ParentCamera>::LerpRotation(const float& lerpRatio)
{
	m_camera->SetRotation
	(
		DirectX::SimpleMath::Quaternion::Lerp
		(
			m_beforeRotation,
			m_afterRotation,
			lerpRatio
		)
	);
}

//------------------------------------------------------------------
/**
 * @brief 射影行列補完
 *
 * @param  lerpRatio：補完の割合
 * @return なし
 */
template<typename ParentCamera>
inline void CameraStateLerpSwitch<ParentCamera>::LerpProjection(const float& lerpRatio)
{
	m_camera->SetProjectionMatrix
	(
		DirectX::SimpleMath::Matrix::Lerp
		(
			m_beforeProjection,
			m_afterProjection,
			lerpRatio
		)
	);
}

//------------------------------------------------------------------
/**
 * @brief パラメーターリセット
 *
 * @param  なし
 * @return なし
 */
template<typename ParentCamera>
inline void CameraStateLerpSwitch<ParentCamera>::Reset()
{
	m_beforeEye        = m_afterEye        = DirectX::SimpleMath::Vector3::Zero;
	m_beforeTarget     = m_afterTarget     = DirectX::SimpleMath::Vector3::Zero;
	m_beforeRotation   = m_afterRotation   = DirectX::SimpleMath::Quaternion::Identity;
	m_beforeProjection = m_afterProjection = DirectX::SimpleMath::Matrix::Identity;
	m_lerpTime         = m_switchTimer     = 0.0f;
	m_nextCamera       = nullptr;
}