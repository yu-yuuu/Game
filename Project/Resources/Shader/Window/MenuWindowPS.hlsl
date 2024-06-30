#include "MenuWindow.hlsli"

// 使用するテクスチャ
Texture2D tex : register(t0);
// テクスチャサンプラー
SamplerState samLinear : register(s0);

// ピクセルシェーダーのエントリーポイント
float4 main(PS_INPUT input) : SV_TARGET
{
    // 画像受け取り
    return tex.Sample(samLinear, input.Tex);
}