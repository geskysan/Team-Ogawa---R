#pragma once
//=============================================================================
//
// ポリゴン処理 [PressEnter.h]
// Author : NAOYA OMORI
//
//=============================================================================

#include "main.h"

typedef struct {

	D3DXVECTOR3 pos;	//位置
	D3DXVECTOR3 rot;	//向き
	float fLength;		//対角線の長さ
	float fAngle;		//対角線の角度
	int iHP;			//自機のHP
	bool bUse;			//使用しているかどうか
}Enter;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitPressEnter(void);
void UninitPressEnter(void);
void UpdatePressEnter(void);
void DrawPressEnter(void);
void SetEnterPosition(D3DXVECTOR3 pos);