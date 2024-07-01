struct PS_IN
{
    float4 pos : SV_POSITION;
    float2 tex : TEXCOORD;
};

// �O���[�o���ϐ��̐錾
// ��C���ꑤ����f�[�^��n���ꂽ���ɃZ�b�g�����ϐ�
Texture2D myTexture : register(t0); //�e�N�X�`���[
SamplerState mySampler : register(s0); //�T���v���[

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

float4 ps_main(PS_IN input) : SV_Target
{
    float4 color = myTexture.Sample(mySampler, input.tex);
    
	//return float4(input.tex.x,input.tex.y, 1.0f, 1.0f);
    
    //return input.tex;
    
    //return color;
    
    // �e�N�X�`���F�ƃ}�e���A���F��������
    return color * materialDiffuse;
}