#pragma once
#include "CScene.h"
#include "CDrawManager.h"
#include "CBackGround.h"
#include "CFloor.h"
#include "CUi.h"
#include "CPlayer.h"
#include "CWoodBox.h"
#include "CPiece.h"
#include "CGoal.h"
#include "Collision.h"
#include "CInput.h"
#include "CSceneManager.h"

class Stage1 : public CScene
{
public: // �R���X�g���N�^�@�f�X�g���N�^
	Stage1();
	~Stage1();

public:
	void Update()override;
	void Draw()override;
private:
	// ����ւ�����
	void ReplaceObj(CGameObject* _pieceobj);

private:
	// �o�b�t�@
	ID3D11Buffer* vertexBufferBg;			// ��ʃT�C�Y�ɕ\������p
	ID3D11Buffer* vertexBufferPlayer;		// �v���C���[�p
	ID3D11Buffer* vertexBufferGoalEffect;	// �S�[���G�t�F�N�g�p
	ID3D11Buffer* vertexBufferPieceEffect;	// �s�[�X�G�t�F�N�g�p

	// �e�N�X�`��

	ID3D11ShaderResourceView* textureBackGround = NULL;			// �w�i�p�e�N�X�`��(��i)
	ID3D11ShaderResourceView* textureFrontGround = NULL;		// �w�i�p�e�N�X�`��(�O�i)
	ID3D11ShaderResourceView* textureBackPazleGround = NULL;	// �w�i�p�p�Y���s�[�X
	ID3D11ShaderResourceView* texturePlayerWalk = NULL;			// �v���C���[�i�����j
	ID3D11ShaderResourceView* texturePlayerJump = NULL;			// �v���C���[�i�W�����v�j
	ID3D11ShaderResourceView* texturePlayerStay = NULL;			// �v���C���[�i�ҋ@�j
	ID3D11ShaderResourceView* texturePlayerDead = NULL;			// �v���C���[�i���S�j
	ID3D11ShaderResourceView* textureFloorTop = NULL;			// �n�ʁi��j
	ID3D11ShaderResourceView* textureWoodBox = NULL;			// �ؔ�
	ID3D11ShaderResourceView* textureHalfWoodBox = NULL;		// �ؔ��i�n�[�t�j
	ID3D11ShaderResourceView* textureMouseCursor = NULL;		// �s�[�X�̃J�[�\��
	ID3D11ShaderResourceView* textureUiPiece = NULL;			// �X�e�[�WUi�p�Y���s�[�X
	ID3D11ShaderResourceView* textureUiPreview = NULL;			// �X�e�[�WUi
	ID3D11ShaderResourceView* textureGoal = NULL;				// �S�[��
	ID3D11ShaderResourceView* textureEffectPiece = NULL;		// �s�[�X�G�t�F�N�g
	ID3D11ShaderResourceView* textureEffectGoal = NULL;			// �S�[���G�t�F�N�g


	// �t�F�[�h�p
	ID3D11ShaderResourceView* texturefade = NULL;		// �t�F�[�h�p
	ID3D11ShaderResourceView* texturefadeblack = NULL;		// �t�F�[�h�p

	// �|�[�Y�p
	ID3D11ShaderResourceView* texturePauseBack = NULL;				// ���w�i
	ID3D11ShaderResourceView* texturePauseButtonBand = NULL;		// �{�^�����
	ID3D11ShaderResourceView* texturePauseButtonContinue = NULL;	// �{�^���R���e�B�j���[
	ID3D11ShaderResourceView* texturePauseButtonRetry = NULL;		// �{�^�����g���C
	ID3D11ShaderResourceView* texturePauseButtonReturn = NULL;		// �{�^�����^�[��
	ID3D11ShaderResourceView* texturePauseScene = NULL;				// �|�[�Y���O
	ID3D11ShaderResourceView* texturePauseStageName = NULL;			// ���݂̃V�[���̖��O
	ID3D11ShaderResourceView* texturePauseSceneBand = NULL;			// �|�[�Y���O�̌��

	// ���U���g�p
	ID3D11ShaderResourceView* textureBlackBackGround = NULL;	// ���w�i
	ID3D11ShaderResourceView* textureClearText = NULL;			// �e�L�X�g�F�N���A
	ID3D11ShaderResourceView* textureResultPanel = NULL;		// ���U���g�p�l��
	ID3D11ShaderResourceView* textureSceneBand = NULL;			// �V�[���o���h
	ID3D11ShaderResourceView* textureStageNameBand = NULL;		// �X�e�[�W�V�[���o���h
	ID3D11ShaderResourceView* textureButton = NULL;				// �{�^��
	ID3D11ShaderResourceView* textureResultText = NULL;			// �e�L�X�g�F������
	ID3D11ShaderResourceView* textureNext = NULL;				// �e�L�X�g�F����
	ID3D11ShaderResourceView* textureRetry = NULL;				// �e�L�X�g�F����������
	ID3D11ShaderResourceView* textureReturn = NULL;				// �e�L�X�g�F���ǂ�
	ID3D11ShaderResourceView* textureOut = NULL;				// �e�L�X�g�F�����ς�
	


	// �I�u�W�F�N�g
	CBackGround* background[2];		// �w�i�i��i�@�O�i�j
	CBackGround* pazlebackground;	// �w�i�i�p�Y���j
	CPlayer*	 player;				// �v���C���[
	CFloor*		 floor[7];				// �n��
	CWoodBox*	 woodbox[2];			// �ؔ�
	CGameObject* mousecursor;		// �J�[�\��
	CGameObject* uipiece;			// Ui�p�Y���s�[�X
	CGameObject* Pieceeffect;		// �s�[�X�G�t�F�N�g�p
	CUi*		 uiPreview;					// Ui�ۑ��ꏊ
	CPiece*		 piece_array[4][7];		// �e�s�[�X�̈ʒu�ۑ��p
	CGoal*		 goal;					// �S�[��
	CGameObject* goaleffect;		// �S�[���G�t�F�N�g�p

	CGameObject* work;
	CDrawManager* D_manager;

	// �t�F�[�h�p
	CGameObject* fade;
	CGameObject* fadeblack;

	// �|�[�Y�p
	CUi* pauseback;
	CUi* pausebutton[3];
	CUi* pausebuttonband[3];
	CUi* pausetext;
	CUi* pausetextband;
	CUi* pausestagename;

	// ���U���g�p
	CUi* BlackBackGround;				// ���w�i
	CUi* ClearText;						// �e�L�X�g�F�N���A
	CUi* ResultPanel;					// ���U���g�p�l��
	CUi* SceneBand;						// �V�[���o���h
	CUi* StageNameBand;					// �X�e�[�W�V�[���o���h
	CUi* ResultButton[3];				// �{�^��
	CUi* ResultText;					// �e�L�X�g�F������
	CUi* Next;							// �e�L�X�g�F����
	CUi* Retry;							// �e�L�X�g�F����������
	CUi* Return;						// �e�L�X�g�F���ǂ�
	CUi* OutText;						// �e�L�X�g�F�����ς�


private:

	std::vector<CGameObject*> floorObj;

	std::vector<CGameObject*> gimickObj;

	CFloat3 _position;
	CFloat3 _scale;
	CFloat3 _rotation;

	bool fadeout = true;

	bool pauseSet = false;

	bool resultset = false;
	bool playerOut = false;
	int pauseCnt = 0;
	int select = 0;
	bool sizeup = true;
};

