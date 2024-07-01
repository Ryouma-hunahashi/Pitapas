#pragma once
#include"CGameObject.h"

class CGoal :public CGameObject
{
public:
	CGoal(ID3D11Buffer* vb, ID3D11ShaderResourceView* tex, int num);
	~CGoal();

	void Update() override;
	void Draw() override;

	bool test = false;
};

