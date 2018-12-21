#pragma once
//=============================================================================
//
// リザルトの各スコア処理（描画も含む）[ResultScore.h]
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

}ResultScore;

//プロトタイプ宣言
void InitResultScore(void);				//	初期化処理
void UninitResultScore(void);			//	
void UpdateResultScore(void);			//	更新処理
void DrawResultScore(void);				//	描画処理