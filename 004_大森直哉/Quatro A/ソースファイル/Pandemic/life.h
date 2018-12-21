#pragma once
//=============================================================================
//
// �e�̏��� [life.h]
// Author : NAOYA OMORI
//
//=============================================================================

#include "main.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAX_LIFE (3)


//�G�̍\����
typedef struct
{
	D3DXVECTOR3 pos;	//�ʒu
	bool bUse;			//�g�p���Ă��邩�ǂ���

}Life;

//�v���g�^�C�v�錾
void InitLife(void);
void UninitLife(void);
void UpdateLife(void);
void DrawLife(void);
void SetLife(D3DXVECTOR3 pos);