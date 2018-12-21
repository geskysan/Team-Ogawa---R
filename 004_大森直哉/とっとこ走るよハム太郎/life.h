//=============================================================================
//
// �e�N�X�`���t���|���S���`�揈�� [Enemy.h]
// Author : AKIRA TANAKA
//
//=============================================================================
#ifndef _LIFE_H_
#define _LIFE_H_

#include "main.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAX_LIFE	(5)


//�G�̍\����
typedef struct
{
	D3DXVECTOR3 pos;	//�ʒu
	int nType;			//���
	bool bUse;			//�g�p���Ă��邩�ǂ���

}Life;

//�v���g�^�C�v�錾
void InitLife(void);
void UninitLife(void);
void UpdateLife(void);
void DrawLife(void);
void SetLife(D3DXVECTOR3 pos);

#endif