#pragma once
//=============================================================================
//
// ランキング処理（描画も含む）[RankingScore.h]
// Author : NAOYA OMORI
//
//=============================================================================
#include "main.h"

//敵の構造体
typedef struct
{
	D3DXVECTOR3 pos;		//	位置
	D3DXVECTOR3 rot;		//	回転
	bool bUse;							//	使用しているかどうか

}RankingScore;

//プロトタイプ宣言
void InitRankingScore(void);			//	初期化処理
void UninitRankingScore(void);			//	
void UpdateRankingScore(void);			//	更新処理
void DrawRankingScore(void);			//	描画処理
void RankingRecord(void);