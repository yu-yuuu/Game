/**
 *
 * @file ResourceManager.cpp
 *
 * @brief �摜�⃂�f�����̃��\�[�X�̍쐬�A�Ǘ�����N���X�̃\�[�X�t�@�C��
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
  * @brief �R���X�g���N�^
  *
  * @param �Ȃ�
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
 * @brief �f�X�g���N�^
 */
ResourceManager::~ResourceManager()
{
	m_textureList.clear();
	m_modelList.clear();
}

//------------------------------------------------------------------
/**
 * @brief ���f���f�[�^�̎擾
 *
 * @param  name  �F�擾���������f���̖��O
 * @return Model*�F���f���ւ̃|�C���^
 */
DirectX::Model* ResourceManager::GetModel(const std::string& name)
{
	return m_modelList.at(name).get();
}

//------------------------------------------------------------------
/**
 * @brief ���f�����X�g�̐ݒ�
 *
 * @param  list�F�ݒ肷�郂�f�����X�g
 * @return �Ȃ�
 */
void ResourceManager::SetModelList(KT::Model::ModelList list)
{
	m_modelList = std::move(list);
}

//------------------------------------------------------------------
/**
 * @brief �e�N�X�`���f�[�^�̎擾
 *
 * @param  name       �F�擾�������e�N�X�`���̖��O
 * @return TextureData�F�e�N�X�`���f�[�^
 */
KT::Texture::TextureData ResourceManager::GetTexture(const std::string& name)
{
	return m_textureList.at(name);
}

//------------------------------------------------------------------
/**
 * @brief �e�N�X�`�����X�g�̐ݒ�
 *
 * @param  list�F�ݒ肷��e�N�X�`�����X�g
 * @return �Ȃ�
 */
void ResourceManager::SetTextureList(KT::Texture::TextureList list)
{
	m_textureList = list;
}

//------------------------------------------------------------------
/**
 * @brief �T�E���h���X�g�̐ݒ�
 *
 * @param  list�F�ݒ肷��T�E���h���X�g
 * @return �Ȃ�
 */
void ResourceManager::SetSoundList(KT::Sound::SoundList list)
{
	m_soundList = std::move(list);
}

//------------------------------------------------------------------
/**
 * @brief �T�E���h�Đ�
 *
 * @param  name       �F�T�E���h�̎��
 * @param  soundNumber�F�Đ�����T�E���h�̔ԍ�
 * @return �Ȃ�
 */
void ResourceManager::PlaySound(const std::string& name, const int& soundNumber)
{
	// �Đ�����T�E���h�f�[�^�擾
	m_soundPlayer[name] = m_soundList[name].sound[soundNumber].get();
	// ���ʒ���
	VolumeSetting(name);
	// �Đ�
	PlaySound(name);
}

//------------------------------------------------------------------
/**
 * @brief �T�E���h�Đ�
 *
 * @param  name�F�T�E���h�̎��
 * @return �Ȃ�
 */
void ResourceManager::PlaySound(const std::string& name)
{
	// �Đ�
	m_soundPlayer[name]->Stop();
	m_soundPlayer[name]->Play(KT::Sound::BGM == name);
}

//------------------------------------------------------------------
/**
 * @brief �T�E���h��~
 *
 * @param  name�F�T�E���h�̎��
 * @return �Ȃ�
 */
void ResourceManager::StopSound(const std::string& name)
{
	// ��~
	m_soundPlayer[name]->Stop();
}

//------------------------------------------------------------------
/**
 * @brief ���ʒ���
 *
 * @param  name�F�T�E���h�̎��
 * @return �Ȃ�
 */
void ResourceManager::VolumeSetting(const std::string& name)
{
	// ���ʃI�v�V�����f�[�^���擾����
	FilePathList* filePathList = GameResource::GetInstance()->GetFilePathList();
	nlohmann::json data = FileManager::LoadJSON(filePathList->GetPath(KT::File::OPTION));
	// ���ʒ���
	VolumeSetting(name, data[KT::Sound::PROPERTIE_SOUND][name]);
}

//------------------------------------------------------------------
/**
 * @brief ���ʒ���
 *
 * @param  name  �F�T�E���h�̎��
 * @param  volume�F���ʁi0 �` 1�j
 * @return �Ȃ�
 */
void ResourceManager::VolumeSetting(const std::string& name, const float& volume)
{
	// ���ʒ���
	m_soundPlayer[name]->SetVolume(volume);
}

//------------------------------------------------------------------
/**
 * @brief ���f�����X�g�̍쐬
 *
 * @param  path     �F���f���̃t�@�C���p�X���X�g
 * @return ModelList�F�쐬�������f�����X�g
 */
void ResourceManager::CreateModelList(KT::File::CSVData pathList)
{
	// �ϐ��錾
	std::string  name;      // ���f���̖��O
	std::string  filePath;  // ���f���̃t�@�C���p�X
	std::wstring directory; // ���f���e�N�X�`���̃t�@�C���p�X

	// �f�[�^�ǂݍ���
	for (std::stringstream& ss : pathList)
	{
		// �f�[�^�擾
		ss >> name >> filePath;

		// ���f���e�N�X�`����
		if (name == KT::Model::TEXTURE_DIRECTORY)
		{
			// �擾���Ď���
			directory = KT::MyUtility::StringToWide(filePath);
			continue;
		}

		// ���f���f�[�^�쐬
		m_modelList[name] = std::move(CreateModel(directory.c_str(), KT::MyUtility::StringToWide(filePath).c_str()));
	}
}

//------------------------------------------------------------------
/**
 * @brief �e�N�X�`�����X�g�̍쐬
 *
 * @param  path     �F�e�N�X�`���̃t�@�C���p�X���X�g
 * @return ModelList�F�쐬�����e�N�X�`�����X�g
 */
void ResourceManager::CreateTextureList(KT::File::CSVData pathList)
{
	// �ϐ��錾
	std::string name;     // �e�N�X�`���̖��O
	std::string filePath; // �e�N�X�`���̃t�@�C���p�X

	// �f�[�^�ǂݍ���
	for (std::stringstream& ss : pathList)
	{
		// �f�[�^�擾
		ss >> name >> filePath;
		// �e�N�X�`���f�[�^�쐬
		m_textureList[name] = CreateTexture(KT::MyUtility::StringToWide(filePath).c_str());
	}
}

//------------------------------------------------------------------
/**
 * @brief �T�E���h���X�g�쐬
 *
 * @param  audioEngine  �F�I�[�f�B�I�G���W��
 * @param  path         �F�T�E���h�̃t�@�C���p�X���X�g
 * @return SoundList    �F�쐬�����T�E���h���X�g
 */
void ResourceManager::CreateSoundList(DirectX::AudioEngine* audioEngine, KT::File::CSVData pathList)
{
	// �ϐ��錾
	std::string name;     // �T�E���h�̖��O
	std::string filePath; // �T�E���h�̃t�@�C���p�X
	int         soundNum; // �T�E���h�̐�

	// �f�[�^�ǂݍ���
	for (std::stringstream& ss : pathList)
	{
		// �f�[�^�擾
		ss >> name >> filePath >> soundNum;
		// ���X�g�֊i�[
		m_soundList[name] = std::move(CreateSound(audioEngine, KT::MyUtility::StringToWide(filePath).c_str(), soundNum));
	}
}

//------------------------------------------------------------------
/**
 * @brief ���f���f�[�^�̍쐬
 *
 * @param  texturePath�F���f���Ɏg�p����e�N�X�`���̃f�B���N�g��
 * @param  path       �F���f���̃p�X
 * @return ModelData  �F�쐬�������f���f�[�^
 */
KT::Model::ModelData ResourceManager::CreateModel(const wchar_t* textureDirectory, const wchar_t* path)
{
	// ���L���\�[�X�̃C���X�^���X�擾
	GameResource* gameResource = GameResource::GetInstance();
	// �f�o�C�X�̎擾
	ID3D11Device1* device = gameResource->GetDeviceResources()->GetD3DDevice();

	// �G�t�F�N�g�t�@�N�g���[�̍쐬
	std::unique_ptr<EffectFactory> effectFactory = std::make_unique<EffectFactory>(device);
	// �e�N�X�`���̃f�B���N�g���ݒ�
	effectFactory->SetDirectory(textureDirectory);

	// ���f���ǂݍ���
	return std::move(Model::CreateFromCMO(device, path, *effectFactory));
}

//------------------------------------------------------------------
/**
 * @brief �e�N�X�`���f�[�^�̍쐬
 *
 * @param  path       �F�e�N�X�`���̃p�X
 * @return TextureData�F�쐬�����e�N�X�`���f�[�^
 */
KT::Texture::TextureData ResourceManager::CreateTexture(const wchar_t* path)
{
	// ���L���\�[�X�̃C���X�^���X�擾
	GameResource* gameResource = GameResource::GetInstance();
	// �f�o�C�X�̎擾
	ID3D11Device1* device = gameResource->GetDeviceResources()->GetD3DDevice();
	// �ǂݎ��p�ϐ���`
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> shaderResourceView;
	Microsoft::WRL::ComPtr<ID3D11Texture2D> texture2D;
	Microsoft::WRL::ComPtr<ID3D11Resource> resource;

	// �摜�ǂݍ���
	DX::ThrowIfFailed(
		CreateDDSTextureFromFile(
			device,
			path,
			resource.ReleaseAndGetAddressOf(),
			shaderResourceView.ReleaseAndGetAddressOf()
		)
	);

	// Texture2D�擾
	DX::ThrowIfFailed(resource.As(&texture2D));
	// �摜�T�C�Y�擾
	D3D11_TEXTURE2D_DESC desc;
	texture2D->GetDesc(&desc);
	SimpleMath::Vector2 size;
	size.x = static_cast<float>(desc.Width);
	size.y = static_cast<float>(desc.Height);

	// �f�[�^��Ԃ�
	return KT::Texture::TextureData{ shaderResourceView, size };
}

//------------------------------------------------------------------
/**
 * @brief �T�E���h�f�[�^�̍쐬
 *
 * @param  audioEngine�F�I�[�f�B�I�G���W��
 * @param  path       �F�e�N�X�`���̃p�X
 * @param  soundNum   �F�T�E���h�̐�
 * @return TextureData�F�쐬�����e�N�X�`���f�[�^
 */
KT::Sound::SoundData ResourceManager::CreateSound(DirectX::AudioEngine* audioEngine, const wchar_t* path, const int& soundNum)
{
	// �E�F�[�u�o���N�쐬
	std::unique_ptr<WaveBank> wb = std::make_unique<WaveBank>(audioEngine, path);

	// �T�E���h�̐������z����m��
	std::vector<std::unique_ptr<DirectX::SoundEffectInstance>> sound;
	sound.resize(soundNum);

	// �T�E���h�f�[�^�쐬
	for (int i = 0; i < soundNum; i++)
	{
		// �T�E���h�f�[�^�쐬
		sound[i] = wb->CreateInstance(i);
	}

	return std::move(KT::Sound::SoundData{ std::move(wb), std::move(sound) });
}