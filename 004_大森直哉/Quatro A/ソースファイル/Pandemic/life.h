#pragma once
//=============================================================================
//
// 弾の処理 [life.h]
// Author : NAOYA OMORI
//
//=============================================================================

#include "main.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MAX_LIFE (3)


//敵の構造体
typedef struct
{
	D3DXVECTOR3 pos;	//位置
	bool bUse;			//使用しているかどうか

}Life;

//プロトタイプ宣言
void InitLife(void);
void UninitLife(void);
void UpdateLife(void);
void DrawLife(void);
void SetLife(D3DXVECTOR3 pos);