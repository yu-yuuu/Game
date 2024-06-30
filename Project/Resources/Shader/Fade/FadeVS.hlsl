#include "Fade.hlsli"

PS_INPUT main(VS_INPUT input)
{
    PS_INPUT output;
	
	// •ÏŠ·‚¹‚¸‚É‚»‚Ì‚Ü‚Ü“n‚·
    output.Pos = float4(input.Pos, 1.0f);
	
	return output;
}