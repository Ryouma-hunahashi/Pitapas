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
    // プレイヤーの足元から下方向に伸びるレイ
    Line[0] = { position.x,squea_col.Bottom,position.z };			// 始点
    Line[1] = { position.x,squea_col.Bottom - 0.001f,position.z };  // 終点
}

void CPlayer::Update()
{
    this->collider->transform->position = { this->transform->position.x,this->transform->position.y,0.0f };
    this->collider->transform->scale.x = 0.9f;
    this->collider->transform->scale.y = 1.8f;
    this->collider->transform->position.y -= 0.15f;

    
    this->transform->VertexPos();

    // 下向きのレイを更新する
    Line[0] = { position.x , this->transform->Bottom,this->transform->position.z };
    Line[1] = { position.x , this->transform->Bottom-0.01f,this->transform->position.z };

	/* プレイヤーにしか行わない処理をここに書く */

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
    // 明示的に親の更新処理を呼び出す
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

	// 明示的に親の描画処理を呼び出す
	CGameObject::Draw();



    //position.x += 0.1f;

}

void CPlayer::CheckJump_Turn(CSquea* object)
{
    if (this->jump_flg)return;
    this->transform->VertexPos();
    this->collider->transform->VertexPos();
    object->VertexPos();
    // 自オブジェクトの足元から相手オブジェクトの
    // 頭の上までの距離を計算する
    float objheight = fabsf(this->transform->Bottom - object->Top);
    // 距離が自オブジェクトの半分の大きさより小さいか
    if (objheight < this->transform->scale.y && objheight > 0.1f && !this->isGravity )
    {
        // 相手オブジェクトの方が
        // 小さければジャンプフラグをＯＮ
        this->jump_flg = true;
        // 速度に初速を与える
        this->vel = 0.6f;
    }
    else
    {
        /*if (fabs(collider->transform->scale.x / 2) + fabs(object->scale.x / 2)-0.05f <
            transform->position.x - object->position.x)
        {
             相手オブジェクトの方が
             大きければベクトルを逆向きにする
            if (sideflg)
            {
                 左方向に向かせる
                this->sideflg = false;
                transform->scale.x *= -1;
            }
            else if (!sideflg)
            {
                 右方向に向かせる
                this->sideflg = true;
                transform->scale.x *= -1;
            }

            return;
        }*/
        //return;
        // 相手オブジェクトの方が
            // 大きければベクトルを逆向きにする
        if (objheight < 0.1f)return;
        if (sideflg)
        {
            // 左方向に向かせる
            this->sideflg = false;
            transform->scale.x *= -1;
        }
        else if (!sideflg)
        {
            // 右方向に向かせる
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
            // 速度から重力を引き現在位置に＋
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
            // 速度を0にして止める
            vel = 0.0f;
            // フラグをOFFにする
            jump_flg = false;
        }
        // 四角（当たり判定用）の位置更新
        squea_col.position = position;
        squea_col.VertexPos();

    }

    /*
    // ジャンプした結果地面より下に
    // 落ちていないかチェック
    if (this->collider->transform->Bottom < floor_line)
    {
        // 四角の下辺を地面と同じ高さにする
        squea_col.Bottom = floor_line;
        // プレイヤーの位置変数と四角の位置変数が
        // 別になっているためプレイヤーの位置変数も更新
        position.y = squea_col.Bottom + scaling.y / 2;
        // 速度を0にして止める
        vel = 0.0f;
        // フラグをOFFにする
        jump_flg = false;
    }
    */
}

void CPlayer::PlayerGravitiy()
{
    // プレイヤーの下辺が落下許可位置より高ければ
    // 重力処理を行う
    if (transform->Bottom > floor_line)
    {
        // ここで重力処理を行う
        this->transform->position.y -= gra;
        transform->VertexPos();
        // エラーチェック
        // プレイヤーの下辺が落下許可位置より低くなれば
        // 落下許可位置と同じ高さにする
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

// 待機状態(更新)
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

// 待機状態(描画)
void CPlayer::IdleDraw()
{
    this->CGameObject::texture = this->texturePlayer_Stay;
}

// 移動状態(更新)
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

    // 左方向に進む
    if (!sideflg)
    {
        this->transform->position.x -= 0.02f;
    }
    else // 右方向に進む
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

// 移動状態(描画)
void CPlayer::WalkDraw()
{
    this->CGameObject::texture = this->texturePlayer_Walk;
}

// ジャンプ状態(更新)
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

// ジャンプ状態(描画)
void CPlayer::JumpDraw()
{
    this->CGameObject::texture = this->texturePlayer_Jump;
}

// 死亡状態(更新)
void CPlayer::DeadUpdate()
{

}

// 死亡状態(描画)
void CPlayer::DeadDraw()
{
    this->CGameObject::texture = this->texturePlayer_Dead1;
}
