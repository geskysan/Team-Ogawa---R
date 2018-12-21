#pragma once
//=============================================================================
//
// �Q�[�����I�����̃X�R�A�`�� [EndGameScore.h]
// Author : NAOYA OMORI
//
//=============================================================================

#include "main.h"

//�G�̍\����
typedef struct
{
	D3DXVECTOR3 pos;			//�ʒu
	int nType;					//���
	bool bUse;					//�g�p���Ă��邩�ǂ���
	int g_nCounterAnim;
	int g_nPatternAnim;
	D3DXVECTOR3 g_posEndGameScore;	//�ʒu
	D3DXVECTOR3 g_rotEndGameScore;	//��]
	float g_fLengthEndGameScore;		//�Ίp���̒���
	float g_fAngleEndGameScore;		//�Ίp���̊p�x

}EndGameScore;

//�v���g�^�C�v�錾
void InitEndGameScore(void);
void UninitEndGameScore(void);
void UpdateEndGameScore(void);
void DrawEndGameScore(void);
void SetEndGameScore(D3DXVECTOR3 pos);