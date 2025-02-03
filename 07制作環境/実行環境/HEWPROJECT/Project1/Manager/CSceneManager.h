#pragma once

#include "CScene.h"

class CSceneManager
{
public:
	// 各シーン遷移の状態
	enum SceneState
	{
		TITLE,
		SERECT,
		GAME,
		RESELT,
		END = 10
	};

	// 各ステージ番号の状態
	enum StageState
	{
		STAGE1 = 1,
		STAGE2 = 2,
		STAGE3 = 3,
		STAGE4 = 4,
		STAGE5 = 5,
	};

private:
	// 現在のシーンを保存しておく変数 最初はタイトルに設定しておく
	SceneState scenestate = SceneState::TITLE;
	// 現在のステージの番号を保存しておく変数
	StageState stagestate = StageState::STAGE1;

public:
	CSceneManager(){};
	~CSceneManager();

	 void ChangeScene(SceneState scene);
	 void Update();
	 void Draw();

	 void ChangeStage(StageState stage);


	static CScene* Get() { return _scene; }
	static CSceneManager* get() { static CSceneManager instance; return &instance; };
private:
	static CScene* _scene;
	static CScene* _stage;

public:
	bool fadeflag = false;
};

