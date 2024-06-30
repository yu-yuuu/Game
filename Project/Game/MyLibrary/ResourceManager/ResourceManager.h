/**
 *
 * @file ResourceManager.h
 *
 * @brief �摜�⃂�f�����̃��\�[�X�̍쐬�A�Ǘ�����N���X�̃w�b�_�[�t�@�C��
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
 * @brief �摜�⃂�f�����̃��\�[�X���Ǘ�����
 */
class ResourceManager
{
//----------------------------------------------
// �ϐ�
//----------------------------------------------
private:

	// ���f���f�[�^�i�[�p
	KT::Model::ModelList m_modelList;
	// �e�N�X�`���f�[�^�i�[�p
	KT::Texture::TextureList m_textureList;
	// �T�E���h�f�[�^�i�[�p
	KT::Sound::SoundList m_soundList;
	// �T�E���h�Đ��p
	std::unordered_map<std::string, DirectX::SoundEffectInstance*> m_soundPlayer;

//----------------------------------------------
// �֐�
//----------------------------------------------
public:
	
	// �R���X�g���N�^
	ResourceManager();
	// �f�X�g���N�^
	~ResourceManager();

	// ���f���f�[�^�擾
	DirectX::Model* GetModel(const std::string& name);
	// ���f�����X�g�ݒ�
	void SetModelList(KT::Model::ModelList list);
	// �e�N�X�`���f�[�^�擾
	KT::Texture::TextureData GetTexture(const std::string& name);
	// �e�N�X�`�����X�g�ݒ�
	void SetTextureList(KT::Texture::TextureList list);
	// �T�E���h���X�g�ݒ�
	void SetSoundList(KT::Sound::SoundList list);
	// �T�E���h�Đ�
	void PlaySound(const std::string& name, const int& soundNumber);
	void PlaySound(const std::string& name);
	// �T�E���h��~
	void StopSound(const std::string& name);
	// ���ʒ���
	void VolumeSetting(const std::string& name);
	void VolumeSetting(const std::string& name, const float& volume);

	// ���f�����X�g�쐬
	void CreateModelList(KT::File::CSVData pathList);
	// �e�N�X�`���쐬
	void CreateTextureList(KT::File::CSVData pathList);
	// �T�E���h�쐬
	void CreateSoundList(DirectX::AudioEngine* audioEngine, KT::File::CSVData pathList);

	// ���f���f�[�^�쐬
	KT::Model::ModelData CreateModel(const wchar_t* textureDirectory, const wchar_t* path);
	// �e�N�X�`���f�[�^�̍쐬
	KT::Texture::TextureData CreateTexture(const wchar_t* path);
	// �T�E���h�f�[�^�̍쐬
	KT::Sound::SoundData CreateSound(DirectX::AudioEngine* audioEngine, const wchar_t* path, const int& soundNum);
};