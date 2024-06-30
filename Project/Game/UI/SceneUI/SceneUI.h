/**
 *
 * @file SceneUI.h
 *
 * @brief �V�[���ɔz�u����UI���܂Ƃ߂�N���X�̃w�b�_�[�t�@�C��
 *
 * @author Kato Yuki
 *
 * @date 2024/1/22
 *
 */
#pragma once

#include <vector>
#include <initializer_list>
#include <string>
#include <unordered_map>
#include "Game/MyLibrary/Texture/Texture.h"
#include "Game/MyLibrary/File/FileManager.h"
#include "Game/MyLibrary/CommonResource/GameResource.h"

class UI;
class OperatableUI;

class SceneUI
{
//----------------------------------------------
// �ϐ�
//----------------------------------------------
private:

	// UI���X�g
	std::unordered_map<std::string, std::unique_ptr<UI>> m_newList;

//----------------------------------------------
// �֐�
//----------------------------------------------
public:

	// �R���X�g���N�^
	SceneUI();
	// �f�X�g���N�^
	virtual ~SceneUI();
	// ������
	virtual void Initialize() = 0;
	// �X�V
	virtual void Update();

	// UI�}�l�[�W���[�֓o�^
	void AddUIManager(const std::string& tag);
	// UI�}�l�[�W���[�փ��X�g���S�Ă�UI��o�^
	void AddUIManagerAll();
	// UI�}�l�[�W���[����폜
	void DeleteUIManager(const std::string& tag);
	// UI�}�l�[�W���[�փ��X�g���S�Ă�UI���폜
	void DeleteUIManagerAll();
	// �V�[��UI���}�l�[�W���[�ɐݒ�
	void SetUIManagerSceneUI();
	// �V�[��UI���}�l�[�W���[����폜
	void DeleteUIManagerSceneUI();

	// UI�쐬�i�Ăяo���p�j
	void CreateUI(const std::string& sceneName);
	// ����UI�擾
	OperatableUI* GetUI(const std::string& name);

private:

	// �ʏ�UI�쐬
	std::unique_ptr<UI> CreateUI(
		const std::vector<std::string>& tagList,
		const std::string& texName,
		const Texture::AnchorPoint& anchor,
		const DirectX::SimpleMath::Vector2& position,
		const DirectX::SimpleMath::Vector2& scale,
		const DirectX::SimpleMath::Color& color,
		const bool& reverseX,
		const bool& reverseY
	);
	// ����UI�쐬
	std::unique_ptr<OperatableUI> CreateOperatableUI(
		const std::vector<std::string>& tagList,
		const std::string& texName,
		const Texture::AnchorPoint& anchor,
		const DirectX::SimpleMath::Vector2& position,
		const DirectX::SimpleMath::Vector2& scale,
		const DirectX::SimpleMath::Color& color,
		const DirectX::Keyboard::Keys& key,
		const bool& reverseX,
		const bool& reverseY
	);
};