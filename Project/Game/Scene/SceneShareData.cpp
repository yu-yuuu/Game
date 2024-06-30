/**
 *
 * @file SceneShareData.cpp
 *
 * @brief �e�V�[���ŋ��L����f�[�^�̃\�[�X�t�@�C��
 *
 * @author Kato Yuki
 *
 * @date 2024/1/21
 *
 */
#include "pch.h"
#include "SceneShareData.h"
#include "Game/MyLibrary/CommonResource/GameResource.h"

using namespace DirectX;

//------------------------------------------------------------------
/**
 * @brief �R���X�g���N�^
 *
 * @param sceneManager�F�V�[���}�l�[�W���[�̃|�C���^
 */
SceneShareData::SceneShareData(SceneManager* sceneManager)
	: m_sceneManager(sceneManager)
	, m_selectStageNumber(0)
{
	// ���\�[�X�}�l�[�W���[�擾
	ResourceManager* resourceManager = GameResource::GetInstance()->GetResourceManager();

	// ���j���[�E�B���h�E�쐬
	m_menuWindow = std::make_unique<MenuWindow>(m_sceneManager, SimpleMath::Vector2(470, 500), resourceManager->GetTexture(KT::Texture::WINDOW_FRAME), SimpleMath::Vector2(640.0f, 360.0f));
	m_menuWindow->Initialize();
}

//------------------------------------------------------------------
/**
 * @brief �R���X�g���N�^
 */
SceneShareData::~SceneShareData()
{
}

//------------------------------------------------------------------
/**
 * @brief ���j���[�E�B���h�E�擾
 *
 * @param  �Ȃ�
 * @return MenuWindow�F���j���[�E�B���h�E�̃|�C���^
 */
MenuWindow* SceneShareData::GetMenuWindow()
{
	return m_menuWindow.get();
}

//------------------------------------------------------------------
/**
 * @brief �I�������X�e�[�W�ԍ��̐ݒ�
 *
 * @param  selectStageNumber�F�I�������X�e�[�W�ԍ�
 * @return �Ȃ�
 */
void SceneShareData::SetSelectStageNumber(const int& selectStageNumber)
{
	m_selectStageNumber = selectStageNumber;
}

//------------------------------------------------------------------
/**
 * @brief �I�������X�e�[�W�ԍ��̎擾
 *
 * @param  �Ȃ�
 * @return int�F�I�������X�e�[�W�ԍ�
 */
const int& SceneShareData::GetSelectStageNumber() const
{
	return m_selectStageNumber;
}