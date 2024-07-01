#include "Stage1.h"

#include "CSoundManager.h"

Stage1::Stage1()
{
	// ���f���쐬
	{
		// �w�i���f���쐬�i�摜�S�̂�\�����鎞�Ɏg�p����j
		center = { 0.0f, 0.0f };
		size = { 1.0f,1.0f };
		uv = { 1.0f, 1.0f };
		CDirectX::Get()->D3D_CreateSquare(center, size, uv, &vertexBufferBg);

		// �v���C���[���f���쐬
		uv = { 0.33f, 0.33f };
		CDirectX::Get()->D3D_CreateSquare(center, size, uv, &vertexBufferPlayer);

		// �S�[���G�t�F�N�g���f���쐬
		uv = { (1.0f / 10), (1.0f / 6) };
		CDirectX::Get()->D3D_CreateSquare(center, size, uv, &vertexBufferGoalEffect);

		// �s�[�X�G�t�F�N�g���f���쐬
		uv = { 1.0f / 5,1.0f / 7 };
		CDirectX::Get()->D3D_CreateSquare(center, size, uv, &vertexBufferPieceEffect);
	}

	// �e�N�X�`���ǂݍ���
	{
		CDirectX::Get()->D3D_LoadTexture(L"asset/stage1/pitapasu_village_far.png", &textureBackGround);		// �w�i�e�N�X�`���i��i�j
		CDirectX::Get()->D3D_LoadTexture(L"asset/stage1/pitapasu_village_close.png", &textureFrontGround);	// �w�i�e�N�X�`��(�O�i)
		CDirectX::Get()->D3D_LoadTexture(L"asset/Ui_Image_PieceGrid_Ver4.png", &textureBackPazleGround);	// �w�i�p�p�Y���s�[�X�e�N�X�`��
		CDirectX::Get()->D3D_LoadTexture(L"asset/player/pitapasu_sprite_Walk.png", &texturePlayerWalk);		// �v���C���[�i�����j
		CDirectX::Get()->D3D_LoadTexture(L"asset/player/pitapasu_sprite_stay.png", &texturePlayerStay);		// �v���C���[�i�ҋ@�j
		CDirectX::Get()->D3D_LoadTexture(L"asset/player/pitapasu_sprite_jump.png", &texturePlayerJump);		// �v���C���[�i�W�����v�j
		CDirectX::Get()->D3D_LoadTexture(L"asset/player/pitapasu_sprite_down.png", &texturePlayerDead);		// �v���C���[�i���S�j
		CDirectX::Get()->D3D_LoadTexture(L"asset/stage1/pitapasu_village_ground01.png", &textureFloorTop);	// �n�ʃe�N�X�`��
		CDirectX::Get()->D3D_LoadTexture(L"asset/gimick/wood box.png", &textureWoodBox);					// �M�~�b�N�ؔ�1�}�X
		CDirectX::Get()->D3D_LoadTexture(L"asset/gimick/half wood box.png", &textureHalfWoodBox);			// �M�~�b�N�ؔ�0.5�}�X
		CDirectX::Get()->D3D_LoadTexture(L"asset/UI/Ui_Image_MouseCursor.png", &textureMouseCursor);		// �}�E�X�p�e�N�X�`��
		CDirectX::Get()->D3D_LoadTexture(L"asset/UI/Ui_Image_Peace.png", &textureUiPiece);					// �P�s�[�X�摜�̃e�N�X�`���iUI�Ɏg�p�j
		CDirectX::Get()->D3D_LoadTexture(L"asset/UI/Ui_Image_PeacePreview02.png", &textureUiPreview);		// �P�s�[�X�摜�̃e�N�X�`���iUI�Ɏg�p�j
		CDirectX::Get()->D3D_LoadTexture(L"asset/effect/pita_effect.png", &textureEffectPiece);				// �s�[�X�G�t�F�N�g
		CDirectX::Get()->D3D_LoadTexture(L"asset/goal_piece.png", &textureGoal);							// �S�[���p�e�N�X�`��
		CDirectX::Get()->D3D_LoadTexture(L"asset/UI/Ui_Image_LoadScreen.png", &texturefade);				// �t�F�[�h�p�e�N�X�`��
		CDirectX::Get()->D3D_LoadTexture(L"asset/effect/pita_goal.png", &textureEffectGoal);				// �S�[���G�t�F�N�g


		// �|�[�Y�p
		CDirectX::Get()->D3D_LoadTexture(L"asset/pause/Ui_Image_PauseBackGround.png", &texturePauseBack);
		CDirectX::Get()->D3D_LoadTexture(L"asset/pause/Ui_Image_PauseButtonBand.png", &texturePauseButtonBand);
		CDirectX::Get()->D3D_LoadTexture(L"asset/pause/Ui_Text_Pause.png", &texturePauseScene);
		CDirectX::Get()->D3D_LoadTexture(L"asset/pause/Ui_Text_PauseButtonContinue.png", &texturePauseButtonContinue);
		CDirectX::Get()->D3D_LoadTexture(L"asset/pause/Ui_Text_PauseButtonRetry.png", &texturePauseButtonRetry);
		CDirectX::Get()->D3D_LoadTexture(L"asset/pause/Ui_Text_PauseButtonReturn.png", &texturePauseButtonReturn);
		CDirectX::Get()->D3D_LoadTexture(L"asset/select/Ui_Text_StageName1-1.png", &texturePauseStageName);
		CDirectX::Get()->D3D_LoadTexture(L"asset/select/Ui_Image_SelectSceneBand.png", &texturePauseSceneBand);

		// ���U���g�p
		CDirectX::Get()->D3D_LoadTexture(L"asset/result/Ui_Image_BlackBackGround.png", &textureBlackBackGround);	// ���w�i
		CDirectX::Get()->D3D_LoadTexture(L"asset/result/Ui_Text_ClearText.png", &textureClearText);				// �e�L�X�g�F�N���A
		CDirectX::Get()->D3D_LoadTexture(L"asset/result/Ui_Image_ResultPanel .png", &textureResultPanel);			// ���U���g�p�l��
		CDirectX::Get()->D3D_LoadTexture(L"asset/select/Ui_Image_SelectSceneBand.png", &textureSceneBand);		// �V�[���o���h
		CDirectX::Get()->D3D_LoadTexture(L"asset/select/Ui_Image_StageNameBand.png", &textureStageNameBand);		// �X�e�[�W�o���h
		CDirectX::Get()->D3D_LoadTexture(L"asset/result/Ui_Image_ResultButtonBand.png", &textureButton);			// ���U���g�{�^��
		CDirectX::Get()->D3D_LoadTexture(L"asset/result/Ui_Text_SceneResult.png", &textureResultText);			// �e�L�X�g�F������
		CDirectX::Get()->D3D_LoadTexture(L"asset/result/Ui_Text_Next.png", &textureNext);							// �e�L�X�g�F����
		CDirectX::Get()->D3D_LoadTexture(L"asset/result/Ui_Text_Retry.png", &textureRetry);						// �e�L�X�g�F����������
		CDirectX::Get()->D3D_LoadTexture(L"asset/result/Ui_Text_Return.png", &textureReturn);						// �e�L�X�g�F���ǂ�
		CDirectX::Get()->D3D_LoadTexture(L"asset/result/Ui_Text_GameOverText.png", &textureOut);						// �e�L�X�g�F���ǂ�

	}

	// �I�u�W�F�N�g����
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
		goal = new CGoal(vertexBufferBg, textureGoal, LayerNum::PLAY_GROUND);						// �S�[��
		goaleffect = new CGameObject(vertexBufferGoalEffect, textureEffectGoal, LayerNum::PLAY_GROUND_BACK);
		work = new CGameObject(NULL, NULL, NULL);
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 7; j++)
			{
				piece_array[i][j] = new CPiece(vertexBufferBg, textureUiPiece, LayerNum::PLAY_GROUND_BACK);
			}
		}

		// �`��}�l�[�W���[�����̉�����
		D_manager = new CDrawManager(0);

		fade = new CGameObject(vertexBufferBg, texturefade, LayerNum::BLACK_OUT);
		fadeblack = new CGameObject(vertexBufferBg, texturefade, LayerNum::BLACK_OUT);

		// �|�[�Y
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

		// ���U���g
		BlackBackGround = new CUi(vertexBufferBg, textureBlackBackGround, LayerNum::BLACK_OUT);		// ���w�i
		ClearText = new CUi(vertexBufferBg, textureClearText, LayerNum::BLACK_OUT);				// �e�L�X�g�F�N���A
		ResultPanel = new CUi(vertexBufferBg, textureResultPanel, LayerNum::BLACK_OUT);			// ���U���g�w�i
		SceneBand = new CUi(vertexBufferBg, textureSceneBand, LayerNum::BLACK_OUT);				// �V�[���o���h
		StageNameBand = new CUi(vertexBufferBg, textureStageNameBand, LayerNum::BLACK_OUT);		// �X�e�[�W�o���h
		for (int i = 0; i < 3; i++)
		{
			ResultButton[i] = new CUi(vertexBufferBg, textureButton, LayerNum::BLACK_OUT);		// �{�^��(3��)
		}
		ResultText = new CUi(vertexBufferBg, textureResultText, LayerNum::BLACK_OUT);			// �e�L�X�g�F������
		Next = new CUi(vertexBufferBg, textureNext, LayerNum::BLACK_OUT);						// �e�L�X�g�F����
		Retry = new CUi(vertexBufferBg, textureRetry, LayerNum::BLACK_OUT);						// �e�L�X�g�F����������
		Return = new CUi(vertexBufferBg, textureReturn, LayerNum::BLACK_OUT);					// �e�L�X�g�F���ǂ�
		OutText = new CUi(vertexBufferBg, textureOut, LayerNum::BLACK_OUT);						// �e�L�X�g�F���ǂ�

	}

	// ���W�ʒu�ݒ�
	{
		// �w�i�ݒ�
		{
			background[0]->transform->scale = { 32.0f,9.0f,1.0f };
			background[1]->transform->scale = { 32.0f,9.0f,1.0f };
			background[0]->transform->position.x = 8.0f;
			background[1]->transform->position.x = 8.0f;
			pazlebackground->transform->scale = { 16.7f,9.1f,1.0f };
		}
		// �v���C���[�ݒ�
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
		// �n�ʐݒ�
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
		// �ؔ��ݒ�
		{
			woodbox[0]->transform->scale = {2.2f,2.2f,1.0f};
			woodbox[1]->transform->scale = {2.2f,2.2f,1.0f};

			woodbox[1]->transform->position.x = floor[0]->transform->position.x;
			woodbox[0]->transform->position.y -= 1.0f;
			woodbox[1]->transform->position.y -= 1.0f;
		}
		// �}�E�X�J�[�\��
		{
			mousecursor->transform->rotate.z = 40.0f;
			mousecursor->transform->scale = { 1.5f,1.5f,1.0f };
		}
		// Ui�s�[�X
		{
			uiPreview->transform->position = { -6.5f,3.3f,1.0f };
			uiPreview->transform->scale = { 4.0f,4.0f,1.0f };
			uipiece->transform->position = { -6.5f,3.3f,1.0f };
			uipiece->transform->scale = { 2.0f,2.0f,1.0f };
		}
		// �e�s�[�X�ʒu�ۑ��ꏊ
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
		// �s�[�X�G�t�F�N�g
		{
			Pieceeffect->transform->scale = { 10.0f,10.0f,1.0f };
			Pieceeffect->anim = new CAnimation(5, 7);
			Pieceeffect->anim->SetPattern(CAnimation::FX_0_19);
			Pieceeffect->anim->animSpeed = 0.6f;
			Pieceeffect->anim->isPlaying = false;
		}
		// �S�[��
		{
			goal->transform->scale = { 2.5f,2.5f,1.0f };
			goal->transform->position = { 7.0f,-1.2f,1.0f };
			goaleffect->transform = goal->transform;
			goaleffect->transform->scale = { 2.7f,2.7f,1.0f };
			goaleffect->anim = new CAnimation(10, 6);
			goaleffect->anim->animSpeed = 0.4f;
			goaleffect->anim->SetPattern(CAnimation::FX_0_54);
		}

		// �t�F�[�h�p
		{
			fade->transform->scale = { 16.0f, 9.0f, 1.0f };
			fadeblack->transform->scale = { 17.0f,17.0f,1.0f };
		}

		// �|�[�Y�p�ݒ�
		{
			{
				pauseback->transform->scale = { 16.0f,9.0f,1.0f };
			}

			// �{�^���̌��
			{
				pausebuttonband[0]->transform->position = { -3.5f,0.9f,1.0f };
				pausebuttonband[0]->transform->scale = { 10.0f,10.0f,1.0f };
				pausebuttonband[1]->transform->position = { -3.5f,-0.9f,1.0f };
				pausebuttonband[1]->transform->scale = { 10.0f,10.0f,1.0f };
				pausebuttonband[2]->transform->position = { -3.5f,-2.8f,1.0f };
				pausebuttonband[2]->transform->scale = { 10.0f,10.0f,1.0f };
			}
			// �{�^��
			{
				pausebutton[0]->transform->position = { -3.0f,0.9f,1.0f };
				pausebutton[0]->transform->scale = { 10.0f,10.0f,1.0f };
				pausebutton[1]->transform->position = { -3.0f,-0.9f,1.0f };
				pausebutton[1]->transform->scale = { 10.0f,10.0f,1.0f };
				pausebutton[2]->transform->position = { -3.0f,-2.8f,1.0f };
				pausebutton[2]->transform->scale = { 10.0f,10.0f,1.0f };
			}
			// ��~�� ���
			{
				pausetextband->transform->position = { -4.7f,3.5f,1.0f };
				pausetextband->transform->scale = { 7.0f,7.0f,1.0f };
				pausetext->transform->position = { -4.4f,3.5f,1.0f };
				pausetext->transform->scale = { 12.0f,12.0f,1.0f };
			}
			// �X�e�[�W��
			{
				pausestagename->transform->position = { -4.0f,2.3f,1.0f };
				pausestagename->transform->scale = { 11.0f,11.0f,1.0f };
			}

		}
		// ���U���g�p�ݒ�
		{
			// �w�i������
			{
				BlackBackGround->transform->scale = { 16.0f,9.0f,1.0f };
			}
			// �N���A
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
			// ����
			{
				Next->transform->scale = { 7.0f,7.0f,1.0f };
				Next->transform->position = { -5.2f,-2.5f,1.0f };
				Next->materialDiffuse.w = 0.0f;
			}
			// ���g���C
			{
				Retry->transform->scale = { 6.5f,6.5f,1.0f };
				Retry->transform->position = { 0.0f,-2.5f,1.0f };
				Retry->materialDiffuse.w = 0.0f;
			}
			// �߂�
			{
				Return->transform->scale = { 7.0f,7.0f,1.0f };
				Return->transform->position = { 5.5f,-2.6f,1.0f };
				Return->materialDiffuse.w = 0.0f;
			}
			// ����
			{
				ResultText->transform->position = { -5.0f,3.5f,1.0f };
				ResultText->transform->scale = { 7.0f,7.0f,1.0f };
			}
			//���ʂ̃o���h 
			{
				StageNameBand->transform->position = { -5.5f,3.5f,1.0f };
				StageNameBand->transform->scale = { 7.0f,7.0f,1.0f };
			}
			// �{�^���̃o���h
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

	// �ϒ��z��Ɋi�[����
	for (int i = 0; i < 7; i++)
	{
		floorObj.push_back(floor[i]->collider);
	}

	gimickObj.push_back(woodbox[0]);
	gimickObj.push_back(woodbox[1]);

	// �`�悷�鎞�Ɏg�p����N���X�Ɋi�[����
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

		// �|�[�Y���
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
		// ���U���g���
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

	// �����蔻�肾���Ɏg�p���邽�ߕ`��͂����ɂ���
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
	// �|�[�Y�n����U�`����������Ƃɂ���
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
	// ���U���g�n����U�`�����
	{
		BlackBackGround->isDraw = false;
		StageNameBand->isDraw = false;
		ResultText->isDraw = false;
		OutText->isDraw = false;
		D_manager->Update();
	}

	// BGM�Đ�
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
	// �ŏ��ɓ��͌n�̍��W���擾����i�L�[�{�[�h�j
	if (CInput::Get()->GetType() == CInput::HIDType::KeyBoardMouse)
	{
		DirectX::XMFLOAT2 mousemove = CInput::Get()->GetMousePos();

		mousecursor->transform->position.x = mousemove.x;
		mousecursor->transform->position.y = mousemove.y;
	}
	else // �R���g���[���[
	{
		DirectX::XMFLOAT2 pos = CInput::Get()->GetControllerStick();

		mousecursor->transform->position.x += (pos.x / 10);
		mousecursor->transform->position.y += (pos.y / 10);
	}

	// �t�F�[�h���
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
	// �|�[�Y���
	else if (pauseSet && !fadeout)	// �|�[�Y���
	{
		// �|�[�Y��ʂ�`�悷��
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
				// �|�[�Y��ʂ�����
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
				// �|�[�Y��Ԃ���������
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
				// �|�[�Y��Ԃ���������
				pauseSet = false;
			}
			else
			{
				CSceneManager::get()->ChangeStage(CSceneManager::StageState::STAGE1);
				// �|�[�Y��Ԃ���������
				pauseSet = false;
			}
		}
		//player->idle_flg = true;
	}
	// ���U���g���
	else if (resultset)
	{
		//drawManager->Update();
		BlackBackGround->isDraw = true;
		StageNameBand->isDraw = true;
		if (playerOut)
		{
			player->Update();
			OutText->isDraw = true;

			// �N���A�̕���������̕����T�C�Y�����߂����ǂ���ɂȂ��Ă�����
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

			// �N���A�̕���������̕����T�C�Y�����߂����ǂ���ɂȂ��Ă�����
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

		// ����
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
		// ����������
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
		// ���ǂ�
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
			//�X�e�[�W1
			if (CSceneManager::StageState::STAGE1)
			{
				// ���ւ̏���
				if (select == 0 && !playerOut)
				{
					CSoundManager::GetSound()->XA_Play(CURSOR, 0.5f);
					CSoundManager::GetSound()->XA_Stop(STAGE1_BGM);
					CSceneManager::get()->ChangeStage(CSceneManager::StageState::STAGE2);
				}
				// ������x�̏���
				if (select == 1)
				{
					CSoundManager::GetSound()->XA_Play(CURSOR, 0.5f);
					CSceneManager::get()->ChangeStage(CSceneManager::StageState::STAGE1);
				}
				// �߂�̏���
				if (select == 2)
				{
					CSoundManager::GetSound()->XA_Play(CURSOR, 0.5f);
					CSoundManager::GetSound()->XA_Stop(STAGE1_BGM);
					CSceneManager::get()->ChangeScene(CSceneManager::SceneState::SERECT);
				}
			}
		}
	}
	// �Q�[���v���C���
	else
	{
		D_manager->Update();
		// �v���C���[�@�������蔻��
		for (auto&& f : floorObj)
		{
			if (DoSquareCollision(player->collider, f))
			{
				// �v���C���[�E < �n�ʍ� && !�v���C���[�� < �n�ʉE
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
		// �M�~�b�N�@�v���C���[�����蔻��
		for (auto&& g : gimickObj)
		{
			if (DoSquareCollision(player->collider, g))
			{
				// �M�~�b�N�̒��ɂ����ԂɂȂ����ꍇ�@���܂�������Ƃ��Ď��s���U���g�Ɉڍs����
				if (player->transform->position.y + 0.7f > g->transform->Bottom && player->transform->Top < g->transform->Top && player->collider->transform->Right < g->transform->Right && player->collider->transform->Left > g->transform->Left)
				{
					player->dead_flg = true;
					playerOut = true;
					resultset = true;
				}
				// �v���C���[�E �M�~�b�N�E && �v���C���[���E���� && 
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
		// �M�~�b�N���m�����蔻��
		if (woodbox[0]->GetLayer() == LayerNum::PLAY_GROUND)
		{
			// �M�~�b�N���m�@�����蔻��
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
		// ���@�M�~�b�N�����蔻��
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
		// �S�[���̓����蔻��
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
		// ����ւ�����
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
	// ���������s�[�X�̒��Ɉړ��ł���q�I�u�W�F�N�g�����邩�ǂ����𒲂ׂ�
	for (auto&& d : gimickObj)
	{
		if (d->isGravity) return;
		d->transform->VertexPos();
		bool hitobj = false;

		// �I�������s�[�X�̒��Ɏq�I�u�W�F�N�g�����邩�ǂ����m�F����
		hitobj = _pieceobj->isCheckObject(d);

		if (hitobj)// ���ɂ������Ƃ�
		{
			sizecount = 1;
			for (auto&& o : gimickObj)
			{

				o->transform->VertexPos();
				// UI�̒��Ɏq�I�u�W�F�N�g���i�[����Ă��邩�ǂ���������
				hitobj = uipiece->isCheckObject(o);

				if (hitobj) // UI�̒��Ɏq�I�u�W�F�N�g���i�[����Ă���Ƃ�
				{
					work->transform = d->transform;
					d->transform = o->transform;
					o->transform = work->transform;

					o->Setlayer(LayerNum::PLAY_GROUND);
					d->Setlayer(LayerNum::UI);

					return;
				}
				else // �i�[����Ă��Ȃ����
				{
					// �i�[����Ă��镪�̃T�C�Y�`�F�b�N����
					if (gimickObj.size() != sizecount)
					{
						sizecount++;
						continue;
					}
					// ���������Ă��Ȃ����UI�̏��Ɏq�I�u�W�F�N�g��z�u����

					d->transform->position = uipiece->transform->position;
					d->transform->scale = { uipiece->transform->scale.x / 2,uipiece->transform->scale.y / 2,1.0f };

					d->Setlayer(LayerNum::BLACK_OUT);
					return;
				}
			}
		}
		else // ���ɂȂ������Ƃ�
		{
			// �T�C�Y���I����ĂȂ���Ώ������X�L�b�v������
			if (gimickObj.size() != sizecount) { sizecount++; continue; }
			sizecount = 1;
			for (auto&& notinPiece : gimickObj)
			{
				// UI�̒��Ɏq�I�u�W�F�N�g�����邩�ǂ������m�F����
				hitobj = uipiece->isCheckObject(notinPiece);

				if (hitobj) // ���ɂ������Ƃ�
				{
					notinPiece->transform->position = _pieceobj->transform->position;
					notinPiece->transform->position.y += 0.5f;
					//notinPiece->transform->rotate = _pieceobj->transform->rotate;
					notinPiece->transform->scale = { _pieceobj->transform->scale.x * 1.0f,_pieceobj->transform->scale.y * 1.0f,1.0f };
					notinPiece->Setlayer(LayerNum::PLAY_GROUND);
					notinPiece->isGravity = true;
					return;
				}
				else // ���ɖ��������Ƃ�
				{
					// �S���m�F����܂Ŋm�F����
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
