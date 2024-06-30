/**
 *
 * @file UIManager.h
 *
 * @brief UI�̊Ǘ��N���X�̃w�b�_�[�t�@�C��
 *
 * @author Kato Yuki
 *
 * @date 2024/1/14
 *
 */
#pragma once

#include <vector>
#include <initializer_list>
#include "PrimitiveBatch.h"
#include "VertexTypes.h"

class UI;
class SceneUI;
template<typename Vertex>
class Shader;

class UIManager
{
//----------------------------------------------
// �\����
//----------------------------------------------
private:

	// UI�Ɏg�p����萔�o�b�t�@
	struct UIConstantBuffer
	{
		DirectX::SimpleMath::Vector4 windowSize; // �E�B���h�E�T�C�Y
	};

public:

	// UI�̒��_�f�[�^
	struct UIVertexData
	{
		DirectX::SimpleMath::Vector4 position;
		DirectX::SimpleMath::Vector4 color;
		DirectX::SimpleMath::Vector4 tex;
		DirectX::SimpleMath::Vector4 reverse;

		// ���_�f�[�^�̐�
		static const int InputElementCount = 4;
		// ���_�f�[�^�̏��
		static const D3D11_INPUT_ELEMENT_DESC InputElements[InputElementCount];
	};

//----------------------------------------------
// �ϐ�
//----------------------------------------------
private:

	// UI���X�g
	std::vector<UI*> m_uiList;
	// �V�[��UI
	SceneUI* m_sceneUI;
	// �V�F�[�_�[
	std::unique_ptr<Shader<UIVertexData>> m_shader;
	// UI�̒萔�o�b�t�@
	UIConstantBuffer m_uiConstantBuffer;

//----------------------------------------------
// �֐�
//----------------------------------------------
public:

	// �R���X�g���N�^
	UIManager();
	// �f�X�g���N�^
	~UIManager();

	// ������
	void Initialize();
	// �X�V
	void Update();
	// �`��
	void Render();

	// UI�̒ǉ�
	void AddUI(UI* ui);
	// UI�̒ǉ�(�ꊇ)
	void AddUI(const std::initializer_list<UI*>& list);
	void AddUI(const std::vector<UI*>& list);
	// �o�^UI�̍폜
	void Delete(UI* deleteUI);
	// �o�^UI�̍폜(�ꊇ)
	void Delete(const std::initializer_list<UI*>& list);
	void Delete(const std::vector<UI*>& list);
	// �V�[��UI�̓o�^
	void SetSceneUI(SceneUI* sceneUI);
	// �V�[��UI�̍폜
	void DeleteSceneUI();
	// �o�^UI�̑S�폜
	void Clear();

	// �V�F�[�_�[�̎擾
	Shader<UIVertexData>* GetShader() const;
};