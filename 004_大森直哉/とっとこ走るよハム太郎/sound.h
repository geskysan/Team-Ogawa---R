//=============================================================================
//
// �T�E���h���� [sound.h]
// Author : 
//
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_

#include "main.h"

//*********************************************************
// �T�E���h�N���X
//*********************************************************

	// �T�E���h�t�@�C��
	typedef enum
	{
		SOUND_LABEL_BGM000 = 0,			// BGM
		SOUND_LABEL_BGM001,				// BGM
		SOUND_LABEL_BGM002,				// BGM
		SOUND_LABEL_SE_SHOT000,			// �e���ˉ�
		SOUND_LABEL_SE_HIT000,			// �Փˉ�
		SOUND_LABEL_SE_HIT001,			// �Փˉ�
		SOUND_LABEL_SE_EXPLOSION000,	// ������
		SOUND_LABEL_SE_PAUSE,			// �|�[�Y��
		SOUND_LABEL_SE_DECIDE,			// ���艹
		SOUND_LABEL_SE_CANCEL,			// �L�����Z����
		SOUND_LABEL_SE_SELECT,			// �I����
		SOUND_LABEL_SE_SPECIAL,			// �X�y�V������
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

	//static PARAM m_aParam[SOUND_LABEL_MAX];					// �p�����[�^

#endif
