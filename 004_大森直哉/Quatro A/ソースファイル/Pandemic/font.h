#pragma once
//=============================================================================
//
// フォント処理 [Font.h]
// Author : NAOYA OMORI
//
//=============================================================================
#include"main.h"

#define MAX_FONT (5)

//敵の構造体
typedef struct
{
	D3DXVECTOR3 pos;	//位置
	D3DXVECTOR3 rot;			//回転情報
	float fLengthFont;			//対角線の長さ
	float fAngleFont;			//対角線の角度
	int nType;			//種類
	bool bUse;			//使用しているかどうか
}Font;

//プロトタイプ宣言
void InitFont(void);
void UninitFont(void);
void UpdateFont(void);
void DrawFont(void);
void SetFont(D3DXVECTOR3 pos, int nType);
void SetUse(bool use);