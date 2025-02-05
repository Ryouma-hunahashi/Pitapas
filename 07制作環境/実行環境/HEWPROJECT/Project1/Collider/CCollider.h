#pragma once

#include "CGameObject.h"


class CCollider:public CGameObject
{
public:
	CCollider(ID3D11Buffer* vb, ID3D11ShaderResourceView* tex, int num);
	~CCollider() override;

	// 更新処理
	void Update() override;
	// 描画処理
	void Draw() override;

	float gra = 0.01f;

	bool isGravity = false;
	
};

