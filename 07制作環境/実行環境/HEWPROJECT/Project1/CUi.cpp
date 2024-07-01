#include "CUi.h"
#include "CCollider.h"


using namespace DirectX;

CUi::CUi(ID3D11Buffer* vb, ID3D11ShaderResourceView* tex, int num) : CGameObject(vb, tex, num)
{
	vertexBuffer = vb;
	texture = tex;

    center = { 0.0f, 0.0f };
    size = { 1.0f, 1.0f };
    uv = { 1.0f, 1.0f };
    CDirectX::Get()->D3D_CreateSquare(center, size, uv, &vertexBufferCollider);
    CDirectX::Get()->D3D_LoadTexture(L"asset/1_1_BoxCollider.png", &textureCollider);	// 

    collider = new CCollider(vb, textureCollider, LayerNum::FORE_GROUND);

    // アニメーションクラスを実体化（アニメーション機能を動くようにする）
    anim = new CAnimation(1, 1);
    anim->SetPattern(CAnimation::NO_ANIMATION);
    m_pBlendStateAlpha = 0;

    // Fadeクラス実体化
    //fade = new CFade();

    // イージングクラスを実体化
    //easing = new CUiEasing();

    // 当たり判定の実体化
    transform = new CSquea();

    
}


void CUi::Update() {
    // アクティブ/非アクティブ判定
    if (!isActive)
    {
        return;
    }

    this->collider->transform->scale = this->transform->scale;
    this->collider->transform->position = this->transform->position;

    this->collider->transform->scale.y /= 7.5f;

    // フェード管理関数呼び出し
   // FadeManager();

    // 単位ベクトル化する（矢印の長さを１にする）＝正規化
   // XMVECTOR v = XMLoadFloat3(&dir); // ベクトル計算用の型に入れる
   // v = XMVector3Normalize(v); //正規化する
   // XMStoreFloat3(&dir, v); //元の変数dirに結果を戻す

    // ベクトルを使って移動

    // アニメーションの更新処理
    anim->Update();

    CGameObject::Update();
    
}

void CUi::Draw() {
   // // 単位ベクトル化する（矢印の長さを１にする）＝正規化
   // XMVECTOR v = XMLoadFloat3(&dir); // ベクトル計算用の型に入れる
   // v = XMVector3Normalize(v); //正規化する
   // XMStoreFloat3(&dir, v); //元の変数dirに結果を戻す


    CGameObject::Draw();
}

