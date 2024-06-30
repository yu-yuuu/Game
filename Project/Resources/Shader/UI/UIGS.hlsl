#include "UI.hlsli"

// �g�����钸�_�̐�
static const unsigned int vnum = 4;

// �g���p���_���W
static const float4 offsetArray[vnum] =
{
    float4(0.0f, 1.0f, 0.0f, 1.0f), // ����
	float4(1.0f, 1.0f, 0.0f, 1.0f), // �E��
	float4(0.0f, 0.0f, 0.0f, 1.0f), // ����
	float4(1.0f, 0.0f, 0.0f, 1.0f), // �E��
};

// �W�I���g���V�F�[�_�[�̃G���g���|�C���g
[maxvertexcount(vnum)]
void main(
	point PS_INPUT input[1],
	inout TriangleStream<PS_INPUT> output
)
{
    for (int i = 0; i < 4; i++)
    {
        PS_INPUT element;
		
        // �E�B���h�E�T�C�Y
        float2 window  = widowSize.xy;
        // �`��ʒu
        float2 pos = (input[0].Pos.xy / window) * 2.0f;
        // �摜�T�C�Y
        float2 texSize = input[0].Tex.xy / window;
        // �摜�X�P�[��
        float2 scale = input[0].Tex.zw;
		
        // �A���J�[�|�C���g
        uint anchor = input[0].Pos.z;
        // �A���J�[�|�C���g�ʒu
        float2 anchorPos;
        anchorPos.x = texSize.x * (anchor % 3) * scale.x;
        anchorPos.y = texSize.y * (anchor / 3) * scale.y;
		
        // ���]
        float2 offset = float2(abs(offsetArray[i].xy - input[0].Reverse.xy));
        
        // �`��ʒu�v�Z
        element.Pos.xy = pos + texSize * scale * offset * 2.0f - float2(1.0f, 1.0f);
        // �ݒ肳�ꂽ�A���J�[�|�C���g�܂ł��炷
        element.Pos.xy -= anchorPos;
        // �㉺�̕������t�Ȃ̂Ŕ��]
        element.Pos.y *= -1.0f;
		        
		//XY���ʂȂ̂� z��0�Aw��1
        element.Pos.z = 0.0f;
        element.Pos.w = 1.0f;
        // �J���[�A���o�[�X�͂��̂܂ܓn��
        element.Color   = input[0].Color;
        element.Reverse = input[0].Reverse;
        // ���_�ʒu�ݒ�
        element.Tex = offsetArray[i];
		
        output.Append(element);
    }
    output.RestartStrip();
}