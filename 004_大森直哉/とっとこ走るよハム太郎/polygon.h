//=============================================================================
//
// ポリゴン処理 [polygon.h]
// Author : AKIRA TANAKA
//
//=============================================================================
#ifndef _POLYGON_H_
#define _POLYGON_H_

#include "main.h"

typedef struct {

	D3DXVECTOR3 g_posPolygon;	//位置
	D3DXVECTOR3 g_rotPolygon;	//向き
	float g_fLengthPolygon;		//対角線の長さ
	float g_fAnglePolygon;		//対角線の角度
	int PlayerHP;				//自機のHP
	bool bUse;					//使用しているかどうか
	bool bHit;					//チカチカ中に当たるか当たらないか
}Mine;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitPolygon(void);
void UninitPolygon(void);
void UpdatePolygon(void);
void DrawPolygon(void);
void SubLife(int);
void InvisiblePlayer(void);
D3DXVECTOR3 GetMinePos(void);
int GetPlayerHP(void);
Mine *GetMine(void);
#endif
