#pragma once
//=============================================================================
//
// �e�̏��� [bullet.h]
// Author : NAOYA OMORI
//
//=============================================================================

//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include "main.h"

#define MAX_BULLET	(128)

//�e�̍\����
typedef struct
{
	D3DXVECTOR3 pos;	//�ʒu
	D3DXVECTOR3 move;	//�ړ���
	int nLife;			//����
	bool bUse;			//�g�p���Ă��邩�ǂ���
}Bullet;

void InitBullet(void);
void UninitBullet(void);
void UpdateBullet(void);
void DrawBullet(void);
void SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 move, int nLife);
void EnemyHit(void);