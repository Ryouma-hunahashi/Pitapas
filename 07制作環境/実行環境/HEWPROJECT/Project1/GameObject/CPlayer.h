#pragma once

#include "CDirectx.h"
#include"CGameObject.h"
#include "CCollider.h"

class CPlayer:public CGameObject
{	
public:
	// �R���X�g���N�^�@�f�X�g���N�^
	CPlayer(ID3D11Buffer* vb, ID3D11ShaderResourceView* tex, int num);
	~CPlayer()override {}

	// �X�V����
	void Update() override;
	// �`�揈��
	void Draw() override;


	bool sideflg = false;

	enum PLAYER_STATE
	{
		IDLE, // �ҋ@���
		WALK, // �ړ����
		JUMP, // �W�����v���
		DEAD  // ���S���
	};

private:
	// ���݂̌�����\���x�N�g���ϐ�
	DirectX::XMFLOAT3 dir = { 0, 0, 0 };

	PLAYER_STATE p_state = IDLE;

	// �e�N�X�`���i�[�ϐ�
	ID3D11ShaderResourceView* texturePlayer_Stay = NULL;// �v���C���[(�ҋ@���)
	ID3D11ShaderResourceView* texturePlayer_Walk = NULL;// �v���C���[(�ړ����)
	ID3D11ShaderResourceView* texturePlayer_Jump = NULL;// �v���C���[(�W�����v���)
	ID3D11ShaderResourceView* texturePlayer_Dead1 = NULL;// �v���C���[(���S���)
	ID3D11ShaderResourceView* texturePlayer_Dead2 = NULL;// �v���C���[(���S���)

public:
	// �l�p�̏������ϐ�
	CSquea squea_col;

	// �W�����v���x
	float vel;

	int cnt = 0;

	// �d��
	float gra = 0.1f;

	// �v���C���[�������ėǂ��ʒu
	float floor_line = -100.0f;

	// �v���C���[�̃X�e�[�g�Ɏg���t���O
	bool idle_flg = true; // �ҋ@
	bool jump_flg = false; // �W�����v
	bool dead_flg = false; // ���S

	// Ray�p�̐���
	CFloat3 Line[2] = { { 0.0f,0.0f,0.0f }, {0.0f,0.0f,0.0f} };

	CCollider* collider;

public:
	// �����o�[�֐�
	void RayUpdate()
	{
		// �v���C���[�̃��C�X�V
		Line[0] = { position.x,squea_col.Bottom,position.z };// �n�_
		Line[1] = { position.x,Line[1].y,position.z};// �I�_
	}

	// �W�����v���^�[���̔���
	void CheckJump_Turn(CSquea* object);
	// �W�����v����
	void Jump();

	// �d�͏���
	void PlayerGravitiy();

	// �v���C���[�̃X�e�[�g�Z�b�^�[
	void SetPlayerState(PLAYER_STATE ps) { p_state = ps; }

	// �v���C���[�̃e�N�X�`���Z�b�^�[�����
	// �����̏����ŕ�����g���Ċi�[��̕ϐ���؂�ւ��Ă���
	// �e�N�X�`���̊i�[����stay,walk,jump�̏��Ő������Ȃ�
	void SetPlayerTexture(ID3D11ShaderResourceView* );

	// �X�e�[�g���ƂɎ��s����֐�
	// �ҋ@���
	void IdleUpdate();
	void IdleDraw();
	// �ړ����
	void WalkUpdate();
	void WalkDraw();
	// �W�����v���
	void JumpUpdate();
	void JumpDraw();
	// ���S���
	void DeadUpdate();
	void DeadDraw();

};

