#pragma once
//=============================================================================
//
// �^�C�g���Z���N�g�L�������� [TitleArrow.h]
// Author : NAOYA OMORI
//
//=============================================================================

#include "main.h"

#define ARROW_SPEED (250.0f/60.0f)

typedef struct {

	D3DXVECTOR3 pos;	//�ʒu
	D3DXVECTOR3 rot;	//����
	float fLength;		//�Ίp���̒���
	float fAngle;		//�Ίp���̊p�x
}Arrow;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitArrow(void);
void UninitArrow(void);
void UpdateArrow(void);
void DrawArrow(void);