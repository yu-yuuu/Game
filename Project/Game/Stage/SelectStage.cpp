/**
 *
 * @file SelectStage.cpp
 *
 * @brief �Z���N�g�V�[���̃X�e�[�W�N���X�̃\�[�X�t�@�C��
 *
 * @author Kato Yuki
 *
 * @date 2024/1/21
 *
 */
#include "pch.h"
#include "SelectStage.h"
#include "Game/MyLibrary/CommonResource/GameResource.h"

 //------------------------------------------------------------------
 /**
  * @brief �R���X�g���N�^)
  *
  * @param stageNumber�F�I������Ă���X�e�[�W�ԍ�
  * @param size�F�X�e�[�W�T�C�Y
  */
SelectStage::SelectStage(int stageNumber, KT::Stage::Size size)
	: Stage(stageNumber, size)
	, m_stageList()
	, m_stageNumberList()
	, m_selectStageNumber(stageNumber)
	, m_nextStage(nullptr)
	, m_nextBasePosition()
{
}

//------------------------------------------------------------------
/**
 * @brief �f�X�g���N�^
 */
SelectStage::~SelectStage()
{
}

//------------------------------------------------------------------
/**
 * @brief ������
 *
 * @param  �Ȃ�
 * @return �Ȃ�
 */
void SelectStage::Initialize()
{
	// �X�e�[�W�}�l�[�W���[�擾
	StageManager* stageManager = GameResource::GetInstance()->GetStageManager();
	// �^�C�g���V�[���p�X�e�[�W��ݒ�
	SetStageData(stageManager->CreateStage3D(GetStageNumber()));
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
void SelectStage::Update()
{
	if (m_nextStage) m_nextStage->Update();

	Stage::Update();
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
void SelectStage::Render(DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix projection, std::function<void()> custom)
{
	if (m_nextStage) m_nextStage->Render(view, projection, custom);
	Stage::Render(view, projection, custom);
}

//------------------------------------------------------------------
/**
 * @brief �I�����Ă���X�e�[�W�̔ԍ��擾
 *
 * @param �Ȃ�
 * @return int�F�I�����Ă���X�e�[�W�ԍ�
 */
const int& SelectStage::GetSelectStageNumber() const
{
	return m_selectStageNumber;
}

//------------------------------------------------------------------
/**
 * @brief �X�e�[�W�ؑ֊���������
 *
 * @param  �Ȃ�
 * @return �Ȃ�
 */
void SelectStage::StageSwitchComplete()
{
	// �؂�ւ���̃X�e�[�W�����݂̃X�e�[�W�ɐݒ�
	SetStageData(std::move(*m_nextStage->GetStageData()));
	// �؂�ւ���̃X�e�[�W���Z�b�g
	m_nextStage.reset();
	m_nextStage = nullptr;
}

//------------------------------------------------------------------
/**
 * @brief �؂�ւ���X�e�[�W�̗p��
 *
 * @param  selectStageIndex�F�I�������X�e�[�W�̗v�f�ԍ�
 * @return �Ȃ�
 */
void SelectStage::ChangeStageSetting(const int& selectStageIndex)
{
	using namespace DirectX;

	// �X�e�[�W�}�l�[�W���[�擾
	StageManager* stageManager = GameResource::GetInstance()->GetStageManager();
	// �X�e�[�W�ԍ����X�g���󂯎��
	std::vector<int> numberList = stageManager->GetStageNumberList();
	// �X�e�[�W�쐬
	m_nextBasePosition = SimpleMath::Vector3(0.0f, -STAGE_HEIGHT_OFFSET * selectStageIndex, 0.0f);
	m_nextStage = std::make_unique<Stage>(numberList[selectStageIndex], stageManager->GetStageSize(numberList[selectStageIndex]));
	m_nextStage->SetStageData(stageManager->CreateStage3D(numberList[selectStageIndex], m_nextBasePosition));
	m_nextStage->Initialize();
}

//------------------------------------------------------------------
/**
 * @brief �؂�ւ���̃X�e�[�W�̊�ʒu���擾
 *
 * @param �Ȃ�
 * @return Vector3�F��ʒu
 */
DirectX::SimpleMath::Vector3 SelectStage::GetNextBasePosition() const
{
	return m_nextBasePosition;
}

//------------------------------------------------------------------
/**
 * @brief �X�e�[�W�T�C�Y�̎擾
 *
 * @param  �Ȃ�
 * @return Size�F�X�e�[�W�T�C�Y
 */
KT::Stage::Size SelectStage::GetNextStageSize() const
{
	return m_nextStage->GetStageSize();
}
