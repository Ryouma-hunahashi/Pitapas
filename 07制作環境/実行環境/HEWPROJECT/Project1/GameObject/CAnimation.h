#pragma once

#include "CDirectX.h"

// �A�j���[�V�����@�\�̃N���X
class CAnimation
{

public:
	// �񋓌^
	// �A�j���[�V�����p�^�[����
	enum PATTERN
	{
		NO_ANIMATION,
		PLAYER = 1,
		PLAYER_DEAD =2,
		FX_0_11 = 3,  // �G�t�F�N�g�p�O�`�P�P�Đ�
		FX_0_19 = 4,  // �G�t�F�N�g�p�O�`�P�X�Đ�
		FX_54_0 = 5,
		FX_0_54 = 6,
	};

private:
	// �����o�[�ϐ�
	CDirectX::FLOAT_XY uv; // �A�j���[�V������UV�ړ��ʂ�ۑ�
	CDirectX::FLOAT_XY split;


	float animCounter = 0.0f; // �A�j���e�[�u���̃J�E���^�[

	// �Đ�����p�^�[��ID�����ϐ�
	int animPattern = 5;

public:
	// �Đ����x��ݒ肷��
	float animSpeed = 0.1f; // �Đ����x

	// ���ݍĐ�������\���ϐ�
	bool isPlaying = true;


public:
	CAnimation(float x, float y) { split.x = x, split.y = y; }

	// �����o�[�֐�
	void Update();

	// �Đ�����A�j���[�V������ύX����

	// UV�ړ��ʂ��擾����
	CDirectX::FLOAT_XY GetUV();

	// �Đ�����p�^�[����ς���
	void SetPattern(int pattern);

	void SetAnimCounter(float count);
};

