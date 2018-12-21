
//=============================================================================
//
// テクスチャ付きポリゴン描画処理 [main.h]
// Author : AKIRA TANAKA
//
//=============================================================================
#ifndef _MAIN_H_
#define _MAIN_H_

//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include "d3dx9.h"
#include"dinput.h"
#include "xAudio2.h"
#define DIRECINPUT_VERSION (0x0800)
//*****************************************************************************
// ライブラリのリンク
// [構成プロパティ]->[リンカー]->[入力]->[追加の依存ファイル]に記述しても可能
//*****************************************************************************
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib,"winmm.lib")
#pragma comment(lib,"dinput8.lib")
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define SCREEN_WIDTH	(1280)				// ウインドウの幅
#define SCREEN_HEIGHT	(720)				// ウインドウの高さ

// 頂点フォーマット( 頂点座標[2D] / 頂点カラー / テクスチャ座標 )
#define FVF_VERTEX_2D (D3DFVF_XYZRHW | D3DFVF_DIFFUSE|D3DFVF_TEX1)

// 上記頂点フォーマットに合わせた構造体を定義
typedef enum {
	MODE_TITLE = 0,
	MODE_TUTORIAL,
	MODE_GAME,
	MODE_CLEAR,
	MODE_RESULT,
	MODE_RANKING,
	MODE_MAX
}MODE;
typedef struct//頂点情報
{

	D3DXVECTOR3 pos;//頂点座標
	FLOAT rhw;      //(1.0fで固定)
	D3DCOLOR col;   //頂点カラー
	D3DXVECTOR2 tex;//テクスチャ座標

}VERTEX_2D;
// 頂点フォーマット( 頂点座標[2D] / 頂点カラー )


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
LPDIRECT3DDEVICE9 GetDevice(void);
void SetMode(MODE mode);
MODE GatMode(void);
#endif