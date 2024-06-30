#include "UI.hlsli"

// 頂点シェーダーのエントリーポイント
PS_INPUT main(VS_INPUT input)
{
    PS_INPUT output;
	
	// 変換せずにそのまま渡す
    output.Pos     = input.Pos;
    output.Color   = input.Color;
    output.Tex     = input.Tex;
    output.Reverse = input.Reverse;
    
    return output;
}