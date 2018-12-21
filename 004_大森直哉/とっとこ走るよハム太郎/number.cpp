//=============================================================================
//
// 弾の処理 [Enemy.cpp]
// Author : 
//
//=============================================================================
#include "number.h"
#include "polygon.h"
#include "bullet.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MAX_DIGIT	(8)
#define MAX_PATTEN	(10)
//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void MakeVertexNumber(LPDIRECT3DDEVICE9 pDevice);
LPDIRECT3DTEXTURE9 g_apTextureNumber = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffNumber = NULL;
Number g_aNumber[MAX_DIGIT];
int iScore;
//=============================================================================
// 初期化処理
//=============================================================================
void InitNumber(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	int nCutNumber;
	for (nCutNumber = 0; nCutNumber < MAX_DIGIT; nCutNumber++)
	{
		g_aNumber[nCutNumber].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aNumber[nCutNumber].nType = 0;
		g_aNumber[nCutNumber].bUse = false;
		g_aNumber[nCutNumber].g_posNumber = D3DXVECTOR3(0, 0, 0);
		g_aNumber[nCutNumber].g_rotNumber = D3DXVECTOR3(0, 0, 0);
		g_aNumber[nCutNumber].g_fAngleNumber = atan2f(0, 0);
		g_aNumber[nCutNumber].g_fLengthNumber = sqrtf(0 * 0 + 0 * 0);
	}

	iScore = 0;

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/number000.png", &g_apTextureNumber);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_DIGIT,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffNumber,
		NULL);

	for (int y = 0; y < MAX_DIGIT; y++)
	{
		SetNumber(D3DXVECTOR3(880 + 50 * y, 10, 0));	//スコア（8桁）
	}

	MakeVertexNumber(pDevice);
}

void UninitNumber(void) {
	// テクスチャの開放
	if (g_pVtxBuffNumber != NULL)
	{
		g_pVtxBuffNumber->Release();
		g_pVtxBuffNumber = NULL;
	}

	if (g_apTextureNumber != NULL) {
		g_apTextureNumber->Release();
		g_apTextureNumber = NULL;
	}
}
//=============================================================================
//更新処理
//=============================================================================
void UpdateNumber(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	VERTEX_2D *pVtx;

	iScore = GetScore();

	//ロック
	g_pVtxBuffNumber->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCutVtx = 0; nCutVtx < MAX_DIGIT; nCutVtx++) {
		int iPow = powf(10, MAX_DIGIT - nCutVtx);
		float fTime = iScore % iPow / (iPow / 10);
		pVtx[0].tex = D3DXVECTOR2(fTime*(1.0f / MAX_PATTEN), 0);
		pVtx[1].tex = D3DXVECTOR2(fTime*(1.0f / MAX_PATTEN) + 1.0f / MAX_PATTEN, 0);
		pVtx[2].tex = D3DXVECTOR2(fTime*(1.0f / MAX_PATTEN), 1);
		pVtx[3].tex = D3DXVECTOR2(fTime*(1.0f / MAX_PATTEN) + 1.0f / MAX_PATTEN, 1);
		pVtx += 4;

		//ロック解除
		g_pVtxBuffNumber->Unlock();
	}
}

void DrawNumber(void) {

	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	int nCutNumber;

	pDevice->SetStreamSource(0,
		g_pVtxBuffNumber,
		0,
		sizeof(VERTEX_2D));

	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, g_apTextureNumber);

	for (nCutNumber = 0; nCutNumber < MAX_DIGIT; nCutNumber++)
	{
		if (g_aNumber[nCutNumber].bUse == true)
		{
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCutNumber * 4, 2);
		}
	}
}

void SetNumber(D3DXVECTOR3 pos) {

	VERTEX_2D *pVtx;
	int nCutNumber;

	for (nCutNumber = 0; nCutNumber < MAX_DIGIT; nCutNumber++)
	{
		if (g_aNumber[nCutNumber].bUse == false)
		{
			g_aNumber[nCutNumber].pos = pos;
			g_aNumber[nCutNumber].bUse = true;

			//ロック
			g_pVtxBuffNumber->Lock(0, 0, (void**)&pVtx, 0);

			pVtx += nCutNumber * 4;
			pVtx[0].pos = g_aNumber[nCutNumber].pos;
			pVtx[1].pos = g_aNumber[nCutNumber].pos;
			pVtx[2].pos = g_aNumber[nCutNumber].pos;
			pVtx[3].pos = g_aNumber[nCutNumber].pos;

			g_pVtxBuffNumber->Unlock();

			break;
		}
	}
}


//=============================================================================
// 頂点情報の作成
//=============================================================================
void MakeVertexNumber(LPDIRECT3DDEVICE9 pDevice)
{
	VERTEX_2D *pVtx;
	int nCutVtx;


	//ロック
	g_pVtxBuffNumber->Lock(0, 0, (void**)&pVtx, 0);

	for (nCutVtx = 0; nCutVtx < MAX_DIGIT; nCutVtx++) {

		pVtx[0].pos.x = g_aNumber[nCutVtx].pos.x ;
		pVtx[1].pos.x = g_aNumber[nCutVtx].pos.x + 50;
		pVtx[2].pos.x = g_aNumber[nCutVtx].pos.x ;
		pVtx[3].pos.x = g_aNumber[nCutVtx].pos.x + 50;

		pVtx[0].pos.y = g_aNumber[nCutVtx].pos.y ;
		pVtx[1].pos.y = g_aNumber[nCutVtx].pos.y ;
		pVtx[2].pos.y = g_aNumber[nCutVtx].pos.y + 50;
		pVtx[3].pos.y = g_aNumber[nCutVtx].pos.y + 50;

		// rhwの設定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		// 頂点カラーの設定

		pVtx[0].col = D3DCOLOR_RGBA(135, 206, 235, 255);//RGBAの色を入れる
		pVtx[1].col = D3DCOLOR_RGBA(135, 206, 235, 255);
		pVtx[2].col = D3DCOLOR_RGBA(135, 206, 235, 255);
		pVtx[3].col = D3DCOLOR_RGBA(135, 206, 235, 255);

		int iPow = powf(10, MAX_DIGIT - nCutVtx);
		float fScore = iScore % iPow / (iPow / 10);
		pVtx[0].tex = D3DXVECTOR2(fScore*(1.0f / MAX_PATTEN), 0);
		pVtx[1].tex = D3DXVECTOR2(fScore*(1.0f / MAX_PATTEN) + 1.0f / MAX_PATTEN, 0);
		pVtx[2].tex = D3DXVECTOR2(fScore*(1.0f / MAX_PATTEN), 1);
		pVtx[3].tex = D3DXVECTOR2(fScore*(1.0f / MAX_PATTEN) + 1.0f / MAX_PATTEN, 1);
		pVtx += 4;
	}

	//ロック解除
	g_pVtxBuffNumber->Unlock();
}

int GetNumber(void) {
	return iScore;
}