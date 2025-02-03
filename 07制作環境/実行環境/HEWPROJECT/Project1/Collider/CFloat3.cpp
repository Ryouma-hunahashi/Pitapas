//�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[
// �����蔻��v���O����
// 2023/12/12���_�ǉ����e
// �Q�[���I�u�W�F�N�g�̃X�e�[�^�X���Ǘ����邽�߂�
// �N���X��ǉ����܂����B
// �������Ō����X�e�[�^�X���ʒu�A�傫���A��]
// 
// �X�V�ҁFAT12B 07 ���їC��
// 
//�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[
#include "CFloat3.h"

CFloat3::CFloat3(float _x, float _y, float _z) { x = _x, y = _y, z = _z; }

const CFloat3 CFloat3::operator+(const CFloat3 _pos) const
{
	return CFloat3(this->x + _pos.x, this->y + _pos.y, this->z + _pos.z);
}

const CFloat3 CFloat3::operator-(const CFloat3 _pos) const
{
	return CFloat3(this->x - _pos.x, this->y - _pos.y, this->z - _pos.z);
}
