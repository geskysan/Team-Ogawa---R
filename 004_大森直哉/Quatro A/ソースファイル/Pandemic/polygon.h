#pragma once
//=============================================================================
//
// �|���S������ [polygon.h]
// Author : NAOYA OMORI
//
//=============================================================================

#include "main.h"

#define MAX_SPEED (2.0f)

typedef struct {

	D3DXVECTOR3 pos;	//�ʒu
	D3DXVECTOR3 rot;	//����
	float fLength;		//�Ίp���̒���
	float fAngle;		//�Ίp���̊p�x
	int iHP;			//���@��HP
	bool bUse;			//�g�p���Ă��邩�ǂ���
	bool bHit;			//�`�J�`�J���ɓ����邩������Ȃ���
}Mine;

//*****************************************************************************
// �v���g�^�C�v�錾
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