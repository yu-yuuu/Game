// 頂点シェーダーの入力
struct VS_INPUT
{
    float3 Pos : SV_Position;
    float2 Tex : TEXCOORD;
    float4 Col : COLOR;
};

// ピクセルシェーダーの入力
struct PS_INPUT
{
    float4 Pos : SV_Position;
    float2 Tex : TEXCOORD;
    float4 Col : COLOR;
};

// 定数バッファ
cbuffer ConstantBuffer : register(b0)
{
    Matrix world;      // ワールド行列
    Matrix view;       // ビュー行列
    Matrix projection; // 射影行列
}