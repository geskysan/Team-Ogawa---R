//=============================================================================
//
// ポリゴン処理 [back.h]
// Author : AKIRA TANAKA
//
//=============================================================================
#ifndef _FADE_H_
#define _FADE_H_

#include "main.h"

typedef enum {
	FADE_NONE = 0,
	FADE_IN,
	FADE_OUT,
	FADE_MAX
 }FADE;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitFade(void);
void UninitFade(void);
void UpdateFade(void);
void DrawFade(void);

void SetFade(MODE mode);
FADE GetFade(void);

#endif