//=============================================================================
//
// �e�N�X�`���t���|���S���`�揈�� [number.h]
// Author : AKIRA TANAKA
//
//=============================================================================
#ifndef _NUMBER_H_
#define _NUMBER_H_

#include "main.h"

//�G�̍\����
typedef struct
{
	D3DXVECTOR3 pos;	//�ʒu
	int nType;			//���
	bool bUse;			//�g�p���Ă��邩�ǂ���

	int g_nCounterAnim = 0;
	int g_nPatternAnim = 0;
	D3DXVECTOR3 g_posNumber;//�ʒu
	D3DXVECTOR3 g_rotNumber;//
	float g_fLengthNumber;//�Ίp���̒���
	float g_fAngleNumber;//�Ίp���̊p�x

}Number;

//�v���g�^�C�v�錾
void InitNumber(void);
void UninitNumber(void);
void UpdateNumber(void);
void DrawNumber(void);
void SetNumber(D3DXVECTOR3 pos);

int GetNumber(void);

#endif