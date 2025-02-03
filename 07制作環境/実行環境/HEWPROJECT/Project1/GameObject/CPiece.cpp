#include "CPiece.h"

CPiece::CPiece(ID3D11Buffer* vb, ID3D11ShaderResourceView* tex, int num) :CGameObject(vb, tex, num)
{
    center = { 0.0f, 0.0f };
    size = { 1.0f,1.0f };
    uv = { 1.0f, 1.0f };
    CDirectX::Get()->D3D_CreateSquare(center, size, uv, &vertexBufferCollider);
    CDirectX::Get()->D3D_LoadTexture(L"asset/1_1_BoxCollider.png", &textureCollider);

    collider = new CCollider(vb, textureCollider, LayerNum::FORE_GROUND);
}

void CPiece::Update()
{
    // コライダーをオブジェクトと同じにする
    this->collider->transform = this->transform;

    // 明示的に親の更新処理を行う
    CGameObject::Update();
}

void CPiece::Draw()
{
    // 明示的に親の描画処理を行う
    CGameObject::Draw();
}

bool CPiece::isCheckObject(const CGameObject* _gimickObj) const
{
    // 左右の当たっているかどうかを判定する
    bool pos_x = this->transform->Left <= _gimickObj->transform->Left &&
        this->transform->Right >= _gimickObj->transform->Right;

    // 上下の当たっているかどうかを判定する
    bool pos_y = this->transform->Top+0.2f >= _gimickObj->transform->Top &&
        this->transform->Bottom-0.2f <= _gimickObj->transform->Bottom;

    return pos_x && pos_y;
}
