#pragma once
#define DIRECTINPUT_VERSION  0x0800

#define DIK_LBUTTON (0) // マウスの右クリック
#define DIK_RBUTTON (1) // マウスの左クリック
#define DIK_MBUTTON (2) // マウスの中クリック（ホイール）

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
    // コントローラーのテーブル
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

    // 対応していないところはNにしている
    // キーボードのテーブル
    const std::map<InputType, DWORD> m_VButtonToXKeyTable =
    {
      {InputType::UP	    , DIK_UP						}, // 上ボタン
      {InputType::DOWN	    , DIK_DOWN						}, // 下ボタン
      {InputType::LEFT	    , DIK_LEFT						}, // 左ボタン
      {InputType::RIGHT	    , DIK_RIGHT						}, // 右ボタン
      {InputType::A		    , DIK_RETURN					}, // Enterキー
      {InputType::B		    , DIK_SPACE						}, // Spaceキー
      {InputType::Y		    , DIK_ESCAPE					}, // Escapeキー
      {InputType::X		    , 'N'							},
      {InputType::SELECT	, DIK_END						},
      {InputType::RB1	    , 'N'                           },
      {InputType::RB2	    , 'N'							},
      {InputType::RB3	    , 'N'							},
      {InputType::LB1	    , 'N'							},
      {InputType::LB2	    , 'N'							},
      {InputType::LB3 	    , 'N'							},
    };
    // マウスのテーブル
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


    // 参照結果
    HRESULT result;
    

private:
    /* インプットデバイス */
    // インプット
    IDirectInput8* input;
    // キーボード用の変数
    IDirectInputDevice8* lpkeyboard = nullptr;
    // マウス用の変数
    IDirectInputDevice8* lpMouse = nullptr;
    // 人数分のコントローラーを用意しておく
    XINPUT_STATE controller[static_cast<int>(PlayerNumber::MAX)];
    XINPUT_STATE oldController[static_cast<int>(PlayerNumber::MAX)];

public:
    HIDType inputType; // インプットの種類を保存する
private:
    // コントローラーの状態を格納する変数
    //XINPUT_STATE conState;
    // キーボードマウスの状態を格納する変数
    DIMOUSESTATE keymouseState;
    DIMOUSESTATE oldkeymouseState;
    DIJOYSTATE joyStick;

    unsigned char mKeyBuffer[256] = {};
    unsigned char mOldKeyBuffer[256] = {};

    bool checkcontroller = false;
    bool checkkeyboard = false;

public:
    // 関数宣言

    // 初期化を行う関数
    bool Initialize(HWND hWnd, HINSTANCE hInstance);
    // 毎ループ呼び出す関数
    void Update();
    // キーボードボタン入力（トリガー）
    bool isKeyTrigger(InputType inputtype) const noexcept;
    // キーボードボタン入力(プレス)
    bool isKeyPress(InputType inputtype) const noexcept;
    // マウスボタン入力（トリガー）
    bool isMouseTrigger(InputType inputtype) const noexcept;
    // マウスボタン入力（プレス）
    bool isMousePress(InputType inputtype) const noexcept;
    // コントローラートリガー取得
    DirectX::XMFLOAT2 GetVertical(PadTrigger triggertype);
    // マウスの位置を取得する
    DirectX::XMFLOAT2 GetMousePos();
    // マウスの移動量を取得する
    POINT GetMouseVelocity();
    // コントローラーの移動量を取得する
    DirectX::XMFLOAT2 GetControllerStick();
    // インプットクラスのゲッター
    static CInput* Get() { static CInput instance; return &instance; }
    // 現在の入力タイプを取得する
    HIDType GetType() { return inputType; }
};