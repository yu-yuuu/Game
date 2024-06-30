/**
 *
 * @file MyUtility.cpp
 *
 * @brief 自作の汎用関数を集めたクラスのソースファイル
 *
 * @author Kato Yuki
 *
 * @date 2023/12/12
 *
 */
#include "pch.h"
#include "MyUtility.h"
#include <cmath>
#include <limits>

using namespace DirectX;

//------------------------------------------------------------------
/**
 * @brief ベクトルの絶対値を求める
 *
 * @param  vec    ：絶対値に変換したいベクトル
 * @return Vector3：絶対値に変換後のベクトル
 */
DirectX::SimpleMath::Vector3 KT::MyUtility::AbsVector(const DirectX::SimpleMath::Vector3& vec)
{
	SimpleMath::Vector3 ret = vec;

	// マイナスの物はプラスへ変換
	if (ret.x < 0.0f) ret.x *= -1.0f;
	if (ret.y < 0.0f) ret.y *= -1.0f;
	if (ret.z < 0.0f) ret.z *= -1.0f;

	return ret;
}

//------------------------------------------------------------------
/**
 * @brief ベクトルの整数部のみ求める
 *
 * @param  vec    ：整数部のみ求めたいベクトル
 * @return Vector3：整数部のみにしたベクトル
 */
DirectX::SimpleMath::Vector3 KT::MyUtility::ModVector(const DirectX::SimpleMath::Vector3& vec)
{
	SimpleMath::Vector3 ret;

	std::modf(vec.x, &ret.x);
	std::modf(vec.y, &ret.y);
	std::modf(vec.z, &ret.z);

	return ret;
}

//------------------------------------------------------------------
/**
 * @brief ベクトルフラグを反転(0：false, 1：true)
 *
 * @param  vec   ：反転させたいベクトルフラグ
 * @return Vectr3：反転後のベクトルフラグ
 */
DirectX::SimpleMath::Vector3 KT::MyUtility::InverseFlag(const DirectX::SimpleMath::Vector3& vec)
{
	return DirectX::SimpleMath::Vector3::One - AbsVector(vec);
}

//------------------------------------------------------------------
/**
 * @brief ベクトルのクランプ処理
 *
 * @param  value  ：クランプ処理を書けたいベクトル
 * @param  min    ：最低値
 * @param  max    ：最高値
 * @return Vector3：クランプ後のベクトル
 */
DirectX::SimpleMath::Vector3 KT::MyUtility::Clamp(
	const DirectX::SimpleMath::Vector3& value,
	const DirectX::SimpleMath::Vector3& min,
	const DirectX::SimpleMath::Vector3& max)
{
	SimpleMath::Vector3 ret;

	ret.x = std::min(max.x, std::max(value.x, min.x));
	ret.y = std::min(max.y, std::max(value.y, min.y));
	ret.z = std::min(max.z, std::max(value.z, min.z));

	return ret;
}

//------------------------------------------------------------------
/**
 * @brief 6方向ベクトルの誤差をなくす
 * @brief 上下左右奥手前方向の 0と1のみのベクトル
 *
 * @param  vec    ：誤差をなくしたいベクトル
 * @return Vector3：誤差をなくした後のベクトル
 */
DirectX::SimpleMath::Vector3 KT::MyUtility::EliminateDirectionError(const DirectX::SimpleMath::Vector3& vec)
{
	// ベクトルとの距離を測る
	float distX = SimpleMath::Vector3::DistanceSquared(SimpleMath::Vector3::UnitX, KT::MyUtility::AbsVector(vec));
	float distY = SimpleMath::Vector3::DistanceSquared(SimpleMath::Vector3::UnitY, KT::MyUtility::AbsVector(vec));
	float distZ = SimpleMath::Vector3::DistanceSquared(SimpleMath::Vector3::UnitZ, KT::MyUtility::AbsVector(vec));

	// どの方向のベクトルに一番近いか確認
	bool x = distX < distY && distX < distZ;
	bool y = distY < distX && distY < distZ;
	bool z = distZ < distX && distZ < distY;
	// 一番近いベクトルを取得
	SimpleMath::Vector3 ret;
	if      (x) ret = SimpleMath::Vector3::UnitX;
	else if (y) ret = SimpleMath::Vector3::UnitY;
	else if (z) ret = SimpleMath::Vector3::UnitZ;
	// マイナスの方向をマイナスに
	if (vec.x < 0.0f) ret.x *= -1.0f;
	if (vec.y < 0.0f) ret.y *= -1.0f;
	if (vec.z < 0.0f) ret.z *= -1.0f;

	return ret;
}

//------------------------------------------------------------------
/**
 * @brief 2つのfloat型変数がほぼ同じか確認する
 *
 * @param  f1   ：ほぼ同じか確認したいfloat変数１
 * @param  f2   ：ほぼ同じか確認したいfloat変数２
 * @return true ：ほぼ等しい
 * @return false：等しくない
 */
bool KT::MyUtility::FloatPresqueEqual(const float& f1, const float& f2)
{
	return std::fabsf(f1 - f2) < std::numeric_limits<float>::epsilon();
}

//------------------------------------------------------------------
/**
 * @brief string から wstring へ変換
 *
 * @param  str    ：変換させたいstring文字列
 * @return wstring：変換後の文字列
 */
std::wstring KT::MyUtility::StringToWide(const std::string& str)
{
	return std::wstring(str.begin(), str.end());
}

//------------------------------------------------------------------
/**
 * @brief string から 16進数の数値へ変換
 *
 * @param  str：変換させたいstring文字列
 * @return int：変換後の数値
 */
int KT::MyUtility::ConvertToHexadecimal(const std::string& str)
{
	return stoi(str, nullptr, 16);
}