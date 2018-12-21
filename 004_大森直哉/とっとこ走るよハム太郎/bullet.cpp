//=============================================================================
//
// 弾の処理 [bullet.cpp]
// Author : 
//
//=============================================================================
#include "bullet.h"
#include "Explosion.h"
#include "Enemy.h"
#include "math.h"
#include "number.h"
#include "sound.h"

//弾の構造体
typedef struct
{
	D3DXVECTOR3 pos;	//位置
	D3DXVECTOR3 move;	//移動量
	int nLife;			//寿命
	bool bUse;			//使用しているかどうか
}Bullet;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void MakeVertexBullet(LPDIRECT3DDEVICE9 pDevice);

//グローバル変数
LPDIRECT3DTEXTURE9 g_pTextureBullet = NULL;
LPDIRECT3DVERTEXBUFFER9 g_VexBuffBullet = NULL;
Bullet g_aBullet[MAX_BULLET];	//弾の総数
int ScoreCount;					//スコア
//=============================================================================
// 初期化処理
//=============================================================================
void InitBullet(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for (int i = 0; i < MAX_BULLET; i++) {
		g_aBullet[i].move = D3DXVECTOR3(0, 0, 0);
		g_aBullet[i].nLife = 0;
		g_aBullet[i].pos = D3DXVECTOR3(0, 0, 0);
		g_aBullet[i].bUse = false;
		//頂点設定
		//pVtx += 4;
	}

	ScoreCount = 0;

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/bullet000.png", &g_pTextureBullet);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_BULLET,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_VexBuffBullet,
		NULL);

		MakeVertexBullet(pDevice);

}

	void UninitBullet(void) {

		if (g_VexBuffBullet != NULL)
		{
			g_VexBuffBullet->Release();
			g_VexBuffBullet = NULL;
		}

		// テクスチャの開放
		if (g_pTextureBullet != NULL) 
		{
			g_pTextureBullet->Release();
			g_pTextureBullet = NULL;
		}
}
//=============================================================================
//更新処理
//=============================================================================
void UpdateBullet(void) {

	VERTEX_2D *pVtx;
	Enemy *pEnemy;
	int nCutBullet;	

	//ロック
	g_VexBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	for (nCutBullet = 0; nCutBullet <MAX_BULLET; nCutBullet++)
	{
		pEnemy = GetEnemy();		//敵の情報

		if (g_aBullet[nCutBullet].bUse == true)
		{
			g_aBullet[nCutBullet].pos += g_aBullet[nCutBullet].move;

			g_aBullet[nCutBullet].nLife--;

			pVtx[0].pos.x = g_aBullet[nCutBullet].pos.x - 10;
			pVtx[1].pos.x = g_aBullet[nCutBullet].pos.x - 10;
			pVtx[2].pos.x = g_aBullet[nCutBullet].pos.x + 10;
			pVtx[3].pos.x = g_aBullet[nCutBullet].pos.x + 10;

			pVtx[0].pos.y = g_aBullet[nCutBullet].pos.y + 10;
			pVtx[1].pos.y = g_aBullet[nCutBullet].pos.y - 10;
			pVtx[2].pos.y = g_aBullet[nCutBullet].pos.y + 10;
			pVtx[3].pos.y = g_aBullet[nCutBullet].pos.y - 10;

			//画面外に出たら自機の弾を消す
			if (g_aBullet[nCutBullet].nLife == 0 || g_aBullet[nCutBullet].pos.y <= 0)
			{
				g_aBullet[nCutBullet].bUse = false;
			}

			for (int nCutEnemy = 0; nCutEnemy < MAX_BULLET; nCutEnemy++) {
				if (pEnemy->bUse == true) {
					//自機の弾と敵の当たり判定
					if (Collision(pEnemy->pos, g_aBullet[nCutBullet].pos, 10,25))
					{
						SetExplosion(pEnemy->pos);
						g_aBullet[nCutBullet].bUse = false;
						pEnemy->bUse = false;
						pEnemy->pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
						EnemyTotal();
						ScoreCount += 10;
					}
				}
				pEnemy++;
			}
		}
		pVtx += 4;
	}
	//ロック解除
	g_VexBuffBullet->Unlock();
}

void DrawBullet(void) {

	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//デバイスの取得

	int nCutBullet;

	pDevice->SetStreamSource(0,
		g_VexBuffBullet,
		0,
		sizeof(VERTEX_2D));

	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, g_pTextureBullet);

	for (nCutBullet = 0; nCutBullet <MAX_BULLET; nCutBullet++)
	{
		if (g_aBullet[nCutBullet].bUse == true)
		{
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCutBullet*4, 2);
		}
	}
}

void SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 move, int nLife) {

	VERTEX_2D *pVtx;
	int nCutBullet;

	for (nCutBullet = 0; nCutBullet < MAX_BULLET; nCutBullet++)
	{
		if (g_aBullet[nCutBullet].bUse == false)
		{
			g_aBullet[nCutBullet].pos = pos; 
			
			//ロック
			g_VexBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

			pVtx += nCutBullet * 4;
			pVtx[0].pos = g_aBullet[nCutBullet].pos;
			pVtx[1].pos = g_aBullet[nCutBullet].pos;
			pVtx[2].pos = g_aBullet[nCutBullet].pos;
			pVtx[3].pos = g_aBullet[nCutBullet].pos;

			//ロック解除
			g_VexBuffBullet->Unlock();

			g_aBullet[nCutBullet].move = move;

			g_aBullet[nCutBullet].nLife = nLife;

			g_aBullet[nCutBullet].bUse = true;

			Play(SOUND_LABEL_SE_SHOT000);
			break;
		}
	}
}


//=============================================================================
// 頂点情報の作成
//=============================================================================
void MakeVertexBullet(LPDIRECT3DDEVICE9 pDevice)
{
	VERTEX_2D *pVtx;
	int nCutVtx;


	//ロック
	g_VexBuffBullet->Lock(0,0,(void**)&pVtx,0);

	for (nCutVtx = 0; nCutVtx < MAX_BULLET; nCutVtx++) {

		pVtx[0].pos.x = g_aBullet[nCutVtx].pos.x;
		pVtx[1].pos.x = g_aBullet[nCutVtx].pos.x;
		pVtx[2].pos.x = g_aBullet[nCutVtx].pos.x + 20;
		pVtx[3].pos.x = g_aBullet[nCutVtx].pos.x + 20;

		pVtx[0].pos.y = g_aBullet[nCutVtx].pos.y + 20;
		pVtx[1].pos.y = g_aBullet[nCutVtx].pos.y;
		pVtx[2].pos.y = g_aBullet[nCutVtx].pos.y + 20;
		pVtx[3].pos.y = g_aBullet[nCutVtx].pos.y;

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

		pVtx[0].tex = D3DXVECTOR2(0, 0);
		pVtx[1].tex = D3DXVECTOR2(1, 0);
		pVtx[2].tex = D3DXVECTOR2(0, 1);
		pVtx[3].tex = D3DXVECTOR2(1, 1);
		pVtx += 4;
	}
	//ロック解除
	g_VexBuffBullet->Unlock();
}

//どうこでも使えるあたり判定の基本（円ver）
bool Collision(D3DXVECTOR3 C1, D3DXVECTOR3 C2, float R1, float R2) {
	float dx, dy, dr;
	dx = fabs(C1.x - C2.x);
	dy = fabs(C1.y - C2.y);
	dr = R1 + R2;
	if (dx * 2 + dy * 2 <= dr * 2)
		return true;
	else
		return false;
}

int GetScore(void) {
	return ScoreCount;
}