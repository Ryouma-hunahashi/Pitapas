#pragma once
//=============================================================================
//
// �T�E���h���� [xa2.h]
//
//=============================================================================
#ifndef _XAUDIO2_H_
#define _XAUDIO2_H_



#include <xaudio2.h>

// �T�E���h�t�@�C��
typedef enum
{
	SOUND_LABEL_BGM000,		// �T���v��BGM
	STAGE1_BGM,		// �T���v��BGM
	STAGE2_BGM,		// �T���v��BGM
	STAGE3_BGM,		// �T���v��BGM
	STAGE4_BGM,		// �T���v��BGM
	TITLE_BGM,		// �T���v��BGM
	CURSOR,
	CLICK,
	SOUND_LABEL_MAX,
} SOUND_LABEL;
#endif

class CSoundManager
{
public:
	// �Q�[�����[�v�J�n�O�ɌĂяo���T�E���h�̏���������
	HRESULT XA_Initialize(void);

	// �Q�[�����[�v�I����ɌĂяo���T�E���h�̉������
	void XA_Release(void);

	// �����Ŏw�肵���T�E���h���Đ�����
	// ���ʂ̍ő�l��1.0f�ŏ��l0.0f�ŉ��͏�����
	void XA_Play(SOUND_LABEL label, float volume);

	// �����Ŏw�肵���T�E���h���~����
	void XA_Stop(SOUND_LABEL label);

	// �����Ŏw�肵���T�E���h�̍Đ����ĊJ����
	void XA_Resume(SOUND_LABEL label);

	static CSoundManager* GetSound() { static CSoundManager sound; return &sound; }

};

