#include "CDirectx.h"
#include <atltypes.h> // CRect���g�����߂̃w�b�_�[�t�@�C��

#include "WICTextureLoader.h"	// �e�N�X�`����ǂݍ��ގ��Ɏg�p����t�@�C��
#include "VertexShader.h"
#include "PixelShader.h"

HRESULT CDirectX::D3D_Create(HWND hWnd)
{
	// HRESULT�^�E�E�EWindows�v���O�����Ŋ֐����s�̐���/���s���󂯎��
	HRESULT  hr = NULL;

	UINT flags = 0;

#ifdef _DEBUG
	flags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

	D3D_FEATURE_LEVEL pLevels[] = { D3D_FEATURE_LEVEL_11_0 };
	D3D_FEATURE_LEVEL level;

	CRect rect;
	DXGI_SWAP_CHAIN_DESC scDesc;

	::GetClientRect(hWnd, &rect);
	::ZeroMemory(&scDesc, sizeof(scDesc));
	scDesc.BufferCount = 1;									// �o�b�t�@�̐�
	scDesc.BufferDesc.Width = rect.Width();					// �o�b�t�@�̉���
	scDesc.BufferDesc.Height = rect.Height();				// �o�b�t�@�̏c��
	scDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;	// �J���[�t�H�[�}�b�g
	scDesc.BufferDesc.RefreshRate.Numerator = 60;			// ���t���b�V�����[�g�̕���
	scDesc.BufferDesc.RefreshRate.Denominator = 1;			// ���t���b�V�����[�g�̕��q
	scDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;	// �o�b�t�@�̎g�����iUsage => �g�p���@�j
	scDesc.OutputWindow = hWnd;								// �o�͑Ώۂ̃E�B���h�E�n���h��
	scDesc.SampleDesc.Count = 1;							// �}���`�T���v�����O�̃T���v�����i���g�p�͂P�j
	scDesc.SampleDesc.Quality = 0;							// �}���`�T���v�����O�̕i���i���g�p�͂O�j
	scDesc.Windowed = true;									// �E�B���h�E���[�h�ƃt���X�N���[�����[�h�̐؂�ւ�

	// DirectX11�f�o�C�X�A�R���e�L�X�g�A�X���b�v�`�F�C���쐬
	hr = D3D11CreateDeviceAndSwapChain(
		NULL,						// �r�f�I�A�_�v�^���w��i nullptr�͊��� �j
		D3D_DRIVER_TYPE_HARDWARE,	// �h���C�o�^�C�v
		NULL,						// D3D_DRIVER_TYPE_SOFTWARE�w�莞�Ɏg�p
		flags,						// �t���O�w��
		pLevels,					// D3D_FEATURE_LEVEL�w��Ŏ����Œ�`�����z����w��\
		1,							// ���D3D_FEATURE_LEVEL�̔z��̗v�f��
		D3D11_SDK_VERSION,			// SDK�o�[�W����
		&scDesc,					// DXGI_SWAP_CHAIN_DESC
		&D3D.m_swapChain,			// �֐���������SwapChain�̏o�͐�
		&D3D.m_device,				// �֐���������Device�̏o�͐�
		&level,						// ��������D3D_FEATURE_LEVEL�̏o�͐�
		&D3D.m_deviceContext		// �֐���������Context�̏o�͐�
	);
	if (FAILED(hr)) { return hr; }

	// �o�b�N�o�b�t�@���擾����
	hr = D3D.m_swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&D3D.m_backBaffer);
	if (FAILED(hr)) { return hr; }

	// �����_�[�r���[���쐬
	hr = D3D.m_device->CreateRenderTargetView(D3D.m_backBaffer, NULL, &D3D.m_renderTargetView);
	// �g��Ȃ��̂ŉ������
	D3D.m_backBaffer->Release();
	if (FAILED(hr)) { return hr; }

	// ���X�^���C�U�쐬�@�� �摜���]���Ɏg�p����
	D3D11_RASTERIZER_DESC rsDesc;

	rsDesc.FillMode = D3D11_FILL_SOLID;		// 
	rsDesc.CullMode = D3D11_CULL_NONE;		// 
	rsDesc.FrontCounterClockwise = FALSE;	// 
	rsDesc.DepthBias = 0;					// 
	rsDesc.DepthBiasClamp = 0.0f;			// 
	rsDesc.DepthClipEnable = FALSE;			// 
	rsDesc.ScissorEnable = FALSE;			// 
	rsDesc.MultisampleEnable = TRUE;		// 
	rsDesc.AntialiasedLineEnable = FALSE;	// 

	// ���X�^���C�U�쐬
	hr = D3D.m_device->CreateRasterizerState(&rsDesc, &D3D.m_Rastaerizer);
	if (FAILED(hr)) { return hr; }


	/* �[�x/�X�e���V���o�b�t�@�͉A�ʏ����i��O�ɂ�����̂����ɂ�����̂��B�������j���s�����Ƃ��o����
	   ���̏����ɂ�Z�\�[�g�@��Z�o�b�t�@�@�̓���邪�������Ȃ��̂�`�悷�邱�Ƃ��Ȃ������{�I�ɂ�
	   Z�o�b�t�@�@���g�p���Ă������Ƃɂ���*/

	   // �[�x/�o�b�t�@�e�N�X�`���̍쐬
	D3D11_TEXTURE2D_DESC txDesc;

	ZeroMemory(&txDesc, sizeof(txDesc));
	txDesc.Width = rect.Width();							// ��
	txDesc.Height = rect.Height();							// ����
	txDesc.MipLevels = 1;									// �~�b�v�}�b�v�E���x����
	txDesc.ArraySize = 1;									// �z��T�C�Y
	txDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;			// �t�H�[�}�b�g�i�[�x�̂݁j
	txDesc.SampleDesc.Count = 1;							// �}���`�T���v�����O�̐ݒ�
	txDesc.SampleDesc.Quality = 0;							// �}���`�T���v�����O�̕i��
	txDesc.Usage = D3D11_USAGE_DEFAULT;						// �f�t�H���g�g�p�@
	txDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;				// �[�x/�X�e���V���Ƃ��Ďg�p
	txDesc.CPUAccessFlags = 0;								// CPU����A�N�Z�X���Ȃ�
	txDesc.MiscFlags = 0;									// ���̑��̐ݒ�(���͂Ȃ�)

	hr = D3D.m_device->CreateTexture2D(&txDesc, NULL, &D3D.m_DepthStencilTexture);
	if (FAILED(hr)) { return hr; }

	// �[�x/�X�e���V���r���[�̍쐬
	D3D11_DEPTH_STENCIL_VIEW_DESC dsDesc;
	ZeroMemory(&dsDesc, sizeof(dsDesc));
	dsDesc.Format = txDesc.Format;		// �r���[�̃t�H�[�}�b�g
	dsDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	//dsDesc.Flags = 0;
	dsDesc.Texture2D.MipSlice = 0;
	hr = D3D.m_device->CreateDepthStencilView(D3D.m_DepthStencilTexture, &dsDesc, &D3D.m_DepthStencilView);
	if (FAILED(hr)) { return hr; }

	

	// �C���v�b�g���C�A�E�g�쐬
	// �����_�P������ɂǂ�ȃf�[�^���܂܂�邩��Direct3D�ɋ�����
	D3D11_INPUT_ELEMENT_DESC g_VertexDesc[]
	{
		// �ʒu���W������Ƃ������Ƃ�`����
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0,
			D3D11_INPUT_PER_VERTEX_DATA, 0 },

			// UV���W������Ƃ������Ƃ�`����
		{ "TEX",    0, DXGI_FORMAT_R32G32_FLOAT, 0,
			D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};

	// �C���v�b�g���C�A�E�g�쐬
	hr = D3D.m_device->CreateInputLayout(g_VertexDesc, ARRAYSIZE(g_VertexDesc), g_vs_main, sizeof(g_vs_main), &D3D.m_InputLayout);
	if (FAILED(hr)) { return hr; }

	// �V�F�[�_�[�̃I�u�W�F�N�g����

	// ���_�V�F�[�_�[�쐬
	hr = D3D.m_device->CreateVertexShader(&g_vs_main, sizeof(g_vs_main), NULL, &D3D.m_VertexShader);
	if (FAILED(hr)) { return hr; }

	// �s�N�Z���V�F�[�_�[�쐬
	hr = D3D.m_device->CreatePixelShader(&g_ps_main, sizeof(g_ps_main), NULL, &D3D.m_PixelShader);
	if (FAILED(hr)) { return hr; }

	//::GetClientRect(hWnd, &rect);
	D3D.m_ViewPort.TopLeftX = 0;
	D3D.m_ViewPort.TopLeftY = 0;
	D3D.m_ViewPort.Width = (FLOAT)rect.Width();
	D3D.m_ViewPort.Height = (FLOAT)rect.Height();
	D3D.m_ViewPort.MinDepth = 0.0f;
	D3D.m_ViewPort.MaxDepth = 1.0f;

	// �T���v���[�ݒ�
	D3D11_SAMPLER_DESC smpDesc;

	::ZeroMemory(&smpDesc, sizeof(smpDesc));
	smpDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
	smpDesc.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
	smpDesc.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
	smpDesc.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
	// �T���v���[�쐬
	hr = D3D.m_device->CreateSamplerState(&smpDesc, &D3D.m_Smapler);
	if (FAILED(hr)) { return hr; }

	
	// �萔�o�b�t�@�쐬
	D3D11_BUFFER_DESC cbDesc;
	cbDesc.ByteWidth = sizeof(ConstBuffer);// ��������萔�o�b�t�@�̃T�C�Y
	cbDesc.Usage = D3D11_USAGE_DEFAULT;
	cbDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;// �萔�o�b�t�@�쐬���w��
	cbDesc.CPUAccessFlags = 0;
	cbDesc.MiscFlags = 0;
	cbDesc.StructureByteStride = 0;

	hr = D3D.m_device->CreateBuffer(&cbDesc, NULL, &D3D.m_ContextBuffer);

	//�u�����h�X�e�[�g ���ߏ�������Z�������\�ɂ��鍇�����@
	D3D11_BLEND_DESC BlendState;
	ZeroMemory(&BlendState, sizeof(D3D11_BLEND_DESC));
	BlendState.AlphaToCoverageEnable = FALSE;
	BlendState.IndependentBlendEnable = FALSE;
	BlendState.RenderTarget[0].BlendEnable = TRUE;
	BlendState.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	// �w�i�F�Ɋ|�����킹��W��
	BlendState.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	BlendState.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	BlendState.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	BlendState.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	BlendState.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	BlendState.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
	hr = D3D.m_device->CreateBlendState(&BlendState, &D3D.m_BlendState);

	D3D.m_deviceContext->OMSetBlendState(D3D.m_BlendState, NULL, 0xffffffff);

	// ���Z�����̐ݒ�����
	// �w�i�F�Ɋ|�����킹��W��
	//BlendState.RenderTarget[0].DestBlend = D3D11_BLEND_ONE;
	//D3D.m_device->CreateBlendState(&BlendState, &D3D.m_pBlendStateAdditive);

	return hr;
}

void CDirectX::D3D_Release()
{
	// �e��ϐ��̉��
	//SAFE_RELEASE(D3D.m_device);
	SAFE_RELEASE(D3D.m_deviceContext);
	SAFE_RELEASE(D3D.m_renderTargetView);
	SAFE_RELEASE(D3D.m_swapChain);
	SAFE_RELEASE(D3D.m_renderTargetView);
	SAFE_RELEASE(D3D.m_backBaffer);
	SAFE_RELEASE(D3D.m_DepthStencilTexture);
	SAFE_RELEASE(D3D.m_DepthStencilView);
	SAFE_RELEASE(D3D.m_InputLayout);
	SAFE_RELEASE(D3D.m_VertexBuffer);
	SAFE_RELEASE(D3D.m_VertexShader);
	SAFE_RELEASE(D3D.m_PixelShader);
	SAFE_RELEASE(D3D.m_Smapler);
	SAFE_RELEASE(D3D.m_ContextBuffer);
	SAFE_RELEASE(D3D.m_Rastaerizer);

}

int CDirectX::D3D_CreateSquare(FLOAT_XY center, FLOAT_XY size, FLOAT_XY uv, ID3D11Buffer** vb)
{
	float left = center.x - size.x/2.0f;
	float right = left + size.x;
	float top = center.y + size.y / 2.0f;
	float bottom = top - size.y;

	Vertex vertex_list[] =
	{
		{left	,top		,0.5f,0.00f	,0.00f},	// ����
		{right	,bottom		,0.5f,uv.x	,uv.y },	// �E��
		{left	,bottom		,0.5f,0.00f	,uv.y },	// ����

		{left	,top		,0.5f,0.00f	,0.00f},	// ����
		{right	,top		,0.5f,uv.x	,0.00f},	// �E��
		{right	,bottom		,0.5f,uv.x	,uv.y }	// �E��

	};


	// ���_�o�b�t�@�쐬
	D3D11_BUFFER_DESC bufferDesc;
	bufferDesc.ByteWidth = sizeof(vertex_list);			// �m�ۂ���o�b�t�@���w�肷��
	bufferDesc.Usage = D3D11_USAGE_DEFAULT;
	bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;	// ���_�o�b�t�@�Ɏw�肷��
	bufferDesc.CPUAccessFlags = 0;
	bufferDesc.MiscFlags = 0;
	bufferDesc.StructureByteStride = 0;

	D3D11_SUBRESOURCE_DATA subResourceData;
	subResourceData.pSysMem = vertex_list;	// VRAM�ɑ���f�[�^���w�肷��
	subResourceData.SysMemPitch = 0;
	subResourceData.SysMemSlicePitch = 0;

	D3D.m_device->CreateBuffer(&bufferDesc, &subResourceData, vb);
	
	return sizeof(vertex_list) / sizeof(vertex_list[0]);
}

int CDirectX::D3D_CreateHexagon(FLOAT_XY center, FLOAT_XY size, FLOAT_XY uv, ID3D11Buffer** vb)
{
	// ���̃T�C�Y�𕪊����ē_�����߂�
	float adjustment = size.x /3.95f;
	float u_adjust = uv.x /3.95f;

	float left = center.x - size.x / 2.0f;
	float right = left + size.x;
	float top = center.y + size.y / 2.0f;
	float bottom = top - size.y;

	Vertex vertex_list[] =
	{
		{left				,center.y	,0.5f,0.00f		,uv.y / 2.0f	},	// ����
		{left + adjustment	,top		,0.5f,u_adjust	,0.00f		},	// �E��
		{left + adjustment	,bottom		,0.5f,u_adjust	,uv.y		},	// ����

		{left + adjustment	,bottom		,0.5f,u_adjust			,uv.y		},	// �E��
		{left + adjustment	,top		,0.5f,u_adjust			,0.00f		},	// ����
		{right - adjustment	,top		,0.5f,uv.x - u_adjust	,0.00f		},	// �E��

		{left + adjustment	,bottom		,0.5f,u_adjust			,uv.y	},	// �E��
		{right - adjustment	,top		,0.5f,uv.x - u_adjust	,0.00f	},	// ����
		{right - adjustment	,bottom		,0.5f,uv.x - u_adjust	,uv.y	},	// �E��

		{right				,center.y	,0.5f,uv.x				,uv.y / 2.0f		},	// ����
		{right - adjustment	,bottom		,0.5f,uv.x - u_adjust	,uv.y		},	// �E��
		{right - adjustment	,top		,0.5f,uv.x - u_adjust	,0.00f		}	// �E��
	};
		// ���_�o�b�t�@�쐬
	D3D11_BUFFER_DESC bufferDesc;
	bufferDesc.ByteWidth = sizeof(vertex_list);			// �m�ۂ���o�b�t�@���w�肷��
	bufferDesc.Usage = D3D11_USAGE_DEFAULT;
	bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;	// ���_�o�b�t�@�Ɏw�肷��
	bufferDesc.CPUAccessFlags = 0;
	bufferDesc.MiscFlags = 0;
	bufferDesc.StructureByteStride = 0;

	D3D11_SUBRESOURCE_DATA subResourceData;
	subResourceData.pSysMem = vertex_list;	// VRAM�ɑ���f�[�^���w�肷��
	subResourceData.SysMemPitch = 0;
	subResourceData.SysMemSlicePitch = 0;

	D3D.m_device->CreateBuffer(&bufferDesc, &subResourceData, vb);

	return sizeof(vertex_list) / sizeof(vertex_list[0]);
}

HRESULT CDirectX::D3D_LoadTexture(const wchar_t* filename, ID3D11ShaderResourceView** texture)
{
	HRESULT hr;

	hr = DirectX::CreateWICTextureFromFile(D3D.m_device, filename, NULL, texture);

	if (FAILED(hr))
	{
		MessageBoxA(NULL, "�e�N�X�`���ǂݍ��݂Ɏ��s", "�G���[",
			MB_OK | MB_ICONERROR);
	}

	return hr;
}

void CDirectX::D3D_ClearScreen()
{
	// �F�ɍŏ��ɓh��Ԃ�
	float clearColor[4] = { 0.0f,0.0f,1.0f,1.0f };

	// ���ߏ���
	D3D.m_deviceContext->OMSetBlendState(D3D.m_BlendState, clearColor, 0xffffffff);
	// �`���̃L�����o�X�Ǝg�p����[�x�o�b�t�@���w�肷��
	D3D.m_deviceContext->OMSetRenderTargets(1, &D3D.m_renderTargetView, D3D.m_DepthStencilView);
	// �`���L�����o�X��h��Ԃ�
	D3D.m_deviceContext->ClearRenderTargetView(D3D.m_renderTargetView, clearColor);

	D3D.m_deviceContext->RSSetState(D3D.m_Rastaerizer);
	// �[�x�o�b�t�@�����Z�b�g����
	D3D.m_deviceContext->ClearDepthStencilView(D3D.m_DepthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);


	D3D.m_deviceContext->IASetInputLayout(D3D.m_InputLayout);
	D3D.m_deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	D3D.m_deviceContext->VSSetShader(D3D.m_VertexShader, NULL, 0);
	D3D.m_deviceContext->RSSetViewports(1, &D3D.m_ViewPort);
	D3D.m_deviceContext->PSSetShader(D3D.m_PixelShader, NULL, 0);

	
	// �T���v���[���s�N�Z���V�F�[�_�[�ɓn��
	D3D.m_deviceContext->PSSetSamplers(0, 1, &D3D.m_Smapler);

	// �萔�o�b�t�@�𒸓_�V�F�[�_�[�ɃZ�b�g����
	D3D.m_deviceContext->VSSetConstantBuffers(
		0, 1, &D3D.m_ContextBuffer);
	// �萔�o�b�t�@���s�N�Z���V�F�[�_�[�ɃZ�b�g����
	D3D.m_deviceContext->PSSetConstantBuffers(
		0, 1, &D3D.m_ContextBuffer);
	
}

void CDirectX::D3D_UpdateScreen()
{
	D3D.m_swapChain->Present(0, 0);
}
CDirectX::~CDirectX()
{

}
