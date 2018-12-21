//=============================================================================
//
// �Q�[�����X�R�A�̕`�� [EndGameScore.cpp]
// Author : NAOYA OMORI
//
//=============================================================================
#include "EndGameScore.h"
#include "polygon.h"
#include "ball.h"
#include "number.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAX_DIGIT	(8)
#define MAX_PATTEN	(10)

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void MakeVertexEndGameScore(LPDIRECT3DDEVICE9 pDevice);
LPDIRECT3DTEXTURE9 g_apTextureEndGameScore = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffEndGameScore = NULL;
EndGameScore g_aEndGameScore[MAX_DIGIT];
int iEndGameScore;

//=============================================================================
// ����������
//=============================================================================
void InitEndGameScore(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	int nCutEndGameScore;

	//�����ݒ�
	for (nCutEndGameScore = 0; nCutEndGameScore < MAX_DIGIT; nCutEndGameScore++)
	{
		g_aEndGameScore[nCutEndGameScore].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aEndGameScore[nCutEndGameScore].nType = 0;
		g_aEndGameScore[nCutEndGameScore].bUse = false;
		g_aEndGameScore[nCutEndGameScore].g_posEndGameScore = D3DXVECTOR3(0, 0, 0);
		g_aEndGameScore[nCutEndGameScore].g_rotEndGameScore = D3DXVECTOR3(0, 0, 0);
		g_aEndGameScore[nCutEndGameScore].g_fAngleEndGameScore = atan2f(0, 0);
		g_aEndGameScore[nCutEndGameScore].g_fLengthEndGameScore = sqrtf(0 * 0 + 0 * 0);
	}

	iEndGameScore = GetNumber();

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/number000.png", &g_apTextureEndGameScore);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_DIGIT,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffEndGameScore,
		NULL);

	for (int y = 0; y < MAX_DIGIT; y++)
	{
		SetEndGameScore(D3DXVECTOR3(65.0f + 50.0f * y, 525.0f, 0.0f));	//�X�R�A�i8���j
	}

	MakeVertexEndGameScore(pDevice);
}

void UninitEndGameScore(void) {

	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffEndGameScore != NULL)
	{
		g_pVtxBuffEndGameScore->Release();
		g_pVtxBuffEndGameScore = NULL;
	}

	// �e�N�X�`���̊J��
	if (g_apTextureEndGameScore != NULL) {
		g_apTextureEndGameScore->Release();
		g_apTextureEndGameScore = NULL;
	}
}
//=============================================================================
//�X�V����
//=============================================================================
void UpdateEndGameScore(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	VERTEX_2D *pVtx;

	iEndGameScore = GetScore(); //�X�R�A���Ƃ��Ă���

						 //���b�N
	g_pVtxBuffEndGameScore->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCutVtx = 0; nCutVtx < MAX_DIGIT; nCutVtx++) {
		int iPow = int(powf(10, float(MAX_DIGIT - nCutVtx)));
		float fTime = float(iEndGameScore % iPow / (iPow / 10));

		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(fTime*(1.0f / MAX_PATTEN), 0);
		pVtx[1].tex = D3DXVECTOR2(fTime*(1.0f / MAX_PATTEN) + 1.0f / MAX_PATTEN, 0);
		pVtx[2].tex = D3DXVECTOR2(fTime*(1.0f / MAX_PATTEN), 1);
		pVtx[3].tex = D3DXVECTOR2(fTime*(1.0f / MAX_PATTEN) + 1.0f / MAX_PATTEN, 1);
		pVtx += 4;

		//���b�N����
		g_pVtxBuffEndGameScore->Unlock();

	}
}

void DrawEndGameScore(void) {

	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	int nCutEndGameScore;

	//�f�[�^�X�g���[���ɃZ�b�g
	pDevice->SetStreamSource(0,
		g_pVtxBuffEndGameScore,
		0,
		sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_apTextureEndGameScore);

	for (nCutEndGameScore = 0; nCutEndGameScore < MAX_DIGIT; nCutEndGameScore++)
	{
		if (g_aEndGameScore[nCutEndGameScore].bUse == true)
		{	// �|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCutEndGameScore * 4, 2);
		}
	}
}

void SetEndGameScore(D3DXVECTOR3 pos) {

	VERTEX_2D *pVtx;
	int nCutEndGameScore;

	for (nCutEndGameScore = 0; nCutEndGameScore < MAX_DIGIT; nCutEndGameScore++)
	{
		if (g_aEndGameScore[nCutEndGameScore].bUse == false)
		{
			g_aEndGameScore[nCutEndGameScore].pos = pos;
			g_aEndGameScore[nCutEndGameScore].bUse = true;

			//���b�N
			g_pVtxBuffEndGameScore->Lock(0, 0, (void**)&pVtx, 0);

			//�e�N�X�`�����W�̐ݒ�
			pVtx += nCutEndGameScore * 4;
			pVtx[0].pos = g_aEndGameScore[nCutEndGameScore].pos;
			pVtx[1].pos = g_aEndGameScore[nCutEndGameScore].pos;
			pVtx[2].pos = g_aEndGameScore[nCutEndGameScore].pos;
			pVtx[3].pos = g_aEndGameScore[nCutEndGameScore].pos;

			//���b�N����
			g_pVtxBuffEndGameScore->Unlock();

			break;
		}
	}
}


//=============================================================================
// ���_���̍쐬
//=============================================================================
void MakeVertexEndGameScore(LPDIRECT3DDEVICE9 pDevice)
{
	VERTEX_2D *pVtx;
	int nCutVtx;

	//���b�N
	g_pVtxBuffEndGameScore->Lock(0, 0, (void**)&pVtx, 0);

	for (nCutVtx = 0; nCutVtx < MAX_DIGIT; nCutVtx++) {

		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].pos.x = g_aEndGameScore[nCutVtx].pos.x;
		pVtx[1].pos.x = g_aEndGameScore[nCutVtx].pos.x + 50;
		pVtx[2].pos.x = g_aEndGameScore[nCutVtx].pos.x;
		pVtx[3].pos.x = g_aEndGameScore[nCutVtx].pos.x + 50;

		pVtx[0].pos.y = g_aEndGameScore[nCutVtx].pos.y;
		pVtx[1].pos.y = g_aEndGameScore[nCutVtx].pos.y;
		pVtx[2].pos.y = g_aEndGameScore[nCutVtx].pos.y + 50;
		pVtx[3].pos.y = g_aEndGameScore[nCutVtx].pos.y + 50;

		// rhw�̐ݒ�
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
		float fScore = float(iEndGameScore % iPow / (iPow / 10));
		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(fScore*(1.0f / MAX_PATTEN), 0);
		pVtx[1].tex = D3DXVECTOR2(fScore*(1.0f / MAX_PATTEN) + 1.0f / MAX_PATTEN, 0);
		pVtx[2].tex = D3DXVECTOR2(fScore*(1.0f / MAX_PATTEN), 1);
		pVtx[3].tex = D3DXVECTOR2(fScore*(1.0f / MAX_PATTEN) + 1.0f / MAX_PATTEN, 1);
		pVtx += 4;
	}

	//���b�N����
	g_pVtxBuffEndGameScore->Unlock();
}

int GetEndGameScore(void) {
	return iEndGameScore;
}