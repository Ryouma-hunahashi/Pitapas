#pragma once
#include"CGameObject.h"
#include "CCollider.h"

class CFloor :public CGameObject
{
public:
	// �R���X�g���N�^�@�f�X�g���N�^
	CFloor(ID3D11Buffer* vb, ID3D11ShaderResourceView* tex, int num);
	~CFloor();

	// �X�V����
	void Update() override;
	// �`�揈��
	void Draw() override;

};

