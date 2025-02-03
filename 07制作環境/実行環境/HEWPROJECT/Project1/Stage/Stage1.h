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
public: // コンストラクタ　デストラクタ
	Stage1();
	~Stage1();

public:
	void Update()override;
	void Draw()override;
private:
	// 入れ替え処理
	void ReplaceObj(CGameObject* _pieceobj);

private:
	// バッファ
	ID3D11Buffer* vertexBufferBg;			// 画面サイズに表示する用
	ID3D11Buffer* vertexBufferPlayer;		// プレイヤー用
	ID3D11Buffer* vertexBufferGoalEffect;	// ゴールエフェクト用
	ID3D11Buffer* vertexBufferPieceEffect;	// ピースエフェクト用

	// テクスチャ

	ID3D11ShaderResourceView* textureBackGround = NULL;			// 背景用テクスチャ(後景)
	ID3D11ShaderResourceView* textureFrontGround = NULL;		// 背景用テクスチャ(前景)
	ID3D11ShaderResourceView* textureBackPazleGround = NULL;	// 背景用パズルピース
	ID3D11ShaderResourceView* texturePlayerWalk = NULL;			// プレイヤー（歩き）
	ID3D11ShaderResourceView* texturePlayerJump = NULL;			// プレイヤー（ジャンプ）
	ID3D11ShaderResourceView* texturePlayerStay = NULL;			// プレイヤー（待機）
	ID3D11ShaderResourceView* texturePlayerDead = NULL;			// プレイヤー（死亡）
	ID3D11ShaderResourceView* textureFloorTop = NULL;			// 地面（上）
	ID3D11ShaderResourceView* textureWoodBox = NULL;			// 木箱
	ID3D11ShaderResourceView* textureHalfWoodBox = NULL;		// 木箱（ハーフ）
	ID3D11ShaderResourceView* textureMouseCursor = NULL;		// ピースのカーソル
	ID3D11ShaderResourceView* textureUiPiece = NULL;			// ステージUiパズルピース
	ID3D11ShaderResourceView* textureUiPreview = NULL;			// ステージUi
	ID3D11ShaderResourceView* textureGoal = NULL;				// ゴール
	ID3D11ShaderResourceView* textureEffectPiece = NULL;		// ピースエフェクト
	ID3D11ShaderResourceView* textureEffectGoal = NULL;			// ゴールエフェクト


	// フェード用
	ID3D11ShaderResourceView* texturefade = NULL;		// フェード用
	ID3D11ShaderResourceView* texturefadeblack = NULL;		// フェード用

	// ポーズ用
	ID3D11ShaderResourceView* texturePauseBack = NULL;				// 黒背景
	ID3D11ShaderResourceView* texturePauseButtonBand = NULL;		// ボタン後ろ
	ID3D11ShaderResourceView* texturePauseButtonContinue = NULL;	// ボタンコンティニュー
	ID3D11ShaderResourceView* texturePauseButtonRetry = NULL;		// ボタンリトライ
	ID3D11ShaderResourceView* texturePauseButtonReturn = NULL;		// ボタンリターン
	ID3D11ShaderResourceView* texturePauseScene = NULL;				// ポーズ名前
	ID3D11ShaderResourceView* texturePauseStageName = NULL;			// 現在のシーンの名前
	ID3D11ShaderResourceView* texturePauseSceneBand = NULL;			// ポーズ名前の後ろ

	// リザルト用
	ID3D11ShaderResourceView* textureBlackBackGround = NULL;	// 黒背景
	ID3D11ShaderResourceView* textureClearText = NULL;			// テキスト：クリア
	ID3D11ShaderResourceView* textureResultPanel = NULL;		// リザルトパネル
	ID3D11ShaderResourceView* textureSceneBand = NULL;			// シーンバンド
	ID3D11ShaderResourceView* textureStageNameBand = NULL;		// ステージシーンバンド
	ID3D11ShaderResourceView* textureButton = NULL;				// ボタン
	ID3D11ShaderResourceView* textureResultText = NULL;			// テキスト：けっか
	ID3D11ShaderResourceView* textureNext = NULL;				// テキスト：つぎへ
	ID3D11ShaderResourceView* textureRetry = NULL;				// テキスト：もういちど
	ID3D11ShaderResourceView* textureReturn = NULL;				// テキスト：もどる
	ID3D11ShaderResourceView* textureOut = NULL;				// テキスト：しっぱい
	


	// オブジェクト
	CBackGround* background[2];		// 背景（後景　前景）
	CBackGround* pazlebackground;	// 背景（パズル）
	CPlayer*	 player;				// プレイヤー
	CFloor*		 floor[7];				// 地面
	CWoodBox*	 woodbox[2];			// 木箱
	CGameObject* mousecursor;		// カーソル
	CGameObject* uipiece;			// Uiパズルピース
	CGameObject* Pieceeffect;		// ピースエフェクト用
	CUi*		 uiPreview;					// Ui保存場所
	CPiece*		 piece_array[4][7];		// 各ピースの位置保存用
	CGoal*		 goal;					// ゴール
	CGameObject* goaleffect;		// ゴールエフェクト用

	CGameObject* work;
	CDrawManager* D_manager;

	// フェード用
	CGameObject* fade;
	CGameObject* fadeblack;

	// ポーズ用
	CUi* pauseback;
	CUi* pausebutton[3];
	CUi* pausebuttonband[3];
	CUi* pausetext;
	CUi* pausetextband;
	CUi* pausestagename;

	// リザルト用
	CUi* BlackBackGround;				// 黒背景
	CUi* ClearText;						// テキスト：クリア
	CUi* ResultPanel;					// リザルトパネル
	CUi* SceneBand;						// シーンバンド
	CUi* StageNameBand;					// ステージシーンバンド
	CUi* ResultButton[3];				// ボタン
	CUi* ResultText;					// テキスト：けっか
	CUi* Next;							// テキスト：つぎへ
	CUi* Retry;							// テキスト：もういちど
	CUi* Return;						// テキスト：もどる
	CUi* OutText;						// テキスト：しっぱい


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

