//=============================================================================
//
// 最終スコア処理 [TotalScore.cpp]
// Author : NAOYA OMORI
//
//=============================================================================
#include "TotalScore.h"
#include "fade.h"
#include "ball.h"
#include "ResultScore.h"
#include "number.h"
#include "main.h"
#include "timer.h"
#include "polygon.h"
#include "number.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MAX_DIGIT	(8)			//桁数
#define MAX_PATTEN	(10)		//１～１０まで

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void MakeVertexTotalScore(LPDIRECT3DDEVICE9 pDevice);
LPDIRECT3DTEXTURE9 g_apTextureTotalScore = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTotalScore = NULL;
TotalScore g_aTotalScore[MAX_DIGIT];
int iTotalScore;
int g_nCutVtxx;

//=============================================================================
// 初期化処理
//=============================================================================
void InitTotalScore(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	int nCutTotalScore;
	int tCount, bCount, lCount, TotalCount;

	//初期設定
	for (nCutTotalScore = 0; nCutTotalScore < MAX_DIGIT; nCutTotalScore++)
	{
		g_aTotalScore[nCutTotalScore].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aTotalScore[nCutTotalScore].nType = 0;
		g_aTotalScore[nCutTotalScore].bUse = false;
		g_aTotalScore[nCutTotalScore].posNumber = D3DXVECTOR3(0, 0, 0);
		g_aTotalScore[nCutTotalScore].rotNumber = D3DXVECTOR3(0, 0, 0);
		g_aTotalScore[nCutTotalScore].fAngleNumber = atan2f(0, 0);
		g_aTotalScore[nCutTotalScore].fLengthNumber = sqrtf(0 * 0 + 0 * 0);
	}

	iTotalScore = 0;
	g_nCutVtxx = 0;

	tCount = GetTime();
	bCount = GetBulletCount();
	lCount = GetPlayerHP();
	TotalCount = GetNumber();

	iTotalScore = tCount * bCount * lCount * TotalCount;
	

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/number000.png", &g_apTextureTotalScore);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_DIGIT,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffTotalScore,
		NULL);

	for (int x = 0; x < MAX_DIGIT; x++)
	{
		SetTotalScore(D3DXVECTOR3(805.0f + 50.0f * x, 525.0f, 0.0f));
	}

	MakeVertexTotalScore(pDevice);

}

void UninitTotalScore(void) {

	// 頂点バッファの開放
	if (g_pVtxBuffTotalScore != NULL)
	{
		g_pVtxBuffTotalScore->Release();
		g_pVtxBuffTotalScore = NULL;
	}

	// テクスチャの開放
	if (g_apTextureTotalScore != NULL) {
		g_apTextureTotalScore->Release();
		g_apTextureTotalScore = NULL;
	}
}
//=============================================================================
//更新処理
//=============================================================================
void UpdateTotalScore(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	VERTEX_2D *pVtx;

	//０以下にしないように
	if (iTotalScore <= 0)
	{
		iTotalScore = 0;
	}

	//ロック
	g_pVtxBuffTotalScore->Lock(0, 0, (void**)&pVtx, 0);

	MakeVertexTotalScore(pDevice);

	//ロック解除
	g_pVtxBuffTotalScore->Unlock();

}

void DrawTotalScore(void) {

	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	int nCutTotalScore;

	//データストリームにセット
	pDevice->SetStreamSource(0,
		g_pVtxBuffTotalScore,
		0,
		sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, g_apTextureTotalScore);

	for (nCutTotalScore = 0; nCutTotalScore < MAX_DIGIT; nCutTotalScore++)
	{
		if (g_aTotalScore[nCutTotalScore].bUse == true)
		{
			// ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCutTotalScore * 4, 2);
		}
	}
}

void SetTotalScore(D3DXVECTOR3 pos) {

	VERTEX_2D *pVtx;
	int nCutTotalScore;
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	for (nCutTotalScore = 0; nCutTotalScore < MAX_DIGIT; nCutTotalScore++)
	{
		if (g_aTotalScore[nCutTotalScore].bUse == false)
		{
			g_aTotalScore[nCutTotalScore].pos = pos;
			g_aTotalScore[nCutTotalScore].bUse = true;

			//ロック
			g_pVtxBuffTotalScore->Lock(0, 0, (void**)&pVtx, 0);

			// 頂点座標の設定
			pVtx += nCutTotalScore * 4;
			pVtx[0].pos = g_aTotalScore[nCutTotalScore].pos;
			pVtx[1].pos = g_aTotalScore[nCutTotalScore].pos;
			pVtx[2].pos = g_aTotalScore[nCutTotalScore].pos;
			pVtx[3].pos = g_aTotalScore[nCutTotalScore].pos;

			//ロック解除
			g_pVtxBuffTotalScore->Unlock();
			break;
		}
	}
}

//=============================================================================
// 頂点情報の作成
//=============================================================================
void MakeVertexTotalScore(LPDIRECT3DDEVICE9 pDevice)
{
	VERTEX_2D *pVtx;
	int g_nCutVtxx;

	//ロック
	g_pVtxBuffTotalScore->Lock(0, 0, (void**)&pVtx, 0);

	for (g_nCutVtxx = 0; g_nCutVtxx < MAX_DIGIT; g_nCutVtxx++) {

		// 頂点座標の設定
		pVtx[0].pos.x = g_aTotalScore[g_nCutVtxx].pos.x;
		pVtx[1].pos.x = g_aTotalScore[g_nCutVtxx].pos.x + 50;
		pVtx[2].pos.x = g_aTotalScore[g_nCutVtxx].pos.x;
		pVtx[3].pos.x = g_aTotalScore[g_nCutVtxx].pos.x + 50;

		pVtx[0].pos.y = g_aTotalScore[g_nCutVtxx].pos.y;
		pVtx[1].pos.y = g_aTotalScore[g_nCutVtxx].pos.y;
		pVtx[2].pos.y = g_aTotalScore[g_nCutVtxx].pos.y + 50;
		pVtx[3].pos.y = g_aTotalScore[g_nCutVtxx].pos.y + 50;

		// rhwの設定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		// 頂点カラーの設定

		pVtx[0].col = D3DCOLOR_RGBA(255, 0, 0, 255);//RGBAの色を入れる
		pVtx[1].col = D3DCOLOR_RGBA(255, 0, 0, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 0, 0, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 0, 0, 255);

		int iPow = int(powf(10, float(MAX_DIGIT - g_nCutVtxx)));
		float fTotalScore = float(iTotalScore % iPow / (iPow / 10));

		// テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(fTotalScore*(1.0f / MAX_PATTEN), 0);
		pVtx[1].tex = D3DXVECTOR2(fTotalScore*(1.0f / MAX_PATTEN) + 1.0f / MAX_PATTEN, 0);
		pVtx[2].tex = D3DXVECTOR2(fTotalScore*(1.0f / MAX_PATTEN), 1);
		pVtx[3].tex = D3DXVECTOR2(fTotalScore*(1.0f / MAX_PATTEN) + 1.0f / MAX_PATTEN, 1);
		pVtx += 4;

	}

	//ロック解除
	g_pVtxBuffTotalScore->Unlock();

}