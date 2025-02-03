#pragma once

#include "CGameObject.h"
#include "CCollider.h"

class CPiece : public CGameObject
{
public:
	CPiece(ID3D11Buffer* vb, ID3D11ShaderResourceView* tex, int num);
	~CPiece()override{}

	void Update() override;
	void Draw()override;

	// �s�[�X�̒��ɃI�u�W�F�N�g�����邩�ǂ����𔻒肷��֐�
	bool isCheckObject(const CGameObject* parent)const override;

	// �����蔻��p�I�u�W�F�N�g
	CCollider* collider;
};

