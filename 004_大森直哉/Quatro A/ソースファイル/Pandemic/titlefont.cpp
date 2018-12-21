//=============================================================================
//
// タイトル文字処理 [titlefont.cpp]
// Author : NAOYA OMORI
//
//=============================================================================
#include "titlefont.h"

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void MakeVertexTitleFont(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9	g_pTextureTitleFont = NULL;	// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTitleFont = NULL;	// 頂点バッファのポインタ

//=============================================================================
// 初期化処理
//=============================================================================
void InitTitleFont(void)
{

	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffTitleFont,
		NULL);

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/pandemicfont.png", &g_pTextureTitleFont);

	//頂点設定
	MakeVertexTitleFont(pDevice);

}

//=============================================================================
// 終了処理
//=============================================================================
void UninitTitleFont(void)
{
	// 頂点バッファの開放
	if (g_pVtxBuffTitleFont != NULL)
	{
		g_pVtxBuffTitleFont->Release();
		g_pVtxBuffTitleFont = NULL;
	}

	// テクスチャの開放
	if (g_pTextureTitleFont != NULL)
	{
		g_pTextureTitleFont->Release();
		g_pTextureTitleFont = NULL;
	}

}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateTitleFont(void)
{

}

//=============================================================================
// 描画処理
//=============================================================================
void DrawTitleFont(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//データストリームにセット
	pDevice->SetStreamSource(0,
		g_pVtxBuffTitleFont,
		0,
		sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, g_pTextureTitleFont);

	// ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}

//=============================================================================
// 頂点情報の作成
//=============================================================================
void MakeVertexTitleFont(LPDIRECT3DDEVICE9 pDevice)
{
	VERTEX_2D *pVtx;

	//ロック
	g_pVtxBuffTitleFont->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(200, 100, 0.0f);					//xy座標で位置決め
	pVtx[1].pos = D3DXVECTOR3(917, 100, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(200, 230, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(917, 230, 0.0f);

	// rhwの設定
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	// 頂点カラーの設定
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);		//RGBAの色を入れる
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	// テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0, 0);
	pVtx[1].tex = D3DXVECTOR2(1, 0);
	pVtx[2].tex = D3DXVECTOR2(0, 1);
	pVtx[3].tex = D3DXVECTOR2(1, 1);

	//ロック解除
	g_pVtxBuffTitleFont->Unlock();
}