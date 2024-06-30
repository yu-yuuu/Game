#include "Fade.hlsli"

float4 main(PS_INPUT input) : SV_TARGET
{
    // フェードの割合を出力の透明度に反映させる
    return float4(0.0f, 0.0f, 0.0f, Rate.x);
}