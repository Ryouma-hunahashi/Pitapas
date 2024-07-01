#pragma once
#include "CGameObject.h"
//#include "CDirectX.h"

class CBackGround : public CGameObject
{
private:


public:
	// コンストラクタ・デストラクタ
	CBackGround(ID3D11Buffer* vb, ID3D11ShaderResourceView* tex,int num) :CGameObject(vb, tex, num) {}
	~CBackGround();

	// 背景の更新処理
	void Update() override;
	// 背景の描画処理
	void Draw() override;

};

