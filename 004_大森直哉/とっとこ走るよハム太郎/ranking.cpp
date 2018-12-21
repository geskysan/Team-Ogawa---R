//=============================================================================
//
// �|���S������ [polygon.cpp]
// Author : AKIRA TANAKA
//
//=============================================================================
#include "ranking.h"
#include "input.h"
#include "fade.h"
#include "RankingScore.h"
//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void MakeVertexRanking(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9	g_pTextureRanking = NULL;	// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffRanking = NULL;//���_�o�b�t�@�̃|�C���^

//=============================================================================
// ����������
//=============================================================================
void InitRanking(void)
{

	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffRanking,
		NULL);

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/ranking.jpg", &g_pTextureRanking);

	//���_�ݒ�
	MakeVertexRanking(pDevice);

	InitRankingScore();
}

//=============================================================================
// �I������
//=============================================================================
void UninitRanking(void)
{
	// �e�N�X�`���̊J��4
	if (g_pVtxBuffRanking != NULL)
	{
		g_pVtxBuffRanking->Release();
		g_pVtxBuffRanking = NULL;
	}

	if (g_pTextureRanking != NULL)
	{
		g_pTextureRanking->Release();
		g_pTextureRanking = NULL;
	}

	UninitRankingScore();

}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateRanking(void)
{
	if (GetKeyboardPress(DIK_RETURN)) {
		SetFade(MODE_TITLE);
	}
	UpdateRankingScore();
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawRanking(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//�f�[�^�X�g���[���ɃZ�b�g
	pDevice->SetStreamSource(0,
		g_pVtxBuffRanking,
		0,
		sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureRanking);

	// �|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
		0,
		2);

	DrawRankingScore();
}

//=============================================================================
// ���_���̍쐬
//=============================================================================
void MakeVertexRanking(LPDIRECT3DDEVICE9 pDevice)
{
	VERTEX_2D *pVtx;

	//���b�N
	g_pVtxBuffRanking->Lock(0,
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
	g_pVtxBuffRanking->Unlock();
}

