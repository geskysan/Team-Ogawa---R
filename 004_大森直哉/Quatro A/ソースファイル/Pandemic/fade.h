#pragma once
//=============================================================================
//
// フェード処理 [Fade.h]
// Author : NAOYA OMORI
//
//=============================================================================

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