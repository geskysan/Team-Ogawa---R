//=============================================================================
//
// テクスチャ付きポリゴン描画処理 [number.h]
// Author : AKIRA TANAKA
//
//=============================================================================
#ifndef _NUMBER_H_
#define _NUMBER_H_

#include "main.h"

//敵の構造体
typedef struct
{
	D3DXVECTOR3 pos;	//位置
	int nType;			//種類
	bool bUse;			//使用しているかどうか

	int g_nCounterAnim = 0;
	int g_nPatternAnim = 0;
	D3DXVECTOR3 g_posNumber;//位置
	D3DXVECTOR3 g_rotNumber;//
	float g_fLengthNumber;//対角線の長さ
	float g_fAngleNumber;//対角線の角度

}Number;

//プロトタイプ宣言
void InitNumber(void);
void UninitNumber(void);
void UpdateNumber(void);
void DrawNumber(void);
void SetNumber(D3DXVECTOR3 pos);

int GetNumber(void);

#endif