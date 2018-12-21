#pragma once
//=============================================================================
//
// �e�̏��� [Enemy.h]
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

//�G�̍\����
typedef struct
{
	D3DXVECTOR3 pos;			//�ʒu
	D3DXVECTOR3 rot;			//��]���
	float fRadius;
	float fLengthEnemy;			//�Ίp���̒���
	float fAngleEnemy;			//�Ίp���̊p�x
	int nType;					//���
	bool bUse;					//�g�p���Ă��邩�ǂ���
	bool bHit;					//�������Ă��邩�ǂ���
}Enemy;

//�v���g�^�C�v�錾
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