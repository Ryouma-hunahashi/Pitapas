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
#pragma once
class CFloat3
{
public:
	float x, y, z;

	CFloat3(float _x = 0.0f, float _y = 0.0f, float _z = 0.0f);

	const CFloat3 operator+(const CFloat3)const; // �t���[�g�^�R�����̑����Z
	const CFloat3 operator-(const CFloat3)const; // �t���[�g�^�R�����̈����Z

};

