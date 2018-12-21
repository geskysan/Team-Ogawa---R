//=============================================================================
//
// 弾の処理 [bullet.h]
// Author : 
//
//=============================================================================
#ifndef _BULLET_H_
#define _BULLET_H_
//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include "main.h"

#define MAX_BULLET	(128)

void InitBullet(void);
void UninitBullet(void);
void UpdateBullet(void);
void DrawBullet(void);
void SetBullet(D3DXVECTOR3 pos,
	D3DXVECTOR3 move,
	int nLife);

int GetScore(void);

bool Collision(D3DXVECTOR3 C1,D3DXVECTOR3 C2,float R1,float R2);

#endif