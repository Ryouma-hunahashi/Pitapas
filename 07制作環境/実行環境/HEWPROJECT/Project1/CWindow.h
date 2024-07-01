#pragma once

#undef UNICODE

#include <Windows.h>
#include <windowsx.h>
#include "CDirectx.h"


// �}�N����`
#define CLASS_NAME    "DX21Smpl"// �E�C���h�E�N���X�̖��O
#define WINDOW_NAME  "�X�P���g���v���O����"// �E�B���h�E�̖��O

#define SCREEN_WIDTH (960)	// �E�C���h�E�̕�
#define SCREEN_HEIGHT (720)	// �E�C���h�E�̍���


#if 0


#elif 1

#define WINDOW_WIDTH  (960) // ��ʉ��T�C�Y
#define WINDOW_HEIGHT (540) // ��ʏc�T�C�Y

#endif // 0


// �N���X�̑O���錾
class CGameObject;
class CGame;

// �E�B���h�E�N���X
class CWindow
{
private:
	HWND hWnd;
public:
	// �E�B���h�E�̏������y�э쐬
	HRESULT Initialize(HINSTANCE hInstance, int nCmdshow);

	// ���C�����[�v
	void Loop(MSG msg);


	// �֐��̃v���g�^�C�v�錾
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

	// �ŏ��̃t���[�����擾����
	void InitFPS();

	static CWindow* GetWindow();
	HWND GetHWND() { return CWindow::GetWindow()->hWnd; }


	CWindow() {}
	~CWindow();

private:
	

	
	//static CDirectX direct;

	LARGE_INTEGER m_freq = { 0 };
	LARGE_INTEGER m_starttime = { 0 };
	LARGE_INTEGER m_nowtime = { 0 };
	LARGE_INTEGER m_frametime_a = { 0 };
	LARGE_INTEGER m_frametime_b = { 0 };
	int m_iCount = 0;

	static HWND g_hWnd;
	static int g_iClientWidth;
	static int g_iClientHeight;
	static double g_dFps;
	static double g_dFrameTime;

	
};
