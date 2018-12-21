//=============================================================================
//
// �Q�[�����X�R�A�̕`�� [Number.cpp]
// Author : NAOYA OMORI
//
//=============================================================================
#include "number.h"
#include "polygon.h"
#include "ball.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAX_DIGIT	(8)
#define MAX_PATTEN	(10)

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void MakeVertexNumber(LPDIRECT3DDEVICE9 pDevice);
LPDIRECT3DTEXTURE9 g_apTextureNumber = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffNumber = NULL;
Number g_aNumber[MAX_DIGIT];
int iScore;

//=============================================================================
// ����������
//=============================================================================
void InitNumber(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	int nCutNumber;

	//�����ݒ�
	for (nCutNumber = 0; nCutNumber < MAX_DIGIT; nCutNumber++)
	{
		g_aNumber[nCutNumber].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aNumber[nCutNumber].nType = 0;
		g_aNumber[nCutNumber].bUse = false;
		g_aNumber[nCutNumber].g_posNumber = D3DXVECTOR3(0, 0, 0);
		g_aNumber[nCutNumber].g_rotNumber = D3DXVECTOR3(0, 0, 0);
		g_aNumber[nCutNumber].g_fAngleNumber = atan2f(0, 0);
		g_aNumber[nCutNumber].g_fLengthNumber = sqrtf(0 * 0 + 0 * 0);
	}

	iScore = 0;

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/number000.png", &g_apTextureNumber);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_DIGIT,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffNumber,
		NULL);

	for (int y = 0; y < MAX_DIGIT; y++)
	{
		SetNumber(D3DXVECTOR3(1080.0f + 22.0f * y, 4.0f, 0.0f));	//�X�R�A�i8���j
	}

	MakeVertexNumber(pDevice);
}

void UninitNumber(void) {

	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffNumber != NULL)
	{
		g_pVtxBuffNumber->Release();
		g_pVtxBuffNumber = NULL;
	}

	// �e�N�X�`���̊J��
	if (g_apTextureNumber != NULL) {
		g_apTextureNumber->Release();
		g_apTextureNumber = NULL;
	}
}
//=============================================================================
//�X�V����
//=============================================================================
void UpdateNumber(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	VERTEX_2D *pVtx;

	iScore = GetScore(); //�X�R�A���Ƃ��Ă���

						 //���b�N
	g_pVtxBuffNumber->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCutVtx = 0; nCutVtx < MAX_DIGIT; nCutVtx++) {
		int iPow = int (powf(10,float ( MAX_DIGIT - nCutVtx)));
		float fTime =  float (iScore % iPow / (iPow / 10));

		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(fTime*(1.0f / MAX_PATTEN), 0);
		pVtx[1].tex = D3DXVECTOR2(fTime*(1.0f / MAX_PATTEN) + 1.0f / MAX_PATTEN, 0);
		pVtx[2].tex = D3DXVECTOR2(fTime*(1.0f / MAX_PATTEN), 1);
		pVtx[3].tex = D3DXVECTOR2(fTime*(1.0f / MAX_PATTEN) + 1.0f / MAX_PATTEN, 1);
		pVtx += 4;

		//���b�N����
		g_pVtxBuffNumber->Unlock();

	}
}

void DrawNumber(void) {

	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	int nCutNumber;

	//�f�[�^�X�g���[���ɃZ�b�g
	pDevice->SetStreamSource(0,
		g_pVtxBuffNumber,
		0,
		sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_apTextureNumber);

	for (nCutNumber = 0; nCutNumber < MAX_DIGIT; nCutNumber++)
	{
		if (g_aNumber[nCutNumber].bUse == true)
		{	// �|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCutNumber * 4, 2);
		}
	}
}

void SetNumber(D3DXVECTOR3 pos) {

	VERTEX_2D *pVtx;
	int nCutNumber;

	for (nCutNumber = 0; nCutNumber < MAX_DIGIT; nCutNumber++)
	{
		if (g_aNumber[nCutNumber].bUse == false)
		{
			g_aNumber[nCutNumber].pos = pos;
			g_aNumber[nCutNumber].bUse = true;

			//���b�N
			g_pVtxBuffNumber->Lock(0, 0, (void**)&pVtx, 0);

			//�e�N�X�`�����W�̐ݒ�
			pVtx += nCutNumber * 4;
			pVtx[0].pos = g_aNumber[nCutNumber].pos;
			pVtx[1].pos = g_aNumber[nCutNumber].pos;
			pVtx[2].pos = g_aNumber[nCutNumber].pos;
			pVtx[3].pos = g_aNumber[nCutNumber].pos;

			//���b�N����
			g_pVtxBuffNumber->Unlock();

			break;
		}
	}
}


//=============================================================================
// ���_���̍쐬
//=============================================================================
void MakeVertexNumber(LPDIRECT3DDEVICE9 pDevice)
{
	VERTEX_2D *pVtx;
	int nCutVtx;

	//���b�N
	g_pVtxBuffNumber->Lock(0, 0, (void**)&pVtx, 0);

	for (nCutVtx = 0; nCutVtx < MAX_DIGIT; nCutVtx++) {

		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].pos.x = g_aNumber[nCutVtx].pos.x;
		pVtx[1].pos.x = g_aNumber[nCutVtx].pos.x + 20;
		pVtx[2].pos.x = g_aNumber[nCutVtx].pos.x;
		pVtx[3].pos.x = g_aNumber[nCutVtx].pos.x + 20;

		pVtx[0].pos.y = g_aNumber[nCutVtx].pos.y;
		pVtx[1].pos.y = g_aNumber[nCutVtx].pos.y;
		pVtx[2].pos.y = g_aNumber[nCutVtx].pos.y + 20;
		pVtx[3].pos.y = g_aNumber[nCutVtx].pos.y + 20;

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

		int iPow = int (powf(10, float (MAX_DIGIT - nCutVtx)));
		float fScore = float (iScore % iPow / (iPow / 10));
		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(fScore*(1.0f / MAX_PATTEN), 0);
		pVtx[1].tex = D3DXVECTOR2(fScore*(1.0f / MAX_PATTEN) + 1.0f / MAX_PATTEN, 0);
		pVtx[2].tex = D3DXVECTOR2(fScore*(1.0f / MAX_PATTEN), 1);
		pVtx[3].tex = D3DXVECTOR2(fScore*(1.0f / MAX_PATTEN) + 1.0f / MAX_PATTEN, 1);
		pVtx += 4;
	}

	//���b�N����
	g_pVtxBuffNumber->Unlock();
}

int GetNumber(void) {
	return iScore;
}