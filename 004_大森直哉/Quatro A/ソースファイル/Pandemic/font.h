#pragma once
//=============================================================================
//
// �t�H���g���� [Font.h]
// Author : NAOYA OMORI
//
//=============================================================================
#include"main.h"

#define MAX_FONT (5)

//�G�̍\����
typedef struct
{
	D3DXVECTOR3 pos;	//�ʒu
	D3DXVECTOR3 rot;			//��]���
	float fLengthFont;			//�Ίp���̒���
	float fAngleFont;			//�Ίp���̊p�x
	int nType;			//���
	bool bUse;			//�g�p���Ă��邩�ǂ���
}Font;

//�v���g�^�C�v�錾
void InitFont(void);
void UninitFont(void);
void UpdateFont(void);
void DrawFont(void);
void SetFont(D3DXVECTOR3 pos, int nType);
void SetUse(bool use);