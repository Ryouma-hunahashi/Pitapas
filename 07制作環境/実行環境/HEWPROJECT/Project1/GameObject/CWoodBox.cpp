#include "CWoodBox.h"

CWoodBox::CWoodBox(ID3D11Buffer* vb, ID3D11ShaderResourceView* tex, int num) :CGameObject(vb, tex, num)
{
    center = { 0.0f, 0.0f };
    size = { 1.0f,1.0f };
    uv = { 1.0f, 1.0f };
    CDirectX::Get()->D3D_CreateSquare(center, size, uv, &vertexBufferCollider);
    CDirectX::Get()->D3D_LoadTexture(L"asset/1_1_BoxCollider.png", &textureCollider);	// 

    collider = new CCollider(vb, textureCollider, LayerNum::FORE_GROUND);
}

void CWoodBox::Update()
{
   //this->collider->transform->position = { this->transform->position.x,this->transform->position.y,0.0f };
   //this->collider->transform->position.y -= 0.2f;
   //this->collider->transform->scale.x = 0.7f;

    //this->transform->position.y += 0.2f;
    this->collider->transform->position = { this->transform->position.x,this->transform->position.y,0.0f };
    this->collider->transform->scale = this->transform->scale;
    //
    //this->collider->transform->position.y -= 0.4f;
    //
    //this->transform->scale = this->collider->transform->scale;
    //this->collider->transform->rotate = this->transform->rotate;

    //if (DrawNum == LayerNum::UI)
    //{
    //    this->transform->position = { -6.5f,3.3f,1.0f };
    //    this->transform->scale = { 0.5f,0.5f,1.0f };
    //}
    //else
    //{
    //    if (!this->ishalf)
    //    {
    //        this->transform->scale = { 1.0f,1.0f,1.0f };
    //    }
    //    else
    //    {
    //        this->transform->scale = { 1.0f,0.5f,1.0f };
    //    }

        if (this->isGravity)
        {
            this->transform->position.y -= 0.05f;
        }
  
    //}
    //collider->Update();

   
    //this->transform->position.y -= gravity;


    CGameObject::Update();
}

void CWoodBox::Draw()
{
    if (!this->isDraw) return;
    CGameObject::Draw();
}

bool CWoodBox::isCheckObject(const CGameObject* parent) const
{
    // ¶‰E‚Ì“–‚½‚Á‚Ä‚¢‚é‚©‚Ç‚¤‚©‚ð”»’è‚·‚é
    bool pos_x = this->transform->position.x >= parent->transform->Left &&
        this->transform->position.x <= parent->transform->Right;

    // ã‰º‚Ì“–‚½‚Á‚Ä‚¢‚é‚©‚Ç‚¤‚©‚ð”»’è‚·‚é
    bool pos_y = this->transform->position.y >= parent->transform->Top &&
        this->transform->position.y <= parent->transform->Bottom;

    return pos_x && pos_y;
}
