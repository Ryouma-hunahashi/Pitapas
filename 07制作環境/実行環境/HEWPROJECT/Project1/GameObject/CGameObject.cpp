#include "CGameObject.h"

#include "CDirectx.h"
#include "CGame.h"
//#include "CCamera.h"

using namespace DirectX;

#include "CSceneManager.h"
#include "CCollider.h"

CGameObject::CGameObject(ID3D11Buffer* vb, ID3D11ShaderResourceView* tex,int num)
{
	// �o�b�t�@�ƃe�N�X�`����ۑ����Ă���
	vertexBuffer = vb;
	texture = tex;
	DrawNum = static_cast<LayerNum>(num);
	// ���W�ۑ��N���X�����̉�����
	transform = new CSquea();
	// �A�j���[�V�����N���X�����̉�����
	anim = new CAnimation(1,1);
	// �A�j���[�V�����̍ŏ��̐ݒ�������Ȃ��ɂ���
	anim->SetPattern(CAnimation::NO_ANIMATION);

}

CGameObject::~CGameObject()
{
	delete transform;
}

void CGameObject::Update()
{
	//if (!this->isDraw) return;
	this->transform->VertexPos();
	anim->Update();
}

void CGameObject::Draw()
{
	if (!this->isDraw) return;
	// DirectX�̕ϐ��̍\���̂��擾����
	CDirectX::Direct d3d = CDirectX::Get()->GetDirect();

	XMMATRIX matrixView;

	//matrixView = CGame::Get()->GetCamera()->GetViewMatrix();

	//matrixView = CSceneManager::Get()->GetCamera()->GetViewMatrix();

	// View�ϊ��s��̍쐬�@���@�J�����p�̍s��
	XMVECTOR eye = XMVectorSet( 0,0, 0, 0);  // ���_�̈ʒu
	XMVECTOR focus = XMVectorSet( 0, 0, 5, 0);  // ���Ă���ʒu
	XMVECTOR up = XMVectorSet(0, 1, 0, 0);  // �J�����̏����
	 matrixView = XMMatrixLookAtLH(eye, focus, up);
	ConstBuffer cb;

	// ���s���e�̍s��쐬
	// �����@�A�F�f���o���ʂ̉��c�̒���
	// �����B�C�F�f���o����Ԃ̉��s�i��O�ƍŉ��j
	float scaleScreen = 1.0f;
	cb.matrixProj = XMMatrixOrthographicLH(16.0f * scaleScreen, 9.0f * scaleScreen, 0.001f, 5.0f);
	cb.matrixProj = XMMatrixTranspose(matrixView * cb.matrixProj);// �J�����~���e

	//// ���[���h�ϊ��s��̍쐬
	//// �ړ��s��
	//XMMATRIX matrixMove = XMMatrixTranslation(position.x, position.y, position.z);
	//// �g��k���s��
	//XMMATRIX matrixScale = XMMatrixScaling(scaling.x, scaling.y, scaling.z);
	//// ��]�s��@XMMatrixRotationZ�֐�
	//XMMATRIX matrixRotateX = XMMatrixRotationX(XMConvertToRadians(rotation.x));
	//XMMATRIX matrixRotateY = XMMatrixRotationY(XMConvertToRadians(rotation.y));
	//XMMATRIX matrixRotateZ = XMMatrixRotationZ(XMConvertToRadians(rotation.z));
	//// �e��]�s��
	//XMMATRIX matrixRotate = matrixRotateX * matrixRotateY * matrixRotateZ;

	//matrixWorld = matrixScale * matrixRotate * matrixMove;


	// �s��͊|���Z�ō����ł��� �i���j�|���鏇�Ԃ��e������
	//cb.matrixWorld = matrixScale * matrixRotate * matrixMove;
	//cb.matrixWorld = XMMatrixTranspose(cb.matrixWorld);

	// �ړ��s��
	XMMATRIX matrixMove = XMMatrixTranslation(
		this->transform->position.x, 
		this->transform->position.y, 
		this->transform->position.z);

	// �g��k���s��
	XMMATRIX matrixScale = XMMatrixScaling(
		this->transform->scale.x,
		this->transform->scale.y,
		this->transform->scale.z);

	// ��]�s��
	XMMATRIX matrixRotateX = XMMatrixRotationX(XMConvertToRadians(this->transform->rotate.x));
	XMMATRIX matrixRotateY = XMMatrixRotationY(XMConvertToRadians(this->transform->rotate.y));
	XMMATRIX matrixRotateZ = XMMatrixRotationZ(XMConvertToRadians(this->transform->rotate.z));

	// ��]�s�����ɂ܂Ƃ߂�
	XMMATRIX matrixRotate = matrixRotateX * matrixRotateY * matrixRotateZ;

	// �s�����ɂ܂Ƃ߂�
	cb.matrixWorld = matrixScale * matrixRotate * matrixMove;
	//cb.matrixWorld = matrixScale  * matrixMove * matrixRotate;
	// �s����V�F�[�_�[�ɑ���
	cb.matrixWorld = XMMatrixTranspose(cb.matrixWorld);

	// UV�A�j���[�V�����̍s��쐬
	// XMMatrixTranslation���ړ��s������֐�
	cb.matrixTex = XMMatrixTranslation(anim->GetUV().x, anim->GetUV().y, 0.0f);
	// XMMatrixTranspose���]�u�s������
	cb.matrixTex = XMMatrixTranspose(cb.matrixTex);

	// �}�e���A���F��萔�o�b�t�@�f�[�^�ɃZ�b�g
	cb.materialDiffuse = materialDiffuse;

	// �s����V�F�[�_�[�ɓn��
	d3d.m_deviceContext->UpdateSubresource(d3d.m_ContextBuffer, 0, NULL, &cb, 0, 0);

	// VertexBuffer���w�肷��
	d3d.m_deviceContext->IASetVertexBuffers(0, 1, &vertexBuffer, &strides, &offset);
	// �s�N�Z���V�F�[�_�[�Ƀe�N�X�`����n��
	d3d.m_deviceContext->PSSetShaderResources(0, 1, &texture);
	// �T���v���[���s�N�Z���V�F�[�_�[�ɓn��
	//d3d.m_deviceContext->PSSetSamplers(0, 1, &d3d.m_Smapler);
	// ��P�����@���@�`�悷�钸�_��
	d3d.m_deviceContext->Draw(vertexNum, 0); // �`�施��
}

bool CGameObject::isCheckObject(const CGameObject* other) const
{
	//// ���E�̓������Ă��邩�ǂ����𔻒肷��
	//bool pos_x = this->transform->Right+0.2f >= other->transform->Left &&
	//	this->transform->Left-0.2f <= other->transform->Right;

	//// �㉺�̓������Ă��邩�ǂ����𔻒肷��
	//bool pos_y = this->transform->Top+0.3f >= other->transform->Top &&
	//	this->transform->Bottom-0.3f <= other->transform->Bottom;

	// ���E�̓������Ă��邩�ǂ����𔻒肷��
	bool pos_x = this->transform->Left <= other->transform->Left &&
		this->transform->Right >= other->transform->Right;

	// �㉺�̓������Ă��邩�ǂ����𔻒肷��
	bool pos_y = this->transform->Top + 0.2f >= other->transform->Top &&
		this->transform->Bottom - 0.2f <= other->transform->Bottom;

	return pos_x && pos_y;
}

const int CGameObject::GetLayer() const
{
	return static_cast<int>(DrawNum);
}
