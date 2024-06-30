/**
 *
 * @file Stage.cpp
 *
 * @brief �X�e�[�W���\���N���X�̃\�[�X�t�@�C��
 *
 * @author Kato Yuki
 *
 * @date 2023/12/28
 *
 */#include "pch.h"
#include "Stage.h"

#include "Game/MyLibrary/CommonResource/GameResource.h"
#include "Game/Block/IBlock.h"

using namespace DirectX;

//------------------------------------------------------------------
/**
 * @brief �R���X�g���N�^
 *
 * @param  stageNumber�F�X�e�[�W�̔ԍ�
 * @param  size       �F�X�e�[�W�T�C�Y
 */
Stage::Stage(int stageNumber, KT::Stage::Size size)
	: m_stageNumber(stageNumber)
	, m_size(size)
	, m_stage()
{
}

//------------------------------------------------------------------
/**
 * @brief �f�X�g���N�^
 */
Stage::~Stage()
{
}

//------------------------------------------------------------------
/**
 * @brief ������
 *
 * @param  effect�F���f���ɓK��������G�t�F�N�g
 * @return �Ȃ�
 */
void Stage::Initialize(std::function<void(DirectX::IEffect* effect)> effect)
{
	// �X�e�[�W�f�[�^���ݒ肳��Ă��Ȃ������狭���I��
	assert(!m_stage.empty() && "�X�e�[�W�f�[�^���ݒ肳��Ă��܂���");

	// �X�e�[�W�u���b�N�̏�����
	for (std::unique_ptr<Block>& block : m_stage)
	{
		block->Initialize(effect);
	}
}

//------------------------------------------------------------------
/**
 * @brief �X�V
 *
 * @param  �Ȃ�
 * @return �Ȃ�
 */
void Stage::Update()
{
	// �X�e�[�W�u���b�N�̍X�V
	for (std::unique_ptr<Block>& block : m_stage)
	{
		block->Update();
	}
}

//------------------------------------------------------------------
/**
 * @brief �`��
 *
 * @param  view      �F�r���[�s��
 * @param  projection�F�ˉe�s��
 * @param  custom    �F�u���b�N�ɓK�������郉���_��
 * @return �Ȃ�
 */
void Stage::Render(
	DirectX::SimpleMath::Matrix view,
	DirectX::SimpleMath::Matrix projection,
	std::function<void()> custom
)
{
	// �X�e�[�W�u���b�N�̕`��
	for (std::unique_ptr<Block>& block : m_stage)
	{
		block->Render(view, projection, custom);
	}
}

//------------------------------------------------------------------
/**
 * @brief �㏈��
 *
 * @param  �Ȃ�
 * @return �Ȃ�
 */
void Stage::Finalize()
{
	// �X�e�[�W�u���b�N�̏�����
	for (std::unique_ptr<Block>& block : m_stage)
	{
		block->Finalize();
	}
}

//------------------------------------------------------------------
/**
 * @brief �X�e�[�W�f�[�^�擾
 *
 * @param �Ȃ�
 * @return StageData�F�X�e�[�W�f�[�^
 */
KT::Stage::StageData* Stage::GetStageData()
{
	return &m_stage;
}

//------------------------------------------------------------------
/**
 * @brief �X�e�[�W�f�[�^�ݒ�
 *
 * @param  stage�F�ݒ肷��X�e�[�W�f�[�^
 * @return �Ȃ�
 */
void Stage::SetStageData(KT::Stage::StageData stage)
{
	m_stage = std::move(stage);
}

//------------------------------------------------------------------
/**
 * @brief �X�e�[�W�ԍ��̎擾
 *
 * @param  �Ȃ�
 * @return int�F�X�e�[�W�ԍ�
 */
const int Stage::GetStageNumber() const
{
	return m_stageNumber;
}

//------------------------------------------------------------------
/**
 * @brief �X�e�[�W�T�C�Y�̎擾
 *
 * @param  �Ȃ�
 * @return Size�F�X�e�[�W�T�C�Y
 */
KT::Stage::Size Stage::GetStageSize() const
{
	return m_size;
}

//------------------------------------------------------------------
/**
 * @brief �X�e�[�W�T�C�Y�̐ݒ�
 *
 * @param  size�F�ݒ肷��T�C�Y
 * @return �Ȃ�
 */
void Stage::SetStageSize(const KT::Stage::Size& size)
{
	m_size = size;
}

//------------------------------------------------------------------
/**
 * @brief �X�e�[�W���폜����
 *
 * @param  �Ȃ�
 * @return �Ȃ�
 */
void Stage::ClearStage()
{
	m_stage.clear();
}

//------------------------------------------------------------------
/**
 * @brief �X�e�[�W�̃A�N�e�B�u��Ԃ�ݒ肷��
 *
 * @param  isActive�F�A�N�e�B�u���
 * @return �Ȃ�
 */
void Stage::SetStageActive(bool isActive)
{
	for (std::unique_ptr<Block>& block : m_stage)
	{
		block->SetActive(isActive);
	}
}
