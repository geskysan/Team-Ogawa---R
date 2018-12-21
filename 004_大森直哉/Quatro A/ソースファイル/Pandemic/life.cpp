//=============================================================================
//
// �e�̏��� [life.cpp]
// Author : NAOYA OMORI
//
//=============================================================================
#include "Life.h"
#include "polygon.h"

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void MakeVertexLife(LPDIRECT3DDEVICE9 pDevice);

LPDIRECT3DTEXTURE9 g_apTextureLife = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffLife = NULL;
Life g_aLife[MAX_LIFE];

//=============================================================================
// ����������
//=============================================================================
void InitLife(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	int nCutLife;

	//�����ݒ�
	for (nCutLife = 0; nCutLife < MAX_LIFE; nCutLife++)
	{
		g_aLife[nCutLife].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aLife[nCutLife].bUse = false;
	}

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/life000.png", &g_apTextureLife);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_LIFE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffLife,
		NULL);

	for (int y = 0; y < MAX_LIFE; y++)
	{
		SetLife(D3DXVECTOR3(150.0f + 25.0f * y, 0.0f, 0.0f));		//�̗͂̕\��
	}

	MakeVertexLife(pDevice);
}

void UninitLife(void) {

	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffLife != NULL)
	{
		g_pVtxBuffLife->Release();
		g_pVtxBuffLife = NULL;
	}

	// �e�N�X�`���̊J��
	if (g_apTextureLife != NULL) {
		g_apTextureLife->Release();
		g_apTextureLife = NULL;
	}
}

//=============================================================================
//�X�V����
//=============================================================================
void UpdateLife(void)
{

}

void DrawLife(void) {

	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	int nCutLife;
	int playerhp;

	playerhp = GetPlayerHP();	//HP�����擾

								//�f�[�^�X�g���[���ɃZ�b�g
	pDevice->SetStreamSource(0,
		g_pVtxBuffLife,
		0,
		sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_apTextureLife);

	for (nCutLife = 0; nCutLife < playerhp; nCutLife++)
	{
		if (g_aLife[nCutLife].bUse == true)
		{
			// �|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCutLife * 4, 2);
		}
	}
}

void SetLife(D3DXVECTOR3 pos) {

	VERTEX_2D *pVtx;
	int nCutLife;

	for (nCutLife = 0; nCutLife < MAX_LIFE; nCutLife++)
	{
		if (g_aLife[nCutLife].bUse == false)
		{
			g_aLife[nCutLife].pos = pos;
			g_aLife[nCutLife].bUse = true;

			//���b�N
			g_pVtxBuffLife->Lock(0, 0, (void**)&pVtx, 0);

			pVtx += nCutLife * 4;
			pVtx[0].pos = g_aLife[nCutLife].pos;
			pVtx[1].pos = g_aLife[nCutLife].pos;
			pVtx[2].pos = g_aLife[nCutLife].pos;
			pVtx[3].pos = g_aLife[nCutLife].pos;


			g_pVtxBuffLife->Unlock();

			break;
		}
	}
}


//=============================================================================
// ���_���̍쐬
//=============================================================================
void MakeVertexLife(LPDIRECT3DDEVICE9 pDevice)
{
	VERTEX_2D *pVtx;
	int nCutVtx;


	//���b�N
	g_pVtxBuffLife->Lock(0, 0, (void**)&pVtx, 0);

	for (nCutVtx = 0; nCutVtx < MAX_LIFE; nCutVtx++) {

		//���_���W�̐ݒ�
		pVtx[0].pos.x = g_aLife[nCutVtx].pos.x;
		pVtx[1].pos.x = g_aLife[nCutVtx].pos.x;
		pVtx[2].pos.x = g_aLife[nCutVtx].pos.x + 25;
		pVtx[3].pos.x = g_aLife[nCutVtx].pos.x + 25;

		pVtx[0].pos.y = g_aLife[nCutVtx].pos.y + 25;
		pVtx[1].pos.y = g_aLife[nCutVtx].pos.y;
		pVtx[2].pos.y = g_aLife[nCutVtx].pos.y + 25;
		pVtx[3].pos.y = g_aLife[nCutVtx].pos.y;

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

		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0, 1);
		pVtx[1].tex = D3DXVECTOR2(0, 0);
		pVtx[2].tex = D3DXVECTOR2(1, 1);
		pVtx[3].tex = D3DXVECTOR2(1, 0);
		pVtx += 4;
	}

	//���b�N����
	g_pVtxBuffLife->Unlock();
}