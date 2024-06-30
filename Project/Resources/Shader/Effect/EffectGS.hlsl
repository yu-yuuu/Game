#include "Effect.hlsli"

// 拡張する頂点の数
static const int vnum = 4;

// 拡張する頂点の位置
static const float4 offset_array[vnum] =
{
    float4(-0.5f, 0.5f, 0.0f, 0.0f), // 左上
	float4(0.5f, 0.5f, 0.0f, 0.0f), // 右上
	float4(-0.5f, -0.5f, 0.0f, 0.0f), // 左下
	float4(0.5f, -0.5f, 0.0f, 0.0f), // 右下
};

[maxvertexcount(vnum)]
void main(
	point PS_INPUT input[1],
	inout TriangleStream<PS_INPUT> output
)
{
    for (int i = 0; i < vnum; i++)
    {
        PS_INPUT element;
        
        // ワールド変換
        element.Pos = input[0].Pos + mul(offset_array[i] * float4(input[0].Tex, 0.0f, 0.0f), world);
        // ビュー変換
        element.Pos = mul(element.Pos, view);
        // 射影変換
        element.Pos = mul(element.Pos, projection);

        // 左上をUVの(0,0)になるように調整
        element.Tex.x = offset_array[i].x + 0.5f;
        element.Tex.y = -offset_array[i].y + 0.5f;

        // 色はそのまま渡す
        element.Col = input[0].Col;
		
        output.Append(element);
    }
    output.RestartStrip();
}