#pragma once
//=============================================================================
//
// �e���̕`�揈�� [BulletCounter.h]
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

}Counter;

//�v���g�^�C�v�錾
void InitBulletCounter(void);
void UninitBulletCounter(void);
void UpdateBulletCounter(void);
void DrawBulletCounter(void);
void SetBulletCounter(D3DXVECTOR3 pos);
