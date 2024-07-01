#pragma once

#include "CDirectx.h"

class CGameObject;

class CDrawManager
{

private:
	// オブジェクトを格納する可変長配列
	std::vector<CGameObject*> obj;

	float mostBack;

public:
	CDrawManager(float most);
	~CDrawManager();

	void Update();
	void Draw();

	void AddObject(CGameObject* obj);
	void SortObject();

};

