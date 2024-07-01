#include "CSelectScene.h"
#include "CInput.h"
#include "CSceneManager.h"
#include "CDirectx.h"
#include "CSoundManager.h"
#include "Collision.h"

#include "CCollider.h"


//CSoundManager soundManager;

#define SPEED (0.009f)

CSelectScene::CSelectScene()
{
	// cunter,size,uv,バッファの順
	// 背景のモデル作成
	CreateBackgroundModel(0.0f, 0.0f, 16.0f, 9.0f, 1.0f, 1.0f, VertexBufferBg);
	// セレクト画面の裏のUIのモデル作成
	CreateBackgroundModel(0.0f,0.0f, 7.0f, 7.0f, 1.0f, 1.0f, VertexBufferBs);
	//紫のピースの背景のモデル作成
	CreateBackgroundModel(0.0f, -0.5f, 15.0f, 15.0f, 1.0f, 1.0f, VertexBufferPg);
	// ステージ名のモデル
	CreateBackgroundModel(0.0f, 1.9f, 9.0f, 9.0f, 1.0f, 1.0f, VertexBufferSg);
	// ステージ１のモデル
	CreateBackgroundModel(0.0f, 0.0f, 4.0f, 4.0f, 1.0f, 1.0f, VertexBufferS1g);
	// ステージ2のモデル
	CreateBackgroundModel(0.0f, 0.0f, 4.0f, 4.0f, 1.0f, 1.0f, VertexBufferS2g);
	// ステージ3のモデル
	CreateBackgroundModel(0.0f, 0.0f, 4.0f, 4.0f, 1.0f, 1.0f, VertexBufferS3g);
	// ステージ4のモデル
	CreateBackgroundModel(0.0f, 0.0f, 4.0f, 4.0f, 1.0f, 1.0f, VertexBufferS4g);
	// 1-1のモデル
	CreateBackgroundModel(0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, VertexBufferS1_1);
	// 1-2のモデル
	CreateBackgroundModel(0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, VertexBufferS1_2);
	// 1-3のモデル
	CreateBackgroundModel(0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, VertexBufferS1_3);
	// 1-4のモデル
	CreateBackgroundModel(0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, VertexBufferS1_4);

	// カーソル1のモデル
	CreateBackgroundModel(0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, VertexBufferKg1);
	// ステージフレームのモデル
	CreateBackgroundModel(2.6f, -1.0f, 7.0f, 7.0f, 1.0f, 1.0f, VertexBufferFrame);
	// ステージ１のイメージ画像のモデル
	CreateBackgroundModel(0.0f, 0.0f, 16.0f, 9.0f, 0.5f,1.0f, vertexBufferSS1g);
	// ステージ２のイメージ画像のモデル			   
	CreateBackgroundModel(0.0f, 0.0f, 16.0f, 9.0f, 0.5f,1.0f, vertexBufferSS2g);
	// ステージ３のイメージ画像のモデル			   
	CreateBackgroundModel(0.0f, 0.0f, 16.0f, 9.0f, 0.5f,1.0f, vertexBufferSS3g);
	// ステージ４のイメージ画像のモデル			  
	CreateBackgroundModel(0.0f, 0.0f, 16.0f, 9.0f, 0.5f,1.0f, vertexBufferSS4g);
	// タイトルに戻るのモデル
	CreateBackgroundModel(0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, vertexBufferBTg);

	

	

	

	// テクスチャ読み込み
	CDirectX::Get()->D3D_LoadTexture(L"asset/title/pitapasu_title.png", &textures[TextureBackGround]);
	CDirectX::Get()->D3D_LoadTexture(L"asset/select/Ui_Image_SelectSceneBand.png", &textures[TextureTestBs]);
	CDirectX::Get()->D3D_LoadTexture(L"asset/select/Ui_Text_SelectScene.png", &textures[TextureSelectScene]);
	CDirectX::Get()->D3D_LoadTexture(L"asset/select/Ui_Image_SelectPanel.png", &textures[TexturePurplePiece]);
	CDirectX::Get()->D3D_LoadTexture(L"asset/select/Ui_Image_StageNameBand.png", &textures[TextureStageName]);
	CDirectX::Get()->D3D_LoadTexture(L"asset/select/Ui_Image_StageSelect.png", &textures[TextureStage1]);
	
	CDirectX::Get()->D3D_LoadTexture(L"asset/select/Ui_Text_StageName1-1.png", &textures[TextureName1]);
	CDirectX::Get()->D3D_LoadTexture(L"asset/select/Ui_Text_StageName1-2.png", &textures[TextureName2]);
	CDirectX::Get()->D3D_LoadTexture(L"asset/select/Ui_Text_StageName1-3.png", &textures[TextureName3]);
	CDirectX::Get()->D3D_LoadTexture(L"asset/select/Ui_Text_StageName1-4.png", &textures[TextureName4]);


	CDirectX::Get()->D3D_LoadTexture(L"asset/select/Ui_Text_Stage1-1.png", &textures[Texture1_1]);
	CDirectX::Get()->D3D_LoadTexture(L"asset/select/Ui_Text_Stage1-2.png", &textures[Texture1_2]);
	CDirectX::Get()->D3D_LoadTexture(L"asset/select/Ui_Text_Stage1-3.png", &textures[Texture1_3]);
	CDirectX::Get()->D3D_LoadTexture(L"asset/select/Ui_Text_Stage1-4.png", &textures[Texture1_4]);

	CDirectX::Get()->D3D_LoadTexture(L"asset/select/Ui_Image_StageScreenPreview.png", &textures[TextureFrame]);
	CDirectX::Get()->D3D_LoadTexture(L"asset/stage1/pitapasu_village_far.png", &textures[TextureStageImage1]);
	CDirectX::Get()->D3D_LoadTexture(L"asset/stage2/pitapasu_cave_far.png", &textures[TextureStageImage2]);
	CDirectX::Get()->D3D_LoadTexture(L"asset/stage3/pitapasu_lake_far.png", &textures[TextureStageImage3]);
	CDirectX::Get()->D3D_LoadTexture(L"asset/stage4/pitapasu_forest_far.png", &textures[TextureStageImage4]);
	CDirectX::Get()->D3D_LoadTexture(L"asset/select/Ui_Button_ToTitle.png", &textures[TextureBackTitle]);
	CDirectX::Get()->D3D_LoadTexture(L"asset/UI/Ui_Image_LoadScreen.png", &textures[TextureFade]);
	CDirectX::Get()->D3D_LoadTexture(L"asset/UI/Ui_Image_LoadScreen.png", &textures[TextureFadeBack]);


	CDirectX::Get()->D3D_LoadTexture(L"asset/UI/Ui_Image_MouseCursor.png", &textures[TextureCursor]);

	// オブジェクトの実体化
	//camera = new CCamera();
	backgrounds[Background]  = new CUi(vertexBuffers[VertexBufferBg], textures[TextureBackGround], LayerNum::BACK_GROUND);
	backgrounds[BackSelect]  = new CUi(vertexBuffers[VertexBufferBs], textures[TextureTestBs], LayerNum::BACK_GROUND);
	backgrounds[SelectScene] = new CUi(vertexBuffers[VertexBufferBs], textures[TextureSelectScene], LayerNum::BACK_GROUND);
	backgrounds[PurplePiece] = new CUi(vertexBuffers[VertexBufferPg], textures[TexturePurplePiece], LayerNum::BACK_GROUND);
	backgrounds[StageName]   = new CUi(vertexBuffers[VertexBufferSg], textures[TextureStageName], LayerNum::BACK_GROUND);
	backgrounds[Stage1]      = new CUi(vertexBuffers[VertexBufferS1g], textures[TextureStage1], LayerNum::BACK_GROUND);
	backgrounds[Stage2]		 = new CUi(vertexBuffers[VertexBufferS2g], textures[TextureStage1], LayerNum::BACK_GROUND);
	backgrounds[Stage3]		 = new CUi(vertexBuffers[VertexBufferS3g], textures[TextureStage1], LayerNum::BACK_GROUND);
	backgrounds[Stage4]		 = new CUi(vertexBuffers[VertexBufferS4g], textures[TextureStage1], LayerNum::BACK_GROUND);
	backgrounds[Cursor1]	 = new CUi(vertexBuffers[VertexBufferKg1], textures[TextureCursor], LayerNum::UI);
	backgrounds[Name1]		 = new CUi(vertexBuffers[VertexBufferKg1], textures[TextureName1], LayerNum::BACK_GROUND);
	backgrounds[Name2]		 = new CUi(vertexBuffers[VertexBufferKg1], textures[TextureName2], LayerNum::BACK_GROUND);
	backgrounds[Name3]		 = new CUi(vertexBuffers[VertexBufferKg1], textures[TextureName3], LayerNum::BACK_GROUND);
	backgrounds[Name4]		 = new CUi(vertexBuffers[VertexBufferKg1], textures[TextureName4], LayerNum::BACK_GROUND);
	backgrounds[Frame]		 = new CUi(vertexBuffers[VertexBufferFrame], textures[TextureFrame], LayerNum::BACK_GROUND);
	backgrounds[StageImage1] = new CUi(vertexBuffers[vertexBufferSS1g], textures[TextureStageImage1], LayerNum::BACK_GROUND);
	backgrounds[StageImage2] = new CUi(vertexBuffers[vertexBufferSS2g], textures[TextureStageImage2], LayerNum::BACK_GROUND);
	backgrounds[StageImage3] = new CUi(vertexBuffers[vertexBufferSS3g], textures[TextureStageImage3], LayerNum::BACK_GROUND);
	backgrounds[StageImage4] = new CUi(vertexBuffers[vertexBufferSS4g], textures[TextureStageImage4], LayerNum::BACK_GROUND);

	backgrounds[S1_1]			= new CUi(vertexBuffers[VertexBufferS1_1], textures[Texture1_1], LayerNum::UI);
	backgrounds[S1_2]			= new CUi(vertexBuffers[VertexBufferS1_2], textures[Texture1_2], LayerNum::UI);
	backgrounds[S1_3]			= new CUi(vertexBuffers[VertexBufferS1_3], textures[Texture1_3], LayerNum::UI);
	backgrounds[S1_4]			= new CUi(vertexBuffers[VertexBufferS1_4], textures[Texture1_4], LayerNum::UI);
	backgrounds[BackTitle]		= new CUi(vertexBuffers[vertexBufferBTg], textures[TextureBackTitle], LayerNum::UI);
	backgrounds[BackTitleName]	= new CUi(vertexBuffers[vertexBufferBTg], textures[Texture1_1], LayerNum::UI);
	backgrounds[Fade]			= new CUi(vertexBuffers[VertexBufferBg], textures[TextureFade], LayerNum::UI);
	backgrounds[FadeBack]		= new CUi(vertexBuffers[VertexBufferBg], textures[TextureFadeBack], LayerNum::UI);
	
	drawmanager = new CDrawManager(0);



	backgrounds[BackSelect]->transform->position = { -4.5f,3.7f,1.0f };
	backgrounds[SelectScene]->transform->position = { -4.5f,3.7f,1.0f };

	backgrounds[Cursor1]->transform->position = { 0.0f,3.5f,1.0f };
	backgrounds[Cursor1]->transform->rotate = { 0.0f,0.0f,45.0f };

	backgrounds[S1_1]->transform->position = { -3.5f,0.6f,1.0f };
	backgrounds[S1_1]->transform->scale = { 4.0f,4.0f,1.0f };
	backgrounds[Stage1]->transform->position = { -3.5f,0.6f,1.0f };

	backgrounds[S1_2]->transform->position = { -3.5f,-0.6f,1.0f };
	backgrounds[S1_2]->transform->scale = { 4.0f,4.0f,1.0f };

	backgrounds[Stage2]->transform->position = { -3.5f,-0.6f,1.0f };

	backgrounds[S1_3]->transform->scale = { 4.0f,4.0f,1.0f };
	backgrounds[S1_3]->transform->position = { -3.5f,-1.8f,1.0f };
	backgrounds[Stage3]->transform->position = { -3.5f,-1.8f,1.0f };

	backgrounds[S1_4]->transform->scale = { 4.0f,4.0f,1.0f };
	backgrounds[S1_4]->transform->position = { -3.5f,-3.0f,1.0f };
	backgrounds[Stage4]->transform->position = { -3.5f,-3.0f,1.0f };

	backgrounds[StageImage1]->transform->scale = { 0.35f,0.35f,1.0f };
	backgrounds[StageImage1]->transform->position = { 2.575f,-1.0f,1.0f };
	backgrounds[StageImage2]->transform->scale = { 0.35f,0.35f,1.0f };
	backgrounds[StageImage2]->transform->position = { 2.575f,-1.0f,1.0f };
	backgrounds[StageImage3]->transform->scale = { 0.35f,0.35f,1.0f };
	backgrounds[StageImage3]->transform->position = { 2.575f,-1.0f,1.0f };
	backgrounds[StageImage4]->transform->scale = { 0.35f,0.35f,1.0f };
	backgrounds[StageImage4]->transform->position = { 2.575f,-1.0f,1.0f };


	backgrounds[BackTitleName]->transform->position = { -6.0f,-3.5f,1.0f };
	backgrounds[BackTitleName]->transform->scale = { 5.0f,5.0f,1.0f };
	backgrounds[BackTitle]->transform->position = { -6.0f,-3.9f,1.0f };
	backgrounds[BackTitle]->transform->scale = { 5.0f,5.0f,1.0f };

	backgrounds[Fade]->transform->scale = { 15.0f,20.0f,1.0f };
	backgrounds[FadeBack]->transform->scale = { 16.5f,21.5f,1.0f };

	backgrounds[Name1]->transform->position = { 0.0f,5.9f,1.0f };
	backgrounds[Name1]->transform->scale = { 8.0f,8.0f,1.0f };
	backgrounds[Name2]->transform->position = { 0.0f,5.9f,1.0f };
	backgrounds[Name2]->transform->scale = { 8.0f,8.0f,1.0f };
	backgrounds[Name3]->transform->position = { 0.0f,5.9f,1.0f };
	backgrounds[Name3]->transform->scale = { 8.0f,8.0f,1.0f };
	backgrounds[Name4]->transform->position = { 0.0f,5.9f,1.0f };
	backgrounds[Name4]->transform->scale = { 8.0f,8.0f,1.0f };

	//CSoundManager::GetSound()->XA_Initialize();
	//// BGM再生
	//CSoundManager::GetSound()->XA_Play(SOUND_LABEL_BGM000 , 1.0f);

	drawmanager->AddObject(backgrounds[Background]);
	drawmanager->AddObject(backgrounds[BackSelect]);
	drawmanager->AddObject(backgrounds[SelectScene]);
	drawmanager->AddObject(backgrounds[PurplePiece]);
	drawmanager->AddObject(backgrounds[StageName]);
	drawmanager->AddObject(backgrounds[Stage1]);
	drawmanager->AddObject(backgrounds[Stage2]);
	drawmanager->AddObject(backgrounds[Stage3]);
	drawmanager->AddObject(backgrounds[Stage4]);
	drawmanager->AddObject(backgrounds[Frame]);
	drawmanager->AddObject(backgrounds[StageImage1]);
	drawmanager->AddObject(backgrounds[StageImage2]);
	drawmanager->AddObject(backgrounds[StageImage3]);
	drawmanager->AddObject(backgrounds[StageImage4]);
	drawmanager->AddObject(backgrounds[Name1]);
	drawmanager->AddObject(backgrounds[Name2]);
	drawmanager->AddObject(backgrounds[Name3]);
	drawmanager->AddObject(backgrounds[Name4]);

	drawmanager->AddObject(backgrounds[S1_1]);
	drawmanager->AddObject(backgrounds[S1_2]);
	drawmanager->AddObject(backgrounds[S1_3]);
	drawmanager->AddObject(backgrounds[S1_4]);
	drawmanager->AddObject(backgrounds[BackTitle]);
	drawmanager->AddObject(backgrounds[Cursor1]);
	drawmanager->AddObject(backgrounds[FadeBack]);
	drawmanager->AddObject(backgrounds[Fade]);

	CSoundManager::GetSound()->XA_Play(TITLE_BGM, 0.4f);
	

}

CSelectScene::~CSelectScene()
{
	for (int i = 0; i < NumBackgroundTypes; i++)
	{
		delete backgrounds[i];
	}

	delete drawmanager;

	
}

void CSelectScene::Update()
{
	drawmanager->Update();
	if (fadeflag)
	{
		if (selectedStage != 0)
		{
			backgrounds[Fade]->transform->scale.x -= 0.12f;
			backgrounds[Fade]->transform->scale.y -= 0.16f;
			backgrounds[FadeBack]->transform->scale.x -= 0.12f;
			backgrounds[FadeBack]->transform->scale.y -= 0.16f;
			
			if (backgrounds[Fade]->transform->scale.y <= 0.2f)
			{
				if (selectedStage < 5 && selectedStage  > 0)
				{
					CSoundManager::GetSound()->XA_Stop(TITLE_BGM);
					// 指定したステージへと移動する
					CSceneManager::get()->ChangeStage(static_cast<CSceneManager::StageState>(selectedStage));
					return;
				}
				else if (selectedStage == 5)
				{
					CSoundManager::GetSound()->XA_Stop(TITLE_BGM);
					// タイトルシーンへ戻る
					CSceneManager::get()->fadeflag = false;
					CSceneManager::get()->ChangeScene(CSceneManager::TITLE);
					return;
				}
			}
		}
		else
		{
			fadeflag = false;
		}
	}
	else
	{
		if (CInput::Get()->GetType() == CInput::HIDType::KeyBoardMouse)
		{

			DirectX::XMFLOAT2 pos = CInput::Get()->GetMousePos();

			backgrounds[Cursor1]->transform->position.x = pos.x;
			backgrounds[Cursor1]->transform->position.y = pos.y;
		}
		else
		{
			DirectX::XMFLOAT2 pos = CInput::Get()->GetControllerStick();

			backgrounds[Cursor1]->transform->position.x += (pos.x / 10);
			backgrounds[Cursor1]->transform->position.y += (pos.y / 10);
		}

		// カーソルとUIの当たり判定
		if (DotSquareCollision(&backgrounds[Cursor1]->transform->position, backgrounds[S1_1]->collider->transform))
		{
			selectedStage = 1;
		}
		else if (DotSquareCollision(&backgrounds[Cursor1]->transform->position, backgrounds[S1_2]->collider->transform))
		{
			selectedStage = 2;
		}
		else if (DotSquareCollision(&backgrounds[Cursor1]->transform->position, backgrounds[S1_3]->collider->transform))
		{
			selectedStage = 3;
		}
		else if (DotSquareCollision(&backgrounds[Cursor1]->transform->position, backgrounds[S1_4]->collider->transform))
		{
			selectedStage = 4;
		}
		else if (DotSquareCollision(&backgrounds[Cursor1]->transform->position, backgrounds[BackTitle]->collider->transform))
		{
			selectedStage = 5;
		}
		else
		{
			selectedStage = 0;
		}

		// カーソルとステージのイメージ画像の挙動
		if (selectedStage == 1)
		{
			backgrounds[S1_2]->transform->scale = { 4.0f,4.0f,1.0f };
			backgrounds[S1_3]->transform->scale = { 4.0f,4.0f,1.0f };
			backgrounds[S1_4]->transform->scale = { 4.0f,4.0f,1.0f };
			backgrounds[BackTitle]->transform->scale = { 5.0f,5.0f,1.0f };
			backgrounds[BackTitleName]->transform->scale = { 4.0f,4.0f,1.0f };
			backgrounds[Stage2]->transform->scale = { 1.0f,1.0f,1.0f };
			backgrounds[Stage3]->transform->scale = { 1.0f,1.0f,1.0f };
			backgrounds[Stage4]->transform->scale = { 1.0f,1.0f,1.0f };


			backgrounds[StageImage1]->transform->position = { 2.575f,-1.0f,1.0f };
			backgrounds[StageImage2]->transform->position = { 0.0f,110.0f };
			backgrounds[StageImage3]->transform->position = { 0.0f,110.0f };
			backgrounds[StageImage4]->transform->position = { 0.0f,110.0f };


			backgrounds[Name1]->transform->position = { 0.0f,1.9f,111.0f };
			backgrounds[Name2]->transform->position = { 0.0f,5.9f,111.0f };
			backgrounds[Name3]->transform->position = { 0.0f,5.9f,111.0f };
			backgrounds[Name4]->transform->position = { 0.0f,5.9f,111.0f };

			if (backgrounds[S1_1]->transform->scale.x >= 4.3f)
			{
				scaleflg = false;
			}
			else if (backgrounds[S1_1]->transform->scale.x <= 3.7f)
			{
				scaleflg = true;
			}
			if (scaleflg)
			{
				backgrounds[S1_1]->transform->scale.x += SPEED;
				backgrounds[S1_1]->transform->scale.y += SPEED;
				backgrounds[Stage1]->transform->scale.x += SPEED / 2;
				backgrounds[Stage1]->transform->scale.y += SPEED / 2;
			}
			else
			{
				backgrounds[S1_1]->transform->scale.x -= SPEED;
				backgrounds[S1_1]->transform->scale.y -= SPEED;
				backgrounds[Stage1]->transform->scale.x -= SPEED / 2;
				backgrounds[Stage1]->transform->scale.y -= SPEED / 2;
			}
		}
		if (selectedStage == 2)
		{
			backgrounds[StageImage1]->transform->position = { 0.0f,100.0f };
			backgrounds[StageImage3]->transform->position = { 0.0f,100.0f };
			backgrounds[StageImage2]->transform->position = { 2.575f,-1.0f,1.0f };

			backgrounds[S1_1]->transform->scale = { 4.0f,4.0f,1.0f };
			backgrounds[Stage1]->transform->scale = { 1.0f,1.0f,1.0f };
			backgrounds[S1_3]->transform->scale = { 4.0f,4.0f,1.0f };
			backgrounds[Stage3]->transform->scale = { 1.0f,1.0f,1.0f };
			backgrounds[S1_4]->transform->scale = { 4.0f,4.0f,1.0f };
			backgrounds[Stage4]->transform->scale = { 1.0f,1.0f,1.0f };
			backgrounds[BackTitle]->transform->scale = { 5.0f,5.0f,1.0f };
			backgrounds[BackTitleName]->transform->scale = { 4.0f,4.0f,1.0f };

			backgrounds[Name1]->transform->position = { 0.0f,5.9f,100.0f };
			backgrounds[Name2]->transform->position = { 0.0f,1.9f,100.0f };
			backgrounds[Name3]->transform->position = { 0.0f,5.9f,100.0f };
			backgrounds[Name4]->transform->position = { 0.0f,5.9f,100.0f };

			if (backgrounds[S1_2]->transform->scale.x >= 4.3f)
			{
				scaleflg = false;
			}
			else if (backgrounds[S1_2]->transform->scale.x <= 3.7f)
			{
				scaleflg = true;
			}
			if (scaleflg)
			{
				backgrounds[S1_2]->transform->scale.x += SPEED;
				backgrounds[S1_2]->transform->scale.y += SPEED;
				backgrounds[Stage2]->transform->scale.x += SPEED;
				backgrounds[Stage2]->transform->scale.y += SPEED;
			}
			else
			{
				backgrounds[S1_2]->transform->scale.x -= SPEED;
				backgrounds[S1_2]->transform->scale.y -= SPEED;
				backgrounds[Stage2]->transform->scale.x -= SPEED;
				backgrounds[Stage2]->transform->scale.y -= SPEED;
			}
		}
		if (selectedStage == 3)
		{
			backgrounds[StageImage1]->transform->position = { 0.0f,110.0f };
			backgrounds[StageImage2]->transform->position = { 0.0f,110.0f };
			backgrounds[StageImage4]->transform->position = { 0.0f,110.0f };
			backgrounds[StageImage3]->transform->position = { 2.575f,-1.0f,0.0f };

			backgrounds[S1_1]->transform->scale = { 4.0f,4.0f,1.0f };
			backgrounds[Stage1]->transform->scale = { 1.0f,1.0f,1.0f };
			backgrounds[S1_2]->transform->scale = { 4.0f,4.0f,1.0f };
			backgrounds[Stage2]->transform->scale = { 1.0f,1.0f,1.0f };
			backgrounds[S1_4]->transform->scale = { 4.0f,4.0f,1.0f };
			backgrounds[Stage4]->transform->scale = { 1.0f,1.0f,1.0f };
			backgrounds[BackTitle]->transform->scale = { 5.0f,5.0f,1.0f };
			backgrounds[BackTitleName]->transform->scale = { 4.0f,4.0f,1.0f };

			backgrounds[Name1]->transform->position = { 0.0f,5.9f,100.0f };
			backgrounds[Name2]->transform->position = { 0.0f,5.9f,100.0f };
			backgrounds[Name3]->transform->position = { 0.0f,1.9f,100.0f };
			backgrounds[Name4]->transform->position = { 0.0f,5.9f,100.0f };

			if (backgrounds[S1_3]->transform->scale.x >= 4.3f)
			{
				scaleflg = false;
			}
			else if (backgrounds[S1_3]->transform->scale.x <= 3.7f)
			{
				scaleflg = true;
			}
			if (scaleflg)
			{
				backgrounds[S1_3]->transform->scale.x += SPEED;
				backgrounds[S1_3]->transform->scale.y += SPEED;
				backgrounds[Stage3]->transform->scale.x += SPEED;
				backgrounds[Stage3]->transform->scale.y += SPEED;
			}
			else
			{
				backgrounds[S1_3]->transform->scale.x -= SPEED;
				backgrounds[S1_3]->transform->scale.y -= SPEED;
				backgrounds[Stage3]->transform->scale.x -= SPEED;
				backgrounds[Stage3]->transform->scale.y -= SPEED;
			}
		}
		if (selectedStage == 4)
		{
			backgrounds[S1_1]->transform->scale = { 4.0f,4.0f,1.0f };
			backgrounds[Stage1]->transform->scale = { 1.0f,1.0f,1.0f };
			backgrounds[S1_3]->transform->scale = { 4.0f,4.0f,1.0f };
			backgrounds[Stage3]->transform->scale = { 1.0f,1.0f,1.0f };
			backgrounds[S1_2]->transform->scale = { 4.0f,4.0f,1.0f };
			backgrounds[Stage2]->transform->scale = { 1.0f,1.0f,1.0f };
			backgrounds[BackTitle]->transform->scale = { 5.0f,5.0f,1.0f };
			backgrounds[BackTitleName]->transform->scale = { 4.0f,4.0f,1.0f };

			backgrounds[StageImage1]->transform->position = { 0.0f,110.0f };
			backgrounds[StageImage2]->transform->position = { 0.0f,110.0f };
			backgrounds[StageImage3]->transform->position = { 0.0f,110.0f };
			backgrounds[StageImage4]->transform->position = { 2.575f,-1.0f,0.0f };

			backgrounds[Name1]->transform->position = { 0.0f,5.9f,100.0f };
			backgrounds[Name2]->transform->position = { 0.0f,5.9f,100.0f };
			backgrounds[Name3]->transform->position = { 0.0f,5.9f,100.0f };
			backgrounds[Name4]->transform->position = { 0.0f,1.9f,100.0f };



			if (backgrounds[S1_4]->transform->scale.x >= 4.3f)
			{
				scaleflg = false;
			}
			else if (backgrounds[S1_4]->transform->scale.x <= 3.7f)
			{
				scaleflg = true;
			}
			if (scaleflg)
			{
				backgrounds[S1_4]->transform->scale.x += SPEED;
				backgrounds[S1_4]->transform->scale.y += SPEED;
				backgrounds[Stage4]->transform->scale.x += SPEED;
				backgrounds[Stage4]->transform->scale.y += SPEED;
			}
			else
			{
				backgrounds[S1_4]->transform->scale.x -= SPEED;
				backgrounds[S1_4]->transform->scale.y -= SPEED;
				backgrounds[Stage4]->transform->scale.x -= SPEED;
				backgrounds[Stage4]->transform->scale.y -= SPEED;
			}
		}
		if (selectedStage == 5)
		{
			backgrounds[S1_1]->transform->scale = { 4.0f,4.0f,1.0f };
			backgrounds[Stage1]->transform->scale = { 1.0f,1.0f,1.0f };
			backgrounds[S1_2]->transform->scale = { 4.0f,4.0f,1.0f };
			backgrounds[Stage2]->transform->scale = { 1.0f,1.0f,1.0f };
			backgrounds[S1_3]->transform->scale = { 4.0f,4.0f,1.0f };
			backgrounds[Stage3]->transform->scale = { 1.0f,1.0f,1.0f };
			backgrounds[S1_4]->transform->scale = { 4.0f,4.0f,1.0f };
			backgrounds[Stage4]->transform->scale = { 1.0f,1.0f,1.0f };

			if (backgrounds[BackTitle]->transform->scale.x >= 5.3f)
			{
				scaleflg = false;
			}
			else if (backgrounds[BackTitle]->transform->scale.x <= 4.7f)
			{
				scaleflg = true;
			}
			if (scaleflg)
			{
				backgrounds[BackTitle]->transform->scale.x += SPEED;
				backgrounds[BackTitle]->transform->scale.y += SPEED;
				backgrounds[BackTitleName]->transform->scale.x += SPEED;
				backgrounds[BackTitleName]->transform->scale.y += SPEED;
			}
			else
			{
				backgrounds[BackTitle]->transform->scale.x -= SPEED;
				backgrounds[BackTitle]->transform->scale.y -= SPEED;
				backgrounds[BackTitleName]->transform->scale.x -= SPEED;
				backgrounds[BackTitleName]->transform->scale.y -= SPEED;
			}

		}
		if (selectedStage == 0)
		{
			backgrounds[S1_1]->transform->scale = { 4.0f,4.0f,1.0f };
			backgrounds[S1_2]->transform->scale = { 4.0f,4.0f,1.0f };
			backgrounds[S1_3]->transform->scale = { 4.0f,4.0f,1.0f };
			backgrounds[S1_4]->transform->scale = { 4.0f,4.0f,1.0f };
			backgrounds[BackTitle]->transform->scale = { 5.0f,5.0f,1.0f };
			backgrounds[BackTitleName]->transform->scale = { 4.0f,4.0f,1.0f };
			backgrounds[Stage1]->transform->scale = { 1.0f,1.0f,1.0f };
			backgrounds[Stage2]->transform->scale = { 1.0f,1.0f,1.0f };
			backgrounds[Stage3]->transform->scale = { 1.0f,1.0f,1.0f };
			backgrounds[Stage4]->transform->scale = { 1.0f,1.0f,1.0f };


			backgrounds[StageImage1]->transform->position = { 0.0f,110.0f };
			backgrounds[StageImage2]->transform->position = { 0.0f,110.0f };
			backgrounds[StageImage3]->transform->position = { 0.0f,110.0f };
			backgrounds[StageImage4]->transform->position = { 0.0f,110.0f };


			backgrounds[Name1]->transform->position = { 0.0f,5.9f,1.0f };
			backgrounds[Name2]->transform->position = { 0.0f,5.9f,1.0f };
			backgrounds[Name3]->transform->position = { 0.0f,5.9f,1.0f };
			backgrounds[Name4]->transform->position = { 0.0f,5.9f,1.0f };
		}

		if (CInput::Get()->GetType() == CInput::HIDType::KeyBoardMouse)
		{
			if (CInput::Get()->isMouseTrigger(CInput::InputType::LB1))
			{
				CSoundManager::GetSound()->XA_Play(CLICK, 0.5f);
				CInput::Get()->GetType();
				fadeflag = true;
			}
		}
		else
		{
			// ステージ選択完了処理
			if (CInput::Get()->isKeyTrigger(CInput::InputType::A) && !fadeflag) // Aボタンが押されたら
			{
				CSoundManager::GetSound()->XA_Play(CLICK, 0.5f);
				CInput::Get()->GetType();
				fadeflag = true;
			}
		}
	}
}



 

void CSelectScene::Draw()
{
	drawmanager->Draw();
}
