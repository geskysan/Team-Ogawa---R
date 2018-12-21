//=============================================================================
//
// 弾の処理 [Explosion.h]
// Author : 
//
//=============================================================================
#ifndef _EXPLOSION_H_
#define _EXPLOSION_H_
//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include "main.h"

void InitExplosion(void);
void UninitExplosion(void);
void UpdateExplosion(void);
void DrawExplosion(void);
void SetExplosion(D3DXVECTOR3 pos);

//敵の構造体
typedef struct
{
	D3DXVECTOR3 pos;
	D3DXCOLOR col;
	int nCounterAnim;
	int nPatternAnim;
	bool bUse;
}Explosion;

#endif
