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

	// �J�����̏����ʒu
	const DirectX::XMFLOAT3 iniCameraPos = { 0,5,-2 };

	// �J�����ʒu�����ϐ�
	DirectX::XMFLOAT3 cameraPos = { iniCameraPos };

	static CGame* Get() { static CGame instance; return &instance; }

	void Initialize();

	void Update();
};

