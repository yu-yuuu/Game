/**
 *
 * @file Shader.h
 *
 * @brief シェーダーリソースを表すクラスのヘッダーファイル
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
// 変数
//----------------------------------------------
private:

	// プリミティブバッチ
	std::unique_ptr<DirectX::PrimitiveBatch<Vertex>> m_primitiveBatch;
	// 入力レイアウト
	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_inputLayout;
	// 定数バッファ
	Microsoft::WRL::ComPtr<ID3D11Buffer> m_buffer;
	// 頂点シェーダー
	Microsoft::WRL::ComPtr<ID3D11VertexShader> m_vertexShader;
	// ジオメトリシェーダー
	Microsoft::WRL::ComPtr<ID3D11GeometryShader> m_geometryShader;
	// ピクセルシェーダー
	Microsoft::WRL::ComPtr<ID3D11PixelShader> m_pixelShader;

	// 画像の登録スロット番号
	int m_registerTextureSlot;

//----------------------------------------------
// 関数
//----------------------------------------------
public:

	// コンストラクタ
	Shader();
	// デストラクタ
	~Shader();

	// シェーダーデータの作成
	void CreateData(const std::string& shaderName);
	// 定数バッファの作成
	template<typename ConstantBuffer>
	void CreateConstantBuffer();
	// 定数バッファの更新
	template<typename ConstantBuffer>
	void UpdateConstantBuffer(const ConstantBuffer& constantBuffer);
	// 画像登録
	void RegisterTexture(ID3D11ShaderResourceView** texture, std::vector<ID3D11SamplerState*> samplerState = std::vector<ID3D11SamplerState*>{});
	// 描画
	void Render(Vertex* vertex, int vertexCount = 1, std::function<void()> renderSetting = nullptr);
	void RenderQuad(const Vertex& v1, const Vertex& v2, const Vertex& v3, const Vertex& v4, std::function<void()> renderSetting = nullptr);

	// プリミティブバッチの取得
	DirectX::PrimitiveBatch<Vertex>* GetPrimitiveBatch() const;
	// 入力レイアウトの取得
	ID3D11InputLayout* GetInputLayout() const;
	// 定数バッファの取得
	ID3D11Buffer* GetBuffer() const;
	// 頂点シェーダーの取得
	ID3D11VertexShader* GetVertexShader() const;
	// ジオメトリシェーダーの取得
	ID3D11GeometryShader* GetGeometryShader() const;
	// ピクセルシェーダーの取得
	ID3D11PixelShader* GetPixelShader() const;

private:

	// シェーダーの読み込み
	bool LoadShader(std::vector<uint8_t>& shader, const std::string& path);
	// 共通の描画設定
	void CommonRenderSetting();
	// 描画のデフォルト設定
	void DefaultRenderSetting();
	// 描画の後の処理
	void AfterRender();
};

//----------------------------------------------
// 関数定義
//----------------------------------------------

//------------------------------------------------------------------
/**
 * @brief コンストラクタ
 *
 * @tparam Vertex：頂点データ
 * @param  なし
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
 * @brief デストラクタ
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
 * @brief シェーダーデータの作成
 *
 * @tparam Vertex    ：頂点データ
 * @param  shaderName：シェーダーの名前
 * @return なし
 */
template<typename Vertex>
inline void Shader<Vertex>::CreateData(const std::string& shaderName)
{	
	// 各種リソース取得
	GameResource*         gameResource = GameResource::GetInstance();
	ID3D11Device1*        device       = gameResource->GetDeviceResources()->GetD3DDevice();
	ID3D11DeviceContext1* context      = gameResource->GetDeviceResources()->GetD3DDeviceContext();
	FilePathList*         filePathList = gameResource->GetFilePathList();
	
	// プリミティブバッチ作成
	m_primitiveBatch = std::make_unique<DirectX::PrimitiveBatch<Vertex>>(context);

	// シェーダーをファイルから取得する
	nlohmann::json shaderFile = FileManager::LoadJSON(filePathList->GetPath(KT::File::SHADER));
	nlohmann::json data = shaderFile[shaderName];
	// 読み込んだシェーダー取得用
	std::vector<uint8_t> vs, gs, ps;

	// 頂点シェーダーを読み込む
	if (LoadShader(vs, data[KT::Shader::PROPERTIE_VS]))
	{
		// 入力レイアウト作成
		DX::ThrowIfFailed(device->CreateInputLayout(
				Vertex::InputElements, Vertex::InputElementCount,
				vs.data(), vs.size(),
				m_inputLayout.ReleaseAndGetAddressOf()));
		// 頂点シェーダー作成
		DX::ThrowIfFailed(device->CreateVertexShader(
				vs.data(), vs.size(), NULL,
				m_vertexShader.ReleaseAndGetAddressOf()));
	}
	// ジオメトリシェーダーを読み込む
	if (LoadShader(gs, data[KT::Shader::PROPERTIE_GS]))
	{
		// ジオメトリシェーダー作成
		DX::ThrowIfFailed(device->CreateGeometryShader(
				gs.data(), gs.size(), NULL,
				m_geometryShader.ReleaseAndGetAddressOf()));
	}
	// ピクセルシェーダーを読み込む
	if (LoadShader(ps, data[KT::Shader::PROPERTIE_PS]))
	{
		// ピクセルシェーダー作成
		DX::ThrowIfFailed(device->CreatePixelShader(
				ps.data(), ps.size(), NULL,
				m_pixelShader.ReleaseAndGetAddressOf()));
	}
}

//------------------------------------------------------------------
/**
 * @brief 定数バッファの作成
 *
 * @tparam Vertex        ：頂点データ
 * @tparam ConstantBuffer：定数バッファ
 * @param  なし
 * @return なし
 */
template<typename Vertex>
template<typename ConstantBuffer>
inline void Shader<Vertex>::CreateConstantBuffer()
{
	// デバイス取得	
	ID3D11Device1* device = GameResource::GetInstance()->GetDeviceResources()->GetD3DDevice();

	//シェーダーにデータを渡すためのコンスタントバッファ生成
	D3D11_BUFFER_DESC bd = {};
	bd.Usage          = D3D11_USAGE_DEFAULT;
	bd.ByteWidth      = sizeof(ConstantBuffer);
	bd.BindFlags      = D3D11_BIND_CONSTANT_BUFFER;
	bd.CPUAccessFlags = 0;
	DX::ThrowIfFailed(device->CreateBuffer(&bd, nullptr, &m_buffer));
}

//------------------------------------------------------------------
/**
 * @brief 定数バッファの更新
 *
 * @tparam Vertex        ：頂点データ
 * @tparam ConstantBuffer：定数バッファ
 * @param  constantBuffer：更新に使用する定数バッファ
 * @return なし
 */
template<typename Vertex>
template<typename ConstantBuffer>
inline void Shader<Vertex>::UpdateConstantBuffer(const ConstantBuffer& constantBuffer)
{
	// デバイスコンテキスト取得
	ID3D11DeviceContext1* context = GameResource::GetInstance()->GetDeviceResources()->GetD3DDeviceContext();
	// 定数バッファの更新
	context->UpdateSubresource(m_buffer.Get(), 0, NULL, &constantBuffer, 0, 0);
	// シェーダーにバッファを渡す
	ID3D11Buffer* cb[1] = { m_buffer.Get() };
	if(m_vertexShader)   context->VSSetConstantBuffers(0, 1, cb);
	if(m_geometryShader) context->GSSetConstantBuffers(0, 1, cb);
	if(m_pixelShader)    context->PSSetConstantBuffers(0, 1, cb);
}

//------------------------------------------------------------------
/**
 * @brief 画像登録
 *
 * @tparam Vertex      ：頂点データ
 * @param  texture     ：テクスチャデータ
 * @param  samplerState：画像サンプラー
 * @return なし
 */
template<typename Vertex>
inline void Shader<Vertex>::RegisterTexture(ID3D11ShaderResourceView** texture, std::vector<ID3D11SamplerState*> samplerState)
{
	// 各種リソース取得
	GameResource*          gameResource = GameResource::GetInstance();
	ID3D11DeviceContext1*  context      = gameResource->GetDeviceResources()->GetD3DDeviceContext();
	DirectX::CommonStates* commonStates = gameResource->GetCommonStates();

	// 画像用サンプラーの登録
	if (samplerState.empty()) samplerState.push_back(commonStates->LinearClamp());
	context->PSSetSamplers(0, static_cast<UINT>(samplerState.size()), samplerState.data());
	// ピクセルシェーダーに画像を設定
	context->PSSetShaderResources(m_registerTextureSlot++, 1, texture);
}

//------------------------------------------------------------------
/**
 * @brief 描画
 *
 * @tparam Vertex       ：頂点データ
 * @param  vertex       ：描画に使用する頂点
 * @param  vertexCount  ：頂点の数
 * @param  renderSetting：描画設定
 * @return なし
 */
template<typename Vertex>
inline void Shader<Vertex>::Render(Vertex* vertex, int vertexCount, std::function<void()> renderSetting)
{
	// 描画設定
	if (renderSetting) renderSetting();
	else               DefaultRenderSetting();
	CommonRenderSetting();
	// 描画
	m_primitiveBatch->Begin();
	m_primitiveBatch->Draw(D3D11_PRIMITIVE_TOPOLOGY_POINTLIST, vertex, vertexCount);
	m_primitiveBatch->End();
	// 描画後の処理
	AfterRender();
}

//------------------------------------------------------------------
/**
 * @brief 描画
 *
 * @tparam Vertex       ：頂点データ
 * @param  v1           ：描画に使用する頂点1
 * @param  v2           ：描画に使用する頂点2
 * @param  v3           ：描画に使用する頂点3
 * @param  v4           ：描画に使用する頂点4
 * @param  renderSetting：描画設定
 * @return なし
 */
template<typename Vertex>
inline void Shader<Vertex>::RenderQuad(const Vertex& v1, const Vertex& v2, const Vertex& v3, const Vertex& v4, std::function<void()> renderSetting)
{
	// 描画設定
	if (renderSetting) renderSetting();
	else               DefaultRenderSetting();
	CommonRenderSetting();	
	// 描画
	m_primitiveBatch->Begin();
	m_primitiveBatch->DrawQuad(v1, v2, v3, v4);
	m_primitiveBatch->End();
	// 描画後の処理
	AfterRender();
}

//------------------------------------------------------------------
/**
 * @brief プリミティブバッチの取得
 *
 * @tparam Vertex：頂点データ
 * @param  なし
 * @return PrimitiveBatch*：プリミティブバッチのポインタ
 */
template<typename Vertex>
inline DirectX::PrimitiveBatch<Vertex>* Shader<Vertex>::GetPrimitiveBatch() const
{
	return m_primitiveBatch.get();
}

//------------------------------------------------------------------
/**
 * @brief 入力レイアウトの取得
 *
 * @tparam Vertex：頂点データ
 * @param  なし
 * @return ID3D11InputLayout*：入力レイアウトのポインタ
 */
template<typename Vertex>
inline ID3D11InputLayout* Shader<Vertex>::GetInputLayout() const
{
	return m_inputLayout.Get();
}

//------------------------------------------------------------------
/**
 * @brief 定数バッファの取得
 *
 * @tparam Vertex：頂点データ
 * @param なし
 * @return ID3D11Buffer*：定数バッファのポインタ
 */
template<typename Vertex>
inline ID3D11Buffer* Shader<Vertex>::GetBuffer() const
{
	return m_buffer.Get();
}

//------------------------------------------------------------------
/**
 * @brief 頂点シェーダーの取得
 *
 * @tparam Vertex：頂点データ
 * @param  なし
 * @return ID3D11VertexShader*：頂点シェーダーのポインタ
 */
template<typename Vertex>
inline ID3D11VertexShader* Shader<Vertex>::GetVertexShader() const
{
	return m_vertexShader.Get();
}

//------------------------------------------------------------------
/**
 * @brief ジオメトリシェーダーの取得
 *
 * @tparam Vertex：頂点データ
 * @param  なし
 * @return ID3D11GeometryShader*：ジオメトリシェーダーのポインタ
 */
template<typename Vertex>
inline ID3D11GeometryShader* Shader<Vertex>::GetGeometryShader() const
{
	return m_geometryShader.Get();
}

//------------------------------------------------------------------
/**
 * @brief ピクセルシェーダーの取得
 *
 * @tparam Vertex：頂点データ
 * @param  なし
 * @return ID3D11PixelShader*：ピクセルシェーダーのポインタ
 */
template<typename Vertex>
inline ID3D11PixelShader* Shader<Vertex>::GetPixelShader() const
{
	return m_pixelShader.Get();
}

//------------------------------------------------------------------
/**
 * @brief シェーダーの読み込み
 *
 * @tparam Vertex：頂点データ
 * @param  shader：読み込んだデータ格納用
 * @param  path  ：シェーダーのパス
 * @return true  ：読み込み成功
 * @return false ：読み込み失敗
 */
template<typename Vertex>
inline bool Shader<Vertex>::LoadShader(std::vector<uint8_t>& shader, const std::string& path)
{
	// パスが設定されていないなら終了
	if (path.empty()) return false;

	// シェーダーを読み込む
	shader = DX::ReadData(KT::MyUtility::StringToWide(path).c_str());
	
	// 読み込み成功
	return true;
}

//------------------------------------------------------------------
/**
 * @brief 共通の描画設定
 *
 * @tparam Vertex：頂点データ
 * @param  なし
 * @return なし
 */
template<typename Vertex>
inline void Shader<Vertex>::CommonRenderSetting()
{
	// デバイスコンテキスト取得
	ID3D11DeviceContext1* context = GameResource::GetInstance()->GetDeviceResources()->GetD3DDeviceContext();
	// シェーダをセットする
	context->VSSetShader(m_vertexShader.Get(), nullptr, 0);
	context->GSSetShader(m_geometryShader.Get(), nullptr, 0);
	context->PSSetShader(m_pixelShader.Get(), nullptr, 0);
	//インプットレイアウトの登録
	context->IASetInputLayout(m_inputLayout.Get());
}

//------------------------------------------------------------------
/**
 * @brief 描画のデフォルト設定
 *
 * @tparam Vertex：頂点データ
 * @param  なし
 * @return なし
 */
template<typename Vertex>
inline void Shader<Vertex>::DefaultRenderSetting()
{
	// 各種リソース受け取り
	GameResource*          gameResource = GameResource::GetInstance();
	ID3D11DeviceContext1*  context      = gameResource->GetDeviceResources()->GetD3DDeviceContext();
	DirectX::CommonStates* commonStates = gameResource->GetCommonStates();

	//半透明描画指定
	ID3D11BlendState* blendstate = commonStates->NonPremultiplied();
	// 透明判定処理
	context->OMSetBlendState(blendstate, nullptr, 0xFFFFFFFF);
	// 深度バッファに書き込み参照する
	context->OMSetDepthStencilState(commonStates->DepthDefault(), 0);
	// カリングはしない
	context->RSSetState(commonStates->CullNone());
}

//------------------------------------------------------------------
/**
 * @brief  描画後の処理
 *
 * @tparam Vertex：頂点データ
 * @param  なし
 * @return なし
 */
template<typename Vertex>
inline void Shader<Vertex>::AfterRender()
{
	// デバイスコンテキスト取得
	ID3D11DeviceContext1* context = GameResource::GetInstance()->GetDeviceResources()->GetD3DDeviceContext();
	//シェーダの登録解除
	context->VSSetShader(nullptr, nullptr, 0);
	context->GSSetShader(nullptr, nullptr, 0);
	context->PSSetShader(nullptr, nullptr, 0);
	// 画像のスロット番号を初期化
	m_registerTextureSlot = 0;
}