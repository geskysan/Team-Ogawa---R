#pragma once
//=============================================================================
//
// ���U���g�̊e�X�R�A�����i�`����܂ށj[ResultScore.h]
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

}ResultScore;

//�v���g�^�C�v�錾
void InitResultScore(void);				//	����������
void UninitResultScore(void);			//	
void UpdateResultScore(void);			//	�X�V����
void DrawResultScore(void);				//	�`�揈��