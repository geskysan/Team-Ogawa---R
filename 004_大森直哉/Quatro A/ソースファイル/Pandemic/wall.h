#pragma once
//=============================================================================
//
// �ǂ̏��� [wall.h]
// Author : NAOYA OMORI
//
//=============================================================================

#include "main.h"

#define MAX_WALL (220)

typedef struct {
	D3DXVECTOR3 pos;			//�ʒu���
	D3DXVECTOR3 rot;	//����
	float fLengthWall;		//�Ίp���̒���
	float fAngleWall;		//�Ίp���̊p�x
	bool bUse;					//�g�p���Ă��邩�ǂ���
}WALL;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitWall(void);
void UninitWall(void);
void UpdateWall(void);
void DrawWall(void);
void SetWall(D3DXVECTOR3 pos);
bool GetWallContactFlag(void);
bool Wallcollision(D3DXVECTOR3 pos);
WALL *GetWall(void);