//�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[
// �����蔻��v���O����
// 2023/12/12���_�ǉ����e
// �}�b�v�Ǝl�p�̃Q�[���I�u�W�F�N�g�Ƃ�
// �����蔻���ǉ����܂����B
// �O���ԂŌ��������o�O�������������܂����B
// CRect�N���X���g���Ă���������CSquea�N���X��
// �u��������Ă��܂��B�i���̏����ɕω��͂Ȃ��j
// 
// �X�V�ҁFAT12B 07 ���їC��
// 
//�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[

#include "Collision.h"
#include "CGameObject.h"

// �}�N����`
// �}�b�v�`�b�v�������̃T�C�Y
#define CHIP_SIZE_X		(1)
#define CHIP_SIZE_Y		(1)

// �l�p�̂����蔻��(������������)
CollisionDirection SquareCollision(const CGameObject* _rect1, const CGameObject* _rect2)
{
	//for (int i = 0; i < 4; i++)
	//{
	//	// ��ڂ̃I�u�W�F�N�g�̃x�N�g�����擾����
	//	CFloat3 VAn = _rect1->transform->Vertices[(i + 1 % 4)] - _rect1->transform->Vertices[i];

	//	for (int j = 0; j < 4; j++)
	//	{
	//		// ��ڂ̃I�u�W�F�N�g�̃x�N�g�����擾����
	//		CFloat3 VBn = _rect2->transform->Vertices[(j + 1 % 4)] - _rect2->transform->Vertices[j];

	//		// ��̃I�u�W�F�N�g�̊O�ς����߂�
	//		float crossTorect = VAn.x * VBn.y - VAn.y * VBn.x;

	//		// 0�ł���Ε��s�ł��邽�ߎ��ɍs��
	//		if (crossTorect == 0)continue;

	//		// 2���̎n�_����I�_�̃x�N�g�������߂�
	//		CFloat3 crossVec = _rect2->transform->Vertices[j] - _rect1->transform->Vertices[i];
	//		// �n�_���m�̃x�N�g���Ɗe�ӂ̃x�N�g���̊O�ς��v�Z����
	//		float crossVtoV1 = crossVec.x * VAn.y - crossVec.y * VAn.x;
	//		float crossVtoV2 = crossVec.x * VBn.y - crossVec.y * VBn.x;

	//		// ��������
	//		float cross1 = crossVtoV2 / crossTorect;
	//		float cross2 = crossVtoV1 / crossTorect;

	//		// �덷��e�F����
	//		const float eos = 0.00001f;

	//		// �������Ă��Ȃ���΁A���̔����
	//		if (cross1 + eos < 0 || cross1 - eos>1 || cross2 + eos < 0 || cross2 - eos>1)
	//			continue;

	//		// �S�č��v���Ă��Ȃ���Ό������Ă���
	//		return COLLISION_UP;

	//	}
	//}






	float dis_x = fabsf(_rect1->transform->position.x - _rect2->transform->position.x);
	float dis_y = fabsf(_rect1->transform->position.y - _rect2->transform->position.y);

	float size_x = fabsf(_rect1->transform->scale.x + _rect2->transform->scale.x) / 2;
	float size_y = fabsf(_rect1->transform->scale.y + _rect2->transform->scale.y) / 2;

	if (dis_x < size_x)
	{
		if (dis_y < size_y)
		{
			float o_x = size_x - dis_x;
			float o_y = size_y - dis_y;

			if (o_x < o_y)
			{
				return (_rect1->transform->position.x < _rect2->transform->position.x) ? COLLISION_LEFT : COLLISION_RIGHT;
			}
			else
			{
				return (_rect1->transform->position.y < _rect2->transform->position.y) ? COLLISION_DOWN : COLLISION_UP;
			}
		}
	}
	return COLLISION_NULL;

	// ��̃I�u�W�F�N�g�̋����𑪂�
	CFloat3 distance(fabsf(_rect1->transform->position.x - _rect2->transform->position.x), fabsf(_rect1->transform->position.y - _rect2->transform->position.y));

	// ��̃I�u�W�F�N�g�T�C�Y�̍��v�l
	CFloat3 sizeSum((fabsf(_rect1->transform->scale.x) + fabsf(_rect2->transform->scale.x))/2.0f, (fabsf(_rect1->transform->scale.y) + fabsf(_rect2->transform->scale.y))/2.0f);

	float disSqLength = distance.x * distance.x + distance.y * distance.y;
	float sizeSqLength = sizeSum.x * sizeSum.x + sizeSum.y * sizeSum.y;

	// �������T�C�Y�������������
	if (disSqLength <= sizeSqLength)
	{
		// �x�N�g�����v�Z
		CFloat3 vector = _rect1->transform->position - _rect2->transform->position;
		// Y�̐�Βl�̂ق����傫�����
		if (fabsf(vector.x) <= fabsf(vector.y))
		{
			// �{�Ȃ���Ԃ�
			if (vector.y > 0)
			{
				//std::cout << "��ɓ���������" << std::endl;
				return CollisionDirection::COLLISION_UP;
			}
			else
			{
				// �[�Ȃ牺��Ԃ�
				//std::cout << "���ɓ���������" << std::endl;
				return CollisionDirection::COLLISION_DOWN;
			}
		}
		// X�̐�Βl�̕����傫�����
		else
		{
			// �{�Ȃ�E��Ԃ�
			if (vector.x > 0)
			{
				//std::cout << "�E�ɓ���������" << std::endl;
				return CollisionDirection::COLLISION_RIGHT;
			}
			else
			{
				// �[�Ȃ獶��Ԃ�
				//std::cout << "���ɓ���������" << std::endl;
				return CollisionDirection::COLLISION_LEFT;
			}
		}

	}

	// �ǂ��ɂ��������Ă��Ȃ��ꍇ
	//std::cout << "�������ĂȂ���" << std::endl;
	return COLLISION_NULL;
}

bool DoSquareCollision(const CGameObject* _rect1, const CGameObject* _rect2)
{
	for (int i = 0; i < 4; i++)
	{
		// ��ڂ̃I�u�W�F�N�g�̃x�N�g�����擾����
		CFloat3 VAn = _rect1->transform->Vertices[(i + 1) % 4] - _rect1->transform->Vertices[i];

		for (int j = 0; j < 4; j++)
		{
			// ��ڂ̃I�u�W�F�N�g�̃x�N�g�����擾����
			CFloat3 VBn = _rect2->transform->Vertices[(j + 1)% 4] - _rect2->transform->Vertices[j];

			// ��̃I�u�W�F�N�g�̊O�ς����߂�
			float crossTorect = VAn.x * VBn.y - VAn.y * VBn.x;

			// 0�ł���Ε��s�ł��邽�ߎ��ɍs��
			if (crossTorect == 0)continue;

			// 2���̎n�_����I�_�̃x�N�g�������߂�
			CFloat3 crossVec = _rect2->transform->Vertices[j] - _rect1->transform->Vertices[i];
			// �n�_���m�̃x�N�g���Ɗe�ӂ̃x�N�g���̊O�ς��v�Z����
			float crossVtoV1 = crossVec.x * VAn.y - crossVec.y * VAn.x;
			float crossVtoV2 = crossVec.x * VBn.y - crossVec.y * VBn.x;

			// ��������
			float cross1 = crossVtoV2 / crossTorect;
			float cross2 = crossVtoV1 / crossTorect;

			// �덷��e�F����
			const float eps = 0.001f;

			// �������Ă��Ȃ���΁A���̔����
			if (cross1 + eps < 0 || cross1 - eps > 1 || cross2 + eps < 0 || cross2 - eps > 1)
				continue;

			// �S�č��v���Ă��Ȃ���Ό������Ă���
			return true;

		}
	}

	return false;
}


// �_�Ǝl�p�̓����蔻��
// �g�p��̓J�[�\���ƃI�u�W�F�N�g�̓����蔻�蓙
// �_�̈ʒu�i���W�j�ƃI�u�W�F�N�g�i�ʒu�A�傫���j�������Ƃ��Ď󂯎��
// �������Ă��邩�̔����bool�^�itrue,false�j�ŕԂ�
bool DotSquareCollision(const CFloat3* _dot, const CSquea* _rect)
{
	// �_�̈ʒu���l�p�̒��ɓ����Ă��邩�H
	// �i�E�[���_�̈ʒu�������A���[���_�̈ʒu���E���A
	// �@��[���_�̈ʒu�������A���[���_�̈ʒu����Ȃ�true��Ԃ��j
	return (_rect->position.x + _rect->scale.x/2 > _dot->x && 
			_rect->position.x - _rect->scale.x/2 < _dot->x&&
			_rect->position.y + _rect->scale.y/2 > _dot->y && 
			_rect->position.y - _rect->scale.y/2 < _dot->y);
}

// �_�Ɖ~�̓����蔻��
bool DotCircleCollision(const CFloat3& _dot, const CCircle& _circle)
{
	// �������v�Z
	CFloat3 distance = _dot - _circle.position;

	// �������悷��
	float dtc = distance.x * distance.x + distance.y * distance.y;

	// �������~�̔��a��菬�������ture
	return (dtc <= _circle.radius);

}

