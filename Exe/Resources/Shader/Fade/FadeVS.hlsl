#include "Fade.hlsli"

PS_INPUT main(VS_INPUT input)
{
    PS_INPUT output;
	
	// 変換せずにそのまま渡す
    output.Pos = float4(input.Pos, 1.0f);
	
	return output;
}