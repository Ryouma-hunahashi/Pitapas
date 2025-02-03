#pragma once
#define DIRECTINPUT_VERSION  0x0800

#define DIK_LBUTTON (0) // �}�E�X�̉E�N���b�N
#define DIK_RBUTTON (1) // �}�E�X�̍��N���b�N
#define DIK_MBUTTON (2) // �}�E�X�̒��N���b�N�i�z�C�[���j

#include<map>
#include<iostream>

#include<dinput.h>
#include <Xinput.h>

#include <unordered_map>
#include "CDirectx.h"

#pragma comment(lib,"dinput8.lib")
#pragma comment(lib,"xinput.lib")
#pragma comment(lib,"dxguid.lib")
class CInput
{
public:
    enum class InputType
    {
        UP,
        DOWN,
        LEFT,
        RIGHT,
        A,
        B,
        Y,
        X,
        SELECT,
        START,
        RB1,
        RB2,
        RB3,
        LB1,
        LB2,
        LB3
    };


    enum class HIDType
    {
        Controller,
        KeyBoardMouse,
    };

    enum class PadTrigger
    {
        LTrigger,
        RTrigger,
    };

private:
    // �R���g���[���[�̃e�[�u��
    const std::map<InputType, DWORD> m_VButtonToXPadTable =
    {
      {InputType::UP	    , XINPUT_GAMEPAD_DPAD_UP			},
      {InputType::DOWN	    , XINPUT_GAMEPAD_DPAD_DOWN			},
      {InputType::LEFT	    , XINPUT_GAMEPAD_DPAD_LEFT			},
      {InputType::RIGHT	    , XINPUT_GAMEPAD_DPAD_RIGHT			},
      {InputType::A		    , XINPUT_GAMEPAD_A					},
      {InputType::B		    , XINPUT_GAMEPAD_B					},
      {InputType::Y		    , XINPUT_GAMEPAD_Y					},
      {InputType::X		    , XINPUT_GAMEPAD_X					},
      {InputType::SELECT	, XINPUT_GAMEPAD_BACK				},
      {InputType::START 	, XINPUT_GAMEPAD_START				},
      {InputType::RB1	    , XINPUT_GAMEPAD_RIGHT_SHOULDER		},
      {InputType::RB2	    , 0								    },
      {InputType::RB3	    , XINPUT_GAMEPAD_RIGHT_THUMB		},
      {InputType::LB1	    , XINPUT_GAMEPAD_LEFT_SHOULDER		},
      {InputType::LB2	    , 0								    },
      {InputType::LB3 	    , XINPUT_GAMEPAD_LEFT_THUMB			},

    };

    // �Ή����Ă��Ȃ��Ƃ����N�ɂ��Ă���
    // �L�[�{�[�h�̃e�[�u��
    const std::map<InputType, DWORD> m_VButtonToXKeyTable =
    {
      {InputType::UP	    , DIK_UP						}, // ��{�^��
      {InputType::DOWN	    , DIK_DOWN						}, // ���{�^��
      {InputType::LEFT	    , DIK_LEFT						}, // ���{�^��
      {InputType::RIGHT	    , DIK_RIGHT						}, // �E�{�^��
      {InputType::A		    , DIK_RETURN					}, // Enter�L�[
      {InputType::B		    , DIK_SPACE						}, // Space�L�[
      {InputType::Y		    , DIK_ESCAPE					}, // Escape�L�[
      {InputType::X		    , 'N'							},
      {InputType::SELECT	, DIK_END						},
      {InputType::RB1	    , 'N'                           },
      {InputType::RB2	    , 'N'							},
      {InputType::RB3	    , 'N'							},
      {InputType::LB1	    , 'N'							},
      {InputType::LB2	    , 'N'							},
      {InputType::LB3 	    , 'N'							},
    };
    // �}�E�X�̃e�[�u��
    const std::map<InputType, DWORD> m_VButtonToXMouseTable =
    {
      {InputType::UP	    , 'N'							},
      {InputType::DOWN	    , 'N'							},
      {InputType::LEFT	    , 'N'							},
      {InputType::RIGHT	    , 'N'							},
      {InputType::A		    , DIK_MBUTTON					},
      {InputType::B		    , 'N'							},
      {InputType::Y		    , 'N'							},
      {InputType::X		    , 'N'							},
      {InputType::SELECT	, 'N'			                },
      {InputType::RB1	    , DIK_RBUTTON					},
      {InputType::RB2	    , 'N'							},
      {InputType::RB3	    , 'N'						    },
      {InputType::LB1   	, DIK_LBUTTON					},
      {InputType::LB2	    , 'N'							},
      {InputType::LB3	    , 'N'							},
    };

    enum class PlayerNumber
    {
        SINGLE,
        DOUBLE,
        TRIPLE,
        MAX,
    };


    // �Q�ƌ���
    HRESULT result;
    

private:
    /* �C���v�b�g�f�o�C�X */
    // �C���v�b�g
    IDirectInput8* input;
    // �L�[�{�[�h�p�̕ϐ�
    IDirectInputDevice8* lpkeyboard = nullptr;
    // �}�E�X�p�̕ϐ�
    IDirectInputDevice8* lpMouse = nullptr;
    // �l�����̃R���g���[���[��p�ӂ��Ă���
    XINPUT_STATE controller[static_cast<int>(PlayerNumber::MAX)];
    XINPUT_STATE oldController[static_cast<int>(PlayerNumber::MAX)];

public:
    HIDType inputType; // �C���v�b�g�̎�ނ�ۑ�����
private:
    // �R���g���[���[�̏�Ԃ��i�[����ϐ�
    //XINPUT_STATE conState;
    // �L�[�{�[�h�}�E�X�̏�Ԃ��i�[����ϐ�
    DIMOUSESTATE keymouseState;
    DIMOUSESTATE oldkeymouseState;
    DIJOYSTATE joyStick;

    unsigned char mKeyBuffer[256] = {};
    unsigned char mOldKeyBuffer[256] = {};

    bool checkcontroller = false;
    bool checkkeyboard = false;

public:
    // �֐��錾

    // ���������s���֐�
    bool Initialize(HWND hWnd, HINSTANCE hInstance);
    // �����[�v�Ăяo���֐�
    void Update();
    // �L�[�{�[�h�{�^�����́i�g���K�[�j
    bool isKeyTrigger(InputType inputtype) const noexcept;
    // �L�[�{�[�h�{�^������(�v���X)
    bool isKeyPress(InputType inputtype) const noexcept;
    // �}�E�X�{�^�����́i�g���K�[�j
    bool isMouseTrigger(InputType inputtype) const noexcept;
    // �}�E�X�{�^�����́i�v���X�j
    bool isMousePress(InputType inputtype) const noexcept;
    // �R���g���[���[�g���K�[�擾
    DirectX::XMFLOAT2 GetVertical(PadTrigger triggertype);
    // �}�E�X�̈ʒu���擾����
    DirectX::XMFLOAT2 GetMousePos();
    // �}�E�X�̈ړ��ʂ��擾����
    POINT GetMouseVelocity();
    // �R���g���[���[�̈ړ��ʂ��擾����
    DirectX::XMFLOAT2 GetControllerStick();
    // �C���v�b�g�N���X�̃Q�b�^�[
    static CInput* Get() { static CInput instance; return &instance; }
    // ���݂̓��̓^�C�v���擾����
    HIDType GetType() { return inputType; }
};