//=============================================================================
//
// ポリゴン処理 [polygon.cpp]
// Author : AKIRA TANAKA
//
//=============================================================================
#include "title.h"
#include "input.h"
#include "main.h"
#include "fade.h"
#include "sound.h"
//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void MakeVertexTitle(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9	g_pTextureTitle[2] = {};	// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTitle = NULL;//頂点バッファのポインタ

//=============================================================================
// 初期化処理
//=============================================================================
void InitTitle(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffTitle,
		NULL);



	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/Title.jpg", &g_pTextureTitle[0]);


	//頂点設定
	MakeVertexTitle(pDevice);

	Stop(SOUND_LABEL_BGM002);
	// サウンド再生
	Play(SOUND_LABEL_BGM000);


}

//=============================================================================
// 終了処理
//=============================================================================
void UninitTitle(void)
{
	// テクスチャの開放4
	if (g_pVtxBuffTitle != NULL)
	{
		g_pVtxBuffTitle->Release();
		g_pVtxBuffTitle = NULL;
	}
	for (int i = 0; i < 3; i++) {
		if (g_pTextureTitle[i] != NULL) {
			g_pTextureTitle[i]->Release();
			g_pTextureTitle[i] = NULL;
		}
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateTitle(void)
{
	if (GetKeyboardPress(DIK_RETURN) && GetFade() == FADE_NONE) {

		SetFade(MODE_TUTORIAL);

		// 決定音再生
		Play(SOUND_LABEL_SE_DECIDE);
	}
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
	pDevice->SetTexture(0, g_pTextureTitle[0]);

	// ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
		0,
		2);
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
	g_pVtxBuffTitle->Unlock();
}