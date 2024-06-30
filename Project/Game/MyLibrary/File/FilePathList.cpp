/**
 *
 * @file FilePathList.cpp
 *
 * @brief �g�p����t�@�C���̃p�X���Ǘ�����N���X�̃\�[�X�t�@�C��
 *
 * @author Kato Yuki
 *
 * @date 2024/4/10
 *
 */
#include "pch.h"
#include "FilePathList.h"

 //------------------------------------------------------------------
 /**
  * @brief �R���X�g���N�^
  *
  * @param �Ȃ�
  */
FilePathList::FilePathList()
	: m_filePathList()
{
}

//------------------------------------------------------------------
/**
 * @brief �f�X�g���N�^
 */
FilePathList::~FilePathList()
{
}

//------------------------------------------------------------------
/**
 * @brief �t�@�C���p�X���X�g�̍쐬
 *
 * @param  csvData�F�ǂݍ���CSV�f�[�^
 * @return �Ȃ�
 */
void FilePathList::CreatePathList(std::vector<std::stringstream> csvData)
{
	// �ǂݍ��ݗp
	std::string name, filePath;

	// �f�[�^�ǂݍ���
	for (std::stringstream& ss : csvData)
	{
		// �f�[�^���󂯎��
		ss >> name >> filePath;
		// �f�[�^�i�[
		m_filePathList[name] = filePath;
	}
}

//------------------------------------------------------------------
/**
 * @brief �t�@�C���p�X�̎擾
 *
 * @param  name  �F�t�@�C���p�X�̖��O
 * @return string�F�t�@�C���p�X
 */
std::string FilePathList::GetPath(const std::string& name)
{
	return m_filePathList.at(name);
}
