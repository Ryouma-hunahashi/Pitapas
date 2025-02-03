#include "CInput.h"
#include <iostream>
#include "CWindow.h"

bool CInput::Initialize(HWND hWnd, HINSTANCE hInstance)
{
	// インプットデバイスを作成する
	result = DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&input, NULL);
	if (FAILED(result)) { return false; }

	/* デバイスを作成する */

	// キーボードデバイス作成
	result = input->CreateDevice(GUID_SysKeyboard, &lpkeyboard, NULL);
	if (FAILED(result)) { return false; }

	// マウスデバイス作成
	result = input->CreateDevice(GUID_SysMouse, &lpMouse, NULL);
	if (FAILED(result)) { return false; }


	/* デバイスのフォーマットの設定 */

	// キーボードのフォーマット設定
	result = lpkeyboard->SetDataFormat(&c_dfDIKeyboard);
	if (FAILED(result)) { return false; }

	// マウスのフォーマット設定
	result = lpMouse->SetDataFormat(&c_dfDIMouse);
	if (FAILED(result)) { return false; }


	/* 協調モード設定 */

	// キーボードの協調モード設定
	result = lpkeyboard->SetCooperativeLevel(hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
	if (FAILED(result)) { return false; }

	// マウスの協調モード作成
	result = lpMouse->SetCooperativeLevel(hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
	if (FAILED(result)) { return false; }


	/* 入力デバイスを開始する */
	lpkeyboard->Acquire();
	lpMouse->Acquire();

	return true;
}

void CInput::Update()
{
	// １フレーム前のデータを保存
	oldController[0] = controller[0];
	// サイズを取得する
	::ZeroMemory(controller, sizeof(XINPUT_STATE));

	// コントローラーの現在の状態を取得する
	DWORD m_result = XInputGetState(0, controller);

	// コントローラーが接続されていれば
	if (m_result == ERROR_SUCCESS)
	{
		inputType = HIDType::Controller; // コントローラー接続にする
	}
	else // コントローラーが接続されていなければ
	{
		inputType = HIDType::KeyBoardMouse; // キーボードマウス接続にする
	}

	// コントローラー接続されているとき
	if (inputType == HIDType::Controller)
	{
	}
	// コントローラーが接続されていないとき
	else if (inputType == HIDType::KeyBoardMouse)
	{
		// １フレーム前のデータを保存
		memcpy_s(mOldKeyBuffer, sizeof(mOldKeyBuffer), mKeyBuffer, sizeof(mKeyBuffer));

		HRESULT hr;

		// キーボードの状態を取得する
		hr = lpkeyboard->GetDeviceState(sizeof(mKeyBuffer), &mKeyBuffer);

		if (FAILED(hr))
		{
			lpkeyboard->Acquire();
			lpkeyboard->GetDeviceState(sizeof(mKeyBuffer), &mKeyBuffer);
		}

		oldkeymouseState = keymouseState;

		hr = lpMouse->GetDeviceState(sizeof(keymouseState), &keymouseState);

		if (FAILED(hr))
		{
			lpMouse->Acquire();
			lpMouse->GetDeviceState(sizeof(keymouseState), &keymouseState);
		}
	}
	// 不具合で何も接続されていないとき
	// ※ ここには行かないはず
	else
	{
#if _DEBUG

		MessageBoxA(NULL, "接続処理が正常ではないです", "DEBUGERROR", MB_ICONERROR);
#endif // _DEBUG

	}
}

bool CInput::isKeyTrigger(InputType inputtype) const noexcept
{
	// コントローラーのボタンがトリガーされたか確認
	if (inputType == HIDType::Controller) 
	{
		int buttonMask = m_VButtonToXPadTable.at(inputtype);

		bool PushButton = (controller[0].Gamepad.wButtons & buttonMask);
		bool PushedButton = !(oldController[0].Gamepad.wButtons & buttonMask);

		return PushButton && PushedButton;
	}
	// キーボードおよびマウスのボタンがトリガーされたか確認
	else if (inputType == HIDType::KeyBoardMouse)
	{

		// 入力された情報を格納する
		auto itKey = m_VButtonToXKeyTable.find(inputtype);
		// キーボード入力の場合

		if (itKey != m_VButtonToXKeyTable.end())
		{
			return (mKeyBuffer[itKey->second] & 0x80) && !(mOldKeyBuffer[itKey->second] & 0x80);	
		}
		
		
		auto itMouse = m_VButtonToXMouseTable.find(inputtype);
		if (itMouse != m_VButtonToXMouseTable.end())
		{
			auto mouseMask = itMouse->second;
			return (GetAsyncKeyState(mouseMask) & 0x80) && !(GetAsyncKeyState(mouseMask) & 0x80);
		}
	}

	return false;
}

bool CInput::isKeyPress(InputType inputtype) const noexcept
{
	// コントローラーのボタンが押されているか確認
	if (inputType == HIDType::Controller)
	{
		// XInputGetState で取得した状態から必要なボタンの状態を確認するコードを追加
		bool isButtonPressed = (controller[0].Gamepad.wButtons & m_VButtonToXPadTable.at(inputtype)) != 0;
		return isButtonPressed;
	}
	// キーボードおよびマウスのボタンが押されているか確認
	else if (inputType == HIDType::KeyBoardMouse)
	{
		// ボタンがキーボードに対応しているか確認
		auto itKey = m_VButtonToXKeyTable.find(inputtype);
		// キーボードのボタンが押されているかどうか
		return mKeyBuffer[itKey->second] & 0x80;
	}
	return false;
}

bool CInput::isMouseTrigger(InputType inputtype) const noexcept
{
	if (inputType == HIDType::KeyBoardMouse)
	{
		auto itMouse = m_VButtonToXMouseTable.find(inputtype);

		return (keymouseState.rgbButtons[itMouse->second] & 0x80) && !(oldkeymouseState.rgbButtons[itMouse->second] & 0x80);
	}
	else // コントローラーはマウス判定無いので反応無しにしておく
	{
		return false;
	}

	return false;
}

bool CInput::isMousePress(InputType inputtype) const noexcept
{
	if (inputType == HIDType::KeyBoardMouse)
	{
		// ボタンがマウスに対応しているか確認
		auto itMouse = m_VButtonToXMouseTable.find(inputtype);
		
		return keymouseState.rgbButtons[itMouse->second] & 0x80;
	}
	return false;
}

DirectX::XMFLOAT2 CInput::GetVertical(PadTrigger tiggertype)
{
	// コントローラーの座標を保存する変数
	DirectX::XMFLOAT2 padThumb = { 0,0 };

	switch (tiggertype)
	{
	case PadTrigger::LTrigger: // 左トリガーの場合
		padThumb.x = controller->Gamepad.sThumbLX;
		padThumb.y = controller->Gamepad.sThumbLY;
		break;
	case PadTrigger::RTrigger: // 右トリガーの場合
		padThumb.x = controller->Gamepad.sThumbRX;
		padThumb.y = controller->Gamepad.sThumbRY;
		break;
	}

	return padThumb;
}

DirectX::XMFLOAT2 CInput::GetMousePos()
{
	POINT p;
	// マウスカーソルの位置を取得する
	GetCursorPos(&p);
	// スクリーン上の座標に変換する
	ScreenToClient(CWindow::GetWindow()->GetHWND(), &p);

	DirectX::XMFLOAT2 mousePoint;

	// マウスの座標を上下左右の端を用いて求める
	mousePoint.x = (static_cast<float>(p.x) / 120.0f)-8;
	mousePoint.y = (static_cast<float>(p.y) / -120.0f) + 4.5;

#if _DEBUG
	char str[100];
	wsprintfA(str, "x = %d , y = %d x = %d , y = %d", p.x, p.y, static_cast<int>(mousePoint.x), static_cast<int>(mousePoint.y));
	SetWindowTextA(CWindow::GetWindow()->GetHWND(), str);
#endif
	
	return mousePoint;
}

POINT CInput::GetMouseVelocity()
{
	POINT mouseVel;

	//現在のマウスの座標を取得する
	mouseVel.x = keymouseState.lX;
	mouseVel.y = keymouseState.lY;

	return mouseVel;
}

DirectX::XMFLOAT2 CInput::GetControllerStick()
{
	// コントローラーのスティックの情報を格納する変数
	DirectX::XMFLOAT2 stick;

	// コントローラーの状態を取得
	if (XInputGetState(0, &controller[0]) == ERROR_SUCCESS)
	{
		// 左スティックの入力を取得
		stick.x = static_cast<float>(controller[0].Gamepad.sThumbLX) / 32767.0f;
		stick.y = static_cast<float>(controller[0].Gamepad.sThumbLY) / 32767.0f;

		// スティックが中央付近の場合は微小な値に修正
		if (fabs(stick.x) < 0.1f)
			stick.x = 0.0f;
		if (fabs(stick.y) < 0.1f)
			stick.y = 0.0f;

		
	}
	return stick;
}

