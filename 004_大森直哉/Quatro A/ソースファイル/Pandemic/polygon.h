#pragma once
//=============================================================================
//
// ポリゴン処理 [polygon.h]
// Author : NAOYA OMORI
//
//=============================================================================

#include "main.h"

#define MAX_SPEED (2.0f)

typedef struct {

	D3DXVECTOR3 pos;	//位置
	D3DXVECTOR3 rot;	//向き
	float fLength;		//対角線の長さ
	float fAngle;		//対角線の角度
	int iHP;			//自機のHP
	bool bUse;			//使用しているかどうか
	bool bHit;			//チカチカ中に当たるか当たらないか
}Mine;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitPolygon(void);
void UninitPolygon(void);
void UpdatePolygon(void);
void DrawPolygon(void);
void InvisiblePlayer(void);
D3DXVECTOR3 GetMinePos(void);
void SetPlayer(D3DXVECTOR3 pos);
void SetPosition(D3DXVECTOR3 pos);
int GetKey(void);
void SubLife(int);
int GetPlayerHP(void);
void SetPlayerKey(bool key);
void SetSpawn(void);