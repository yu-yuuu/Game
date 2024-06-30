/**
 *
 * @file StageManager.h
 *
 * @brief �X�e�[�W�̃f�[�^�A�������Ǘ�����}�l�[�W���[�N���X�̃w�b�_�[�t�@�C��
 *
 * @author Kato Yuki
 *
 * @date 2023/12/31
 *
 */
#pragma once

#include "Game/Stage/StageData.h"

class StageManager
{
//----------------------------------------------
// �ϐ�
//----------------------------------------------
private:

	// �S�X�e�[�W�f�[�^
	KT::Stage::AllStage m_allStage;

//----------------------------------------------
// �֐�
//----------------------------------------------
public:

	// �R���X�g���N�^
	StageManager(const KT::Stage::AllStage& allStage);
	// �f�X�g���N�^
	~StageManager();

	// �X�e�[�W�T�C�Y�擾
	const KT::Stage::Size& GetStageSize(const int& stageNumber);
	// 3D�X�e�[�W�쐬
	KT::Stage::StageData CreateStage3D(const int& stageNumber, const DirectX::SimpleMath::Vector3& basePosition = DirectX::SimpleMath::Vector3::Zero);
	// 2D�X�e�[�W�쐬
	void Switch3DTo2DStageData(
		const DirectX::SimpleMath::Vector3& stageSize,
		KT::Stage::StageData* stageData,
		const DirectX::SimpleMath::Vector3& cameraDirection);
	// �X�e�[�W�ԍ����X�g�擾
	std::vector<int> GetStageNumberList();
	// �X�e�[�W�ԍ��̃X�e�[�W�����݂��邩�m�F
	bool CheckStageNumber(const int& stageNumber);
	// �X�e�[�W���擾
	int GetStageNum();
};