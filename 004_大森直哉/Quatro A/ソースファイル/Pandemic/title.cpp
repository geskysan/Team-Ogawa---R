//=============================================================================
//
// タイトル処理 [title.cpp]
// Author : NAOYA OMORI
//
//=============================================================================
#include "title.h"
#include "input.h"
#include "main.h"
#include "fade.h"
#include "sound.h"
#include "titlefont.h"
#include "titleplayer.h"
#include "Selectfont.h"
#include "TitleArrow.h"
#include "PressEnter.h"

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void MakeVertexTitle(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9	g_pTextureTitle = NULL;	// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTitle = NULL;//頂点バッファのポインタ
int TimeCount;
bool ReturnFlag;

//=============================================================================
// 初期化処理
//=============================================================================
void InitTitle(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	TimeCount = 0;
	ReturnFlag = TRUE;

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffTitle,
		NULL);

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/Title.jpg", &g_pTextureTitle);

	////頂点設定
	MakeVertexTitle(pDevice);

	Stop(SOUND_LABEL_BGM001);
	Stop(SOUND_LABEL_BGM002);
	Play(SOUND_LABEL_BGM000);

	InitTitleFont();
	InitTitlePlayer();
	InitSelectfont();
	InitArrow();
	InitPressEnter();
}


//=============================================================================
// 終了処理
//=============================================================================
void UninitTitle(void)
{
	// 頂点バッファの開放
	if (g_pVtxBuffTitle != NULL)
	{
		g_pVtxBuffTitle->Release();
		g_pVtxBuffTitle = NULL;
	}

	// テクスチャの開放
	if (g_pTextureTitle != NULL) {
		g_pTextureTitle->Release();
		g_pTextureTitle = NULL;
	}

	UninitTitleFont();
	UninitTitlePlayer();
	UninitSelectfont();
	UninitArrow();
	UninitPressEnter();

}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateTitle(void)
{

	TimeCount++;

	if (TimeCount == 600 && ReturnFlag == TRUE) {
		SetFade(MODE_RANKING);
		TimeCount = 0;
	}

	SetSelectfont(D3DXVECTOR3(650.0f, 400.0f, 0.0f), 0);
	SetSelectfont(D3DXVECTOR3(650.0f, 500.0f, 0.0f), 1);
	SetSelectfont(D3DXVECTOR3(650.0f, 600.0f, 0.0f), 2);
	SetEnterPosition(D3DXVECTOR3(1100.0f, 680.0f, 0.0f));

	UpdateTitleFont();
	UpdateTitlePlayer();
	UpdateArrow();
	UpdateSelectfont();
	UpdatePressEnter();
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawTitle(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//データストリームにセット
	pDevice->SetStreamSource(0,
		g_pVtxBuffTitle,
		0,
		sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, g_pTextureTitle);

	// ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
		0,
		2);

	DrawTitleFont();
	DrawTitlePlayer();
	DrawSelectfont();
	DrawArrow();
	DrawPressEnter();
}

//=============================================================================
// 頂点情報の作成
//=============================================================================
void MakeVertexTitle(LPDIRECT3DDEVICE9 pDevice)
{
	VERTEX_2D *pVtx;

	//ロック
	g_pVtxBuffTitle->Lock(0,
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
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 0);//RGBAの色を入れる
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 0);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 0);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 0);

	// テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0, 0);
	pVtx[1].tex = D3DXVECTOR2(1, 0);
	pVtx[2].tex = D3DXVECTOR2(0, 1);
	pVtx[3].tex = D3DXVECTOR2(1, 1);

	//ロック解除
	g_pVtxBuffTitle->Unlock();
}

int GetFlag(void) {
	return ReturnFlag;
}