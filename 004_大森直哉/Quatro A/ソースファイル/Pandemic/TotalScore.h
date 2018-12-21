#pragma once
//=============================================================================
//
// �ŏI�X�R�A���� [TotalScore.h]
// Author : NAOYA OMORI
//
//=============================================================================

#include "main.h"

//�G�̍\����
typedef struct
{
	D3DXVECTOR3 pos;	//�ʒu
	int nType;			//���
	bool bUse;			//�g�p���Ă��邩�ǂ���
	int nCounterAnim = 0;
	int nPatternAnim = 0;
	D3DXVECTOR3 posNumber;//�ʒu
	D3DXVECTOR3 rotNumber;//
	float fLengthNumber;//�Ίp���̒���
	float fAngleNumber;//�Ίp���̊p�x

}TotalScore;

//�v���g�^�C�v�錾
void InitTotalScore(void);
void UninitTotalScore(void);
void UpdateTotalScore(void);
void DrawTotalScore(void);
void SetTotalScore(D3DXVECTOR3 pos);
