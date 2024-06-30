/**
 *
 * @file FilePathList.cpp
 *
 * @brief 使用するファイルのパスを管理するクラスのソースファイル
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
  * @brief コンストラクタ
  *
  * @param なし
  */
FilePathList::FilePathList()
	: m_filePathList()
{
}

//------------------------------------------------------------------
/**
 * @brief デストラクタ
 */
FilePathList::~FilePathList()
{
}

//------------------------------------------------------------------
/**
 * @brief ファイルパスリストの作成
 *
 * @param  csvData：読み込んだCSVデータ
 * @return なし
 */
void FilePathList::CreatePathList(std::vector<std::stringstream> csvData)
{
	// 読み込み用
	std::string name, filePath;

	// データ読み込み
	for (std::stringstream& ss : csvData)
	{
		// データを受け取る
		ss >> name >> filePath;
		// データ格納
		m_filePathList[name] = filePath;
	}
}

//------------------------------------------------------------------
/**
 * @brief ファイルパスの取得
 *
 * @param  name  ：ファイルパスの名前
 * @return string：ファイルパス
 */
std::string FilePathList::GetPath(const std::string& name)
{
	return m_filePathList.at(name);
}
