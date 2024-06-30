#include "Effect.hlsli"

// 使用するテクスチャ
Texture2D tex : register(t0);
// テクスチャサンプラー
SamplerState samLinear : register(s0);

// ピクセルシェーダーのエントリーポイント
float4 main(PS_INPUT input) : SV_TARGET
{
    // 画像受け取り
    float4 output = tex.Sample(samLinear, input.Tex);
        
    // 設定されていた色を掛ける
    output *= input.Col;    
    
    return output;
}