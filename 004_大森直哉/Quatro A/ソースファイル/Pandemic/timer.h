#pragma once
//=============================================================================
//
// �������Ԃ̏��� [timer.h]
// Author : NAOYA OMORI
//
//=============================================================================

#include "main.h"

//�G�̍\����
typedef struct
{
	D3DXVECTOR3 pos;				//�ʒu
	int nType;						//���
	bool bUse;						//�g�p���Ă��邩�ǂ���
	int g_nCounterAnim = 0;
	int g_nPatternAnim = 0;
	D3DXVECTOR3 g_posNumber;		//�ʒu
	D3DXVECTOR3 g_rotNumber;		//��]
	float g_fLengthNumber;			//�Ίp���̒���
	float g_fAngleNumber;			//�Ίp���̊p�x

}Timer;

//�v���g�^�C�v�錾
void InitTimer(void);
void UninitTimer(void);
void UpdateTimer(void);
void DrawTimer(void);
void SetTimer(D3DXVECTOR3 pos);
void SetTimerKey(bool key);
int GetTime(void);
