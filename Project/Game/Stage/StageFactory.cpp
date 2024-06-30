/**
 *
 * @file StageFactory.cpp
 *
 * @brief �X�e�[�W�̐������s���N���X�̃\�[�X�t�@�C��
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
// �萔��`
//----------------------------------------------

// ���C�̈ʒu�����p
const float StageFactory::RAY_POSITION_ADJUSTMENT = 2.0f;

//------------------------------------------------------------------
/**
 * @brief �X�e�[�W�f�[�^�̓ǂݍ���
 *
 * @param  path			�F�X�e�[�W�f�[�^�p�X
 * @return StageDataList�F�쐬�����X�e�[�W���X�g
 */
KT::Stage::AllStage StageFactory::CreateStageList(std::ifstream ifs)
{
	// �ϐ��錾
	KT::Stage::AllStage list;					// �X�e�[�W�f�[�^�ԋp�p
	KT::Stage::Size		size;					// �X�e�[�W�T�C�Y
	int					stageNumber = 0;		// �X�e�[�W�ԍ�
	std::string			line;					// ��f�[�^�擾�p

	// �t�@�C���ǂݍ���
	while (std::getline(ifs, line))
	{
		// �X�e�[�W�̐擪�܂ňړ�����
		if (line.find(KT::File::STAGE_DATA_TOP) == std::string::npos)
			continue;

		// �X�e�[�W�ԍ����擾����
		stageNumber = std::stoi(line.substr(KT::File::STAGE_DATA_TOP.size(), *(line.end() - 1)));
		// �X�e�[�W�T�C�Y���擾����
		std::getline(ifs, line);
		FileManager::SeparateData(line) >> size.x >> size.y >> size.z;
		// �X�e�[�W�f�[�^�쐬�A�i�[
		list[stageNumber] = { size, CreateStageData(ifs, size) };
	}

	// �t�@�C�������
	ifs.close();

	return list;
}

//------------------------------------------------------------------
/**
 * @brief �X�e�[�W�f�[�^�쐬
 *
 * @param  ifs  �F�ǂݍ���ł���X�e�[�W�f�[�^�t�@�C��
 * @param  size �F�쐬����X�e�[�W�̃T�C�Y
 * @return Stage�F�쐬�����X�e�[�W�f�[�^
 */
KT::Stage::BlockID StageFactory::CreateStageData(std::ifstream& ifs, const KT::Stage::Size& size)
{
	// �ϐ��錾
	KT::Stage::BlockID  stage;	// �f�[�^�ԋp�p
	std::string			line;	// ��f�[�^�擾�p
	std::stringstream	ss;		// ��f�[�^�ǂݍ��ݗp
	std::stringstream	ssGrid;		// 1�}�X�f�[�^�ǂݍ��ݗp


	// �X�e�[�W�T�C�Y���f�[�^�e�ʂ��m�ۂ���
	std::vector<std::vector<int>> vec;
	vec.resize(size.y, std::vector<int>(size.z, 0));
	stage.resize(size.x, vec);

	// �X�e�[�W�f�[�^�ǂݍ���
	for (int z = 0; z < size.z; z++)
	{
		// �J���}��؂�f�[�^�擾�p
		std::string comma;
		// �P��ǂݍ���
		std::getline(ifs, line);
		// \r �������Ă�����폜����
		if (line.find('\r') != std::string::npos) line.erase(line.find('\r'));
		// �J���}�Ńf�[�^����؂�
		ss = FileManager::SeparateData(line);

		for (int x = 0; x < size.x; x++)
		{
			// �n�C�t����؂�f�[�^�擾�p
			std::string hyphen;	
			// �f�[�^�擾
			std::getline(ss, comma, ' ');

			// �����f�[�^�������Ă��Ȃ������玟��
			if (comma.empty()) continue;

			// �n�C�t���̐��𐔂���(�f�[�^���̓n�C�t�� + 1)
			int hyphenNum = static_cast<int>(std::count(comma.begin(), comma.end(), '-') + 1);
			// �n�C�t���ŋ�؂�
			ssGrid = FileManager::SeparateData(comma, '-');

			for (int y = 0; y < hyphenNum; y++)
			{
				// ��؂����������󂯎��
				std::getline(ssGrid, hyphen, ' ');
				// �u���b�N�̔ԍ��i�[					
				stage[x][y][z] = std::stoi(hyphen);
			}
		}
	}

	return stage;
}

//------------------------------------------------------------------
/**
 * @brief 3D�X�e�[�W�f�[�^�̍쐬
 *
 * @param  stage  �F��������X�e�[�W�̃f�[�^
 * @param basePosition �F�쐬����X�e�[�W�̊�ʒu
 * @return StageData�F�쐬����3D�X�e�[�W�f�[�^
 */
KT::Stage::StageData StageFactory::Create3DStageData(const KT::Stage::SingleStage& stage, const DirectX::SimpleMath::Vector3& basePosition)
{	
	// �f�[�^���󂯎��
	KT::Stage::Size		size       = stage.first;
	KT::Stage::BlockID	stageBlock = stage.second;
	// �ԋp�p�f�[�^
	KT::Stage::StageData stage3D;
	// �e�ʂ��m�ۂ���
	stage3D.resize(size.x * size.y * size.z);

	for (int x = 0; x < size.x; x++)
	{
		for (int y = 0; y < size.y; y++)
		{
			for (int z = 0; z < size.z; z++)
			{
				// �u���b�N�̎�ނ��擾
				KT::Block::Type type = static_cast<KT::Block::Type>(stageBlock[x][y][z]);

				// ���ݒ�Ȃ�쐬���Ȃ�
				if (type == KT::Block::Type::NONE) continue;

				// �ʒu�쐬
				SimpleMath::Vector3 position =
				{
					basePosition.x + static_cast<float>(x),
					basePosition.y + static_cast<float>(y),
					basePosition.z + static_cast<float>(z)
				};

				// �u���b�N�쐬
				std::unique_ptr<Block> block = BlockFactory::CreateBlock(type, position);
				// 3������1�����ɒ���
				int index = (x * size.y * size.z) + (y * size.z + z);
				// �i�[
				stage3D[index] = std::move(block);
			}
		}
	}

	// ��̕����폜����
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
 * @brief 2D�X�e�[�W�f�[�^�̍쐬
 *
 * @param  stageSize      �F�X�e�[�W�T�C�Y
 * @param  stageData      �F3D�X�e�[�W�f�[�^
 * @param  cameraDirection�F�J�����̕���
 * @return StageData�F�쐬����2D�X�e�[�W�f�[�^
 */
void StageFactory::Switch3DTo2DStageData(
	const DirectX::SimpleMath::Vector3& stageSize,
	KT::Stage::StageData* stageData,
	const DirectX::SimpleMath::Vector3& cameraDirection)
{
	// ���C�̐���
	SimpleMath::Ray ray;
	ray.direction = cameraDirection;
	// ���C���ړ��������
	SimpleMath::Vector3 moveDir = SimpleMath::Vector3::One - KT::MyUtility::AbsVector(cameraDirection);
	// �ړ�����v�f�����v�Z
	SimpleMath::Vector3 indexF = stageSize * moveDir;
	// 1��̓��[�v�ɓ���悤�� 0 �� 1 �ɂ���
	indexF = SimpleMath::Vector3::Max(indexF, SimpleMath::Vector3::One);
	// int�^�ɕϊ��A�덷�͎l�̌ܓ��Ŋۂߍ���
	int index[3];
	index[0] = static_cast<int>(std::round(indexF.x));
	index[1] = static_cast<int>(std::round(indexF.y));
	index[2] = static_cast<int>(std::round(indexF.z));

	// ���C����
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

				// ���C�̈ʒu���v�Z
				SimpleMath::Vector3 pos = xyz * moveDir + stageSize * RAY_POSITION_ADJUSTMENT * cameraDirection * -1.0f;
				// �ʒu��ݒ�
				ray.position = pos;
				// ���C������������ԋ߂��u���b�N���擾
				Block* block = CheckRay(stageData, ray);
				// �A�N�e�B�u��Ԃ�
				if (block) block->SetActive(true);
			}
		}
	}
}

//------------------------------------------------------------------
/**
 * @brief ���C�ɓ���������ԋ߂��u���b�N���擾����
 *
 * @param stageData�F3D�X�e�[�W�f�[�^
 * @param ray�F�g�p���郌�C
 * @return Block*�F���C�ɓ���������ԋ߂��u���b�N
 */
Block* StageFactory::CheckRay(
	KT::Stage::StageData* stageData,
	const DirectX::SimpleMath::Ray& ray)
{
	// ���C�ɓ��������u���b�N�擾�p
	std::vector<std::pair<std::unique_ptr<Block>&, float>> hitBlock;

	float distance = 0.0f;

	for (std::unique_ptr<Block>& block : *stageData)
	{
		// �����蔻������Ȃ��Ȃ��΂�
		if (block->GetCollisionMode() == KT::Block::CollisionMode::NONE) continue;

		// ����{�b�N�X�擾
		Collider* collider = block->GetCollider();
		BoundingBox bb = dynamic_cast<BoxCollider*>(collider)->GetBoundingBox();
		
		// �������Ă��Ȃ��������΂�
		if (!ray.Intersects(bb, distance)) continue;

		// �������Ă�����ۑ�
		hitBlock.push_back({ block, distance });
	}

	// ���C���������Ă��Ȃ�������I��
	if (hitBlock.empty()) return nullptr;

	// ��������ԒZ�����̎��o��
	auto min = std::min_element(hitBlock.begin(), hitBlock.end(),
		[](auto lhs, auto rhs)
		{
			return lhs.second < rhs.second;
		}
	);

	return min->first.get();
}

