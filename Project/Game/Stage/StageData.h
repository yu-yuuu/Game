/**
 *
 * @file StageData.h
 *
 * @brief ステージに関する処理に使用する物を宣言するヘッダー
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
// 自作の共通定義を扱う名前空間
//----------------------------------------------
namespace KT
{
	//----------------------------------------------
	// ステージ関係の物を扱う名前空間
	//----------------------------------------------
	namespace Stage
	{

		// ステージブロックの番号データ
		using BlockID = std::vector<std::vector<std::vector<int>>>;

		// ステージサイズ
		struct Size
		{
			int x;// x方向の大きさ
			int y;// y方向の大きさ
			int z;// z方向の大きさ

			// Vector3型で取得
			DirectX::SimpleMath::Vector3 GetVector3()
			{
				DirectX::SimpleMath::Vector3 vec;
				vec.x = static_cast<float>(this->x);
				vec.y = static_cast<float>(this->y);
				vec.z = static_cast<float>(this->z);
				return vec;
			}
		};


		// ステージ１つの番号データ
		using SingleStage = std::pair<Size, BlockID>;

		// 全ステージの番号データ
		using AllStage = std::map<int, SingleStage>;

		// 生成されたブロック（unique_ptr ver）
		//using StageBlock_U = std::unique_ptr<Block>;

		// 生成されたブロック（shared_ptr ver）
		//using StageBlock_S = std::shared_ptr<Block>;

		// 3Dステージデータ
		//template <typename T>
		//using Stage3D = std::vector<T>;

		// ステージデータ
		// 全てをunique_ptrにする為
		using StageData = std::vector<std::unique_ptr<class Block>>;
	}
}