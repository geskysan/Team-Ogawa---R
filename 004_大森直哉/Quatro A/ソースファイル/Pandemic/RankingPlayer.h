#pragma once
//=============================================================================
//
// �����L���O�v���C���[(�ł����ق��j���� [RankingPlayer.h]
// Author : NAOYA OMORI
//
//=============================================================================

#include "main.h"

typedef struct {

	D3DXVECTOR3 pos;	//�ʒu
	D3DXVECTOR3 rot;	//����
	float fLength;		//�Ίp���̒���
	float fAngle;		//�Ίp���̊p�x
	bool bUse;					//�g�p���Ă��邩�ǂ���
}RankingPlayer;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitRankingPlayer(void);
void UninitRankingPlayer(void);
void UpdateRankingPlayer(void);
void DrawRankingPlayer(void);