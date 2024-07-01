#include "CUi.h"
#include "CCollider.h"


using namespace DirectX;

CUi::CUi(ID3D11Buffer* vb, ID3D11ShaderResourceView* tex, int num) : CGameObject(vb, tex, num)
{
	vertexBuffer = vb;
	texture = tex;

    center = { 0.0f, 0.0f };
    size = { 1.0f, 1.0f };
    uv = { 1.0f, 1.0f };
    CDirectX::Get()->D3D_CreateSquare(center, size, uv, &vertexBufferCollider);
    CDirectX::Get()->D3D_LoadTexture(L"asset/1_1_BoxCollider.png", &textureCollider);	// 

    collider = new CCollider(vb, textureCollider, LayerNum::FORE_GROUND);

    // �A�j���[�V�����N���X�����̉��i�A�j���[�V�����@�\�𓮂��悤�ɂ���j
    anim = new CAnimation(1, 1);
    anim->SetPattern(CAnimation::NO_ANIMATION);
    m_pBlendStateAlpha = 0;

    // Fade�N���X���̉�
    //fade = new CFade();

    // �C�[�W���O�N���X�����̉�
    //easing = new CUiEasing();

    // �����蔻��̎��̉�
    transform = new CSquea();

    
}


void CUi::Update() {
    // �A�N�e�B�u/��A�N�e�B�u����
    if (!isActive)
    {
        return;
    }

    this->collider->transform->scale = this->transform->scale;
    this->collider->transform->position = this->transform->position;

    this->collider->transform->scale.y /= 7.5f;

    // �t�F�[�h�Ǘ��֐��Ăяo��
   // FadeManager();

    // �P�ʃx�N�g��������i���̒������P�ɂ���j�����K��
   // XMVECTOR v = XMLoadFloat3(&dir); // �x�N�g���v�Z�p�̌^�ɓ����
   // v = XMVector3Normalize(v); //���K������
   // XMStoreFloat3(&dir, v); //���̕ϐ�dir�Ɍ��ʂ�߂�

    // �x�N�g�����g���Ĉړ�

    // �A�j���[�V�����̍X�V����
    anim->Update();

    CGameObject::Update();
    
}

void CUi::Draw() {
   // // �P�ʃx�N�g��������i���̒������P�ɂ���j�����K��
   // XMVECTOR v = XMLoadFloat3(&dir); // �x�N�g���v�Z�p�̌^�ɓ����
   // v = XMVector3Normalize(v); //���K������
   // XMStoreFloat3(&dir, v); //���̕ϐ�dir�Ɍ��ʂ�߂�


    CGameObject::Draw();
}

