#pragma once
#include "CDirectx.h"
//#include "CCamera.h"
//#include "CSoundManager.h"

class CScene 
{
public:
	/* これら二つは各子のクラスで処理を行うため、純粋仮想関数にしておく */
	// 更新関数
	virtual void Update() = 0;
	// 描画関数
	virtual void Draw() = 0;

	// カメラを取得する関数
	//virtual CCamera* GetCamera() = 0;

protected:
	CDirectX::FLOAT_XY center = { 0.0f, 0.0f };
	CDirectX::FLOAT_XY size = { 1.0f, 1.0f };
	CDirectX::FLOAT_XY uv = { 1.0000f, 1.0000f };

};

