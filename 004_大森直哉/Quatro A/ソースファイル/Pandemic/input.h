#pragma once
//=============================================================================
//
// ���͏��� [input.h]
// Author : NAOYA OMORI
//
//=============================================================================

#include "main.h"
//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitKeyboard(HINSTANCE hInstance, HWND hWnd);
void UninitKeyboard(void);
void UpdateKeyboard(void);
bool GetKeyboardPress(int nKey);
bool GetKeyboardTrigger(int nKey);
bool GetKeyboardRepeat(int nKey);
bool GetKeyboardRelease(int nKey);