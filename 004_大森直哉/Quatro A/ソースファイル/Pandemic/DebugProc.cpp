//=============================================================================
//
// デバッグ処理 [debugproc.cpp]
// Author : NAOYA OMORI
//
//=============================================================================
#include <stdio.h>
#include <stdarg.h>
#include "debugproc.h"

//*****************************************************************************
// 静的変数
//*****************************************************************************
LPD3DXFONT m_pFont = NULL;
char m_aStr[LENGTH_STRING_BUFF] = { "\0" };
bool m_bDisp = true;

//=============================================================================
// 初期化処理
//=============================================================================
void InitDebug()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 情報表示用フォントを設定
	D3DXCreateFont(pDevice, 18, 0, 0, 0, FALSE, SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "チェックポイント★リベンジ", &m_pFont);

}

//=============================================================================
// 開放処理
//=============================================================================
void UninitDebug(void)
{

	if (m_pFont != NULL)
	{// 情報表示用フォントの開放
		m_pFont->Release();
		m_pFont = NULL;
	}

}

//=============================================================================
// 書き込み処理
//=============================================================================
void PrintDebug(char *fmt, ...)
{
#ifdef _DEBUG
#if 0
	long *pParam;
	static char aBuf[256];

	pParam = (long*)&fmt;
	sprintf(aBuf, fmt, pParam[1], pParam[2], pParam[3], pParam[4],
		pParam[5], pParam[6], pParam[7], pParam[8],
		pParam[9], pParam[10], pParam[11], pParam[12]);
#else
	va_list list;			// 可変引数を処理する為に使用する変数
	char *pCur;
	char aBuf[256] = { "\0" };
	char aWk[32];

	// 可変引数にアクセスする前の初期処理
	va_start(list, fmt);

	pCur = fmt;
	for (; *pCur; ++pCur)
	{
		if (*pCur != '%')
		{
			sprintf(aWk, "%c", *pCur);
		}
		else
		{
			pCur++;

			switch (*pCur)
			{
			case 'd':
				// 可変引数にアクセスしてその変数を取り出す処理
				sprintf(aWk, "%d", va_arg(list, int));
				break;

			case 'f':
				// 可変引数にアクセスしてその変数を取り出す処理
				sprintf(aWk, "%f", va_arg(list, double));		// double型で指定
				break;

			case 's':
				// 可変引数にアクセスしてその変数を取り出す処理
				sprintf(aWk, "%s", va_arg(list, char*));
				break;

			case 'c':
				// 可変引数にアクセスしてその変数を取り出す処理
				sprintf(aWk, "%c", va_arg(list, char));
				break;

			default:
				sprintf(aWk, "%c", *pCur);
				break;
			}
		}

		strcat(aBuf, aWk);
	}

	// 可変引数にアクセスした後の終了処理
	va_end(list);

#endif
	if ((strlen(m_aStr) + strlen(aBuf)) < sizeof m_aStr - 1)
	{
		strcat(m_aStr, aBuf);
	}
#endif
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawDebug(void)
{
#ifdef _DEBUG
	if (m_bDisp)
	{
		RECT rect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };

		m_pFont->DrawText(NULL, m_aStr, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 255, 0, 0));

		// バッファクリア
		memset(m_aStr, 0, sizeof m_aStr);
	}
#endif
}

