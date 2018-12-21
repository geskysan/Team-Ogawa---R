//=============================================================================
//
// テクスチャ付きポリゴン描画処理 [Enemy.h]
// Author : AKIRA TANAKA
//
//=============================================================================
#ifndef _ENEMY_H_
#define _ENEMY_H_

#include"main.h"

//敵の構造体
typedef struct
{
	D3DXVECTOR3 pos;	//位置
	int nType;			//種類
	bool bUse;			//使用しているかどうか
}Enemy;

//プロトタイプ宣言
void InitEnemy(void);
void UninitEnemy(void);
void UpdateEnemy(void);
void DrawEnemy(void);
void SetEnemy(D3DXVECTOR3 pos, int nType);
int GetEnemyCount(void);
void EnemyTotal(void);
Enemy *GetEnemy(void);

#endif