//=============================================================================
//
// ポリゴン処理 [polygon.cpp]
// Author : NAOYA OMORI
//
//=============================================================================
#include "polygon.h"
#include "input.h"
#include "fade.h"
#include "sound.h"
#include "DebugProc.h"
#include "bullet.h"
#include "Enemy.h"
#include "wall.h"
#include "map.h"
#include "life.h"
#include "ball.h"
#include "explosion.h"
#include "timer.h"
#include "font.h"
#include "ball.h"

//*****************************************************************************
// マクロ定義宣言
//*****************************************************************************
#define PLAYER_SIZE_X (45)
#define PLAYER_SIZE_Y (45)
#define MAX_PATTERN (4)

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void MakeVertexPolygon(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9	g_pTexturePolygon = NULL;		// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPolygon = NULL;	//頂点バッファのポインタ
Mine mine;

int g_nCounterEnemyAnim;	//アニメーション用
int g_nPattenEnemyAnim;		//アニメーション用
int InvisibleCount;			//自キャラを点滅させるよう
int PlayerMoveKey;			//どの方向に動かすかの変数
int SpawnCount;				//復活用
bool SpawnFlag;				//復活用
bool KeyFlag;				//自キャラを動かすか動かさないかのフラグ

//=============================================================================
// 初期化処理
//=============================================================================
void InitPolygon(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//初期設定
	mine.pos = D3DXVECTOR3(0, 0, 0);
	mine.rot = D3DXVECTOR3(0, 0, 0);
	mine.fAngle = atan2f(PLAYER_SIZE_X / 2, PLAYER_SIZE_Y / 2);
	mine.fLength = sqrtf((PLAYER_SIZE_X / 2) * (PLAYER_SIZE_X / 2) + (PLAYER_SIZE_Y / 2) * (PLAYER_SIZE_Y / 2));
	mine.iHP = MAX_LIFE;
	mine.bUse = false;
	mine.bHit = false;
	PlayerMoveKey = 3;
	KeyFlag = true;
	SpawnFlag = true;
	SpawnCount = 0;
	g_nCounterEnemyAnim = 0;
	g_nPattenEnemyAnim = 0;

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffPolygon,
		NULL);

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/playeranim.png", &g_pTexturePolygon);

	//頂点設定
	MakeVertexPolygon(pDevice);

}

//=============================================================================
// 終了処理
//=============================================================================
void UninitPolygon(void)
{
	// 頂点バッファの開放
	if (g_pVtxBuffPolygon != NULL)
	{
		g_pVtxBuffPolygon->Release();
		g_pVtxBuffPolygon = NULL;
	}

	// テクスチャの開放
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
	VERTEX_2D *pVtx;
	D3DXVECTOR3 *ePos[MAX_ENEMY];
	int bCount;

	ePos[0] = GetEnemy();			//敵の位置をとってくる
	ePos[1] = GetChase();			//敵の位置をとってくる
	ePos[2] = GetMoody();			//敵の位置をとってくる
	ePos[3] = GetSilly();			//敵の位置をとってくる
	bCount = GetBulletCount();		//弾の情報をとってくる

	if (SpawnFlag == true || mine.bHit == false) {
		g_nCounterEnemyAnim++;
	}

	//アニメーション処理
	if (g_nCounterEnemyAnim % 6 == 0)
	{
		g_nPattenEnemyAnim = (g_nPattenEnemyAnim + 1) % MAX_PATTERN;
	}

	if (g_nCounterEnemyAnim % 15 == 0) {

		//ロック
		g_pVtxBuffPolygon->Lock(0, 0, (void**)&pVtx, 0);
		// テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(g_nPattenEnemyAnim*(1.0f / MAX_PATTERN) + 1.0f, 0);
		pVtx[1].tex = D3DXVECTOR2(g_nPattenEnemyAnim*(1.0f / MAX_PATTERN) / MAX_PATTERN, 0);
		pVtx[2].tex = D3DXVECTOR2(g_nPattenEnemyAnim*(1.0f / MAX_PATTERN) + 1.0f, 1);
		pVtx[3].tex = D3DXVECTOR2(g_nPattenEnemyAnim*(1.0f / MAX_PATTERN) / MAX_PATTERN, 1);
		//ロック解除
		g_pVtxBuffPolygon->Unlock();

	}

	//TRUEだったら以下の処理を実行
	if (SpawnFlag == TRUE) {
		SetSpawn();		//自キャラを復活させる
		SetUse(true);	//文字を表示させる
	}

	//FALSEだったら以下の処理を実行
	if (SpawnFlag == false) {
		SetUse(false);	//文字を隠す
	}

	for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++) {
		//敵と自キャラがぶつかったときの処理
		if (Collision(*ePos[nCntEnemy], mine.pos, 23, PLAYER_SIZE_Y / 2) && mine.bHit == false && mine.iHP != 0 && mine.bUse == true) {
			mine.bHit = true;
			SetPlayerKey(false);
			SetChaseMoveKey(false);		//敵を動くようにする
			SetAmbushMoveKey(false);	//敵を動くようにする
			SetMoodyMoveKey(false);		//敵を動くようにする
			SetSillyMoveKey(false);		//敵を動くようにする
			SetTimerKey(false);
			SubLife(1);					//ライフを減らす
			ResetChase();
			SetExplosion(mine.pos);
			Play(SOUND_LABEL_SE_EXPLOSION000);
		}
	}

	//自分のHPが0の場合
	if (mine.iHP == 0) {
		KeyFlag = false;
		SetFade(MODE_RESULT);
	}

	//bHit(ぶつかったとき)がtrueだった場合の処理
	if (mine.bHit == true) {
		InvisiblePlayer();
	}

	//これがtrueの時に移動するようになる
	if (KeyFlag == true) {

		//	上移動
		if (GetKeyboardPress(DIK_UP)) {
			PlayerMoveKey = 1;
		}

		//	下移動
		else if (GetKeyboardPress(DIK_DOWN)) {
			PlayerMoveKey = 2;
		}

		//	左移動
		else if (GetKeyboardPress(DIK_LEFT)) {
			PlayerMoveKey = 3;
		}

		//	右移動
		else if (GetKeyboardPress(DIK_RIGHT)) {
			PlayerMoveKey = 4;
		}


		//プレイヤーの移動処理
		//上方向に移動
		if (PlayerMoveKey == 1) {
			mine.pos.y -= MAX_SPEED;
			//ロック
			g_pVtxBuffPolygon->Lock(0, 0, (void**)&pVtx, 0);
			pVtx[3].tex = D3DXVECTOR2(g_nPattenEnemyAnim*(1.0f / MAX_PATTERN), 0);
			pVtx[2].tex = D3DXVECTOR2(g_nPattenEnemyAnim*(1.0f / MAX_PATTERN), 1);
			pVtx[1].tex = D3DXVECTOR2(g_nPattenEnemyAnim*(1.0f / MAX_PATTERN) + 1.0f / MAX_PATTERN, 0);
			pVtx[0].tex = D3DXVECTOR2(g_nPattenEnemyAnim*(1.0f / MAX_PATTERN) + 1.0f / MAX_PATTERN, 1);
			//ロック解除
			g_pVtxBuffPolygon->Unlock();
			if (GetKeyboardTrigger(DIK_SPACE)) {
				if (bCount != 0) {
					SetBullet(mine.pos, D3DXVECTOR3(0, -7, 0), 80);
					SubBulletCount(1);
				}
			}
		}

		//下方向に移動
		else if (PlayerMoveKey == 2) {
			mine.pos.y += MAX_SPEED;
			//ロック
			g_pVtxBuffPolygon->Lock(0, 0, (void**)&pVtx, 0);
			pVtx[0].tex = D3DXVECTOR2(g_nPattenEnemyAnim*(1.0f / MAX_PATTERN), 0);
			pVtx[1].tex = D3DXVECTOR2(g_nPattenEnemyAnim*(1.0f / MAX_PATTERN), 1);
			pVtx[2].tex = D3DXVECTOR2(g_nPattenEnemyAnim*(1.0f / MAX_PATTERN) + 1.0f / MAX_PATTERN, 0);
			pVtx[3].tex = D3DXVECTOR2(g_nPattenEnemyAnim*(1.0f / MAX_PATTERN) + 1.0f / MAX_PATTERN, 1);
			//ロック解除
			g_pVtxBuffPolygon->Unlock();
			if (GetKeyboardTrigger(DIK_SPACE)) {
				if (bCount != 0) {
					SetBullet(mine.pos, D3DXVECTOR3(0, 7, 0), 80);
					SubBulletCount(1);
				}
			}
		}

		//左に移動
		else if (PlayerMoveKey == 3) {
			mine.pos.x -= MAX_SPEED;
			//ロック
			g_pVtxBuffPolygon->Lock(0, 0, (void**)&pVtx, 0);
			pVtx[0].tex = D3DXVECTOR2(g_nPattenEnemyAnim*(1.0f / MAX_PATTERN) + 1.0f / MAX_PATTERN, 0);
			pVtx[1].tex = D3DXVECTOR2(g_nPattenEnemyAnim*(1.0f / MAX_PATTERN), 0);
			pVtx[2].tex = D3DXVECTOR2(g_nPattenEnemyAnim*(1.0f / MAX_PATTERN) + 1.0f / MAX_PATTERN, 1);
			pVtx[3].tex = D3DXVECTOR2(g_nPattenEnemyAnim*(1.0f / MAX_PATTERN), 1);
			//ロック解除
			g_pVtxBuffPolygon->Unlock();
			if (GetKeyboardTrigger(DIK_SPACE)) {
				if (bCount != 0) {
					SetBullet(mine.pos, D3DXVECTOR3(-7, 0, 0), 80);
					SubBulletCount(1);
				}
			}
		}

		//右に移動
		else if (PlayerMoveKey == 4) {
			mine.pos.x += MAX_SPEED;
			//ロック
			g_pVtxBuffPolygon->Lock(0, 0, (void**)&pVtx, 0);
			pVtx[0].tex = D3DXVECTOR2(g_nPattenEnemyAnim*(1.0f / MAX_PATTERN), 0);
			pVtx[2].tex = D3DXVECTOR2(g_nPattenEnemyAnim*(1.0f / MAX_PATTERN), 1);
			pVtx[1].tex = D3DXVECTOR2(g_nPattenEnemyAnim*(1.0f / MAX_PATTERN) + 1.0f / MAX_PATTERN, 0);
			pVtx[3].tex = D3DXVECTOR2(g_nPattenEnemyAnim*(1.0f / MAX_PATTERN) + 1.0f / MAX_PATTERN, 1);
			//ロック解除
			g_pVtxBuffPolygon->Unlock();
			if (GetKeyboardTrigger(DIK_SPACE)) {
				if (bCount != 0) {
					SetBullet(mine.pos, D3DXVECTOR3(7, 0, 0), 80);
					SubBulletCount(1);
				}
			}
		}

		PrintDebug("\n");
		PrintDebug("ジャンキーの情報\n");
		PrintDebug("Player Position(X:%f,Y:%f,Z:%f)\n", mine.pos.x, mine.pos.y, mine.pos.z);
		PrintDebug("Player Rotation(X:%f,Y:%f,Z:%f)\n", mine.rot.x, mine.rot.y, mine.rot.z);
		PrintDebug("\n");

	}

	{

		//ロック
		g_pVtxBuffPolygon->Lock(0, 0, (void**)&pVtx, 0);

		//頂点座標の設定
		pVtx[0].pos.x = mine.pos.x - sinf(mine.fAngle - mine.rot.z)*mine.fLength;
		pVtx[0].pos.y = mine.pos.y - cosf(mine.fAngle - mine.rot.z)*mine.fLength;
		pVtx[0].pos.z = 0.0f;

		pVtx[1].pos.x = mine.pos.x + sinf(mine.fAngle + mine.rot.z)*mine.fLength;
		pVtx[1].pos.y = mine.pos.y - cosf(mine.fAngle + mine.rot.z)*mine.fLength;
		pVtx[1].pos.z = 0.0f;

		pVtx[2].pos.x = mine.pos.x - sinf(mine.fAngle + mine.rot.z)*mine.fLength;
		pVtx[2].pos.y = mine.pos.y + cosf(mine.fAngle + mine.rot.z)*mine.fLength;
		pVtx[2].pos.z = 0.0f;

		pVtx[3].pos.x = mine.pos.x + sinf(mine.fAngle - mine.rot.z)*mine.fLength;
		pVtx[3].pos.y = mine.pos.y + cosf(mine.fAngle - mine.rot.z)*mine.fLength;
		pVtx[3].pos.z = 0.0f;

		//ロック解除
		g_pVtxBuffPolygon->Unlock();

	}

}

//=============================================================================
// 描画処理
//=============================================================================
void DrawPolygon(void)
{
	if (!mine.bUse)
		return;
	//デバイスを取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//データストリームにセット
	pDevice->SetStreamSource(0, g_pVtxBuffPolygon, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, g_pTexturePolygon);

	// ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

}

//=============================================================================
// 頂点情報の作成
//=============================================================================
void MakeVertexPolygon(LPDIRECT3DDEVICE9 pDevice)
{

	VERTEX_2D *pVtx;

	//ロック
	g_pVtxBuffPolygon->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点座標の設定
	pVtx[0].pos.x = mine.pos.x - sinf(mine.fAngle - mine.rot.z)*mine.fLength;
	pVtx[0].pos.y = mine.pos.y - cosf(mine.fAngle - mine.rot.z)*mine.fLength;
	pVtx[0].pos.z = 0.0f;

	pVtx[1].pos.x = mine.pos.x + sinf(mine.fAngle + mine.rot.z)*mine.fLength;
	pVtx[1].pos.y = mine.pos.y - cosf(mine.fAngle + mine.rot.z)*mine.fLength;
	pVtx[1].pos.z = 0.0f;

	pVtx[2].pos.x = mine.pos.x - sinf(-mine.fAngle + mine.rot.z)*mine.fLength;
	pVtx[2].pos.y = mine.pos.y - cosf(-mine.fAngle + mine.rot.z)*mine.fLength;
	pVtx[2].pos.z = 0.0f;

	pVtx[3].pos.x = mine.pos.x + sinf(mine.fAngle - mine.rot.z)*mine.fLength;
	pVtx[3].pos.y = mine.pos.y + cosf(mine.fAngle - mine.rot.z)*mine.fLength;
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
	pVtx[0].tex = D3DXVECTOR2(g_nPattenEnemyAnim*(1.0f / MAX_PATTERN) + 1.0f / MAX_PATTERN, 0);
	pVtx[1].tex = D3DXVECTOR2(g_nPattenEnemyAnim*(1.0f / MAX_PATTERN), 0);
	pVtx[2].tex = D3DXVECTOR2(g_nPattenEnemyAnim*(1.0f / MAX_PATTERN) + 1.0f / MAX_PATTERN, 1);
	pVtx[3].tex = D3DXVECTOR2(g_nPattenEnemyAnim*(1.0f / MAX_PATTERN), 1);

	//ロック解除
	g_pVtxBuffPolygon->Unlock();

}

D3DXVECTOR3 GetMinePos(void) {
	return mine.pos;
}

//自キャラをチカチカさせる処理
void InvisiblePlayer(void) {

	if (mine.bUse && InvisibleCount % 5 == 0) {
		mine.bUse = false;
	}
	else if (!mine.bUse && InvisibleCount % 5 == 0) {
		mine.bUse = true;
	}
	InvisibleCount++;
	if (InvisibleCount == 60)
	{
		InvisibleCount = 0;
		mine.bHit = false;
		mine.bUse = false;
		SpawnFlag = TRUE;
	}
}

void SetPlayer(D3DXVECTOR3 pos) {

	if (mine.bUse == false)
	{
		mine.pos = pos;
		mine.bUse = true;
	}
}

void SetSpawn(void) {

	D3DXVECTOR3 *ePos[MAX_ENEMY];	//敵の情報用
	VERTEX_2D *pVtx;
	mine.bUse = true;
	ePos[0] = GetEnemy();
	ePos[1] = GetChase();
	ePos[2] = GetMoody();
	ePos[3] = GetSilly();
	mine.pos = D3DXVECTOR3(1190.0f, 100.0f, 0.0f);
	ePos[0]->x = 590;
	ePos[0]->y = 350;
	ePos[1]->x = 690;
	ePos[1]->y = 350;
	ePos[2]->x = 590;
	ePos[2]->y = 400;
	ePos[3]->x = 690;
	ePos[3]->y = 400;

	SpawnCount++;

	//ロック
	g_pVtxBuffPolygon->Lock(0, 0, (void**)&pVtx, 0);
	//テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(g_nPattenEnemyAnim*(1.0f / MAX_PATTERN) + 1.0f / MAX_PATTERN, 0);
	pVtx[1].tex = D3DXVECTOR2(g_nPattenEnemyAnim*(1.0f / MAX_PATTERN), 0);
	pVtx[2].tex = D3DXVECTOR2(g_nPattenEnemyAnim*(1.0f / MAX_PATTERN) + 1.0f / MAX_PATTERN, 1);
	pVtx[3].tex = D3DXVECTOR2(g_nPattenEnemyAnim*(1.0f / MAX_PATTERN), 1);
	//ロック解除
	g_pVtxBuffPolygon->Unlock();

	if (SpawnCount == 120) {
		KeyFlag = 1;
		Reset();
		SetAmbushMoveKey(TRUE);		//敵を動くようにする
		SetChaseMoveKey(TRUE);		//敵を動くようにする
		SetMoodyMoveKey(TRUE);		//敵を動くようにする
		SetSillyMoveKey(TRUE);		//敵を動くようにする
		SetTimerKey(true);
		SpawnFlag = false;
		SpawnCount = 0;
	}
}

void SetPosition(D3DXVECTOR3 pos) {
	mine.pos = pos;
}

int GetKey(void) {
	return PlayerMoveKey;
}

int GetPlayerHP(void) {
	return 	mine.iHP;
}

void SubLife(int Life) {
	mine.iHP -= Life;
}

void SetPlayerKey(bool key) {
	KeyFlag = key;
}