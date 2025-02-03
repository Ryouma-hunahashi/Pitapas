#include "Stage1.h"

#include "CSoundManager.h"

Stage1::Stage1()
{
	// モデル作成
	{
		// 背景モデル作成（画像全体を表示する時に使用する）
		center = { 0.0f, 0.0f };
		size = { 1.0f,1.0f };
		uv = { 1.0f, 1.0f };
		CDirectX::Get()->D3D_CreateSquare(center, size, uv, &vertexBufferBg);

		// プレイヤーモデル作成
		uv = { 0.33f, 0.33f };
		CDirectX::Get()->D3D_CreateSquare(center, size, uv, &vertexBufferPlayer);

		// ゴールエフェクトモデル作成
		uv = { (1.0f / 10), (1.0f / 6) };
		CDirectX::Get()->D3D_CreateSquare(center, size, uv, &vertexBufferGoalEffect);

		// ピースエフェクトモデル作成
		uv = { 1.0f / 5,1.0f / 7 };
		CDirectX::Get()->D3D_CreateSquare(center, size, uv, &vertexBufferPieceEffect);
	}

	// テクスチャ読み込み
	{
		CDirectX::Get()->D3D_LoadTexture(L"asset/stage1/pitapasu_village_far.png", &textureBackGround);		// 背景テクスチャ（後景）
		CDirectX::Get()->D3D_LoadTexture(L"asset/stage1/pitapasu_village_close.png", &textureFrontGround);	// 背景テクスチャ(前景)
		CDirectX::Get()->D3D_LoadTexture(L"asset/Ui_Image_PieceGrid_Ver4.png", &textureBackPazleGround);	// 背景用パズルピーステクスチャ
		CDirectX::Get()->D3D_LoadTexture(L"asset/player/pitapasu_sprite_Walk.png", &texturePlayerWalk);		// プレイヤー（歩き）
		CDirectX::Get()->D3D_LoadTexture(L"asset/player/pitapasu_sprite_stay.png", &texturePlayerStay);		// プレイヤー（待機）
		CDirectX::Get()->D3D_LoadTexture(L"asset/player/pitapasu_sprite_jump.png", &texturePlayerJump);		// プレイヤー（ジャンプ）
		CDirectX::Get()->D3D_LoadTexture(L"asset/player/pitapasu_sprite_down.png", &texturePlayerDead);		// プレイヤー（死亡）
		CDirectX::Get()->D3D_LoadTexture(L"asset/stage1/pitapasu_village_ground01.png", &textureFloorTop);	// 地面テクスチャ
		CDirectX::Get()->D3D_LoadTexture(L"asset/gimick/wood box.png", &textureWoodBox);					// ギミック木箱1マス
		CDirectX::Get()->D3D_LoadTexture(L"asset/gimick/half wood box.png", &textureHalfWoodBox);			// ギミック木箱0.5マス
		CDirectX::Get()->D3D_LoadTexture(L"asset/UI/Ui_Image_MouseCursor.png", &textureMouseCursor);		// マウス用テクスチャ
		CDirectX::Get()->D3D_LoadTexture(L"asset/UI/Ui_Image_Peace.png", &textureUiPiece);					// １ピース画像のテクスチャ（UIに使用）
		CDirectX::Get()->D3D_LoadTexture(L"asset/UI/Ui_Image_PeacePreview02.png", &textureUiPreview);		// １ピース画像のテクスチャ（UIに使用）
		CDirectX::Get()->D3D_LoadTexture(L"asset/effect/pita_effect.png", &textureEffectPiece);				// ピースエフェクト
		CDirectX::Get()->D3D_LoadTexture(L"asset/goal_piece.png", &textureGoal);							// ゴール用テクスチャ
		CDirectX::Get()->D3D_LoadTexture(L"asset/UI/Ui_Image_LoadScreen.png", &texturefade);				// フェード用テクスチャ
		CDirectX::Get()->D3D_LoadTexture(L"asset/effect/pita_goal.png", &textureEffectGoal);				// ゴールエフェクト


		// ポーズ用
		CDirectX::Get()->D3D_LoadTexture(L"asset/pause/Ui_Image_PauseBackGround.png", &texturePauseBack);
		CDirectX::Get()->D3D_LoadTexture(L"asset/pause/Ui_Image_PauseButtonBand.png", &texturePauseButtonBand);
		CDirectX::Get()->D3D_LoadTexture(L"asset/pause/Ui_Text_Pause.png", &texturePauseScene);
		CDirectX::Get()->D3D_LoadTexture(L"asset/pause/Ui_Text_PauseButtonContinue.png", &texturePauseButtonContinue);
		CDirectX::Get()->D3D_LoadTexture(L"asset/pause/Ui_Text_PauseButtonRetry.png", &texturePauseButtonRetry);
		CDirectX::Get()->D3D_LoadTexture(L"asset/pause/Ui_Text_PauseButtonReturn.png", &texturePauseButtonReturn);
		CDirectX::Get()->D3D_LoadTexture(L"asset/select/Ui_Text_StageName1-1.png", &texturePauseStageName);
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

	// オブジェクト生成
	{
		background[0] = new CBackGround(vertexBufferBg, textureBackGround, LayerNum::BACK_GROUND);
		background[1] = new CBackGround(vertexBufferBg, textureFrontGround, LayerNum::FORE_GROUND);
		pazlebackground = new CBackGround(vertexBufferBg, textureBackPazleGround, LayerNum::BACK_GROUND);
		player = new CPlayer(vertexBufferPlayer, texturePlayerWalk,LayerNum::PLAY_GROUND);
		for (int i = 0; i < 7; i++)
		{
			floor[i] = new CFloor(vertexBufferBg, textureFloorTop, LayerNum::PLAY_GROUND_BACK);
		}
		woodbox[0] = new CWoodBox(vertexBufferBg, textureWoodBox, LayerNum::PLAY_GROUND);
		woodbox[1] = new CWoodBox(vertexBufferBg, textureWoodBox, LayerNum::PLAY_GROUND);
		mousecursor = new CGameObject(vertexBufferBg, textureMouseCursor, LayerNum::BLACK_OUT);
		uipiece = new CGameObject(vertexBufferBg, textureUiPiece, LayerNum::UI);
		uiPreview = new CUi(vertexBufferBg, textureUiPreview, LayerNum::UI);
		Pieceeffect = new CGameObject(vertexBufferPieceEffect, textureEffectPiece, LayerNum::PLAY_GROUND_FRONT);
		goal = new CGoal(vertexBufferBg, textureGoal, LayerNum::PLAY_GROUND);						// ゴール
		goaleffect = new CGameObject(vertexBufferGoalEffect, textureEffectGoal, LayerNum::PLAY_GROUND_BACK);
		work = new CGameObject(NULL, NULL, NULL);
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 7; j++)
			{
				piece_array[i][j] = new CPiece(vertexBufferBg, textureUiPiece, LayerNum::PLAY_GROUND_BACK);
			}
		}

		// 描画マネージャーを実体化する
		D_manager = new CDrawManager(0);

		fade = new CGameObject(vertexBufferBg, texturefade, LayerNum::BLACK_OUT);
		fadeblack = new CGameObject(vertexBufferBg, texturefade, LayerNum::BLACK_OUT);

		// ポーズ
		pauseback = new CUi(vertexBufferBg, texturePauseBack, LayerNum::BLACK_OUT);
		pausebutton[0] = new CUi(vertexBufferBg, texturePauseButtonContinue, LayerNum::BLACK_OUT);
		pausebutton[1] = new CUi(vertexBufferBg, texturePauseButtonReturn, LayerNum::BLACK_OUT);
		pausebutton[2] = new CUi(vertexBufferBg, texturePauseButtonRetry, LayerNum::BLACK_OUT);
		pausebuttonband[0] = new CUi(vertexBufferBg, texturePauseButtonBand, LayerNum::BLACK_OUT);
		pausebuttonband[1] = new CUi(vertexBufferBg, texturePauseButtonBand, LayerNum::BLACK_OUT);
		pausebuttonband[2] = new CUi(vertexBufferBg, texturePauseButtonBand, LayerNum::BLACK_OUT);
		pausetext = new CUi(vertexBufferBg, texturePauseScene, LayerNum::BLACK_OUT);
		pausetextband = new CUi(vertexBufferBg, texturePauseSceneBand, LayerNum::BLACK_OUT);
		pausestagename = new CUi(vertexBufferBg, texturePauseStageName, LayerNum::BLACK_OUT);

		// リザルト
		BlackBackGround = new CUi(vertexBufferBg, textureBlackBackGround, LayerNum::BLACK_OUT);		// 黒背景
		ClearText = new CUi(vertexBufferBg, textureClearText, LayerNum::BLACK_OUT);				// テキスト：クリア
		ResultPanel = new CUi(vertexBufferBg, textureResultPanel, LayerNum::BLACK_OUT);			// リザルト背景
		SceneBand = new CUi(vertexBufferBg, textureSceneBand, LayerNum::BLACK_OUT);				// シーンバンド
		StageNameBand = new CUi(vertexBufferBg, textureStageNameBand, LayerNum::BLACK_OUT);		// ステージバンド
		for (int i = 0; i < 3; i++)
		{
			ResultButton[i] = new CUi(vertexBufferBg, textureButton, LayerNum::BLACK_OUT);		// ボタン(3個)
		}
		ResultText = new CUi(vertexBufferBg, textureResultText, LayerNum::BLACK_OUT);			// テキスト：けっか
		Next = new CUi(vertexBufferBg, textureNext, LayerNum::BLACK_OUT);						// テキスト：つぎへ
		Retry = new CUi(vertexBufferBg, textureRetry, LayerNum::BLACK_OUT);						// テキスト：もういちど
		Return = new CUi(vertexBufferBg, textureReturn, LayerNum::BLACK_OUT);					// テキスト：もどる
		OutText = new CUi(vertexBufferBg, textureOut, LayerNum::BLACK_OUT);						// テキスト：もどる

	}

	// 座標位置設定
	{
		// 背景設定
		{
			background[0]->transform->scale = { 32.0f,9.0f,1.0f };
			background[1]->transform->scale = { 32.0f,9.0f,1.0f };
			background[0]->transform->position.x = 8.0f;
			background[1]->transform->position.x = 8.0f;
			pazlebackground->transform->scale = { 16.7f,9.1f,1.0f };
		}
		// プレイヤー設定
		{
			player->transform->position = { -4.0f,-1.0f,1.0f };
			player->transform->scale = { -2.0f,2.0f,1.0f };
			player->anim = new CAnimation(3, 3);
			player->anim->SetPattern(CAnimation::PLAYER);

			player->SetPlayerTexture(texturePlayerStay);
			player->SetPlayerTexture(texturePlayerWalk);
			player->SetPlayerTexture(texturePlayerJump);
			player->SetPlayerTexture(texturePlayerDead);

		}
		// 地面設定
		{
			CFloat3 position = { -6.9f,-3.35f,1.0f };
			for (int i = 0; i < 7; i++)
			{
				floor[i]->transform->position = position;
				floor[i]->transform->scale = { 2.2f,2.2f,1.0f };
				position.x += 2.3f;
			}

			floor[3]->transform->position.y -= 2.3f;
			floor[4]->transform->position.y -= 2.3f;
		}
		// 木箱設定
		{
			woodbox[0]->transform->scale = {2.2f,2.2f,1.0f};
			woodbox[1]->transform->scale = {2.2f,2.2f,1.0f};

			woodbox[1]->transform->position.x = floor[0]->transform->position.x;
			woodbox[0]->transform->position.y -= 1.0f;
			woodbox[1]->transform->position.y -= 1.0f;
		}
		// マウスカーソル
		{
			mousecursor->transform->rotate.z = 40.0f;
			mousecursor->transform->scale = { 1.5f,1.5f,1.0f };
		}
		// Uiピース
		{
			uiPreview->transform->position = { -6.5f,3.3f,1.0f };
			uiPreview->transform->scale = { 4.0f,4.0f,1.0f };
			uipiece->transform->position = { -6.5f,3.3f,1.0f };
			uipiece->transform->scale = { 2.0f,2.0f,1.0f };
		}
		// 各ピース位置保存場所
		{
			_position = { -6.9f,3.4f,1.0f };
			_scale = { 2.3f,2.3f,1.0f };

			for (int i = 0; i < 4; i++)
			{
				for (int j = 0; j < 7; j++)
				{
					piece_array[i][j]->transform->position = _position;
					piece_array[i][j]->transform->scale = _scale;
					piece_array[i][j]->transform->rotate = _rotation;

					_position.x += 2.31f;
					_rotation.z += 90.0f;
				}
				_position.x = -6.9f;
				_position.y -= 2.3f;
			}
		}
		// ピースエフェクト
		{
			Pieceeffect->transform->scale = { 10.0f,10.0f,1.0f };
			Pieceeffect->anim = new CAnimation(5, 7);
			Pieceeffect->anim->SetPattern(CAnimation::FX_0_19);
			Pieceeffect->anim->animSpeed = 0.6f;
			Pieceeffect->anim->isPlaying = false;
		}
		// ゴール
		{
			goal->transform->scale = { 2.5f,2.5f,1.0f };
			goal->transform->position = { 7.0f,-1.2f,1.0f };
			goaleffect->transform = goal->transform;
			goaleffect->transform->scale = { 2.7f,2.7f,1.0f };
			goaleffect->anim = new CAnimation(10, 6);
			goaleffect->anim->animSpeed = 0.4f;
			goaleffect->anim->SetPattern(CAnimation::FX_0_54);
		}

		// フェード用
		{
			fade->transform->scale = { 16.0f, 9.0f, 1.0f };
			fadeblack->transform->scale = { 17.0f,17.0f,1.0f };
		}

		// ポーズ用設定
		{
			{
				pauseback->transform->scale = { 16.0f,9.0f,1.0f };
			}

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

	// 可変長配列に格納する
	for (int i = 0; i < 7; i++)
	{
		floorObj.push_back(floor[i]->collider);
	}

	gimickObj.push_back(woodbox[0]);
	gimickObj.push_back(woodbox[1]);

	// 描画する時に使用するクラスに格納する
	{
		D_manager->AddObject(background[0]);
		D_manager->AddObject(background[1]);
		D_manager->AddObject(pazlebackground);
		D_manager->AddObject(player);
		D_manager->AddObject(player->collider);
		for (int i = 0; i < 7; i++)
		{
			D_manager->AddObject(floor[i]);
			D_manager->AddObject(floor[i]->collider);
		}
		D_manager->AddObject(woodbox[0]);
		D_manager->AddObject(woodbox[1]);
		D_manager->AddObject(uiPreview);
		D_manager->AddObject(uipiece);
		D_manager->AddObject(goal);
		D_manager->AddObject(goal->collider);

		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 7; j++)
			{
				D_manager->AddObject(piece_array[i][j]);
				D_manager->AddObject(piece_array[i][j]->collider);
			}
		}
		D_manager->AddObject(Pieceeffect);
		D_manager->AddObject(goaleffect);

		// ポーズ画面
		{
			D_manager->AddObject(pauseback);
			D_manager->AddObject(pausebuttonband[0]);
			D_manager->AddObject(pausebuttonband[1]);
			D_manager->AddObject(pausebuttonband[2]);
			D_manager->AddObject(pausebutton[0]);
			//drawManager->AddObject(pausebutton[0]);
			D_manager->AddObject(pausebutton[1]);
			D_manager->AddObject(pausebutton[2]);
			D_manager->AddObject(pausestagename);
			D_manager->AddObject(pausetextband);
			D_manager->AddObject(pausetext);
		}
		// リザルト画面
		{
			D_manager->AddObject(BlackBackGround);
			//drawManager->AddObject(ResultPanel);
			//drawManager->AddObject(SceneBand);
			D_manager->AddObject(StageNameBand);
			D_manager->AddObject(ResultText);
			D_manager->AddObject(ClearText);
			D_manager->AddObject(OutText);
			D_manager->AddObject(ResultButton[0]);
			D_manager->AddObject(ResultButton[1]);
			D_manager->AddObject(ResultButton[2]);
			D_manager->AddObject(Next);
			D_manager->AddObject(Retry);
			D_manager->AddObject(Return);
		}

		D_manager->AddObject(mousecursor);
		//D_manager->AddObject(fadeblack);
		D_manager->AddObject(fade);
	}

	// 当たり判定だけに使用するため描画はせずにする
	{
		for (int i = 0; i < 7; i++)
		{
			floor[i]->collider->isDraw = false;
		}
		player->collider->isDraw = false;
		goal->collider->isDraw = false;
		floor[4]->isDraw = false;

		player->idle_flg = false;

		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 7; j++)
			{
				piece_array[i][j]->isDraw = false;
				piece_array[i][j]->collider->isDraw = false;
			}
		}
	}
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
	// リザルト系を一旦描画消す
	{
		BlackBackGround->isDraw = false;
		StageNameBand->isDraw = false;
		ResultText->isDraw = false;
		OutText->isDraw = false;
		D_manager->Update();
	}

	// BGM再生
	CSoundManager::GetSound()->XA_Play(STAGE1_BGM, 0.4f);
}

Stage1::~Stage1()
{
	delete background[0];
	delete background[1];
	delete pazlebackground;
	delete player;
	for (int i = 0; i < 7; i++)
	{
		delete floor[i];
	}
	delete woodbox[0];
	delete woodbox[1];
	delete mousecursor;
	delete uipiece;
	delete Pieceeffect;
	delete uiPreview;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 7; j++)
		{
			delete piece_array[i][j];
		}
	}
	delete 	goal;
	delete 	goaleffect;


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

void Stage1::Update()
{
	// 最初に入力系の座標を取得する（キーボード）
	if (CInput::Get()->GetType() == CInput::HIDType::KeyBoardMouse)
	{
		DirectX::XMFLOAT2 mousemove = CInput::Get()->GetMousePos();

		mousecursor->transform->position.x = mousemove.x;
		mousecursor->transform->position.y = mousemove.y;
	}
	else // コントローラー
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

		if (CInput::Get()->GetType() == CInput::HIDType::KeyBoardMouse ? CInput::Get()->isMouseTrigger(CInput::InputType::LB1): CInput::Get()->isKeyTrigger(CInput::InputType::A))
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
				CSoundManager::GetSound()->XA_Stop(STAGE1_BGM);

				CSceneManager::get()->ChangeScene(CSceneManager::SceneState::SERECT);
				// ポーズ状態を解除する
				pauseSet = false;
			}
			else
			{
				CSceneManager::get()->ChangeStage(CSceneManager::StageState::STAGE1);
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
			//ステージ1
			if (CSceneManager::StageState::STAGE1)
			{
				// 次への処理
				if (select == 0 && !playerOut)
				{
					CSoundManager::GetSound()->XA_Play(CURSOR, 0.5f);
					CSoundManager::GetSound()->XA_Stop(STAGE1_BGM);
					CSceneManager::get()->ChangeStage(CSceneManager::StageState::STAGE2);
				}
				// もう一度の処理
				if (select == 1)
				{
					CSoundManager::GetSound()->XA_Play(CURSOR, 0.5f);
					CSceneManager::get()->ChangeStage(CSceneManager::StageState::STAGE1);
				}
				// 戻るの処理
				if (select == 2)
				{
					CSoundManager::GetSound()->XA_Play(CURSOR, 0.5f);
					CSoundManager::GetSound()->XA_Stop(STAGE1_BGM);
					CSceneManager::get()->ChangeScene(CSceneManager::SceneState::SERECT);
				}
			}
		}
	}
	// ゲームプレイ状態
	else
	{
		D_manager->Update();
		// プレイヤー　床当たり判定
		for (auto&& f : floorObj)
		{
			if (DoSquareCollision(player->collider, f))
			{
				// プレイヤー右 < 地面左 && !プレイヤー左 < 地面右
				if (player->sideflg)
				{
					if (player->transform->Right < f->transform->Left && !player->transform->Left < f->transform->Right)
					{
						player->CheckJump_Turn(f->transform);
					}
				}
				player->isGravity = false;
				break;
			}
			player->isGravity = true;
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
					continue;
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
		// ギミック同士当たり判定
		if (woodbox[0]->GetLayer() == LayerNum::PLAY_GROUND)
		{
			// ギミック同士　当たり判定
			if (woodbox[0]->transform->Bottom < woodbox[1]->transform->Top && 0.1f>fabs(woodbox[0]->transform->Left - woodbox[1]->transform->Left))
			{
				woodbox[0]->isGravity = false;
			}
			else
			{
				woodbox[0]->isGravity = true;
			}
		}
		if (woodbox[1]->GetLayer() == LayerNum::PLAY_GROUND)
		{
			if (woodbox[0]->transform->Top > woodbox[1]->transform->Bottom && 0.1f > fabs(woodbox[0]->transform->Left - woodbox[1]->transform->Left))
			{
				woodbox[1]->isGravity = false;
			}
			else
			{
				woodbox[1]->isGravity = true;
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
				if (g->isGravity)g->isGravity = true;
			}
		}
		// ゴールの当たり判定
		if (player->collider->transform->Right > goal->collider->transform->Left)
		{
			resultset = true;
		}

		if (player->transform->position.y <= -2.0f)
		{
			player->isGravity = true;
		}
		if (player->transform->position.y <= -4.0f)
		{
			playerOut = true;
			resultset = true;
		}

		if (CInput::Get()->GetType() == CInput::HIDType::KeyBoardMouse ? CInput::Get()->isMouseTrigger(CInput::InputType::RB1):CInput::Get()->isKeyTrigger(CInput::InputType::START))
		{
			pauseSet = true;
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

void Stage1::Draw()
{
	D_manager->Draw();
}

void Stage1::ReplaceObj(CGameObject* _pieceobj)
{
	for (auto&& f:floorObj)
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
		if (d->isGravity) return;
		d->transform->VertexPos();
		bool hitobj = false;

		// 選択したピースの中に子オブジェクトがあるかどうか確認する
		hitobj = _pieceobj->isCheckObject(d);

		if (hitobj)// 中にあったとき
		{
			sizecount = 1;
			for (auto&& o : gimickObj)
			{

				o->transform->VertexPos();
				// UIの中に子オブジェクトが格納されているかどうかを見る
				hitobj = uipiece->isCheckObject(o);

				if (hitobj) // UIの中に子オブジェクトが格納されているとき
				{
					work->transform = d->transform;
					d->transform = o->transform;
					o->transform = work->transform;

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

					d->transform->position = uipiece->transform->position;
					d->transform->scale = { uipiece->transform->scale.x / 2,uipiece->transform->scale.y / 2,1.0f };

					d->Setlayer(LayerNum::BLACK_OUT);
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
				hitobj = uipiece->isCheckObject(notinPiece);

				if (hitobj) // 中にあったとき
				{
					notinPiece->transform->position = _pieceobj->transform->position;
					notinPiece->transform->position.y += 0.5f;
					//notinPiece->transform->rotate = _pieceobj->transform->rotate;
					notinPiece->transform->scale = { _pieceobj->transform->scale.x * 1.0f,_pieceobj->transform->scale.y * 1.0f,1.0f };
					notinPiece->Setlayer(LayerNum::PLAY_GROUND);
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
