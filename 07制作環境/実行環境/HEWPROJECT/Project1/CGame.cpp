#include "CGame.h"
//#include "CCamera.h"
#include "CInput.h"
#include "CSceneManager.h"
#include "CSoundManager.h"

void CGame::Initialize()
{
	// �����̏�����
	// ��srand�֐��̓A�v���P�[�V�����J�n���ɂP�񂾂��Ăяo��
	srand(GetTickCount64());

	//camera = new CCamera();

	//camera->SetEye(cameraPos);
	//camera->SetFocus({ 1,1,0 });// �J�������f���Ă���ꏊ

	CSoundManager::GetSound()->XA_Initialize();

	CSceneManager::get()->ChangeScene(CSceneManager::SceneState::TITLE);
}

CGame::~CGame()
{

}

void CGame::Update()
{
	CDirectX::Get()->D3D_ClearScreen();

	CSceneManager::get()->Update();
	CSceneManager::get()->Draw();
	if (CInput::Get()->isKeyTrigger(CInput::InputType::Y))endflg = true;


	CDirectX::Get()->D3D_UpdateScreen();
}

