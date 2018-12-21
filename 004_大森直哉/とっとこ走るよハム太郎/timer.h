//=============================================================================
//
// テクスチャ付きポリゴン描画処理 [number.h]
// Author : AKIRA TANAKA
//
//=============================================================================
#ifndef _TIMER_H_
#define _TIMER_H_

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

}Timer;

//プロトタイプ宣言
void InitTimer(void);
void UninitTimer(void);
void UpdateTimer(void);
void DrawTimer(void);
void SetTimer(D3DXVECTOR3 pos);

#endif