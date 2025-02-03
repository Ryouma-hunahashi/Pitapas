//#include <iostream>

#include "CSceneManager.h"
//#include "CResultScene.h"
#include "CTitleScene.h"
#include "CSelectScene.h"
//#include "CGameScene.h"
#include "Stage1.h"
#include "Stage2.h"
#include "Stage3.h"
#include "Stage4.h"

CScene* CSceneManager::_scene = NULL;
CScene* CSceneManager::_stage = NULL;

CSceneManager::~CSceneManager()
{
}

void CSceneManager::ChangeScene(SceneState scene)
{
	if (_scene != nullptr)
	{
		delete _scene;
		_scene = nullptr;
	}
	else
	{
		delete _stage;
		_stage = nullptr;
	}

	switch (scene)
	{
	case SceneState::TITLE:
		_scene = new CTitleScene();
		break;
	case SceneState::SERECT:
		_scene = new CSelectScene();
		break;
	case SceneState::GAME:
		//_scene = new CGameScene();
		break;
	case SceneState::RESELT:
		//_scene = new CResultScene();
		break;
	default:
		break;
	}

	delete _stage;
}

void CSceneManager::Update()
{
	
	if (_stage != nullptr)
	{
		_stage->Update();
	}
	else
	{
		_scene->Update();
	}
}

void CSceneManager::Draw()
{
	if (_stage != nullptr)
	{
		_stage->Draw();
	}
	else
	{
		_scene->Draw();
	}
}

void CSceneManager::ChangeStage(StageState stage)
{
	if (_stage != nullptr)
	{
		delete _stage;
		_stage = nullptr;
	}
	else
	{
		delete _scene;
		_scene = nullptr;
	}

	switch (stage)
	{
	case StageState::STAGE1:
		_stage = new Stage1();
		break;
	case StageState::STAGE2:
		_stage = new Stage2();
		break;
	case StageState::STAGE3:
		_stage = new Stage3();
		break;
	case StageState::STAGE4:
		_stage = new Stage4();
		break;
	default:
		break;
	}

	delete _scene;
}
