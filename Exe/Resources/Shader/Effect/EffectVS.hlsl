#include "Effect.hlsli"

// 頂点シェーダーのエントリーポイント
PS_INPUT main(VS_INPUT input)
{
    PS_INPUT output;
	
	// 変換せずにそのまま渡す
    output.Pos = float4(input.Pos, 1.0f);
    output.Tex = input.Tex;
    output.Col = input.Col;
    
    return output;
}