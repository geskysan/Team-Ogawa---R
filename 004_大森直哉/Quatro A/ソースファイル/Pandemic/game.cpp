//=============================================================================
//
// �Q�[����ʏ��� [game.cpp]
// Author : NAOYA OMORI
//
//=============================================================================
#include "main.h"
#include "sound.h"
#include "polygon.h"
#include "back.h"
#include "Explosion.h"
#include "game.h"
#include "fade.h"
#include "DebugProc.h"
#include "bullet.h"
#include "Enemy.h"
#include "wall.h"
#include "map.h"
#include "ball.h"
#include "door.h"
#include "number.h"
#include "life.h"
#include "font.h"
#include "timer.h"
#include "bullet.h"
#include "bulletcounter.h"

//=============================================================================
// ����������
//=============================================================================
void InitGame(void)
{

	InitBack();
	InitBullet();
	InitWall();
	InitDoor();
	InitBall();
	InitEnemy();
	InitPolygon();
	InitMap();
	InitDebug();
	InitNumber();
	InitLife();
	InitFont();
	InitTimer();
	InitExplosion();
	InitBulletCounter();

	Stop(SOUND_LABEL_BGM000);
	Play(SOUND_LABEL_BGM001);

	SetFont(D3DXVECTOR3(100.0f, 12.5f, 0.0f), 0);
	SetFont(D3DXVECTOR3(570.0f, 12.5f, 0.0f), 1);
	SetFont(D3DXVECTOR3(1025.0f, 12.5f, 0.0f), 2);
	SetFont(D3DXVECTOR3(635.0f, 250.0f, 0.0f), 3);
	SetFont(D3DXVECTOR3(350.0f, 12.5f, 0.0f), 4);

}

//=============================================================================
// �I������
//=============================================================================
void UninitGame(void)
{

	UninitBack();
	UninitBullet();
	UninitWall();
	UninitDoor();
	UninitBall();
	UninitEnemy();
	UninitPolygon();
	UninitMap();
	UninitDebug();
	UninitNumber();
	UninitLife();
	UninitFont();
	UninitTimer();
	UninitExplosion();
	UninitBulletCounter();

}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateGame(void)
{
	UpdateBack();
	UpdateBullet();
	UpdateWall();
	UpdateDoor();
	UpdateBall();
	UpdateEnemy();
	UpdatePolygon();
	UpdateMap();
	UpdateLife();
	UpdateFont();
	UpdateNumber();
	UpdateTimer();
	UpdateExplosion();
	UpdateBulletCounter();

	if (GetBallCount() == 0 && GetFade() == FADE_NONE)
	{
		SetAmbushMoveKey(false);
		SetChaseMoveKey(false);
		SetMoodyMoveKey(false);
		SetSillyMoveKey(false);
		SetFade(MODE_CLEAR);
	}

}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawGame(void)
{
	DrawBack();
	DrawBullet();
	DrawWall();
	DrawDoor();
	DrawBall();
	DrawPolygon();
	DrawEnemy();
	DrawMap();
	DrawDebug();
	DrawNumber();
	DrawLife();
	DrawFont();
	DrawTimer();
	DrawExplosion();
	DrawBulletCounter();

}