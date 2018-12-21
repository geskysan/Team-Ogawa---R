//=============================================================================
//
// 爆発アニメーション処理 [Explosion.cpp]
// Author : NAOYA OMORI
//
//=============================================================================
#include "Explosion.h"
#include "sound.h"

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void MakeVertexExplosion(LPDIRECT3DDEVICE9 pDevice);

#define MAX_ANIM	8

//グローバル変数
LPDIRECT3DTEXTURE9 g_apTextureExplosion;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffExplosion = NULL;
Explosion g_aExplosion[128];

//=============================================================================
// 初期化処理
//=============================================================================
void InitExplosion(void)
{

	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	int nCutExp;

	//初期設定
	for (nCutExp = 0; nCutExp < 128; nCutExp++) {
		g_aExplosion[nCutExp].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aExplosion[nCutExp].bUse = false;
		g_aExplosion[nCutExp].nCounterAnim = 0;
		g_aExplosion[nCutExp].nPatternAnim = 0;
	}

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/explosion000.png", &g_apTextureExplosion);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * 128,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffExplosion,
		NULL);

	MakeVertexExplosion(pDevice);

}

void UninitExplosion(void) {

	// テクスチャの開放
	if (g_apTextureExplosion != NULL) {
		g_apTextureExplosion->Release();
		g_apTextureExplosion = NULL;
	}

	// 頂点バッファの開放
	if (g_pVtxBuffExplosion != NULL) {
		g_pVtxBuffExplosion->Release();
		g_pVtxBuffExplosion = NULL;
	}
}

//=============================================================================
//更新処理
//=============================================================================
void UpdateExplosion(void) {

	VERTEX_2D *pVtx;
	int nCutEnemy;

	//ロック
	g_pVtxBuffExplosion->Lock(0, 0, (void**)&pVtx, 0);

	for (nCutEnemy = 0; nCutEnemy <128; nCutEnemy++)
	{
		if (g_aExplosion[nCutEnemy].bUse == true)
		{

			if (g_aExplosion[nCutEnemy].nCounterAnim % 10 == 0) {

				g_aExplosion[nCutEnemy].nCounterAnim = 0;
				g_aExplosion[nCutEnemy].nPatternAnim++;

			}

			//テクスチャ座標の設定
			pVtx[0].tex = D3DXVECTOR2(g_aExplosion[nCutEnemy].nPatternAnim *(1.0f / MAX_ANIM), 1);
			pVtx[1].tex = D3DXVECTOR2(g_aExplosion[nCutEnemy].nPatternAnim*(1.0f / MAX_ANIM), 0);
			pVtx[2].tex = D3DXVECTOR2(g_aExplosion[nCutEnemy].nPatternAnim *(1.0f / MAX_ANIM) + 1.f / MAX_ANIM, 1);
			pVtx[3].tex = D3DXVECTOR2(g_aExplosion[nCutEnemy].nPatternAnim*(1.0f / MAX_ANIM) + 1.f / MAX_ANIM, 0);

			g_aExplosion[nCutEnemy].nCounterAnim++;

		}
		if (g_aExplosion[nCutEnemy].nPatternAnim == MAX_ANIM) {
			g_aExplosion[nCutEnemy].bUse = false;
		}
		pVtx += 4;
	}
	//ロック解除
	g_pVtxBuffExplosion->Unlock();
}

void DrawExplosion(void) {

	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//データストリームにセット
	pDevice->SetStreamSource(0,
		g_pVtxBuffExplosion,
		0,
		sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nMori = 0; nMori < 128; nMori++)
	{
		if (g_aExplosion[nMori].bUse)
		{
			// テクスチャの設定
			pDevice->SetTexture(0, g_apTextureExplosion);
			// ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nMori * 4, 2);
		}
	}
}

void SetExplosion(D3DXVECTOR3 pos) {

	VERTEX_2D *pVtx;
	int nCutEnemy;

	for (nCutEnemy = 0; nCutEnemy < 128; nCutEnemy++)
	{
		if (g_aExplosion[nCutEnemy].bUse == false)
		{
			g_aExplosion[nCutEnemy].pos = pos;
			g_aExplosion[nCutEnemy].bUse = true;
			g_aExplosion[nCutEnemy].nCounterAnim = 0;
			g_aExplosion[nCutEnemy].nPatternAnim = 0;

			//ロック
			g_pVtxBuffExplosion->Lock(0, 0, (void**)&pVtx, 0);

			pVtx += nCutEnemy * 4;

			// 頂点座標の設定
			pVtx[0].pos.x = g_aExplosion[nCutEnemy].pos.x - 30;
			pVtx[1].pos.x = g_aExplosion[nCutEnemy].pos.x - 30;
			pVtx[2].pos.x = g_aExplosion[nCutEnemy].pos.x + 30;
			pVtx[3].pos.x = g_aExplosion[nCutEnemy].pos.x + 30;

			pVtx[0].pos.y = g_aExplosion[nCutEnemy].pos.y + 30;
			pVtx[1].pos.y = g_aExplosion[nCutEnemy].pos.y - 30;
			pVtx[2].pos.y = g_aExplosion[nCutEnemy].pos.y + 30;
			pVtx[3].pos.y = g_aExplosion[nCutEnemy].pos.y - 30;

			//ロック解除
			g_pVtxBuffExplosion->Unlock();

			Play(SOUND_LABEL_SE_EXPLOSION000);

			break;
		}
	}
}


//=============================================================================
// 頂点情報の作成
//=============================================================================
void MakeVertexExplosion(LPDIRECT3DDEVICE9 pDevice)
{
	VERTEX_2D *pVtx;
	int nCutVtx;

	//ロック
	g_pVtxBuffExplosion->Lock(0, 0, (void**)&pVtx, 0);

	for (nCutVtx = 0; nCutVtx < 128; nCutVtx++) {

		// 頂点座標の設定
		pVtx[0].pos.x = g_aExplosion[nCutVtx].pos.x;
		pVtx[1].pos.x = g_aExplosion[nCutVtx].pos.x;
		pVtx[2].pos.x = g_aExplosion[nCutVtx].pos.x + 100;
		pVtx[3].pos.x = g_aExplosion[nCutVtx].pos.x + 100;

		pVtx[0].pos.y = g_aExplosion[nCutVtx].pos.y + 100;
		pVtx[1].pos.y = g_aExplosion[nCutVtx].pos.y;
		pVtx[2].pos.y = g_aExplosion[nCutVtx].pos.y + 100;
		pVtx[3].pos.y = g_aExplosion[nCutVtx].pos.y;

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
		pVtx[0].tex = D3DXVECTOR2(float (g_aExplosion[nCutVtx].nPatternAnim / MAX_ANIM), 1);
		pVtx[1].tex = D3DXVECTOR2(float (g_aExplosion[nCutVtx].nPatternAnim / MAX_ANIM), 0);
		pVtx[2].tex = D3DXVECTOR2(float (g_aExplosion[nCutVtx].nPatternAnim / MAX_ANIM + 1.f / MAX_ANIM), 1);
		pVtx[3].tex = D3DXVECTOR2(float (g_aExplosion[nCutVtx].nPatternAnim / MAX_ANIM + 1.f / MAX_ANIM), 0);
		pVtx += 4;

	}

	//ロック解除
	g_pVtxBuffExplosion->Unlock();

}
