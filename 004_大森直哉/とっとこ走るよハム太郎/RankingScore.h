//=============================================================================
//
// �e�N�X�`���t���|���S���`�揈�� [RankingScore.h]
// Author : AKIRA TANAKA
//
//=============================================================================
#ifndef _RANKINGSCORE_H_
#define _RANKINGSCORE_H_

#include "main.h"

//�G�̍\����
typedef struct
{
	D3DXVECTOR3 pos;		//	�ʒu
	D3DXVECTOR3 rot;		//	��]
	bool bUse;							//	�g�p���Ă��邩�ǂ���

}RankingScore;

//�v���g�^�C�v�錾
void InitRankingScore(void);			//	����������
void UninitRankingScore(void);			//	
void UpdateRankingScore(void);			//	�X�V����
void DrawRankingScore(void);			//	�`�揈��
#endif