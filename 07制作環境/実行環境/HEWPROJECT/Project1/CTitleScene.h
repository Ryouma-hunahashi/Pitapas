#pragma once

#include "CScene.h"
#include "CUi.h"
#include "CBackGround.h"
#include "CPlayer.h"
#include "CDrawManager.h"
#include "Collision.h"

// タイトル用シーン
class CTitleScene : public CScene
{
private:

	// 背景用バッファ
	ID3D11Buffer* vertexBufferUi;
	ID3D11Buffer* vertexBufferBg;

	/* タイトルシーンで用いるテクスチャ */
	ID3D11ShaderResourceView* textureBackGround= NULL;
	ID3D11ShaderResourceView* textureTitleLogo = NULL;
	ID3D11ShaderResourceView* textureStartUi = NULL;
	ID3D11ShaderResourceView* textureEndUi = NULL;
	ID3D11ShaderResourceView* textureBackText = NULL;
	ID3D11ShaderResourceView* textureExit = NULL;
	ID3D11ShaderResourceView* textureStart = NULL;
	ID3D11ShaderResourceView* textureCursor = NULL;

	
	// 各オブジェクト変数宣言
	CBackGround* backGround;	// 背景
	//CGameObject* uiStartLogo;
	CGameObject* uiEndLogo;
	CGameObject* titleLogo;

	CUi* uiStartLogo;
	CUi* uistart;
	CUi* uiexit;
	CUi* uibackLogo[2];
	CUi* uicursor;
	

	CDrawManager* drawmanager;
	//CCamera* camera;

public:
	// コンストラクタ・デストラクタ
	CTitleScene();
	~CTitleScene();

	void Update();
	void Draw();



	bool test;

	bool isStart = false;

	bool isGameStart = false;
	bool isGameEnd = false;

	bool nextSceneSet = false;
};

