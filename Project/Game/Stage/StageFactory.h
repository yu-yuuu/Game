/**
 *
 * @file StageFactory.h
 *
 * @brief �X�e�[�W�̐������s���N���X�̃w�b�_�[�t�@�C��
 *
 * @author Kato Yuki
 *
 * @date 2023/12/17
 *
 */
#pragma once

#include <unordered_map>
#include <string>
#include <vector>
#include <array>
#include <fstream>

#include "Game/Stage/StageData.h"


class IBlock;


class StageFactory
{
//----------------------------------------------
// �萔
//----------------------------------------------

	// ���C�̈ʒu�����p
	static const float RAY_POSITION_ADJUSTMENT;

//----------------------------------------------
// �֐�
//----------------------------------------------
public:

	// �X�e�[�W�f�[�^�̓ǂݍ���
	static KT::Stage::AllStage CreateStageList(std::ifstream ifs);
	// �X�e�[�W�f�[�^�쐬
	static KT::Stage::BlockID CreateStageData(std::ifstream& ifs, const KT::Stage::Size& size);
	// 3D�X�e�[�W�̍쐬
	static KT::Stage::StageData Create3DStageData(const KT::Stage::SingleStage& stage, const DirectX::SimpleMath::Vector3& basePosition);
	// 2D�X�e�[�W�֐؂�ւ���
	static void Switch3DTo2DStageData(
		const DirectX::SimpleMath::Vector3& stageSize,
		KT::Stage::StageData* stageData,
		const DirectX::SimpleMath::Vector3& cameraDirection);
	// ���C�ɓ���������ԋ߂��u���b�N���擾����
	static Block* CheckRay(
		KT::Stage::StageData* stageData,
		const DirectX::SimpleMath::Ray& ray
	);
};

