#pragma once
//=============================================================================
//
// マップ処理 [map.h]
// Author : NAOYA OMORI
//
//=============================================================================

#include "main.h"

#define MAX_OBJ_X 26	//横列
#define MAX_OBJ_Y 16	//縦列
#define OBJ_SIZE 50.0f

//map用列挙型宣言
typedef enum {
	OBJECTTYPE_NONE,
	OBJECTTYPE_JUNKIE,
	OBJECTTYPE_AMBUSH,
	OBJECTTYPE_CHASE,
	OBJECTTYPE_MOODY,
	OBJECTTYPE_SILLY,
	OBJECTTYPE_WALL,
	OBJECTTYPE_BALL,
	OBJECTTYPE_LINE,
	OBJECTTYPE_MAX
}OBJECT_TYPE;

void InitMap(void);
void UninitMap(void);
void UpdateMap(void);
void DrawMap(void);