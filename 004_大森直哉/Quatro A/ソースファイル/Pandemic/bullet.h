#pragma once
//=============================================================================
//
// 弾の処理 [bullet.h]
// Author : NAOYA OMORI
//
//=============================================================================

//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include "main.h"

#define MAX_BULLET	(128)

//弾の構造体
typedef struct
{
	D3DXVECTOR3 pos;	//位置
	D3DXVECTOR3 move;	//移動量
	int nLife;			//寿命
	bool bUse;			//使用しているかどうか
}Bullet;

void InitBullet(void);
void UninitBullet(void);
void UpdateBullet(void);
void DrawBullet(void);
void SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 move, int nLife);
void EnemyHit(void);