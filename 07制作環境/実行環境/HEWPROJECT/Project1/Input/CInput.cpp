#include "CInput.h"
#include <iostream>
#include "CWindow.h"

bool CInput::Initialize(HWND hWnd, HINSTANCE hInstance)
{
	// �C���v�b�g�f�o�C�X���쐬����
	result = DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&input, NULL);
	if (FAILED(result)) { return false; }

	/* �f�o�C�X���쐬���� */

	// �L�[�{�[�h�f�o�C�X�쐬
	result = input->CreateDevice(GUID_SysKeyboard, &lpkeyboard, NULL);
	if (FAILED(result)) { return false; }

	// �}�E�X�f�o�C�X�쐬
	result = input->CreateDevice(GUID_SysMouse, &lpMouse, NULL);
	if (FAILED(result)) { return false; }


	/* �f�o�C�X�̃t�H�[�}�b�g�̐ݒ� */

	// �L�[�{�[�h�̃t�H�[�}�b�g�ݒ�
	result = lpkeyboard->SetDataFormat(&c_dfDIKeyboard);
	if (FAILED(result)) { return false; }

	// �}�E�X�̃t�H�[�}�b�g�ݒ�
	result = lpMouse->SetDataFormat(&c_dfDIMouse);
	if (FAILED(result)) { return false; }


	/* �������[�h�ݒ� */

	// �L�[�{�[�h�̋������[�h�ݒ�
	result = lpkeyboard->SetCooperativeLevel(hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
	if (FAILED(result)) { return false; }

	// �}�E�X�̋������[�h�쐬
	result = lpMouse->SetCooperativeLevel(hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
	if (FAILED(result)) { return false; }


	/* ���̓f�o�C�X���J�n���� */
	lpkeyboard->Acquire();
	lpMouse->Acquire();

	return true;
}

void CInput::Update()
{
	// �P�t���[���O�̃f�[�^��ۑ�
	oldController[0] = controller[0];
	// �T�C�Y���擾����
	::ZeroMemory(controller, sizeof(XINPUT_STATE));

	// �R���g���[���[�̌��݂̏�Ԃ��擾����
	DWORD m_result = XInputGetState(0, controller);

	// �R���g���[���[���ڑ�����Ă����
	if (m_result == ERROR_SUCCESS)
	{
		inputType = HIDType::Controller; // �R���g���[���[�ڑ��ɂ���
	}
	else // �R���g���[���[���ڑ�����Ă��Ȃ����
	{
		inputType = HIDType::KeyBoardMouse; // �L�[�{�[�h�}�E�X�ڑ��ɂ���
	}

	// �R���g���[���[�ڑ�����Ă���Ƃ�
	if (inputType == HIDType::Controller)
	{
	}
	// �R���g���[���[���ڑ�����Ă��Ȃ��Ƃ�
	else if (inputType == HIDType::KeyBoardMouse)
	{
		// �P�t���[���O�̃f�[�^��ۑ�
		memcpy_s(mOldKeyBuffer, sizeof(mOldKeyBuffer), mKeyBuffer, sizeof(mKeyBuffer));

		HRESULT hr;

		// �L�[�{�[�h�̏�Ԃ��擾����
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
	// �s��ŉ����ڑ�����Ă��Ȃ��Ƃ�
	// �� �����ɂ͍s���Ȃ��͂�
	else
	{
#if _DEBUG

		MessageBoxA(NULL, "�ڑ�����������ł͂Ȃ��ł�", "DEBUGERROR", MB_ICONERROR);
#endif // _DEBUG

	}
}

bool CInput::isKeyTrigger(InputType inputtype) const noexcept
{
	// �R���g���[���[�̃{�^�����g���K�[���ꂽ���m�F
	if (inputType == HIDType::Controller) 
	{
		int buttonMask = m_VButtonToXPadTable.at(inputtype);

		bool PushButton = (controller[0].Gamepad.wButtons & buttonMask);
		bool PushedButton = !(oldController[0].Gamepad.wButtons & buttonMask);

		return PushButton && PushedButton;
	}
	// �L�[�{�[�h����у}�E�X�̃{�^�����g���K�[���ꂽ���m�F
	else if (inputType == HIDType::KeyBoardMouse)
	{

		// ���͂��ꂽ�����i�[����
		auto itKey = m_VButtonToXKeyTable.find(inputtype);
		// �L�[�{�[�h���͂̏ꍇ

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
	// �R���g���[���[�̃{�^����������Ă��邩�m�F
	if (inputType == HIDType::Controller)
	{
		// XInputGetState �Ŏ擾������Ԃ���K�v�ȃ{�^���̏�Ԃ��m�F����R�[�h��ǉ�
		bool isButtonPressed = (controller[0].Gamepad.wButtons & m_VButtonToXPadTable.at(inputtype)) != 0;
		return isButtonPressed;
	}
	// �L�[�{�[�h����у}�E�X�̃{�^����������Ă��邩�m�F
	else if (inputType == HIDType::KeyBoardMouse)
	{
		// �{�^�����L�[�{�[�h�ɑΉ����Ă��邩�m�F
		auto itKey = m_VButtonToXKeyTable.find(inputtype);
		// �L�[�{�[�h�̃{�^����������Ă��邩�ǂ���
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
	else // �R���g���[���[�̓}�E�X���薳���̂Ŕ��������ɂ��Ă���
	{
		return false;
	}

	return false;
}

bool CInput::isMousePress(InputType inputtype) const noexcept
{
	if (inputType == HIDType::KeyBoardMouse)
	{
		// �{�^�����}�E�X�ɑΉ����Ă��邩�m�F
		auto itMouse = m_VButtonToXMouseTable.find(inputtype);
		
		return keymouseState.rgbButtons[itMouse->second] & 0x80;
	}
	return false;
}

DirectX::XMFLOAT2 CInput::GetVertical(PadTrigger tiggertype)
{
	// �R���g���[���[�̍��W��ۑ�����ϐ�
	DirectX::XMFLOAT2 padThumb = { 0,0 };

	switch (tiggertype)
	{
	case PadTrigger::LTrigger: // ���g���K�[�̏ꍇ
		padThumb.x = controller->Gamepad.sThumbLX;
		padThumb.y = controller->Gamepad.sThumbLY;
		break;
	case PadTrigger::RTrigger: // �E�g���K�[�̏ꍇ
		padThumb.x = controller->Gamepad.sThumbRX;
		padThumb.y = controller->Gamepad.sThumbRY;
		break;
	}

	return padThumb;
}

DirectX::XMFLOAT2 CInput::GetMousePos()
{
	POINT p;
	// �}�E�X�J�[�\���̈ʒu���擾����
	GetCursorPos(&p);
	// �X�N���[����̍��W�ɕϊ�����
	ScreenToClient(CWindow::GetWindow()->GetHWND(), &p);

	DirectX::XMFLOAT2 mousePoint;

	// �}�E�X�̍��W���㉺���E�̒[��p���ċ��߂�
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

	//���݂̃}�E�X�̍��W���擾����
	mouseVel.x = keymouseState.lX;
	mouseVel.y = keymouseState.lY;

	return mouseVel;
}

DirectX::XMFLOAT2 CInput::GetControllerStick()
{
	// �R���g���[���[�̃X�e�B�b�N�̏����i�[����ϐ�
	DirectX::XMFLOAT2 stick;

	// �R���g���[���[�̏�Ԃ��擾
	if (XInputGetState(0, &controller[0]) == ERROR_SUCCESS)
	{
		// ���X�e�B�b�N�̓��͂��擾
		stick.x = static_cast<float>(controller[0].Gamepad.sThumbLX) / 32767.0f;
		stick.y = static_cast<float>(controller[0].Gamepad.sThumbLY) / 32767.0f;

		// �X�e�B�b�N�������t�߂̏ꍇ�͔����Ȓl�ɏC��
		if (fabs(stick.x) < 0.1f)
			stick.x = 0.0f;
		if (fabs(stick.y) < 0.1f)
			stick.y = 0.0f;

		
	}
	return stick;
}

