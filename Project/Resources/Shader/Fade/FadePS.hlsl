#include "Fade.hlsli"

float4 main(PS_INPUT input) : SV_TARGET
{
    // �t�F�[�h�̊������o�͂̓����x�ɔ��f������
    return float4(0.0f, 0.0f, 0.0f, Rate.x);
}