//=============================================================================
//
// 弾の処理 [Enemy.cpp]
// Author : 
//
//=============================================================================
#include "Life.h"
#include "polygon.h"
//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void MakeVertexLife(LPDIRECT3DDEVICE9 pDevice);
LPDIRECT3DTEXTURE9 g_apTextureLife = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffLife = NULL;
Life g_aLife[MAX_LIFE];
int PlayerHitPoint;
//=============================================================================
// 初期化処理
//=============================================================================
void InitLife(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	int nCutLife;
	for (nCutLife = 0; nCutLife < MAX_LIFE; nCutLife++)
	{
		g_aLife[nCutLife].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aLife[nCutLife].nType = 0;
		g_aLife[nCutLife].bUse = false;
	}

	PlayerHitPoint = 0;

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/life000.png", &g_apTextureLife);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_LIFE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffLife,
		NULL);

	for (int y = 0; y < MAX_LIFE; y++)
	{
		SetLife(D3DXVECTOR3(0 + 60 *y, 10, 0));		//体力(5個)
	}
	
	MakeVertexLife(pDevice);
}

void UninitLife(void) {
	// テクスチャの開放4
	if (g_pVtxBuffLife != NULL)
	{
		g_pVtxBuffLife->Release();
		g_pVtxBuffLife = NULL;
	}

	if (g_apTextureLife != NULL) {
		g_apTextureLife->Release();
		g_apTextureLife = NULL;
	}
}
//=============================================================================
//更新処理
//=============================================================================
void UpdateLife(void)
{

}

void DrawLife(void) {

	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	int nCutLife;
	int playerhp;

	playerhp = GetPlayerHP();

	pDevice->SetStreamSource(0,
		g_pVtxBuffLife,
		0,
		sizeof(VERTEX_2D));

	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, g_apTextureLife);

	for (nCutLife = 0; nCutLife < playerhp; nCutLife++)
	{
		if (g_aLife[nCutLife].bUse == true)
		{
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCutLife * 4, 2);
		}
	}
}

void SetLife(D3DXVECTOR3 pos) {

	VERTEX_2D *pVtx;
	int nCutLife;

	for (nCutLife = 0; nCutLife < MAX_LIFE; nCutLife++)
	{
		if (g_aLife[nCutLife].bUse == false)
		{
			g_aLife[nCutLife].pos = pos;
			g_aLife[nCutLife].bUse = true;

			//ロック
			g_pVtxBuffLife->Lock(0, 0, (void**)&pVtx, 0);

			pVtx += nCutLife * 4;
			pVtx[0].pos = g_aLife[nCutLife].pos;
			pVtx[1].pos = g_aLife[nCutLife].pos;
			pVtx[2].pos = g_aLife[nCutLife].pos;
			pVtx[3].pos = g_aLife[nCutLife].pos;


			g_pVtxBuffLife->Unlock();

			break;
		}
	}
}


//=============================================================================
// 頂点情報の作成
//=============================================================================
void MakeVertexLife(LPDIRECT3DDEVICE9 pDevice)
{
	VERTEX_2D *pVtx;
	int nCutVtx;


	//ロック
	g_pVtxBuffLife->Lock(0, 0, (void**)&pVtx, 0);

	for (nCutVtx = 0; nCutVtx < MAX_LIFE; nCutVtx++) {

		pVtx[0].pos.x = g_aLife[nCutVtx].pos.x ;
		pVtx[1].pos.x = g_aLife[nCutVtx].pos.x ;
		pVtx[2].pos.x = g_aLife[nCutVtx].pos.x + 60;
		pVtx[3].pos.x = g_aLife[nCutVtx].pos.x + 60;

		pVtx[0].pos.y = g_aLife[nCutVtx].pos.y + 60;
		pVtx[1].pos.y = g_aLife[nCutVtx].pos.y ;
		pVtx[2].pos.y = g_aLife[nCutVtx].pos.y + 60;
		pVtx[3].pos.y = g_aLife[nCutVtx].pos.y ;

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

		pVtx[0].tex = D3DXVECTOR2(0, 1);
		pVtx[1].tex = D3DXVECTOR2(0, 0);
		pVtx[2].tex = D3DXVECTOR2(1, 1);
		pVtx[3].tex = D3DXVECTOR2(1, 0);
		pVtx += 4;
	}
	//ロック解除
	g_pVtxBuffLife->Unlock();
}