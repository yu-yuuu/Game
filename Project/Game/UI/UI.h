/**
 *
 * @file UI.h
 *
 * @brief UI��\���N���X�̃w�b�_�[�t�@�C��
 *
 * @author Kato Yuki
 *
 * @date 2024/1/14
 *
 */
#pragma once

#include "Game/MyLibrary/ResourceManager/ResourceType.h"
#include "Game/MyLibrary/Texture/Texture.h"
#include "Game/UI/UIManager.h"

class UI
{
//----------------------------------------------
// �ϐ�
//----------------------------------------------
private:

	// �^�O
	std::vector<std::string> m_tagList;
	// �e�N�X�`���f�[�^
	std::unique_ptr<Texture> m_texture;
	// �`��ʒu
	DirectX::SimpleMath::Vector2 m_position;
	// ���]�\�������邩
	bool m_reverseX; // ��
	bool m_reverseY; // �c

//----------------------------------------------
//  �֐�
//----------------------------------------------
public:

	// �R���X�g���N�^
	UI(
		const std::vector<std::string>& tagList,
		std::unique_ptr<Texture> texture, 
		const DirectX::SimpleMath::Vector2& position, 
		bool reverseX = false, 
		bool reverseY = false);
	// �f�X�g���N�^
	~UI();

	// �X�V
	virtual void Update();
	// �`��
	void Render(UIManager* uiManager);

	// �^�O���X�g�̎擾
	std::vector<std::string> GetTagList() const;
	// �e�N�X�`���f�[�^�̎擾�A�ݒ�
	Texture* GetTexture() const;
	void SetTexture(std::unique_ptr<Texture> texture);
	// �ʒu�̎擾�A�ݒ�
	DirectX::SimpleMath::Vector2 GetPosition() const;
	void SetPosition(const DirectX::SimpleMath::Vector2& position);
};