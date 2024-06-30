/**
 *
 * @file FilePathList.h
 *
 * @brief 使用するファイルのパスを管理するクラスのヘッダーファイル
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
// 変数
//----------------------------------------------
private:

	// ファイルパスリスト
	std::unordered_map<std::string, std::string> m_filePathList;

//----------------------------------------------
// 関数
//----------------------------------------------
public:

	// コンストラクタ
	FilePathList();
	// デストラクタ
	~FilePathList();

	// パスリストを作成する
	void CreatePathList(std::vector<std::stringstream> csvData);
	// ファイルパスを取得
	std::string GetPath(const std::string& name);

};