#pragma once

#include <d3d11.h>  // DirectX11を使うためのヘッダーファイル
#include <DirectXMath.h> // DirextXの数学関連のヘッダーファイル
#include <vector>

// ライブラリのリンク設定
#pragma comment (lib, "d3d11.lib")

#include <iostream>
#include <wrl/client.h>
using Microsoft::WRL::ComPtr;


// Direct3D解放の簡略化マクロ
#define SAFE_RELEASE(p)      { if( NULL != p ) { p->Release(); p = NULL; } }

class CDirectX
{
public:
	// 構造体の定義
	// ｘｙを表す構造体
	struct FLOAT_XY
	{
		float x, y;
	};

	struct Vertex {
		float pos[3];
		float col[4];
	};

public:
	// 定数バッファ用構造体
	struct ConstBuffer
	{
		// UV座標移動行列
		DirectX::XMMATRIX matrixTex;
		// 投影行列
		DirectX::XMMATRIX matrixProj;
		// ワールド変換行列
		DirectX::XMMATRIX matrixWorld;
		// マテリアル色
		DirectX::XMFLOAT4 materialDiffuse;
	};
public:
	struct Direct
	{
		ID3D11Device*				m_device = NULL;					// デバイス
		ID3D11DeviceContext*		m_deviceContext = NULL;				// デバイスコンテキスト
		IDXGISwapChain*				m_swapChain = NULL;					// スワップチェイン
		ID3D11RenderTargetView*		m_renderTargetView = NULL;			// レンダーターゲットビュー
		ID3D11Texture2D*			m_backBaffer = NULL;				// バックバッファ
		ID3D11Texture2D*			m_DepthStencilTexture = NULL;		// 深度・ステンシルテクスチャ
		ID3D11DepthStencilView*		m_DepthStencilView = NULL;			// 深度・ステンシルビュー
		ID3D11InputLayout*			m_InputLayout = NULL;				// インプットレイアウト
		ID3D11Buffer*				m_VertexBuffer = NULL;				// バーテックスバッファー
		ID3D11VertexShader*			m_VertexShader = NULL;				// バーテックスシェーダー
		ID3D11PixelShader*			m_PixelShader = NULL;				// ピクセルシェーダー
		D3D11_VIEWPORT				m_ViewPort;							// ビューポート
		ID3D11SamplerState*			m_Smapler = NULL;					// サンプラー
		ID3D11Buffer*				m_ContextBuffer = NULL;				// 定数バッファ
		ID3D11BlendState*			m_BlendState = NULL;				// ブレンドステート
		ID3D11BlendState*			m_pBlendStateAdditive = NULL;		// ブレンドステート用変数（加算合成）
		ID3D11RasterizerState*		m_Rastaerizer = NULL;				// ラスタライザ設定

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
	// IASetVertexBuffersで使用する変数
	const UINT strides = sizeof(Vertex);
	const UINT offsets = 0;
	Direct D3D;
	ID3D11ShaderResourceView* textureTitle;

public:
	// DirectXの初期化
	HRESULT D3D_Create(HWND hWnd);
	// DirectXの解放
	void    D3D_Release();

	// 四角形ポリゴンを作成し、頂点バッファ生成を行う
	int D3D_CreateSquare(FLOAT_XY center, FLOAT_XY size, FLOAT_XY uv, ID3D11Buffer** vb);

	// 六角形ポリゴン生成
	int D3D_CreateHexagon(FLOAT_XY center, FLOAT_XY size, FLOAT_XY uv, ID3D11Buffer** vb);

	// テクスチャを読み込む
	// 引数：(1)ファイル名　(2)テクスチャ格納用変数のアドレス
	HRESULT D3D_LoadTexture(const wchar_t* filename, ID3D11ShaderResourceView** texture);

	// 画面塗りつぶしと設定を行う関数
	void D3D_ClearScreen();

	// 画面を更新する関数
	void D3D_UpdateScreen();

	// DirectXの構造体を取得する関数
	static CDirectX* Get() { static CDirectX instance; return &instance; }

	Direct GetDirect() { return D3D; }
	ID3D11DeviceContext* GetContext() { return D3D.m_deviceContext; }
	
	UINT GetStrides() { return sizeof(Vertex); }

private:

	CDirectX() {};
	~CDirectX();

};