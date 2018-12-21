#pragma once
//=============================================================================
//
// ランキングプレイヤー(でかいほう）処理 [RankingPlayer.h]
// Author : NAOYA OMORI
//
//=============================================================================

#include "main.h"

typedef struct {

	D3DXVECTOR3 pos;	//位置
	D3DXVECTOR3 rot;	//向き
	float fLength;		//対角線の長さ
	float fAngle;		//対角線の角度
	bool bUse;					//使用しているかどうか
}RankingPlayer;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitRankingPlayer(void);
void UninitRankingPlayer(void);
void UpdateRankingPlayer(void);
void DrawRankingPlayer(void);