#include "MenuWindow.hlsli"

// ピクセルシェーダーのエントリーポイント
float4 main(PS_INPUT input) : SV_TARGET
{
    // 暗くする
    return float4(0.0f, 0.0f, 0.0f, 0.5f);
}