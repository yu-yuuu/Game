/**
 *
 * @file Shader.h
 *
 * @brief �V�F�[�_�[���\�[�X��\���N���X�̃w�b�_�[�t�@�C��
 *
 * @author Kato Yuki
 *
 * @date 2024/5/7
 *
 */
#pragma once

#include <string>
#include <vector>
#include <functional>
#include "PrimitiveBatch.h"
#include "Library/DirectXTK_Helper/ReadData.h"
#include "Game/MyLibrary/ResourceManager/ResourceType.h"
#include "Game/MyLibrary/File/FileManager.h"
#include "Game/MyLibrary/CommonResource/GameResource.h"
#include "Game/MyLibrary/Utility/MyUtility.h"

template<typename Vertex>
class Shader
{
//----------------------------------------------
// �ϐ�
//----------------------------------------------
private:

	// �v���~�e�B�u�o�b�`
	std::unique_ptr<DirectX::PrimitiveBatch<Vertex>> m_primitiveBatch;
	// ���̓��C�A�E�g
	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_inputLayout;
	// �萔�o�b�t�@
	Microsoft::WRL::ComPtr<ID3D11Buffer> m_buffer;
	// ���_�V�F�[�_�[
	Microsoft::WRL::ComPtr<ID3D11VertexShader> m_vertexShader;
	// �W�I���g���V�F�[�_�[
	Microsoft::WRL::ComPtr<ID3D11GeometryShader> m_geometryShader;
	// �s�N�Z���V�F�[�_�[
	Microsoft::WRL::ComPtr<ID3D11PixelShader> m_pixelShader;

	// �摜�̓o�^�X���b�g�ԍ�
	int m_registerTextureSlot;

//----------------------------------------------
// �֐�
//----------------------------------------------
public:

	// �R���X�g���N�^
	Shader();
	// �f�X�g���N�^
	~Shader();

	// �V�F�[�_�[�f�[�^�̍쐬
	void CreateData(const std::string& shaderName);
	// �萔�o�b�t�@�̍쐬
	template<typename ConstantBuffer>
	void CreateConstantBuffer();
	// �萔�o�b�t�@�̍X�V
	template<typename ConstantBuffer>
	void UpdateConstantBuffer(const ConstantBuffer& constantBuffer);
	// �摜�o�^
	void RegisterTexture(ID3D11ShaderResourceView** texture, std::vector<ID3D11SamplerState*> samplerState = std::vector<ID3D11SamplerState*>{});
	// �`��
	void Render(Vertex* vertex, int vertexCount = 1, std::function<void()> renderSetting = nullptr);
	void RenderQuad(const Vertex& v1, const Vertex& v2, const Vertex& v3, const Vertex& v4, std::function<void()> renderSetting = nullptr);

	// �v���~�e�B�u�o�b�`�̎擾
	DirectX::PrimitiveBatch<Vertex>* GetPrimitiveBatch() const;
	// ���̓��C�A�E�g�̎擾
	ID3D11InputLayout* GetInputLayout() const;
	// �萔�o�b�t�@�̎擾
	ID3D11Buffer* GetBuffer() const;
	// ���_�V�F�[�_�[�̎擾
	ID3D11VertexShader* GetVertexShader() const;
	// �W�I���g���V�F�[�_�[�̎擾
	ID3D11GeometryShader* GetGeometryShader() const;
	// �s�N�Z���V�F�[�_�[�̎擾
	ID3D11PixelShader* GetPixelShader() const;

private:

	// �V�F�[�_�[�̓ǂݍ���
	bool LoadShader(std::vector<uint8_t>& shader, const std::string& path);
	// ���ʂ̕`��ݒ�
	void CommonRenderSetting();
	// �`��̃f�t�H���g�ݒ�
	void DefaultRenderSetting();
	// �`��̌�̏���
	void AfterRender();
};

//----------------------------------------------
// �֐���`
//----------------------------------------------

//------------------------------------------------------------------
/**
 * @brief �R���X�g���N�^
 *
 * @tparam Vertex�F���_�f�[�^
 * @param  �Ȃ�
 */
template<typename Vertex>
inline Shader<Vertex>::Shader()
	: m_primitiveBatch(nullptr)
	, m_inputLayout(nullptr)
	, m_buffer(nullptr)
	, m_vertexShader(nullptr)
	, m_geometryShader(nullptr)
	, m_pixelShader(nullptr)
	, m_registerTextureSlot(0)
{
}

//------------------------------------------------------------------
/**
 * @brief �f�X�g���N�^
 */
template<typename Vertex>
inline Shader<Vertex>::~Shader()
{
	m_primitiveBatch.reset();
	m_inputLayout.Reset();
	m_buffer.Reset();
	m_vertexShader.Reset();
	m_geometryShader.Reset();
	m_pixelShader.Reset();
}

//------------------------------------------------------------------
/**
 * @brief �V�F�[�_�[�f�[�^�̍쐬
 *
 * @tparam Vertex    �F���_�f�[�^
 * @param  shaderName�F�V�F�[�_�[�̖��O
 * @return �Ȃ�
 */
template<typename Vertex>
inline void Shader<Vertex>::CreateData(const std::string& shaderName)
{	
	// �e�탊�\�[�X�擾
	GameResource*         gameResource = GameResource::GetInstance();
	ID3D11Device1*        device       = gameResource->GetDeviceResources()->GetD3DDevice();
	ID3D11DeviceContext1* context      = gameResource->GetDeviceResources()->GetD3DDeviceContext();
	FilePathList*         filePathList = gameResource->GetFilePathList();
	
	// �v���~�e�B�u�o�b�`�쐬
	m_primitiveBatch = std::make_unique<DirectX::PrimitiveBatch<Vertex>>(context);

	// �V�F�[�_�[���t�@�C������擾����
	nlohmann::json shaderFile = FileManager::LoadJSON(filePathList->GetPath(KT::File::SHADER));
	nlohmann::json data = shaderFile[shaderName];
	// �ǂݍ��񂾃V�F�[�_�[�擾�p
	std::vector<uint8_t> vs, gs, ps;

	// ���_�V�F�[�_�[��ǂݍ���
	if (LoadShader(vs, data[KT::Shader::PROPERTIE_VS]))
	{
		// ���̓��C�A�E�g�쐬
		DX::ThrowIfFailed(device->CreateInputLayout(
				Vertex::InputElements, Vertex::InputElementCount,
				vs.data(), vs.size(),
				m_inputLayout.ReleaseAndGetAddressOf()));
		// ���_�V�F�[�_�[�쐬
		DX::ThrowIfFailed(device->CreateVertexShader(
				vs.data(), vs.size(), NULL,
				m_vertexShader.ReleaseAndGetAddressOf()));
	}
	// �W�I���g���V�F�[�_�[��ǂݍ���
	if (LoadShader(gs, data[KT::Shader::PROPERTIE_GS]))
	{
		// �W�I���g���V�F�[�_�[�쐬
		DX::ThrowIfFailed(device->CreateGeometryShader(
				gs.data(), gs.size(), NULL,
				m_geometryShader.ReleaseAndGetAddressOf()));
	}
	// �s�N�Z���V�F�[�_�[��ǂݍ���
	if (LoadShader(ps, data[KT::Shader::PROPERTIE_PS]))
	{
		// �s�N�Z���V�F�[�_�[�쐬
		DX::ThrowIfFailed(device->CreatePixelShader(
				ps.data(), ps.size(), NULL,
				m_pixelShader.ReleaseAndGetAddressOf()));
	}
}

//------------------------------------------------------------------
/**
 * @brief �萔�o�b�t�@�̍쐬
 *
 * @tparam Vertex        �F���_�f�[�^
 * @tparam ConstantBuffer�F�萔�o�b�t�@
 * @param  �Ȃ�
 * @return �Ȃ�
 */
template<typename Vertex>
template<typename ConstantBuffer>
inline void Shader<Vertex>::CreateConstantBuffer()
{
	// �f�o�C�X�擾	
	ID3D11Device1* device = GameResource::GetInstance()->GetDeviceResources()->GetD3DDevice();

	//�V�F�[�_�[�Ƀf�[�^��n�����߂̃R���X�^���g�o�b�t�@����
	D3D11_BUFFER_DESC bd = {};
	bd.Usage          = D3D11_USAGE_DEFAULT;
	bd.ByteWidth      = sizeof(ConstantBuffer);
	bd.BindFlags      = D3D11_BIND_CONSTANT_BUFFER;
	bd.CPUAccessFlags = 0;
	DX::ThrowIfFailed(device->CreateBuffer(&bd, nullptr, &m_buffer));
}

//------------------------------------------------------------------
/**
 * @brief �萔�o�b�t�@�̍X�V
 *
 * @tparam Vertex        �F���_�f�[�^
 * @tparam ConstantBuffer�F�萔�o�b�t�@
 * @param  constantBuffer�F�X�V�Ɏg�p����萔�o�b�t�@
 * @return �Ȃ�
 */
template<typename Vertex>
template<typename ConstantBuffer>
inline void Shader<Vertex>::UpdateConstantBuffer(const ConstantBuffer& constantBuffer)
{
	// �f�o�C�X�R���e�L�X�g�擾
	ID3D11DeviceContext1* context = GameResource::GetInstance()->GetDeviceResources()->GetD3DDeviceContext();
	// �萔�o�b�t�@�̍X�V
	context->UpdateSubresource(m_buffer.Get(), 0, NULL, &constantBuffer, 0, 0);
	// �V�F�[�_�[�Ƀo�b�t�@��n��
	ID3D11Buffer* cb[1] = { m_buffer.Get() };
	if(m_vertexShader)   context->VSSetConstantBuffers(0, 1, cb);
	if(m_geometryShader) context->GSSetConstantBuffers(0, 1, cb);
	if(m_pixelShader)    context->PSSetConstantBuffers(0, 1, cb);
}

//------------------------------------------------------------------
/**
 * @brief �摜�o�^
 *
 * @tparam Vertex      �F���_�f�[�^
 * @param  texture     �F�e�N�X�`���f�[�^
 * @param  samplerState�F�摜�T���v���[
 * @return �Ȃ�
 */
template<typename Vertex>
inline void Shader<Vertex>::RegisterTexture(ID3D11ShaderResourceView** texture, std::vector<ID3D11SamplerState*> samplerState)
{
	// �e�탊�\�[�X�擾
	GameResource*          gameResource = GameResource::GetInstance();
	ID3D11DeviceContext1*  context      = gameResource->GetDeviceResources()->GetD3DDeviceContext();
	DirectX::CommonStates* commonStates = gameResource->GetCommonStates();

	// �摜�p�T���v���[�̓o�^
	if (samplerState.empty()) samplerState.push_back(commonStates->LinearClamp());
	context->PSSetSamplers(0, static_cast<UINT>(samplerState.size()), samplerState.data());
	// �s�N�Z���V�F�[�_�[�ɉ摜��ݒ�
	context->PSSetShaderResources(m_registerTextureSlot++, 1, texture);
}

//------------------------------------------------------------------
/**
 * @brief �`��
 *
 * @tparam Vertex       �F���_�f�[�^
 * @param  vertex       �F�`��Ɏg�p���钸�_
 * @param  vertexCount  �F���_�̐�
 * @param  renderSetting�F�`��ݒ�
 * @return �Ȃ�
 */
template<typename Vertex>
inline void Shader<Vertex>::Render(Vertex* vertex, int vertexCount, std::function<void()> renderSetting)
{
	// �`��ݒ�
	if (renderSetting) renderSetting();
	else               DefaultRenderSetting();
	CommonRenderSetting();
	// �`��
	m_primitiveBatch->Begin();
	m_primitiveBatch->Draw(D3D11_PRIMITIVE_TOPOLOGY_POINTLIST, vertex, vertexCount);
	m_primitiveBatch->End();
	// �`���̏���
	AfterRender();
}

//------------------------------------------------------------------
/**
 * @brief �`��
 *
 * @tparam Vertex       �F���_�f�[�^
 * @param  v1           �F�`��Ɏg�p���钸�_1
 * @param  v2           �F�`��Ɏg�p���钸�_2
 * @param  v3           �F�`��Ɏg�p���钸�_3
 * @param  v4           �F�`��Ɏg�p���钸�_4
 * @param  renderSetting�F�`��ݒ�
 * @return �Ȃ�
 */
template<typename Vertex>
inline void Shader<Vertex>::RenderQuad(const Vertex& v1, const Vertex& v2, const Vertex& v3, const Vertex& v4, std::function<void()> renderSetting)
{
	// �`��ݒ�
	if (renderSetting) renderSetting();
	else               DefaultRenderSetting();
	CommonRenderSetting();	
	// �`��
	m_primitiveBatch->Begin();
	m_primitiveBatch->DrawQuad(v1, v2, v3, v4);
	m_primitiveBatch->End();
	// �`���̏���
	AfterRender();
}

//------------------------------------------------------------------
/**
 * @brief �v���~�e�B�u�o�b�`�̎擾
 *
 * @tparam Vertex�F���_�f�[�^
 * @param  �Ȃ�
 * @return PrimitiveBatch*�F�v���~�e�B�u�o�b�`�̃|�C���^
 */
template<typename Vertex>
inline DirectX::PrimitiveBatch<Vertex>* Shader<Vertex>::GetPrimitiveBatch() const
{
	return m_primitiveBatch.get();
}

//------------------------------------------------------------------
/**
 * @brief ���̓��C�A�E�g�̎擾
 *
 * @tparam Vertex�F���_�f�[�^
 * @param  �Ȃ�
 * @return ID3D11InputLayout*�F���̓��C�A�E�g�̃|�C���^
 */
template<typename Vertex>
inline ID3D11InputLayout* Shader<Vertex>::GetInputLayout() const
{
	return m_inputLayout.Get();
}

//------------------------------------------------------------------
/**
 * @brief �萔�o�b�t�@�̎擾
 *
 * @tparam Vertex�F���_�f�[�^
 * @param �Ȃ�
 * @return ID3D11Buffer*�F�萔�o�b�t�@�̃|�C���^
 */
template<typename Vertex>
inline ID3D11Buffer* Shader<Vertex>::GetBuffer() const
{
	return m_buffer.Get();
}

//------------------------------------------------------------------
/**
 * @brief ���_�V�F�[�_�[�̎擾
 *
 * @tparam Vertex�F���_�f�[�^
 * @param  �Ȃ�
 * @return ID3D11VertexShader*�F���_�V�F�[�_�[�̃|�C���^
 */
template<typename Vertex>
inline ID3D11VertexShader* Shader<Vertex>::GetVertexShader() const
{
	return m_vertexShader.Get();
}

//------------------------------------------------------------------
/**
 * @brief �W�I���g���V�F�[�_�[�̎擾
 *
 * @tparam Vertex�F���_�f�[�^
 * @param  �Ȃ�
 * @return ID3D11GeometryShader*�F�W�I���g���V�F�[�_�[�̃|�C���^
 */
template<typename Vertex>
inline ID3D11GeometryShader* Shader<Vertex>::GetGeometryShader() const
{
	return m_geometryShader.Get();
}

//------------------------------------------------------------------
/**
 * @brief �s�N�Z���V�F�[�_�[�̎擾
 *
 * @tparam Vertex�F���_�f�[�^
 * @param  �Ȃ�
 * @return ID3D11PixelShader*�F�s�N�Z���V�F�[�_�[�̃|�C���^
 */
template<typename Vertex>
inline ID3D11PixelShader* Shader<Vertex>::GetPixelShader() const
{
	return m_pixelShader.Get();
}

//------------------------------------------------------------------
/**
 * @brief �V�F�[�_�[�̓ǂݍ���
 *
 * @tparam Vertex�F���_�f�[�^
 * @param  shader�F�ǂݍ��񂾃f�[�^�i�[�p
 * @param  path  �F�V�F�[�_�[�̃p�X
 * @return true  �F�ǂݍ��ݐ���
 * @return false �F�ǂݍ��ݎ��s
 */
template<typename Vertex>
inline bool Shader<Vertex>::LoadShader(std::vector<uint8_t>& shader, const std::string& path)
{
	// �p�X���ݒ肳��Ă��Ȃ��Ȃ�I��
	if (path.empty()) return false;

	// �V�F�[�_�[��ǂݍ���
	shader = DX::ReadData(KT::MyUtility::StringToWide(path).c_str());
	
	// �ǂݍ��ݐ���
	return true;
}

//------------------------------------------------------------------
/**
 * @brief ���ʂ̕`��ݒ�
 *
 * @tparam Vertex�F���_�f�[�^
 * @param  �Ȃ�
 * @return �Ȃ�
 */
template<typename Vertex>
inline void Shader<Vertex>::CommonRenderSetting()
{
	// �f�o�C�X�R���e�L�X�g�擾
	ID3D11DeviceContext1* context = GameResource::GetInstance()->GetDeviceResources()->GetD3DDeviceContext();
	// �V�F�[�_���Z�b�g����
	context->VSSetShader(m_vertexShader.Get(), nullptr, 0);
	context->GSSetShader(m_geometryShader.Get(), nullptr, 0);
	context->PSSetShader(m_pixelShader.Get(), nullptr, 0);
	//�C���v�b�g���C�A�E�g�̓o�^
	context->IASetInputLayout(m_inputLayout.Get());
}

//------------------------------------------------------------------
/**
 * @brief �`��̃f�t�H���g�ݒ�
 *
 * @tparam Vertex�F���_�f�[�^
 * @param  �Ȃ�
 * @return �Ȃ�
 */
template<typename Vertex>
inline void Shader<Vertex>::DefaultRenderSetting()
{
	// �e�탊�\�[�X�󂯎��
	GameResource*          gameResource = GameResource::GetInstance();
	ID3D11DeviceContext1*  context      = gameResource->GetDeviceResources()->GetD3DDeviceContext();
	DirectX::CommonStates* commonStates = gameResource->GetCommonStates();

	//�������`��w��
	ID3D11BlendState* blendstate = commonStates->NonPremultiplied();
	// �������菈��
	context->OMSetBlendState(blendstate, nullptr, 0xFFFFFFFF);
	// �[�x�o�b�t�@�ɏ������ݎQ�Ƃ���
	context->OMSetDepthStencilState(commonStates->DepthDefault(), 0);
	// �J�����O�͂��Ȃ�
	context->RSSetState(commonStates->CullNone());
}

//------------------------------------------------------------------
/**
 * @brief  �`���̏���
 *
 * @tparam Vertex�F���_�f�[�^
 * @param  �Ȃ�
 * @return �Ȃ�
 */
template<typename Vertex>
inline void Shader<Vertex>::AfterRender()
{
	// �f�o�C�X�R���e�L�X�g�擾
	ID3D11DeviceContext1* context = GameResource::GetInstance()->GetDeviceResources()->GetD3DDeviceContext();
	//�V�F�[�_�̓o�^����
	context->VSSetShader(nullptr, nullptr, 0);
	context->GSSetShader(nullptr, nullptr, 0);
	context->PSSetShader(nullptr, nullptr, 0);
	// �摜�̃X���b�g�ԍ���������
	m_registerTextureSlot = 0;
}