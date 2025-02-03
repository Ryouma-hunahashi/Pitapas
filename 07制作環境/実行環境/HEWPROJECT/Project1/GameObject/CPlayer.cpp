#include "CPlayer.h"

#include "CInput.h"

CPlayer::CPlayer(ID3D11Buffer* vb, ID3D11ShaderResourceView* tex,int num):CGameObject(vb,tex,num)
{
    center = { 0.0f, 0.0f };
    size = { 1.0f,1.0f };
    uv = { 1.0f, 1.0f };
    CDirectX::Get()->D3D_CreateSquare(center, size, uv, &vertexBufferCollider);
    CDirectX::Get()->D3D_LoadTexture(L"asset/1_1_BoxCollider.png", &textureCollider);	// 

    collider = new CCollider(vertexBufferCollider, textureCollider, LayerNum::FORE_GROUND);
    scaling = { 0.5f,0.5f,1.0f };
    squea_col.scale = scaling;
    vel = 0;
    squea_col.VertexPos();
    // �v���C���[�̑������牺�����ɐL�т郌�C
    Line[0] = { position.x,squea_col.Bottom,position.z };			// �n�_
    Line[1] = { position.x,squea_col.Bottom - 0.001f,position.z };  // �I�_
}

void CPlayer::Update()
{
    this->collider->transform->position = { this->transform->position.x,this->transform->position.y,0.0f };
    this->collider->transform->scale.x = 0.9f;
    this->collider->transform->scale.y = 1.8f;
    this->collider->transform->position.y -= 0.15f;

    
    this->transform->VertexPos();

    // �������̃��C���X�V����
    Line[0] = { position.x , this->transform->Bottom,this->transform->position.z };
    Line[1] = { position.x , this->transform->Bottom-0.01f,this->transform->position.z };

	/* �v���C���[�ɂ����s��Ȃ������������ɏ��� */

    switch (p_state)
    {
    case CPlayer::IDLE:
        IdleUpdate();
        break;
    case CPlayer::WALK:
        WalkUpdate();
        break;
    case CPlayer::JUMP:
        JumpUpdate();
        break;
    case CPlayer::DEAD:
        DeadUpdate();
        break;
    default:
        break;
    }
  
    if (this->isGravity)
    {
        CPlayer::PlayerGravitiy();
    }
    this->collider->Update();
    // �����I�ɐe�̍X�V�������Ăяo��
	CGameObject::Update();
}

void CPlayer::Draw()
{

    switch (p_state)
    {
    case CPlayer::IDLE:
        IdleDraw();
        break;
    case CPlayer::WALK:
        WalkDraw();
        break;
    case CPlayer::JUMP:
        JumpDraw();
        break;
    case CPlayer::DEAD:
        DeadDraw();
        break;
    default:
        break;
    }

	// �����I�ɐe�̕`�揈�����Ăяo��
	CGameObject::Draw();



    //position.x += 0.1f;

}

void CPlayer::CheckJump_Turn(CSquea* object)
{
    if (this->jump_flg)return;
    this->transform->VertexPos();
    this->collider->transform->VertexPos();
    object->VertexPos();
    // ���I�u�W�F�N�g�̑������瑊��I�u�W�F�N�g��
    // ���̏�܂ł̋������v�Z����
    float objheight = fabsf(this->transform->Bottom - object->Top);
    // ���������I�u�W�F�N�g�̔����̑傫����菬������
    if (objheight < this->transform->scale.y && objheight > 0.1f && !this->isGravity )
    {
        // ����I�u�W�F�N�g�̕���
        // ��������΃W�����v�t���O���n�m
        this->jump_flg = true;
        // ���x�ɏ�����^����
        this->vel = 0.6f;
    }
    else
    {
        /*if (fabs(collider->transform->scale.x / 2) + fabs(object->scale.x / 2)-0.05f <
            transform->position.x - object->position.x)
        {
             ����I�u�W�F�N�g�̕���
             �傫����΃x�N�g�����t�����ɂ���
            if (sideflg)
            {
                 �������Ɍ�������
                this->sideflg = false;
                transform->scale.x *= -1;
            }
            else if (!sideflg)
            {
                 �E�����Ɍ�������
                this->sideflg = true;
                transform->scale.x *= -1;
            }

            return;
        }*/
        //return;
        // ����I�u�W�F�N�g�̕���
            // �傫����΃x�N�g�����t�����ɂ���
        if (objheight < 0.1f)return;
        if (sideflg)
        {
            // �������Ɍ�������
            this->sideflg = false;
            transform->scale.x *= -1;
        }
        else if (!sideflg)
        {
            // �E�����Ɍ�������
            this->sideflg = true;
            transform->scale.x *= -1;
        }
    }
}

void CPlayer::Jump()
{
    if (cnt < 10)
    {
        cnt++;
    }
    else
    {
        if (vel >= 0)
        {
            // ���x����d�͂��������݈ʒu�Ɂ{
            vel -= gra;
            this->transform->position.y += vel;
        }
        else if (vel <= 0 && vel >= (-0.09f))
        {
            vel -= gra/2.0f;
            this->transform->position.y += vel;
            if (sideflg)
            {
                this->transform->position.x += fabs(0.8f);
            }
            else if (!sideflg)
            {
                this->transform->position.x -= fabs(0.8f);
            }
        }
        else
        {
            // ���x��0�ɂ��Ď~�߂�
            vel = 0.0f;
            // �t���O��OFF�ɂ���
            jump_flg = false;
        }
        // �l�p�i�����蔻��p�j�̈ʒu�X�V
        squea_col.position = position;
        squea_col.VertexPos();

    }

    /*
    // �W�����v�������ʒn�ʂ�艺��
    // �����Ă��Ȃ����`�F�b�N
    if (this->collider->transform->Bottom < floor_line)
    {
        // �l�p�̉��ӂ�n�ʂƓ��������ɂ���
        squea_col.Bottom = floor_line;
        // �v���C���[�̈ʒu�ϐ��Ǝl�p�̈ʒu�ϐ���
        // �ʂɂȂ��Ă��邽�߃v���C���[�̈ʒu�ϐ����X�V
        position.y = squea_col.Bottom + scaling.y / 2;
        // ���x��0�ɂ��Ď~�߂�
        vel = 0.0f;
        // �t���O��OFF�ɂ���
        jump_flg = false;
    }
    */
}

void CPlayer::PlayerGravitiy()
{
    // �v���C���[�̉��ӂ��������ʒu��荂�����
    // �d�͏������s��
    if (transform->Bottom > floor_line)
    {
        // �����ŏd�͏������s��
        this->transform->position.y -= gra;
        transform->VertexPos();
        // �G���[�`�F�b�N
        // �v���C���[�̉��ӂ��������ʒu���Ⴍ�Ȃ��
        // �������ʒu�Ɠ��������ɂ���
//        if (transform->Bottom < floor_line)
    }
}

void CPlayer::SetPlayerTexture(ID3D11ShaderResourceView* _tex)
{
    static int cnt = 0;
    switch (cnt % 4)
    {
    case 0:
        this->texturePlayer_Stay = _tex;
        break;
    case 1:
        this->texturePlayer_Walk = _tex;
        break;
    case 2:
        this->texturePlayer_Jump = _tex;
        break;
    case 3:
        this->texturePlayer_Dead1 = _tex;
    default:
        break;
    }
    cnt++;
}

// �ҋ@���(�X�V)
void CPlayer::IdleUpdate()
{
    if (idle_flg == true)
    {

    }
    else
    {
        SetPlayerState(CPlayer::PLAYER_STATE::WALK);
    }
}

// �ҋ@���(�`��)
void CPlayer::IdleDraw()
{
    this->CGameObject::texture = this->texturePlayer_Stay;
}

// �ړ����(�X�V)
void CPlayer::WalkUpdate()
{
    if (this->transform->position.x >= 7.5f)
    {
        sideflg = false;
        this->transform->scale.x *= -1.0f;
    }
    else if (this->transform->position.x <= -7.5f)
    {
        sideflg = true;
        this->transform->scale.x *= -1.0f;
    }

    // �������ɐi��
    if (!sideflg)
    {
        this->transform->position.x -= 0.02f;
    }
    else // �E�����ɐi��
    {
        this->transform->position.x += 0.02f;
    }

    if (jump_flg == true)
    {
        SetPlayerState(CPlayer::PLAYER_STATE::JUMP);
        cnt = 0;
        this->anim->SetAnimCounter(0.0f);
        this->anim->animSpeed = 0.14f;
    }

    if (dead_flg)
    {
        SetPlayerState(CPlayer::PLAYER_STATE::DEAD);
        this->anim->SetAnimCounter(0.0f);
        this->anim->SetPattern(CAnimation::PLAYER_DEAD);
        this->anim->animSpeed = 0.1f;
        this->transform->position.x += 0.7f;
    }
}

// �ړ����(�`��)
void CPlayer::WalkDraw()
{
    this->CGameObject::texture = this->texturePlayer_Walk;
}

// �W�����v���(�X�V)
void CPlayer::JumpUpdate()
{
    if (jump_flg == true)
    {
        Jump();
    }
    if (jump_flg == false)
    {
        SetPlayerState(CPlayer::PLAYER_STATE::WALK);
        this->anim->animSpeed = 0.07f;
    }

}

// �W�����v���(�`��)
void CPlayer::JumpDraw()
{
    this->CGameObject::texture = this->texturePlayer_Jump;
}

// ���S���(�X�V)
void CPlayer::DeadUpdate()
{

}

// ���S���(�`��)
void CPlayer::DeadDraw()
{
    this->CGameObject::texture = this->texturePlayer_Dead1;
}
