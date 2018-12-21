#pragma once
//=============================================================================
//
// ドア処理 [door.h]
// Author : NAOYA OMORI
//
//=============================================================================
#include "main.h"

typedef struct {
	D3DXVECTOR3 pos;			//位置情報
	D3DXVECTOR3 rot;	//向き
	float fLength;		//対角線の長さ
	float fAngle;		//対角線の角度
	int nType;			//種類
	bool bUse;					//使用しているかどうか
}DOOR;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitDoor(void);
void UninitDoor(void);
void UpdateDoor(void);
void DrawDoor(void);
void SetDoor(D3DXVECTOR3 pos);