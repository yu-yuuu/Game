#include "MenuWindow.hlsli"

// �g�p����e�N�X�`��
Texture2D tex : register(t0);
// �e�N�X�`���T���v���[
SamplerState samLinear : register(s0);

// �s�N�Z���V�F�[�_�[�̃G���g���[�|�C���g
float4 main(PS_INPUT input) : SV_TARGET
{
    // �摜�󂯎��
    return tex.Sample(samLinear, input.Tex);
}