#pragma once
//=============================================================================
//
// �����L���O�����i�`����܂ށj[RankingScore.h]
// Author : NAOYA OMORI
//
//=============================================================================
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
void RankingRecord(void);