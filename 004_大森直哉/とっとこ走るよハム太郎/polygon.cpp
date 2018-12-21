//=============================================================================
//
// ポリゴン処理 [polygon.cpp]
// Author : AKIRA TANAKA
//
//=============================================================================
#include "polygon.h"
#include "input.h"
#include "bullet.h"
#include "enemy.h"
#include "number.h"
#include "explosion.h"
#include "life.h"
#include "fade.h"
#include "Enemybullet.h"
#include "sound.h"
//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void MakeVertexPolygon(LPDIRECT3DDEVICE9 pDevice);

#define MAX_ENEMY (128)

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9	g_pTexturePolygon = NULL;		// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPolygon = NULL;	//頂点バッファのポインタ

int g_nCounterAnim = 0;
int g_nPatternAnim = 0;
int InvisibleCount = 0;
int KeyFlag;

Mine mine;

//=============================================================================
// 初期化処理
//=============================================================================
void InitPolygon(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D)*4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffPolygon,
		NULL);

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,"data/TEXTURE/player000.png", &g_pTexturePolygon);

	mine.g_posPolygon = D3DXVECTOR3(630, 600, 0);
	mine.g_rotPolygon = D3DXVECTOR3(0, 0, 0);
	mine.g_fAnglePolygon = atan2f(50, 50);
	mine.g_fLengthPolygon = sqrtf(50 * 50 + 50 * 50);
	mine.PlayerHP = MAX_LIFE;
	mine.bUse = true;
	mine.bHit = false;
	KeyFlag = true;

	//頂点設定
	MakeVertexPolygon(pDevice);

}

//=============================================================================
// 終了処理
//=============================================================================
void UninitPolygon(void)
{
	// テクスチャの開放4
	if (g_pVtxBuffPolygon != NULL)
	{
		g_pVtxBuffPolygon->Release();
		g_pVtxBuffPolygon = NULL;
	}
	if (g_pTexturePolygon != NULL)
	{
		g_pTexturePolygon->Release();
		g_pTexturePolygon = NULL;
	}

}
//=============================================================================
// 更新処理
//=============================================================================
void UpdatePolygon(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	Enemy *pEnemy;
	VERTEX_2D *pVtx;
	int move;

	move = 5;

	//ロック
	g_pVtxBuffPolygon->Lock(0,
		0,
		(void**)&pVtx,
		0);


		// テクスチャ座標の設定
		MakeVertexPolygon(pDevice);

		pVtx[0].pos.x = mine.g_posPolygon.x + sinf(-D3DX_PI + mine.g_fAnglePolygon + mine.g_rotPolygon.z)*mine.g_fLengthPolygon;
		pVtx[0].pos.y = mine.g_posPolygon.y + cosf(-D3DX_PI + mine.g_fAnglePolygon + mine.g_rotPolygon.z)*mine.g_fLengthPolygon;
		pVtx[0].pos.z = 0.0f;

		pVtx[1].pos.x = mine.g_posPolygon.x + sinf(3.14 - mine.g_fAnglePolygon + mine.g_rotPolygon.z)*mine.g_fLengthPolygon;
		pVtx[1].pos.y = mine.g_posPolygon.y + cosf(3.14 - mine.g_fAnglePolygon + mine.g_rotPolygon.z)*mine.g_fLengthPolygon;
		pVtx[1].pos.z = 0.0f;

		pVtx[2].pos.x = mine.g_posPolygon.x + sinf(-mine.g_fAnglePolygon + mine.g_rotPolygon.z)*mine.g_fLengthPolygon;
		pVtx[2].pos.y = mine.g_posPolygon.y + cosf(-mine.g_fAnglePolygon + mine.g_rotPolygon.z)*mine.g_fLengthPolygon;
		pVtx[2].pos.z = 0.0f;

		pVtx[3].pos.x = mine.g_posPolygon.x + sinf(mine.g_fAnglePolygon + mine.g_rotPolygon.z)*mine.g_fLengthPolygon;
		pVtx[3].pos.y = mine.g_posPolygon.y + cosf(mine.g_fAnglePolygon + mine.g_rotPolygon.z)*mine.g_fLengthPolygon;
		pVtx[3].pos.z = 0.0f;

	//ロック解除
	g_pVtxBuffPolygon->Unlock();

	if (KeyFlag == true) {

		if (GetKeyboardPress(DIK_W))
			mine.g_posPolygon.y -= move;

		if (GetKeyboardPress(DIK_S))
			mine.g_posPolygon.y += move;

		if (GetKeyboardPress(DIK_A))
			mine.g_posPolygon.x -= move;

		if (GetKeyboardPress(DIK_D))
			mine.g_posPolygon.x += move;

		if (GetKeyboardPress(DIK_LEFT))
			mine.g_rotPolygon.z += 0.05;

		if (GetKeyboardPress(DIK_RIGHT))
			mine.g_rotPolygon.z -= 0.05;

		if (GetKeyboardTrigger(DIK_SPACE))
			SetBullet(mine.g_posPolygon, D3DXVECTOR3(0, -7, 0), 100);
	}

	if (mine.PlayerHP == 0) {
		KeyFlag = false;
		SetFade(MODE_RESULT);				//ゲームオーバー処理
		mine.bUse = false;
	}

	//敵の０番目の情報を取得
	pEnemy = GetEnemy();

	for (int nCutEnemy = 0; nCutEnemy < MAX_ENEMY; nCutEnemy++) {
		if (pEnemy->bUse == true) {
			//プレイヤーと敵との当たり判定
			if (mine.bHit == false) {
				if (Collision(pEnemy->pos, mine.g_posPolygon, 10, 30) && mine.PlayerHP != 0)
				{
					mine.bHit = true;
					//pEnemy->bUse = (false);
					EnemyTotal();
					SubLife(1);
					Play(SOUND_LABEL_SE_HIT001);
				}
			}
		}

		pEnemy++;

	}

	if (mine.bHit == true) {
		InvisiblePlayer();
	}

}

//=============================================================================
// 描画処理
//=============================================================================
void DrawPolygon(void)
{
	if (!mine.bUse)
		return;
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//データストリームにセット
	pDevice->SetStreamSource(0,
		g_pVtxBuffPolygon,
		0,
		sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, g_pTexturePolygon);

	// ポリゴンの描画
	pDevice -> DrawPrimitive(D3DPT_TRIANGLESTRIP,0,2);

}

//=============================================================================
// 頂点情報の作成
//=============================================================================
void MakeVertexPolygon(LPDIRECT3DDEVICE9 pDevice)
{

	VERTEX_2D *pVtx;

	//ロック
	g_pVtxBuffPolygon->Lock(0,
		0,
		(void**)&pVtx,
		0);

	// 頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(0, 0, 0.0f);//xy座標で位置決め
	pVtx[1].pos = D3DXVECTOR3(100, 0, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0, 100, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(100, 100, 0.0f);


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
	  
	//ロック解除
	g_pVtxBuffPolygon->Unlock();

}

D3DXVECTOR3 GetMinePos(void) {
	return mine.g_posPolygon;
}

int GetPlayerHP(void) {
	return 	mine.PlayerHP;
}

void SubLife(int Life) {
	mine.PlayerHP -= Life;
}

void InvisiblePlayer(void) {

	if (mine.bUse && InvisibleCount % 5 == 0) {
		mine.bUse = false;
	}
	else if (!mine.bUse && InvisibleCount % 5 == 0) {
		mine.bUse = true;
	}
	InvisibleCount++;
	if (InvisibleCount >= 150)
	{
		InvisibleCount = 0;
		mine.bHit = false;
		mine.bUse = true;
	}
}

Mine *GetMine(void) {
	return &mine;
}