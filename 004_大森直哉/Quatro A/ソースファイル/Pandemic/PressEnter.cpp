//=============================================================================
//
// ポリゴン処理 [PressEnter.cpp]
// Author : NAOYA OMORI
//
//=============================================================================
#include "PressEnter.h"

//*****************************************************************************
// マクロ定義宣言
//*****************************************************************************
#define PRESSENTER_SIZE_X (300)
#define PRESSENTER_SIZE_Y (50)
#define MAX_ENTER (3)

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void MakeVertexPressEnter(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9	g_pTexturePressEnter = NULL;		// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPressEnter = NULL;	//頂点バッファのポインタ
Enter enter[MAX_ENTER];
int g_col;

//=============================================================================
// 初期化処理
//=============================================================================
void InitPressEnter(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	int nCntEnter;

	//初期設定
	for (nCntEnter = 0; nCntEnter < MAX_ENTER; nCntEnter++) {
		enter[nCntEnter].pos = D3DXVECTOR3(0, 0, 0);
		enter[nCntEnter].rot = D3DXVECTOR3(0, 0, 0);
		enter[nCntEnter].fAngle = atan2f(PRESSENTER_SIZE_X / 2, PRESSENTER_SIZE_Y / 2);
		enter[nCntEnter].fLength = sqrtf((PRESSENTER_SIZE_X / 2) * (PRESSENTER_SIZE_X / 2) + (PRESSENTER_SIZE_Y / 2) * (PRESSENTER_SIZE_Y / 2));
		enter[nCntEnter].bUse = false;
	}

	g_col = 0;

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_ENTER,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffPressEnter,
		NULL);

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/press_enter.png", &g_pTexturePressEnter);

	//頂点設定
	MakeVertexPressEnter(pDevice);

}

//=============================================================================
// 終了処理
//=============================================================================
void UninitPressEnter(void)
{
	// 頂点バッファの開放
	if (g_pVtxBuffPressEnter != NULL)
	{
		g_pVtxBuffPressEnter->Release();
		g_pVtxBuffPressEnter = NULL;
	}

	// テクスチャの開放
	if (g_pTexturePressEnter != NULL)
	{
		g_pTexturePressEnter->Release();
		g_pTexturePressEnter = NULL;
	}

}
//=============================================================================
// 更新処理
//=============================================================================
void UpdatePressEnter(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	VERTEX_2D *pVtx;

	g_col -= 10;

	for (int nCntEnter = 0; nCntEnter < MAX_ENTER; nCntEnter++) {

		//ロック
		g_pVtxBuffPressEnter->Lock(0, 0, (void**)&pVtx, 0);

		//頂点座標の設定
		pVtx[0].pos.x = enter[nCntEnter].pos.x - sinf(enter[nCntEnter].fAngle - enter[nCntEnter].rot.z)*enter[nCntEnter].fLength;
		pVtx[0].pos.y = enter[nCntEnter].pos.y - cosf(enter[nCntEnter].fAngle - enter[nCntEnter].rot.z)*enter[nCntEnter].fLength;
		pVtx[0].pos.z = 0.0f;

		pVtx[1].pos.x = enter[nCntEnter].pos.x + sinf(enter[nCntEnter].fAngle + enter[nCntEnter].rot.z)*enter[nCntEnter].fLength;
		pVtx[1].pos.y = enter[nCntEnter].pos.y - cosf(enter[nCntEnter].fAngle + enter[nCntEnter].rot.z)*enter[nCntEnter].fLength;
		pVtx[1].pos.z = 0.0f;

		pVtx[2].pos.x = enter[nCntEnter].pos.x - sinf(enter[nCntEnter].fAngle + enter[nCntEnter].rot.z)*enter[nCntEnter].fLength;
		pVtx[2].pos.y = enter[nCntEnter].pos.y + cosf(enter[nCntEnter].fAngle + enter[nCntEnter].rot.z)*enter[nCntEnter].fLength;
		pVtx[2].pos.z = 0.0f;

		pVtx[3].pos.x = enter[nCntEnter].pos.x + sinf(enter[nCntEnter].fAngle - enter[nCntEnter].rot.z)*enter[nCntEnter].fLength;
		pVtx[3].pos.y = enter[nCntEnter].pos.y + cosf(enter[nCntEnter].fAngle - enter[nCntEnter].rot.z)*enter[nCntEnter].fLength;
		pVtx[3].pos.z = 0.0f;

		// 頂点カラーの設定
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, g_col);//RGBAの色を入れる
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, g_col);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, g_col);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, g_col);

		//ロック解除
		g_pVtxBuffPressEnter->Unlock();
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawPressEnter(void)
{
	for (int nCntEnter = 0; nCntEnter < MAX_ENTER; nCntEnter++) {

		if (!enter[nCntEnter].bUse)
			return;

		//デバイスを取得
		LPDIRECT3DDEVICE9 pDevice = GetDevice();

		//データストリームにセット
		pDevice->SetStreamSource(0, g_pVtxBuffPressEnter, 0, sizeof(VERTEX_2D));

		// 頂点フォーマットの設定
		pDevice->SetFVF(FVF_VERTEX_2D);

		// テクスチャの設定
		pDevice->SetTexture(0, g_pTexturePressEnter);

		// ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4 * nCntEnter, 2);
	}
}
//=============================================================================
// 頂点情報の作成
//=============================================================================
void MakeVertexPressEnter(LPDIRECT3DDEVICE9 pDevice)
{

	VERTEX_2D *pVtx;
	for (int nCntEnter = 0; nCntEnter < MAX_ENTER; nCntEnter++) {
		//ロック
		g_pVtxBuffPressEnter->Lock(0, 0, (void**)&pVtx, 0);

		// 頂点座標の設定
		pVtx[0].pos.x = enter[nCntEnter].pos.x - sinf(enter[nCntEnter].fAngle - enter[nCntEnter].rot.z)*enter[nCntEnter].fLength;
		pVtx[0].pos.y = enter[nCntEnter].pos.y - cosf(enter[nCntEnter].fAngle - enter[nCntEnter].rot.z)*enter[nCntEnter].fLength;
		pVtx[0].pos.z = 0.0f;

		pVtx[1].pos.x = enter[nCntEnter].pos.x + sinf(enter[nCntEnter].fAngle + enter[nCntEnter].rot.z)*enter[nCntEnter].fLength;
		pVtx[1].pos.y = enter[nCntEnter].pos.y - cosf(enter[nCntEnter].fAngle + enter[nCntEnter].rot.z)*enter[nCntEnter].fLength;
		pVtx[1].pos.z = 0.0f;

		pVtx[2].pos.x = enter[nCntEnter].pos.x - sinf(enter[nCntEnter].fAngle + enter[nCntEnter].rot.z)*enter[nCntEnter].fLength;
		pVtx[2].pos.y = enter[nCntEnter].pos.y + cosf(enter[nCntEnter].fAngle + enter[nCntEnter].rot.z)*enter[nCntEnter].fLength;
		pVtx[2].pos.z = 0.0f;

		pVtx[3].pos.x = enter[nCntEnter].pos.x + sinf(enter[nCntEnter].fAngle - enter[nCntEnter].rot.z)*enter[nCntEnter].fLength;
		pVtx[3].pos.y = enter[nCntEnter].pos.y + cosf(enter[nCntEnter].fAngle - enter[nCntEnter].rot.z)*enter[nCntEnter].fLength;
		pVtx[3].pos.z = 0.0f;

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

		//テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0, 0);
		pVtx[1].tex = D3DXVECTOR2(1, 0);
		pVtx[2].tex = D3DXVECTOR2(0, 1);
		pVtx[3].tex = D3DXVECTOR2(1, 1);

		//ロック解除
		g_pVtxBuffPressEnter->Unlock();
	}
}


void SetEnterPosition(D3DXVECTOR3 pos) {

	for (int nCntEnter = 0; nCntEnter < MAX_ENTER; nCntEnter++) {
		if (enter[nCntEnter].bUse == false)
		{
			enter[nCntEnter].pos = pos;
			enter[nCntEnter].bUse = true;
		}
	}
}