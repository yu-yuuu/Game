/**
 *
 * @file CameraProjection.cpp
 *
 * @brief JΙgp·ιΛesρπμ¬·ιNXΜ\[Xt@C
 *
 * @author Kato Yuki
 *
 * @date 2023/11/23
 *
 */
#include "pch.h"
#include "CameraProjection.h"

//----------------------------------------------
// θθ`
//----------------------------------------------

// μpix@j
const float CameraProjection::FOV = 45.0f;
//θOΜ\¦£
const float CameraProjection::NEAR_PLANE = 0.1f;
// Μ\¦£
const float CameraProjection::FAR_PLANE = 200.0f;

// ‘_ΜJΝΝ
const RECT CameraProjection::SIDE_RECT = { -8, 12, 8, -4 };
// ©Ίλ΅_ΜJΝΝ
const RECT CameraProjection::TOPDOWN_RECT = { -6, 6, 6, -6 };
// ©n΅σΤΜJΝΝ
const RECT CameraProjection::OVER_LOOKING_RECT = { -8, 8, 8, -8 };


//------------------------------------------------------------------
/**
 * @brief §ei 3D jΜΛesρπμ¬
 *
 * @param  aspectRatioFζΚδ
 * @return Matrix     F§esρ
 */
DirectX::SimpleMath::Matrix CameraProjection::CreatePerspectiveProjection(const float& aspectRatio)
{
	return DirectX::SimpleMath::Matrix::CreatePerspectiveFieldOfView
	(
		FOV,
		aspectRatio,
		NEAR_PLANE,
		FAR_PLANE
	);
}

//------------------------------------------------------------------
/**
 * @brief ΐsei 2D jΜΛesρπμ¬
 *
 * @param  aspectRatioFζΚδ
 * @param  rect       FJΝΝ
 * @return Matrix     Fΐsesρ
 */
DirectX::SimpleMath::Matrix CameraProjection::CreateOrthographicProjection(const float& aspectRatio, const RECT& rect)
{
	return DirectX::SimpleMath::Matrix::CreateOrthographicOffCenter
	(
		static_cast<float>(rect.left)  * aspectRatio,
		static_cast<float>(rect.right) * aspectRatio,
		static_cast<float>(rect.bottom),
		static_cast<float>(rect.top),
		NEAR_PLANE, // θOΜ\¦£
		FAR_PLANE	// Μ\¦£
	);
}