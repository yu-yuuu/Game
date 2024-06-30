/**
 *
 * @file ResourceManager.cpp
 *
 * @brief 画像やモデル等のリソースの作成、管理するクラスのソースファイル
 *
 * @author Kato Yuki
 *
 * @date 2023/9/7
 *
 */
#include "pch.h"
#include "ResourceManager.h"

#include <fstream>
#include <sstream>
#include "Effects.h"
#include "DDSTextureLoader.h"
#include "Library/nlohmann/json.hpp"

#include "Game/MyLibrary/File/FileManager.h"
#include "Game/MyLibrary/CommonResource/GameResource.h"
#include "Game/MyLibrary/Utility/MyUtility.h"


using namespace DirectX;

 //------------------------------------------------------------------
 /**
  * @brief コンストラクタ
  *
  * @param なし
  */
ResourceManager::ResourceManager()
	: m_modelList()
	, m_textureList()
	, m_soundList()
	, m_soundPlayer()
{
}

//------------------------------------------------------------------
/**
 * @brief デストラクタ
 */
ResourceManager::~ResourceManager()
{
	m_textureList.clear();
	m_modelList.clear();
}

//------------------------------------------------------------------
/**
 * @brief モデルデータの取得
 *
 * @param  name  ：取得したいモデルの名前
 * @return Model*：モデルへのポインタ
 */
DirectX::Model* ResourceManager::GetModel(const std::string& name)
{
	return m_modelList.at(name).get();
}

//------------------------------------------------------------------
/**
 * @brief モデルリストの設定
 *
 * @param  list：設定するモデルリスト
 * @return なし
 */
void ResourceManager::SetModelList(KT::Model::ModelList list)
{
	m_modelList = std::move(list);
}

//------------------------------------------------------------------
/**
 * @brief テクスチャデータの取得
 *
 * @param  name       ：取得したいテクスチャの名前
 * @return TextureData：テクスチャデータ
 */
KT::Texture::TextureData ResourceManager::GetTexture(const std::string& name)
{
	return m_textureList.at(name);
}

//------------------------------------------------------------------
/**
 * @brief テクスチャリストの設定
 *
 * @param  list：設定するテクスチャリスト
 * @return なし
 */
void ResourceManager::SetTextureList(KT::Texture::TextureList list)
{
	m_textureList = list;
}

//------------------------------------------------------------------
/**
 * @brief サウンドリストの設定
 *
 * @param  list：設定するサウンドリスト
 * @return なし
 */
void ResourceManager::SetSoundList(KT::Sound::SoundList list)
{
	m_soundList = std::move(list);
}

//------------------------------------------------------------------
/**
 * @brief サウンド再生
 *
 * @param  name       ：サウンドの種類
 * @param  soundNumber：再生するサウンドの番号
 * @return なし
 */
void ResourceManager::PlaySound(const std::string& name, const int& soundNumber)
{
	// 再生するサウンドデータ取得
	m_soundPlayer[name] = m_soundList[name].sound[soundNumber].get();
	// 音量調節
	VolumeSetting(name);
	// 再生
	PlaySound(name);
}

//------------------------------------------------------------------
/**
 * @brief サウンド再生
 *
 * @param  name：サウンドの種類
 * @return なし
 */
void ResourceManager::PlaySound(const std::string& name)
{
	// 再生
	m_soundPlayer[name]->Stop();
	m_soundPlayer[name]->Play(KT::Sound::BGM == name);
}

//------------------------------------------------------------------
/**
 * @brief サウンド停止
 *
 * @param  name：サウンドの種類
 * @return なし
 */
void ResourceManager::StopSound(const std::string& name)
{
	// 停止
	m_soundPlayer[name]->Stop();
}

//------------------------------------------------------------------
/**
 * @brief 音量調節
 *
 * @param  name：サウンドの種類
 * @return なし
 */
void ResourceManager::VolumeSetting(const std::string& name)
{
	// 音量オプションデータを取得する
	FilePathList* filePathList = GameResource::GetInstance()->GetFilePathList();
	nlohmann::json data = FileManager::LoadJSON(filePathList->GetPath(KT::File::OPTION));
	// 音量調節
	VolumeSetting(name, data[KT::Sound::PROPERTIE_SOUND][name]);
}

//------------------------------------------------------------------
/**
 * @brief 音量調節
 *
 * @param  name  ：サウンドの種類
 * @param  volume：音量（0 ～ 1）
 * @return なし
 */
void ResourceManager::VolumeSetting(const std::string& name, const float& volume)
{
	// 音量調節
	m_soundPlayer[name]->SetVolume(volume);
}

//------------------------------------------------------------------
/**
 * @brief モデルリストの作成
 *
 * @param  path     ：モデルのファイルパスリスト
 * @return ModelList：作成したモデルリスト
 */
void ResourceManager::CreateModelList(KT::File::CSVData pathList)
{
	// 変数宣言
	std::string  name;      // モデルの名前
	std::string  filePath;  // モデルのファイルパス
	std::wstring directory; // モデルテクスチャのファイルパス

	// データ読み込み
	for (std::stringstream& ss : pathList)
	{
		// データ取得
		ss >> name >> filePath;

		// モデルテクスチャか
		if (name == KT::Model::TEXTURE_DIRECTORY)
		{
			// 取得して次へ
			directory = KT::MyUtility::StringToWide(filePath);
			continue;
		}

		// モデルデータ作成
		m_modelList[name] = std::move(CreateModel(directory.c_str(), KT::MyUtility::StringToWide(filePath).c_str()));
	}
}

//------------------------------------------------------------------
/**
 * @brief テクスチャリストの作成
 *
 * @param  path     ：テクスチャのファイルパスリスト
 * @return ModelList：作成したテクスチャリスト
 */
void ResourceManager::CreateTextureList(KT::File::CSVData pathList)
{
	// 変数宣言
	std::string name;     // テクスチャの名前
	std::string filePath; // テクスチャのファイルパス

	// データ読み込み
	for (std::stringstream& ss : pathList)
	{
		// データ取得
		ss >> name >> filePath;
		// テクスチャデータ作成
		m_textureList[name] = CreateTexture(KT::MyUtility::StringToWide(filePath).c_str());
	}
}

//------------------------------------------------------------------
/**
 * @brief サウンドリスト作成
 *
 * @param  audioEngine  ：オーディオエンジン
 * @param  path         ：サウンドのファイルパスリスト
 * @return SoundList    ：作成したサウンドリスト
 */
void ResourceManager::CreateSoundList(DirectX::AudioEngine* audioEngine, KT::File::CSVData pathList)
{
	// 変数宣言
	std::string name;     // サウンドの名前
	std::string filePath; // サウンドのファイルパス
	int         soundNum; // サウンドの数

	// データ読み込み
	for (std::stringstream& ss : pathList)
	{
		// データ取得
		ss >> name >> filePath >> soundNum;
		// リストへ格納
		m_soundList[name] = std::move(CreateSound(audioEngine, KT::MyUtility::StringToWide(filePath).c_str(), soundNum));
	}
}

//------------------------------------------------------------------
/**
 * @brief モデルデータの作成
 *
 * @param  texturePath：モデルに使用するテクスチャのディレクトリ
 * @param  path       ：モデルのパス
 * @return ModelData  ：作成したモデルデータ
 */
KT::Model::ModelData ResourceManager::CreateModel(const wchar_t* textureDirectory, const wchar_t* path)
{
	// 共有リソースのインスタンス取得
	GameResource* gameResource = GameResource::GetInstance();
	// デバイスの取得
	ID3D11Device1* device = gameResource->GetDeviceResources()->GetD3DDevice();

	// エフェクトファクトリーの作成
	std::unique_ptr<EffectFactory> effectFactory = std::make_unique<EffectFactory>(device);
	// テクスチャのディレクトリ設定
	effectFactory->SetDirectory(textureDirectory);

	// モデル読み込み
	return std::move(Model::CreateFromCMO(device, path, *effectFactory));
}

//------------------------------------------------------------------
/**
 * @brief テクスチャデータの作成
 *
 * @param  path       ：テクスチャのパス
 * @return TextureData：作成したテクスチャデータ
 */
KT::Texture::TextureData ResourceManager::CreateTexture(const wchar_t* path)
{
	// 共有リソースのインスタンス取得
	GameResource* gameResource = GameResource::GetInstance();
	// デバイスの取得
	ID3D11Device1* device = gameResource->GetDeviceResources()->GetD3DDevice();
	// 読み取り用変数定義
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> shaderResourceView;
	Microsoft::WRL::ComPtr<ID3D11Texture2D> texture2D;
	Microsoft::WRL::ComPtr<ID3D11Resource> resource;

	// 画像読み込み
	DX::ThrowIfFailed(
		CreateDDSTextureFromFile(
			device,
			path,
			resource.ReleaseAndGetAddressOf(),
			shaderResourceView.ReleaseAndGetAddressOf()
		)
	);

	// Texture2D取得
	DX::ThrowIfFailed(resource.As(&texture2D));
	// 画像サイズ取得
	D3D11_TEXTURE2D_DESC desc;
	texture2D->GetDesc(&desc);
	SimpleMath::Vector2 size;
	size.x = static_cast<float>(desc.Width);
	size.y = static_cast<float>(desc.Height);

	// データを返す
	return KT::Texture::TextureData{ shaderResourceView, size };
}

//------------------------------------------------------------------
/**
 * @brief サウンドデータの作成
 *
 * @param  audioEngine：オーディオエンジン
 * @param  path       ：テクスチャのパス
 * @param  soundNum   ：サウンドの数
 * @return TextureData：作成したテクスチャデータ
 */
KT::Sound::SoundData ResourceManager::CreateSound(DirectX::AudioEngine* audioEngine, const wchar_t* path, const int& soundNum)
{
	// ウェーブバンク作成
	std::unique_ptr<WaveBank> wb = std::make_unique<WaveBank>(audioEngine, path);

	// サウンドの数だけ配列を確保
	std::vector<std::unique_ptr<DirectX::SoundEffectInstance>> sound;
	sound.resize(soundNum);

	// サウンドデータ作成
	for (int i = 0; i < soundNum; i++)
	{
		// サウンドデータ作成
		sound[i] = wb->CreateInstance(i);
	}

	return std::move(KT::Sound::SoundData{ std::move(wb), std::move(sound) });
}