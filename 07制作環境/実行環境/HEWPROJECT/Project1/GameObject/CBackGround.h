#pragma once
#include "CGameObject.h"
//#include "CDirectX.h"

class CBackGround : public CGameObject
{
private:


public:
	// �R���X�g���N�^�E�f�X�g���N�^
	CBackGround(ID3D11Buffer* vb, ID3D11ShaderResourceView* tex,int num) :CGameObject(vb, tex, num) {}
	~CBackGround();

	// �w�i�̍X�V����
	void Update() override;
	// �w�i�̕`�揈��
	void Draw() override;

};

