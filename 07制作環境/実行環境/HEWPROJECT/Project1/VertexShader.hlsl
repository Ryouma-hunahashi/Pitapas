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

// �O���[�o���ϐ��̐錾
// �萔�o�b�t�@�󂯎��p
cbuffer ConstBuffer : register(b0)
{
    // UV���W�ړ��s��
    matrix matrixTex;
    // ���e�s��
    matrix matrixProj;
    // ���[���h�ϊ��s��
    matrix matrixWorld;
    // �}�e���A���F
    float4 materialDiffuse;
}


VS_OUT vs_main( VS_IN input )
{
    VS_OUT output;
    
    
     // ���[���h�ϊ��s��𒸓_�Ɋ|����
    input.pos = mul(input.pos, matrixWorld);
    
    //output.pos = input.pos;
    // ���s���e�̂��ߍs��𒸓_�Ɋ|����
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