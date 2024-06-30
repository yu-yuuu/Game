// 頂点シェーダーの入力
struct VS_INPUT
{
    float4 Pos     : SV_Position;
    float4 Color   : COLOR;
    float4 Tex     : TEXCOORD0;
    float4 Reverse : TEXCOORD1;
};

// ピクセルシェーダーの入力
struct PS_INPUT
{
    float4 Pos     : SV_Position;
    float4 Color   : COLOR;
    float4 Tex     : TEXCOORD0;
    float4 Reverse : TEXCOORD1;
};

// 定数バッファ
cbuffer ConstantBuffer : register(b0)
{
    float4 widowSize;  //ウィンドウサイズ
}