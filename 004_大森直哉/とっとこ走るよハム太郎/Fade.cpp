//=============================================================================
//
// ポリゴン処理 [polygon.cpp]
// Author : AKIRA TANAKA
//
//=============================================================================
#include "fade.h"
//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void MakeVertexFade(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9	g_pTextureFade = NULL;	// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffFade = NULL;//頂点バッファのポインタ
D3DXCOLOR g_colorFade;	//フェード色
FADE g_fade = FADE_IN;
MODE g_modeNext = MODE_TITLE;

//=============================================================================
// 初期化処理
//=============================================================================
void InitFade(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	g_colorFade = D3DXCOLOR(0, 0, 0, 1.0f);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffFade,
		NULL);



	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/back.jpg", &g_pTextureFade);


	//頂点設定
	MakeVertexFade(pDevice);
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitFade(void)
{
	// テクスチャの開放4
	if (g_pVtxBuffFade != NULL)
	{
		g_pVtxBuffFade->Release();
		g_pVtxBuffFade = NULL;
	}
	if (g_pTextureFade != NULL) {
		g_pTextureFade->Release();
		g_pTextureFade = NULL;
	}

}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateFade(void)
{

	if (g_fade != FADE_NONE) {
		if (g_fade == FADE_IN) {
			g_colorFade.a -= 0.01;
			if (g_colorFade.a <= 0.0f) {
				g_colorFade.a = 0.0f;
				g_fade = FADE_NONE;
			}
		}
		else if (g_fade == FADE_OUT) {
			g_colorFade.a += 0.01;
			if (g_colorFade.a >= 1.0f)
			{
				g_colorFade.a = 1.0f;
				g_fade = FADE_IN;
				//次ぼ画面（モード）の処理
				SetMode(g_modeNext);
			}
		}
		VERTEX_2D *pVtx;

		//ロック
		g_pVtxBuffFade->Lock(0,
			0,
			(void**)&pVtx,
			0);

		pVtx[0].col = g_colorFade;
		pVtx[1].col = g_colorFade;
		pVtx[2].col = g_colorFade;
		pVtx[3].col = g_colorFade;

		//ロック解除
		g_pVtxBuffFade->Unlock();
	}
}

void SetFade(MODE mode) {
	g_fade = FADE_OUT;
	g_modeNext = mode;
}

FADE GetFade(void) {
	return g_fade;
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawFade(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//データストリームにセット
	pDevice->SetStreamSource(0,
		g_pVtxBuffFade,
		0,
		sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, g_pTextureFade);

	// ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
		0,
		2);
}

//=============================================================================
// 頂点情報の作成
//=============================================================================
void MakeVertexFade(LPDIRECT3DDEVICE9 pDevice)
{
	VERTEX_2D *pVtx;

	//ロック
	g_pVtxBuffFade->Lock(0,
		0,
		(void**)&pVtx,
		0);

	// 頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(0, 0, 0.0f);//xy座標で位置決め
	pVtx[1].pos = D3DXVECTOR3(1280, 0, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0, 720, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(1280, 720, 0.0f);


	// rhwの設定
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	// 頂点カラーの設定

	pVtx[0].col = g_colorFade;
	pVtx[1].col = g_colorFade;
	pVtx[2].col = g_colorFade;
	pVtx[3].col = g_colorFade;

	// テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0, 0);
	pVtx[1].tex = D3DXVECTOR2(1, 0);
	pVtx[2].tex = D3DXVECTOR2(0, 1);
	pVtx[3].tex = D3DXVECTOR2(1, 1);

	//ロック解除
	g_pVtxBuffFade->Unlock();
}