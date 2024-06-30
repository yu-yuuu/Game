// ���_�V�F�[�_�[�̓���
struct VS_INPUT
{
    float3 Pos : SV_Position;
    float2 Tex : TEXCOORD;
    float4 Col : COLOR;
};

// �s�N�Z���V�F�[�_�[�̓���
struct PS_INPUT
{
    float4 Pos : SV_Position;
    float2 Tex : TEXCOORD;
    float4 Col : COLOR;
};

// �萔�o�b�t�@
cbuffer ConstantBuffer : register(b0)
{
    Matrix world;      // ���[���h�s��
    Matrix view;       // �r���[�s��
    Matrix projection; // �ˉe�s��
}