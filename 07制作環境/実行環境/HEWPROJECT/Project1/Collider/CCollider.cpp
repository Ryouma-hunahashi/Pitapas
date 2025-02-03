#include "CCollider.h"

CCollider::CCollider(ID3D11Buffer* vb, ID3D11ShaderResourceView* tex, int num):CGameObject(vb,tex,num)
{
}

CCollider::~CCollider()
{
	delete transform;
}

void CCollider::Update()
{
	//if (!this->isDraw) return;
	
	
	CGameObject::Update();
}

void CCollider::Draw()
{
	if(!this->isDraw) return;
	CGameObject::Draw();
}
