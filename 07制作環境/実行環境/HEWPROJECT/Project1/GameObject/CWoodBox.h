#pragma once
#include "CGameObject.h"
#include "CCollider.h"

class CWoodBox :public CGameObject
{
public:

	// コンストラクタ・デストラクタ
	CWoodBox(ID3D11Buffer* vb, ID3D11ShaderResourceView* tex, int num);
	~CWoodBox()override {}

	// 更新処理
	void Update() override;
	// 描画処理
	void Draw() override;
	// ピースの中にオブジェクトがあるかどうかを判定する関数
	bool isCheckObject(const CGameObject* parent)const override;

	// 当たり判定用オブジェクト
	CCollider* collider;

	float gra = 0.01f;

public:
	

};

