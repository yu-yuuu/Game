/**
 *
 * @file StageData.h
 *
 * @brief �X�e�[�W�Ɋւ��鏈���Ɏg�p���镨��錾����w�b�_�[
 *
 * @author Kato Yuki
 *
 * @date 2023/12/31
 *
 */
#pragma once

#include <memory>
#include <string>
#include <array>
#include <vector>
#include <map>
#include <unordered_map>

#include "Game/Block/Block.h"

//----------------------------------------------
// ����̋��ʒ�`���������O���
//----------------------------------------------
namespace KT
{
	//----------------------------------------------
	// �X�e�[�W�֌W�̕����������O���
	//----------------------------------------------
	namespace Stage
	{

		// �X�e�[�W�u���b�N�̔ԍ��f�[�^
		using BlockID = std::vector<std::vector<std::vector<int>>>;

		// �X�e�[�W�T�C�Y
		struct Size
		{
			int x;// x�����̑傫��
			int y;// y�����̑傫��
			int z;// z�����̑傫��

			// Vector3�^�Ŏ擾
			DirectX::SimpleMath::Vector3 GetVector3()
			{
				DirectX::SimpleMath::Vector3 vec;
				vec.x = static_cast<float>(this->x);
				vec.y = static_cast<float>(this->y);
				vec.z = static_cast<float>(this->z);
				return vec;
			}
		};


		// �X�e�[�W�P�̔ԍ��f�[�^
		using SingleStage = std::pair<Size, BlockID>;

		// �S�X�e�[�W�̔ԍ��f�[�^
		using AllStage = std::map<int, SingleStage>;

		// �������ꂽ�u���b�N�iunique_ptr ver�j
		//using StageBlock_U = std::unique_ptr<Block>;

		// �������ꂽ�u���b�N�ishared_ptr ver�j
		//using StageBlock_S = std::shared_ptr<Block>;

		// 3D�X�e�[�W�f�[�^
		//template <typename T>
		//using Stage3D = std::vector<T>;

		// �X�e�[�W�f�[�^
		// �S�Ă�unique_ptr�ɂ����
		using StageData = std::vector<std::unique_ptr<class Block>>;
	}
}