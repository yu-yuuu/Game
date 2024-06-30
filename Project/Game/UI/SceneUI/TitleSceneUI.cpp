/**
 *
 * @file TitleSceneUI.cpp
 *
 * @brief �^�C�g���V�[���V�[���Ŏg�p����UI�A�摜�N���X�̃\�[�X�t�@�C��
 *
 * @author Kato Yuki
 *
 * @date 2024/1/22
 *
 */
#include "pch.h"
#include "TitleSceneUI.h"

#include "Game/MyLibrary/CommonResource/GameResource.h"
#include "Game/Scene/TitleScene.h"
#include "Game/UI/OperatableUI.h"

using namespace DirectX;

//------------------------------------------------------------------
/**
 * @brief �R���X�g���N�^
 *
 * @param titleScene�F�^�C�g���V�[���̃|�C���^
 */
TitleSceneUI::TitleSceneUI(TitleScene* titleScene)
	: m_titleScene(titleScene)
	, m_pushEnterText()
{
}

//------------------------------------------------------------------
/**
 * @brief �f�X�g���N�^
 */
TitleSceneUI::~TitleSceneUI()
{
}

//------------------------------------------------------------------
/**
 * @brief ������
 *
 * @param  �Ȃ�
 * @return �Ȃ�
 */
void TitleSceneUI::Initialize()
{
	namespace TextureName = KT::Texture;

	// UI�쐬
	CreateUI(KT::UI::PROPERTIE_TITLE);
	// ����UI�擾
	m_pushEnterText = GetUI(KT::UI::TITLE_PUSH_ENTER_TEXT);

	// UI�}�l�[�W���[�ɓo�^
	AddUIManager(TAG_ALWAYS);
	AddUIManager(TAG_PUSH_ENTER);
	// ���g��UI�}�l�[�W���[�֓o�^
	SetUIManagerSceneUI();
}

//------------------------------------------------------------------
/**
 * @brief �X�V
 *
 * @param  �Ȃ�
 * @return �Ȃ�
 */
void TitleSceneUI::Update()
{
	// �X�e�b�v�^�C�}�[�擾
	DX::StepTimer* stepTimer = GameResource::GetInstance()->GetStepTimer();
	// sin�œ_��
	float alpha = std::sinf(static_cast<float>(stepTimer->GetTotalSeconds()));
	// -1 �` 1 �� 0 �` 1 �͈̔͂Ɏ��߂�
	alpha = alpha * FLASH_ADJUSTMENT + FLASH_ADJUSTMENT;
	// �����x��ݒ�
	SimpleMath::Color color = m_pushEnterText->GetTexture()->GetColor();
	m_pushEnterText->GetTexture()->SetColor(SimpleMath::Color(color.R(), color.G(), color.B(), alpha));
}

//------------------------------------------------------------------
/**
 * @brief �����ؑ֏�Ԃɐ؂�ւ�
 *
 * @param  �Ȃ�
 * @return �Ȃ�
 */
void TitleSceneUI::ChangeStateSwitching()
{
	// �G���^�[�L�[���͑ҋ@��Ԃ�UI�̓o�^����
	DeleteUIManager(TAG_PUSH_ENTER);
	// UI�̍X�V�����͖����̂ŃV�[��UI�o�^����
	DeleteUIManagerSceneUI();
}

//------------------------------------------------------------------
/**
 * @brief ���[�h�I����Ԃɐ؂�ւ�
 *
 * @param  �Ȃ�
 * @return �Ȃ�
 */
void TitleSceneUI::ChangeStateModeSelect()
{
	// ���[�h�I����Ԃ�UI��o�^
	AddUIManager(TAG_MODE_SELECT);
}