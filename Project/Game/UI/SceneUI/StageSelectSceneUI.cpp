/**
 *
 * @file StageSelectSceneUI.cpp
 *
 * @brief �X�e�[�W�Z���N�g�V�[���Ŏg�p����UI�A�摜�N���X�̃\�[�X�t�@�C��
 *
 * @author Kato Yuki
 *
 * @date 2024/1/22
 *
 */
#include "pch.h"
#include "StageSelectSceneUI.h"

#include "Game/MyLibrary/CommonResource/GameResource.h"
#include "Game/Scene/StageSelectScene.h"
#include "Game/UI/OperatableUI.h"

using namespace DirectX;

//------------------------------------------------------------------
/**
 * @brief �R���X�g���N�^
 *
 * @param stageSelectScene�F�Z���N�g�V�[���̃|�C���^
 */
StageSelectSceneUI::StageSelectSceneUI(StageSelectScene* stageSelectScene)
	: m_stageSelectScene(stageSelectScene)
	, m_selectArrowUp(nullptr)
	, m_selectArrowDown(nullptr)
{
}

//------------------------------------------------------------------
/**
 * @brief �f�X�g���N�^
 */
StageSelectSceneUI::~StageSelectSceneUI()
{
}

//------------------------------------------------------------------
/**
 * @brief ������
 *
 * @param  �Ȃ�
 * @return �Ȃ�
 */
void StageSelectSceneUI::Initialize()
{
	// UI�쐬
	CreateUI(KT::UI::PROPERTIE_STAGESELECT);
	// ����UI�擾
	m_selectArrowUp   = GetUI(KT::UI::STAGE_SELECT_ARROW_UP);
	m_selectArrowDown = GetUI(KT::UI::STAGE_SELECT_ARROW_DOWN);

	// ���N���X�̑S�Ă�UI��UI�}�l�[�W���[�ɓo�^
	AddUIManagerAll();
	// UI�}�l�[�W���[�Ɏ��g��ݒ肷��
	SetUIManagerSceneUI();
}

//------------------------------------------------------------------
/**
 * @brief �X�V
 *
 * @param  �Ȃ�
 * @return �Ȃ�
 */
void StageSelectSceneUI::Update()
{
	// �X�e�b�v�^�C�}�[�擾
	DX::StepTimer* stepTimer = GameResource::GetInstance()->GetStepTimer();
	float totalTime = static_cast<float>(stepTimer->GetTotalSeconds());

	// ���̈ʒu�擾
	SimpleMath::Vector2 upPos   = m_selectArrowUp->GetPosition();
	SimpleMath::Vector2 downPos = m_selectArrowDown->GetPosition();
	// ���̈ړ���
	float move = std::sinf(totalTime * STAGE_SELECT_ARROW_MOVE_SPEED) * STAGE_SELECT_ARROW_MOVE_WIDTH;
	// ���𓮂���
	upPos.y += move;
	downPos.y -= move;
	// ���̈ʒu�ݒ�
	m_selectArrowUp->SetPosition(upPos);
	m_selectArrowDown->SetPosition(downPos);
}

//------------------------------------------------------------------
/**
 * @brief ���̕`��ݒ�
 *
 * @param  isStart�F�擪�̃X�e�[�W��I�����Ă��邩
 * @param  isEnd  �F�Ō�̃X�e�[�W��I�����Ă��邩
 * @return �Ȃ�
 */
void StageSelectSceneUI::SelectTriangleRenderSetting(bool isStart, bool isEnd)
{
	// 1�X�e�[�W�ڂ�I�����Ă���
	if (isStart)
	{
		DeleteUIManager(TAG_ARROW_UP);
	}
	// �Ō�̃X�e�[�W��I�����Ă���
	else if (isEnd)
	{
		DeleteUIManager(TAG_ARROW_DOWN);
	}
	// ��L�ȊO
	else
	{
		AddUIManager(TAG_ARROW_UP);
		AddUIManager(TAG_ARROW_DOWN);
	}
}