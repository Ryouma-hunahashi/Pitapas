#pragma once


//#include"main.h"

//#include"CCharacter.h"

#include "CDirectx.h"
#include "CSquea.h"
#include "CAnimation.h"

#define PIECESIZE_X (16.0f/PIECE_X)
#define PIECESIZE_Y (9.0f/PIECE_Y)
#define PIECE_X 7
#define PIECE_Y 4

enum LayerNum //�`�揇�Ǘ��p�̗񋓌^
{
	BLACK_OUT,				//�Ó]�p���C���[
	UI,						//UI�p���C���[
	FORE_GROUND,			//�O�i�p���C���[
	MIDDLE_GROUND,			//���i�p���C���[�O��
	PLAY_GROUND_FRONT,		//����
	PLAY_GROUND,			//����
	PLAY_GROUND_BACK,		//����
	MIDDLE_GROUND_BACK,		//���i�p���C���[�w��
	BACK_GROUND,			//�w�i�p���C���[
	END,
};

struct ConstBuffer
{
	// UV���W�ړ��s��
	DirectX::XMMATRIX matrixTex;
	// ���e�s��
	DirectX::XMMATRIX matrixProj;
	// ���[���h�ϊ��s��
	DirectX::XMMATRIX matrixWorld;

	// �}�e���A���F
	DirectX::XMFLOAT4 materialDiffuse;
};

class CCollider;

class CGameObject
{
public:
	// ���_����ۑ����Ă����ϐ�
	int vertexNum = 6;

	float gravity = 0.01f;	//�d��
protected:
	// �R���C�_�[�p
	ID3D11Buffer* vertexBufferCollider;
	ID3D11ShaderResourceView* textureCollider;

	CDirectX::FLOAT_XY size;
	CDirectX::FLOAT_XY center;
	CDirectX::FLOAT_XY uv;

protected:
	// �`��Ɏg�p���钸�_�o�b�t�@
	ID3D11Buffer* vertexBuffer;
	// �`��Ɏg�p����e�N�X�`��
	ID3D11ShaderResourceView* texture;

	UINT strides = sizeof(CDirectX::Vertex);
	UINT offset = 0;

	// �`�揇�Ԃ����߂�ϐ�
	LayerNum DrawNum;

public:
	//�֐�
	//�R���X�g���N�^
	//CGameObject();
	CGameObject(ID3D11Buffer* vb, ID3D11ShaderResourceView* tex,int num);

	//�f�X�g���N�^
	virtual ~CGameObject();

	//�X�V����
	virtual void Update();

	//�`�揈��
	virtual void Draw();


	// �p�Y���̃s�[�X�̒��ɃI�u�W�F�N�g�����邩�ǂ������肷��֐�
	virtual bool isCheckObject(const CGameObject* other)const;
public:

	const int GetLayer()const;
	const void Setlayer(LayerNum _num){ this->DrawNum = _num; }
	const void Settexture(ID3D11ShaderResourceView* _tex) { this->texture = _tex; }

	// �`�悷�邵�Ȃ��̂Ƃ��Ɏg�p���锻��
	bool isDraw = true;
	
	// �d�͂����Z���邩�ǂ����Ɏg�p���锻��
	bool isGravity = true;

	// ���W��ۑ����Ă����N���X
	CSquea *transform;
	
	// �����蔻��p�I�u�W�F�N�g
	CCollider* collider;
	
	// �A�j���[�V�������W���v�Z����N���X
	CAnimation* anim;
	
	// ����GameObject�̉��z���E�ł̈ʒu�i���[���h���W�j
	CFloat3 position = { 0,0,0 };
	
	// �I�C���[�p
	CFloat3 rotation = { 0,0,0 };

	// �g��k����
	CFloat3 scaling = { 1, 1, 1 };

	// ���̃L�����N�^�[�ɓK�p����}�e���A���F
	DirectX::XMFLOAT4 materialDiffuse = { 1,1,1,1 };

	// �n�[�t�{�b�N�X�p
	bool ishalf = false;

};

