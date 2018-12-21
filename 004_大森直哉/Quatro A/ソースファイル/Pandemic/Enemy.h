#pragma once
//=============================================================================
//
// 弾の処理 [Enemy.h]
// Author : NAOYA OMORI
//
//=============================================================================

#include"main.h"

#define MAX_ENEMY (4)
#define MOVE_SPEED (2.0f)

typedef enum {
	UP = 0,
	DOWN,
	RIGHT,
	LEFT
}ENEMY_MOVE_STATE;

//敵の構造体
typedef struct
{
	D3DXVECTOR3 pos;			//位置
	D3DXVECTOR3 rot;			//回転情報
	float fRadius;
	float fLengthEnemy;			//対角線の長さ
	float fAngleEnemy;			//対角線の角度
	int nType;					//種類
	bool bUse;					//使用しているかどうか
	bool bHit;					//あたっているかどうか
}Enemy;

//プロトタイプ宣言
void InitEnemy(void);
void UninitEnemy(void);
void UpdateEnemy(void);
void DrawEnemy(void);
void MoveAmbush(void);
void MoveChase(void);
void MoveMoody(void);
void MoveSilly(void);
void SetEnemy(D3DXVECTOR3 pos, int nType);
void SetAmbushPosition(D3DXVECTOR3 pos);
void SetEnemyPos(D3DXVECTOR3 pos);
void SetAmbushMoveKey(bool key);
void SetChaseMoveKey(bool key);
void SetMoodyMoveKey(bool key);
void SetSillyMoveKey(bool key);
void SetAmbushHitKey(bool hit);
void SetMoodyHitKey(bool hit);
void SetSillyHitKey(bool hit);
void SetChaseHitKey(bool hit);
void ResetChase(void);
void InvisibleAmbush(void);
void InvisibleChase(void);
void InvisibleMoody(void);
void InvisibleSilly(void);
void Reset(void);
D3DXVECTOR3 *GetEnemy(void);
D3DXVECTOR3 *GetChase(void);
D3DXVECTOR3 *GetMoody(void);
D3DXVECTOR3 *GetSilly(void);
D3DXVECTOR3 GetEnemyPos(void);
float GetEnemyRadius(void);