#pragma once
#include "CScene.h"
#include "CPlayer.h"
#include "CBackGround.h"
#include "CFloor.h"
#include "Collision.h"
#include "CGoal.h"
#include "CWoodBox.h"
#include "CDrawManager.h"
#include "CCollider.h"
#include "CUi.h"
#include "CPiece.h"


class Stage4 : public CScene
{
public:
	// �R���X�g���N�^�E�f�X�g���N�^
	Stage4();
	~Stage4();

	// �X�V����
	void Update()override;
	// �`�揈��
	void Draw()override;
private:
	ID3D11Buffer* vertexBufferBg;			// �S��ʂŕ\�����鎞�Ɏg�p����o�b�t�@
	ID3D11Buffer* vertexBufferCharacter;	// ����̑傫���ŕ\������Ƃ��Ɏg�p����o�b�t�@
	ID3D11Buffer* vertexBufferEffect;	// ����̑傫���ŕ\������Ƃ��Ɏg�p����o�b�t�@
	ID3D11Buffer* vertexBufferPieceEffect;	// ����̑傫���ŕ\������Ƃ��Ɏg�p����o�b�t�@

	ID3D11Buffer* vertexBufferPiece;		// ����̑傫���ŕ\������Ƃ��Ɏg�p����o�b�t�@

	ID3D11ShaderResourceView* texturePazlePiece = NULL;		// �p�Y���̃s�[�X�w�i
	ID3D11ShaderResourceView* textureBackGround = NULL;		// �X�e�[�W�w�i�i��i�j
	ID3D11ShaderResourceView* textureBackfrontGround = NULL;		// �X�e�[�W�w�i�i�O�i�j
	ID3D11ShaderResourceView* texturePlayer = NULL;		// �v���C���[
	ID3D11ShaderResourceView* texturePlayer_stay = NULL;// �v���C���[
	ID3D11ShaderResourceView* texturePlayer_jump = NULL;// �v���C���[
	ID3D11ShaderResourceView* texturePlayerDead = NULL;// �v���C���[
	ID3D11ShaderResourceView* textureFloor = NULL;		// ��
	ID3D11ShaderResourceView* textureFloormiddle = NULL;		// ��
	ID3D11ShaderResourceView* textureFloortop = NULL;		// ��
	ID3D11ShaderResourceView* textureUiPiece = NULL;		// �X�e�[�Wui
	ID3D11ShaderResourceView* textureUiOnePiece = NULL;		// �X�e�[�Wui	
	ID3D11ShaderResourceView* textureWoodBox = NULL;		// �X�e�[�W�ؔ�	
	ID3D11ShaderResourceView* texturehalfWoodBox = NULL;		// �X�e�[�W�����T�C�Y�ؔ�	
	ID3D11ShaderResourceView* textureEffect = NULL;		// �G�t�F�N�g
	ID3D11ShaderResourceView* textureEffectPanel = NULL;		// �G�t�F�N�g
	ID3D11ShaderResourceView* textureUiCursor = NULL;		// �s�[�X�̃J�[�\��
	ID3D11ShaderResourceView* textureGoal = NULL;		// �s�[�X�̃J�[�\��
	ID3D11ShaderResourceView* texturefade = NULL;		// �t�F�[�h�p
	ID3D11ShaderResourceView* texturefadeblack = NULL;		// �t�F�[�h�p
	ID3D11ShaderResourceView* textureMouseCursor = NULL;		// �t�F�[�h�p

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


private:
	CBackGround* background;	// �w�i�i��i�j
	CBackGround* frontground;	// �w�i�i�O�i�j
	CWoodBox* woodbox[2];		// �ؔ�
	CWoodBox* halfwoodbox[2];		// �����T�C�Y�̖ؔ�
	CGoal* goal;				// �S�[��
	CFloor* floor[11];			// ��
	CBackGround* pazle[2];		// �w�i�p�s�[�X
	CPlayer* player;			// �v���C���[

	/* UI�p��ŕύX���� */
	CUi* uipiecestock;		// �s�[�X�ۑ�UI
	CUi* uionepiece;		// �s�[�X�ۑ��ꏊ�̃s�[�X
	CPiece* piece_array[PIECE_Y][PIECE_X];// �e�z�u�Ƀs�[�X��E�΂��Ă���
	CGameObject* previewpiece;	// UI�s�[�X

	CGameObject* work;			// ����ւ��g�p���Ɏg��

	CGameObject* uiDrawPiece;
	CGameObject* goaleffect;// �S�[���G�t�F�N�g�p
	CGameObject* Pieceeffect;// �S�[���G�t�F�N�g�p
	CGameObject* fade;
	CGameObject* fadeblack;
	CGameObject* mousecursor;
	CDrawManager* drawManager;

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

	int pauseCnt = 0;
	int select = 0;
	bool sizeup = true;

	// �q�I�u�W�F�N�g�̃|�C���^���i�[����ϒ��z��
	std::vector<CGameObject*> gimickObj = {};
	// �q�I�u�W�F�N�g�̓����蔻����i�[����ϒ��z��
	std::vector<CGameObject*> colliderObj = {};

	std::vector<CGameObject*> floorObj = {};

	bool fadeout = true;

	bool pauseSet = false;

	bool resultset = false;
	bool playerOut = false;
public:

	// ����ւ�����
	void ReplaceObj(CGameObject* _pieceobj);


	CFloat3 _position = { 0,0,0 };

	CFloat3 _rotation = { 0,0,0 };

	CFloat3 _scaling = { 0,0,0 };

	LayerNum drawNum = LayerNum::BLACK_OUT;

	CollisionDirection collision = COLLISION_NULL;
};

