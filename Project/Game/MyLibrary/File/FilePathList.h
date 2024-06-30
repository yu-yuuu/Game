/**
 *
 * @file FilePathList.h
 *
 * @brief �g�p����t�@�C���̃p�X���Ǘ�����N���X�̃w�b�_�[�t�@�C��
 *
 * @author Kato Yuki
 *
 * @date 2024/4/10
 *
 */
#pragma once

#include <string>
#include <unordered_map>
#include <sstream>

class FilePathList
{
//----------------------------------------------
// �ϐ�
//----------------------------------------------
private:

	// �t�@�C���p�X���X�g
	std::unordered_map<std::string, std::string> m_filePathList;

//----------------------------------------------
// �֐�
//----------------------------------------------
public:

	// �R���X�g���N�^
	FilePathList();
	// �f�X�g���N�^
	~FilePathList();

	// �p�X���X�g���쐬����
	void CreatePathList(std::vector<std::stringstream> csvData);
	// �t�@�C���p�X���擾
	std::string GetPath(const std::string& name);

};