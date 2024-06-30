#include "MenuWindow.hlsli"

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
        float2 window = windowSize.xy;
        // �`��ʒu
        float2 pos = (input[0].Pos.xy / window) * 2.0f;
        // �摜�T�C�Y
        float2 texSize = input[0].Tex / window;
		
        // �A���J�[�|�C���g
        uint anchor = input[0].Pos.z;
        // �A���J�[�|�C���g�ʒu
        float2 anchorPos;
        anchorPos.x = texSize.x * (anchor % 3);
        anchorPos.y = texSize.y * (anchor / 3);
		
        // �`��ʒu�v�Z
        element.Pos.xy = pos + texSize * offsetArray[i].xy * 2.0f - float2(1.0f, 1.0f);
        // �ݒ肳�ꂽ�A���J�[�|�C���g�܂ł��炷
        element.Pos.xy -= anchorPos;
        // �㉺�̕������t�Ȃ̂Ŕ��]
        element.Pos.y *= -1.0f;
		        
		//XY���ʂȂ̂� z��0�Aw��1
        element.Pos.z = 0.0f;
        element.Pos.w = 1.0f;

        // ���_�ʒu�ݒ�
        element.Tex = offsetArray[i].xy;
		
        output.Append(element);
    }
    output.RestartStrip();
}