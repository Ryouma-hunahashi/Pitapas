#include "CGoal.h"
#include "CCollider.h"

CGoal::CGoal(ID3D11Buffer* vb, ID3D11ShaderResourceView* tex, int num) :CGameObject(vb, tex, num)
{
	center = { 0.0f, 0.0f };
	size = { 1.0f,1.0f };
	uv = { 1.0f, 1.0f };
	CDirectX::Get()->D3D_CreateSquare(center, size, uv, &vertexBufferCollider);
	CDirectX::Get()->D3D_LoadTexture(L"asset/1_1_BoxCollider.png", &textureCollider);	// 

	collider = new CCollider(vertexBufferCollider, textureCollider, LayerNum::FORE_GROUND);
}

CGoal::~CGoal()
{
}

void CGoal::Update()
{

	this->collider->transform->position = this->transform->position;
	this->collider->transform->scale.x = 1.7f;

	//this->transform->scale.z = 0.1f;
	//this->transform->rotate.y += 5.0f;
	//this->transform->rotate.z += 180.0f;
	//this->transform->position.y += 0.01f;

	//if (this->transform->position.y >= 0.0f)
	//{
	//	test = false;
	//}
	//else if (this->transform->position.y <= -0.4f)
	//{
	//	test = true;
	//}
	//if (test)
	//{
	//	this->transform->position.y += 0.0075f;
	//}
	//else
	//{
	//	this->transform->position.y -= 0.005f;
	//}


	// 明示的に更新処理を呼び出す
	CGameObject::Update();
}

void CGoal::Draw()
{
	if (!this->isDraw) return;

	// 明示的に描画処理を呼び出す
	CGameObject::Draw();
}
