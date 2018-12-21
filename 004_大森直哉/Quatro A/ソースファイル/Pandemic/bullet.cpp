//=============================================================================
//
// 弾の処理 [bullet.cpp]
// Author : NAOYA OMORI
//
//=============================================================================
#include "bullet.h"
#include "Explosion.h"
#include "math.h"
#include "sound.h"
#include "ball.h"
#include "enemy.h"
#include "debugproc.h"
#include "wall.h"

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void MakeVertexBullet(LPDIRECT3DDEVICE9 pDevice);
LPDIRECT3DTEXTURE9 g_pTextureBullet = NULL;
LPDIRECT3DVERTEXBUFFER9 g_VexBuffBullet = NULL;
Bullet g_aBullet[MAX_BULLET];	//弾の総数

//*****************************************************************************
// グローバル変数
//*****************************************************************************
int g_Count = 0;
bool g_Flag = false;

//=============================================================================
// 初期化処理
//=============================================================================
void InitBullet(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//初期設定
	for (int i = 0; i < MAX_BULLET; i++) {
		g_aBullet[i].move = D3DXVECTOR3(0, 0, 0);
		g_aBullet[i].nLife = 0;
		g_aBullet[i].pos = D3DXVECTOR3(0, 0, 0);
		g_aBullet[i].bUse = false;
	}

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

	// 頂点バッファの開放
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

	D3DXVECTOR3 *ePos[MAX_ENEMY];
	VERTEX_2D *pVtx;
	int nCutBullet;

	ePos[0] = GetEnemy();			//敵の位置をとってくる
	ePos[1] = GetChase();			//敵の位置をとってくる
	ePos[2] = GetMoody();			//敵の位置をとってくる
	ePos[3] = GetSilly();			//敵の位置をとってくる

									//当たった時カウント開始
	if (g_Flag == false) {
		g_Count++;
	}

	//カウントが120に達したら以下の処理を行う
	if (g_Count == 120) {
		g_Count = 0;				//リセット
		g_Flag = true;				//Flagをtrueに
		SetChaseMoveKey(TRUE);		//敵を動くようにする
		SetAmbushMoveKey(TRUE);		//敵を動くようにする
		SetMoodyMoveKey(TRUE);		//敵を動くようにする
		SetSillyMoveKey(TRUE);		//敵を動くようにする
	}

	//ロック
	g_VexBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	for (nCutBullet = 0; nCutBullet < MAX_BULLET; nCutBullet++)
	{
		//弾と敵の当たり判定
		if (Collision(g_aBullet[nCutBullet].pos, *ePos[0], 10, 20) && g_aBullet[nCutBullet].bUse == true) {
			g_aBullet[nCutBullet].bUse = false;		//当たった弾を消す
			SetExplosion(*ePos[0]);					//敵の位置に爆発エフェクト
			EnemyHit();								//ヒット時の敵の関数呼び出し
			SetAmbushHitKey(TRUE);
		}

		//弾と敵の当たり判定
		if (Collision(g_aBullet[nCutBullet].pos, *ePos[1], 10, 20) && g_aBullet[nCutBullet].bUse == true) {
			g_aBullet[nCutBullet].bUse = false;		//当たった弾を消す
			SetExplosion(*ePos[1]);					//敵の位置に爆発エフェクト
			SetChaseMoveKey(false);					//敵を動くようにする
			g_Flag = false;
			SetChaseHitKey(TRUE);
		}

		//弾と敵の当たり判定
		if (Collision(g_aBullet[nCutBullet].pos, *ePos[2], 10, 20) && g_aBullet[nCutBullet].bUse == true) {
			g_aBullet[nCutBullet].bUse = false;		//当たった弾を消す
			SetExplosion(*ePos[2]);					//敵の位置に爆発エフェクト
			SetMoodyMoveKey(false);					//敵を動くようにする
			g_Flag = false;
			SetMoodyHitKey(TRUE);
		}

		//弾と敵の当たり判定
		if (Collision(g_aBullet[nCutBullet].pos, *ePos[3], 10, 20) && g_aBullet[nCutBullet].bUse == true) {
			g_aBullet[nCutBullet].bUse = false;		//当たった弾を消す
			SetExplosion(*ePos[3]);					//敵の位置に爆発エフェクト
			SetSillyMoveKey(false);					//敵を動くようにする
			g_Flag = false;
			SetSillyHitKey(TRUE);
		}

		//弾がtureの場合
		if (g_aBullet[nCutBullet].bUse == true)
		{
			g_aBullet[nCutBullet].pos += g_aBullet[nCutBullet].move;

			g_aBullet[nCutBullet].nLife--;

			// 頂点座標の設定
			pVtx[0].pos.x = g_aBullet[nCutBullet].pos.x - 10;
			pVtx[1].pos.x = g_aBullet[nCutBullet].pos.x - 10;
			pVtx[2].pos.x = g_aBullet[nCutBullet].pos.x + 10;
			pVtx[3].pos.x = g_aBullet[nCutBullet].pos.x + 10;

			pVtx[0].pos.y = g_aBullet[nCutBullet].pos.y + 10;
			pVtx[1].pos.y = g_aBullet[nCutBullet].pos.y - 10;
			pVtx[2].pos.y = g_aBullet[nCutBullet].pos.y + 10;
			pVtx[3].pos.y = g_aBullet[nCutBullet].pos.y - 10;

			pVtx += 4;

			//画面外に出たら自機の弾を消す
			if (g_aBullet[nCutBullet].nLife == 0 || g_aBullet[nCutBullet].pos.y <= 0)
			{
				g_aBullet[nCutBullet].bUse = false;				//弾を消す
				SetExplosion(g_aBullet[nCutBullet].pos);		//消えた所で爆発エフェクトを出す
			}
		}
	}
	//ロック解除
	g_VexBuffBullet->Unlock();
}

void DrawBullet(void) {

	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//デバイスの取得

	int nCutBullet;

	//データストリームにセット
	pDevice->SetStreamSource(0,
		g_VexBuffBullet,
		0,
		sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, g_pTextureBullet);

	for (nCutBullet = 0; nCutBullet <MAX_BULLET; nCutBullet++)
	{
		if (g_aBullet[nCutBullet].bUse == true)
		{
			// ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCutBullet * 4, 2);
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

			// 頂点座標の設定
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
	g_VexBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	for (nCutVtx = 0; nCutVtx < MAX_BULLET; nCutVtx++) {

		// 頂点座標の設定
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

		// テクスチャの設定
		pVtx[0].tex = D3DXVECTOR2(0, 0);
		pVtx[1].tex = D3DXVECTOR2(1, 0);
		pVtx[2].tex = D3DXVECTOR2(0, 1);
		pVtx[3].tex = D3DXVECTOR2(1, 1);
		pVtx += 4;

	}

	//ロック解除
	g_VexBuffBullet->Unlock();
}

void EnemyHit(void) {
	SetAmbushMoveKey(false);		//敵を動くようにする
	g_Flag = false;
}