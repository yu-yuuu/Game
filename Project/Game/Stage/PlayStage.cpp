/**
 *
 * @file PlayStage.cpp
 *
 * @brief �v���C�V�[���Ŏg�p����X�e�[�W�̃\�[�X�t�@�C��
 *
 * @author Kato Yuki
 *
 * @date 2023/12/31
 *
 */
#include "pch.h"
#include "PlayStage.h"
#include "Game/Block/BlockType.h"
#include "Game/Block/Block.h"
#include "Game/MyLibrary/Collision/BoxCollider.h"
#include "Game/MyLibrary/CommonResource/GameResource.h"

using namespace DirectX;

//------------------------------------------------------------------
/**
 * @brief �R���X�g���N�^
 *
 * @param  stageNumber �F�X�e�[�W�ԍ�
 * @param  size        �F�X�e�[�W�T�C�Y
 */
PlayStage::PlayStage(int stageNumber, KT::Stage::Size size)
	: Stage(stageNumber, size)
	//, m_stage()
	, m_isChange2D(false)
	, m_cameraDirection()
	, m_dimension()
{
}

//------------------------------------------------------------------
/**
 * @brief �f�X�g���N�^
 */
PlayStage::~PlayStage()
{
}

//------------------------------------------------------------------
/**
 * @brief ������
 *
 * @param  �Ȃ�
 * @return �Ȃ�
 */
void PlayStage::Initialize()
{
	// �X�e�[�W�}�l�[�W���[�擾
	StageManager* manager = GameResource::GetInstance()->GetStageManager();
	// �X�e�[�W�쐬
	SetStageData(manager->CreateStage3D(GetStageNumber()));
	// ���N���X�̏�����
	Stage::Initialize();
}

//------------------------------------------------------------------
/**
 * @brief �X�V
 *
 * @param  IsSwitching�F�����ؑ֒���
 * @return �Ȃ�
 */
void PlayStage::Update(bool IsSwitching)
{
	// 3D �� 2D �ؑ�
	if (IsChange2DStage(IsSwitching))
	{
		SetStageActive(false);
		StageManager* manager = GameResource::GetInstance()->GetStageManager();
		manager->Switch3DTo2DStageData(GetStageSize().GetVector3(), GetStageData(), m_cameraDirection);
		m_isChange2D = false;
	}
	// 2D �� 3D �ؑ�
	else if (IsChange3DStage(IsSwitching))
	{
		SetStageActive(true);
		m_isChange2D = false;
	}
	// �X�e�[�W�u���b�N�̍X�V
	Stage::Update();
}

//------------------------------------------------------------------
/**
 * @brief �`��
 *
 * @param view      �F�r���[�s��
 * @param projection�F�ˉe�s��
 * @param eye       �F�J�����ʒu
 * @param custom    �F�X�e�[�W�ɓK��������G�t�F�N�g
 * @return �Ȃ�
 */
void PlayStage::Render(DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix projection, DirectX::SimpleMath::Vector3 eye, std::function<void()> custom)
{
	// �X�e�[�W�f�[�^�擾
	KT::Stage::StageData* stage = GetStageData();
	// �u���b�N���J�����ɋ߂����Ƀ\�[�g����
	std::sort(stage->begin(), stage->end(),
		[&](std::unique_ptr<Block>& lhs, std::unique_ptr<Block>& rhs)
		{
			auto l = lhs->GetPosition() - eye;
			auto r = rhs->GetPosition() - eye;

			return l.LengthSquared() < r.LengthSquared();
		}
	);
	// �X�e�[�W�u���b�N�̕`��
	for (std::unique_ptr<Block>& block : *stage)
	{
		block->Render(view, projection, custom);
	}
}

//------------------------------------------------------------------
/**
 * @brief �����؂�ւ�
 *
 * @param  dimension�F���݂̎���
 * @param  cameraDirection�F�J�����̎��_����
 * @return �Ȃ�
 */
void PlayStage::ChangeDimension(
	KT::GameParam::Dimension dimension,
	const DirectX::SimpleMath::Vector3& cameraDirection)
{
	m_isChange2D = true;
	m_dimension = dimension;
	m_cameraDirection = cameraDirection;
}

//------------------------------------------------------------------
/**
 * @brief �X�^�[�g�ʒu�擾
 *
 * @param  �Ȃ�
 * @return Vector3�F�X�^�[�g�ʒu
 */
const DirectX::SimpleMath::Vector3& PlayStage::GetStartPosition()
{
	KT::Stage::StageData* stage = GetStageData();
	for (std::unique_ptr<Block>& block : *stage)
	{
		// �X�^�[�g�u���b�N�ȊO�͔�΂�
		if (block->GetType() != KT::Block::Type::START) continue;
	
		// �ʒu��Ԃ�
		return block->GetPosition();
	}

	return SimpleMath::Vector3::Zero;
}

//------------------------------------------------------------------
/**
 * @brief �S�[���ʒu�̎擾
 *
 * @param  �Ȃ�
 * @return �Ȃ�
 */
const DirectX::SimpleMath::Vector3& PlayStage::GetGoalPosition()
{
	KT::Stage::StageData* stage = GetStageData();
	for (std::unique_ptr<Block>& block : *stage)
	{
		// �X�^�[�g�u���b�N�ȊO�͔�΂�
		if (block->GetType() != KT::Block::Type::GOAL) continue;
		// �ʒu��Ԃ�
		return block->GetPosition();
	}

	return SimpleMath::Vector3::Zero;
}

//------------------------------------------------------------------
/**
 * @brief �X�e�[�W�̓����蔻����擾
 *
 * @param  �Ȃ�
 * @return vector<Collider*>�F�X�e�[�W�̓����蔻�胊�X�g
 */
std::vector<Collider*> PlayStage::GetCollisionStage()
{
	// ���݂̃X�e�[�W�f�[�^
	KT::Stage::StageData* stage = GetStageData();
	// �ԋp�p
	std::vector<Collider*> ret;
	// ���炩���߃������̈���m�ۂ��Ă���
	ret.reserve(stage->size());
	
	for (std::unique_ptr<Block>& block : *stage)
	{
		// �����蔻������Ȃ��u���b�N�Ȃ��΂�
		if (block->GetCollisionMode() == KT::Block::CollisionMode::NONE) continue;
		// �ԋp�p�ɒǉ�
		ret.push_back(block->GetCollider());
	}
	// �������T�C�Y��v�f�T�C�Y�ɍ��킹��
	ret.shrink_to_fit();
	return ret;
}

//------------------------------------------------------------------
/**
 * @brief 2D�ɐ؂�ւ��Ă悢��
 *
 * @param IsSwitching�F�����ؑ֒���
 * @return true �F�ؑ։�
 * @return false�F�ؑ֕s��
 */
bool PlayStage::IsChange2DStage(bool IsSwitching)
{
	return m_isChange2D && !IsSwitching && m_dimension == KT::GameParam::Dimension::_3D;
}
//------------------------------------------------------------------
/**
 * @brief 3D�ɐ؂�ւ��Ă悢��
 *
 * @param IsSwitching�F�����ؑ֒���
 * @return true �F�ؑ։�
 * @return false�F�ؑ֕s��
 */
bool PlayStage::IsChange3DStage(bool IsSwitching)
{
	return m_isChange2D && IsSwitching && m_dimension == KT::GameParam::Dimension::_2D;
}