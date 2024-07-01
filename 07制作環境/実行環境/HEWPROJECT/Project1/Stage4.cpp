#include "Stage4.h"
#include "CInput.h"
#include "CSceneManager.h"
#include "CSoundManager.h"


#define TEST_MOVE (2.0f)
#define TEST_MATRIX (1.5f)
#define OBJECT_X ((1.0f/16))
#define OBJECT_Y ((1.0f/9))


Stage4::Stage4()
{
	// モデル作成
	{
		// 背景のモデル作成
		center = { 0.0f, 0.0f };
		size = { 16.0f,9.0f };
		uv = { 1.0f, 1.0f };
		CDirectX::Get()->D3D_CreateSquare(center, size, uv, &vertexBufferBg);

		// プレイヤー用（アニメーションする時に用いる）
		center = { 0.0f, 0.0f };
		size = { 1.0f,1.0f };
		uv = { 0.33f, 0.33f };
		CDirectX::Get()->D3D_CreateSquare(center, size, uv, &vertexBufferCharacter);

		center = { 0.0f, 0.0f };
		size = { 2.4f, 2.4f };
		uv = { (1.0f / 9), (1.0f / 6) };
		CDirectX::Get()->D3D_CreateSquare(center, size, uv, &vertexBufferEffect);

		uv = { 1.0f / 5,1.0f / 7 };
		CDirectX::Get()->D3D_CreateSquare(center, size, uv, &vertexBufferPieceEffect);

		// 1ピースサイズ用 ※ゲームオブジェクト等は全部これ　背景は除く
		center = { 0.0f, 0.0f };
		size = { 1.0f,1.0f };
		uv = { 1.0f, 1.0f };

		CDirectX::Get()->D3D_CreateSquare(center, size, uv, &vertexBufferPiece);
	}

	// テクスチャ読み込み
	{
		CDirectX::Get()->D3D_LoadTexture(L"asset/Ui_Image_PieceGrid_Ver4.png", &texturePazlePiece);			// 背景用パズルピーステクスチャ
		CDirectX::Get()->D3D_LoadTexture(L"asset/stage4/pitapasu_forest_far.png", &textureBackGround);		// 背景テクスチャ（後景）
		CDirectX::Get()->D3D_LoadTexture(L"asset/stage4/pitapasu_forest_close.png", &textureBackfrontGround);	// 背景テクスチャ(前景)
		CDirectX::Get()->D3D_LoadTexture(L"asset/stage4/pitapasu_forest_ground01.png", &textureFloor);		// 地面テクスチャ
		CDirectX::Get()->D3D_LoadTexture(L"asset/stage4/pitapasu_forest_ground02.png", &textureFloormiddle);		// 地面テクスチャ
		CDirectX::Get()->D3D_LoadTexture(L"asset/stage4/pitapasu_forest_ground04.png", &textureFloortop);		// 地面テクスチャ
		CDirectX::Get()->D3D_LoadTexture(L"asset/player/pitapasu_sprite_Walk.png", &texturePlayer);				// プレイヤーテクスチャ
		CDirectX::Get()->D3D_LoadTexture(L"asset/player/pitapasu_sprite_stay.png", (&texturePlayer_stay));
		CDirectX::Get()->D3D_LoadTexture(L"asset/player/pitapasu_sprite_jump.png", (&texturePlayer_jump));
		CDirectX::Get()->D3D_LoadTexture(L"asset/player/pitapasu_sprite_down.png", &texturePlayerDead);		// プレイヤー（死亡）
		CDirectX::Get()->D3D_LoadTexture(L"asset/UI/Ui_Image_PeacePreview02.png", &textureUiPiece);			// ゲーム用UIプレビューテクスチャ
		CDirectX::Get()->D3D_LoadTexture(L"asset/UI/Ui_Image_Peace.png", &textureUiOnePiece);				// １ピース画像のテクスチャ（UIに使用）
		CDirectX::Get()->D3D_LoadTexture(L"asset/gimick/wood box.png", &textureWoodBox);							// ギミック木箱1マス
		CDirectX::Get()->D3D_LoadTexture(L"asset/gimick/half wood box.png", &texturehalfWoodBox);					// ギミック木箱0.5マス
		CDirectX::Get()->D3D_LoadTexture(L"asset/effect/pita_goal.png", &textureEffect);					// エフェクト
		CDirectX::Get()->D3D_LoadTexture(L"asset/effect/pita_effect.png", &textureEffectPanel);					// エフェクト
		CDirectX::Get()->D3D_LoadTexture(L"asset/UI/Ui_Image_PeaceCursor.png", &textureUiCursor);			// Uiカーソル
		CDirectX::Get()->D3D_LoadTexture(L"asset/goal_piece.png", &textureGoal);							// ゴール用テクスチャ
		CDirectX::Get()->D3D_LoadTexture(L"asset/UI/Ui_Image_LoadScreen.png", &texturefade);							// ゴール用テクスチャ
		CDirectX::Get()->D3D_LoadTexture(L"asset/UI/Ui_Image_MouseCursor.png", &textureMouseCursor);							// ゴール用テクスチャ

		// ポーズ用
		CDirectX::Get()->D3D_LoadTexture(L"asset/pause/Ui_Image_PauseBackGround.png", &texturePauseBack);
		CDirectX::Get()->D3D_LoadTexture(L"asset/pause/Ui_Image_PauseButtonBand.png", &texturePauseButtonBand);
		CDirectX::Get()->D3D_LoadTexture(L"asset/pause/Ui_Text_Pause.png", &texturePauseScene);
		CDirectX::Get()->D3D_LoadTexture(L"asset/pause/Ui_Text_PauseButtonContinue.png", &texturePauseButtonContinue);
		CDirectX::Get()->D3D_LoadTexture(L"asset/pause/Ui_Text_PauseButtonRetry.png", &texturePauseButtonRetry);
		CDirectX::Get()->D3D_LoadTexture(L"asset/pause/Ui_Text_PauseButtonReturn.png", &texturePauseButtonReturn);
		CDirectX::Get()->D3D_LoadTexture(L"asset/select/Ui_Text_StageName1-4.png", &texturePauseStageName);
		CDirectX::Get()->D3D_LoadTexture(L"asset/select/Ui_Image_SelectSceneBand.png", &texturePauseSceneBand);

		// リザルト用
		CDirectX::Get()->D3D_LoadTexture(L"asset/result/Ui_Image_BlackBackGround.png", &textureBlackBackGround);	// 黒背景
		CDirectX::Get()->D3D_LoadTexture(L"asset/result/Ui_Text_ClearText.png", &textureClearText);				// テキスト：クリア
		CDirectX::Get()->D3D_LoadTexture(L"asset/result/Ui_Image_ResultPanel .png", &textureResultPanel);			// リザルトパネル
		CDirectX::Get()->D3D_LoadTexture(L"asset/select/Ui_Image_SelectSceneBand.png", &textureSceneBand);		// シーンバンド
		CDirectX::Get()->D3D_LoadTexture(L"asset/select/Ui_Image_StageNameBand.png", &textureStageNameBand);		// ステージバンド
		CDirectX::Get()->D3D_LoadTexture(L"asset/result/Ui_Image_ResultButtonBand.png", &textureButton);			// リザルトボタン
		CDirectX::Get()->D3D_LoadTexture(L"asset/result/Ui_Text_SceneResult.png", &textureResultText);			// テキスト：けっか
		CDirectX::Get()->D3D_LoadTexture(L"asset/result/Ui_Text_Next.png", &textureNext);							// テキスト：つぎへ
		CDirectX::Get()->D3D_LoadTexture(L"asset/result/Ui_Text_Retry.png", &textureRetry);						// テキスト：もういちど
		CDirectX::Get()->D3D_LoadTexture(L"asset/result/Ui_Text_Return.png", &textureReturn);						// テキスト：もどる
		CDirectX::Get()->D3D_LoadTexture(L"asset/result/Ui_Text_GameOverText.png", &textureOut);						// テキスト：もどる
	}
	// オブジェクトの実体化
	{
		background = new CBackGround(vertexBufferBg, textureBackGround, LayerNum::BACK_GROUND);			// 背景（後景）
		frontground = new CBackGround(vertexBufferBg, textureBackfrontGround, LayerNum::FORE_GROUND);	// 背景（前景）
		pazle[0] = new CBackGround(vertexBufferBg, texturePazlePiece, LayerNum::MIDDLE_GROUND_BACK);		// パズル背景
		pazle[1] = new CBackGround(vertexBufferBg, texturePazlePiece, LayerNum::MIDDLE_GROUND_BACK);		// パズル背景
		player = new CPlayer(vertexBufferCharacter, texturePlayer, LayerNum::PLAY_GROUND_BACK);			// プレイヤー
		woodbox[0] = new CWoodBox(vertexBufferPiece, textureWoodBox, LayerNum::PLAY_GROUND);				// 木箱
		woodbox[1] = new CWoodBox(vertexBufferPiece, textureWoodBox, LayerNum::PLAY_GROUND);				// 木箱
		uipiecestock = new CUi(vertexBufferPiece, textureUiPiece, LayerNum::FORE_GROUND);				// UI
		uionepiece = new CUi(vertexBufferPiece, textureUiCursor, LayerNum::PLAY_GROUND_FRONT);			// テスト用　現在のマウスカーソルを見る用オブジェクト
		previewpiece = new CGameObject(vertexBufferPiece, textureUiOnePiece, LayerNum::BLACK_OUT);		// UIの所のピース
		for (int i = 0; i < PIECE_Y; i++)
		{
			for (int j = 0; j < PIECE_X; j++)
			{
				piece_array[i][j] = new CPiece(vertexBufferPiece, textureUiOnePiece, LayerNum::BLACK_OUT);// 各ピースの配列
			}
		}
		for (int i = 0; i < 11; i++)
		{
			floor[i] = new CFloor(vertexBufferPiece, textureFloor, LayerNum::PLAY_GROUND_FRONT);				// 地面
		}
		work = new CGameObject(NULL, NULL, NULL);	// 入れ替える用の中身に何もないオブジェクト
		uiDrawPiece = new CGameObject(vertexBufferPiece, textureUiOnePiece, LayerNum::UI);					// エフェクト
		halfwoodbox[0] = new CWoodBox(vertexBufferPiece, texturehalfWoodBox, LayerNum::PLAY_GROUND);		// 半分サイズの木箱
		halfwoodbox[1] = new CWoodBox(vertexBufferPiece, texturehalfWoodBox, LayerNum::PLAY_GROUND);		// 半分サイズの木箱
		goal = new CGoal(vertexBufferPiece, textureGoal, LayerNum::PLAY_GROUND);						// ゴール
		goaleffect = new CGameObject(vertexBufferEffect, textureEffect, LayerNum::PLAY_GROUND_BACK);
		Pieceeffect = new CGameObject(vertexBufferPieceEffect, textureEffectPanel, LayerNum::PLAY_GROUND_BACK);
		fade = new CGameObject(vertexBufferPiece, texturefade, LayerNum::BLACK_OUT);
		fadeblack = new CGameObject(vertexBufferPiece, texturefade, LayerNum::BLACK_OUT);
		mousecursor = new CGameObject(vertexBufferPiece, textureMouseCursor, LayerNum::BLACK_OUT);

		drawManager = new CDrawManager(0);	// 描画マネージャー

		// ポーズ
		pauseback = new CUi(vertexBufferBg, texturePauseBack, LayerNum::BLACK_OUT);
		pausebutton[0] = new CUi(vertexBufferPiece, texturePauseButtonContinue, LayerNum::BLACK_OUT);
		pausebutton[1] = new CUi(vertexBufferPiece, texturePauseButtonReturn, LayerNum::BLACK_OUT);
		pausebutton[2] = new CUi(vertexBufferPiece, texturePauseButtonRetry, LayerNum::BLACK_OUT);
		pausebuttonband[0] = new CUi(vertexBufferPiece, texturePauseButtonBand, LayerNum::BLACK_OUT);
		pausebuttonband[1] = new CUi(vertexBufferPiece, texturePauseButtonBand, LayerNum::BLACK_OUT);
		pausebuttonband[2] = new CUi(vertexBufferPiece, texturePauseButtonBand, LayerNum::BLACK_OUT);
		pausetext = new CUi(vertexBufferPiece, texturePauseScene, LayerNum::BLACK_OUT);
		pausetextband = new CUi(vertexBufferPiece, texturePauseSceneBand, LayerNum::BLACK_OUT);
		pausestagename = new CUi(vertexBufferPiece, texturePauseStageName, LayerNum::BLACK_OUT);

		// リザルト
		BlackBackGround = new CUi(vertexBufferBg, textureBlackBackGround, LayerNum::BLACK_OUT);		// 黒背景
		ClearText = new CUi(vertexBufferPiece, textureClearText, LayerNum::BLACK_OUT);				// テキスト：クリア
		ResultPanel = new CUi(vertexBufferPiece, textureResultPanel, LayerNum::BLACK_OUT);			// リザルト背景
		SceneBand = new CUi(vertexBufferPiece, textureSceneBand, LayerNum::BLACK_OUT);				// シーンバンド
		StageNameBand = new CUi(vertexBufferPiece, textureStageNameBand, LayerNum::BLACK_OUT);		// ステージバンド
		for (int i = 0; i < 3; i++)
		{
			ResultButton[i] = new CUi(vertexBufferPiece, textureButton, LayerNum::BLACK_OUT);		// ボタン(3個)
		}
		ResultText = new CUi(vertexBufferPiece, textureResultText, LayerNum::BLACK_OUT);			// テキスト：けっか
		Next = new CUi(vertexBufferPiece, textureNext, LayerNum::BLACK_OUT);						// テキスト：つぎへ
		Retry = new CUi(vertexBufferPiece, textureRetry, LayerNum::BLACK_OUT);						// テキスト：もういちど
		Return = new CUi(vertexBufferPiece, textureReturn, LayerNum::BLACK_OUT);					// テキスト：もどる
		OutText = new CUi(vertexBufferPiece, textureOut, LayerNum::BLACK_OUT);						// テキスト：もどる
	}

	// 初期座標設定
	{
		// 各1ピース画像
		{
			_position = { -6.9f,3.4f,0.2f };
			_scaling = { 2.3f,2.3f,1.0f };
			_rotation = { 0,0,0 };
			{
				//_position = { -6.75f, 3.4f ,0.1f };
				for (int i = 0; i < PIECE_Y; i++)
				{
					for (int j = 0; j < PIECE_X; j++)
					{
						piece_array[i][j]->transform->position = _position;
						piece_array[i][j]->transform->scale = _scaling;
						piece_array[i][j]->transform->rotate = _rotation;

						_position.x += 2.305f;
						_rotation.z += 90.0f;
					}
					_position.x = -6.9f;
					_position.y -= 2.26f;
				}
				//piece_array[2][3]->transform->position.x = 0;
			}
		}
		// 背景画像（後景）
		{
			background->transform->scale = { OBJECT_X * 32.0f,OBJECT_Y * 9.0f,1.0f };
			background->transform->position = { 8.0f,0.0f,1.0f };
		}
		// 背景画像（前景）
		{
			frontground->transform->scale = { OBJECT_X * 32.0f,OBJECT_Y * 9.0f, 1.0f };
			frontground->transform->position = { 8.0f, 0.0f, 1.0f };
		}
		// 背景パズルピース画像
		{
			pazle[0]->transform->scale = { 1.035f,1.0f,1.0f };
			pazle[1]->transform->scale = { 1.035f,1.0f,1.0f };
		}
		// 地面画像
		{
			for (int i = 0; i < 7; i++)
			{
				floor[i]->transform->scale = {2.25f,2.25f,1.0f};
				floor[i]->transform->position = piece_array[3][i]->transform->position;
				floor[i]->collider->transform = floor[i]->transform;
			}
			floor[5]->transform->position.y -= 2.3f;
			floor[6]->transform->position.y -= 2.3f;
			floor[7]->transform->position = piece_array[2][2]->transform->position;
			floor[7]->transform->scale = { 2.25f,2.25f,1.0f };
			floor[8]->transform->position = piece_array[2][3]->transform->position;
			floor[8]->transform->scale = { 2.3f,2.3f,1.0f };
			floor[9]->transform->position = piece_array[1][4]->transform->position;
			floor[9]->transform->scale = { 2.3f,2.3f,1.0f };
			floor[10]->transform->position = piece_array[1][5]->transform->position;
			floor[10]->transform->scale = { 2.3f,2.3f,1.0f };

			floor[2]->Settexture(textureFloormiddle);
			floor[3]->Settexture(textureFloormiddle);
			floor[7]->Settexture(textureFloortop);
			floor[8]->Settexture(textureFloortop);
			floor[9]->Settexture(textureFloortop);
			floor[10]->Settexture(textureFloortop);
			
		}
		// UIに置くパズルのピース画像
		{
			previewpiece->transform->position = { -6.5f,3.3f,1.0f };
			previewpiece->transform->scale = { 2.0f,2.0f,1.0f };
		}
		// エフェクト画像（テスト）
		{
			//effect->transform->position = { 0,0,0.5f };
			//effect->transform->scale = { 0.1,0.1,0.8f };
		}
		// UIピース置き場画像
		{
			uipiecestock->transform->position = { -6.5f,3.3f, 0.15f };
			uipiecestock->transform->scale = { 4.0f,4.0f,1.0f };
		}
		// プレイヤー
		{
			// アニメーション設定
			player->anim = new CAnimation(3, 3);
			player->anim->SetPattern(CAnimation::PLAYER);
			player->anim->animSpeed = 0.16f;
			// プレイヤーのサイズ調整
			player->transform->scale = { -2.0f,2.0f,1.0f };
			player->transform->position = { -6.8f,0.1f,1.0f };
	

			player->SetPlayerTexture(texturePlayer_stay);
			player->SetPlayerTexture(texturePlayer);
			player->SetPlayerTexture(texturePlayer_jump);
			player->SetPlayerTexture(texturePlayerDead);
		}
		// 木箱（1マスサイズ）
		{
			woodbox[0]->transform->position = piece_array[2][1]->transform->position;
			woodbox[0]->transform->position.y += 0.5f;
			woodbox[0]->transform->scale = { 2.2f,2.2f,1.0f };

			woodbox[1]->transform->position = piece_array[0][4]->transform->position;
			woodbox[1]->transform->position.y += 0.5f;
			woodbox[1]->transform->scale = { 2.2f,2.2f,1.0f };

		}
		// 木箱（0.5マスサイズ）
		{
			halfwoodbox[0]->transform->position = piece_array[0][5]->transform->position;
			halfwoodbox[0]->transform->scale = { 2.2f,2.2f,1.0f };
			halfwoodbox[0]->transform->scale.y /= 1.8f;
			halfwoodbox[0]->transform->position.y += 0.5f;
			halfwoodbox[0]->ishalf = true;

			halfwoodbox[1]->transform->position = piece_array[1][3]->transform->position;
			halfwoodbox[1]->transform->scale = { 2.2f,2.2f,1.0f };
			halfwoodbox[1]->transform->scale.y /= 1.8f;
			halfwoodbox[1]->transform->position.y += 0.5f;
			halfwoodbox[1]->ishalf = true;
		}
		// ゴール画像　テストで鍵になっている
		{
			goal->transform->position = piece_array[2][4]->transform->position;
			goal->transform->scale = { 2.5f,2.5f,1.0f };
			//goal->transform->rotate.z = 30.0f;
			goal->collider->transform = goal->transform;

			goaleffect->anim = new CAnimation(10, 6);
			goaleffect->anim->SetPattern(CAnimation::FX_0_54);
			goaleffect->anim->animSpeed = 0.4f;

			goaleffect->transform->position = goal->transform->position;
			goaleffect->transform->scale = { 2.5f,2.5f,1.0f };
		}
		// エフェクト
		{
			Pieceeffect->anim = new CAnimation(5, 7);
			Pieceeffect->anim->SetPattern(CAnimation::FX_54_0);
			Pieceeffect->anim->isPlaying = false;
			Pieceeffect->anim->animSpeed = 0.9f;

			Pieceeffect->transform->position = { 0.45f,1.1f,1.0f };
			Pieceeffect->transform->scale = { 4.0f,4.0f,1.0f };
		}
		// フェード
		{
			fade->transform->scale = { 16.0f, 9.0f, 1.0f };
			fadeblack->transform->scale = { 17.0f,17.0f,1.0f };
		}

		uionepiece->transform->scale = { 2.0f,2.0f,1.0f };
		uionepiece->transform->position = piece_array[0][0]->transform->position;

		mousecursor->transform->rotate.z = 40.0f;
		mousecursor->transform->scale = { 1.5f,1.5f,1.0f };

		// ポーズ用設定
		{
			// ボタンの後ろ
			{
				pausebuttonband[0]->transform->position = { -3.5f,0.9f,1.0f };
				pausebuttonband[0]->transform->scale = { 10.0f,10.0f,1.0f };
				pausebuttonband[1]->transform->position = { -3.5f,-0.9f,1.0f };
				pausebuttonband[1]->transform->scale = { 10.0f,10.0f,1.0f };
				pausebuttonband[2]->transform->position = { -3.5f,-2.8f,1.0f };
				pausebuttonband[2]->transform->scale = { 10.0f,10.0f,1.0f };
			}
			// ボタン
			{
				pausebutton[0]->transform->position = { -3.0f,0.9f,1.0f };
				pausebutton[0]->transform->scale = { 10.0f,10.0f,1.0f };
				pausebutton[1]->transform->position = { -3.0f,-0.9f,1.0f };
				pausebutton[1]->transform->scale = { 10.0f,10.0f,1.0f };
				pausebutton[2]->transform->position = { -3.0f,-2.8f,1.0f };
				pausebutton[2]->transform->scale = { 10.0f,10.0f,1.0f };
			}
			// 停止中 後ろ
			{
				pausetextband->transform->position = { -4.7f,3.5f,1.0f };
				pausetextband->transform->scale = { 7.0f,7.0f,1.0f };
				pausetext->transform->position = { -4.4f,3.5f,1.0f };
				pausetext->transform->scale = { 12.0f,12.0f,1.0f };
			}
			// ステージ名
			{
				pausestagename->transform->position = { -4.0f,2.3f,1.0f };
				pausestagename->transform->scale = { 11.0f,11.0f,1.0f };
			}

		}
		// リザルト用設定
		{
			// 背景黒透過
			{
				BlackBackGround->transform->scale = { 16.0f,9.0f,1.0f };
			}
			// クリア
			{
				//ClearText->transform->position = { 0.5f,-0.5f,1.0f };
				ClearText->transform->scale = { 24.0f,24.0f,1.0f };
				ClearText->materialDiffuse.w = 0.0f;
				OutText->transform->scale = { 24.0f,24.0f,1.0f };
				OutText->materialDiffuse.w = 0.0f;

				for (int i = 0; i < 3; i++)
				{
					//ResultButton[0]->materialDiffuse.w == 0.0f;
				}
			}
			// 次へ
			{
				Next->transform->scale = { 7.0f,7.0f,1.0f };
				Next->transform->position = { -5.2f,-2.5f,1.0f };
				Next->materialDiffuse.w = 0.0f;
			}
			// リトライ
			{
				Retry->transform->scale = { 6.5f,6.5f,1.0f };
				Retry->transform->position = { 0.0f,-2.5f,1.0f };
				Retry->materialDiffuse.w = 0.0f;
			}
			// 戻る
			{
				Return->transform->scale = { 7.0f,7.0f,1.0f };
				Return->transform->position = { 5.5f,-2.6f,1.0f };
				Return->materialDiffuse.w = 0.0f;
			}
			// 結果
			{
				ResultText->transform->position = { -5.0f,3.5f,1.0f };
				ResultText->transform->scale = { 7.0f,7.0f,1.0f };
			}
			//結果のバンド 
			{
				StageNameBand->transform->position = { -5.5f,3.5f,1.0f };
				StageNameBand->transform->scale = { 7.0f,7.0f,1.0f };
			}
			// ボタンのバンド
			{
				ResultButton[0]->transform->position = { -5.2f,-2.5f,1.0f };
				ResultButton[0]->transform->scale = { 10.0f,10.0f,1.0f };
				ResultButton[0]->materialDiffuse.w = 0.0f;
				ResultButton[1]->transform->position = Retry->transform->position;
				ResultButton[1]->transform->scale = { 5.0f,4.7f,1.0f };
				ResultButton[1]->materialDiffuse.w = 0.0f;
				ResultButton[2]->transform->position = { 5.2f,-2.5f,1.0f };
				ResultButton[2]->transform->scale = { 20.0f,4.7f,1.0f };
				ResultButton[2]->materialDiffuse.w = 0.0f;
			}
		}
	}



	// 各種可変長配列に格納
	{

		for (int i = 0; i < 11; i++)
		{
			floorObj.push_back(floor[i]);
		}

		// 子オブジェクトを子オブジェクト用可変長配列に格納する
		gimickObj.push_back(woodbox[0]);
		gimickObj.push_back(woodbox[1]);
		gimickObj.push_back(halfwoodbox[0]);
		gimickObj.push_back(halfwoodbox[1]);

	}
	// 描画するオブジェクトを配列に格納する
	{
		drawManager->AddObject(pazle[0]);					// 背景パズル
		drawManager->AddObject(pazle[1]);					// 背景パズル
		drawManager->AddObject(background);				// 背景（後景）
		drawManager->AddObject(frontground);			// 背景（前景）
		drawManager->AddObject(uionepiece);				// 現在ピースの場所を表示するUi
		drawManager->AddObject(player->collider);		// プレイヤーコライダー
		drawManager->AddObject(player);					// プレイヤー
		//drawManager->AddObject(woodbox[0]->collider);		// 木箱（1ピース）コライダー
		//drawManager->AddObject(woodbox[1]->collider);		// 木箱（1ピース）コライダー
		//drawManager->AddObject(halfwoodbox->collider);	// 木箱（0.5ピース）コライダー
		drawManager->AddObject(halfwoodbox[0]);			// 木箱（0.5ピース）
		drawManager->AddObject(halfwoodbox[1]);			// 木箱（0.5ピース）
		drawManager->AddObject(uipiecestock);			// Ui保存する場所
		drawManager->AddObject(woodbox[0]);				// 木箱（1ピース）
		drawManager->AddObject(woodbox[1]);				// 木箱（1ピース）
		drawManager->AddObject(goaleffect);					// エフェクト
		drawManager->AddObject(previewpiece);
		drawManager->AddObject(Pieceeffect);


		for (int i = 0; i < PIECE_Y; i++)
		{
			for (int j = 0; j < PIECE_X; j++)
			{
				drawManager->AddObject(piece_array[i][j]); // ピースの配列
				drawManager->AddObject(piece_array[i][j]->collider); // ピースの配列
			}
		}

		for (int i = 0; i < 11; i++)
		{
			drawManager->AddObject(floor[i]);			// 地面
			drawManager->AddObject(floor[i]->collider); // 地面コライダー
		}

		drawManager->AddObject(goal);			// ゴール
		drawManager->AddObject(goal->collider);	// ゴールコライダー	
		// 
		// ポーズ画面
		{
			drawManager->AddObject(pauseback);
			drawManager->AddObject(pausebuttonband[0]);
			drawManager->AddObject(pausebuttonband[1]);
			drawManager->AddObject(pausebuttonband[2]);
			drawManager->AddObject(pausebutton[0]);
			//drawManager->AddObject(pausebutton[0]);
			drawManager->AddObject(pausebutton[1]);
			drawManager->AddObject(pausebutton[2]);
			drawManager->AddObject(pausestagename);
			drawManager->AddObject(pausetextband);
			drawManager->AddObject(pausetext);
		}
		// リザルト画面
		{
			drawManager->AddObject(BlackBackGround);
			//drawManager->AddObject(ResultPanel);
			//drawManager->AddObject(SceneBand);
			drawManager->AddObject(StageNameBand);
			drawManager->AddObject(ResultText);
			drawManager->AddObject(ClearText);
			drawManager->AddObject(OutText);
			drawManager->AddObject(ResultButton[0]);
			drawManager->AddObject(ResultButton[1]);
			drawManager->AddObject(ResultButton[2]);
			drawManager->AddObject(Next);
			drawManager->AddObject(Retry);
			drawManager->AddObject(Return);

			BlackBackGround->isDraw = false;
			StageNameBand->isDraw = false;
			ResultText->isDraw = false;
			OutText->isDraw = false;
		}
		drawManager->AddObject(mousecursor);
		//drawManager->AddObject(fadeblack);
		drawManager->AddObject(fade);


		// ポーズ系を一旦描画を消すことにする
		{
			pauseback->isDraw = false;
			pausebuttonband[0]->isDraw = false;
			pausebuttonband[1]->isDraw = false;
			pausebuttonband[2]->isDraw = false;
			pausebutton[0]->isDraw = false;
			pausebutton[1]->isDraw = false;
			pausebutton[2]->isDraw = false;
			pausetextband->isDraw = false;
			pausetext->isDraw = false;
			pausestagename->isDraw = false;
		}

	}

	// 描画しない物をオフにしておく

	for (int i = 0; i < PIECE_Y; i++)
	{
		for (int j = 0; j < PIECE_X; j++)
		{
			piece_array[i][j]->isDraw = false;
			piece_array[i][j]->collider->isDraw = false;
		}
	}
	for (int i = 0; i < 11; i++)
	{
		floor[i]->collider->isDraw = false; // 地面コライダー
	}
	player->collider->isDraw = false;
	goal->collider->isDraw = false;
	
	drawManager->Update();

	CSoundManager::GetSound()->XA_Play(STAGE4_BGM, 0.4f);
}

Stage4::~Stage4()
{
	delete pazle;
	delete background;
	delete player;

	delete uipiecestock;
	delete uionepiece;
	delete previewpiece;
	delete work;
	delete uiDrawPiece;
	delete woodbox;

	for (int i = 0; i < PIECE_X; i++)
	{
		for (int j = 0; j < PIECE_Y; j++)
		{
			delete piece_array[j][i];
		}
	}
	for (int i = 0; i < PIECE_X; i++)
	{
		delete floor[i];
	}
	//delete boxcolider;
	delete goal;
	delete drawManager;

	delete pauseback;
	for (int i = 0; i < 3; i++)
	{
		delete pausebutton[i];
		delete pausebuttonband[i];
	}
	delete pausetext;
	delete pausetextband;
	delete pausestagename;

	delete BlackBackGround;
	delete ClearText;
	delete ResultPanel;
	delete SceneBand;
	delete StageNameBand;
	for (int i = 0; i < 3; i++)
	{
		delete ResultButton[i];
	}
	delete ResultText;
	delete Next;
	delete Retry;
	delete Return;
	delete OutText;

}

void Stage4::Update()
{
	{
		if (CInput::Get()->GetType() == CInput::HIDType::KeyBoardMouse)
		{
			DirectX::XMFLOAT2 pos = CInput::Get()->GetMousePos();
			mousecursor->transform->position.x = pos.x;
			mousecursor->transform->position.y = pos.y;
		}
		else
		{
			DirectX::XMFLOAT2 pos = CInput::Get()->GetControllerStick();

			mousecursor->transform->position.x += (pos.x / 10);
			mousecursor->transform->position.y += (pos.y / 10);
		}

		// フェード状態
		if (fadeout && !pauseSet)
		{
			fade->Update();
			fadeblack->Update();
			fade->transform->scale.x += 3.2f;
			fade->transform->scale.y += 1.8f;
			fadeblack->transform->scale.x += 0.2f;
			fadeblack->transform->scale.y += 0.2f;

			if (fade->transform->scale.y > 180.0f)
			{
				fadeout = false;
				player->idle_flg = false;
				CSceneManager::get()->fadeflag = false;
			}
		}
		// ポーズ状態
		else if (pauseSet && !fadeout)	// ポーズ画面
		{
			// ポーズ画面を描画する
			{
				pauseback->isDraw = true;
				pausebuttonband[0]->isDraw = true;
				pausebuttonband[1]->isDraw = true;
				pausebuttonband[2]->isDraw = true;
				pausebutton[0]->isDraw = true;
				pausebutton[1]->isDraw = true;
				pausebutton[2]->isDraw = true;
				pausetextband->isDraw = true;
				pausetext->isDraw = true;
				pausestagename->isDraw = true;
			}

			if (DotSquareCollision(&mousecursor->transform->position, pausebutton[0]->collider->transform))
			{
				pauseCnt = 0;
			}
			else if (DotSquareCollision(&mousecursor->transform->position, pausebutton[1]->collider->transform))
			{
				pauseCnt = 1;
			}
			else if (DotSquareCollision(&mousecursor->transform->position, pausebutton[2]->collider->transform))
			{
				pauseCnt = 2;
			}
			else
			{
				pauseCnt = 3;
			}

			if (pauseCnt == 0)
			{
				pausebuttonband[1]->transform->scale = { 10.0f,10.0f,1.0f };
				pausebutton[1]->transform->scale = { 10.0f,10.0f,1.0f };

				if (pausebutton[0]->transform->scale.x < 9.0f)
				{
					sizeup = true;
				}
				else if (pausebutton[0]->transform->scale.x > 11.0f)
				{
					sizeup = false;
				}

				if (sizeup)
				{
					pausebuttonband[0]->transform->scale.x += 0.05f;
					pausebuttonband[0]->transform->scale.y += 0.05f;
					pausebutton[0]->transform->scale.x += 0.05f;
					pausebutton[0]->transform->scale.y += 0.05f;
				}
				else
				{
					pausebuttonband[0]->transform->scale.x -= 0.05f;
					pausebuttonband[0]->transform->scale.y -= 0.05f;
					pausebutton[0]->transform->scale.x -= 0.05f;
					pausebutton[0]->transform->scale.y -= 0.05f;
				}
			}
			if (pauseCnt == 1)
			{
				pausebuttonband[0]->transform->scale = { 10.0f,10.0f,1.0f };
				pausebutton[0]->transform->scale = { 10.0f,10.0f,1.0f };
				pausebuttonband[2]->transform->scale = { 10.0f,10.0f,1.0f };
				pausebutton[2]->transform->scale = { 10.0f,10.0f,1.0f };

				if (pausebutton[1]->transform->scale.x < 9.0f)
				{
					sizeup = true;
				}
				else if (pausebutton[1]->transform->scale.x > 11.0f)
				{
					sizeup = false;
				}

				if (sizeup)
				{
					pausebuttonband[1]->transform->scale.x += 0.05f;
					pausebuttonband[1]->transform->scale.y += 0.05f;
					pausebutton[1]->transform->scale.x += 0.05f;
					pausebutton[1]->transform->scale.y += 0.05f;
				}
				else
				{
					pausebuttonband[1]->transform->scale.x -= 0.05f;
					pausebuttonband[1]->transform->scale.y -= 0.05f;
					pausebutton[1]->transform->scale.x -= 0.05f;
					pausebutton[1]->transform->scale.y -= 0.05f;
				}
			}
			if (pauseCnt == 2)
			{
				pausebuttonband[1]->transform->scale = { 10.0f,10.0f,1.0f };
				pausebutton[1]->transform->scale = { 10.0f,10.0f,1.0f };

				if (pausebutton[2]->transform->scale.x < 9.0f)
				{
					sizeup = true;
				}
				else if (pausebutton[2]->transform->scale.x > 11.0f)
				{
					sizeup = false;
				}

				if (sizeup)
				{
					pausebuttonband[2]->transform->scale.x += 0.05f;
					pausebuttonband[2]->transform->scale.y += 0.05f;
					pausebutton[2]->transform->scale.x += 0.05f;
					pausebutton[2]->transform->scale.y += 0.05f;
				}
				else
				{
					pausebuttonband[2]->transform->scale.x -= 0.05f;
					pausebuttonband[2]->transform->scale.y -= 0.05f;
					pausebutton[2]->transform->scale.x -= 0.05f;
					pausebutton[2]->transform->scale.y -= 0.05f;
				}
			}

			if (CInput::Get()->GetType() == CInput::HIDType::KeyBoardMouse ? CInput::Get()->isMouseTrigger(CInput::InputType::LB1) : CInput::Get()->isKeyTrigger(CInput::InputType::A))
			{
				if (pauseCnt == 0)
				{
					// ポーズ画面を消す
					{
						pauseback->isDraw = false;
						pausebuttonband[0]->isDraw = false;
						pausebuttonband[1]->isDraw = false;
						pausebuttonband[2]->isDraw = false;
						pausebutton[0]->isDraw = false;
						pausebutton[1]->isDraw = false;
						pausebutton[2]->isDraw = false;
						pausetextband->isDraw = false;
						pausetext->isDraw = false;
						pausestagename->isDraw = false;

					}
					// ポーズ状態を解除する
					pauseSet = false;
				}
				else if (pauseCnt == 1)
				{

					while (fade->transform->scale.y <= 1.0f)
					{
						fade->Update();
						fadeblack->Update();
						fade->transform->scale.x -= 0.12f;
						fade->transform->scale.y -= 0.12f;
						fadeblack->transform->scale.x -= 0.2f;
						fadeblack->transform->scale.y -= 0.2f;
					}
					CSoundManager::GetSound()->XA_Stop(STAGE4_BGM);

					CSceneManager::get()->ChangeScene(CSceneManager::SceneState::SERECT);
					// ポーズ状態を解除する
					pauseSet = false;
				}
				else
				{
					CSceneManager::get()->ChangeStage(CSceneManager::StageState::STAGE4);
					// ポーズ状態を解除する
					pauseSet = false;
				}
			}
			//player->idle_flg = true;
		}
		// リザルト状態
		else if (resultset)
		{
			//drawManager->Update();
			BlackBackGround->isDraw = true;
			StageNameBand->isDraw = true;
			if (playerOut)
			{
				player->Update();
				OutText->isDraw = true;

				// クリアの文字が既定の文字サイズ＆透過が元どおりになっていたら
				if (OutText->transform->scale.x >= 15.0f && OutText->transform->scale.y >= 15.0f)
				{
					OutText->transform->scale.x -= 0.1f;
					OutText->transform->scale.y -= 0.1f;

				}
				if (OutText->materialDiffuse.w != 1.0f)
				{
					OutText->materialDiffuse.w += 0.01f;
				}
				if (OutText->transform->scale.x <= 15.0f && OutText->materialDiffuse.w >= 1.0f)
				{
					OutText->transform->position.y += 0.02f;
				}
				if (OutText->transform->position.y >= 1.3f)
				{
					OutText->transform->position.y = 1.3f;
					Next->materialDiffuse.w = 0.3f;
					Retry->materialDiffuse.w += 0.05f;
					Return->materialDiffuse.w += 0.05f;
					ResultButton[0]->materialDiffuse.w = 0.3f;
					ResultButton[1]->materialDiffuse.w += 0.05f;
					ResultButton[2]->materialDiffuse.w += 0.05f;
				}

			}
			else
			{
				ResultText->isDraw = true;

				// クリアの文字が既定の文字サイズ＆透過が元どおりになっていたら
				if (ClearText->transform->scale.x >= 15.0f && ClearText->transform->scale.y >= 15.0f)
				{
					ClearText->transform->scale.x -= 0.1f;
					ClearText->transform->scale.y -= 0.1f;

				}
				if (ClearText->materialDiffuse.w != 1.0f)
				{
					ClearText->materialDiffuse.w += 0.01f;
				}
				if (ClearText->transform->scale.x <= 15.0f && ClearText->materialDiffuse.w >= 1.0f)
				{
					ClearText->transform->position.y += 0.02f;
				}
				if (ClearText->transform->position.y >= 1.3f)
				{
					ClearText->transform->position.y = 1.3f;
					Next->materialDiffuse.w += 0.05f;
					Retry->materialDiffuse.w += 0.05f;
					Return->materialDiffuse.w += 0.05f;
					ResultButton[0]->materialDiffuse.w += 0.05f;
					ResultButton[1]->materialDiffuse.w += 0.05f;
					ResultButton[2]->materialDiffuse.w += 0.05f;
				}
			}

			if (DotSquareCollision(&mousecursor->transform->position, Next->collider->transform))
			{
				select = 0;
			}
			else if (DotSquareCollision(&mousecursor->transform->position, Retry->collider->transform))
			{
				select = 1;
			}
			else if (DotSquareCollision(&mousecursor->transform->position, Return->collider->transform))
			{
				select = 2;
			}
			else
			{
				select = 3;
			}

			// つぎへ
			if (select == 0 && !playerOut)
			{
				if (ResultButton[0]->transform->scale.x <= 6.5f && ResultButton[0]->transform->scale.y <= 6.3f)
				{
					ResultButton[0]->transform->scale.x += 0.1f;
					ResultButton[0]->transform->scale.y += 0.1f;
				}
			}
			else
			{
				ResultButton[0]->transform->scale.x = 6.0f;
				ResultButton[0]->transform->scale.y = 5.8f;
			}
			// もういちど
			if (select == 1)
			{
				if (ResultButton[1]->transform->scale.x <= 6.5f && ResultButton[1]->transform->scale.y <= 6.3f)
				{
					ResultButton[1]->transform->scale.x += 0.1f;
					ResultButton[1]->transform->scale.y += 0.1f;
				}
			}
			else
			{
				ResultButton[1]->transform->scale.x = 6.0f;
				ResultButton[1]->transform->scale.y = 5.8f;
			}
			// もどる
			if (select == 2)
			{
				if (ResultButton[2]->transform->scale.x <= 6.5f && ResultButton[2]->transform->scale.y <= 6.3f)
				{
					ResultButton[2]->transform->scale.x += 0.1f;
					ResultButton[2]->transform->scale.y += 0.1f;
				}
			}
			else
			{
				ResultButton[2]->transform->scale.x = 6.0f;
				ResultButton[2]->transform->scale.y = 5.8f;
			}
			if (CInput::Get()->GetType() == CInput::HIDType::KeyBoardMouse ? CInput::Get()->isMouseTrigger(CInput::InputType::LB1) : CInput::Get()->isKeyTrigger(CInput::InputType::A))
			{
				// 次への処理
				if (select == 0 && !playerOut)
				{
					CSoundManager::GetSound()->XA_Play(CURSOR, 0.5f);
					CSoundManager::GetSound()->XA_Stop(STAGE4_BGM);
					CSceneManager::get()->ChangeStage(CSceneManager::StageState::STAGE1);
				}
				// もう一度の処理
				if (select == 1)
				{
					CSoundManager::GetSound()->XA_Play(CURSOR, 0.5f);
					CSceneManager::get()->ChangeStage(CSceneManager::StageState::STAGE4);
				}
				// 戻るの処理
				if (select == 2)
				{
					CSoundManager::GetSound()->XA_Play(CURSOR, 0.5f);
					CSoundManager::GetSound()->XA_Stop(STAGE4_BGM);
					CSceneManager::get()->ChangeScene(CSceneManager::SceneState::SERECT);
				}
			}
		}
		else
		{
			drawManager->Update();
			 
			// プレイヤー　床当たり判定
			for (auto&& f : floorObj)
			{
				if (player->collider->transform->Right > floor[7]->transform->Left  && player->sideflg && player->transform->position.x < floor[7]->transform->Left)
 				{ player->CheckJump_Turn(floor[7]->transform); break; }
				if (player->collider->transform->Right > floor[9]->transform->Left   && player->sideflg && player->transform->position.x < floor[9]->transform->Left && player->collider->transform->Bottom + 0.3f < floor[9]->transform->Top)
				{ player->CheckJump_Turn(floor[9]->transform); break; }
				if (player->collider->transform->Left  < floor[10]->transform->Right && !player->sideflg && player->collider->transform->Left> floor[10]->transform->Right && player->collider->transform->Top > floor[10]->transform->Bottom)
				{ player->CheckJump_Turn(f->transform); break; }
				if (DoSquareCollision(player, f)){ player->isGravity = false; break; }
				player->isGravity = true;
			}

			// ギミック同士の当たり判定
			for (auto&& g : gimickObj)
			{
				for (auto&& g2 : gimickObj)
				{
					if (g == g2) continue;
					if (DoSquareCollision(g, g2))
					{
						if (g->transform->Bottom < g2->transform->Top)
						{
							g->isGravity = false;
							break;
						}
					}
					if (g->GetLayer() == LayerNum::PLAY_GROUND)g->isGravity = true;
				}
			}

			// 床　ギミック当たり判定
			for (auto&& f : floorObj)
			{
				for (auto&& g : gimickObj)
				{
					if (g->GetLayer() == LayerNum::PLAY_GROUND)
					{
						if (DoSquareCollision(g, f))
						{
							g->isGravity = false;
						}
					}
				}
			}

			// ギミック　プレイヤー当たり判定
			for (auto&& g : gimickObj)
			{
				if (DoSquareCollision(player->collider, g))
				{
					// ギミックの中にいる状態になった場合　挟まった判定として失敗リザルトに移行する
					if (player->transform->position.y + 0.7f > g->transform->Bottom && player->transform->Top < g->transform->Top && player->collider->transform->Right < g->transform->Right && player->collider->transform->Left > g->transform->Left)
					{
						player->dead_flg = true;
						playerOut = true;
						resultset = true;
					}
					// プレイヤー右 ギミック右 && プレイヤーが右向き && 
					if (player->collider->transform->Right > g->transform->Left && player->sideflg && 0.5f < fabs(player->collider->transform->Left - g->transform->Right))
					{
						if (0.5f < fabsf(player->transform->Bottom - g->transform->Top))
						{
							player->CheckJump_Turn(g->transform);
						}
						else
						{
							player->isGravity = false;
						}
						break;
					}
					else if (player->collider->transform->Left < g->transform->Right && !player->sideflg && 0.5f < fabs(player->collider->transform->Right - g->transform->Left))
					{
						if (0.5f < fabsf(player->transform->Bottom - g->transform->Top))
						{
							player->CheckJump_Turn(g->transform);
						}
						else
						{
							player->isGravity = false;
						}
						break;
					}
				}
			}

			// ゴールの当たり判定
			if (DoSquareCollision(goal->collider,player->collider))
			{
				resultset = true;
			}

			// ポーズ画面選択するとき
			if (CInput::Get()->GetType() == CInput::HIDType::KeyBoardMouse ? CInput::Get()->isMouseTrigger(CInput::InputType::RB1) : CInput::Get()->isKeyTrigger(CInput::InputType::START))
			{
				pauseSet = true;
			}

			// 一定以下の座標に行ったらゲームオーバーにする
			if (player->transform->position.y <= -4.0f)
			{
				playerOut = true;
				resultset = true;
			}

			// 入れ替え処理
			if (CInput::Get()->GetType() == CInput::HIDType::KeyBoardMouse ? CInput::Get()->isMouseTrigger(CInput::InputType::LB1) : CInput::Get()->isKeyTrigger(CInput::InputType::A))
			{
				for (int i = 0; i < 4; i++)
				{
					for (int j = 0; j < 7; j++)
					{
						if (DotSquareCollision(&mousecursor->transform->position, piece_array[i][j]->transform))
						{
							if (!Pieceeffect->anim->isPlaying)
							{
								Pieceeffect->transform->position = piece_array[i][j]->transform->position;
								Pieceeffect->transform->rotate = piece_array[i][j]->transform->rotate;
								Pieceeffect->anim->isPlaying = true;
							}
							ReplaceObj(piece_array[i][j]);
							break;
						}
					}
				}
			}
		}
	}
}

void Stage4::Draw()
{
	drawManager->Draw();
}

void Stage4::ReplaceObj(CGameObject* _pieceobj)
{
	for (auto&& f : floorObj)
	{
		if (_pieceobj->isCheckObject(f))return;
	}
	for (auto&& g : gimickObj)
	{
		if (g->isGravity)return;
	}
	if (_pieceobj->isCheckObject(goal->collider))return;
	if (_pieceobj->isCheckObject(player->collider))return;
	int sizecount = 1;
	// 当たったピースの中に移動できる子オブジェクトがあるかどうかを調べる
	for (auto&& d : gimickObj)
	{
		d->transform->VertexPos();
		bool hitobj = false;

		// 選択したピースの中に子オブジェクトがあるかどうか確認する
		hitobj = _pieceobj->isCheckObject(d);

		if (hitobj)// 中にあったとき
		{
			for (auto&& o : gimickObj)
			{
				o->transform->VertexPos();
				// UIの中にいるか子オブジェクトが格納されているかどうかを見る
				hitobj = previewpiece->isCheckObject(o);

				if (hitobj) // UIの中に子オブジェクトが格納されているとき
				{
					// オブジェクト同士を入れ替える
					// ゲーム画面オブジェクトを保存する
					work->transform->position = d->transform->position;
					//// UIの中のオブジェクトをゲーム画面に移動する
					d->transform->position = o->transform->position;
					//// 保存したオブジェクトをUIの中に入れる
					o->transform->position = _pieceobj->transform->position;

					// オブジェクトの大きさを変更する
					o->transform->scale = { 2.3f,2.3f,1.0f };
					if (o->ishalf)o->transform->scale.y /= 2;
					_scaling = previewpiece->transform->scale;
					d->transform->scale = CFloat3(_scaling.x / 2, _scaling.y / 2, _scaling.z);
					if (d->ishalf)d->transform->scale.y /= 2;
					o->transform->position.y += 0.2f;
					//if (o->ishalf) o->transform->scale.y /= 2;

					o->Setlayer(LayerNum::PLAY_GROUND);
					d->Setlayer(LayerNum::UI);

					return;
				}
				else // 格納されていなければ
				{
					// 格納されている分のサイズチェックする
					if (gimickObj.size() != sizecount)
					{
						sizecount++;
						continue;
					}
					// 何も入っていなければUIの所に子オブジェクトを配置する
					_position = previewpiece->transform->position;
					_scaling = previewpiece->transform->scale;

					d->transform->position = _position;
					d->transform->scale = CFloat3(_scaling.x / 2, _scaling.y / 2, _scaling.z);

					if (d->ishalf)d->transform->scale.y /= 2;

					d->Setlayer(LayerNum::UI);
					return;
				}
			}
		}
		else // 中になかったとき
		{
			// サイズ分終わってなければ処理をスキップさせる
			if (gimickObj.size() != sizecount) { sizecount++; continue; }
			sizecount = 1;
			for (auto&& notinPiece : gimickObj)
			{
				// UIの中に子オブジェクトがあるかどうかを確認する
				hitobj = previewpiece->isCheckObject(notinPiece);

				if (hitobj) // 中にあったとき
				{
					notinPiece->transform->position = _pieceobj->transform->position;
					//notinPiece->transform->rotate = _pieceobj->transform->rotate;
					notinPiece->transform->scale = { _pieceobj->transform->scale.x * 1.0f,_pieceobj->transform->scale.y * 1.0f,1.0f };
					notinPiece->Setlayer(LayerNum::PLAY_GROUND);
					if (notinPiece->ishalf)notinPiece->transform->scale.y /= 2;
					notinPiece->isGravity = true;
					return;
				}
				else // 中に無かったとき
				{
					// 全部確認するまで確認する
					if (gimickObj.size() == sizecount)
					{
						return;
					}
					else
					{
						sizecount++;
						continue;
					}
				}
			}
		}
	}
}
