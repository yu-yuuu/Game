/**
 *
 * @file TitleStage.cpp
 *
 * @brief �^�C�g���V�[���X�e�[�W��\���N���X�̃\�[�X�t�@�C��
 *
 * @author Kato Yuki
 *
 * @date 2024/1/21
 *
 */
#include "pch.h"
#include "TitleStage.h"
#include "Game/MyLibrary/CommonResource/GameResource.h"
#include "Game/Scene/TitleScene.h"

using namespace DirectX;

//------------------------------------------------------------------
/**
 * @brief �R���X�g���N�^
 *
 * @param titleScene �F�^�C�g���V�[���̃|�C���^
 * @param stageNumber�F�X�e�[�W�ԍ�
 * @param size       �F�X�e�[�W�T�C�Y
 */
TitleStage::TitleStage(TitleScene* titleScene, int stageNumber, KT::Stage::Size size)
	: Stage(stageNumber, size)
	, m_titleScene(titleScene)
{
}

//------------------------------------------------------------------
/**
 * @brief �f�X�g���N�^
 */
TitleStage::~TitleStage()
{
}

//------------------------------------------------------------------
/**
 * @brief ������
 *
 * @param  �Ȃ�
 * @return �Ȃ�
 */
void TitleStage::Initialize()
{
	// �X�e�[�W�}�l�[�W���[�擾
	StageManager* stageManager = GameResource::GetInstance()->GetStageManager();

	// �^�C�g���V�[���p�X�e�[�W���擾
	KT::Stage::Size stageSize = stageManager->GetStageSize(GetStageNumber());
	KT::Stage::StageData stage = stageManager->CreateStage3D(GetStageNumber());

	// �����u���b�N�̃��C�g�ݒ�
	for (std::unique_ptr<Block>& block : stage)
	{
		if (
			block->GetType() == KT::Block::Type::GAME_START    ||
			block->GetType() == KT::Block::Type::GAME_START_A  ||
			block->GetType() == KT::Block::Type::GAME_START_SO ||
			block->GetType() == KT::Block::Type::GAME_START_BU ||
			block->GetType() == KT::Block::Type::GAME_END      ||
			block->GetType() == KT::Block::Type::GAME_END_O    ||
			block->GetType() == KT::Block::Type::GAME_END_WA   ||
			block->GetType() == KT::Block::Type::GAME_END_RU 
			)
		{
			block->Initialize([](IEffect* effect)
				{
					IEffectLights* lights = dynamic_cast<IEffectLights*>(effect);

					if (lights)
					{
						// ���C�g�̉e�����Ȃ���
						lights->SetAmbientLightColor(SimpleMath::Vector3::Zero);
						lights->SetLightEnabled(0, false);
						lights->SetLightEnabled(1, false);
						lights->SetLightEnabled(2, false);
					}

					BasicEffect* basicEffect = dynamic_cast<BasicEffect*>(effect);
					if (basicEffect)
					{
						// ���Ȕ���������
						basicEffect->SetEmissiveColor(SimpleMath::Vector3::One);
					}
				}
			);
		}
	}
	// �X�e�[�W�f�[�^�ݒ�
	SetStageData(std::move(stage));
	// �X�e�[�W�̏�����
	Stage::Initialize();
}

//------------------------------------------------------------------
/**
 * @brief �X�V
 *
 * @param  �Ȃ�
 * @return �Ȃ�
 */
void TitleStage::Update()
{
	// �X�e�b�v�^�C�}�[�擾
	DX::StepTimer* stepTimer = GameResource::GetInstance()->GetStepTimer();

	// �I����ԂłȂ��Ȃ�I��
	if (m_titleScene->GetTitleState() != TitleScene::TitleState::MODE_SELECT)
		return;

	// sin�œ_��
	float brightness = std::sinf(static_cast<float>(stepTimer->GetTotalSeconds()) * FLASH_SPEED);
	// 0.75 �` 1 �͈̔͂Ɏ��߂�
	brightness = brightness * SELECT_BUTTON_BRIGHTNESS_MIN + SELECT_BUTTON_BRIGHTNESS_MAX;

	// �^�C�g���V�[���̃��[�h�擾
	TitleScene::NextMode mode = m_titleScene->GetMode();
	// �X�e�[�W�擾
	KT::Stage::StageData* stage = GetStageData();
	// �{�^���̐F
	SimpleMath::Vector3 col;

	for (std::unique_ptr<Block>& block : *stage)
	{
		// �F��ݒ�
		col = SimpleMath::Vector3(brightness, brightness, brightness);

		// �I������Ă��Ȃ��Ȃ�Â�����
		if (mode == TitleScene::NextMode::PLAY)
		{
			if (block->GetType() == KT::Block::Type::GAME_END ||
				block->GetType() == KT::Block::Type::GAME_END_O ||
				block->GetType() == KT::Block::Type::GAME_END_WA ||
				block->GetType() == KT::Block::Type::GAME_END_RU)
			{
				col = SimpleMath::Vector3(0.5f, 0.5f, 0.5f);
			}
		}
		else if (mode == TitleScene::NextMode::EXIT)
		{
			if (block->GetType() == KT::Block::Type::GAME_START ||
				block->GetType() == KT::Block::Type::GAME_START_A ||
				block->GetType() == KT::Block::Type::GAME_START_SO ||
				block->GetType() == KT::Block::Type::GAME_START_BU )
			{
				col = SimpleMath::Vector3(0.5f, 0.5f, 0.5f);
			}
		}

		// �F��K�p������
		if (
			block->GetType() == KT::Block::Type::GAME_START ||
			block->GetType() == KT::Block::Type::GAME_START_A ||
			block->GetType() == KT::Block::Type::GAME_START_SO ||
			block->GetType() == KT::Block::Type::GAME_START_BU ||
			block->GetType() == KT::Block::Type::GAME_END ||
			block->GetType() == KT::Block::Type::GAME_END_O ||
			block->GetType() == KT::Block::Type::GAME_END_WA ||
			block->GetType() == KT::Block::Type::GAME_END_RU
			)
		{
			block->GetModel()->UpdateEffects([&](IEffect* effect)
				{
					BasicEffect* basicEffect = dynamic_cast<BasicEffect*>(effect);
					if (basicEffect)
					{
						// ���Ȕ���������
						basicEffect->SetEmissiveColor(col);
					}
				}
			);
		}
	}
}
