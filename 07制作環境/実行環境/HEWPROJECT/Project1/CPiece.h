#pragma once

#include "CGameObject.h"
#include "CCollider.h"

class CPiece : public CGameObject
{
public:
	CPiece(ID3D11Buffer* vb, ID3D11ShaderResourceView* tex, int num);
	~CPiece()override{}

	void Update() override;
	void Draw()override;

	// ピースの中にオブジェクトがあるかどうかを判定する関数
	bool isCheckObject(const CGameObject* parent)const override;

	// 当たり判定用オブジェクト
	CCollider* collider;
};

