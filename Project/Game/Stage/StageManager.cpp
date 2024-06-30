/**
 *
 * @file StageManager.cpp
 *
 * @brief �X�e�[�W�̃f�[�^�A�������Ǘ�����}�l�[�W���[�N���X�̃\�[�X�t�@�C��
 *
 * @author Kato Yuki
 *
 * @date 2023/12/31
 *
 */
#include "pch.h"
#include "StageManager.h"
#include "Game/Stage/StageFactory.h"

 //------------------------------------------------------------------
 /**
  * @brief �R���X�g���N�^
  *
  * @param allStage�F�S�X�e�[�W�̐����O�f�[�^
  */
StageManager::StageManager(const KT::Stage::AllStage& allStage)
	: m_allStage(allStage)
{
}

//------------------------------------------------------------------
/**
 * @brief �f�X�g���N�^
 */
StageManager::~StageManager()
{
}

//----------------------------------------F--------------------------
/**
 * @brief �X�e�[�W�T�C�Y�擾
 *
 * @param stageNumber�F�T�C�Y���擾�������X�e�[�W�ԍ�
 * @return Size�F�X�e�[�W�T�C�Y
 */
const KT::Stage::Size& StageManager::GetStageSize(const int& stageNumber)
{
	// �X�e�[�W���݊m�F
	assert(CheckStageNumber(stageNumber) && "�X�e�[�W�ԍ��̃X�e�[�W�����݂��܂���");

	return m_allStage.at(stageNumber).first;
}

//------------------------------------------------------------------
/**
 * @brief 3D�X�e�[�W�f�[�^�쐬
 *
 * @param stageNumber�F�쐬����X�e�[�W�̔ԍ�
 * @param basePosition �F�쐬����X�e�[�W�̊�ʒu
 * @return StageData�F�쐬�����X�e�[�W�f�[�^
 */
KT::Stage::StageData StageManager::CreateStage3D(const int& stageNumber, const DirectX::SimpleMath::Vector3& basePosition)
{
	// �X�e�[�W���݊m�F
	assert(CheckStageNumber(stageNumber) && "�X�e�[�W�ԍ��̃X�e�[�W�����݂��܂���");

	return std::move(StageFactory::Create3DStageData(m_allStage.at(stageNumber), basePosition));
}

//------------------------------------------------------------------
/**
 * @brief 2D�X�e�[�W�֐؂�ւ���
 *
 * @param stageSize�F�X�e�[�W�T�C�Y
 * @param stageData�F3D�X�e�[�W�f�[�^
 * @param cameraDirection�F�J�����̌���
 * @return �Ȃ�
 */
void StageManager::Switch3DTo2DStageData(
	const DirectX::SimpleMath::Vector3& stageSize,
	KT::Stage::StageData* stageData,
	const DirectX::SimpleMath::Vector3& cameraDirection)
{
	StageFactory::Switch3DTo2DStageData(stageSize, stageData, cameraDirection);
}

//------------------------------------------------------------------
/**
 * @brief �X�e�[�W�ԍ����X�g�擾
 *
 * @param �Ȃ�
 * @return �Ȃ�
 */
std::vector<int> StageManager::GetStageNumberList()
{
	std::vector<int> stageNumberList;

	for (const std::pair<int, KT::Stage::SingleStage> stage : m_allStage)
	{
		// 1000�Ԉȍ~�͗V�ׂȂ��X�e�[�W�Ȃ̂Œǉ����Ȃ�
		if (stage.first >= 1000) continue;

		// �X�e�[�W�ԍ����i�[
		stageNumberList.push_back(stage.first);
	}

	return stageNumberList;
}

//------------------------------------------------------------------
/**
 * @brief �X�e�[�W�ԍ��̃X�e�[�W�����݂��邩�m�F
 *
 * @param stageNumber�F�m�F�������X�e�[�W�ԍ�
 * @return true �F���݂���
 * @return false�F���݂��Ȃ�
 */
bool StageManager::CheckStageNumber(const int& stageNumber)
{
	auto count = std::count_if(m_allStage.begin(), m_allStage.end(),
		[&](std::pair<int, KT::Stage::SingleStage> stage)
		{ return stage.first == stageNumber; } );

	return count == 1;
}

//------------------------------------------------------------------
/**
 * @brief �X�e�[�W���擾
 *
 * @param  �Ȃ�
 * @return int�F�X�e�[�W��
 */
int StageManager::GetStageNum()
{
	std::vector<int> stage = GetStageNumberList();

	return static_cast<int>(stage.size());
}
