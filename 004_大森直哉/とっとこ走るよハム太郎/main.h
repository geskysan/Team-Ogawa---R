
//=============================================================================
//
// �e�N�X�`���t���|���S���`�揈�� [main.h]
// Author : AKIRA TANAKA
//
//=============================================================================
#ifndef _MAIN_H_
#define _MAIN_H_

//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include "d3dx9.h"
#include"dinput.h"
#include "xAudio2.h"
#define DIRECINPUT_VERSION (0x0800)
//*****************************************************************************
// ���C�u�����̃����N
// [�\���v���p�e�B]->[�����J�[]->[����]->[�ǉ��̈ˑ��t�@�C��]�ɋL�q���Ă��\
//*****************************************************************************
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib,"winmm.lib")
#pragma comment(lib,"dinput8.lib")
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define SCREEN_WIDTH	(1280)				// �E�C���h�E�̕�
#define SCREEN_HEIGHT	(720)				// �E�C���h�E�̍���

// ���_�t�H�[�}�b�g( ���_���W[2D] / ���_�J���[ / �e�N�X�`�����W )
#define FVF_VERTEX_2D (D3DFVF_XYZRHW | D3DFVF_DIFFUSE|D3DFVF_TEX1)

// ��L���_�t�H�[�}�b�g�ɍ��킹���\���̂��`
typedef enum {
	MODE_TITLE = 0,
	MODE_TUTORIAL,
	MODE_GAME,
	MODE_CLEAR,
	MODE_RESULT,
	MODE_RANKING,
	MODE_MAX
}MODE;
typedef struct//���_���
{

	D3DXVECTOR3 pos;//���_���W
	FLOAT rhw;      //(1.0f�ŌŒ�)
	D3DCOLOR col;   //���_�J���[
	D3DXVECTOR2 tex;//�e�N�X�`�����W

}VERTEX_2D;
// ���_�t�H�[�}�b�g( ���_���W[2D] / ���_�J���[ )


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
LPDIRECT3DDEVICE9 GetDevice(void);
void SetMode(MODE mode);
MODE GatMode(void);
#endif