//=============================================================================
//
// �����L���O�����i�`����܂ށj[ResultScore.cpp]
// Author : NAOYA OMORI
//
//=============================================================================
#include "ResultScore.h"
#include "number.h"
#include "main.h"
#include "ball.h"
#include "timer.h"
#include "polygon.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAX_DIGIT	(3)		//����
#define MAX_RANKING (3)		//�l�̐��܂ŕ\��
#define MAX_PATTEN	(10)	//0�`9�܂�

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void MakeVertexResultScore(LPDIRECT3DDEVICE9 pDevice);
LPDIRECT3DTEXTURE9 g_apTextureResultScore = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffResultScore = NULL;
ResultScore g_aResultScore[MAX_RANKING][MAX_DIGIT];
int iResult[MAX_RANKING] = { 0,0,0 };
int g_tCount, g_bCount, g_lCount;
//=============================================================================
// ����������
//=============================================================================
void InitResultScore(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	int nCutResultScore;
	int nCutResult;

	//�����ݒ�
	for (nCutResultScore = 0; nCutResultScore < MAX_DIGIT; nCutResultScore++)
		for (nCutResult = 0; nCutResult < MAX_RANKING; nCutResult++) {
			{
				g_aResultScore[nCutResult][nCutResultScore].bUse = false;
				g_aResultScore[nCutResult][nCutResultScore].pos = D3DXVECTOR3(125.0f + 50.0f * nCutResultScore, 250.0f + 1.0f * nCutResult, 0.0f);
				g_aResultScore[1][nCutResultScore].pos = D3DXVECTOR3(560.0f + 50.0f * nCutResultScore, 250.0f + 1.0f * nCutResult, 0.0f);
				g_aResultScore[2][nCutResultScore].pos = D3DXVECTOR3(1010.0f + 50.0f * nCutResultScore, 250.0f + 1.0f * nCutResult, 0.0f);
				g_aResultScore[nCutResult][nCutResultScore].rot = D3DXVECTOR3(0, 0, 0);
			}
		}

	g_tCount = 0;
	g_bCount = 0;
	g_lCount = 0;

	g_tCount = GetTime();
	g_bCount = GetBulletCount();
	g_lCount = GetPlayerHP();

	iResult[0] = g_tCount;
	iResult[1] = g_bCount;
	iResult[2] = g_lCount;

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/number000.png", &g_apTextureResultScore);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_DIGIT * MAX_RANKING,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffResultScore,
		NULL);

	MakeVertexResultScore(pDevice);

}

void UninitResultScore(void) {

	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffResultScore != NULL)
	{
		g_pVtxBuffResultScore->Release();
		g_pVtxBuffResultScore = NULL;
	}

	// �e�N�X�`���̊J��
	if (g_apTextureResultScore != NULL) {
		g_apTextureResultScore->Release();
		g_apTextureResultScore = NULL;
	}
}

//=============================================================================
//�X�V����
//=============================================================================
void UpdateResultScore(void)
{

}

void DrawResultScore(void) {

	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//�f�[�^�X�g���[���ɃZ�b�g
	pDevice->SetStreamSource(0,
		g_pVtxBuffResultScore,
		0,
		sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_apTextureResultScore);


	for (int nCutResultScore = 0; nCutResultScore < MAX_DIGIT * MAX_RANKING; nCutResultScore++) {

		//�|���S���̍쐬
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCutResultScore * 4, 2);

	}
}

//=============================================================================
// ���_���̍쐬
//=============================================================================
void MakeVertexResultScore(LPDIRECT3DDEVICE9 pDevice)
{
	VERTEX_2D *pVtx;
	int nCutVtx;

	//���b�N
	g_pVtxBuffResultScore->Lock(0, 0, (void**)&pVtx, 0);

	for (nCutVtx = 0; nCutVtx < MAX_DIGIT; nCutVtx++) {
		for (int nCutVtxx = 0; nCutVtxx < MAX_RANKING; nCutVtxx++) {

			//���_���W�̐ݒ�
			pVtx[0].pos.x = g_aResultScore[nCutVtxx][nCutVtx].pos.x;
			pVtx[1].pos.x = g_aResultScore[nCutVtxx][nCutVtx].pos.x + 50;
			pVtx[2].pos.x = g_aResultScore[nCutVtxx][nCutVtx].pos.x;
			pVtx[3].pos.x = g_aResultScore[nCutVtxx][nCutVtx].pos.x + 50;

			pVtx[0].pos.y = g_aResultScore[nCutVtxx][nCutVtx].pos.y;
			pVtx[1].pos.y = g_aResultScore[nCutVtxx][nCutVtx].pos.y;
			pVtx[2].pos.y = g_aResultScore[nCutVtxx][nCutVtx].pos.y + 50;
			pVtx[3].pos.y = g_aResultScore[nCutVtxx][nCutVtx].pos.y + 50;

			//rhw�̐ݒ�
			pVtx[0].rhw = 1.0f;
			pVtx[1].rhw = 1.0f;
			pVtx[2].rhw = 1.0f;
			pVtx[3].rhw = 1.0f;

			// ���_�J���[�̐ݒ�
			pVtx[0].col = D3DCOLOR_RGBA(255, 0, 0, 255);//RGBA�̐F������
			pVtx[1].col = D3DCOLOR_RGBA(255, 0, 0, 255);
			pVtx[2].col = D3DCOLOR_RGBA(255, 0, 0, 255);
			pVtx[3].col = D3DCOLOR_RGBA(255, 0, 0, 255);

			int iPow = int(powf(10, float(MAX_DIGIT - nCutVtx)));
			float fScore = float(iResult[nCutVtxx] % iPow / (iPow / 10));
			//�e�N�X�`�����W�̐ݒ�
			pVtx[0].tex = D3DXVECTOR2(fScore*(1.0f / MAX_PATTEN), 0);
			pVtx[1].tex = D3DXVECTOR2(fScore*(1.0f / MAX_PATTEN) + 1.0f / MAX_PATTEN, 0);
			pVtx[2].tex = D3DXVECTOR2(fScore*(1.0f / MAX_PATTEN), 1);
			pVtx[3].tex = D3DXVECTOR2(fScore*(1.0f / MAX_PATTEN) + 1.0f / MAX_PATTEN, 1);
			pVtx += 4;
		}
	}

	//���b�N����
	g_pVtxBuffResultScore->Unlock();
}