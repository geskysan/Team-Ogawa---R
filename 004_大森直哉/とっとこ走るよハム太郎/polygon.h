//=============================================================================
//
// �|���S������ [polygon.h]
// Author : AKIRA TANAKA
//
//=============================================================================
#ifndef _POLYGON_H_
#define _POLYGON_H_

#include "main.h"

typedef struct {

	D3DXVECTOR3 g_posPolygon;	//�ʒu
	D3DXVECTOR3 g_rotPolygon;	//����
	float g_fLengthPolygon;		//�Ίp���̒���
	float g_fAnglePolygon;		//�Ίp���̊p�x
	int PlayerHP;				//���@��HP
	bool bUse;					//�g�p���Ă��邩�ǂ���
	bool bHit;					//�`�J�`�J���ɓ����邩������Ȃ���
}Mine;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitPolygon(void);
void UninitPolygon(void);
void UpdatePolygon(void);
void DrawPolygon(void);
void SubLife(int);
void InvisiblePlayer(void);
D3DXVECTOR3 GetMinePos(void);
int GetPlayerHP(void);
Mine *GetMine(void);
#endif
