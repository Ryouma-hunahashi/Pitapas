#pragma once
#include "CGameObject.h"
#include "CCollider.h"

class CWoodBox :public CGameObject
{
public:

	// �R���X�g���N�^�E�f�X�g���N�^
	CWoodBox(ID3D11Buffer* vb, ID3D11ShaderResourceView* tex, int num);
	~CWoodBox()override {}

	// �X�V����
	void Update() override;
	// �`�揈��
	void Draw() override;
	// �s�[�X�̒��ɃI�u�W�F�N�g�����邩�ǂ����𔻒肷��֐�
	bool isCheckObject(const CGameObject* parent)const override;

	// �����蔻��p�I�u�W�F�N�g
	CCollider* collider;

	float gra = 0.01f;

public:
	

};

