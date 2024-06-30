/**
 *
 * @file FileManager.cpp
 *
 * @brief ファイルの入出力を行うクラスのソースファイル
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
 * @brief ファイルを開く（読み込み）
 *
 * @param  path    ：開くファイルのパス(const wchar_t*)
 * @return ifstream：開いたファイル
 */
std::ifstream FileManager::OpenLoadFile(const wchar_t* path)
{
	// ファイルを開く
	std::ifstream ifs(path, std::ios::in | std::ios::binary);

	// 開けなかったら強制終了
	assert(ifs.is_open() && "ファイルが開けませんでした");

	return ifs;
}

//------------------------------------------------------------------
/**
 * @brief ファイルを開く（読み込み）
 *
 * @param path     ：開くファイルのパス(string)
 * @return ifstream：開いたファイル
 */
std::ifstream FileManager::OpenLoadFile(const std::string& path)
{
	return OpenLoadFile(KT::MyUtility::StringToWide(path).c_str());
}

//------------------------------------------------------------------
/**
 * @brief ファイルを開く（書き込み）
 *
 * @param  path    ：開くファイルのパス(const wchar_t*)
 * @return ofstream：開いたファイル
 */
std::ofstream FileManager::OpenReadFile(const wchar_t* path)
{
	// ファイルを開く
	std::ofstream ofs(path, std::ios::out | std::ios::binary);

	// 開けなかったら強制終了
	assert(ofs.is_open() && "ファイルが開けませんでした");

	return ofs;
}

//------------------------------------------------------------------
/**
 * @brief ファイルを開く（書き込み）
 *
 * @param path     ：開くファイルのパス(string)
 * @return ofstream：開いたファイル
 */
std::ofstream FileManager::OpenReadFile(const std::string& path)
{
	return OpenReadFile(KT::MyUtility::StringToWide(path).c_str());
}

//------------------------------------------------------------------
/**
 * @brief CSVファイルの読み込み
 *
 * @param  path   ：CSVファイルのパス(const wchar_t*)
 * @return CSVData：読み込んだCSVデータ
 */
KT::File::CSVData FileManager::LoadCSV(const wchar_t* path)
{
	// ファイルデータ返却用
	KT::File::CSVData fileData;

	// ファイルを開く
	std::ifstream ifs = OpenLoadFile(path);

	// 読み込み用
	std::string line;

	// データ読み込み
	while (std::getline(ifs, line))
	{
		// カンマで区切ってから格納
		fileData.push_back(SeparateData(line));
	}

	// ファイルを閉じる
	ifs.close();

	return fileData;
}

//------------------------------------------------------------------
/**
 * @brief CSVファイルの読み込み
 *
 * @param  path   ：開くファイルのパス(string)
 * @return CSVData：読み込んだCSVデータ
 */
KT::File::CSVData FileManager::LoadCSV(const std::string& path)
{
	return LoadCSV(KT::MyUtility::StringToWide(path).c_str());
}

//------------------------------------------------------------------
/**
 * @brief JSONファイルの読み込み
 *
 * @param  path：JSONファイルのパス(const wchar_t*)
 * @return json：読み込んだJSONデータ
 */
nlohmann::json FileManager::LoadJSON(const wchar_t* path)
{
	// ファイルを開く
	std::ifstream ifs = OpenLoadFile(path);

	// Jsonデータへ変換
	nlohmann::json json = nlohmann::json::parse(ifs);

	// ファイルを閉じる
	ifs.close();

	return json;
}

//------------------------------------------------------------------
/**
 * @brief JSONファイルの読み込み
 *
 * @param  path：JSONファイルのパス(string)
 * @return json：読み込んだJSONデータ
 */
nlohmann::json FileManager::LoadJSON(const std::string& path)
{
	return LoadJSON(KT::MyUtility::StringToWide(path).c_str());
}

//------------------------------------------------------------------
/**
 * @brief JSONファイルの書き込み
 *
 * @param  path：書き込むJSONファイルのパス(const wchar_t*)
 * @return json：書き込むJSONデータ
 */
void FileManager::ReadJSON(const wchar_t* path, const nlohmann::json& data)
{
	// 書き込み先のファイルを開く
	std::ofstream ofs = OpenReadFile(path);

	// データを書き込む
	ofs << data;

	// ファイルを閉じる
	ofs.close();
}

//------------------------------------------------------------------
/**
 * @brief JSONファイルの書き込み
 *
 * @param  path：書き込むJSONファイルのパス(string)
 * @return json：書き込むJSONデータ
 */void FileManager::ReadJSON(const std::string& path, const nlohmann::json& data)
{
	ReadJSON(KT::MyUtility::StringToWide(path).c_str(), data);
}

 //------------------------------------------------------------------
 /**
  * @brief 文字列データを区切る
  *
  * @param  str         ：区切る文字列
  * @param  separate    ：区切り文字
  * @return stringstream：区切った文字列
  */
 std::stringstream FileManager::SeparateData(std::string str, const char& separate)
{
	// 文字データの区切り文字を空白に変換する
	std::replace(str.begin(), str.end(), separate, ' ');

	return std::stringstream(str);
}