/**
 *
 * @file PlayStage.h
 *
 * @brief �v���C�V�[���Ŏg�p����X�e�[�W�̃w�b�_�[�t�@�C��
 *
 * @author Kato Yuki
 *
 * @date 2023/12/31
 *
 */
#pragma once

#include "Game/Stage/Stage.h"
#include "Game/Stage/StageData.h"
#include "Game/Scene/PlayScene.h"
#include "Game/MyLibrary/GameParameter/GameParameter.h"


class PlayStage : public Stage
{
//----------------------------------------------
// �ϐ�
//----------------------------------------------
private:

	// �X�e�[�W�f�[�^
	//KT::Stage::StageData m_stage;
	// 2D�X�e�[�W�ɐ؂�ւ�����
	bool m_isChange2D;
	// �J�����������Ă������
	DirectX::SimpleMath::Vector3 m_cameraDirection;
	// �؂�ւ����̎���
	KT::GameParam::Dimension m_dimension;

//----------------------------------------------
// �֐�
//----------------------------------------------
public:

	// �R���X�g���N�^
	PlayStage(int stageNumber, KT::Stage::Size size);
	// �f�X�g���N�^
	~PlayStage();

	// ������
	void Initialize();
	// �X�V
	void Update(bool IsSwitching);
	// �`��
	void Render(
		DirectX::SimpleMath::Matrix view,
		DirectX::SimpleMath::Matrix projection,
		DirectX::SimpleMath::Vector3 eye,
		std::function<void()> custom = nullptr
	);

	// �����؂�ւ�
	void ChangeDimension(
		KT::GameParam::Dimension dimension,
		const DirectX::SimpleMath::Vector3& cameraDirection
	);
	// �X�^�[�g�u���b�N�̈ʒu�擾
	const DirectX::SimpleMath::Vector3& GetStartPosition();
	// �S�[���u���b�N�̈ʒu�擾
	const DirectX::SimpleMath::Vector3& GetGoalPosition();
	// �����蔻������u���b�N���擾
	std::vector<Collider*> GetCollisionStage();
	// 2D�ɐ؂�ւ��Ă悢��
	bool IsChange2DStage(bool IsSwitching);
	// 3D�ɐ؂�ւ��Ă悢��
	bool IsChange3DStage(bool IsSwitching);

};