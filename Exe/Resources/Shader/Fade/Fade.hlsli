// ���_�V�F�[�_�[�̓���
struct VS_INPUT
{
    float3 Pos : SV_Position;
};

// �s�N�Z���V�F�[�_�[�̓���
struct PS_INPUT
{
    float4 Pos : SV_Position;
};

// �萔�o�b�t�@
cbuffer ConstantBuffer : register(b0)
{
    float4 Rate;// �t�F�[�h�̊���
}