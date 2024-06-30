/**
 *
 * @file FileManager.h
 *
 * @brief ファイルの入出力を行うクラスのヘッダーファイル
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
// 関数
//----------------------------------------------
public:

	// ファイルを開く（読み込み）
	static std::ifstream OpenLoadFile(const wchar_t* path);
	static std::ifstream OpenLoadFile(const std::string& path);
	// ファイルを開く（書き込み）
	static std::ofstream OpenReadFile(const wchar_t* path);
	static std::ofstream OpenReadFile(const std::string& path);

	// CSVファイルを読む
	static KT::File::CSVData LoadCSV(const wchar_t* path);
	static KT::File::CSVData LoadCSV(const std::string& path);
	// JSONファイルの読み書き
	static nlohmann::json LoadJSON(const wchar_t* path);
	static nlohmann::json LoadJSON(const std::string& path);
	static void ReadJSON(const wchar_t* path, const nlohmann::json& data);
	static void ReadJSON(const std::string& path, const nlohmann::json& data);

	// 文字列データを区切り文字で分ける
	static std::stringstream SeparateData(std::string str, const char& separate = ',');
};