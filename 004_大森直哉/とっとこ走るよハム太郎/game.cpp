//=============================================================================
//
// ポリゴン処理 [polygon.cpp]
// Author : AKIRA TANAKA
//
//=============================================================================
#include "main.h"
#include "input.h"
#include "polygon.h"
#include "back.h"
#include "bullet.h"
#include "Enemy.h"
#include "Explosion.h"
#include "title.h"
#include "result.h"
#include "game.h"
#include "fade.h"
#include "life.h"
#include "number.h"
#include "timer.h"
#include "EnemyBullet.h"
//=============================================================================
// 初期化処理
//=============================================================================
void InitGame(void)
{
	InitBack();
	InitPolygon();
	InitBullet();
	InitEnemy();
	InitExplosion();
	InitLife();
	InitNumber();
	InitTimer();
	InitEnemyBullet();
}
//=============================================================================
// 終了処理
//=============================================================================
void UninitGame(void)
{
	// ポリゴンの終了処理
	UninitBack();
	UninitPolygon();
	UninitBullet();
	UninitEnemy();
	UninitExplosion();
	UninitLife();
	UninitNumber();
	UninitTimer();
	UninitEnemyBullet();
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateGame(void)
{
	// ポリゴン処理の更新
	UpdatePolygon();
	UpdateKeyboard();
	UpdateBullet();
	UpdateEnemy();
	UpdateExplosion();
	UpdateLife();
	UpdateNumber();
	UpdateTimer();
	UpdateEnemyBullet();

	if (GetEnemyCount() == 0 && GetFade() == FADE_NONE) {
		SetFade(MODE_CLEAR);
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawGame(void)
{
		DrawBack();
		DrawPolygon();
		DrawBullet();
		DrawEnemy();
		DrawExplosion();
		DrawLife();
		DrawNumber();
		DrawTimer();
		DrawEnemyBullet();
}
