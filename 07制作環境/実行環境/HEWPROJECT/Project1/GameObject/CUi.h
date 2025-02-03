#pragma once
//#include "CFade.h"
//#include "CUiEasing.h"
#include "CDirectx.h"
#include "CSquea.h"
#include "CGameObject.h"
class CAnimation;


class CUi: public CGameObject
{
protected:
	// �`��Ɏg�p���钸�_�o�b�t�@
	ID3D11Buffer* vertexBuffer;
	// �`��Ɏg�p����e�N�X�`��
	ID3D11ShaderResourceView* texture;


	// ���݂̌�����\���x�N�g���ϐ�
	DirectX::XMFLOAT3 dir = { 0, 0, 0 };

	// �A���t�@�u�����h�p
	ID3D11BlendState* m_pBlendStateAlpha;

	// �C�[�W���O�N���X�I�u�W�F�N�g
	//CUiEasing* easing;


	// �b��
	int frame = 0;

private:

	//CFade*  fade;
	//
	//CFade::FADE_STATE  fadeState = CFade::NO_FADE; // ���݂̃t�F�[�h���

public:
	// ���z���E�̒��̈ʒu���W
	CFloat3 pos = { 0, 0, 0 };

	// �f�t�H���g�̈ʒu���W
	//const DirectX::XMFLOAT3 DEFAULT_POS;

	// �g��k���������ϐ�
	DirectX::XMFLOAT3 scale = { 1.0f, 1.0f, 1.0f };
	// ��]�p�x
	float angle = 0.0f;

	// ���̃L�����N�^�[�ɓK�p����}�e���A���F
	//DirectX::XMFLOAT4 materialDiffuse = { 1,1,1,1 };

	// �A�N�e�B�u/��A�N�e�B�u�؂�ւ��ϐ�
	bool isActive = true;


public:
	// �����o�[�֐�
	// �f�[�^�̏���������
	void InitializeData();

	// �����������i�R���X�g���N�^�j
	// �����F�g�p���钸�_�o�b�t�@�ƃe�N�X�`����n��
	CUi(ID3D11Buffer* vb, ID3D11ShaderResourceView* tex, int num);

	// �I�������i�f�X�g���N�^�j
	~CUi() override{};


	// �X�V����
	void Update();
	// �`�揈��
	void Draw();



	// �A�j���[�V�����Đ����x��ݒ肷��֐�
	void SetAnimationSpeed(float speed);

	// �A�j���[�V�����p�^�[����ݒ肷��֐�
	void SetAnimationPattern(int pattern);

	// �t�F�[�h���
	//void SetFadeState(CFade::FADE_STATE _fadeState);

	// �e�@�\�}�l�[�W���[
	void FadeManager(void);

	void ColorManager(void);

	void ScaleManager(void);

	void MoveManager(void);
	

	DirectX::XMFLOAT3 GetDir()
	{
		return dir;
	}

	void SetDir(DirectX::XMFLOAT3 v)
	{
		dir = v;
	}
};

