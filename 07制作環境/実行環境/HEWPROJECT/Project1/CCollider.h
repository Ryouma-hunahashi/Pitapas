#pragma once

#include "CGameObject.h"


class CCollider:public CGameObject
{
public:
	CCollider(ID3D11Buffer* vb, ID3D11ShaderResourceView* tex, int num);
	~CCollider() override;

	// XVˆ—
	void Update() override;
	// •`‰æˆ—
	void Draw() override;

	float gra = 0.01f;

	bool isGravity = false;
	
};

