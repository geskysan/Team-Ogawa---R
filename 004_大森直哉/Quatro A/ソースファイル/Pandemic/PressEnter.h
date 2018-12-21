#pragma once
//=============================================================================
//
// �|���S������ [PressEnter.h]
// Author : NAOYA OMORI
//
//=============================================================================

#include "main.h"

typedef struct {

	D3DXVECTOR3 pos;	//�ʒu
	D3DXVECTOR3 rot;	//����
	float fLength;		//�Ίp���̒���
	float fAngle;		//�Ίp���̊p�x
	int iHP;			//���@��HP
	bool bUse;			//�g�p���Ă��邩�ǂ���
}Enter;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitPressEnter(void);
void UninitPressEnter(void);
void UpdatePressEnter(void);
void DrawPressEnter(void);
void SetEnterPosition(D3DXVECTOR3 pos);