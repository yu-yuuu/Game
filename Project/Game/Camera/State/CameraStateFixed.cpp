/**
 *
 * @file CameraStateFixed.cpp
 *
 * @brief 固定位置カメラのソースファイル
 *
 * @author Kato Yuki
 *
 * @date 2024/3/2
 *
 */
#include "pch.h"
#include "CameraStateFixed.h"
#include "Game/Camera/SceneCamera/StateCamera .h"

//------------------------------------------------------------------
/**
 * @brief コンストラクタ
 *
 * @param stateCamera：ステートカメラのポインタ
 */
CameraStateFixed::CameraStateFixed(StateCamera* stateCamera)
	: m_stateCamera(stateCamera)
{
}

//------------------------------------------------------------------
/**
 * @brief デストラクタ
 */
CameraStateFixed::~CameraStateFixed()
{
}

//------------------------------------------------------------------
/**
 * @brief 初期化
 *
 * @param  なし
 * @return なし
 */
void CameraStateFixed::Initialize()
{
}

//------------------------------------------------------------------
/**
 * @brief 更新
 *
 * @param  なし
 * @return なし
 */
void CameraStateFixed::Update()
{
}

//------------------------------------------------------------------
/**
 * @brief 操作中フラグ
 *
 * @param  なし
 * @return false：操作可能
 */
bool CameraStateFixed::IsOperation()
{
	return false;
}
