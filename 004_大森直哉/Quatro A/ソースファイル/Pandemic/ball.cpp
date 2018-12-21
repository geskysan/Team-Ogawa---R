//=============================================================================
//
// ボール処理 [ball.cpp]
// Author : NAOYA OMORI
//
//=============================================================================
#include "ball.h"
#include "polygon.h"
#include "explosion.h"
#include "DebugProc.h"
#include "input.h"
#include "sound.h"
//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void MakeVertexBall(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// マクロ定義宣言
//*****************************************************************************
#define MAX_BALL	(135)
#define BALL_SIZE_X	(30)
#define BALL_SIZE_Y (30)

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9	g_pTextureBall = NULL;	// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBall = NULL;//頂点バッファのポインタ
BALL g_ball[MAX_BALL];

int g_BallCount;		//ボールの数を数える変数
int g_ScoreCount;		//スコアを数える変数
int g_BulletCounter;	//弾（バレット）の数える変数
int g_BulletCount;		//BulletCounterを変更するための変数

//=============================================================================
// 初期化処理
//=============================================================================
void InitBall(void)
{

	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//弾の初期設定
	for (int nCntBall = 0; nCntBall < MAX_BALL; nCntBall++) {
		g_ball[nCntBall].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_ball[nCntBall].rot = D3DXVECTOR3(0, 0, 0);
		g_ball[nCntBall].fAngleBall = atan2f(BALL_SIZE_X / 2, BALL_SIZE_Y / 2);
		g_ball[nCntBall].fLengthBall = sqrtf((BALL_SIZE_X / 2) * (BALL_SIZE_X / 2) + (BALL_SIZE_Y / 2) * (BALL_SIZE_Y / 2));
		g_ball[nCntBall].bUse = false;
	}

	//変数の初期設定
	g_ScoreCount = 0;
	g_BallCount = 0;
	g_BulletCount = 0;
	g_BulletCounter = 0;

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_BALL,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBall,
		NULL);

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/ball.png", &g_pTextureBall);

	//頂点設定
	MakeVertexBall(pDevice);

}

//=============================================================================
// 終了処理
//=============================================================================
void UninitBall(void)
{
	// 頂点バッファの開放
	if (g_pVtxBuffBall != NULL)
	{
		g_pVtxBuffBall->Release();
		g_pVtxBuffBall = NULL;
	}

	// テクスチャの開放
	if (g_pTextureBall != NULL)
	{
		g_pTextureBall->Release();
		g_pTextureBall = NULL;
	}

}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateBall(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXVECTOR3 PlayerPos;	//自機の位置用
	VERTEX_2D *pVtx;
	int nCntBall;

	PlayerPos = GetMinePos();	//プレイヤーのポジションを持ってくる。

	for (nCntBall = 0; nCntBall < MAX_BALL; nCntBall++) {
		if (g_ball[nCntBall].bUse == true) {

			//ロック
			g_pVtxBuffBall->Lock(0, 0, (void**)&pVtx, 0);

			pVtx += 4 * nCntBall;

			// 頂点座標の設定
			pVtx[0].pos.x = g_ball[nCntBall].pos.x - sinf(g_ball[nCntBall].fAngleBall - g_ball[nCntBall].rot.z)*g_ball[nCntBall].fLengthBall;
			pVtx[0].pos.y = g_ball[nCntBall].pos.y - cosf(g_ball[nCntBall].fAngleBall - g_ball[nCntBall].rot.z)*g_ball[nCntBall].fLengthBall;
			pVtx[0].pos.z = 0.0f;

			pVtx[1].pos.x = g_ball[nCntBall].pos.x + sinf(g_ball[nCntBall].fAngleBall + g_ball[nCntBall].rot.z)*g_ball[nCntBall].fLengthBall;
			pVtx[1].pos.y = g_ball[nCntBall].pos.y - cosf(g_ball[nCntBall].fAngleBall + g_ball[nCntBall].rot.z)*g_ball[nCntBall].fLengthBall;
			pVtx[1].pos.z = 0.0f;

			pVtx[2].pos.x = g_ball[nCntBall].pos.x - sinf(g_ball[nCntBall].fAngleBall + g_ball[nCntBall].rot.z)*g_ball[nCntBall].fLengthBall;
			pVtx[2].pos.y = g_ball[nCntBall].pos.y + cosf(g_ball[nCntBall].fAngleBall + g_ball[nCntBall].rot.z)*g_ball[nCntBall].fLengthBall;
			pVtx[2].pos.z = 0.0f;

			pVtx[3].pos.x = g_ball[nCntBall].pos.x + sinf(g_ball[nCntBall].fAngleBall - g_ball[nCntBall].rot.z)*g_ball[nCntBall].fLengthBall;
			pVtx[3].pos.y = g_ball[nCntBall].pos.y + cosf(g_ball[nCntBall].fAngleBall - g_ball[nCntBall].rot.z)*g_ball[nCntBall].fLengthBall;
			pVtx[3].pos.z = 0.0f;

			//解除（アンロック）
			g_pVtxBuffBall->Unlock();

			//玉とプレイヤーの接触時の当たり判定
			if (Collision(g_ball[nCntBall].pos, PlayerPos, 10, 20)) {
				g_ball[nCntBall].bUse = false;
				g_ScoreCount += 10;
				g_BulletCounter += 1;
				BallTotal();
				Play(SOUND_LABEL_SE_EATING);
			}
		}
	}

	//玉を１０個とると弾の数字を1あげるように
	if (g_BulletCounter == 10) {
		g_BulletCount += 1;
		g_BulletCounter = 0;
	}

	//数字が０以下にならないように
	if (g_BulletCount <= 0) {
		g_BulletCount = 0;
	}

	PrintDebug("\n");
	PrintDebug("\n");
	PrintDebug("玉の数：%d\n", g_BallCount);
	PrintDebug("testcount:%d\n", g_BulletCounter);

}

//=============================================================================
// 描画処理
//=============================================================================
void DrawBall(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	int nCntBall;

	for (nCntBall = 0; nCntBall < MAX_BALL; nCntBall++) {

		if (g_ball[nCntBall].bUse == true) {

			//データストリームにセット
			pDevice->SetStreamSource(0,
				g_pVtxBuffBall,
				0,
				sizeof(VERTEX_2D));

			// 頂点フォーマットの設定
			pDevice->SetFVF(FVF_VERTEX_2D);

			// テクスチャの設定
			pDevice->SetTexture(0, g_pTextureBall);

			// ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntBall * 4, 2);
		}
	}

}

//=============================================================================
// 頂点情報の作成
//=============================================================================
void MakeVertexBall(LPDIRECT3DDEVICE9 pDevice)
{
	VERTEX_2D *pVtx;
	int nCutVtx;

	//ロック
	g_pVtxBuffBall->Lock(0, 0, (void**)&pVtx, 0);

	for (nCutVtx = 0; nCutVtx < MAX_BALL; nCutVtx++) {

		// 頂点座標の設定
		pVtx[0].pos.x = g_ball[nCutVtx].pos.x - sinf(g_ball[nCutVtx].fAngleBall - g_ball[nCutVtx].rot.z)*g_ball[nCutVtx].fLengthBall;
		pVtx[0].pos.y = g_ball[nCutVtx].pos.y - cosf(g_ball[nCutVtx].fAngleBall - g_ball[nCutVtx].rot.z)*g_ball[nCutVtx].fLengthBall;
		pVtx[0].pos.z = 0.0f;

		pVtx[1].pos.x = g_ball[nCutVtx].pos.x + sinf(g_ball[nCutVtx].fAngleBall + g_ball[nCutVtx].rot.z)*g_ball[nCutVtx].fLengthBall;
		pVtx[1].pos.y = g_ball[nCutVtx].pos.y - cosf(g_ball[nCutVtx].fAngleBall + g_ball[nCutVtx].rot.z)*g_ball[nCutVtx].fLengthBall;
		pVtx[1].pos.z = 0.0f;

		pVtx[2].pos.x = g_ball[nCutVtx].pos.x - sinf(g_ball[nCutVtx].fAngleBall + g_ball[nCutVtx].rot.z)*g_ball[nCutVtx].fLengthBall;
		pVtx[2].pos.y = g_ball[nCutVtx].pos.y + cosf(g_ball[nCutVtx].fAngleBall + g_ball[nCutVtx].rot.z)*g_ball[nCutVtx].fLengthBall;
		pVtx[2].pos.z = 0.0f;

		pVtx[3].pos.x = g_ball[nCutVtx].pos.x + sinf(g_ball[nCutVtx].fAngleBall - g_ball[nCutVtx].rot.z)*g_ball[nCutVtx].fLengthBall;
		pVtx[3].pos.y = g_ball[nCutVtx].pos.y + cosf(g_ball[nCutVtx].fAngleBall - g_ball[nCutVtx].rot.z)*g_ball[nCutVtx].fLengthBall;
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

		// テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0, 1);
		pVtx[1].tex = D3DXVECTOR2(0, 0);
		pVtx[2].tex = D3DXVECTOR2(1, 1);
		pVtx[3].tex = D3DXVECTOR2(1, 0);
		pVtx += 4;
	}

	//ロック解除
	g_pVtxBuffBall->Unlock();
}


//ボールを並べるための処理
void SetBall(D3DXVECTOR3 pos) {

	int nCntBall;

	for (nCntBall = 0; nCntBall < MAX_BALL; nCntBall++) {

		if (g_ball[nCntBall].bUse == false)
		{
			g_ball[nCntBall].pos = pos;
			g_ball[nCntBall].bUse = true;
			g_BallCount++;
			break;
		}
	}
}

//どこでも使えるあたり判定の基本（円ver）
bool Collision(D3DXVECTOR3 C1, D3DXVECTOR3 C2, float R1, float R2) {
	double dx, dy, dr;
	dx = fabs(C1.x - C2.x);
	dy = fabs(C1.y - C2.y);
	dr = R1 + R2;
	if (dx * 2 + dy * 2 <= dr * 2)
		return true;
	else
		return false;
}

int GetBallCount(void) {
	return g_BallCount;
}

void BallTotal(void) {
	g_BallCount--;
}

int GetScore(void) {
	return g_ScoreCount;
}

int GetBulletCount(void) {
	return g_BulletCount;
}

void SubBulletCount(int number) {
	g_BulletCount -= number;
}
