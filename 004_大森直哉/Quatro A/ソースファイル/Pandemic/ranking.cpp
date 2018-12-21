//=============================================================================
//
// ランキング画面の描画処理 [ranking.cpp]
// Author : NAOYA OMORI
//
//=============================================================================
#include "ranking.h"
#include "input.h"
#include "fade.h"
#include "RankingScore.h"
#include "Title.h"
#include "rankingplayer.h"
#include "sound.h"

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void MakeVertexRanking(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9	g_pTextureRanking = NULL;	// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffRanking = NULL;//頂点バッファのポインタ

int ReturnCount;
int BackFlag;

//=============================================================================
// 初期化処理
//=============================================================================
void InitRanking(void)
{

	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//初期設定
	ReturnCount = 0;
	BackFlag = FALSE;

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffRanking,
		NULL);

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/ranking.jpg", &g_pTextureRanking);

	//頂点設定
	MakeVertexRanking(pDevice);

	InitRankingScore();
	InitRankingPlayer();

}

//=============================================================================
// 終了処理
//=============================================================================
void UninitRanking(void)
{

	// 頂点バッファの開放
	if (g_pVtxBuffRanking != NULL)
	{
		g_pVtxBuffRanking->Release();
		g_pVtxBuffRanking = NULL;
	}

	// テクスチャの開放
	if (g_pTextureRanking != NULL)
	{
		g_pTextureRanking->Release();
		g_pTextureRanking = NULL;
	}

	UninitRankingScore();
	UninitRankingPlayer();

}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateRanking(void)
{

	ReturnCount++;

	BackFlag = GetFlag();

	if (ReturnCount == 300 && BackFlag == TRUE) {
		SetFade(MODE_TITLE);
	}

	if (GetKeyboardPress(DIK_RETURN)) {
		SetFade(MODE_TITLE);

	}

	UpdateRankingScore();
	UpdateRankingPlayer();
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawRanking(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//データストリームにセット
	pDevice->SetStreamSource(0,
		g_pVtxBuffRanking,
		0,
		sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, g_pTextureRanking);

	// ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
		0,
		2);

	DrawRankingScore();
	DrawRankingPlayer();
}

//=============================================================================
// 頂点情報の作成
//=============================================================================
void MakeVertexRanking(LPDIRECT3DDEVICE9 pDevice)
{
	VERTEX_2D *pVtx;

	//ロック
	g_pVtxBuffRanking->Lock(0,
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
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);//RGBAの色を入れる
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	// テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0, 0);
	pVtx[1].tex = D3DXVECTOR2(1, 0);
	pVtx[2].tex = D3DXVECTOR2(0, 1);
	pVtx[3].tex = D3DXVECTOR2(1, 1);

	//ロック解除
	g_pVtxBuffRanking->Unlock();
}

