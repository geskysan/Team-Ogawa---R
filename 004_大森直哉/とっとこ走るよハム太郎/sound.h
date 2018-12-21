//=============================================================================
//
// サウンド処理 [sound.h]
// Author : 
//
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_

#include "main.h"

//*********************************************************
// サウンドクラス
//*********************************************************

	// サウンドファイル
	typedef enum
	{
		SOUND_LABEL_BGM000 = 0,			// BGM
		SOUND_LABEL_BGM001,				// BGM
		SOUND_LABEL_BGM002,				// BGM
		SOUND_LABEL_SE_SHOT000,			// 弾発射音
		SOUND_LABEL_SE_HIT000,			// 衝突音
		SOUND_LABEL_SE_HIT001,			// 衝突音
		SOUND_LABEL_SE_EXPLOSION000,	// 爆発音
		SOUND_LABEL_SE_PAUSE,			// ポーズ音
		SOUND_LABEL_SE_DECIDE,			// 決定音
		SOUND_LABEL_SE_CANCEL,			// キャンセル音
		SOUND_LABEL_SE_SELECT,			// 選択音
		SOUND_LABEL_SE_SPECIAL,			// スペシャル音
		SOUND_LABEL_MAX
	} SOUND_LABEL;

	HRESULT InitSound(HWND hWnd);
	void UninitSound(void);
	HRESULT Play(SOUND_LABEL label);
	void Stop(SOUND_LABEL label);
	void Stop(void);
	void SetVolume(SOUND_LABEL label, float fValue);

	HRESULT CheckChunk(HANDLE hFile, DWORD dwFormat, DWORD *pChunkSize, DWORD *pChunkDataPosition);
	HRESULT ReadChunkData(HANDLE hFile, void *pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset);

	//static PARAM m_aParam[SOUND_LABEL_MAX];					// パラメータ

#endif
