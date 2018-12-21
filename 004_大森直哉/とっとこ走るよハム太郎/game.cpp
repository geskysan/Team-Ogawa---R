//=============================================================================
//
// �|���S������ [polygon.cpp]
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
// ����������
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
// �I������
//=============================================================================
void UninitGame(void)
{
	// �|���S���̏I������
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
// �X�V����
//=============================================================================
void UpdateGame(void)
{
	// �|���S�������̍X�V
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
// �`�揈��
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
