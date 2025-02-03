#pragma once

#include "CScene.h"
#include "CUi.h"
#include "CBackGround.h"
#include "CPlayer.h"
#include "CDrawManager.h"
#include "Collision.h"

// �^�C�g���p�V�[��
class CTitleScene : public CScene
{
private:

	// �w�i�p�o�b�t�@
	ID3D11Buffer* vertexBufferUi;
	ID3D11Buffer* vertexBufferBg;

	/* �^�C�g���V�[���ŗp����e�N�X�`�� */
	ID3D11ShaderResourceView* textureBackGround= NULL;
	ID3D11ShaderResourceView* textureTitleLogo = NULL;
	ID3D11ShaderResourceView* textureStartUi = NULL;
	ID3D11ShaderResourceView* textureEndUi = NULL;
	ID3D11ShaderResourceView* textureBackText = NULL;
	ID3D11ShaderResourceView* textureExit = NULL;
	ID3D11ShaderResourceView* textureStart = NULL;
	ID3D11ShaderResourceView* textureCursor = NULL;

	
	// �e�I�u�W�F�N�g�ϐ��錾
	CBackGround* backGround;	// �w�i
	//CGameObject* uiStartLogo;
	CGameObject* uiEndLogo;
	CGameObject* titleLogo;

	CUi* uiStartLogo;
	CUi* uistart;
	CUi* uiexit;
	CUi* uibackLogo[2];
	CUi* uicursor;
	

	CDrawManager* drawmanager;
	//CCamera* camera;

public:
	// �R���X�g���N�^�E�f�X�g���N�^
	CTitleScene();
	~CTitleScene();

	void Update();
	void Draw();



	bool test;

	bool isStart = false;

	bool isGameStart = false;
	bool isGameEnd = false;

	bool nextSceneSet = false;
};

