#include "CGameObject.h"

#include "CDirectx.h"
#include "CGame.h"
//#include "CCamera.h"

using namespace DirectX;

#include "CSceneManager.h"
#include "CCollider.h"

CGameObject::CGameObject(ID3D11Buffer* vb, ID3D11ShaderResourceView* tex,int num)
{
	// バッファとテクスチャを保存しておく
	vertexBuffer = vb;
	texture = tex;
	DrawNum = static_cast<LayerNum>(num);
	// 座標保存クラスを実体化する
	transform = new CSquea();
	// アニメーションクラスを実体化する
	anim = new CAnimation(1,1);
	// アニメーションの最初の設定を何もなしにする
	anim->SetPattern(CAnimation::NO_ANIMATION);

}

CGameObject::~CGameObject()
{
	delete transform;
}

void CGameObject::Update()
{
	//if (!this->isDraw) return;
	this->transform->VertexPos();
	anim->Update();
}

void CGameObject::Draw()
{
	if (!this->isDraw) return;
	// DirectXの変数の構造体を取得する
	CDirectX::Direct d3d = CDirectX::Get()->GetDirect();

	XMMATRIX matrixView;

	//matrixView = CGame::Get()->GetCamera()->GetViewMatrix();

	//matrixView = CSceneManager::Get()->GetCamera()->GetViewMatrix();

	// View変換行列の作成　＝　カメラ用の行列
	XMVECTOR eye = XMVectorSet( 0,0, 0, 0);  // 視点の位置
	XMVECTOR focus = XMVectorSet( 0, 0, 5, 0);  // 見ている位置
	XMVECTOR up = XMVectorSet(0, 1, 0, 0);  // カメラの上方向
	 matrixView = XMMatrixLookAtLH(eye, focus, up);
	ConstBuffer cb;

	// 平行投影の行列作成
	// 引数①②：映し出す面の横縦の長さ
	// 引数③④：映し出す空間の奥行（手前と最奥）
	float scaleScreen = 1.0f;
	cb.matrixProj = XMMatrixOrthographicLH(16.0f * scaleScreen, 9.0f * scaleScreen, 0.001f, 5.0f);
	cb.matrixProj = XMMatrixTranspose(matrixView * cb.matrixProj);// カメラ×投影

	//// ワールド変換行列の作成
	//// 移動行列
	//XMMATRIX matrixMove = XMMatrixTranslation(position.x, position.y, position.z);
	//// 拡大縮小行列
	//XMMATRIX matrixScale = XMMatrixScaling(scaling.x, scaling.y, scaling.z);
	//// 回転行列　XMMatrixRotationZ関数
	//XMMATRIX matrixRotateX = XMMatrixRotationX(XMConvertToRadians(rotation.x));
	//XMMATRIX matrixRotateY = XMMatrixRotationY(XMConvertToRadians(rotation.y));
	//XMMATRIX matrixRotateZ = XMMatrixRotationZ(XMConvertToRadians(rotation.z));
	//// 各回転行列
	//XMMATRIX matrixRotate = matrixRotateX * matrixRotateY * matrixRotateZ;

	//matrixWorld = matrixScale * matrixRotate * matrixMove;


	// 行列は掛け算で合成できる （注）掛ける順番が影響する
	//cb.matrixWorld = matrixScale * matrixRotate * matrixMove;
	//cb.matrixWorld = XMMatrixTranspose(cb.matrixWorld);

	// 移動行列
	XMMATRIX matrixMove = XMMatrixTranslation(
		this->transform->position.x, 
		this->transform->position.y, 
		this->transform->position.z);

	// 拡大縮小行列
	XMMATRIX matrixScale = XMMatrixScaling(
		this->transform->scale.x,
		this->transform->scale.y,
		this->transform->scale.z);

	// 回転行列
	XMMATRIX matrixRotateX = XMMatrixRotationX(XMConvertToRadians(this->transform->rotate.x));
	XMMATRIX matrixRotateY = XMMatrixRotationY(XMConvertToRadians(this->transform->rotate.y));
	XMMATRIX matrixRotateZ = XMMatrixRotationZ(XMConvertToRadians(this->transform->rotate.z));

	// 回転行列を一つにまとめる
	XMMATRIX matrixRotate = matrixRotateX * matrixRotateY * matrixRotateZ;

	// 行列を一つにまとめる
	cb.matrixWorld = matrixScale * matrixRotate * matrixMove;
	//cb.matrixWorld = matrixScale  * matrixMove * matrixRotate;
	// 行列をシェーダーに送る
	cb.matrixWorld = XMMatrixTranspose(cb.matrixWorld);

	// UVアニメーションの行列作成
	// XMMatrixTranslation＝移動行列を作る関数
	cb.matrixTex = XMMatrixTranslation(anim->GetUV().x, anim->GetUV().y, 0.0f);
	// XMMatrixTranspose＝転置行列を作る
	cb.matrixTex = XMMatrixTranspose(cb.matrixTex);

	// マテリアル色を定数バッファデータにセット
	cb.materialDiffuse = materialDiffuse;

	// 行列をシェーダーに渡す
	d3d.m_deviceContext->UpdateSubresource(d3d.m_ContextBuffer, 0, NULL, &cb, 0, 0);

	// VertexBufferを指定する
	d3d.m_deviceContext->IASetVertexBuffers(0, 1, &vertexBuffer, &strides, &offset);
	// ピクセルシェーダーにテクスチャを渡す
	d3d.m_deviceContext->PSSetShaderResources(0, 1, &texture);
	// サンプラーをピクセルシェーダーに渡す
	//d3d.m_deviceContext->PSSetSamplers(0, 1, &d3d.m_Smapler);
	// 第１引数　→　描画する頂点数
	d3d.m_deviceContext->Draw(vertexNum, 0); // 描画命令
}

bool CGameObject::isCheckObject(const CGameObject* other) const
{
	//// 左右の当たっているかどうかを判定する
	//bool pos_x = this->transform->Right+0.2f >= other->transform->Left &&
	//	this->transform->Left-0.2f <= other->transform->Right;

	//// 上下の当たっているかどうかを判定する
	//bool pos_y = this->transform->Top+0.3f >= other->transform->Top &&
	//	this->transform->Bottom-0.3f <= other->transform->Bottom;

	// 左右の当たっているかどうかを判定する
	bool pos_x = this->transform->Left <= other->transform->Left &&
		this->transform->Right >= other->transform->Right;

	// 上下の当たっているかどうかを判定する
	bool pos_y = this->transform->Top + 0.2f >= other->transform->Top &&
		this->transform->Bottom - 0.2f <= other->transform->Bottom;

	return pos_x && pos_y;
}

const int CGameObject::GetLayer() const
{
	return static_cast<int>(DrawNum);
}
