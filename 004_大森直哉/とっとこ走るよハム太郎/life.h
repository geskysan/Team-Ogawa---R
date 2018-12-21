//=============================================================================
//
// テクスチャ付きポリゴン描画処理 [Enemy.h]
// Author : AKIRA TANAKA
//
//=============================================================================
#ifndef _LIFE_H_
#define _LIFE_H_

#include "main.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MAX_LIFE	(5)


//敵の構造体
typedef struct
{
	D3DXVECTOR3 pos;	//位置
	int nType;			//種類
	bool bUse;			//使用しているかどうか

}Life;

//プロトタイプ宣言
void InitLife(void);
void UninitLife(void);
void UpdateLife(void);
void DrawLife(void);
void SetLife(D3DXVECTOR3 pos);

#endif