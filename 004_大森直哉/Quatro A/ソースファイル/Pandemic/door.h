#pragma once
//=============================================================================
//
// �h�A���� [door.h]
// Author : NAOYA OMORI
//
//=============================================================================
#include "main.h"

typedef struct {
	D3DXVECTOR3 pos;			//�ʒu���
	D3DXVECTOR3 rot;	//����
	float fLength;		//�Ίp���̒���
	float fAngle;		//�Ίp���̊p�x
	int nType;			//���
	bool bUse;					//�g�p���Ă��邩�ǂ���
}DOOR;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitDoor(void);
void UninitDoor(void);
void UpdateDoor(void);
void DrawDoor(void);
void SetDoor(D3DXVECTOR3 pos);