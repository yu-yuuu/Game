/**
 *
 * @file UIManager.cpp
 *
 * @brief UI�̊Ǘ��N���X�̃\�[�X�t�@�C��
 *
 * @author Kato Yuki
 *
 * @date 2024/1/14
 *
 *
 */
#include "pch.h"
#include "UIManager.h"

#include "Game/UI/UI.h"
#include "Game/MyLibrary/CommonResource/GameResource.h"
#include "Game/UI/SceneUI/SceneUI.h"
#include "Game/MyLibrary/Shader/Shader.h"

using namespace DirectX;

//----------------------------------------------
// �萔�錾
//----------------------------------------------

// ���_�f�[�^�̏��
const D3D11_INPUT_ELEMENT_DESC UIManager::UIVertexData::InputElements[] =
{
	{ "SV_Position", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "COLOR",       0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "TEXCOORD",    0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "TEXCOORD",    1, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
};

//------------------------------------------------------------------
/**
 * @brief �R���X�g���N�^
 *
 * @param �Ȃ�
 */
UIManager::UIManager()
	: m_uiList()
	, m_sceneUI(nullptr)
	, m_uiConstantBuffer{}
{
}

//------------------------------------------------------------------
/**
 * @brief �f�X�g���N�^
 *
 */
UIManager::~UIManager()
{
}

//------------------------------------------------------------------
/**
 * @brief ������
 *
 * @param  �Ȃ�
 * @return �Ȃ�
 */
void UIManager::Initialize()
{
	// �V�F�[�_�[�쐬
	m_shader = std::make_unique<Shader<UIVertexData>>();
	m_shader->CreateData(KT::Shader::UI);
	m_shader->CreateConstantBuffer<UIConstantBuffer>();
	// �萔�o�b�t�@�ɃE�B���h�E�T�C�Y��ݒ�
	DX::DeviceResources*  deviceResources = GameResource::GetInstance()->GetDeviceResources();
	RECT window = deviceResources->GetOutputSize();
	m_uiConstantBuffer.windowSize.x = static_cast<float>(window.right);
	m_uiConstantBuffer.windowSize.y = static_cast<float>(window.bottom);
}

//------------------------------------------------------------------
/**
 * @brief �X�V
 *
 * @param  �Ȃ�
 * @return �Ȃ�
 */
void UIManager::Update()
{
	// �V�[��UI�̍X�V
	if(m_sceneUI) m_sceneUI->Update();

	// �o�^����Ă���UI�̍X�V
	for (UI* ui : m_uiList)
	{
		ui->Update();
	}
}

//------------------------------------------------------------------
/**
 * @brief �`��
 *
 * @param  �Ȃ�
 * @return �Ȃ�
 */
void UIManager::Render()
{
	// �萔�o�b�t�@�̍X�V
	m_shader->UpdateConstantBuffer(m_uiConstantBuffer);
	// �o�^����Ă���UI�̕`��
	for (UI* ui : m_uiList)
	{
		ui->Render(this);
	}
}

//------------------------------------------------------------------
/**
 * @brief UI�̒ǉ�
 *
 * @param  ui�F�ǉ�����UI�̃|�C���^
 * @return �Ȃ�
 */
void UIManager::AddUI(UI* ui)
{
	if (std::find(m_uiList.begin(), m_uiList.end(), ui) == m_uiList.end())
	{
		m_uiList.push_back(ui);
	}
}

//------------------------------------------------------------------
/**
 * @brief UI�̒ǉ�
 *
 * @param  list�F�ǉ�����UI�̃��X�g(initializerList)
 * @return �Ȃ�
 */
void UIManager::AddUI(const std::initializer_list<UI*>& list)
{
	for (UI* ui : list)
	{
		AddUI(ui);
	}
}

//------------------------------------------------------------------
/**
 * @brief UI�̒ǉ�
 *
 * @param  list�F�ǉ�����UI�̃��X�g(vector)
 * @return �Ȃ�
 */
void UIManager::AddUI(const std::vector<UI*>& list)
{
	for (UI* ui : list)
	{
		AddUI(ui);
	}
}

//------------------------------------------------------------------
/**
 * @brief �o�^UI�̍폜
 *
 * @param deleteUI�F�o�^����������UI�̃|�C���^
 * @return �Ȃ�
 */
void UIManager::Delete(UI* deleteUI)
{
	// �폜����UI��T��
	std::vector<UI*>::iterator it = std::find(m_uiList.begin(), m_uiList.end(), deleteUI);
	
	// ��������
	if (it != m_uiList.end())
	{
		// �폜
		m_uiList.erase(it);
	}
}

//------------------------------------------------------------------
/**
 * @brief �o�^UI�̍폜(�ꊇ)
 *
 * @param list�F�o�^����������UI�̃��X�g(initializerList)
 * @return �Ȃ�
 */
void UIManager::Delete(const std::initializer_list<UI*>& list)
{
	for (UI* ui : list)
	{
		Delete(ui);
	}
}

//------------------------------------------------------------------
/**
 * @brief �o�^UI�̍폜(�ꊇ)
 *
 * @param list�F�o�^����������UI�̃��X�g(vector)
 * @return �Ȃ�
 */
void UIManager::Delete(const std::vector<UI*>& list)
{
	for (UI* ui : list)
	{
		Delete(ui);
	}
}

//------------------------------------------------------------------
/**
 * @brief �V�[��UI�̓o�^
 *
 * @param  sceneUI�F�o�^����V�[��UI
 * @return �Ȃ�
 */
void UIManager::SetSceneUI(SceneUI* sceneUI)
{
	m_sceneUI = sceneUI;
}

//------------------------------------------------------------------
/**
 * @brief �V�[��UI�̍폜
 *
 * @param  �Ȃ�
 * @return �Ȃ�
 */
void UIManager::DeleteSceneUI()
{
	m_sceneUI = nullptr;
}

//------------------------------------------------------------------
/**
 * @brief �o�^UI�̑S�폜
 *
 * @param  �Ȃ�
 * @return �Ȃ�
 */
void UIManager::Clear()
{
	m_uiList.clear();
	m_sceneUI = nullptr;
}

//------------------------------------------------------------------
/**
 * @brief �V�F�[�_�[�̎擾
 *
 * @param  �Ȃ�
 * @return Shader<Vertex>*�F�V�F�[�_�[�̃|�C���^
 */
Shader<UIManager::UIVertexData>* UIManager::GetShader() const
{
	return m_shader.get();
}
