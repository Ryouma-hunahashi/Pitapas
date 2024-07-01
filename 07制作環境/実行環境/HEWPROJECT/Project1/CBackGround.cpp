#include "CBackGround.h"


CBackGround::~CBackGround()
{
}

void CBackGround::Update()
{

	// 明示的に親の更新処理を呼び出す
	CGameObject::Update();
}

void CBackGround::Draw()
{
	// 明示的に親の描画処理を呼び出す
	CGameObject::Draw();
}
