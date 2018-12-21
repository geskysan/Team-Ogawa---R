#pragma once
//=============================================================================
//
// �|���S������ [ball.h]
// Author : NAOYA OMORI
//
//=============================================================================

#include "main.h"

typedef struct {
	D3DXVECTOR3 pos;			//�ʒu���
	D3DXVECTOR3 rot;			//��]���
	float fLengthBall;			//�Ίp���̒���
	float fAngleBall;			//�Ίp���̊p�x
	bool bUse;					//�g�p���Ă��邩�ǂ���
}BALL;

//*****************************************************************************
// �v���g�^�C�v�錾
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