#pragma once

#include "CDirectx.h"
#include"CGameObject.h"
#include "CCollider.h"

class CPlayer:public CGameObject
{	
public:
	// コンストラクタ　デストラクタ
	CPlayer(ID3D11Buffer* vb, ID3D11ShaderResourceView* tex, int num);
	~CPlayer()override {}

	// 更新処理
	void Update() override;
	// 描画処理
	void Draw() override;


	bool sideflg = false;

	enum PLAYER_STATE
	{
		IDLE, // 待機状態
		WALK, // 移動状態
		JUMP, // ジャンプ状態
		DEAD  // 死亡状態
	};

private:
	// 現在の向きを表すベクトル変数
	DirectX::XMFLOAT3 dir = { 0, 0, 0 };

	PLAYER_STATE p_state = IDLE;

	// テクスチャ格納変数
	ID3D11ShaderResourceView* texturePlayer_Stay = NULL;// プレイヤー(待機状態)
	ID3D11ShaderResourceView* texturePlayer_Walk = NULL;// プレイヤー(移動状態)
	ID3D11ShaderResourceView* texturePlayer_Jump = NULL;// プレイヤー(ジャンプ状態)
	ID3D11ShaderResourceView* texturePlayer_Dead1 = NULL;// プレイヤー(死亡状態)
	ID3D11ShaderResourceView* texturePlayer_Dead2 = NULL;// プレイヤー(死亡状態)

public:
	// 四角の情報を持つ変数
	CSquea squea_col;

	// ジャンプ速度
	float vel;

	int cnt = 0;

	// 重力
	float gra = 0.1f;

	// プレイヤーが落ちて良い位置
	float floor_line = -100.0f;

	// プレイヤーのステートに使うフラグ
	bool idle_flg = true; // 待機
	bool jump_flg = false; // ジャンプ
	bool dead_flg = false; // 死亡

	// Ray用の線分
	CFloat3 Line[2] = { { 0.0f,0.0f,0.0f }, {0.0f,0.0f,0.0f} };

	CCollider* collider;

public:
	// メンバー関数
	void RayUpdate()
	{
		// プレイヤーのレイ更新
		Line[0] = { position.x,squea_col.Bottom,position.z };// 始点
		Line[1] = { position.x,Line[1].y,position.z};// 終点
	}

	// ジャンプかターンの判定
	void CheckJump_Turn(CSquea* object);
	// ジャンプ処理
	void Jump();

	// 重力処理
	void PlayerGravitiy();

	// プレイヤーのステートセッター
	void SetPlayerState(PLAYER_STATE ps) { p_state = ps; }

	// プレイヤーのテクスチャセッターを作る
	// 内部の処理で分岐を使って格納先の変数を切り替えている
	// テクスチャの格納順はstay,walk,jumpの順で正しくなる
	void SetPlayerTexture(ID3D11ShaderResourceView* );

	// ステートごとに実行する関数
	// 待機状態
	void IdleUpdate();
	void IdleDraw();
	// 移動状態
	void WalkUpdate();
	void WalkDraw();
	// ジャンプ状態
	void JumpUpdate();
	void JumpDraw();
	// 死亡状態
	void DeadUpdate();
	void DeadDraw();

};

