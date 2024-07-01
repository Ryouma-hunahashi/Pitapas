#include "CGame.h"
//#include "CCamera.h"
#include "CInput.h"
#include "CSceneManager.h"
#include "CSoundManager.h"

void CGame::Initialize()
{
	// 乱数の初期化
	// ※srand関数はアプリケーション開始時に１回だけ呼び出す
	srand(GetTickCount64());

	//camera = new CCamera();

	//camera->SetEye(cameraPos);
	//camera->SetFocus({ 1,1,0 });// カメラが映している場所

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

