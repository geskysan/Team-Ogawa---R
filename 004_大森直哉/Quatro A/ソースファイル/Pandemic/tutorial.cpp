//=============================================================================
//
// チュートリアル処理 [tutorial.cpp]
// Author : NAOYA OMORI
//
//=============================================================================
#include "tutorial.h"
#include "input.h"
#include "fade.h"
#include "sound.h"
#include "PressEnter.h"
#include "bullet.h"
#include "Explosion.h"

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void MakeVertexTutorial(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9	g_pTextureTutorial = NULL;	// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTutorial = NULL;//頂点バッファのポインタ

//=============================================================================
// 初期化処理
//=============================================================================
void InitTutorial(void)
{

	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffTutorial,
		NULL);

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/tutorial.jpg", &g_pTextureTutorial);

	//頂点設定
	MakeVertexTutorial(pDevice);

	Stop(SOUND_LABEL_BGM000);
	Play(SOUND_LABEL_BGM001);

}

//=============================================================================
// 終了処理
//=============================================================================
void UninitTutorial(void)
{
	// 頂点バッファの開放
	if (g_pVtxBuffTutorial != NULL)
	{
		g_pVtxBuffTutorial->Release();
		g_pVtxBuffTutorial = NULL;
	}

	// テクスチャの開放
	if (g_pTextureTutorial != NULL)
	{
		g_pTextureTutorial->Release();
		g_pTextureTutorial = NULL;
	}

}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateTutorial(void)
{
	if (GetKeyboardPress(DIK_RETURN)) {
		SetFade(MODE_TITLE);
	}

}

//=============================================================================
// 描画処理
//=============================================================================
void DrawTutorial(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//データストリームにセット
	pDevice->SetStreamSource(0,
		g_pVtxBuffTutorial,
		0,
		sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, g_pTextureTutorial);

	// ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
		0,
		2);

}

//=============================================================================
// 頂点情報の作成
//=============================================================================
void MakeVertexTutorial(LPDIRECT3DDEVICE9 pDevice)
{
	VERTEX_2D *pVtx;

	//ロック
	g_pVtxBuffTutorial->Lock(0,
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
	g_pVtxBuffTutorial->Unlock();

}