#include "UI.hlsli"

// 拡張する頂点の数
static const unsigned int vnum = 4;

// 拡張用頂点座標
static const float4 offsetArray[vnum] =
{
    float4(0.0f, 1.0f, 0.0f, 1.0f), // 左上
	float4(1.0f, 1.0f, 0.0f, 1.0f), // 右上
	float4(0.0f, 0.0f, 0.0f, 1.0f), // 左下
	float4(1.0f, 0.0f, 0.0f, 1.0f), // 右下
};

// ジオメトリシェーダーのエントリポイント
[maxvertexcount(vnum)]
void main(
	point PS_INPUT input[1],
	inout TriangleStream<PS_INPUT> output
)
{
    for (int i = 0; i < 4; i++)
    {
        PS_INPUT element;
		
        // ウィンドウサイズ
        float2 window  = widowSize.xy;
        // 描画位置
        float2 pos = (input[0].Pos.xy / window) * 2.0f;
        // 画像サイズ
        float2 texSize = input[0].Tex.xy / window;
        // 画像スケール
        float2 scale = input[0].Tex.zw;
		
        // アンカーポイント
        uint anchor = input[0].Pos.z;
        // アンカーポイント位置
        float2 anchorPos;
        anchorPos.x = texSize.x * (anchor % 3) * scale.x;
        anchorPos.y = texSize.y * (anchor / 3) * scale.y;
		
        // 反転
        float2 offset = float2(abs(offsetArray[i].xy - input[0].Reverse.xy));
        
        // 描画位置計算
        element.Pos.xy = pos + texSize * scale * offset * 2.0f - float2(1.0f, 1.0f);
        // 設定されたアンカーポイントまでずらす
        element.Pos.xy -= anchorPos;
        // 上下の方向が逆なので反転
        element.Pos.y *= -1.0f;
		        
		//XY平面なので zは0、wは1
        element.Pos.z = 0.0f;
        element.Pos.w = 1.0f;
        // カラー、リバースはそのまま渡す
        element.Color   = input[0].Color;
        element.Reverse = input[0].Reverse;
        // 頂点位置設定
        element.Tex = offsetArray[i];
		
        output.Append(element);
    }
    output.RestartStrip();
}