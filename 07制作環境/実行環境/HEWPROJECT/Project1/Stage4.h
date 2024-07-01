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
	// コンストラクタ・デストラクタ
	Stage4();
	~Stage4();

	// 更新処理
	void Update()override;
	// 描画処理
	void Draw()override;
private:
	ID3D11Buffer* vertexBufferBg;			// 全画面で表示する時に使用するバッファ
	ID3D11Buffer* vertexBufferCharacter;	// 特定の大きさで表示するときに使用するバッファ
	ID3D11Buffer* vertexBufferEffect;	// 特定の大きさで表示するときに使用するバッファ
	ID3D11Buffer* vertexBufferPieceEffect;	// 特定の大きさで表示するときに使用するバッファ

	ID3D11Buffer* vertexBufferPiece;		// 特定の大きさで表示するときに使用するバッファ

	ID3D11ShaderResourceView* texturePazlePiece = NULL;		// パズルのピース背景
	ID3D11ShaderResourceView* textureBackGround = NULL;		// ステージ背景（後景）
	ID3D11ShaderResourceView* textureBackfrontGround = NULL;		// ステージ背景（前景）
	ID3D11ShaderResourceView* texturePlayer = NULL;		// プレイヤー
	ID3D11ShaderResourceView* texturePlayer_stay = NULL;// プレイヤー
	ID3D11ShaderResourceView* texturePlayer_jump = NULL;// プレイヤー
	ID3D11ShaderResourceView* texturePlayerDead = NULL;// プレイヤー
	ID3D11ShaderResourceView* textureFloor = NULL;		// 床
	ID3D11ShaderResourceView* textureFloormiddle = NULL;		// 床
	ID3D11ShaderResourceView* textureFloortop = NULL;		// 床
	ID3D11ShaderResourceView* textureUiPiece = NULL;		// ステージui
	ID3D11ShaderResourceView* textureUiOnePiece = NULL;		// ステージui	
	ID3D11ShaderResourceView* textureWoodBox = NULL;		// ステージ木箱	
	ID3D11ShaderResourceView* texturehalfWoodBox = NULL;		// ステージ半分サイズ木箱	
	ID3D11ShaderResourceView* textureEffect = NULL;		// エフェクト
	ID3D11ShaderResourceView* textureEffectPanel = NULL;		// エフェクト
	ID3D11ShaderResourceView* textureUiCursor = NULL;		// ピースのカーソル
	ID3D11ShaderResourceView* textureGoal = NULL;		// ピースのカーソル
	ID3D11ShaderResourceView* texturefade = NULL;		// フェード用
	ID3D11ShaderResourceView* texturefadeblack = NULL;		// フェード用
	ID3D11ShaderResourceView* textureMouseCursor = NULL;		// フェード用

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


private:
	CBackGround* background;	// 背景（後景）
	CBackGround* frontground;	// 背景（前景）
	CWoodBox* woodbox[2];		// 木箱
	CWoodBox* halfwoodbox[2];		// 半分サイズの木箱
	CGoal* goal;				// ゴール
	CFloor* floor[11];			// 床
	CBackGround* pazle[2];		// 背景用ピース
	CPlayer* player;			// プレイヤー

	/* UI用後で変更する */
	CUi* uipiecestock;		// ピース保存UI
	CUi* uionepiece;		// ピース保存場所のピース
	CPiece* piece_array[PIECE_Y][PIECE_X];// 各配置にピースを忍ばせておく
	CGameObject* previewpiece;	// UIピース

	CGameObject* work;			// 入れ替え使用時に使う

	CGameObject* uiDrawPiece;
	CGameObject* goaleffect;// ゴールエフェクト用
	CGameObject* Pieceeffect;// ゴールエフェクト用
	CGameObject* fade;
	CGameObject* fadeblack;
	CGameObject* mousecursor;
	CDrawManager* drawManager;

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

	int pauseCnt = 0;
	int select = 0;
	bool sizeup = true;

	// 子オブジェクトのポインタを格納する可変長配列
	std::vector<CGameObject*> gimickObj = {};
	// 子オブジェクトの当たり判定を格納する可変長配列
	std::vector<CGameObject*> colliderObj = {};

	std::vector<CGameObject*> floorObj = {};

	bool fadeout = true;

	bool pauseSet = false;

	bool resultset = false;
	bool playerOut = false;
public:

	// 入れ替え処理
	void ReplaceObj(CGameObject* _pieceobj);


	CFloat3 _position = { 0,0,0 };

	CFloat3 _rotation = { 0,0,0 };

	CFloat3 _scaling = { 0,0,0 };

	LayerNum drawNum = LayerNum::BLACK_OUT;

	CollisionDirection collision = COLLISION_NULL;
};

