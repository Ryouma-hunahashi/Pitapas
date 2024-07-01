#include "CDrawManager.h"
#include "CGameObject.h"
#include <algorithm>

CDrawManager::CDrawManager(float most)
{
	mostBack = 0.0f;
}

CDrawManager::~CDrawManager()
{
}

void CDrawManager::Update()
{
	this->SortObject();

	for (auto&& d : obj) { d->Update(); }
}

void CDrawManager::Draw()
{
	this->SortObject();

	float drawPosZ = 4;

	for (auto&& d : obj)
	{
		drawPosZ -= 0.01f;
		d->transform->position.z = drawPosZ;
		d->Draw();
	}
}

void CDrawManager::AddObject(CGameObject* _obj)
{
	for (auto&& d : obj)
	{
		if (d == _obj)
		{
			return;
		}
	}
	obj.push_back(_obj);
}

void CDrawManager::SortObject()
{
	auto sort = [](const CGameObject* _a, const CGameObject* _b)mutable->bool {return _a->GetLayer() > _b->GetLayer(); };

	std::sort(obj.begin(), obj.end(), sort);
}
