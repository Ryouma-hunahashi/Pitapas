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
	// 描画に使用する頂点バッファ
	ID3D11Buffer* vertexBuffer;
	// 描画に使用するテクスチャ
	ID3D11ShaderResourceView* texture;


	// 現在の向きを表すベクトル変数
	DirectX::XMFLOAT3 dir = { 0, 0, 0 };

	// アルファブレンド用
	ID3D11BlendState* m_pBlendStateAlpha;

	// イージングクラスオブジェクト
	//CUiEasing* easing;


	// 暫定
	int frame = 0;

private:

	//CFade*  fade;
	//
	//CFade::FADE_STATE  fadeState = CFade::NO_FADE; // 現在のフェード状態

public:
	// 仮想世界の中の位置座標
	CFloat3 pos = { 0, 0, 0 };

	// デフォルトの位置座標
	//const DirectX::XMFLOAT3 DEFAULT_POS;

	// 拡大縮小率を持つ変数
	DirectX::XMFLOAT3 scale = { 1.0f, 1.0f, 1.0f };
	// 回転角度
	float angle = 0.0f;

	// このキャラクターに適用するマテリアル色
	//DirectX::XMFLOAT4 materialDiffuse = { 1,1,1,1 };

	// アクティブ/非アクティブ切り替え変数
	bool isActive = true;


public:
	// メンバー関数
	// データの初期化処理
	void InitializeData();

	// 初期化処理（コンストラクタ）
	// 引数：使用する頂点バッファとテクスチャを渡す
	CUi(ID3D11Buffer* vb, ID3D11ShaderResourceView* tex, int num);

	// 終了処理（デストラクタ）
	~CUi() override{};


	// 更新処理
	void Update();
	// 描画処理
	void Draw();



	// アニメーション再生速度を設定する関数
	void SetAnimationSpeed(float speed);

	// アニメーションパターンを設定する関数
	void SetAnimationPattern(int pattern);

	// フェード状態
	//void SetFadeState(CFade::FADE_STATE _fadeState);

	// 各機能マネージャー
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

