//=============================================================================
//
// �^�C�g������ [title.cpp]
// Author : NAOYA OMORI
//
//=============================================================================
#include "title.h"
#include "input.h"
#include "main.h"
#include "fade.h"
#include "sound.h"
#include "titlefont.h"
#include "titleplayer.h"
#include "Selectfont.h"
#include "TitleArrow.h"
#include "PressEnter.h"

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void MakeVertexTitle(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9	g_pTextureTitle = NULL;	// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTitle = NULL;//���_�o�b�t�@�̃|�C���^
int TimeCount;
bool ReturnFlag;

//=============================================================================
// ����������
//=============================================================================
void InitTitle(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	TimeCount = 0;
	ReturnFlag = TRUE;

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffTitle,
		NULL);

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/Title.jpg", &g_pTextureTitle);

	////���_�ݒ�
	MakeVertexTitle(pDevice);

	Stop(SOUND_LABEL_BGM001);
	Stop(SOUND_LABEL_BGM002);
	Play(SOUND_LABEL_BGM000);

	InitTitleFont();
	InitTitlePlayer();
	InitSelectfont();
	InitArrow();
	InitPressEnter();
}


//=============================================================================
// �I������
//=============================================================================
void UninitTitle(void)
{
	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffTitle != NULL)
	{
		g_pVtxBuffTitle->Release();
		g_pVtxBuffTitle = NULL;
	}

	// �e�N�X�`���̊J��
	if (g_pTextureTitle != NULL) {
		g_pTextureTitle->Release();
		g_pTextureTitle = NULL;
	}

	UninitTitleFont();
	UninitTitlePlayer();
	UninitSelectfont();
	UninitArrow();
	UninitPressEnter();

}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateTitle(void)
{

	TimeCount++;

	if (TimeCount == 600 && ReturnFlag == TRUE) {
		SetFade(MODE_RANKING);
		TimeCount = 0;
	}

	SetSelectfont(D3DXVECTOR3(650.0f, 400.0f, 0.0f), 0);
	SetSelectfont(D3DXVECTOR3(650.0f, 500.0f, 0.0f), 1);
	SetSelectfont(D3DXVECTOR3(650.0f, 600.0f, 0.0f), 2);
	SetEnterPosition(D3DXVECTOR3(1100.0f, 680.0f, 0.0f));

	UpdateTitleFont();
	UpdateTitlePlayer();
	UpdateArrow();
	UpdateSelectfont();
	UpdatePressEnter();
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawTitle(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//�f�[�^�X�g���[���ɃZ�b�g
	pDevice->SetStreamSource(0,
		g_pVtxBuffTitle,
		0,
		sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureTitle);

	// �|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
		0,
		2);

	DrawTitleFont();
	DrawTitlePlayer();
	DrawSelectfont();
	DrawArrow();
	DrawPressEnter();
}

//=============================================================================
// ���_���̍쐬
//=============================================================================
void MakeVertexTitle(LPDIRECT3DDEVICE9 pDevice)
{
	VERTEX_2D *pVtx;

	//���b�N
	g_pVtxBuffTitle->Lock(0,
		0,
		(void**)&pVtx,
		0);

	// ���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(0, 0, 0.0f);//xy���W�ňʒu����
	pVtx[1].pos = D3DXVECTOR3(1280, 0, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0, 720, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(1280, 720, 0.0f);

	// rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	// ���_�J���[�̐ݒ�
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 0);//RGBA�̐F������
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 0);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 0);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 0);

	// �e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0, 0);
	pVtx[1].tex = D3DXVECTOR2(1, 0);
	pVtx[2].tex = D3DXVECTOR2(0, 1);
	pVtx[3].tex = D3DXVECTOR2(1, 1);

	//���b�N����
	g_pVtxBuffTitle->Unlock();
}

int GetFlag(void) {
	return ReturnFlag;
}