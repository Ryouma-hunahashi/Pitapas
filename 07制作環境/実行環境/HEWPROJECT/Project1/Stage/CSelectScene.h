#pragma once

#include "CScene.h"
#include "CBackGround.h"
#include "CDrawManager.h"
#include "CDirectX.h"
#include "CUi.h"
struct Vector2 {
	float x, y;

	Vector2(float _x, float _y) : x(_x), y(_y) {}
};

class VertexBuffer {
public:
	// 頂点バッファに関連するメソッドやデータを定義する

	VertexBuffer() {}
	~VertexBuffer() {}
};

class IDirectX {
public:
	virtual void D3D_CreateSquare(const Vector2& center, const Vector2& size, const Vector2& uv, VertexBuffer* pVertexBuffer) = 0;

	virtual ~IDirectX() {} // 仮想デストラクタ
};

class CSelectScene : public CScene
{

public:
	
	float cursorY = 0.0f;
	CSelectScene();
	~CSelectScene();

void CreateBackgroundModel(float centerX, float centerY, float width, float height, float uvX, float uvY, int bufferIndex)
{
	CDirectX::FLOAT_XY centerFloatXY = { centerX, centerY };
	CDirectX::FLOAT_XY sizeFloatXY = { width, height };
	CDirectX::FLOAT_XY uvFloatXY = { uvX, uvY };

	CDirectX::Get()->D3D_CreateSquare(centerFloatXY, sizeFloatXY, uvFloatXY, &vertexBuffers[bufferIndex]);
};
private:

	//CCamera* camera;

	enum BufferType 
	{
		VertexBufferBg,			// 全画面で表示する時に使用するバッファ
		VertexBufferBs,			// セレクト画面の文字に使用するバッファ
		VertexBufferPg,			// 紫のピースの背景に使用するバッファ
		VertexBufferSg,			// 紫のピースの背景に使用するバッファ
		VertexBufferS1g,		// ステージ選択に使用するバッファ
		VertexBufferS2g,		// ステージ選択に使用するバッファ
		VertexBufferS3g,		// ステージ選択に使用するバッファ
		VertexBufferS4g,		// ステージ選択に使用するバッファ
		VertexBufferKg1,		// カーソル1画像に使用するバッファ
		VertexBufferS1_1,		// 1-1バッファ
		VertexBufferS1_2,		// 1-2バッファ
		VertexBufferS1_3,		// 1-3バッファ
		VertexBufferS1_4,		// 1-4バッファ
		VertexBufferFrame,		// ステージフレームのバッファ
		vertexBufferSS1g,		// ステージ選択に使用するバッファ
		vertexBufferSS2g,		// ステージ選択に使用するバッファ
		vertexBufferSS3g,		// ステージ選択に使用するバッファ
		vertexBufferSS4g,		// ステージ選択に使用するバッファ
		vertexBufferBTg,		// タイトルに戻る時に使用するバッファ
		NumBufferTypes			// バッファの数を自動的に計算するための追加の要素
	};

	ID3D11Buffer* vertexBuffers[NumBufferTypes];

	enum TextureType 
	{
		TextureBackGround,		// 全画面で表示する時に使用するテクスチャ
		TextureTestBs,			// セレクト画面の文字に使用するテクスチャ
		TextureSelectScene,	// 紫のピースの背景に使用するテクスチャ
		TexturePurplePiece,		// 紫のピースの背景に使用するテクスチャ
		TextureStageName,		// ステージ選択に使用するテクスチャ
		TextureStage1,			// ステージ選択に使用するテクスチャ
		TextureStage2,			// ステージ選択に使用するテクスチャ
		TextureStage3,			// ステージ選択に使用するテクスチャ
		TextureStage4,			// ステージ選択に使用するテクスチャ
		TextureCursor,			// カーソル1画像に使用するテクスチャ
		TextureName1,			// ステージ名１
		TextureName2,			// ステージ名２
		TextureName3,			// ステージ名３
		TextureName4,			// ステージ名４
		Texture1_1,				// 1-1テクスチャ
		Texture1_2,				// 1-2テクスチャ
		Texture1_3,				// 1-3テクスチャ
		Texture1_4,				// 1-4テクスチャ
		TextureFrame,			// ステージフレームのテクスチャ
		TextureStageImage1,		// ステージ選択に使用するテクスチャ
		TextureStageImage2,		// ステージ選択に使用するテクスチャ
		TextureStageImage3,		// ステージ選択に使用するテクスチャ
		TextureStageImage4,		// ステージ選択に使用するテクスチャ
		TextureBackTitle,		// タイトルに戻るときに使用するテクスチャ
		TextureFade,
		TextureFadeBack,
		
		NumTextureTypes,			// バッファの数を自動的に計算するための追加の要素


	};

	ID3D11ShaderResourceView* textures[NumTextureTypes] = { nullptr };

public:
	CDrawManager* drawmanager;
	enum BackgroundType 
	{
		Background,
		BackSelect,
		SelectScene,
		PurplePiece,
		StageName,
		Stage1,
		Stage2,
		Stage3,
		Stage4,
		Cursor1,
		Name1,
		Name2,
		Name3,
		Name4,
		S1_1,
		S1_2,
		S1_3,
		S1_4,
		Frame,

		StageImage1,
		StageImage2,
		StageImage3,
		StageImage4,
		BackTitle,
		BackTitleName,
		Fade,
		FadeBack,
		NumBackgroundTypes
	};

	CUi* backgrounds[NumBackgroundTypes] = { nullptr };


	void Update();
	void Draw();

	// ステージの最大数を設定 ※タイトルに戻る時の個数も含めること
	const int totalStages = 5;
	// 選択されているステージの数
	int selectedStage = 1;

	bool scaleflg = false;

	bool fadeflag = false;

	static CSelectScene* getSelect() { static CSelectScene* instance; return instance; }
	
	//CCamera* GetCamera() { return camera; }
};

