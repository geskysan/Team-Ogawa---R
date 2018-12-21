#pragma once
//=============================================================================
//
// セレクトフォントの処理 [Selectfont.h]
// Author :  NAOYA OMORI
//
//=============================================================================

#include"main.h"

#define MAX_SELECTFONT (3)

//セレクトフォントの構造体
typedef struct
{
	D3DXVECTOR3 pos;				//位置
	D3DXVECTOR3 rot;				//回転情報
	float fLengthSelectfont;		//対角線の長さ
	float fAngleSelectfont;			//対角線の角度
	int nType;						//種類
	bool bUse;						//使用しているかどうか

}Selectfont;

//プロトタイプ宣言
void InitSelectfont(void);
void UninitSelectfont(void);
void UpdateSelectfont(void);
void DrawSelectfont(void);
void SetSelectfont(D3DXVECTOR3 pos, int nType);
void MoveFont(int type, float time);