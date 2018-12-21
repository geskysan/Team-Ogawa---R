#pragma once
//=============================================================================
//
// 弾数の描画処理 [BulletCounter.h]
// Author : NAOYA OMORI
//
//=============================================================================

#include "main.h"

//敵の構造体
typedef struct
{
	D3DXVECTOR3 pos;	//位置
	int nType;			//種類
	bool bUse;			//使用しているかどうか
	int nCounterAnim = 0;
	int nPatternAnim = 0;
	D3DXVECTOR3 posNumber;//位置
	D3DXVECTOR3 rotNumber;//
	float fLengthNumber;//対角線の長さ
	float fAngleNumber;//対角線の角度

}Counter;

//プロトタイプ宣言
void InitBulletCounter(void);
void UninitBulletCounter(void);
void UpdateBulletCounter(void);
void DrawBulletCounter(void);
void SetBulletCounter(D3DXVECTOR3 pos);
