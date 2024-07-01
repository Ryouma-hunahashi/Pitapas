#undef UNICODE

#include "CWindow.h"

// 関数のプロトタイプ宣言
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int nCmdShow)
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
	hWnd = CreateWindowEx(0,// 拡張ウィンドウスタイル
		CLASS_NAME,// ウィンドウクラスの名前
		WINDOW_NAME,// ウィンドウの名前
		WS_OVERLAPPEDWINDOW,// ウィンドウスタイル ※ 上のバーを消すときは WS_POPUP  WS_OVERLAPPEDWINDOW
		0,//(WINDOW_WIDTH-SCREEN_WIDTH)/2,// ウィンドウの左上Ｘ座標
		0,//(WINDOW_HEIGHT-SCREEN_HEIGHT)/2,// ウィンドウの左上Ｙ座標 
		SCREEN_WIDTH,// ウィンドウの幅
		SCREEN_HEIGHT,// ウィンドウの高さ
		NULL,// 親ウィンドウのハンドル
		NULL,// メニューハンドルまたは子ウィンドウID
		hInstance,// インスタンスハンドル
		NULL);// ウィンドウ作成データ

	// 指定されたウィンドウの表示状態を設定(ウィンドウを表示)
	ShowWindow(hWnd, SW_MAXIMIZE);
	// ウィンドウの状態を直ちに反映(ウィンドウのクライアント領域を更新)
	UpdateWindow(hWnd);

	// DirectXの初期化
	CDirectX::Get()->D3D_Create(hWnd);


	// ゲームクラスの初期化
	//CGame::Get()->Initialize();

	// サウンドの初期化
	//CSoundManager::GetSound()->XA_Initialize();

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

	MSG msg ={};

	// メインループ
	while (msg.message != WM_QUIT)
	{
		// キュー内のメッセージを処理
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			// 1/60秒経過したか？
			QueryPerformanceCounter(&liWork);
			nowCount = liWork.QuadPart; // 現在時間を取得（単位：カウント）
			if (nowCount >= oldCount + numCount_1frame)
			{
				// テスト用 Sceneのクラスがあればそちらに移行する
				CDirectX::Get()->D3D_ClearScreen();

				//if (!CSceneManager::get()->fadeflag)
				//{
				//	CInput::Get()->Update();
				//}
				////CInput::Get()->Update();
				//CGame::Get()->Update();
				//
				//if (CGame::Get()->endflg)break;

				CDirectX::Get()->D3D_UpdateScreen();
				fpsCounter++; // ゲームループ実行回数をカウント＋１
				oldCount = nowCount;
			}

			nowTick = GetTickCount64(); // 現在時間取得
			// １秒経過したか？
			if (nowTick >= oldTick + 1000)
			{
				// FPSを表示する
				char str[32];
				wsprintfA(str, "FPS=%d", fpsCounter);
				SetWindowTextA(hWnd, str);
				// カウンターをリセット
				fpsCounter = 0;
				oldTick = nowTick;
			}

		}
	}


	//// DirectXの初期化※ここに書く
	//CWindow* window;
	//HWND hWnd;
	//window = new CWindow();
	//
	//// ウィンドウの初期化及び作成
	////hWnd = CWindow::GetWindow()->Initialize(hInstance, nCmdShow);
	//if (FAILED(CWindow::GetWindow()->Initialize(hInstance, nCmdShow))) { return 0; }
	//
	//// メインループ処理
	//MSG	msg = {};
	//
	//window->Loop(msg);
	//
	//delete window;
	//
	// WM_QUITメッセージの部分をWindowsに返す
	return static_cast<char>(msg.wParam);

}


LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_DESTROY: // ウィンドウ破棄のメッセージ
		PostQuitMessage(0); // WM_QUITメッセージを送る →アプリ終了
		break;
	}

	// switch文が処理しなかったメッセージを処理
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}
