//=============================================================================
//
// テクスチャ付きポリゴン描画処理 [RankingScore.h]
// Author : AKIRA TANAKA
//
//=============================================================================
#ifndef _RANKINGSCORE_H_
#define _RANKINGSCORE_H_

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
#endif