//�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[
// �����蔻��v���O����
// 2023/12/12���_�ǉ����e
// �}�b�v�Ǝl�p�̃Q�[���I�u�W�F�N�g�Ƃ�
// �����蔻����Ƃ邽�߂Ɏl�ӂƎl���_��
// �v�Z�A�������֐��ƃ����o�ϐ���ǉ����܂����B
// 
// �X�V�ҁFAT12B 07 ���їC��
// 
//�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[
#pragma once

#define SCALESIZE 1.0f
#include"CFloat3.h"
class CSquea
{
public:
	CFloat3 position = {0,0,0};
	CFloat3 rotate = {0,0,0};
	CFloat3 scale = {1,1,1};

	// �l�ӂ̍��W
	float Left;
	float Right;
	float Top;
	float Bottom;

	// �l�p�̎l���_
	CFloat3 Vertices[4] =
	{
	  { Left,  Top, 0},	// ����
	  { Right, Top, 0},	// �E��
	  { Left,  Bottom, 0},	// ����
	  { Right, Bottom, 0}	// �E��
	};

	// �R���X�g���N�^
	// �l�ӂ̍��W�����ߕۑ�����
	CSquea();
	void VertexPos(void);

	
};

