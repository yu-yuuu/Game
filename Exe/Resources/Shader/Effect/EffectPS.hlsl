#include "Effect.hlsli"

// �g�p����e�N�X�`��
Texture2D tex : register(t0);
// �e�N�X�`���T���v���[
SamplerState samLinear : register(s0);

// �s�N�Z���V�F�[�_�[�̃G���g���[�|�C���g
float4 main(PS_INPUT input) : SV_TARGET
{
    // �摜�󂯎��
    float4 output = tex.Sample(samLinear, input.Tex);
        
    // �ݒ肳��Ă����F���|����
    output *= input.Col;    
    
    return output;
}