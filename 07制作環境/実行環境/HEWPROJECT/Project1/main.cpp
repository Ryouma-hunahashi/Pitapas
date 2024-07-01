#undef UNICODE  // Unicode�ł͂Ȃ��A�}���`�o�C�g�������g��

#include <Windows.h>
#include "CDirectx.h"
#include "CGame.h"
#include "CInput.h"
#include "CSceneManager.h"

// �}�N����`
#define CLASS_NAME    "DX21Smpl"// �E�C���h�E�N���X�̖��O
#define WINDOW_NAME  "�X�P���g���v���O����"// �E�B���h�E�̖��O

#define SCREEN_WIDTH (1080)	// �E�C���h�E�̕�
#define SCREEN_HEIGHT (720)	// �E�C���h�E�̍���

#if _DEBUG
#define WINDOW_WIDTH  (1920) // ��ʉ��T�C�Y
#define WINDOW_HEIGHT (1080) // ��ʏc�T�C�Y
#else
#define WINDOW_WIDTH  (1920) // ��ʉ��T�C�Y
#define WINDOW_HEIGHT (1080) // ��ʏc�T�C�Y
#endif

// �֐��̃v���g�^�C�v�錾
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);



// �G���g���|�C���g����ԍŏ��Ɏ��s�����֐�
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
	hWnd = CreateWindowEx(0,// �g���E�B���h�E�X�^�C��
		CLASS_NAME,// �E�B���h�E�N���X�̖��O
		WINDOW_NAME,// �E�B���h�E�̖��O
		WS_OVERLAPPEDWINDOW,// �E�B���h�E�X�^�C��
		(WINDOW_WIDTH - SCREEN_WIDTH) / 2,// �E�B���h�E�̍���w���W
		(WINDOW_HEIGHT - SCREEN_HEIGHT) / 2,// �E�B���h�E�̍���x���W 
		SCREEN_WIDTH,// �E�B���h�E�̕�
		SCREEN_HEIGHT,// �E�B���h�E�̍���
		NULL,// �e�E�B���h�E�̃n���h��
		NULL,// ���j���[�n���h���܂��͎q�E�B���h�EID
		hInstance,// �C���X�^���X�n���h��
		NULL);// �E�B���h�E�쐬�f�[�^

#elif 1
	hWnd = CreateWindowEx(0,// �g���E�B���h�E�X�^�C��
		CLASS_NAME,// �E�B���h�E�N���X�̖��O
		WINDOW_NAME,// �E�B���h�E�̖��O
		WS_POPUP,// �E�B���h�E�X�^�C��
		0,//(WINDOW_WIDTH - SCREEN_WIDTH) / 2,// �E�B���h�E�̍���w���W
		0,//(WINDOW_HEIGHT - SCREEN_HEIGHT) / 2,// �E�B���h�E�̍���x���W 
		/*SCREEN*/WINDOW_WIDTH,// �E�B���h�E�̕�
		/*SCREEN*/WINDOW_HEIGHT,// �E�B���h�E�̍���
		NULL,// �e�E�B���h�E�̃n���h��
		NULL,// ���j���[�n���h���܂��͎q�E�B���h�EID
		hInstance,// �C���X�^���X�n���h��
		NULL);// �E�B���h�E�쐬�f�[�^

#endif


	// �w�肳�ꂽ�E�B���h�E�̕\����Ԃ�ݒ�(�E�B���h�E��\��)
	ShowWindow(hWnd, nCmdShow);
	// �E�B���h�E�̏�Ԃ𒼂��ɔ��f(�E�B���h�E�̃N���C�A���g�̈���X�V)
	UpdateWindow(hWnd);

	// �Q�[�����[�v�ɓ���O��
	// DirectX�̏�����������
	CDirectX::Get()->D3D_Create(hWnd);

	CGame::Get()->Initialize();
	
	// Input�N���X�̏�����
	CInput::Get()->Initialize(hWnd, hInstance);

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

	MSG msg;

	//SetWindowPos(hWnd, NULL, SCREEN_WIDTH / 2,
		//SCREEN_HEIGHT / 2, 0, 0, SWP_NOSIZE | SWP_NOZORDER);


	// �Q�[�����[�v
	for (;;)
	{
		BOOL isAnyMessage = PeekMessage(&msg, NULL, 0, 0, PM_REMOVE);

		if (isAnyMessage)// �������b�Z�[�W�����邩����
		{
			DispatchMessage(&msg);

			if (msg.message == WM_QUIT) {
				break;
			}
		}
		else
		{
			// 1/60�b�o�߂������H
			QueryPerformanceCounter(&liWork);
			nowCount = liWork.QuadPart; // ���ݎ��Ԃ��擾�i�P�ʁF�J�E���g�j
			if (nowCount >= oldCount + numCount_1frame)
			{
				// �Q�[���������s
				//CDirectX::Get()->D3D_ClearScreen();

				// �t�F�[�h���͓��͏������s��Ȃ��悤�ɂ���
				if (!CSceneManager::get()->fadeflag)
				{
					CInput::Get()->Update();
				}
				CGame::Get()->Update();

				//CDirectX::Get()->D3D_UpdateScreen();
				
				
				fpsCounter++; // �Q�[�����[�v���s�񐔂��J�E���g�{�P
				oldCount = nowCount;

				if (CGame::Get()->endflg) break;
			}

			nowTick = GetTickCount64(); // ���ݎ��Ԏ擾
			// �P�b�o�߂������H
			if (nowTick >= oldTick + 1000)
			{
				// FPS��\������
				char str[32];
				wsprintfA(str, "FPS=%d", fpsCounter);
				SetWindowTextA(hWnd, str);
				POINT mouse;
				GetCursorPos(&mouse);
				ScreenToClient(hWnd, &mouse);
				wsprintfA(str, "x = %d y = %d", mouse.x, mouse.y);
				SetWindowTextA(hWnd, str);
				// �J�E���^�[�����Z�b�g
				fpsCounter = 0;
				oldTick = nowTick;
			}
		}
	} // �Q�[�����[�v�̕��J�b�R

	UnregisterClass(CLASS_NAME, hInstance);

	return (int)msg.wParam;
}


LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
		//case WM_PAINT: // �E�B���h�E�̃N���C�A���g���W��ύX���鎞�̏���
		//	PAINTSTRUCT ps;
		//	HDC hdc = BeginPaint(hWnd, &ps);

		//	// �N���C�A���g�̈�̃T�C�Y���擾
		//	RECT clientRect;
		//	GetClientRect(hWnd, &clientRect);

		//	break;

	case WM_DESTROY:// �E�B���h�E�j���̃��b�Z�[�W
		PostQuitMessage(0);// �gWM_QUIT�h���b�Z�[�W�𑗂�@���@�A�v���I��
		break;

	case WM_CLOSE:  // x�{�^���������ꂽ��
		DestroyWindow(hWnd);  // �gWM_DESTROY�h���b�Z�[�W�𑗂�
		break;

		// �L�[�������ꂽ�C�x���g
	case WM_KEYDOWN:
		break;

		// �L�[�������ꂽ�C�x���g
	case WM_KEYUP:
		break;

	default:
		// ���case�ȊO�̏ꍇ�̏��������s
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
		break;
	}

	return 0;
}
