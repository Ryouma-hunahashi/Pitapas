//�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[
// �����蔻��v���O����
// 2023/12/12���_�ǉ����e
// CRect�N���X��DX�̕��Ŏg���Ȃ���������
// ���O���ύX����܂����B
// �}�b�v�Ǝl�p�̃Q�[���I�u�W�F�N�g�Ƃ�
// �����蔻����Ƃ邽�߂Ɏl�ӂƎl���_��
// �v�Z�A�������֐���ǉ����܂����B
// 
// �X�V�ҁFAT12B 07 ���їC��
// 
//�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[

#include "CSquea.h"

CSquea::CSquea()
{
	VertexPos();
}

void CSquea::VertexPos(void)
{
	Left = this->position.x - this->scale.x/2;
	Right = this->position.x + this->scale.x/2;
	Top = this->position.y + this->scale.y/2;
	Bottom = this->position.y - this->scale.y/2;

	Vertices[0] = { Left,Top };
	Vertices[1] = { Right,Top };
	Vertices[2] = { Right,Bottom };
	Vertices[3] = { Left,Bottom };
}


