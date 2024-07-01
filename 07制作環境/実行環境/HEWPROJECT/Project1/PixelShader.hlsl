struct PS_IN
{
    float4 pos : SV_POSITION;
    float2 tex : TEXCOORD;
};

// グローバル変数の宣言
// ※C言語側からデータを渡された時にセットされる変数
Texture2D myTexture : register(t0); //テクスチャー
SamplerState mySampler : register(s0); //サンプラー

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

float4 ps_main(PS_IN input) : SV_Target
{
    float4 color = myTexture.Sample(mySampler, input.tex);
    
	//return float4(input.tex.x,input.tex.y, 1.0f, 1.0f);
    
    //return input.tex;
    
    //return color;
    
    // テクスチャ色とマテリアル色を混ぜる
    return color * materialDiffuse;
}