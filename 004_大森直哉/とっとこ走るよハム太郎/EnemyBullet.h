//=============================================================================
//
// �e�̏��� [EnemyBullet.h]
// Author : 
//
//=============================================================================
#ifndef _ENEMYBULLET_H_
#define _ENEMYBULLET_H_
//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include "main.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAX_ENEMYBULLET 80

void InitEnemyBullet(void);
void UninitEnemyBullet(void);
void UpdateEnemyBullet(void);
void DrawEnemyBullet(void);
void SetEnemyBullet(D3DXVECTOR3 pos,
	D3DXVECTOR3 move,
	int nLife);

#endif