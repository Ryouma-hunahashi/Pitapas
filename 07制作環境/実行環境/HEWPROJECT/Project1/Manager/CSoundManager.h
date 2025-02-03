#pragma once
//=============================================================================
//
// サウンド処理 [xa2.h]
//
//=============================================================================
#ifndef _XAUDIO2_H_
#define _XAUDIO2_H_



#include <xaudio2.h>

// サウンドファイル
typedef enum
{
	SOUND_LABEL_BGM000,		// サンプルBGM
	STAGE1_BGM,		// サンプルBGM
	STAGE2_BGM,		// サンプルBGM
	STAGE3_BGM,		// サンプルBGM
	STAGE4_BGM,		// サンプルBGM
	TITLE_BGM,		// サンプルBGM
	CURSOR,
	CLICK,
	SOUND_LABEL_MAX,
} SOUND_LABEL;
#endif

class CSoundManager
{
public:
	// ゲームループ開始前に呼び出すサウンドの初期化処理
	HRESULT XA_Initialize(void);

	// ゲームループ終了後に呼び出すサウンドの解放処理
	void XA_Release(void);

	// 引数で指定したサウンドを再生する
	// 音量の最大値は1.0f最小値0.0fで音は消える
	void XA_Play(SOUND_LABEL label, float volume);

	// 引数で指定したサウンドを停止する
	void XA_Stop(SOUND_LABEL label);

	// 引数で指定したサウンドの再生を再開する
	void XA_Resume(SOUND_LABEL label);

	static CSoundManager* GetSound() { static CSoundManager sound; return &sound; }

};

