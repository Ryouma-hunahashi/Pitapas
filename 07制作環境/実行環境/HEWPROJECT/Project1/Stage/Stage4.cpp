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
	// ���f���쐬
	{
		// �w�i�̃��f���쐬
		center = { 0.0f, 0.0f };
		size = { 16.0f,9.0f };
		uv = { 1.0f, 1.0f };
		CDirectX::Get()->D3D_CreateSquare(center, size, uv, &vertexBufferBg);

		// �v���C���[�p�i�A�j���[�V�������鎞�ɗp����j
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

		// 1�s�[�X�T�C�Y�p ���Q�[���I�u�W�F�N�g���͑S������@�w�i�͏���
		center = { 0.0f, 0.0f };
		size = { 1.0f,1.0f };
		uv = { 1.0f, 1.0f };

		CDirectX::Get()->D3D_CreateSquare(center, size, uv, &vertexBufferPiece);
	}

	// �e�N�X�`���ǂݍ���
	{
		CDirectX::Get()->D3D_LoadTexture(L"asset/Ui_Image_PieceGrid_Ver4.png", &texturePazlePiece);			// �w�i�p�p�Y���s�[�X�e�N�X�`��
		CDirectX::Get()->D3D_LoadTexture(L"asset/stage4/pitapasu_forest_far.png", &textureBackGround);		// �w�i�e�N�X�`���i��i�j
		CDirectX::Get()->D3D_LoadTexture(L"asset/stage4/pitapasu_forest_close.png", &textureBackfrontGround);	// �w�i�e�N�X�`��(�O�i)
		CDirectX::Get()->D3D_LoadTexture(L"asset/stage4/pitapasu_forest_ground01.png", &textureFloor);		// �n�ʃe�N�X�`��
		CDirectX::Get()->D3D_LoadTexture(L"asset/stage4/pitapasu_forest_ground02.png", &textureFloormiddle);		// �n�ʃe�N�X�`��
		CDirectX::Get()->D3D_LoadTexture(L"asset/stage4/pitapasu_forest_ground04.png", &textureFloortop);		// �n�ʃe�N�X�`��
		CDirectX::Get()->D3D_LoadTexture(L"asset/player/pitapasu_sprite_Walk.png", &texturePlayer);				// �v���C���[�e�N�X�`��
		CDirectX::Get()->D3D_LoadTexture(L"asset/player/pitapasu_sprite_stay.png", (&texturePlayer_stay));
		CDirectX::Get()->D3D_LoadTexture(L"asset/player/pitapasu_sprite_jump.png", (&texturePlayer_jump));
		CDirectX::Get()->D3D_LoadTexture(L"asset/player/pitapasu_sprite_down.png", &texturePlayerDead);		// �v���C���[�i���S�j
		CDirectX::Get()->D3D_LoadTexture(L"asset/UI/Ui_Image_PeacePreview02.png", &textureUiPiece);			// �Q�[���pUI�v���r���[�e�N�X�`��
		CDirectX::Get()->D3D_LoadTexture(L"asset/UI/Ui_Image_Peace.png", &textureUiOnePiece);				// �P�s�[�X�摜�̃e�N�X�`���iUI�Ɏg�p�j
		CDirectX::Get()->D3D_LoadTexture(L"asset/gimick/wood box.png", &textureWoodBox);							// �M�~�b�N�ؔ�1�}�X
		CDirectX::Get()->D3D_LoadTexture(L"asset/gimick/half wood box.png", &texturehalfWoodBox);					// �M�~�b�N�ؔ�0.5�}�X
		CDirectX::Get()->D3D_LoadTexture(L"asset/effect/pita_goal.png", &textureEffect);					// �G�t�F�N�g
		CDirectX::Get()->D3D_LoadTexture(L"asset/effect/pita_effect.png", &textureEffectPanel);					// �G�t�F�N�g
		CDirectX::Get()->D3D_LoadTexture(L"asset/UI/Ui_Image_PeaceCursor.png", &textureUiCursor);			// Ui�J�[�\��
		CDirectX::Get()->D3D_LoadTexture(L"asset/goal_piece.png", &textureGoal);							// �S�[���p�e�N�X�`��
		CDirectX::Get()->D3D_LoadTexture(L"asset/UI/Ui_Image_LoadScreen.png", &texturefade);							// �S�[���p�e�N�X�`��
		CDirectX::Get()->D3D_LoadTexture(L"asset/UI/Ui_Image_MouseCursor.png", &textureMouseCursor);							// �S�[���p�e�N�X�`��

		// �|�[�Y�p
		CDirectX::Get()->D3D_LoadTexture(L"asset/pause/Ui_Image_PauseBackGround.png", &texturePauseBack);
		CDirectX::Get()->D3D_LoadTexture(L"asset/pause/Ui_Image_PauseButtonBand.png", &texturePauseButtonBand);
		CDirectX::Get()->D3D_LoadTexture(L"asset/pause/Ui_Text_Pause.png", &texturePauseScene);
		CDirectX::Get()->D3D_LoadTexture(L"asset/pause/Ui_Text_PauseButtonContinue.png", &texturePauseButtonContinue);
		CDirectX::Get()->D3D_LoadTexture(L"asset/pause/Ui_Text_PauseButtonRetry.png", &texturePauseButtonRetry);
		CDirectX::Get()->D3D_LoadTexture(L"asset/pause/Ui_Text_PauseButtonReturn.png", &texturePauseButtonReturn);
		CDirectX::Get()->D3D_LoadTexture(L"asset/select/Ui_Text_StageName1-4.png", &texturePauseStageName);
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
	// �I�u�W�F�N�g�̎��̉�
	{
		background = new CBackGround(vertexBufferBg, textureBackGround, LayerNum::BACK_GROUND);			// �w�i�i��i�j
		frontground = new CBackGround(vertexBufferBg, textureBackfrontGround, LayerNum::FORE_GROUND);	// �w�i�i�O�i�j
		pazle[0] = new CBackGround(vertexBufferBg, texturePazlePiece, LayerNum::MIDDLE_GROUND_BACK);		// �p�Y���w�i
		pazle[1] = new CBackGround(vertexBufferBg, texturePazlePiece, LayerNum::MIDDLE_GROUND_BACK);		// �p�Y���w�i
		player = new CPlayer(vertexBufferCharacter, texturePlayer, LayerNum::PLAY_GROUND_BACK);			// �v���C���[
		woodbox[0] = new CWoodBox(vertexBufferPiece, textureWoodBox, LayerNum::PLAY_GROUND);				// �ؔ�
		woodbox[1] = new CWoodBox(vertexBufferPiece, textureWoodBox, LayerNum::PLAY_GROUND);				// �ؔ�
		uipiecestock = new CUi(vertexBufferPiece, textureUiPiece, LayerNum::FORE_GROUND);				// UI
		uionepiece = new CUi(vertexBufferPiece, textureUiCursor, LayerNum::PLAY_GROUND_FRONT);			// �e�X�g�p�@���݂̃}�E�X�J�[�\��������p�I�u�W�F�N�g
		previewpiece = new CGameObject(vertexBufferPiece, textureUiOnePiece, LayerNum::BLACK_OUT);		// UI�̏��̃s�[�X
		for (int i = 0; i < PIECE_Y; i++)
		{
			for (int j = 0; j < PIECE_X; j++)
			{
				piece_array[i][j] = new CPiece(vertexBufferPiece, textureUiOnePiece, LayerNum::BLACK_OUT);// �e�s�[�X�̔z��
			}
		}
		for (int i = 0; i < 11; i++)
		{
			floor[i] = new CFloor(vertexBufferPiece, textureFloor, LayerNum::PLAY_GROUND_FRONT);				// �n��
		}
		work = new CGameObject(NULL, NULL, NULL);	// ����ւ���p�̒��g�ɉ����Ȃ��I�u�W�F�N�g
		uiDrawPiece = new CGameObject(vertexBufferPiece, textureUiOnePiece, LayerNum::UI);					// �G�t�F�N�g
		halfwoodbox[0] = new CWoodBox(vertexBufferPiece, texturehalfWoodBox, LayerNum::PLAY_GROUND);		// �����T�C�Y�̖ؔ�
		halfwoodbox[1] = new CWoodBox(vertexBufferPiece, texturehalfWoodBox, LayerNum::PLAY_GROUND);		// �����T�C�Y�̖ؔ�
		goal = new CGoal(vertexBufferPiece, textureGoal, LayerNum::PLAY_GROUND);						// �S�[��
		goaleffect = new CGameObject(vertexBufferEffect, textureEffect, LayerNum::PLAY_GROUND_BACK);
		Pieceeffect = new CGameObject(vertexBufferPieceEffect, textureEffectPanel, LayerNum::PLAY_GROUND_BACK);
		fade = new CGameObject(vertexBufferPiece, texturefade, LayerNum::BLACK_OUT);
		fadeblack = new CGameObject(vertexBufferPiece, texturefade, LayerNum::BLACK_OUT);
		mousecursor = new CGameObject(vertexBufferPiece, textureMouseCursor, LayerNum::BLACK_OUT);

		drawManager = new CDrawManager(0);	// �`��}�l�[�W���[

		// �|�[�Y
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

		// ���U���g
		BlackBackGround = new CUi(vertexBufferBg, textureBlackBackGround, LayerNum::BLACK_OUT);		// ���w�i
		ClearText = new CUi(vertexBufferPiece, textureClearText, LayerNum::BLACK_OUT);				// �e�L�X�g�F�N���A
		ResultPanel = new CUi(vertexBufferPiece, textureResultPanel, LayerNum::BLACK_OUT);			// ���U���g�w�i
		SceneBand = new CUi(vertexBufferPiece, textureSceneBand, LayerNum::BLACK_OUT);				// �V�[���o���h
		StageNameBand = new CUi(vertexBufferPiece, textureStageNameBand, LayerNum::BLACK_OUT);		// �X�e�[�W�o���h
		for (int i = 0; i < 3; i++)
		{
			ResultButton[i] = new CUi(vertexBufferPiece, textureButton, LayerNum::BLACK_OUT);		// �{�^��(3��)
		}
		ResultText = new CUi(vertexBufferPiece, textureResultText, LayerNum::BLACK_OUT);			// �e�L�X�g�F������
		Next = new CUi(vertexBufferPiece, textureNext, LayerNum::BLACK_OUT);						// �e�L�X�g�F����
		Retry = new CUi(vertexBufferPiece, textureRetry, LayerNum::BLACK_OUT);						// �e�L�X�g�F����������
		Return = new CUi(vertexBufferPiece, textureReturn, LayerNum::BLACK_OUT);					// �e�L�X�g�F���ǂ�
		OutText = new CUi(vertexBufferPiece, textureOut, LayerNum::BLACK_OUT);						// �e�L�X�g�F���ǂ�
	}

	// �������W�ݒ�
	{
		// �e1�s�[�X�摜
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
		// �w�i�摜�i��i�j
		{
			background->transform->scale = { OBJECT_X * 32.0f,OBJECT_Y * 9.0f,1.0f };
			background->transform->position = { 8.0f,0.0f,1.0f };
		}
		// �w�i�摜�i�O�i�j
		{
			frontground->transform->scale = { OBJECT_X * 32.0f,OBJECT_Y * 9.0f, 1.0f };
			frontground->transform->position = { 8.0f, 0.0f, 1.0f };
		}
		// �w�i�p�Y���s�[�X�摜
		{
			pazle[0]->transform->scale = { 1.035f,1.0f,1.0f };
			pazle[1]->transform->scale = { 1.035f,1.0f,1.0f };
		}
		// �n�ʉ摜
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
		// UI�ɒu���p�Y���̃s�[�X�摜
		{
			previewpiece->transform->position = { -6.5f,3.3f,1.0f };
			previewpiece->transform->scale = { 2.0f,2.0f,1.0f };
		}
		// �G�t�F�N�g�摜�i�e�X�g�j
		{
			//effect->transform->position = { 0,0,0.5f };
			//effect->transform->scale = { 0.1,0.1,0.8f };
		}
		// UI�s�[�X�u����摜
		{
			uipiecestock->transform->position = { -6.5f,3.3f, 0.15f };
			uipiecestock->transform->scale = { 4.0f,4.0f,1.0f };
		}
		// �v���C���[
		{
			// �A�j���[�V�����ݒ�
			player->anim = new CAnimation(3, 3);
			player->anim->SetPattern(CAnimation::PLAYER);
			player->anim->animSpeed = 0.16f;
			// �v���C���[�̃T�C�Y����
			player->transform->scale = { -2.0f,2.0f,1.0f };
			player->transform->position = { -6.8f,0.1f,1.0f };
	

			player->SetPlayerTexture(texturePlayer_stay);
			player->SetPlayerTexture(texturePlayer);
			player->SetPlayerTexture(texturePlayer_jump);
			player->SetPlayerTexture(texturePlayerDead);
		}
		// �ؔ��i1�}�X�T�C�Y�j
		{
			woodbox[0]->transform->position = piece_array[2][1]->transform->position;
			woodbox[0]->transform->position.y += 0.5f;
			woodbox[0]->transform->scale = { 2.2f,2.2f,1.0f };

			woodbox[1]->transform->position = piece_array[0][4]->transform->position;
			woodbox[1]->transform->position.y += 0.5f;
			woodbox[1]->transform->scale = { 2.2f,2.2f,1.0f };

		}
		// �ؔ��i0.5�}�X�T�C�Y�j
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
		// �S�[���摜�@�e�X�g�Ō��ɂȂ��Ă���
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
		// �G�t�F�N�g
		{
			Pieceeffect->anim = new CAnimation(5, 7);
			Pieceeffect->anim->SetPattern(CAnimation::FX_54_0);
			Pieceeffect->anim->isPlaying = false;
			Pieceeffect->anim->animSpeed = 0.9f;

			Pieceeffect->transform->position = { 0.45f,1.1f,1.0f };
			Pieceeffect->transform->scale = { 4.0f,4.0f,1.0f };
		}
		// �t�F�[�h
		{
			fade->transform->scale = { 16.0f, 9.0f, 1.0f };
			fadeblack->transform->scale = { 17.0f,17.0f,1.0f };
		}

		uionepiece->transform->scale = { 2.0f,2.0f,1.0f };
		uionepiece->transform->position = piece_array[0][0]->transform->position;

		mousecursor->transform->rotate.z = 40.0f;
		mousecursor->transform->scale = { 1.5f,1.5f,1.0f };

		// �|�[�Y�p�ݒ�
		{
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



	// �e��ϒ��z��Ɋi�[
	{

		for (int i = 0; i < 11; i++)
		{
			floorObj.push_back(floor[i]);
		}

		// �q�I�u�W�F�N�g���q�I�u�W�F�N�g�p�ϒ��z��Ɋi�[����
		gimickObj.push_back(woodbox[0]);
		gimickObj.push_back(woodbox[1]);
		gimickObj.push_back(halfwoodbox[0]);
		gimickObj.push_back(halfwoodbox[1]);

	}
	// �`�悷��I�u�W�F�N�g��z��Ɋi�[����
	{
		drawManager->AddObject(pazle[0]);					// �w�i�p�Y��
		drawManager->AddObject(pazle[1]);					// �w�i�p�Y��
		drawManager->AddObject(background);				// �w�i�i��i�j
		drawManager->AddObject(frontground);			// �w�i�i�O�i�j
		drawManager->AddObject(uionepiece);				// ���݃s�[�X�̏ꏊ��\������Ui
		drawManager->AddObject(player->collider);		// �v���C���[�R���C�_�[
		drawManager->AddObject(player);					// �v���C���[
		//drawManager->AddObject(woodbox[0]->collider);		// �ؔ��i1�s�[�X�j�R���C�_�[
		//drawManager->AddObject(woodbox[1]->collider);		// �ؔ��i1�s�[�X�j�R���C�_�[
		//drawManager->AddObject(halfwoodbox->collider);	// �ؔ��i0.5�s�[�X�j�R���C�_�[
		drawManager->AddObject(halfwoodbox[0]);			// �ؔ��i0.5�s�[�X�j
		drawManager->AddObject(halfwoodbox[1]);			// �ؔ��i0.5�s�[�X�j
		drawManager->AddObject(uipiecestock);			// Ui�ۑ�����ꏊ
		drawManager->AddObject(woodbox[0]);				// �ؔ��i1�s�[�X�j
		drawManager->AddObject(woodbox[1]);				// �ؔ��i1�s�[�X�j
		drawManager->AddObject(goaleffect);					// �G�t�F�N�g
		drawManager->AddObject(previewpiece);
		drawManager->AddObject(Pieceeffect);


		for (int i = 0; i < PIECE_Y; i++)
		{
			for (int j = 0; j < PIECE_X; j++)
			{
				drawManager->AddObject(piece_array[i][j]); // �s�[�X�̔z��
				drawManager->AddObject(piece_array[i][j]->collider); // �s�[�X�̔z��
			}
		}

		for (int i = 0; i < 11; i++)
		{
			drawManager->AddObject(floor[i]);			// �n��
			drawManager->AddObject(floor[i]->collider); // �n�ʃR���C�_�[
		}

		drawManager->AddObject(goal);			// �S�[��
		drawManager->AddObject(goal->collider);	// �S�[���R���C�_�[	
		// 
		// �|�[�Y���
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
		// ���U���g���
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

	}

	// �`�悵�Ȃ������I�t�ɂ��Ă���

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
		floor[i]->collider->isDraw = false; // �n�ʃR���C�_�[
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

			if (CInput::Get()->GetType() == CInput::HIDType::KeyBoardMouse ? CInput::Get()->isMouseTrigger(CInput::InputType::LB1) : CInput::Get()->isKeyTrigger(CInput::InputType::A))
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
					CSoundManager::GetSound()->XA_Stop(STAGE4_BGM);

					CSceneManager::get()->ChangeScene(CSceneManager::SceneState::SERECT);
					// �|�[�Y��Ԃ���������
					pauseSet = false;
				}
				else
				{
					CSceneManager::get()->ChangeStage(CSceneManager::StageState::STAGE4);
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
				// ���ւ̏���
				if (select == 0 && !playerOut)
				{
					CSoundManager::GetSound()->XA_Play(CURSOR, 0.5f);
					CSoundManager::GetSound()->XA_Stop(STAGE4_BGM);
					CSceneManager::get()->ChangeStage(CSceneManager::StageState::STAGE1);
				}
				// ������x�̏���
				if (select == 1)
				{
					CSoundManager::GetSound()->XA_Play(CURSOR, 0.5f);
					CSceneManager::get()->ChangeStage(CSceneManager::StageState::STAGE4);
				}
				// �߂�̏���
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
			 
			// �v���C���[�@�������蔻��
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

			// �M�~�b�N���m�̓����蔻��
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
				}
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

			// �S�[���̓����蔻��
			if (DoSquareCollision(goal->collider,player->collider))
			{
				resultset = true;
			}

			// �|�[�Y��ʑI������Ƃ�
			if (CInput::Get()->GetType() == CInput::HIDType::KeyBoardMouse ? CInput::Get()->isMouseTrigger(CInput::InputType::RB1) : CInput::Get()->isKeyTrigger(CInput::InputType::START))
			{
				pauseSet = true;
			}

			// ���ȉ��̍��W�ɍs������Q�[���I�[�o�[�ɂ���
			if (player->transform->position.y <= -4.0f)
			{
				playerOut = true;
				resultset = true;
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
	// ���������s�[�X�̒��Ɉړ��ł���q�I�u�W�F�N�g�����邩�ǂ����𒲂ׂ�
	for (auto&& d : gimickObj)
	{
		d->transform->VertexPos();
		bool hitobj = false;

		// �I�������s�[�X�̒��Ɏq�I�u�W�F�N�g�����邩�ǂ����m�F����
		hitobj = _pieceobj->isCheckObject(d);

		if (hitobj)// ���ɂ������Ƃ�
		{
			for (auto&& o : gimickObj)
			{
				o->transform->VertexPos();
				// UI�̒��ɂ��邩�q�I�u�W�F�N�g���i�[����Ă��邩�ǂ���������
				hitobj = previewpiece->isCheckObject(o);

				if (hitobj) // UI�̒��Ɏq�I�u�W�F�N�g���i�[����Ă���Ƃ�
				{
					// �I�u�W�F�N�g���m�����ւ���
					// �Q�[����ʃI�u�W�F�N�g��ۑ�����
					work->transform->position = d->transform->position;
					//// UI�̒��̃I�u�W�F�N�g���Q�[����ʂɈړ�����
					d->transform->position = o->transform->position;
					//// �ۑ������I�u�W�F�N�g��UI�̒��ɓ����
					o->transform->position = _pieceobj->transform->position;

					// �I�u�W�F�N�g�̑傫����ύX����
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
				else // �i�[����Ă��Ȃ����
				{
					// �i�[����Ă��镪�̃T�C�Y�`�F�b�N����
					if (gimickObj.size() != sizecount)
					{
						sizecount++;
						continue;
					}
					// ���������Ă��Ȃ����UI�̏��Ɏq�I�u�W�F�N�g��z�u����
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
		else // ���ɂȂ������Ƃ�
		{
			// �T�C�Y���I����ĂȂ���Ώ������X�L�b�v������
			if (gimickObj.size() != sizecount) { sizecount++; continue; }
			sizecount = 1;
			for (auto&& notinPiece : gimickObj)
			{
				// UI�̒��Ɏq�I�u�W�F�N�g�����邩�ǂ������m�F����
				hitobj = previewpiece->isCheckObject(notinPiece);

				if (hitobj) // ���ɂ������Ƃ�
				{
					notinPiece->transform->position = _pieceobj->transform->position;
					//notinPiece->transform->rotate = _pieceobj->transform->rotate;
					notinPiece->transform->scale = { _pieceobj->transform->scale.x * 1.0f,_pieceobj->transform->scale.y * 1.0f,1.0f };
					notinPiece->Setlayer(LayerNum::PLAY_GROUND);
					if (notinPiece->ishalf)notinPiece->transform->scale.y /= 2;
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
