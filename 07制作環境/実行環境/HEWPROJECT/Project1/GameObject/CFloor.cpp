#include "CFloor.h"


CFloor::CFloor(ID3D11Buffer* vb, ID3D11ShaderResourceView* tex, int num) :CGameObject(vb, tex, num)
{
	center = { 0.0f, 0.0f };
	size = { 1.0f,1.0f };
	uv = { 1.0f, 1.0f };
	CDirectX::Get()->D3D_CreateSquare(center, size, uv, &vertexBufferCollider);
	CDirectX::Get()->D3D_LoadTexture(L"asset/1_1_BoxCollider.png", &textureCollider);	// 

	collider = new CCollider(vertexBufferCollider, textureCollider, LayerNum::FORE_GROUND);
}

CFloor::~CFloor()
{

}

void CFloor::Update()
{
	this->collider->transform->position = this->transform->position;
	this->collider->transform->scale = this->transform->scale;

	this->collider->Update();
	// 明示的に親の更新処理を呼び出す
	CGameObject::Update();
}

void CFloor::Draw()
{
	if (!this->isDraw) return;
	// 明示的に親の描画処理を呼び出す
	CGameObject::Draw();
}
