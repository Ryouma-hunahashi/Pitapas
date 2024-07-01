#include "CDirectx.h"
#include <atltypes.h> // CRectを使うためのヘッダーファイル

#include "WICTextureLoader.h"	// テクスチャを読み込む時に使用するファイル
#include "VertexShader.h"
#include "PixelShader.h"

HRESULT CDirectX::D3D_Create(HWND hWnd)
{
	// HRESULT型・・・Windowsプログラムで関数実行の成功/失敗を受け取る
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
	scDesc.BufferCount = 1;									// バッファの数
	scDesc.BufferDesc.Width = rect.Width();					// バッファの横幅
	scDesc.BufferDesc.Height = rect.Height();				// バッファの縦幅
	scDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;	// カラーフォーマット
	scDesc.BufferDesc.RefreshRate.Numerator = 60;			// リフレッシュレートの分母
	scDesc.BufferDesc.RefreshRate.Denominator = 1;			// リフレッシュレートの分子
	scDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;	// バッファの使い方（Usage => 使用方法）
	scDesc.OutputWindow = hWnd;								// 出力対象のウィンドウハンドル
	scDesc.SampleDesc.Count = 1;							// マルチサンプリングのサンプル数（未使用は１）
	scDesc.SampleDesc.Quality = 0;							// マルチサンプリングの品質（未使用は０）
	scDesc.Windowed = true;									// ウィンドウモードとフルスクリーンモードの切り替え

	// DirectX11デバイス、コンテキスト、スワップチェイン作成
	hr = D3D11CreateDeviceAndSwapChain(
		NULL,						// ビデオアダプタを指定（ nullptrは既定 ）
		D3D_DRIVER_TYPE_HARDWARE,	// ドライバタイプ
		NULL,						// D3D_DRIVER_TYPE_SOFTWARE指定時に使用
		flags,						// フラグ指定
		pLevels,					// D3D_FEATURE_LEVEL指定で自分で定義した配列を指定可能
		1,							// 上のD3D_FEATURE_LEVELの配列の要素数
		D3D11_SDK_VERSION,			// SDKバージョン
		&scDesc,					// DXGI_SWAP_CHAIN_DESC
		&D3D.m_swapChain,			// 関数成功時のSwapChainの出力先
		&D3D.m_device,				// 関数成功時のDeviceの出力先
		&level,						// 成功したD3D_FEATURE_LEVELの出力先
		&D3D.m_deviceContext		// 関数成功時のContextの出力先
	);
	if (FAILED(hr)) { return hr; }

	// バックバッファを取得する
	hr = D3D.m_swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&D3D.m_backBaffer);
	if (FAILED(hr)) { return hr; }

	// レンダービューを作成
	hr = D3D.m_device->CreateRenderTargetView(D3D.m_backBaffer, NULL, &D3D.m_renderTargetView);
	// 使わないので解放する
	D3D.m_backBaffer->Release();
	if (FAILED(hr)) { return hr; }

	// ラスタライザ作成　※ 画像反転時に使用する
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

	// ラスタライザ作成
	hr = D3D.m_device->CreateRasterizerState(&rsDesc, &D3D.m_Rastaerizer);
	if (FAILED(hr)) { return hr; }


	/* 深度/ステンシルバッファは陰面処理（手前にあるものが後ろにあるものを隠す処理）を行うことが出来る
	   その処理にはZソート法とZバッファ法の二つあるが半透明なものを描画することがない限り基本的には
	   Zバッファ法を使用していくことにする*/

	   // 深度/バッファテクスチャの作成
	D3D11_TEXTURE2D_DESC txDesc;

	ZeroMemory(&txDesc, sizeof(txDesc));
	txDesc.Width = rect.Width();							// 幅
	txDesc.Height = rect.Height();							// 高さ
	txDesc.MipLevels = 1;									// ミップマップ・レベル数
	txDesc.ArraySize = 1;									// 配列サイズ
	txDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;			// フォーマット（深度のみ）
	txDesc.SampleDesc.Count = 1;							// マルチサンプリングの設定
	txDesc.SampleDesc.Quality = 0;							// マルチサンプリングの品質
	txDesc.Usage = D3D11_USAGE_DEFAULT;						// デフォルト使用法
	txDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;				// 深度/ステンシルとして使用
	txDesc.CPUAccessFlags = 0;								// CPUからアクセスしない
	txDesc.MiscFlags = 0;									// その他の設定(今はなし)

	hr = D3D.m_device->CreateTexture2D(&txDesc, NULL, &D3D.m_DepthStencilTexture);
	if (FAILED(hr)) { return hr; }

	// 深度/ステンシルビューの作成
	D3D11_DEPTH_STENCIL_VIEW_DESC dsDesc;
	ZeroMemory(&dsDesc, sizeof(dsDesc));
	dsDesc.Format = txDesc.Format;		// ビューのフォーマット
	dsDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	//dsDesc.Flags = 0;
	dsDesc.Texture2D.MipSlice = 0;
	hr = D3D.m_device->CreateDepthStencilView(D3D.m_DepthStencilTexture, &dsDesc, &D3D.m_DepthStencilView);
	if (FAILED(hr)) { return hr; }

	

	// インプットレイアウト作成
	// →頂点１つあたりにどんなデータが含まれるかをDirect3Dに教える
	D3D11_INPUT_ELEMENT_DESC g_VertexDesc[]
	{
		// 位置座標があるということを伝える
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0,
			D3D11_INPUT_PER_VERTEX_DATA, 0 },

			// UV座標があるということを伝える
		{ "TEX",    0, DXGI_FORMAT_R32G32_FLOAT, 0,
			D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};

	// インプットレイアウト作成
	hr = D3D.m_device->CreateInputLayout(g_VertexDesc, ARRAYSIZE(g_VertexDesc), g_vs_main, sizeof(g_vs_main), &D3D.m_InputLayout);
	if (FAILED(hr)) { return hr; }

	// シェーダーのオブジェクト生成

	// 頂点シェーダー作成
	hr = D3D.m_device->CreateVertexShader(&g_vs_main, sizeof(g_vs_main), NULL, &D3D.m_VertexShader);
	if (FAILED(hr)) { return hr; }

	// ピクセルシェーダー作成
	hr = D3D.m_device->CreatePixelShader(&g_ps_main, sizeof(g_ps_main), NULL, &D3D.m_PixelShader);
	if (FAILED(hr)) { return hr; }

	//::GetClientRect(hWnd, &rect);
	D3D.m_ViewPort.TopLeftX = 0;
	D3D.m_ViewPort.TopLeftY = 0;
	D3D.m_ViewPort.Width = (FLOAT)rect.Width();
	D3D.m_ViewPort.Height = (FLOAT)rect.Height();
	D3D.m_ViewPort.MinDepth = 0.0f;
	D3D.m_ViewPort.MaxDepth = 1.0f;

	// サンプラー設定
	D3D11_SAMPLER_DESC smpDesc;

	::ZeroMemory(&smpDesc, sizeof(smpDesc));
	smpDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
	smpDesc.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
	smpDesc.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
	smpDesc.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
	// サンプラー作成
	hr = D3D.m_device->CreateSamplerState(&smpDesc, &D3D.m_Smapler);
	if (FAILED(hr)) { return hr; }

	
	// 定数バッファ作成
	D3D11_BUFFER_DESC cbDesc;
	cbDesc.ByteWidth = sizeof(ConstBuffer);// 今から作る定数バッファのサイズ
	cbDesc.Usage = D3D11_USAGE_DEFAULT;
	cbDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;// 定数バッファ作成を指定
	cbDesc.CPUAccessFlags = 0;
	cbDesc.MiscFlags = 0;
	cbDesc.StructureByteStride = 0;

	hr = D3D.m_device->CreateBuffer(&cbDesc, NULL, &D3D.m_ContextBuffer);

	//ブレンドステート 透過処理や加算合成を可能にする合成方法
	D3D11_BLEND_DESC BlendState;
	ZeroMemory(&BlendState, sizeof(D3D11_BLEND_DESC));
	BlendState.AlphaToCoverageEnable = FALSE;
	BlendState.IndependentBlendEnable = FALSE;
	BlendState.RenderTarget[0].BlendEnable = TRUE;
	BlendState.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	// 背景色に掛け合わせる係数
	BlendState.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	BlendState.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	BlendState.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	BlendState.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	BlendState.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	BlendState.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
	hr = D3D.m_device->CreateBlendState(&BlendState, &D3D.m_BlendState);

	D3D.m_deviceContext->OMSetBlendState(D3D.m_BlendState, NULL, 0xffffffff);

	// 加算合成の設定を作る
	// 背景色に掛け合わせる係数
	//BlendState.RenderTarget[0].DestBlend = D3D11_BLEND_ONE;
	//D3D.m_device->CreateBlendState(&BlendState, &D3D.m_pBlendStateAdditive);

	return hr;
}

void CDirectX::D3D_Release()
{
	// 各種変数の解放
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
		{left	,top		,0.5f,0.00f	,0.00f},	// 左上
		{right	,bottom		,0.5f,uv.x	,uv.y },	// 右下
		{left	,bottom		,0.5f,0.00f	,uv.y },	// 左下

		{left	,top		,0.5f,0.00f	,0.00f},	// 左上
		{right	,top		,0.5f,uv.x	,0.00f},	// 右上
		{right	,bottom		,0.5f,uv.x	,uv.y }	// 右下

	};


	// 頂点バッファ作成
	D3D11_BUFFER_DESC bufferDesc;
	bufferDesc.ByteWidth = sizeof(vertex_list);			// 確保するバッファを指定する
	bufferDesc.Usage = D3D11_USAGE_DEFAULT;
	bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;	// 頂点バッファに指定する
	bufferDesc.CPUAccessFlags = 0;
	bufferDesc.MiscFlags = 0;
	bufferDesc.StructureByteStride = 0;

	D3D11_SUBRESOURCE_DATA subResourceData;
	subResourceData.pSysMem = vertex_list;	// VRAMに送るデータを指定する
	subResourceData.SysMemPitch = 0;
	subResourceData.SysMemSlicePitch = 0;

	D3D.m_device->CreateBuffer(&bufferDesc, &subResourceData, vb);
	
	return sizeof(vertex_list) / sizeof(vertex_list[0]);
}

int CDirectX::D3D_CreateHexagon(FLOAT_XY center, FLOAT_XY size, FLOAT_XY uv, ID3D11Buffer** vb)
{
	// 横のサイズを分割して点を求める
	float adjustment = size.x /3.95f;
	float u_adjust = uv.x /3.95f;

	float left = center.x - size.x / 2.0f;
	float right = left + size.x;
	float top = center.y + size.y / 2.0f;
	float bottom = top - size.y;

	Vertex vertex_list[] =
	{
		{left				,center.y	,0.5f,0.00f		,uv.y / 2.0f	},	// 左上
		{left + adjustment	,top		,0.5f,u_adjust	,0.00f		},	// 右下
		{left + adjustment	,bottom		,0.5f,u_adjust	,uv.y		},	// 左下

		{left + adjustment	,bottom		,0.5f,u_adjust			,uv.y		},	// 右上
		{left + adjustment	,top		,0.5f,u_adjust			,0.00f		},	// 左上
		{right - adjustment	,top		,0.5f,uv.x - u_adjust	,0.00f		},	// 右下

		{left + adjustment	,bottom		,0.5f,u_adjust			,uv.y	},	// 右上
		{right - adjustment	,top		,0.5f,uv.x - u_adjust	,0.00f	},	// 左上
		{right - adjustment	,bottom		,0.5f,uv.x - u_adjust	,uv.y	},	// 右下

		{right				,center.y	,0.5f,uv.x				,uv.y / 2.0f		},	// 左上
		{right - adjustment	,bottom		,0.5f,uv.x - u_adjust	,uv.y		},	// 右上
		{right - adjustment	,top		,0.5f,uv.x - u_adjust	,0.00f		}	// 右下
	};
		// 頂点バッファ作成
	D3D11_BUFFER_DESC bufferDesc;
	bufferDesc.ByteWidth = sizeof(vertex_list);			// 確保するバッファを指定する
	bufferDesc.Usage = D3D11_USAGE_DEFAULT;
	bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;	// 頂点バッファに指定する
	bufferDesc.CPUAccessFlags = 0;
	bufferDesc.MiscFlags = 0;
	bufferDesc.StructureByteStride = 0;

	D3D11_SUBRESOURCE_DATA subResourceData;
	subResourceData.pSysMem = vertex_list;	// VRAMに送るデータを指定する
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
		MessageBoxA(NULL, "テクスチャ読み込みに失敗", "エラー",
			MB_OK | MB_ICONERROR);
	}

	return hr;
}

void CDirectX::D3D_ClearScreen()
{
	// 青色に最初に塗りつぶす
	float clearColor[4] = { 0.0f,0.0f,1.0f,1.0f };

	// 透過処理
	D3D.m_deviceContext->OMSetBlendState(D3D.m_BlendState, clearColor, 0xffffffff);
	// 描画先のキャンバスと使用する深度バッファを指定する
	D3D.m_deviceContext->OMSetRenderTargets(1, &D3D.m_renderTargetView, D3D.m_DepthStencilView);
	// 描画先キャンバスを塗りつぶす
	D3D.m_deviceContext->ClearRenderTargetView(D3D.m_renderTargetView, clearColor);

	D3D.m_deviceContext->RSSetState(D3D.m_Rastaerizer);
	// 深度バッファをリセットする
	D3D.m_deviceContext->ClearDepthStencilView(D3D.m_DepthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);


	D3D.m_deviceContext->IASetInputLayout(D3D.m_InputLayout);
	D3D.m_deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	D3D.m_deviceContext->VSSetShader(D3D.m_VertexShader, NULL, 0);
	D3D.m_deviceContext->RSSetViewports(1, &D3D.m_ViewPort);
	D3D.m_deviceContext->PSSetShader(D3D.m_PixelShader, NULL, 0);

	
	// サンプラーをピクセルシェーダーに渡す
	D3D.m_deviceContext->PSSetSamplers(0, 1, &D3D.m_Smapler);

	// 定数バッファを頂点シェーダーにセットする
	D3D.m_deviceContext->VSSetConstantBuffers(
		0, 1, &D3D.m_ContextBuffer);
	// 定数バッファをピクセルシェーダーにセットする
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
