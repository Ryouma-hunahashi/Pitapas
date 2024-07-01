#pragma once
//�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[
// �����蔻��v���O����
// 2023/12/12���_�ǉ����e
// �}�b�v�Ǝl�p�̃Q�[���I�u�W�F�N�g�Ƃ�
// �����蔻���ǉ����܂����B
// 
// �X�V�ҁFAT12B 07 ���їC��
// 
//�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[
#include"CSquea.h"
#include"CCircle.h"
#include"CGameObject.h"
#include<math.h>

// �O���錾
class CGameObject;

// �񋓑�
// ������������{�������ĂȂ��A��A���A���A�E};
enum CollisionDirection { COLLISION_NULL, COLLISION_UP, COLLISION_DOWN, COLLISION_LEFT, COLLISION_RIGHT };

// �l�p�̂����蔻��
// �߂�l��CollisionDirection�ɂȂ��Ă��邯��bool�^�ł��߂�l�̎󂯎�肪�o����
// CollisionDirection���񋓑̂Ȃ��ߖ߂�l�͐��l������
CollisionDirection SquareCollision(const CGameObject*, const CGameObject*);

bool DoSquareCollision(const CGameObject* _rect1, const CGameObject* _rect2);

// �_�Ǝl�p�̓����蔻��
bool DotSquareCollision(const CFloat3*, const CSquea*);

// �_�Ɖ~�̓����蔻��
bool DotCircleCollision(const CFloat3&, const CCircle&);

