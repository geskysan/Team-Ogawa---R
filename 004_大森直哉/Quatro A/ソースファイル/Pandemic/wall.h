#pragma once
//=============================================================================
//
// 壁の処理 [wall.h]
// Author : NAOYA OMORI
//
//=============================================================================

#include "main.h"

#define MAX_WALL (220)

typedef struct {
	D3DXVECTOR3 pos;			//位置情報
	D3DXVECTOR3 rot;	//向き
	float fLengthWall;		//対角線の長さ
	float fAngleWall;		//対角線の角度
	bool bUse;					//使用しているかどうか
}WALL;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitWall(void);
void UninitWall(void);
void UpdateWall(void);
void DrawWall(void);
void SetWall(D3DXVECTOR3 pos);
bool GetWallContactFlag(void);
bool Wallcollision(D3DXVECTOR3 pos);
WALL *GetWall(void);