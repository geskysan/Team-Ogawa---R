#pragma once
//=============================================================================
//
// ゲーム内終了時のスコア描画 [EndGameScore.h]
// Author : NAOYA OMORI
//
//=============================================================================

#include "main.h"

//敵の構造体
typedef struct
{
	D3DXVECTOR3 pos;			//位置
	int nType;					//種類
	bool bUse;					//使用しているかどうか
	int g_nCounterAnim;
	int g_nPatternAnim;
	D3DXVECTOR3 g_posEndGameScore;	//位置
	D3DXVECTOR3 g_rotEndGameScore;	//回転
	float g_fLengthEndGameScore;		//対角線の長さ
	float g_fAngleEndGameScore;		//対角線の角度

}EndGameScore;

//プロトタイプ宣言
void InitEndGameScore(void);
void UninitEndGameScore(void);
void UpdateEndGameScore(void);
void DrawEndGameScore(void);
void SetEndGameScore(D3DXVECTOR3 pos);