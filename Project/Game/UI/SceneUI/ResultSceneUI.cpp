/**
 *
 * @file ResultSceneUI.cpp
 *
 * @brief ���U���g�V�[����UI���܂Ƃ߂�N���X�̃\�[�X�t�@�C��
 *
 * @author Kato Yuki
 *
 * @date 2024/3/13
 *
 */
#include "pch.h"
#include "ResultSceneUI.h"

#include "Game/MyLibrary/CommonResource/GameResource.h"
#include "Game/Scene/ResultScene.h"
#include "Game/UI/OperatableUI.h"

using namespace DirectX;

//------------------------------------------------------------------
/**
 * @brief �R���X�g���N�^
 *
 * @param resultScene�F���U���g�V�[���̃|�C���^
 */
ResultSceneUI::ResultSceneUI(ResultScene* resultScene)
	: m_resultScene(resultScene)
	, m_selectUI()
{
}

//------------------------------------------------------------------
/**
 * @brief �f�X�g���N�^
 */
ResultSceneUI::~ResultSceneUI()
{
}

//------------------------------------------------------------------
/**
 * @brief ������
 *
 * @param  �Ȃ�
 * @return �Ȃ�
 */
void ResultSceneUI::Initialize()
{
	// �G�C���A�X�錾
	using Mode = ResultScene::NextMode;

	// UI�쐬
	CreateUI(KT::UI::PROPERTIE_RESULT);
	// �I������UI�̐ݒ�
	m_selectUI.resize(static_cast<int>(Mode::COUNT));
	m_selectUI[static_cast<int>(Mode::NEXT)]         = GetUI(KT::UI::RESULT_NEXT_SCENE_TEXT);
	m_selectUI[static_cast<int>(Mode::STAGE_SELECT)] = GetUI(KT::UI::RESULT_TOSELECT_SCENE_TEXT);

	// �Ō�̃X�e�[�W��
	if (m_resultScene->IsEndStageNumber())
	{
		m_selectUI[static_cast<int>(Mode::NEXT)]->ActiveStateUpdate(false);
		m_selectUI[static_cast<int>(Mode::STAGE_SELECT)]->SelectStateUpdate(true);
	}

	// UI�}�l�[�W���[�ɓo�^
	AddUIManagerAll();
}

//------------------------------------------------------------------
/**
 * @brief �I������
 *
 * @param  type�F���Ԃ�I�����Ă��邩
 * @return �Ȃ�
 */
void ResultSceneUI::Select(const int& type)
{
	for (int i = 0; i < m_selectUI.size(); i++)
	{
		// �I�����Ă�����UI�̐F��ύX
		m_selectUI[i]->SelectStateUpdate(i == type);
	}
}