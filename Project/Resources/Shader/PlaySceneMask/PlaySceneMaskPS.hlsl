#include "PlaySceneMask.hlsli"

float4 main(PS_INPUT input) : SV_TARGET
{
    float4 output = float4(0.0f, 0.0f, 0.0f, 1.0f);

    output.a = lerp(0.0f, 1.0f, step(input.Tex.y, 0.1f) + step(0.9f, input.Tex.y));

    return output;
}