#pragma once

#include "CScene.h"

class CSceneManager
{
public:
	// �e�V�[���J�ڂ̏��
	enum SceneState
	{
		TITLE,
		SERECT,
		GAME,
		RESELT,
		END = 10
	};

	// �e�X�e�[�W�ԍ��̏��
	enum StageState
	{
		STAGE1 = 1,
		STAGE2 = 2,
		STAGE3 = 3,
		STAGE4 = 4,
		STAGE5 = 5,
	};

private:
	// ���݂̃V�[����ۑ����Ă����ϐ� �ŏ��̓^�C�g���ɐݒ肵�Ă���
	SceneState scenestate = SceneState::TITLE;
	// ���݂̃X�e�[�W�̔ԍ���ۑ����Ă����ϐ�
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

