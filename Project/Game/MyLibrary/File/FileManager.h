/**
 *
 * @file FileManager.h
 *
 * @brief �t�@�C���̓��o�͂��s���N���X�̃w�b�_�[�t�@�C��
 *
 * @author Kato Yuki
 *
 * @date 2024/4/10
 *
 */
#pragma once
#include <fstream>
#include <string>
#include <sstream>
#include <unordered_map>
#include "Library/nlohmann/json.hpp"
#include "Game/MyLibrary/ResourceManager/ResourceType.h"


class FileManager
{
//----------------------------------------------
// �֐�
//----------------------------------------------
public:

	// �t�@�C�����J���i�ǂݍ��݁j
	static std::ifstream OpenLoadFile(const wchar_t* path);
	static std::ifstream OpenLoadFile(const std::string& path);
	// �t�@�C�����J���i�������݁j
	static std::ofstream OpenReadFile(const wchar_t* path);
	static std::ofstream OpenReadFile(const std::string& path);

	// CSV�t�@�C����ǂ�
	static KT::File::CSVData LoadCSV(const wchar_t* path);
	static KT::File::CSVData LoadCSV(const std::string& path);
	// JSON�t�@�C���̓ǂݏ���
	static nlohmann::json LoadJSON(const wchar_t* path);
	static nlohmann::json LoadJSON(const std::string& path);
	static void ReadJSON(const wchar_t* path, const nlohmann::json& data);
	static void ReadJSON(const std::string& path, const nlohmann::json& data);

	// ������f�[�^����؂蕶���ŕ�����
	static std::stringstream SeparateData(std::string str, const char& separate = ',');
};