// ���_�V�F�[�_�[�̓���
struct VS_INPUT
{
    float4 Pos     : SV_Position;
    float4 Color   : COLOR;
    float4 Tex     : TEXCOORD0;
    float4 Reverse : TEXCOORD1;
};

// �s�N�Z���V�F�[�_�[�̓���
struct PS_INPUT
{
    float4 Pos     : SV_Position;
    float4 Color   : COLOR;
    float4 Tex     : TEXCOORD0;
    float4 Reverse : TEXCOORD1;
};

// �萔�o�b�t�@
cbuffer ConstantBuffer : register(b0)
{
    float4 widowSize;  //�E�B���h�E�T�C�Y
}