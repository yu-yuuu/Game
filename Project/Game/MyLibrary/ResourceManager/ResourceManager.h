/**
 *
 * @file ResourceManager.h
 *
 * @brief 画像やモデル等のリソースの作成、管理するクラスのヘッダーファイル
 *
 * @author Kato Yuki
 *
 * @date 2023/9/7
 *
 */
#pragma once

#include <unordered_map>

#include "Model.h"
#include "Audio.h"
#include "Library/nlohmann/json.hpp"

#include "Game/MyLibrary/ResourceManager/ResourceType.h"


//------------------------------------------------------------------
/**
 * @class ResourceManager
 *
 * @brief 画像やモデル等のリソースを管理する
 */
class ResourceManager
{
//----------------------------------------------
// 変数
//----------------------------------------------
private:

	// モデルデータ格納用
	KT::Model::ModelList m_modelList;
	// テクスチャデータ格納用
	KT::Texture::TextureList m_textureList;
	// サウンドデータ格納用
	KT::Sound::SoundList m_soundList;
	// サウンド再生用
	std::unordered_map<std::string, DirectX::SoundEffectInstance*> m_soundPlayer;

//----------------------------------------------
// 関数
//----------------------------------------------
public:
	
	// コンストラクタ
	ResourceManager();
	// デストラクタ
	~ResourceManager();

	// モデルデータ取得
	DirectX::Model* GetModel(const std::string& name);
	// モデルリスト設定
	void SetModelList(KT::Model::ModelList list);
	// テクスチャデータ取得
	KT::Texture::TextureData GetTexture(const std::string& name);
	// テクスチャリスト設定
	void SetTextureList(KT::Texture::TextureList list);
	// サウンドリスト設定
	void SetSoundList(KT::Sound::SoundList list);
	// サウンド再生
	void PlaySound(const std::string& name, const int& soundNumber);
	void PlaySound(const std::string& name);
	// サウンド停止
	void StopSound(const std::string& name);
	// 音量調節
	void VolumeSetting(const std::string& name);
	void VolumeSetting(const std::string& name, const float& volume);

	// モデルリスト作成
	void CreateModelList(KT::File::CSVData pathList);
	// テクスチャ作成
	void CreateTextureList(KT::File::CSVData pathList);
	// サウンド作成
	void CreateSoundList(DirectX::AudioEngine* audioEngine, KT::File::CSVData pathList);

	// モデルデータ作成
	KT::Model::ModelData CreateModel(const wchar_t* textureDirectory, const wchar_t* path);
	// テクスチャデータの作成
	KT::Texture::TextureData CreateTexture(const wchar_t* path);
	// サウンドデータの作成
	KT::Sound::SoundData CreateSound(DirectX::AudioEngine* audioEngine, const wchar_t* path, const int& soundNum);
};