// ���_�V�F�[�_�[�̓���
struct VS_INPUT
{
    float3 Pos : SV_Position;
    float2 Tex : TEXCOORD;
};

// �s�N�Z���V�F�[�_�[�̓���
struct PS_INPUT
{
    float4 Pos : SV_Position;
    float2 Tex : TEXCOORD;
};

// �萔�o�b�t�@
cbuffer ConstantBuffer : register(b0)
{
    float4 windowSize; //�E�B���h�E�T�C�Y
}
