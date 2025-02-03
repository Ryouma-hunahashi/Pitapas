#include "CTitleScene.h"
#include "CSceneManager.h"
#include "CSoundManager.h"
#include "CInput.h"
#include "CGame.h"

CTitleScene::CTitleScene()
{
	// �w�i�̃��f���쐬
	center = { 0.0f, 0.0f };
	size = { 16.0f, 9.0f };
	uv = { 1.0f, 1.0f };
	CDirectX::Get()->D3D_CreateSquare(center, size, uv, &vertexBufferBg);

	size = { 1.0f,1.0f };
	CDirectX::Get()->D3D_CreateSquare(center, size, uv, &vertexBufferUi);

	// �w�i�̃e�N�X�`���ǂݍ���
	CDirectX::Get()->D3D_LoadTexture(L"asset/title/pitapasu_title.png", &textureBackGround);
	CDirectX::Get()->D3D_LoadTexture(L"asset/title/titleLogo.png", &textureTitleLogo);
	CDirectX::Get()->D3D_LoadTexture(L"asset/title/Ui_Text_PressAnyButton.png", &textureStartUi);
	CDirectX::Get()->D3D_LoadTexture(L"asset/title/Ui_Text_Start.png", &textureStart);
	CDirectX::Get()->D3D_LoadTexture(L"asset/title/Ui_Text_Exit.png", &textureExit);
	CDirectX::Get()->D3D_LoadTexture(L"asset/title/Ui_Image_StartExit.png", &textureBackText);
	CDirectX::Get()->D3D_LoadTexture(L"asset/UI/Ui_Image_MouseCursor.png", &textureCursor);

	 
	// �w�i�̎��̉�
	backGround = new CBackGround(vertexBufferBg, textureBackGround,LayerNum::BACK_GROUND);
	titleLogo = new CUi(vertexBufferUi, textureTitleLogo, LayerNum::PLAY_GROUND);
	uiStartLogo = new CUi(vertexBufferUi, textureStartUi, LayerNum::UI);
	uistart = new CUi(vertexBufferUi, textureStart, LayerNum::UI);
	uiexit = new CUi(vertexBufferUi, textureExit, LayerNum::UI);
	uibackLogo[0] = new CUi(vertexBufferUi, textureBackText, LayerNum::UI);
	uibackLogo[1] = new CUi(vertexBufferUi, textureBackText, LayerNum::UI);
	uicursor = new CUi(vertexBufferUi, textureCursor, LayerNum::UI);

	drawmanager = new CDrawManager(0);

	// �^�C�g�����S
	{
		titleLogo->transform->scale = { 8.0f,3.0f,1.0f };
		titleLogo->transform->position.y = 2.0f;
	}
	// �u�{�^���������ĂˁvUi
	{
		uiStartLogo->transform->scale = { 10.0f,10.0f,1.0f };
		uiStartLogo->transform->position.y = -2.0f;
	}
	// �u�͂��߂�vUi
	{
		uistart->transform->scale = { 7.0f,7.0f,1.0f };
		uistart->transform->position.y = -1.0f;
		uistart->collider->transform->scale.y = 0.3f;

	}
	// �u�����vUi
	{
		uiexit->transform->scale = { 7.0f,7.0f,1.0f };
		uiexit->transform->position.y = -3.0f;
	}
	// Ui�̌��ɂ��������w�i
	{
		uibackLogo[0]->transform = uiexit->transform;
		uibackLogo[1]->transform = uistart->transform;
	}
	uicursor->transform->rotate.z = 40.0f;


	drawmanager->AddObject(backGround);
	drawmanager->AddObject(titleLogo);
	drawmanager->AddObject(uiStartLogo);
	drawmanager->AddObject(uibackLogo[0]);
	drawmanager->AddObject(uibackLogo[1]);

	drawmanager->AddObject(uistart);
	drawmanager->AddObject(uiexit);
	drawmanager->AddObject(uicursor);
	//drawmanager->AddObject(uistart->collider);
	//drawmanager->AddObject(uiexit->collider);


	test = false;

	uiexit->isDraw = false;
	uistart->isDraw = false;
	uibackLogo[0]->isDraw = false;
	uibackLogo[1]->isDraw = false;

	// �}�E�X�J�[�\���̔�\��
	ShowCursor(FALSE);
	
	CSoundManager::GetSound()->XA_Play(TITLE_BGM, 0.5f);
	
}

CTitleScene::~CTitleScene()
{
	delete backGround;
	delete titleLogo;
	delete uiStartLogo;
	delete uistart;
	delete uiexit;
	delete uibackLogo[0];
	delete uibackLogo[1];

	delete drawmanager;
}

void CTitleScene::Update()
{
	if (CInput::Get()->GetType() == CInput::HIDType::KeyBoardMouse)
	{
		DirectX::XMFLOAT2 pos = CInput::Get()->GetMousePos();

		uicursor->transform->position.x = pos.x;
		uicursor->transform->position.y = pos.y;
	}
	else
	{
		DirectX::XMFLOAT2 pos = CInput::Get()->GetControllerStick();

		uicursor->transform->position.x += (pos.x/10);
		uicursor->transform->position.y += (pos.y/10);
	}
	drawmanager->Update();

	if (uiStartLogo->transform->scale.x >= 11.0f)
	{
		test = false;
	}
	else if (uiStartLogo->transform->scale.x <= 9.0f)
	{
		test = true;
	}
	if (test)
	{
		uiStartLogo->transform->scale.x += 0.05f;
		uiStartLogo->transform->scale.y += 0.05f;
	}
	else
	{
		uiStartLogo->transform->scale.x -= 0.05f;
		uiStartLogo->transform->scale.y -= 0.05f;
	}

	// �n�߂�I����\�����Ȃ�
	uistart->isDraw = false;
	uiexit->isDraw = false;
	uibackLogo[0]->isDraw = false;
	uibackLogo[1]->isDraw = false;


	// �ŏ��̏�Ԃ̃V�[��
	if (!isStart)
	{
		if (CInput::Get()->GetType() == CInput::HIDType::KeyBoardMouse)
		{
			// �ŏ��́u�{�^���������Ăˁv�̂Ƃ��ɂǂ̃{�^���������Ă���������悤�ɂ���
			for (int i = 0; i < static_cast<int>(CInput::InputType::LB3); i++)
			{
				CInput::InputType input = static_cast<CInput::InputType>(i);
				if (CInput::Get()->isKeyTrigger(input))
				{
					CSoundManager::GetSound()->XA_Play(CLICK, 0.5f);
					isStart = true;
					uiStartLogo->isDraw = false;

				}

			}
			for (int i = 0; i < 9; i++)
			{
				if (CInput::Get()->isMouseTrigger(static_cast<CInput::InputType>(i)))
				{
					CSoundManager::GetSound()->XA_Play(CLICK, 0.5f);
					isStart = true;
					uiStartLogo->isDraw = false;
				}
			}
		}
		else
		{
			// �ŏ��́u�{�^���������Ăˁv�̂Ƃ��ɂǂ̃{�^���������Ă���������悤�ɂ���
			if (CInput::Get()->isKeyTrigger(CInput::InputType::A))
			{
				CSoundManager::GetSound()->XA_Play(CLICK, 0.5f);
				isStart = true;
				uiStartLogo->isDraw = false;

			}
		}
	}
	else
	{
		// �n�߂�I����\������
		uistart->isDraw = true;
		uiexit->isDraw = true;
		uibackLogo[0]->isDraw = true;
		uibackLogo[1]->isDraw = true;



		// �{�^���N���b�N����
		//if(CInput::Get()->GetMousePos())

		if (DotSquareCollision(&uicursor->transform->position, uistart->collider->transform))
		{
			isGameStart = true;
		}
		else
		{
			isGameStart = false;
		}
		
		if (DotSquareCollision(&uicursor->transform->position, uiexit->collider->transform))
		{
			isGameEnd = true;
		}
		else
		{
			isGameEnd = false;
		}


		// �u�͂��߂�v�ɃJ�[�\���������Ă���Ƃ�
		if (isGameStart)
		{
			uiexit->transform->scale = { 7.0f,7.0f,1.0f };
			// �I��ł��邩�̂悤�ɃX�P�[����ύX���Ă���
			if (uistart->transform->scale.x >= 8.0f)
			{
				test = false;
			}
			else if (uistart->transform->scale.x <= 6.0f)
			{
				test = true;
			}
			if (test)
			{
				uistart->transform->scale.x += 0.05f;
				uistart->transform->scale.y += 0.05f;
			}
			else
			{
				uistart->transform->scale.x -= 0.05f;
				uistart->transform->scale.y -= 0.05f;
			}


			if (CInput::Get()->isKeyTrigger(CInput::InputType::DOWN))
			{
				isGameStart = false;
			}

			if (CInput::Get()->isMouseTrigger(CInput::InputType::LB1))
			{
				if (DotSquareCollision(&uicursor->transform->position, uistart->collider->transform))
				{
					CSoundManager::GetSound()->XA_Stop(TITLE_BGM);

					CSceneManager::get()->ChangeScene(CSceneManager::SceneState::SERECT);
				}
			}
			// �X�e�[�W��؂�ւ��鏈�� ��ԍŌ�ɂ������� enter�L�[
			if (CInput::Get()->isKeyTrigger(CInput::InputType::A))
			{
				CSoundManager::GetSound()->XA_Play(CLICK, 0.5f);
				nextSceneSet = true;
			}
			if (nextSceneSet)
			{
				
				// �t�F�[�h�C���t�F�[�h�A�E�g����
				CSoundManager::GetSound()->XA_Stop(TITLE_BGM);
					// �X�e�[�W�Z���N�g�Ɉړ�����
				CSceneManager::get()->ChangeScene(CSceneManager::SceneState::SERECT);

			}
		}
		else if(isGameEnd)
		{
			uistart->transform->scale = { 7.0f, 7.0f, 1.0f };
			// �I��ł��邩�̂悤�ɃX�P�[����ύX���Ă���
			if (uiexit->transform->scale.x >= 8.0f)
			{
				test = false;
			}
			else if (uiexit->transform->scale.x <= 6.0f)
			{
				test = true;
			}
			if (test)
			{
				uiexit->transform->scale.x += 0.05f;
				uiexit->transform->scale.y += 0.05f;
			}
			else
			{
				uiexit->transform->scale.x -= 0.05f;
				uiexit->transform->scale.y -= 0.05f;
			}

			if (CInput::Get()->isMouseTrigger(CInput::InputType::LB1))
			{
				CSoundManager::GetSound()->XA_Play(CLICK, 0.5f);
				if (DotSquareCollision(&uicursor->transform->position, uiexit->collider->transform))
				{
					CGame::Get()->endflg = true;
				}
			}


			if (CInput::Get()->isKeyTrigger(CInput::InputType::UP))
			{
				isGameStart = true;
			}

			if (CInput::Get()->isKeyTrigger(CInput::InputType::A))
			{
				isStart = false;
				uiStartLogo->isDraw = true;
				CGame::Get()->endflg = true;
			}
		}
		else
		{
			uistart->transform->scale = { 7.0f, 7.0f, 1.0f };
			uiexit->transform->scale = { 7.0f, 7.0f, 1.0f };
		}
		
	}
}

void CTitleScene::Draw()
{
	drawmanager->Draw();
}
