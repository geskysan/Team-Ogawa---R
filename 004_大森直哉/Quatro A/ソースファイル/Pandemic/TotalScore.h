#pragma once
//=============================================================================
//
// 最終スコア処理 [TotalScore.h]
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

}TotalScore;

//プロトタイプ宣言
void InitTotalScore(void);
void UninitTotalScore(void);
void UpdateTotalScore(void);
void DrawTotalScore(void);
void SetTotalScore(D3DXVECTOR3 pos);
