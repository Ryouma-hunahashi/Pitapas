#undef UNICODE

#include "CWindow.h"

// �֐��̃v���g�^�C�v�錾
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
	hWnd = CreateWindowEx(0,// �g���E�B���h�E�X�^�C��
		CLASS_NAME,// �E�B���h�E�N���X�̖��O
		WINDOW_NAME,// �E�B���h�E�̖��O
		WS_OVERLAPPEDWINDOW,// �E�B���h�E�X�^�C�� �� ��̃o�[�������Ƃ��� WS_POPUP  WS_OVERLAPPEDWINDOW
		0,//(WINDOW_WIDTH-SCREEN_WIDTH)/2,// �E�B���h�E�̍���w���W
		0,//(WINDOW_HEIGHT-SCREEN_HEIGHT)/2,// �E�B���h�E�̍���x���W 
		SCREEN_WIDTH,// �E�B���h�E�̕�
		SCREEN_HEIGHT,// �E�B���h�E�̍���
		NULL,// �e�E�B���h�E�̃n���h��
		NULL,// ���j���[�n���h���܂��͎q�E�B���h�EID
		hInstance,// �C���X�^���X�n���h��
		NULL);// �E�B���h�E�쐬�f�[�^

	// �w�肳�ꂽ�E�B���h�E�̕\����Ԃ�ݒ�(�E�B���h�E��\��)
	ShowWindow(hWnd, SW_MAXIMIZE);
	// �E�B���h�E�̏�Ԃ𒼂��ɔ��f(�E�B���h�E�̃N���C�A���g�̈���X�V)
	UpdateWindow(hWnd);

	// DirectX�̏�����
	CDirectX::Get()->D3D_Create(hWnd);


	// �Q�[���N���X�̏�����
	//CGame::Get()->Initialize();

	// �T�E���h�̏�����
	//CSoundManager::GetSound()->XA_Initialize();

	// FPS�\���p�ϐ�
	int fpsCounter = 0;
	long long oldTick = GetTickCount64();//���ݎ��Ԃ�ۑ�
	long long nowTick = oldTick; // ���ݎ��Ԏ擾�p

	// FPS�Œ�p�ϐ�
	LARGE_INTEGER liWork; // �֐�����l���󂯎��p
	long long frequency; // �v�����x
	// �v�����x���擾
	QueryPerformanceFrequency(&liWork);
	frequency = liWork.QuadPart; // �P�b������̉𑜓x������
	// �P�t���[��������̃J�E���g�l���v�Z
	long long numCount_1frame = frequency / 60; // 60FPS�Ōv�Z
	// ���ݎ��ԁi�P�ʁF�J�E���g�j���擾
	QueryPerformanceCounter(&liWork);
	long long oldCount = liWork.QuadPart;
	long long nowCount = oldCount;

	MSG msg ={};

	// ���C�����[�v
	while (msg.message != WM_QUIT)
	{
		// �L���[���̃��b�Z�[�W������
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			// 1/60�b�o�߂������H
			QueryPerformanceCounter(&liWork);
			nowCount = liWork.QuadPart; // ���ݎ��Ԃ��擾�i�P�ʁF�J�E���g�j
			if (nowCount >= oldCount + numCount_1frame)
			{
				// �e�X�g�p Scene�̃N���X������΂�����Ɉڍs����
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
				fpsCounter++; // �Q�[�����[�v���s�񐔂��J�E���g�{�P
				oldCount = nowCount;
			}

			nowTick = GetTickCount64(); // ���ݎ��Ԏ擾
			// �P�b�o�߂������H
			if (nowTick >= oldTick + 1000)
			{
				// FPS��\������
				char str[32];
				wsprintfA(str, "FPS=%d", fpsCounter);
				SetWindowTextA(hWnd, str);
				// �J�E���^�[�����Z�b�g
				fpsCounter = 0;
				oldTick = nowTick;
			}

		}
	}


	//// DirectX�̏������������ɏ���
	//CWindow* window;
	//HWND hWnd;
	//window = new CWindow();
	//
	//// �E�B���h�E�̏������y�э쐬
	////hWnd = CWindow::GetWindow()->Initialize(hInstance, nCmdShow);
	//if (FAILED(CWindow::GetWindow()->Initialize(hInstance, nCmdShow))) { return 0; }
	//
	//// ���C�����[�v����
	//MSG	msg = {};
	//
	//window->Loop(msg);
	//
	//delete window;
	//
	// WM_QUIT���b�Z�[�W�̕�����Windows�ɕԂ�
	return static_cast<char>(msg.wParam);

}


LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_DESTROY: // �E�B���h�E�j���̃��b�Z�[�W
		PostQuitMessage(0); // WM_QUIT���b�Z�[�W�𑗂� ���A�v���I��
		break;
	}

	// switch�����������Ȃ��������b�Z�[�W������
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}
