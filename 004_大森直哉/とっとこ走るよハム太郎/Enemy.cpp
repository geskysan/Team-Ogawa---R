//=============================================================================
//
// 弾の処理 [Enemy.cpp]
// Author : 
//
//=============================================================================
#include "Enemy.h"
#include "EnemyBullet.h"
#include "polygon.h"
#include "bullet.h"
#include "explosion.h"
//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void MakeVertexEnemy(LPDIRECT3DDEVICE9 pDevice);

#define MAX_ENEMY (40)
#define MAX_ENEMY_TEX (4)
#define MIN_ENEMY (0)

//グローバル変数
LPDIRECT3DTEXTURE9 g_apTextureEnemy[MAX_ENEMY_TEX] = {};
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffEnemy = NULL;
Enemy g_aEnemy[MAX_ENEMY];
int EnemyCount;
int BulletCount;	//敵の弾のタイマー
int Random;
//=============================================================================
// 初期化処理
//=============================================================================
void InitEnemy(void)
{
	EnemyCount = 0;
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	int nCutEnemy;

		for (nCutEnemy = 0; nCutEnemy < MAX_ENEMY; nCutEnemy++) {
			g_aEnemy[nCutEnemy].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_aEnemy[nCutEnemy].nType = 0;
			g_aEnemy[nCutEnemy].bUse = false;
		}
		BulletCount = 0;

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/enemy000.png", &g_apTextureEnemy[0]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/enemy001.png", &g_apTextureEnemy[1]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/enemy002.png", &g_apTextureEnemy[2]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/enemy003.png", &g_apTextureEnemy[3]);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * 128,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffEnemy,
		NULL);

	MakeVertexEnemy(pDevice);

	for (int x = 0; x < 10; x++) {
		SetEnemy(D3DXVECTOR3(250 + 85 * x, 100, 0), 3);	//エネミー1
		SetEnemy(D3DXVECTOR3(250 + 85 * x, 180, 0), 2);	//エネミー1
		SetEnemy(D3DXVECTOR3(250 + 85 * x, 260, 0), 1);	//エネミー1
		SetEnemy(D3DXVECTOR3(250 + 85 * x, 340, 0), 0);	//エネミー1
		}
	}

void UninitEnemy(void) {
	// テクスチャの開放
	if (g_pVtxBuffEnemy != NULL)
	{
		g_pVtxBuffEnemy->Release();
		g_pVtxBuffEnemy = NULL;
	}
}
//=============================================================================
//更新処理
//=============================================================================
void UpdateEnemy(void) {

	VERTEX_2D *pVtx;
	D3DXVECTOR3 PolygonPos;
	int nCutEnemy;
	int count = 0;

	PolygonPos = GetMinePos();

	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

	for (nCutEnemy = 0; nCutEnemy <MAX_ENEMY; nCutEnemy++)
	{
		if (g_aEnemy[nCutEnemy].bUse == true)
		{
			pVtx[0].pos.x = g_aEnemy[nCutEnemy].pos.x - 40;
			pVtx[1].pos.x = g_aEnemy[nCutEnemy].pos.x - 40;
			pVtx[2].pos.x = g_aEnemy[nCutEnemy].pos.x + 40;
			pVtx[3].pos.x = g_aEnemy[nCutEnemy].pos.x + 40;

			pVtx[0].pos.y = g_aEnemy[nCutEnemy].pos.y + 40;
			pVtx[1].pos.y = g_aEnemy[nCutEnemy].pos.y - 40;
			pVtx[2].pos.y = g_aEnemy[nCutEnemy].pos.y + 40;
			pVtx[3].pos.y = g_aEnemy[nCutEnemy].pos.y - 40;

			//[頂点バッファの内容も更新]
			if (g_aEnemy[nCutEnemy].pos.y <= 0)
			{
				g_aEnemy[nCutEnemy].bUse = false;
			}
		}
		pVtx += 4;
	}
	g_pVtxBuffEnemy->Unlock();

	Random = rand() % MAX_ENEMY;
	if (BulletCount == 30) {
		while (1)
		{

			if (g_aEnemy[Random].bUse == true) {
				SetEnemyBullet(g_aEnemy[Random].pos, PolygonPos / 100 -= g_aEnemy[Random].pos / 100, 300);
				break;
			}

			else {
				count++;
				Random++;
				if (Random >= MAX_ENEMY) {
					Random = 0;
				}
				if (count >= MAX_ENEMY) {
					break;
				}
			}
		}

		BulletCount = 0;
	}
	else
		BulletCount++;

}

void DrawEnemy(void) {

	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	int nCutEnemy;

	pDevice->SetStreamSource(0,
		g_pVtxBuffEnemy,
		0,
		sizeof(VERTEX_2D));

	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定


	for (nCutEnemy = 0; nCutEnemy < MAX_ENEMY; nCutEnemy++)
	{
		if (g_aEnemy[nCutEnemy].bUse == true)
		{
			pDevice->SetTexture(0, g_apTextureEnemy[g_aEnemy[nCutEnemy].nType]);

			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCutEnemy * 4, 2);
		}
	}
}

Enemy *GetEnemy(void) {
		return &g_aEnemy[0];
}

void SetEnemy(D3DXVECTOR3 pos,int nType) {

	VERTEX_2D *pVtx;
	int nCutEnemy;

	for (nCutEnemy = 0; nCutEnemy < MAX_ENEMY; nCutEnemy++)
	{
		if (g_aEnemy[nCutEnemy].bUse == false)
		{
			g_aEnemy[nCutEnemy].pos = pos;
			g_aEnemy[nCutEnemy].nType = nType;
			g_aEnemy[nCutEnemy].bUse = true;

			//ロック
			g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);
			/*pVtx += nCutEnemy * 4;
			pVtx[0].pos = g_aEnemy[nCutEnemy].pos;
			pVtx[1].pos = g_aEnemy[nCutEnemy].pos;
			pVtx[2].pos = g_aEnemy[nCutEnemy].pos;
			pVtx[3].pos = g_aEnemy[nCutEnemy].pos;*/
			g_pVtxBuffEnemy->Unlock();
			EnemyCount++;
			break;
		}
	}
}


//=============================================================================
// 頂点情報の作成
//=============================================================================
void MakeVertexEnemy(LPDIRECT3DDEVICE9 pDevice)
{
	VERTEX_2D *pVtx;
	int nCutVtx;


	//ロック
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

	for (nCutVtx = 0; nCutVtx < MAX_ENEMY; nCutVtx++) {

		pVtx[0].pos.x = g_aEnemy[nCutVtx].pos.x - 30;
		pVtx[1].pos.x = g_aEnemy[nCutVtx].pos.x - 30 ;
		pVtx[2].pos.x = g_aEnemy[nCutVtx].pos.x + 30;
		pVtx[3].pos.x = g_aEnemy[nCutVtx].pos.x + 30;

		pVtx[0].pos.y = g_aEnemy[nCutVtx].pos.y + 30;
		pVtx[1].pos.y = g_aEnemy[nCutVtx].pos.y - 30;
		pVtx[2].pos.y = g_aEnemy[nCutVtx].pos.y + 30;
		pVtx[3].pos.y = g_aEnemy[nCutVtx].pos.y - 30;

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
	g_pVtxBuffEnemy->Unlock();
}

int GetEnemyCount(void) {
	return EnemyCount;
}

void EnemyTotal(void) {
	EnemyCount--;
}