//=============================================================================
//
// マップ処理 [map.cpp]
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
//マクロ定義
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
		MessageBox(NULL, "マップデータが読み込めません", NULL, MB_OK);
	}

	for (int y = 0; y < MAX_OBJ_Y; y++) {
		for (int x = 0; x < MAX_OBJ_X; x++) {

			fscanf_s(fp, "%d,", &objtype);

			g_maptype[x][y] = objtype;

			switch (objtype) {

			case OBJECTTYPE_NONE:	//何も描画しない(NONE)
				break;

			case OBJECTTYPE_JUNKIE:
				SetPlayer(D3DXVECTOR3(40.0f + OBJ_SIZE * x, OBJ_SIZE + OBJ_SIZE * y, 0.0f));		//JUNKIEの描画(Player)
				break;

			case OBJECTTYPE_AMBUSH:
				SetEnemy(D3DXVECTOR3(40.0f + OBJ_SIZE * x, OBJ_SIZE + OBJ_SIZE * y, 0.0f), 0);		//AMBUSHの描画(Enemy)
				break;

			case OBJECTTYPE_CHASE:
				SetEnemy(D3DXVECTOR3(40.0f + OBJ_SIZE * x, OBJ_SIZE + OBJ_SIZE * y, 0.0f), 1);		//CHASEの描画(Enemy)
				break;

			case OBJECTTYPE_MOODY:
				SetEnemy(D3DXVECTOR3(40.0f + OBJ_SIZE * x, OBJ_SIZE + OBJ_SIZE * y, 0.0f), 2);		//MOODYの描画(Enemy)
				break;

			case OBJECTTYPE_SILLY:
				SetEnemy(D3DXVECTOR3(40.0f + OBJ_SIZE * x, OBJ_SIZE + OBJ_SIZE * y, 0.0f), 3);		//SILLYの描画(Enemy)
				break;

			case OBJECTTYPE_WALL:
				SetWall(D3DXVECTOR3(40.0f + OBJ_SIZE * x, OBJ_SIZE + OBJ_SIZE * y, 0.0f));	//壁の描画(WALL)
				break;

			case OBJECTTYPE_BALL:
				SetBall(D3DXVECTOR3(40.0f + OBJ_SIZE * x, OBJ_SIZE + OBJ_SIZE * y, 0.0f));	//玉の描画(BALL)
				break;

			case OBJECTTYPE_LINE:
				SetDoor(D3DXVECTOR3(40.0f + OBJ_SIZE * x, 45.0f + OBJ_SIZE * y, 0.0f));	//ドアの描画(DOOR)
				break;

			}
		}
	}
	fclose(fp);	//ファイルを閉じる
	fp = NULL;
	return;
}

void UninitMap() {

}

void UpdateMap() {
}

void DrawMap() {

}