#pragma once

#include "CScene.h"
#include "CBackGround.h"
#include "CDrawManager.h"
#include "CDirectX.h"
#include "CUi.h"
struct Vector2 {
	float x, y;

	Vector2(float _x, float _y) : x(_x), y(_y) {}
};

class VertexBuffer {
public:
	// ���_�o�b�t�@�Ɋ֘A���郁�\�b�h��f�[�^���`����

	VertexBuffer() {}
	~VertexBuffer() {}
};

class IDirectX {
public:
	virtual void D3D_CreateSquare(const Vector2& center, const Vector2& size, const Vector2& uv, VertexBuffer* pVertexBuffer) = 0;

	virtual ~IDirectX() {} // ���z�f�X�g���N�^
};

class CSelectScene : public CScene
{

public:
	
	float cursorY = 0.0f;
	CSelectScene();
	~CSelectScene();

void CreateBackgroundModel(float centerX, float centerY, float width, float height, float uvX, float uvY, int bufferIndex)
{
	CDirectX::FLOAT_XY centerFloatXY = { centerX, centerY };
	CDirectX::FLOAT_XY sizeFloatXY = { width, height };
	CDirectX::FLOAT_XY uvFloatXY = { uvX, uvY };

	CDirectX::Get()->D3D_CreateSquare(centerFloatXY, sizeFloatXY, uvFloatXY, &vertexBuffers[bufferIndex]);
};
private:

	//CCamera* camera;

	enum BufferType 
	{
		VertexBufferBg,			// �S��ʂŕ\�����鎞�Ɏg�p����o�b�t�@
		VertexBufferBs,			// �Z���N�g��ʂ̕����Ɏg�p����o�b�t�@
		VertexBufferPg,			// ���̃s�[�X�̔w�i�Ɏg�p����o�b�t�@
		VertexBufferSg,			// ���̃s�[�X�̔w�i�Ɏg�p����o�b�t�@
		VertexBufferS1g,		// �X�e�[�W�I���Ɏg�p����o�b�t�@
		VertexBufferS2g,		// �X�e�[�W�I���Ɏg�p����o�b�t�@
		VertexBufferS3g,		// �X�e�[�W�I���Ɏg�p����o�b�t�@
		VertexBufferS4g,		// �X�e�[�W�I���Ɏg�p����o�b�t�@
		VertexBufferKg1,		// �J�[�\��1�摜�Ɏg�p����o�b�t�@
		VertexBufferS1_1,		// 1-1�o�b�t�@
		VertexBufferS1_2,		// 1-2�o�b�t�@
		VertexBufferS1_3,		// 1-3�o�b�t�@
		VertexBufferS1_4,		// 1-4�o�b�t�@
		VertexBufferFrame,		// �X�e�[�W�t���[���̃o�b�t�@
		vertexBufferSS1g,		// �X�e�[�W�I���Ɏg�p����o�b�t�@
		vertexBufferSS2g,		// �X�e�[�W�I���Ɏg�p����o�b�t�@
		vertexBufferSS3g,		// �X�e�[�W�I���Ɏg�p����o�b�t�@
		vertexBufferSS4g,		// �X�e�[�W�I���Ɏg�p����o�b�t�@
		vertexBufferBTg,		// �^�C�g���ɖ߂鎞�Ɏg�p����o�b�t�@
		NumBufferTypes			// �o�b�t�@�̐��������I�Ɍv�Z���邽�߂̒ǉ��̗v�f
	};

	ID3D11Buffer* vertexBuffers[NumBufferTypes];

	enum TextureType 
	{
		TextureBackGround,		// �S��ʂŕ\�����鎞�Ɏg�p����e�N�X�`��
		TextureTestBs,			// �Z���N�g��ʂ̕����Ɏg�p����e�N�X�`��
		TextureSelectScene,	// ���̃s�[�X�̔w�i�Ɏg�p����e�N�X�`��
		TexturePurplePiece,		// ���̃s�[�X�̔w�i�Ɏg�p����e�N�X�`��
		TextureStageName,		// �X�e�[�W�I���Ɏg�p����e�N�X�`��
		TextureStage1,			// �X�e�[�W�I���Ɏg�p����e�N�X�`��
		TextureStage2,			// �X�e�[�W�I���Ɏg�p����e�N�X�`��
		TextureStage3,			// �X�e�[�W�I���Ɏg�p����e�N�X�`��
		TextureStage4,			// �X�e�[�W�I���Ɏg�p����e�N�X�`��
		TextureCursor,			// �J�[�\��1�摜�Ɏg�p����e�N�X�`��
		TextureName1,			// �X�e�[�W���P
		TextureName2,			// �X�e�[�W���Q
		TextureName3,			// �X�e�[�W���R
		TextureName4,			// �X�e�[�W���S
		Texture1_1,				// 1-1�e�N�X�`��
		Texture1_2,				// 1-2�e�N�X�`��
		Texture1_3,				// 1-3�e�N�X�`��
		Texture1_4,				// 1-4�e�N�X�`��
		TextureFrame,			// �X�e�[�W�t���[���̃e�N�X�`��
		TextureStageImage1,		// �X�e�[�W�I���Ɏg�p����e�N�X�`��
		TextureStageImage2,		// �X�e�[�W�I���Ɏg�p����e�N�X�`��
		TextureStageImage3,		// �X�e�[�W�I���Ɏg�p����e�N�X�`��
		TextureStageImage4,		// �X�e�[�W�I���Ɏg�p����e�N�X�`��
		TextureBackTitle,		// �^�C�g���ɖ߂�Ƃ��Ɏg�p����e�N�X�`��
		TextureFade,
		TextureFadeBack,
		
		NumTextureTypes,			// �o�b�t�@�̐��������I�Ɍv�Z���邽�߂̒ǉ��̗v�f


	};

	ID3D11ShaderResourceView* textures[NumTextureTypes] = { nullptr };

public:
	CDrawManager* drawmanager;
	enum BackgroundType 
	{
		Background,
		BackSelect,
		SelectScene,
		PurplePiece,
		StageName,
		Stage1,
		Stage2,
		Stage3,
		Stage4,
		Cursor1,
		Name1,
		Name2,
		Name3,
		Name4,
		S1_1,
		S1_2,
		S1_3,
		S1_4,
		Frame,

		StageImage1,
		StageImage2,
		StageImage3,
		StageImage4,
		BackTitle,
		BackTitleName,
		Fade,
		FadeBack,
		NumBackgroundTypes
	};

	CUi* backgrounds[NumBackgroundTypes] = { nullptr };


	void Update();
	void Draw();

	// �X�e�[�W�̍ő吔��ݒ� ���^�C�g���ɖ߂鎞�̌����܂߂邱��
	const int totalStages = 5;
	// �I������Ă���X�e�[�W�̐�
	int selectedStage = 1;

	bool scaleflg = false;

	bool fadeflag = false;

	static CSelectScene* getSelect() { static CSelectScene* instance; return instance; }
	
	//CCamera* GetCamera() { return camera; }
};

