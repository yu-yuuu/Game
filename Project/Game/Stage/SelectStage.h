/**
 *
 * @file SelectStage.h
 *
 * @brief �Z���N�g�V�[���̃X�e�[�W�N���X�̃w�b�_�[�|�t�@�C��
 *
 * @author Kato Yuki
 *
 * @date 2024/1/21
 *
 */
#pragma once

#include <vector>
#include <unordered_map>
#include "Game/Stage/Stage.h"
#include "Game/Stage/StageData.h"

class SelectStage : public Stage
{
//----------------------------------------------
// �萔
//----------------------------------------------
private:

	// �X�e�[�W�̐����ʒu�̊Ԋu
	const float STAGE_HEIGHT_OFFSET = 100.0f;

//----------------------------------------------
// �ϐ�
//----------------------------------------------
private:

	// �X�e�[�W�f�[�^���X�g
	std::unordered_map<int, KT::Stage::StageData> m_stageList;
	// �X�e�[�W�ԍ����X�g
	std::vector<int> m_stageNumberList;
	// �I�𒆂̃X�e�[�W�ԍ�
	int m_selectStageNumber;
	// �؂�ւ���̃X�e�[�W
	std::unique_ptr<Stage> m_nextStage;
	// �؂�ւ���̃X�e�[�W�̊�ʒu
	DirectX::SimpleMath::Vector3 m_nextBasePosition;


//----------------------------------------------
// �֐�
//----------------------------------------------
public:

	// �R���X�g���N�^
	SelectStage(int stageNumber, KT::Stage::Size size);
	// �f�X�g���N�^
	~SelectStage();
	// ������
	void Initialize();
	// �X�V
	void Update();
	// �`��
	void Render(
		DirectX::SimpleMath::Matrix view,
		DirectX::SimpleMath::Matrix projection,
		std::function<void()> custom = nullptr
	);

	// �I�����Ă���X�e�[�W�̔ԍ��擾
	const int& GetSelectStageNumber() const;
	// �X�e�[�W�ؑ֊���������
	void StageSwitchComplete();

	// �؂�ւ���X�e�[�W�̗p��
	void ChangeStageSetting(const int& selectStageIndex);
	// �؂�ւ���̃X�e�[�W�̊�ʒu�擾
	DirectX::SimpleMath::Vector3 GetNextBasePosition() const;
	// �؂�ւ���̃X�e�[�W�̃T�C�Y�擾
	KT::Stage::Size GetNextStageSize() const;

};