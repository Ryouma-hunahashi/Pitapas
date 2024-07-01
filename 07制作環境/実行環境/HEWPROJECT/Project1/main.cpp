#undef UNICODE  // Unicodeではなく、マルチバイト文字を使う

#include <Windows.h>
#include "CDirectx.h"
#include "CGame.h"
#include "CInput.h"
#include "CSceneManager.h"

// マクロ定義
#define CLASS_NAME    "DX21Smpl"// ウインドウクラスの名前
#define WINDOW_NAME  "スケルトンプログラム"// ウィンドウの名前

#define SCREEN_WIDTH (1080)	// ウインドウの幅
#define SCREEN_HEIGHT (720)	// ウインドウの高さ

#if _DEBUG
#define WINDOW_WIDTH  (1920) // 画面横サイズ
#define WINDOW_HEIGHT (1080) // 画面縦サイズ
#else
#define WINDOW_WIDTH  (1920) // 画面横サイズ
#define WINDOW_HEIGHT (1080) // 画面縦サイズ
#endif

// 関数のプロトタイプ宣言
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);



// エントリポイント＝一番最初に実行される関数
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow)
{
	WNDCLASSEX wc;

	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_CLASSDC;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = NULL;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = CLASS_NAME;
	wc.hIconSm = NULL;

	RegisterClassEx(&wc);

	HWND hWnd;

#if _DEBUG
	hWnd = CreateWindowEx(0,// 拡張ウィンドウスタイル
		CLASS_NAME,// ウィンドウクラスの名前
		WINDOW_NAME,// ウィンドウの名前
		WS_OVERLAPPEDWINDOW,// ウィンドウスタイル
		(WINDOW_WIDTH - SCREEN_WIDTH) / 2,// ウィンドウの左上Ｘ座標
		(WINDOW_HEIGHT - SCREEN_HEIGHT) / 2,// ウィンドウの左上Ｙ座標 
		SCREEN_WIDTH,// ウィンドウの幅
		SCREEN_HEIGHT,// ウィンドウの高さ
		NULL,// 親ウィンドウのハンドル
		NULL,// メニューハンドルまたは子ウィンドウID
		hInstance,// インスタンスハンドル
		NULL);// ウィンドウ作成データ

#elif 1
	hWnd = CreateWindowEx(0,// 拡張ウィンドウスタイル
		CLASS_NAME,// ウィンドウクラスの名前
		WINDOW_NAME,// ウィンドウの名前
		WS_POPUP,// ウィンドウスタイル
		0,//(WINDOW_WIDTH - SCREEN_WIDTH) / 2,// ウィンドウの左上Ｘ座標
		0,//(WINDOW_HEIGHT - SCREEN_HEIGHT) / 2,// ウィンドウの左上Ｙ座標 
		/*SCREEN*/WINDOW_WIDTH,// ウィンドウの幅
		/*SCREEN*/WINDOW_HEIGHT,// ウィンドウの高さ
		NULL,// 親ウィンドウのハンドル
		NULL,// メニューハンドルまたは子ウィンドウID
		hInstance,// インスタンスハンドル
		NULL);// ウィンドウ作成データ

#endif


	// 指定されたウィンドウの表示状態を設定(ウィンドウを表示)
	ShowWindow(hWnd, nCmdShow);
	// ウィンドウの状態を直ちに反映(ウィンドウのクライアント領域を更新)
	UpdateWindow(hWnd);

	// ゲームループに入る前に
	// DirectXの初期化をする
	CDirectX::Get()->D3D_Create(hWnd);

	CGame::Get()->Initialize();
	
	// Inputクラスの初期化
	CInput::Get()->Initialize(hWnd, hInstance);

	// FPS表示用変数
	int fpsCounter = 0;
	long long oldTick = GetTickCount64();//現在時間を保存
	long long nowTick = oldTick; // 現在時間取得用

	// FPS固定用変数
	LARGE_INTEGER liWork; // 関数から値を受け取る用
	long long frequency; // 計測精度
	// 計測精度を取得
	QueryPerformanceFrequency(&liWork);
	frequency = liWork.QuadPart; // １秒あたりの解像度が入る
	// １フレームあたりのカウント値を計算
	long long numCount_1frame = frequency / 60; // 60FPSで計算
	// 現在時間（単位：カウント）を取得
	QueryPerformanceCounter(&liWork);
	long long oldCount = liWork.QuadPart;
	long long nowCount = oldCount;

	MSG msg;

	//SetWindowPos(hWnd, NULL, SCREEN_WIDTH / 2,
		//SCREEN_HEIGHT / 2, 0, 0, SWP_NOSIZE | SWP_NOZORDER);


	// ゲームループ
	for (;;)
	{
		BOOL isAnyMessage = PeekMessage(&msg, NULL, 0, 0, PM_REMOVE);

		if (isAnyMessage)// 何かメッセージがあるか判定
		{
			DispatchMessage(&msg);

			if (msg.message == WM_QUIT) {
				break;
			}
		}
		else
		{
			// 1/60秒経過したか？
			QueryPerformanceCounter(&liWork);
			nowCount = liWork.QuadPart; // 現在時間を取得（単位：カウント）
			if (nowCount >= oldCount + numCount_1frame)
			{
				// ゲーム処理実行
				//CDirectX::Get()->D3D_ClearScreen();

				// フェード中は入力処理を行わないようにする
				if (!CSceneManager::get()->fadeflag)
				{
					CInput::Get()->Update();
				}
				CGame::Get()->Update();

				//CDirectX::Get()->D3D_UpdateScreen();
				
				
				fpsCounter++; // ゲームループ実行回数をカウント＋１
				oldCount = nowCount;

				if (CGame::Get()->endflg) break;
			}

			nowTick = GetTickCount64(); // 現在時間取得
			// １秒経過したか？
			if (nowTick >= oldTick + 1000)
			{
				// FPSを表示する
				char str[32];
				wsprintfA(str, "FPS=%d", fpsCounter);
				SetWindowTextA(hWnd, str);
				POINT mouse;
				GetCursorPos(&mouse);
				ScreenToClient(hWnd, &mouse);
				wsprintfA(str, "x = %d y = %d", mouse.x, mouse.y);
				SetWindowTextA(hWnd, str);
				// カウンターをリセット
				fpsCounter = 0;
				oldTick = nowTick;
			}
		}
	} // ゲームループの閉じカッコ

	UnregisterClass(CLASS_NAME, hInstance);

	return (int)msg.wParam;
}


LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
		//case WM_PAINT: // ウィンドウのクライアント座標を変更する時の処理
		//	PAINTSTRUCT ps;
		//	HDC hdc = BeginPaint(hWnd, &ps);

		//	// クライアント領域のサイズを取得
		//	RECT clientRect;
		//	GetClientRect(hWnd, &clientRect);

		//	break;

	case WM_DESTROY:// ウィンドウ破棄のメッセージ
		PostQuitMessage(0);// “WM_QUIT”メッセージを送る　→　アプリ終了
		break;

	case WM_CLOSE:  // xボタンが押されたら
		DestroyWindow(hWnd);  // “WM_DESTROY”メッセージを送る
		break;

		// キーが押されたイベント
	case WM_KEYDOWN:
		break;

		// キーが離されたイベント
	case WM_KEYUP:
		break;

	default:
		// 上のcase以外の場合の処理を実行
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
		break;
	}

	return 0;
}
