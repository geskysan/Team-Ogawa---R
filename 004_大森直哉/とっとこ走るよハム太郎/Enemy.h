//=============================================================================
//
// �e�N�X�`���t���|���S���`�揈�� [Enemy.h]
// Author : AKIRA TANAKA
//
//=============================================================================
#ifndef _ENEMY_H_
#define _ENEMY_H_

#include"main.h"

//�G�̍\����
typedef struct
{
	D3DXVECTOR3 pos;	//�ʒu
	int nType;			//���
	bool bUse;			//�g�p���Ă��邩�ǂ���
}Enemy;

//�v���g�^�C�v�錾
void InitEnemy(void);
void UninitEnemy(void);
void UpdateEnemy(void);
void DrawEnemy(void);
void SetEnemy(D3DXVECTOR3 pos, int nType);
int GetEnemyCount(void);
void EnemyTotal(void);
Enemy *GetEnemy(void);

#endif