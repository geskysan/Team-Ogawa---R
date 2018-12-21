//=============================================================================
//
// �N���A��ʏ��� [clear.cpp]
// Author : NAOYA OMORI
//
//=============================================================================
#include "clear.h"
#include "input.h"
#include "fade.h"
#include "sound.h"
#include "rankingscore.h"
//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void MakeVertexClear(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9	g_pTextureClear = NULL;	// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffClear = NULL;//���_�o�b�t�@�̃|�C���^

//=============================================================================
// ����������
//=============================================================================
void InitClear(void)
{

	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffClear,
		NULL);

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/GameClear.jpg", &g_pTextureClear);

	//���_�ݒ�
	MakeVertexClear(pDevice);

	RankingRecord();

	Stop(SOUND_LABEL_BGM001);
	Play(SOUND_LABEL_SE_SPECIAL);

}

//=============================================================================
// �I������
//=============================================================================
void UninitClear(void)
{
	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffClear != NULL)
	{
		g_pVtxBuffClear->Release();
		g_pVtxBuffClear = NULL;
	}

	// �e�N�X�`���̊J��
	if (g_pTextureClear != NULL)
	{
		g_pTextureClear->Release();
		g_pTextureClear = NULL;
	}

}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateClear(void)
{
	//�G���^�[�L�[�������ƃ����L���O��ʂɍs������
	if (GetKeyboardPress(DIK_RETURN) && GetFade() == FADE_NONE) {
		SetFade(MODE_RESULT);
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawClear(void)
{

	//�f�o�C�X�擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//�f�[�^�X�g���[���ɃZ�b�g
	pDevice->SetStreamSource(0, g_pVtxBuffClear, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureClear);

	// �|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

}

//=============================================================================
// ���_���̍쐬
//=============================================================================
void MakeVertexClear(LPDIRECT3DDEVICE9 pDevice)
{
	VERTEX_2D *pVtx;

	//���b�N
	g_pVtxBuffClear->Lock(0, 0, (void**)&pVtx, 0);

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
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);//RGBA�̐F������
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	// �e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0, 0);
	pVtx[1].tex = D3DXVECTOR2(1, 0);
	pVtx[2].tex = D3DXVECTOR2(0, 1);
	pVtx[3].tex = D3DXVECTOR2(1, 1);

	//���b�N����
	g_pVtxBuffClear->Unlock();

}