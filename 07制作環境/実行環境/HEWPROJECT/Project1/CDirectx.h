#pragma once

#include <d3d11.h>  // DirectX11���g�����߂̃w�b�_�[�t�@�C��
#include <DirectXMath.h> // DirextX�̐��w�֘A�̃w�b�_�[�t�@�C��
#include <vector>

// ���C�u�����̃����N�ݒ�
#pragma comment (lib, "d3d11.lib")

#include <iostream>
#include <wrl/client.h>
using Microsoft::WRL::ComPtr;


// Direct3D����̊ȗ����}�N��
#define SAFE_RELEASE(p)      { if( NULL != p ) { p->Release(); p = NULL; } }

class CDirectX
{
public:
	// �\���̂̒�`
	// ������\���\����
	struct FLOAT_XY
	{
		float x, y;
	};

	struct Vertex {
		float pos[3];
		float col[4];
	};

public:
	// �萔�o�b�t�@�p�\����
	struct ConstBuffer
	{
		// UV���W�ړ��s��
		DirectX::XMMATRIX matrixTex;
		// ���e�s��
		DirectX::XMMATRIX matrixProj;
		// ���[���h�ϊ��s��
		DirectX::XMMATRIX matrixWorld;
		// �}�e���A���F
		DirectX::XMFLOAT4 materialDiffuse;
	};
public:
	struct Direct
	{
		ID3D11Device*				m_device = NULL;					// �f�o�C�X
		ID3D11DeviceContext*		m_deviceContext = NULL;				// �f�o�C�X�R���e�L�X�g
		IDXGISwapChain*				m_swapChain = NULL;					// �X���b�v�`�F�C��
		ID3D11RenderTargetView*		m_renderTargetView = NULL;			// �����_�[�^�[�Q�b�g�r���[
		ID3D11Texture2D*			m_backBaffer = NULL;				// �o�b�N�o�b�t�@
		ID3D11Texture2D*			m_DepthStencilTexture = NULL;		// �[�x�E�X�e���V���e�N�X�`��
		ID3D11DepthStencilView*		m_DepthStencilView = NULL;			// �[�x�E�X�e���V���r���[
		ID3D11InputLayout*			m_InputLayout = NULL;				// �C���v�b�g���C�A�E�g
		ID3D11Buffer*				m_VertexBuffer = NULL;				// �o�[�e�b�N�X�o�b�t�@�[
		ID3D11VertexShader*			m_VertexShader = NULL;				// �o�[�e�b�N�X�V�F�[�_�[
		ID3D11PixelShader*			m_PixelShader = NULL;				// �s�N�Z���V�F�[�_�[
		D3D11_VIEWPORT				m_ViewPort;							// �r���[�|�[�g
		ID3D11SamplerState*			m_Smapler = NULL;					// �T���v���[
		ID3D11Buffer*				m_ContextBuffer = NULL;				// �萔�o�b�t�@
		ID3D11BlendState*			m_BlendState = NULL;				// �u�����h�X�e�[�g
		ID3D11BlendState*			m_pBlendStateAdditive = NULL;		// �u�����h�X�e�[�g�p�ϐ��i���Z�����j
		ID3D11RasterizerState*		m_Rastaerizer = NULL;				// ���X�^���C�U�ݒ�

	public:
		Direct() 
		{
		m_ViewPort.Height = 0;
		m_ViewPort.Width = 0;
		m_ViewPort.MaxDepth = 0;
		m_ViewPort.MinDepth = 0;
		m_ViewPort.TopLeftX = 0;
		m_ViewPort.TopLeftY = 0;

		}
	};
private:
	// IASetVertexBuffers�Ŏg�p����ϐ�
	const UINT strides = sizeof(Vertex);
	const UINT offsets = 0;
	Direct D3D;
	ID3D11ShaderResourceView* textureTitle;

public:
	// DirectX�̏�����
	HRESULT D3D_Create(HWND hWnd);
	// DirectX�̉��
	void    D3D_Release();

	// �l�p�`�|���S�����쐬���A���_�o�b�t�@�������s��
	int D3D_CreateSquare(FLOAT_XY center, FLOAT_XY size, FLOAT_XY uv, ID3D11Buffer** vb);

	// �Z�p�`�|���S������
	int D3D_CreateHexagon(FLOAT_XY center, FLOAT_XY size, FLOAT_XY uv, ID3D11Buffer** vb);

	// �e�N�X�`����ǂݍ���
	// �����F(1)�t�@�C�����@(2)�e�N�X�`���i�[�p�ϐ��̃A�h���X
	HRESULT D3D_LoadTexture(const wchar_t* filename, ID3D11ShaderResourceView** texture);

	// ��ʓh��Ԃ��Ɛݒ���s���֐�
	void D3D_ClearScreen();

	// ��ʂ��X�V����֐�
	void D3D_UpdateScreen();

	// DirectX�̍\���̂��擾����֐�
	static CDirectX* Get() { static CDirectX instance; return &instance; }

	Direct GetDirect() { return D3D; }
	ID3D11DeviceContext* GetContext() { return D3D.m_deviceContext; }
	
	UINT GetStrides() { return sizeof(Vertex); }

private:

	CDirectX() {};
	~CDirectX();

};