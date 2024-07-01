#pragma once

#include "CDirectx.h"

class CGameObject;

class CDrawManager
{

private:
	// �I�u�W�F�N�g���i�[����ϒ��z��
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

