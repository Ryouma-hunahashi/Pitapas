#pragma once

#undef UNICODE

#include <Windows.h>
#include <windowsx.h>
#include "CDirectx.h"


// マクロ定義
#define CLASS_NAME    "DX21Smpl"// ウインドウクラスの名前
#define WINDOW_NAME  "スケルトンプログラム"// ウィンドウの名前

#define SCREEN_WIDTH (960)	// ウインドウの幅
#define SCREEN_HEIGHT (720)	// ウインドウの高さ


#if 0


#elif 1

#define WINDOW_WIDTH  (960) // 画面横サイズ
#define WINDOW_HEIGHT (540) // 画面縦サイズ

#endif // 0


// クラスの前方宣言
class CGameObject;
class CGame;

// ウィンドウクラス
class CWindow
{
private:
	HWND hWnd;
public:
	// ウィンドウの初期化及び作成
	HRESULT Initialize(HINSTANCE hInstance, int nCmdshow);

	// メインループ
	void Loop(MSG msg);


	// 関数のプロトタイプ宣言
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

	// 最初のフレームを取得する
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
