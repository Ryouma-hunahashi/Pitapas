#pragma once
#include"CGameObject.h"
#include "CCollider.h"

class CFloor :public CGameObject
{
public:
	// コンストラクタ　デストラクタ
	CFloor(ID3D11Buffer* vb, ID3D11ShaderResourceView* tex, int num);
	~CFloor();

	// 更新処理
	void Update() override;
	// 描画処理
	void Draw() override;

};

