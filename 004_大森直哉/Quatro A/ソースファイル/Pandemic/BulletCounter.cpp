//=============================================================================
//
// �e���̕`�揈�� [BulletCounter.cpp]
// Author : NAOYA OMORI
//
//=============================================================================
#include "BulletCounter.h"
#include "fade.h"
#include "ball.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAX_DIGIT	(2)			//����
#define MAX_PATTEN	(10)		//�P�`�P�O�܂�
//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void MakeVertexBulletCounter(LPDIRECT3DDEVICE9 pDevice);
LPDIRECT3DTEXTURE9 g_apTextureBulletCounter = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBulletCounter = NULL;
Counter g_aCounter[MAX_DIGIT];
int iCounter;
int g_nCutVtx;

//=============================================================================
// ����������
//=============================================================================
void InitBulletCounter(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	int nCutCounter;

	//�����ݒ�
	for (nCutCounter = 0; nCutCounter < MAX_DIGIT; nCutCounter++)
	{
		g_aCounter[nCutCounter].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aCounter[nCutCounter].nType = 0;
		g_aCounter[nCutCounter].bUse = false;
		g_aCounter[nCutCounter].posNumber = D3DXVECTOR3(0, 0, 0);
		g_aCounter[nCutCounter].rotNumber = D3DXVECTOR3(0, 0, 0);
		g_aCounter[nCutCounter].fAngleNumber = atan2f(0, 0);
		g_aCounter[nCutCounter].fLengthNumber = sqrtf(0 * 0 + 0 * 0);
	}

	iCounter = 0;
	g_nCutVtx = 0;

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/number000.png", &g_apTextureBulletCounter);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_DIGIT,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBulletCounter,
		NULL);

	for (int x = 0; x < MAX_DIGIT; x++)
	{
		SetBulletCounter(D3DXVECTOR3(415.0f + 20.0f * x, 3.0f, 0.0f));	//�^�C�}�[�i2���j
	}

	MakeVertexBulletCounter(pDevice);

}

void UninitBulletCounter(void) {

	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffBulletCounter != NULL)
	{
		g_pVtxBuffBulletCounter->Release();
		g_pVtxBuffBulletCounter = NULL;
	}

	// �e�N�X�`���̊J��
	if (g_apTextureBulletCounter != NULL) {
		g_apTextureBulletCounter->Release();
		g_apTextureBulletCounter = NULL;
	}
}
//=============================================================================
//�X�V����
//=============================================================================
void UpdateBulletCounter(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	VERTEX_2D *pVtx;

	//�O�ȉ��ɂ��Ȃ��悤��
	if (iCounter <= 0)
	{
		iCounter = 0;
	}

	//���b�N
	g_pVtxBuffBulletCounter->Lock(0, 0, (void**)&pVtx, 0);

	MakeVertexBulletCounter(pDevice);

	//���b�N����
	g_pVtxBuffBulletCounter->Unlock();

}

void DrawBulletCounter(void) {

	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	int nCutCounter;

	//�f�[�^�X�g���[���ɃZ�b�g
	pDevice->SetStreamSource(0,
		g_pVtxBuffBulletCounter,
		0,
		sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_apTextureBulletCounter);

	for (nCutCounter = 0; nCutCounter < MAX_DIGIT; nCutCounter++)
	{
		if (g_aCounter[nCutCounter].bUse == true)
		{
			// �|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCutCounter * 4, 2);
		}
	}
}

void SetBulletCounter(D3DXVECTOR3 pos) {

	VERTEX_2D *pVtx;
	int nCutCounter;
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	for (nCutCounter = 0; nCutCounter < MAX_DIGIT; nCutCounter++)
	{
		if (g_aCounter[nCutCounter].bUse == false)
		{
			g_aCounter[nCutCounter].pos = pos;
			g_aCounter[nCutCounter].bUse = true;

			//���b�N
			g_pVtxBuffBulletCounter->Lock(0, 0, (void**)&pVtx, 0);

			// ���_���W�̐ݒ�
			pVtx += nCutCounter * 4;
			pVtx[0].pos = g_aCounter[nCutCounter].pos;
			pVtx[1].pos = g_aCounter[nCutCounter].pos;
			pVtx[2].pos = g_aCounter[nCutCounter].pos;
			pVtx[3].pos = g_aCounter[nCutCounter].pos;

			//���b�N����
			g_pVtxBuffBulletCounter->Unlock();
			break;
		}
	}
}

//=============================================================================
// ���_���̍쐬
//=============================================================================
void MakeVertexBulletCounter(LPDIRECT3DDEVICE9 pDevice)
{
	VERTEX_2D *pVtx;
	int g_nCutVtx;

	iCounter = GetBulletCount();

	//���b�N
	g_pVtxBuffBulletCounter->Lock(0, 0, (void**)&pVtx, 0);

	for (g_nCutVtx = 0; g_nCutVtx < MAX_DIGIT; g_nCutVtx++) {

		// ���_���W�̐ݒ�
		pVtx[0].pos.x = g_aCounter[g_nCutVtx].pos.x;
		pVtx[1].pos.x = g_aCounter[g_nCutVtx].pos.x + 20;
		pVtx[2].pos.x = g_aCounter[g_nCutVtx].pos.x;
		pVtx[3].pos.x = g_aCounter[g_nCutVtx].pos.x + 20;

		pVtx[0].pos.y = g_aCounter[g_nCutVtx].pos.y;
		pVtx[1].pos.y = g_aCounter[g_nCutVtx].pos.y;
		pVtx[2].pos.y = g_aCounter[g_nCutVtx].pos.y + 20;
		pVtx[3].pos.y = g_aCounter[g_nCutVtx].pos.y + 20;

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

		int iPow = int (powf(10,  float (MAX_DIGIT - g_nCutVtx)));
		float fCounter = float (iCounter % iPow / (iPow / 10));

		// �e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(fCounter*(1.0f / MAX_PATTEN), 0);
		pVtx[1].tex = D3DXVECTOR2(fCounter*(1.0f / MAX_PATTEN) + 1.0f / MAX_PATTEN, 0);
		pVtx[2].tex = D3DXVECTOR2(fCounter*(1.0f / MAX_PATTEN), 1);
		pVtx[3].tex = D3DXVECTOR2(fCounter*(1.0f / MAX_PATTEN) + 1.0f / MAX_PATTEN, 1);
		pVtx += 4;

	}

	//���b�N����
	g_pVtxBuffBulletCounter->Unlock();

}