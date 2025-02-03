#pragma once
#include "CDirectx.h"
//#include "CCamera.h"
//#include "CSoundManager.h"

class CScene 
{
public:
	/* ������͊e�q�̃N���X�ŏ������s�����߁A�������z�֐��ɂ��Ă��� */
	// �X�V�֐�
	virtual void Update() = 0;
	// �`��֐�
	virtual void Draw() = 0;

	// �J�������擾����֐�
	//virtual CCamera* GetCamera() = 0;

protected:
	CDirectX::FLOAT_XY center = { 0.0f, 0.0f };
	CDirectX::FLOAT_XY size = { 1.0f, 1.0f };
	CDirectX::FLOAT_XY uv = { 1.0000f, 1.0000f };

};

