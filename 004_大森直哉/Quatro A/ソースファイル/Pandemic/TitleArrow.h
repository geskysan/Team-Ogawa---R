#pragma once
//=============================================================================
//
// タイトルセレクトキャラ処理 [TitleArrow.h]
// Author : NAOYA OMORI
//
//=============================================================================

#include "main.h"

#define ARROW_SPEED (250.0f/60.0f)

typedef struct {

	D3DXVECTOR3 pos;	//位置
	D3DXVECTOR3 rot;	//向き
	float fLength;		//対角線の長さ
	float fAngle;		//対角線の角度
}Arrow;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitArrow(void);
void UninitArrow(void);
void UpdateArrow(void);
void DrawArrow(void);