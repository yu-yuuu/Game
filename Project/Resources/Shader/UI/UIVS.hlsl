#include "UI.hlsli"

// ���_�V�F�[�_�[�̃G���g���[�|�C���g
PS_INPUT main(VS_INPUT input)
{
    PS_INPUT output;
	
	// �ϊ������ɂ��̂܂ܓn��
    output.Pos     = input.Pos;
    output.Color   = input.Color;
    output.Tex     = input.Tex;
    output.Reverse = input.Reverse;
    
    return output;
}