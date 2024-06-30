// 頂点シェーダーの入力
struct VS_INPUT
{
    float3 Pos : SV_Position;
};

// ピクセルシェーダーの入力
struct PS_INPUT
{
    float4 Pos : SV_Position;
};

// 定数バッファ
cbuffer ConstantBuffer : register(b0)
{
    float4 Rate;// フェードの割合
}