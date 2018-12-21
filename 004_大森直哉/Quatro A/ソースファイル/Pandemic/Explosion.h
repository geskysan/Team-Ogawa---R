#pragma once
//=============================================================================
//
// 爆発アニメーション処理 [Explosion.h]
// Author : NAOYA OMORI
//
//=============================================================================

//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include "main.h"

//敵の構造体
typedef struct
{
	D3DXVECTOR3 pos;
	D3DXCOLOR col;
	int nCounterAnim;
	int nPatternAnim;
	bool bUse;
}Explosion;

void InitExplosion(void);
void UninitExplosion(void);
void UpdateExplosion(void);
void DrawExplosion(void);
void SetExplosion(D3DXVECTOR3 pos);