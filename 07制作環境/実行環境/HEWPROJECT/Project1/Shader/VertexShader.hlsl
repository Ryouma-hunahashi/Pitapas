struct VS_IN
{
    float4 pos : POSITION0;
    float2 tex : TEX;
};

struct VS_OUT
{
    float4 pos : SV_POSITION;
    float2 tex : TEXCOORD;
};

// グローバル変数の宣言
// 定数バッファ受け取り用
cbuffer ConstBuffer : register(b0)
{
    // UV座標移動行列
    matrix matrixTex;
    // 投影行列
    matrix matrixProj;
    // ワールド変換行列
    matrix matrixWorld;
    // マテリアル色
    float4 materialDiffuse;
}


VS_OUT vs_main( VS_IN input )
{
    VS_OUT output;
    
    
     // ワールド変換行列を頂点に掛ける
    input.pos = mul(input.pos, matrixWorld);
    
    //output.pos = input.pos;
    // 平行投影のため行列を頂点に掛ける
    output.pos = mul(input.pos, matrixProj);
    
    //output.tex = input.tex;
    
    float4 uv;
    uv.xy = input.tex;
    uv.z = 0;
    uv.w = 1.0f;
    uv = mul(uv, matrixTex);
    
    output.tex = uv.xy;
    
	return output;
}