/**
 *
 * @file StageFactory.cpp
 *
 * @brief ステージの生成を行うクラスのソースファイル
 *
 * @author Kato Yuki
 *
 * @date 2023/12/17
 *
 */
#include "pch.h"
#include "StageFactory.h"

#include <sstream>
#include <cmath>
#include "Game/Block/BlockType.h"
#include "Game/Block/IBlock.h"
#include "Game/Block/BlockFactory.h"
#include "Game/MyLibrary/Collision/Collider.h"
#include "Game/MyLibrary/Collision/BoxCollider.h"

#include "Game/MyLibrary/Utility/MyUtility.h"
#include "Game/MyLibrary/File/FileManager.h"

using namespace DirectX;

//----------------------------------------------
// 定数定義
//----------------------------------------------

// レイの位置調整用
const float StageFactory::RAY_POSITION_ADJUSTMENT = 2.0f;

//------------------------------------------------------------------
/**
 * @brief ステージデータの読み込み
 *
 * @param  path			：ステージデータパス
 * @return StageDataList：作成したステージリスト
 */
KT::Stage::AllStage StageFactory::CreateStageList(std::ifstream ifs)
{
	// 変数宣言
	KT::Stage::AllStage list;					// ステージデータ返却用
	KT::Stage::Size		size;					// ステージサイズ
	int					stageNumber = 0;		// ステージ番号
	std::string			line;					// 列データ取得用

	// ファイル読み込み
	while (std::getline(ifs, line))
	{
		// ステージの先頭まで移動する
		if (line.find(KT::File::STAGE_DATA_TOP) == std::string::npos)
			continue;

		// ステージ番号を取得する
		stageNumber = std::stoi(line.substr(KT::File::STAGE_DATA_TOP.size(), *(line.end() - 1)));
		// ステージサイズを取得する
		std::getline(ifs, line);
		FileManager::SeparateData(line) >> size.x >> size.y >> size.z;
		// ステージデータ作成、格納
		list[stageNumber] = { size, CreateStageData(ifs, size) };
	}

	// ファイルを閉じる
	ifs.close();

	return list;
}

//------------------------------------------------------------------
/**
 * @brief ステージデータ作成
 *
 * @param  ifs  ：読み込んでいるステージデータファイル
 * @param  size ：作成するステージのサイズ
 * @return Stage：作成したステージデータ
 */
KT::Stage::BlockID StageFactory::CreateStageData(std::ifstream& ifs, const KT::Stage::Size& size)
{
	// 変数宣言
	KT::Stage::BlockID  stage;	// データ返却用
	std::string			line;	// 列データ取得用
	std::stringstream	ss;		// 列データ読み込み用
	std::stringstream	ssGrid;		// 1マスデータ読み込み用


	// ステージサイズ分データ容量を確保する
	std::vector<std::vector<int>> vec;
	vec.resize(size.y, std::vector<int>(size.z, 0));
	stage.resize(size.x, vec);

	// ステージデータ読み込み
	for (int z = 0; z < size.z; z++)
	{
		// カンマ区切りデータ取得用
		std::string comma;
		// １列読み込む
		std::getline(ifs, line);
		// \r が入っていたら削除する
		if (line.find('\r') != std::string::npos) line.erase(line.find('\r'));
		// カンマでデータを区切る
		ss = FileManager::SeparateData(line);

		for (int x = 0; x < size.x; x++)
		{
			// ハイフン区切りデータ取得用
			std::string hyphen;	
			// データ取得
			std::getline(ss, comma, ' ');

			// もしデータが入っていなかったら次へ
			if (comma.empty()) continue;

			// ハイフンの数を数える(データ数はハイフン + 1)
			int hyphenNum = static_cast<int>(std::count(comma.begin(), comma.end(), '-') + 1);
			// ハイフンで区切る
			ssGrid = FileManager::SeparateData(comma, '-');

			for (int y = 0; y < hyphenNum; y++)
			{
				// 区切った文字を受け取る
				std::getline(ssGrid, hyphen, ' ');
				// ブロックの番号格納					
				stage[x][y][z] = std::stoi(hyphen);
			}
		}
	}

	return stage;
}

//------------------------------------------------------------------
/**
 * @brief 3Dステージデータの作成
 *
 * @param  stage  ：生成するステージのデータ
 * @param basePosition ：作成するステージの基準位置
 * @return StageData：作成した3Dステージデータ
 */
KT::Stage::StageData StageFactory::Create3DStageData(const KT::Stage::SingleStage& stage, const DirectX::SimpleMath::Vector3& basePosition)
{	
	// データを受け取る
	KT::Stage::Size		size       = stage.first;
	KT::Stage::BlockID	stageBlock = stage.second;
	// 返却用データ
	KT::Stage::StageData stage3D;
	// 容量を確保する
	stage3D.resize(size.x * size.y * size.z);

	for (int x = 0; x < size.x; x++)
	{
		for (int y = 0; y < size.y; y++)
		{
			for (int z = 0; z < size.z; z++)
			{
				// ブロックの種類を取得
				KT::Block::Type type = static_cast<KT::Block::Type>(stageBlock[x][y][z]);

				// 未設定なら作成しない
				if (type == KT::Block::Type::NONE) continue;

				// 位置作成
				SimpleMath::Vector3 position =
				{
					basePosition.x + static_cast<float>(x),
					basePosition.y + static_cast<float>(y),
					basePosition.z + static_cast<float>(z)
				};

				// ブロック作成
				std::unique_ptr<Block> block = BlockFactory::CreateBlock(type, position);
				// 3次元を1次元に直す
				int index = (x * size.y * size.z) + (y * size.z + z);
				// 格納
				stage3D[index] = std::move(block);
			}
		}
	}

	// 空の物を削除する
	stage3D.erase
	(
		std::remove_if(stage3D.begin(), stage3D.end(),
			[](std::unique_ptr<Block>& block)
			{
				return block == nullptr;
			}
		), stage3D.end()
	);

	return std::move(stage3D);
}

//------------------------------------------------------------------
/**
 * @brief 2Dステージデータの作成
 *
 * @param  stageSize      ：ステージサイズ
 * @param  stageData      ：3Dステージデータ
 * @param  cameraDirection：カメラの方向
 * @return StageData：作成した2Dステージデータ
 */
void StageFactory::Switch3DTo2DStageData(
	const DirectX::SimpleMath::Vector3& stageSize,
	KT::Stage::StageData* stageData,
	const DirectX::SimpleMath::Vector3& cameraDirection)
{
	// レイの生成
	SimpleMath::Ray ray;
	ray.direction = cameraDirection;
	// レイが移動する方向
	SimpleMath::Vector3 moveDir = SimpleMath::Vector3::One - KT::MyUtility::AbsVector(cameraDirection);
	// 移動する要素数を計算
	SimpleMath::Vector3 indexF = stageSize * moveDir;
	// 1回はループに入るように 0 を 1 にする
	indexF = SimpleMath::Vector3::Max(indexF, SimpleMath::Vector3::One);
	// int型に変換、誤差は四捨五入で丸め込む
	int index[3];
	index[0] = static_cast<int>(std::round(indexF.x));
	index[1] = static_cast<int>(std::round(indexF.y));
	index[2] = static_cast<int>(std::round(indexF.z));

	// レイ判定
	for (int x = 0; x < index[0]; x++)
	{
		for (int y = 0; y < index[1]; y++)
		{
			for (int z = 0; z < index[2]; z++)
			{
				SimpleMath::Vector3 xyz =
				{
					static_cast<float>(x),
					static_cast<float>(y),
					static_cast<float>(z)
				};

				// レイの位置を計算
				SimpleMath::Vector3 pos = xyz * moveDir + stageSize * RAY_POSITION_ADJUSTMENT * cameraDirection * -1.0f;
				// 位置を設定
				ray.position = pos;
				// レイが当たった一番近いブロックを取得
				Block* block = CheckRay(stageData, ray);
				// アクティブ状態へ
				if (block) block->SetActive(true);
			}
		}
	}
}

//------------------------------------------------------------------
/**
 * @brief レイに当たった一番近いブロックを取得する
 *
 * @param stageData：3Dステージデータ
 * @param ray：使用するレイ
 * @return Block*：レイに当たった一番近いブロック
 */
Block* StageFactory::CheckRay(
	KT::Stage::StageData* stageData,
	const DirectX::SimpleMath::Ray& ray)
{
	// レイに当たったブロック取得用
	std::vector<std::pair<std::unique_ptr<Block>&, float>> hitBlock;

	float distance = 0.0f;

	for (std::unique_ptr<Block>& block : *stageData)
	{
		// 当たり判定を取らないなら飛ばす
		if (block->GetCollisionMode() == KT::Block::CollisionMode::NONE) continue;

		// 判定ボックス取得
		Collider* collider = block->GetCollider();
		BoundingBox bb = dynamic_cast<BoxCollider*>(collider)->GetBoundingBox();
		
		// 当たっていなかったら飛ばす
		if (!ray.Intersects(bb, distance)) continue;

		// 当たっていたら保存
		hitBlock.push_back({ block, distance });
	}

	// レイが当たっていなかったら終了
	if (hitBlock.empty()) return nullptr;

	// 距離が一番短いもの取り出す
	auto min = std::min_element(hitBlock.begin(), hitBlock.end(),
		[](auto lhs, auto rhs)
		{
			return lhs.second < rhs.second;
		}
	);

	return min->first.get();
}

