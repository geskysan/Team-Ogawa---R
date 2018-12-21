#pragma once
//=============================================================================
//
// �Q�[�����X�R�A�̕`�� [Number.h]
// Author : NAOYA OMORI
//
//=============================================================================

#include "main.h"

//�G�̍\����
typedef struct
{
	D3DXVECTOR3 pos;			//�ʒu
	int nType;					//���
	bool bUse;					//�g�p���Ă��邩�ǂ���
	int g_nCounterAnim;
	int g_nPatternAnim;
	D3DXVECTOR3 g_posNumber;	//�ʒu
	D3DXVECTOR3 g_rotNumber;	//��]
	float g_fLengthNumber;		//�Ίp���̒���
	float g_fAngleNumber;		//�Ίp���̊p�x

}Number;

//�v���g�^�C�v�錾
void InitNumber(void);
void UninitNumber(void);
void UpdateNumber(void);
void DrawNumber(void);
void SetNumber(D3DXVECTOR3 pos);
int GetNumber(void);