#include "Effect.hlsli"

// ���_�V�F�[�_�[�̃G���g���[�|�C���g
PS_INPUT main(VS_INPUT input)
{
    PS_INPUT output;
	
	// �ϊ������ɂ��̂܂ܓn��
    output.Pos = float4(input.Pos, 1.0f);
    output.Tex = input.Tex;
    output.Col = input.Col;
    
    return output;
}