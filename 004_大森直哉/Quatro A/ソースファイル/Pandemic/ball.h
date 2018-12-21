#pragma once
//=============================================================================
//
// ポリゴン処理 [ball.h]
// Author : NAOYA OMORI
//
//=============================================================================

#include "main.h"

typedef struct {
	D3DXVECTOR3 pos;			//位置情報
	D3DXVECTOR3 rot;			//回転情報
	float fLengthBall;			//対角線の長さ
	float fAngleBall;			//対角線の角度
	bool bUse;					//使用しているかどうか
}BALL;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitBall(void);
void UninitBall(void);
void UpdateBall(void);
void DrawBall(void);
void SetBall(D3DXVECTOR3 pos);
bool Collision(D3DXVECTOR3 C1, D3DXVECTOR3 C2, float R1, float R2);
int GetBallCount(void);
void BallTotal(void);
int GetScore(void);
int GetBulletCount(void);
void SubBulletCount(int number);