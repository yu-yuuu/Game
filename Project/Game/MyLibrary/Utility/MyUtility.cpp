/**
 *
 * @file MyUtility.cpp
 *
 * @brief ����̔ėp�֐����W�߂��N���X�̃\�[�X�t�@�C��
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
 * @brief �x�N�g���̐�Βl�����߂�
 *
 * @param  vec    �F��Βl�ɕϊ��������x�N�g��
 * @return Vector3�F��Βl�ɕϊ���̃x�N�g��
 */
DirectX::SimpleMath::Vector3 KT::MyUtility::AbsVector(const DirectX::SimpleMath::Vector3& vec)
{
	SimpleMath::Vector3 ret = vec;

	// �}�C�i�X�̕��̓v���X�֕ϊ�
	if (ret.x < 0.0f) ret.x *= -1.0f;
	if (ret.y < 0.0f) ret.y *= -1.0f;
	if (ret.z < 0.0f) ret.z *= -1.0f;

	return ret;
}

//------------------------------------------------------------------
/**
 * @brief �x�N�g���̐������̂݋��߂�
 *
 * @param  vec    �F�������̂݋��߂����x�N�g��
 * @return Vector3�F�������݂̂ɂ����x�N�g��
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
 * @brief �x�N�g���t���O�𔽓](0�Ffalse, 1�Ftrue)
 *
 * @param  vec   �F���]���������x�N�g���t���O
 * @return Vectr3�F���]��̃x�N�g���t���O
 */
DirectX::SimpleMath::Vector3 KT::MyUtility::InverseFlag(const DirectX::SimpleMath::Vector3& vec)
{
	return DirectX::SimpleMath::Vector3::One - AbsVector(vec);
}

//------------------------------------------------------------------
/**
 * @brief �x�N�g���̃N�����v����
 *
 * @param  value  �F�N�����v���������������x�N�g��
 * @param  min    �F�Œ�l
 * @param  max    �F�ō��l
 * @return Vector3�F�N�����v��̃x�N�g��
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
 * @brief 6�����x�N�g���̌덷���Ȃ���
 * @brief �㉺���E����O������ 0��1�݂̂̃x�N�g��
 *
 * @param  vec    �F�덷���Ȃ��������x�N�g��
 * @return Vector3�F�덷���Ȃ�������̃x�N�g��
 */
DirectX::SimpleMath::Vector3 KT::MyUtility::EliminateDirectionError(const DirectX::SimpleMath::Vector3& vec)
{
	// �x�N�g���Ƃ̋����𑪂�
	float distX = SimpleMath::Vector3::DistanceSquared(SimpleMath::Vector3::UnitX, KT::MyUtility::AbsVector(vec));
	float distY = SimpleMath::Vector3::DistanceSquared(SimpleMath::Vector3::UnitY, KT::MyUtility::AbsVector(vec));
	float distZ = SimpleMath::Vector3::DistanceSquared(SimpleMath::Vector3::UnitZ, KT::MyUtility::AbsVector(vec));

	// �ǂ̕����̃x�N�g���Ɉ�ԋ߂����m�F
	bool x = distX < distY && distX < distZ;
	bool y = distY < distX && distY < distZ;
	bool z = distZ < distX && distZ < distY;
	// ��ԋ߂��x�N�g�����擾
	SimpleMath::Vector3 ret;
	if      (x) ret = SimpleMath::Vector3::UnitX;
	else if (y) ret = SimpleMath::Vector3::UnitY;
	else if (z) ret = SimpleMath::Vector3::UnitZ;
	// �}�C�i�X�̕������}�C�i�X��
	if (vec.x < 0.0f) ret.x *= -1.0f;
	if (vec.y < 0.0f) ret.y *= -1.0f;
	if (vec.z < 0.0f) ret.z *= -1.0f;

	return ret;
}

//------------------------------------------------------------------
/**
 * @brief 2��float�^�ϐ����قړ������m�F����
 *
 * @param  f1   �F�قړ������m�F������float�ϐ��P
 * @param  f2   �F�قړ������m�F������float�ϐ��Q
 * @return true �F�قړ�����
 * @return false�F�������Ȃ�
 */
bool KT::MyUtility::FloatPresqueEqual(const float& f1, const float& f2)
{
	return std::fabsf(f1 - f2) < std::numeric_limits<float>::epsilon();
}

//------------------------------------------------------------------
/**
 * @brief string ���� wstring �֕ϊ�
 *
 * @param  str    �F�ϊ���������string������
 * @return wstring�F�ϊ���̕�����
 */
std::wstring KT::MyUtility::StringToWide(const std::string& str)
{
	return std::wstring(str.begin(), str.end());
}

//------------------------------------------------------------------
/**
 * @brief string ���� 16�i���̐��l�֕ϊ�
 *
 * @param  str�F�ϊ���������string������
 * @return int�F�ϊ���̐��l
 */
int KT::MyUtility::ConvertToHexadecimal(const std::string& str)
{
	return stoi(str, nullptr, 16);
}