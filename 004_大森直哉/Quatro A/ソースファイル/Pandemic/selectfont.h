#pragma once
//=============================================================================
//
// �Z���N�g�t�H���g�̏��� [Selectfont.h]
// Author :  NAOYA OMORI
//
//=============================================================================

#include"main.h"

#define MAX_SELECTFONT (3)

//�Z���N�g�t�H���g�̍\����
typedef struct
{
	D3DXVECTOR3 pos;				//�ʒu
	D3DXVECTOR3 rot;				//��]���
	float fLengthSelectfont;		//�Ίp���̒���
	float fAngleSelectfont;			//�Ίp���̊p�x
	int nType;						//���
	bool bUse;						//�g�p���Ă��邩�ǂ���

}Selectfont;

//�v���g�^�C�v�錾
void InitSelectfont(void);
void UninitSelectfont(void);
void UpdateSelectfont(void);
void DrawSelectfont(void);
void SetSelectfont(D3DXVECTOR3 pos, int nType);
void MoveFont(int type, float time);