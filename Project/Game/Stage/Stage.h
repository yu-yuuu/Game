/**
 *
 * @file Stage.h
 *
 * @brief �X�e�[�W���\���N���X�̃w�b�_�[�t�@�C��
 *
 * @author Kato Yuki
 *
 * @date 2023/12/28
 *
 */
#pragma once

#include <vector>
#include <unordered_map>
#include <functional>
#include "Game/Stage/StageData.h"

class IBlock;

class Stage
{
//----------------------------------------------
// �ϐ�
//----------------------------------------------
private:

	// �X�e�[�W�ԍ�
	int m_stageNumber;
	// �X�e�[�W�T�C�Y
	KT::Stage::Size m_size;
	// �X�e�[�W�f�[�^
	KT::Stage::StageData m_stage;

//----------------------------------------------
// �֐�
//----------------------------------------------
public:

	// �R���X�g���N�^
	Stage(int stageNumber, KT::Stage::Size size);
	// �f�X�g���N�^
	~Stage();

	// ������
	void Initialize(std::function<void(DirectX::IEffect* effect)> effect = nullptr);
	// �X�V
	void Update();
	// �`��
	void Render(
		DirectX::SimpleMath::Matrix view,
		DirectX::SimpleMath::Matrix projection,
		std::function<void()> custom = nullptr
	);
	// �㏈��
	void Finalize();
	
	// �X�e�[�W�f�[�^�擾
	KT::Stage::StageData* GetStageData();
	// �X�e�[�W�f�[�^�ݒ�
	void SetStageData(KT::Stage::StageData stage);
	// �X�e�[�W�ԍ��擾
	const int GetStageNumber() const;
	// �X�e�[�W�T�C�Y�擾�A�ݒ�
	KT::Stage::Size GetStageSize() const;
	void SetStageSize(const KT::Stage::Size& size);
	// �X�e�[�W���폜����
	void ClearStage();
	// �X�e�[�W�̃A�N�e�B�u��Ԃ�ݒ肷��
	void SetStageActive(bool isActive);
};
