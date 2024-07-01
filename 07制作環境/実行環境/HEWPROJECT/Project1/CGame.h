#pragma once

#include "CDirectx.h"

class CCamera;

class CGame
{
private:
	CGame() {}
	~CGame();

public:
	CCamera* camera;

	bool endflg = false;

	// カメラの初期位置
	const DirectX::XMFLOAT3 iniCameraPos = { 0,5,-2 };

	// カメラ位置を持つ変数
	DirectX::XMFLOAT3 cameraPos = { iniCameraPos };

	static CGame* Get() { static CGame instance; return &instance; }

	void Initialize();

	void Update();
};

