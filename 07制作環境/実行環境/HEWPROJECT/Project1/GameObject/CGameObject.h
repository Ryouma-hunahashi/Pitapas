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

enum LayerNum //描画順管理用の列挙型
{
	BLACK_OUT,				//暗転用レイヤー
	UI,						//UI用レイヤー
	FORE_GROUND,			//前景用レイヤー
	MIDDLE_GROUND,			//中景用レイヤー前面
	PLAY_GROUND_FRONT,		//未定
	PLAY_GROUND,			//未定
	PLAY_GROUND_BACK,		//未定
	MIDDLE_GROUND_BACK,		//中景用レイヤー背面
	BACK_GROUND,			//背景用レイヤー
	END,
};

struct ConstBuffer
{
	// UV座標移動行列
	DirectX::XMMATRIX matrixTex;
	// 投影行列
	DirectX::XMMATRIX matrixProj;
	// ワールド変換行列
	DirectX::XMMATRIX matrixWorld;

	// マテリアル色
	DirectX::XMFLOAT4 materialDiffuse;
};

class CCollider;

class CGameObject
{
public:
	// 頂点数を保存しておく変数
	int vertexNum = 6;

	float gravity = 0.01f;	//重力
protected:
	// コライダー用
	ID3D11Buffer* vertexBufferCollider;
	ID3D11ShaderResourceView* textureCollider;

	CDirectX::FLOAT_XY size;
	CDirectX::FLOAT_XY center;
	CDirectX::FLOAT_XY uv;

protected:
	// 描画に使用する頂点バッファ
	ID3D11Buffer* vertexBuffer;
	// 描画に使用するテクスチャ
	ID3D11ShaderResourceView* texture;

	UINT strides = sizeof(CDirectX::Vertex);
	UINT offset = 0;

	// 描画順番を決める変数
	LayerNum DrawNum;

public:
	//関数
	//コンストラクタ
	//CGameObject();
	CGameObject(ID3D11Buffer* vb, ID3D11ShaderResourceView* tex,int num);

	//デストラクタ
	virtual ~CGameObject();

	//更新処理
	virtual void Update();

	//描画処理
	virtual void Draw();


	// パズルのピースの中にオブジェクトがあるかどうか判定する関数
	virtual bool isCheckObject(const CGameObject* other)const;
public:

	const int GetLayer()const;
	const void Setlayer(LayerNum _num){ this->DrawNum = _num; }
	const void Settexture(ID3D11ShaderResourceView* _tex) { this->texture = _tex; }

	// 描画するしないのときに使用する判定
	bool isDraw = true;
	
	// 重力を加算するかどうかに使用する判定
	bool isGravity = true;

	// 座標を保存しておくクラス
	CSquea *transform;
	
	// 当たり判定用オブジェクト
	CCollider* collider;
	
	// アニメーション座標を計算するクラス
	CAnimation* anim;
	
	// このGameObjectの仮想世界での位置（ワールド座標）
	CFloat3 position = { 0,0,0 };
	
	// オイラー角
	CFloat3 rotation = { 0,0,0 };

	// 拡大縮小率
	CFloat3 scaling = { 1, 1, 1 };

	// このキャラクターに適用するマテリアル色
	DirectX::XMFLOAT4 materialDiffuse = { 1,1,1,1 };

	// ハーフボックス用
	bool ishalf = false;

};

