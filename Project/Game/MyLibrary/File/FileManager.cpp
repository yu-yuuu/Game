/**
 *
 * @file FileManager.cpp
 *
 * @brief �t�@�C���̓��o�͂��s���N���X�̃\�[�X�t�@�C��
 *
 * @author Kato Yuki
 *
 * @date 2024/4/10
 *
 */
#include "pch.h"
#include "FileManager.h"

#include "Game/MyLibrary/Utility/MyUtility.h"


//------------------------------------------------------------------
/**
 * @brief �t�@�C�����J���i�ǂݍ��݁j
 *
 * @param  path    �F�J���t�@�C���̃p�X(const wchar_t*)
 * @return ifstream�F�J�����t�@�C��
 */
std::ifstream FileManager::OpenLoadFile(const wchar_t* path)
{
	// �t�@�C�����J��
	std::ifstream ifs(path, std::ios::in | std::ios::binary);

	// �J���Ȃ������狭���I��
	assert(ifs.is_open() && "�t�@�C�����J���܂���ł���");

	return ifs;
}

//------------------------------------------------------------------
/**
 * @brief �t�@�C�����J���i�ǂݍ��݁j
 *
 * @param path     �F�J���t�@�C���̃p�X(string)
 * @return ifstream�F�J�����t�@�C��
 */
std::ifstream FileManager::OpenLoadFile(const std::string& path)
{
	return OpenLoadFile(KT::MyUtility::StringToWide(path).c_str());
}

//------------------------------------------------------------------
/**
 * @brief �t�@�C�����J���i�������݁j
 *
 * @param  path    �F�J���t�@�C���̃p�X(const wchar_t*)
 * @return ofstream�F�J�����t�@�C��
 */
std::ofstream FileManager::OpenReadFile(const wchar_t* path)
{
	// �t�@�C�����J��
	std::ofstream ofs(path, std::ios::out | std::ios::binary);

	// �J���Ȃ������狭���I��
	assert(ofs.is_open() && "�t�@�C�����J���܂���ł���");

	return ofs;
}

//------------------------------------------------------------------
/**
 * @brief �t�@�C�����J���i�������݁j
 *
 * @param path     �F�J���t�@�C���̃p�X(string)
 * @return ofstream�F�J�����t�@�C��
 */
std::ofstream FileManager::OpenReadFile(const std::string& path)
{
	return OpenReadFile(KT::MyUtility::StringToWide(path).c_str());
}

//------------------------------------------------------------------
/**
 * @brief CSV�t�@�C���̓ǂݍ���
 *
 * @param  path   �FCSV�t�@�C���̃p�X(const wchar_t*)
 * @return CSVData�F�ǂݍ���CSV�f�[�^
 */
KT::File::CSVData FileManager::LoadCSV(const wchar_t* path)
{
	// �t�@�C���f�[�^�ԋp�p
	KT::File::CSVData fileData;

	// �t�@�C�����J��
	std::ifstream ifs = OpenLoadFile(path);

	// �ǂݍ��ݗp
	std::string line;

	// �f�[�^�ǂݍ���
	while (std::getline(ifs, line))
	{
		// �J���}�ŋ�؂��Ă���i�[
		fileData.push_back(SeparateData(line));
	}

	// �t�@�C�������
	ifs.close();

	return fileData;
}

//------------------------------------------------------------------
/**
 * @brief CSV�t�@�C���̓ǂݍ���
 *
 * @param  path   �F�J���t�@�C���̃p�X(string)
 * @return CSVData�F�ǂݍ���CSV�f�[�^
 */
KT::File::CSVData FileManager::LoadCSV(const std::string& path)
{
	return LoadCSV(KT::MyUtility::StringToWide(path).c_str());
}

//------------------------------------------------------------------
/**
 * @brief JSON�t�@�C���̓ǂݍ���
 *
 * @param  path�FJSON�t�@�C���̃p�X(const wchar_t*)
 * @return json�F�ǂݍ���JSON�f�[�^
 */
nlohmann::json FileManager::LoadJSON(const wchar_t* path)
{
	// �t�@�C�����J��
	std::ifstream ifs = OpenLoadFile(path);

	// Json�f�[�^�֕ϊ�
	nlohmann::json json = nlohmann::json::parse(ifs);

	// �t�@�C�������
	ifs.close();

	return json;
}

//------------------------------------------------------------------
/**
 * @brief JSON�t�@�C���̓ǂݍ���
 *
 * @param  path�FJSON�t�@�C���̃p�X(string)
 * @return json�F�ǂݍ���JSON�f�[�^
 */
nlohmann::json FileManager::LoadJSON(const std::string& path)
{
	return LoadJSON(KT::MyUtility::StringToWide(path).c_str());
}

//------------------------------------------------------------------
/**
 * @brief JSON�t�@�C���̏�������
 *
 * @param  path�F��������JSON�t�@�C���̃p�X(const wchar_t*)
 * @return json�F��������JSON�f�[�^
 */
void FileManager::ReadJSON(const wchar_t* path, const nlohmann::json& data)
{
	// �������ݐ�̃t�@�C�����J��
	std::ofstream ofs = OpenReadFile(path);

	// �f�[�^����������
	ofs << data;

	// �t�@�C�������
	ofs.close();
}

//------------------------------------------------------------------
/**
 * @brief JSON�t�@�C���̏�������
 *
 * @param  path�F��������JSON�t�@�C���̃p�X(string)
 * @return json�F��������JSON�f�[�^
 */void FileManager::ReadJSON(const std::string& path, const nlohmann::json& data)
{
	ReadJSON(KT::MyUtility::StringToWide(path).c_str(), data);
}

 //------------------------------------------------------------------
 /**
  * @brief ������f�[�^����؂�
  *
  * @param  str         �F��؂镶����
  * @param  separate    �F��؂蕶��
  * @return stringstream�F��؂���������
  */
 std::stringstream FileManager::SeparateData(std::string str, const char& separate)
{
	// �����f�[�^�̋�؂蕶�����󔒂ɕϊ�����
	std::replace(str.begin(), str.end(), separate, ' ');

	return std::stringstream(str);
}