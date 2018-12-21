//=============================================================================
//
// 弾の処理 [bullet.cpp]
// Author : 
//
//=============================================================================
#include "EnemyBullet.h"
#include "Explosion.h"
#include "Enemy.h"
#include "math.h"
#include "number.h"
#include "bullet.h"
#include "life.h"
#include "polygon.h"
#include "sound.h"
//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void MakeVertexEnemyBullet(LPDIRECT3DDEVICE9 pDevice);	//頂点座標作成

//*****************************************************************************
// 敵の弾の構造体定義
//*****************************************************************************
typedef struct
{
	D3DXVECTOR3 pos;	//位置
	D3DXVECTOR3 move;	//移動量
	int nLife;			//寿命
	bool bUse;			//使用しているかどうか
}EnemyBullet;			//構造体名

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
LPDIRECT3DTEXTURE9 g_pTextureEnemyBullet = NULL;		//敵の弾の
LPDIRECT3DVERTEXBUFFER9 g_VexBuffEnemyBullet = NULL;	//敵の弾の
EnemyBullet g_aEnemyBullet[MAX_ENEMYBULLET];			//敵の弾の総数

//=============================================================================
// 初期化処理
//=============================================================================
void InitEnemyBullet(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//構造体の中身の初期化
	for (int i = 0; i < MAX_ENEMYBULLET; i++) {
		g_aEnemyBullet[i].move = D3DXVECTOR3(0, 0, 0);	//移動量
		g_aEnemyBullet[i].nLife = 0;					//寿命
		g_aEnemyBullet[i].pos = D3DXVECTOR3(0, 0, 0);	//位置
		g_aEnemyBullet[i].bUse = false;					//使用しているかどうか
	}

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/bullet000.png", &g_pTextureEnemyBullet);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_ENEMYBULLET,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_VexBuffEnemyBullet,
		NULL);

	//頂点座標の呼び出し
	MakeVertexEnemyBullet(pDevice);

}
//=============================================================================
// 終了処理
//=============================================================================
void UninitEnemyBullet(void) {

	if (g_VexBuffEnemyBullet != NULL)
	{
		g_VexBuffEnemyBullet->Release();
		g_VexBuffEnemyBullet = NULL;
	}

	// テクスチャの開放
	if (g_pTextureEnemyBullet != NULL) 
	{
		g_pTextureEnemyBullet->Release();
		g_pTextureEnemyBullet = NULL;
	}

}
//=============================================================================
//更新処理
//=============================================================================
void UpdateEnemyBullet(void) {

	VERTEX_2D *pVtx;
	D3DXVECTOR3 PolygonPos;
	Mine *pMine;
	bool PHit;
	int nCutEnemyBullet;

	pMine = GetMine();

	g_VexBuffEnemyBullet->Lock(0, 0, (void**)&pVtx, 0);
	for (nCutEnemyBullet = 0; nCutEnemyBullet <MAX_ENEMYBULLET; nCutEnemyBullet++)
	{
		PolygonPos = GetMinePos();

		if (g_aEnemyBullet[nCutEnemyBullet].bUse == true)
		{

			g_aEnemyBullet[nCutEnemyBullet].pos += g_aEnemyBullet[nCutEnemyBullet].move;
			g_aEnemyBullet[nCutEnemyBullet].nLife--;


			pVtx[0].pos.x = g_aEnemyBullet[nCutEnemyBullet].pos.x - 10;
			pVtx[1].pos.x = g_aEnemyBullet[nCutEnemyBullet].pos.x - 10;
			pVtx[2].pos.x = g_aEnemyBullet[nCutEnemyBullet].pos.x + 10;
			pVtx[3].pos.x = g_aEnemyBullet[nCutEnemyBullet].pos.x + 10;

			pVtx[0].pos.y = g_aEnemyBullet[nCutEnemyBullet].pos.y + 10;
			pVtx[1].pos.y = g_aEnemyBullet[nCutEnemyBullet].pos.y - 10;
			pVtx[2].pos.y = g_aEnemyBullet[nCutEnemyBullet].pos.y + 10;
			pVtx[3].pos.y = g_aEnemyBullet[nCutEnemyBullet].pos.y - 10;

			//[頂点バッファの内容も更新]
			if (g_aEnemyBullet[nCutEnemyBullet].nLife == 0 || g_aEnemyBullet[nCutEnemyBullet].pos.y >= SCREEN_HEIGHT)
			{
				g_aEnemyBullet[nCutEnemyBullet].bUse = false;
				//SetExplosion(g_aEnemyBullet[nCutEnemyBullet].pos);
			}

			if (Collision(g_aEnemyBullet[nCutEnemyBullet].pos, PolygonPos, 10, 30) && pMine->bHit == false && pMine->PlayerHP != 0) {	//敵の弾と自機の当たり判定
				g_aEnemyBullet[nCutEnemyBullet].bUse = false;							//自機と当たった弾を消す
				pMine->bHit = (true);
				SubLife(1);
				Play(SOUND_LABEL_SE_HIT001);
			}
		}
		pVtx += 4;
	}
	//アンロック
	g_VexBuffEnemyBullet->Unlock();
}

void DrawEnemyBullet(void) {

	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	int nCutBullet;

	pDevice->SetStreamSource(0,
		g_VexBuffEnemyBullet,
		0,
		sizeof(VERTEX_2D));

	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, g_pTextureEnemyBullet);

	for (nCutBullet = 0; nCutBullet <MAX_ENEMYBULLET; nCutBullet++)
	{
		if (g_aEnemyBullet[nCutBullet].bUse == true)
		{
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCutBullet * 4, 2);
		}
	}
}

void SetEnemyBullet(D3DXVECTOR3 pos, D3DXVECTOR3 move, int nLife) {

	VERTEX_2D *pVtx;
	int nCutEnemyBullet;

	for (nCutEnemyBullet = 0; nCutEnemyBullet < MAX_ENEMYBULLET; nCutEnemyBullet++)
	{
		if (g_aEnemyBullet[nCutEnemyBullet].bUse == false)
		{
			g_aEnemyBullet[nCutEnemyBullet].pos = pos;

			//ロック
			g_VexBuffEnemyBullet->Lock(0, 0, (void**)&pVtx, 0);

			pVtx += nCutEnemyBullet * 4;
			pVtx[0].pos.x = g_aEnemyBullet[nCutEnemyBullet].pos.x - 10;
			pVtx[1].pos.x = g_aEnemyBullet[nCutEnemyBullet].pos.x - 10;
			pVtx[2].pos.x = g_aEnemyBullet[nCutEnemyBullet].pos.x + 10;
			pVtx[3].pos.x = g_aEnemyBullet[nCutEnemyBullet].pos.x + 10;

			pVtx[0].pos.y = g_aEnemyBullet[nCutEnemyBullet].pos.y + 10;
			pVtx[1].pos.y = g_aEnemyBullet[nCutEnemyBullet].pos.y - 10;
			pVtx[2].pos.y = g_aEnemyBullet[nCutEnemyBullet].pos.y + 10;
			pVtx[3].pos.y = g_aEnemyBullet[nCutEnemyBullet].pos.y - 10;
			g_VexBuffEnemyBullet->Unlock();

			g_aEnemyBullet[nCutEnemyBullet].move = move;
			g_aEnemyBullet[nCutEnemyBullet].nLife = nLife;
			g_aEnemyBullet[nCutEnemyBullet].bUse = true;
			break;
		}
	}
}


//=============================================================================
// 頂点情報の作成
//=============================================================================
void MakeVertexEnemyBullet(LPDIRECT3DDEVICE9 pDevice)
{
	VERTEX_2D *pVtx;
	int nCutVtx;


	//ロック
	g_VexBuffEnemyBullet->Lock(0, 0, (void**)&pVtx, 0);

	for (nCutVtx = 0; nCutVtx < MAX_ENEMYBULLET; nCutVtx++) {

		pVtx[0].pos.x = g_aEnemyBullet[nCutVtx].pos.x - 20;
		pVtx[1].pos.x = g_aEnemyBullet[nCutVtx].pos.x - 20;
		pVtx[2].pos.x = g_aEnemyBullet[nCutVtx].pos.x + 20;
		pVtx[3].pos.x = g_aEnemyBullet[nCutVtx].pos.x + 20;

		pVtx[0].pos.y = g_aEnemyBullet[nCutVtx].pos.y + 20;
		pVtx[1].pos.y = g_aEnemyBullet[nCutVtx].pos.y - 20;
		pVtx[2].pos.y = g_aEnemyBullet[nCutVtx].pos.y + 20;
		pVtx[3].pos.y = g_aEnemyBullet[nCutVtx].pos.y - 20;

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
	g_VexBuffEnemyBullet->Unlock();

}