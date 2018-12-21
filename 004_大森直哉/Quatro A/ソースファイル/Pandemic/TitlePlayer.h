#pragma once
//=============================================================================
//
// �^�C�g���v���C���[�i�ł����ق��j���� [TitlePlayer.h]
// Author : NAOYA OMORI
//
//=============================================================================

#include "main.h"

typedef struct {

	D3DXVECTOR3 pos;	//�ʒu
	D3DXVECTOR3 rot;	//����
	float fLength;		//�Ίp���̒���
	float fAngle;		//�Ίp���̊p�x
	bool bUse;					//�g�p���Ă��邩�ǂ���
}TitlePlayer;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitTitlePlayer(void);
void UninitTitlePlayer(void);
void UpdateTitlePlayer(void);
void DrawTitlePlayer(void);