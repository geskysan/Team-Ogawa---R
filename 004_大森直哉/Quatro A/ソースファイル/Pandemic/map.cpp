//=============================================================================
//
// �}�b�v���� [map.cpp]
// Author : NAOYA OMORI
//
//=============================================================================
#include "map.h"
#include "Enemy.h"
#include "polygon.h"
#include "wall.h"
#include "DebugProc.h"
#include "ball.h"
#include "door.h"

//==============================================================================
//�}�N����`
//==============================================================================

int g_maptype[MAX_OBJ_X][MAX_OBJ_Y];

OBJECT_TYPE objtype;
const char *FileName;


void InitMap() {

	FileName = "test.csv";

	FILE *fp;

	fopen_s(&fp, FileName, "r");

	if (!fp)
	{
		MessageBox(NULL, "�}�b�v�f�[�^���ǂݍ��߂܂���", NULL, MB_OK);
	}

	for (int y = 0; y < MAX_OBJ_Y; y++) {
		for (int x = 0; x < MAX_OBJ_X; x++) {

			fscanf_s(fp, "%d,", &objtype);

			g_maptype[x][y] = objtype;

			switch (objtype) {

			case OBJECTTYPE_NONE:	//�����`�悵�Ȃ�(NONE)
				break;

			case OBJECTTYPE_JUNKIE:
				SetPlayer(D3DXVECTOR3(40.0f + OBJ_SIZE * x, OBJ_SIZE + OBJ_SIZE * y, 0.0f));		//JUNKIE�̕`��(Player)
				break;

			case OBJECTTYPE_AMBUSH:
				SetEnemy(D3DXVECTOR3(40.0f + OBJ_SIZE * x, OBJ_SIZE + OBJ_SIZE * y, 0.0f), 0);		//AMBUSH�̕`��(Enemy)
				break;

			case OBJECTTYPE_CHASE:
				SetEnemy(D3DXVECTOR3(40.0f + OBJ_SIZE * x, OBJ_SIZE + OBJ_SIZE * y, 0.0f), 1);		//CHASE�̕`��(Enemy)
				break;

			case OBJECTTYPE_MOODY:
				SetEnemy(D3DXVECTOR3(40.0f + OBJ_SIZE * x, OBJ_SIZE + OBJ_SIZE * y, 0.0f), 2);		//MOODY�̕`��(Enemy)
				break;

			case OBJECTTYPE_SILLY:
				SetEnemy(D3DXVECTOR3(40.0f + OBJ_SIZE * x, OBJ_SIZE + OBJ_SIZE * y, 0.0f), 3);		//SILLY�̕`��(Enemy)
				break;

			case OBJECTTYPE_WALL:
				SetWall(D3DXVECTOR3(40.0f + OBJ_SIZE * x, OBJ_SIZE + OBJ_SIZE * y, 0.0f));	//�ǂ̕`��(WALL)
				break;

			case OBJECTTYPE_BALL:
				SetBall(D3DXVECTOR3(40.0f + OBJ_SIZE * x, OBJ_SIZE + OBJ_SIZE * y, 0.0f));	//�ʂ̕`��(BALL)
				break;

			case OBJECTTYPE_LINE:
				SetDoor(D3DXVECTOR3(40.0f + OBJ_SIZE * x, 45.0f + OBJ_SIZE * y, 0.0f));	//�h�A�̕`��(DOOR)
				break;

			}
		}
	}
	fclose(fp);	//�t�@�C�������
	fp = NULL;
	return;
}

void UninitMap() {

}

void UpdateMap() {
}

void DrawMap() {

}