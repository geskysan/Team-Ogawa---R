//=============================================================================
//
// �������Ԃ̏��� [time.cpp]
// Author : NAOYA OMORI
//
//=============================================================================
#include "timer.h"
#include "fade.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAX_DIGIT	(3)
#define MAX_PATTEN	(10)
//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void MakeVertexTimer(LPDIRECT3DDEVICE9 pDevice);
LPDIRECT3DTEXTURE9 g_apTextureTimer = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTimer = NULL;
Timer g_aTimer[MAX_DIGIT];
bool TimeFlag;
int iTime;
int TCount;
int nCutVtx;
//=============================================================================
// ����������
//=============================================================================
void InitTimer(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	int nCutTimer;

	for (nCutTimer = 0; nCutTimer < MAX_DIGIT; nCutTimer++)
	{
		g_aTimer[nCutTimer].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aTimer[nCutTimer].nType = 0;
		g_aTimer[nCutTimer].bUse = false;
		g_aTimer[nCutTimer].g_posNumber = D3DXVECTOR3(0, 0, 0);
		g_aTimer[nCutTimer].g_rotNumber = D3DXVECTOR3(0, 0, 0);
		g_aTimer[nCutTimer].g_fAngleNumber = atan2f(0, 0);
		g_aTimer[nCutTimer].g_fLengthNumber = sqrtf(0 * 0 + 0 * 0);
	}

	TimeFlag = false;
	TCount = 0;
	iTime = 120;
	nCutVtx = 0;

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/number000.png", &g_apTextureTimer);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_DIGIT,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffTimer,
		NULL);

	for (int x = 0; x < MAX_DIGIT; x++)
	{
		SetTimer(D3DXVECTOR3(610.0f + 20.0f * x, 3.0f, 0.0f));	//�^�C�}�[�i�R���j
	}

	MakeVertexTimer(pDevice);

}

void UninitTimer(void) {
	// �e�N�X�`���̊J��
	if (g_pVtxBuffTimer != NULL)
	{
		g_pVtxBuffTimer->Release();
		g_pVtxBuffTimer = NULL;
	}

	if (g_apTextureTimer != NULL) {
		g_apTextureTimer->Release();
		g_apTextureTimer = NULL;
	}
}
//=============================================================================
//�X�V����
//=============================================================================
void UpdateTimer(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	VERTEX_2D *pVtx;

	TCount++;

	if (TCount % 60 == 0 && TimeFlag == TRUE)
	{
		iTime -= 1;
		TCount = 0;
	}

	if (iTime == 0 && GetFade() == FADE_NONE) {
		SetFade(MODE_RESULT);
	}
	if (iTime <= 0)
	{
		iTime = 0;
	}

	//���b�N
	g_pVtxBuffTimer->Lock(0, 0, (void**)&pVtx, 0);

	for (nCutVtx = 0; nCutVtx < MAX_DIGIT; nCutVtx++) {
		//�e�N�X�`�����W�̐ݒ�
		int iPow = int (powf(10, float (MAX_DIGIT - nCutVtx)));
		float fTime = float (iTime % iPow / (iPow / 10));
		pVtx[0].tex = D3DXVECTOR2(fTime*(1.0f / MAX_PATTEN), 0);
		pVtx[1].tex = D3DXVECTOR2(fTime*(1.0f / MAX_PATTEN) + 1.0f / MAX_PATTEN, 0);
		pVtx[2].tex = D3DXVECTOR2(fTime*(1.0f / MAX_PATTEN), 1);
		pVtx[3].tex = D3DXVECTOR2(fTime*(1.0f / MAX_PATTEN) + 1.0f / MAX_PATTEN, 1);
		pVtx += 4;

		//���b�N����
		g_pVtxBuffTimer->Unlock();
	}
}

void DrawTimer(void) {

	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	int nCutTimer;

	pDevice->SetStreamSource(0,
		g_pVtxBuffTimer,
		0,
		sizeof(VERTEX_2D));

	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_apTextureTimer);

	for (nCutTimer = 0; nCutTimer < MAX_DIGIT; nCutTimer++)
	{
		if (g_aTimer[nCutTimer].bUse == true)
		{
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCutTimer * 4, 2);
		}
	}
}

void SetTimer(D3DXVECTOR3 pos) {

	VERTEX_2D *pVtx;
	int nCutTimer;
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	for (nCutTimer = 0; nCutTimer < MAX_DIGIT; nCutTimer++)
	{
		if (g_aTimer[nCutTimer].bUse == false)
		{
			g_aTimer[nCutTimer].pos = pos;
			g_aTimer[nCutTimer].bUse = true;

			//���b�N
			g_pVtxBuffTimer->Lock(0, 0, (void**)&pVtx, 0);

			pVtx += nCutTimer * 4;
			pVtx[0].pos = g_aTimer[nCutTimer].pos;
			pVtx[1].pos = g_aTimer[nCutTimer].pos;
			pVtx[2].pos = g_aTimer[nCutTimer].pos;
			pVtx[3].pos = g_aTimer[nCutTimer].pos;

			g_pVtxBuffTimer->Unlock();
			break;
		}
	}
}


//=============================================================================
// ���_���̍쐬
//=============================================================================
void MakeVertexTimer(LPDIRECT3DDEVICE9 pDevice)
{
	VERTEX_2D *pVtx;
	int nCutVtx;


	//���b�N
	g_pVtxBuffTimer->Lock(0, 0, (void**)&pVtx, 0);

	for (nCutVtx = 0; nCutVtx < MAX_DIGIT; nCutVtx++) {

		//���_���W�̐ݒ�
		pVtx[0].pos.x = g_aTimer[nCutVtx].pos.x;
		pVtx[1].pos.x = g_aTimer[nCutVtx].pos.x + 20;
		pVtx[2].pos.x = g_aTimer[nCutVtx].pos.x;
		pVtx[3].pos.x = g_aTimer[nCutVtx].pos.x + 20;

		pVtx[0].pos.y = g_aTimer[nCutVtx].pos.y;
		pVtx[1].pos.y = g_aTimer[nCutVtx].pos.y;
		pVtx[2].pos.y = g_aTimer[nCutVtx].pos.y + 20;
		pVtx[3].pos.y = g_aTimer[nCutVtx].pos.y + 20;

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
		int iPow = int (powf(10, float( MAX_DIGIT - nCutVtx)));
		float fTime = float( iTime % iPow / (iPow / 10));
		pVtx[0].tex = D3DXVECTOR2(fTime*(1.0f / MAX_PATTEN), 0);
		pVtx[1].tex = D3DXVECTOR2(fTime*(1.0f / MAX_PATTEN) + 1.0f / MAX_PATTEN, 0);
		pVtx[2].tex = D3DXVECTOR2(fTime*(1.0f / MAX_PATTEN), 1);
		pVtx[3].tex = D3DXVECTOR2(fTime*(1.0f / MAX_PATTEN) + 1.0f / MAX_PATTEN, 1);
		pVtx += 4;

	}

	//���b�N����
	g_pVtxBuffTimer->Unlock();
}

void SetTimerKey(bool key) {
	TimeFlag = key;
}

int GetTime(void) {
	return iTime;
}