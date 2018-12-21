//=============================================================================
//
// �t�H���g���� [Font.cpp]
// Author : NAOYA OMORI
//
//=============================================================================
#include "font.h"

//*****************************************************************************
// �}�N����`�錾
//*****************************************************************************
#define MAX_FONT_TEX (5)
#define FONT_SIZE_X (200)
#define FONT_SIZE_Y (20)

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void MakeVertexFont(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9 g_apTextureFont[MAX_FONT_TEX] = {};
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffFont = NULL;
Font g_aFont[MAX_FONT];

//=============================================================================
// ����������
//=============================================================================
void InitFont(void)
{

	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	int nCntFont;

	//�����ݒ�
	for (nCntFont = 0; nCntFont < MAX_FONT; nCntFont++) {
		g_aFont[nCntFont].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aFont[nCntFont].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aFont[nCntFont].fAngleFont = atan2f(FONT_SIZE_X / 2, FONT_SIZE_Y / 2);
		g_aFont[nCntFont].fLengthFont = sqrtf((FONT_SIZE_X / 2) * (FONT_SIZE_X / 2) + (FONT_SIZE_Y / 2) * (FONT_SIZE_Y / 2));
		g_aFont[nCntFont].nType = 0;
		g_aFont[nCntFont].bUse = false;
	}

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/lifefont.png", &g_apTextureFont[0]);			//���C�t�̕���
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/timefont.png", &g_apTextureFont[1]);			//�^�C���̕���
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/scorefont.png", &g_apTextureFont[2]);			//�X�R�A�̕���
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/getreadyfont.png", &g_apTextureFont[3]);		//���f�B�̕���
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/bulletfont.png", &g_apTextureFont[4]);			//�o���b�g�̕���

																									//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_FONT,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffFont,
		NULL);

	MakeVertexFont(pDevice);

}

void UninitFont(void) {

	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffFont != NULL)
	{
		g_pVtxBuffFont->Release();
		g_pVtxBuffFont = NULL;
	}

	// �e�N�X�`���̊J��
	for (int nCntEnemy = 0; nCntEnemy < MAX_FONT; nCntEnemy++)
	{
		if (g_apTextureFont[nCntEnemy] != NULL)
		{
			g_apTextureFont[nCntEnemy]->Release();
			g_apTextureFont[nCntEnemy] = NULL;
		}
	}
}

//=============================================================================
//�X�V����
//=============================================================================
void UpdateFont(void) {

	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	VERTEX_2D *pVtx;

	for (int nCntFont = 0; nCntFont < MAX_FONT; nCntFont++)
	{

		//���b�N
		g_pVtxBuffFont->Lock(0, 0, (void**)&pVtx, 0);

		if (g_aFont[nCntFont].bUse == true) {

			pVtx += 4 * nCntFont;

			//���_���W�̐ݒ�
			pVtx[0].pos.x = g_aFont[nCntFont].pos.x - sinf(g_aFont[nCntFont].fAngleFont - g_aFont[nCntFont].rot.z)*g_aFont[nCntFont].fLengthFont;
			pVtx[0].pos.y = g_aFont[nCntFont].pos.y - cosf(g_aFont[nCntFont].fAngleFont - g_aFont[nCntFont].rot.z)*g_aFont[nCntFont].fLengthFont;
			pVtx[0].pos.z = 0.0f;

			pVtx[1].pos.x = g_aFont[nCntFont].pos.x + sinf(g_aFont[nCntFont].fAngleFont + g_aFont[nCntFont].rot.z)*g_aFont[nCntFont].fLengthFont;
			pVtx[1].pos.y = g_aFont[nCntFont].pos.y - cosf(g_aFont[nCntFont].fAngleFont + g_aFont[nCntFont].rot.z)*g_aFont[nCntFont].fLengthFont;
			pVtx[1].pos.z = 0.0f;

			pVtx[2].pos.x = g_aFont[nCntFont].pos.x - sinf(g_aFont[nCntFont].fAngleFont + g_aFont[nCntFont].rot.z)*g_aFont[nCntFont].fLengthFont;
			pVtx[2].pos.y = g_aFont[nCntFont].pos.y + cosf(g_aFont[nCntFont].fAngleFont + g_aFont[nCntFont].rot.z)*g_aFont[nCntFont].fLengthFont;
			pVtx[2].pos.z = 0.0f;

			pVtx[3].pos.x = g_aFont[nCntFont].pos.x + sinf(g_aFont[nCntFont].fAngleFont - g_aFont[nCntFont].rot.z)*g_aFont[nCntFont].fLengthFont;
			pVtx[3].pos.y = g_aFont[nCntFont].pos.y + cosf(g_aFont[nCntFont].fAngleFont - g_aFont[nCntFont].rot.z)*g_aFont[nCntFont].fLengthFont;
			pVtx[3].pos.z = 0.0f;

			//���b�N����
			g_pVtxBuffFont->Unlock();
		}
	}
}

void DrawFont(void) {

	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	int nCntFont;

	// �e�N�X�`���̐ݒ�
	for (nCntFont = 0; nCntFont < MAX_FONT; nCntFont++)
	{
		if (g_aFont[nCntFont].bUse == true)
		{

			//�f�[�^�X�g���[���ɃZ�b�g
			pDevice->SetStreamSource(0,
				g_pVtxBuffFont,
				0,
				sizeof(VERTEX_2D));

			// ���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_2D);

			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_apTextureFont[g_aFont[nCntFont].nType]);

			// �|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntFont * 4, 2);

		}
	}
}


void SetFont(D3DXVECTOR3 pos, int nType) {

	int nCntFont;

	for (nCntFont = 0; nCntFont < MAX_FONT; nCntFont++)
	{
		if (g_aFont[nCntFont].bUse == false)
		{
			g_aFont[nCntFont].pos = pos;
			g_aFont[nCntFont].nType = nType;
			g_aFont[nCntFont].bUse = true;
			break;
		}
	}
}

//=============================================================================
// ���_���̍쐬
//=============================================================================
void MakeVertexFont(LPDIRECT3DDEVICE9 pDevice)
{
	VERTEX_2D *pVtx;
	int nCutVtx;

	//���b�N
	g_pVtxBuffFont->Lock(0, 0, (void**)&pVtx, 0);

	for (nCutVtx = 0; nCutVtx < MAX_FONT; nCutVtx++) {

		//���_���W�̐ݒ�
		pVtx[0].pos.x = g_aFont[nCutVtx].pos.x - sinf(g_aFont[nCutVtx].fAngleFont - g_aFont[nCutVtx].rot.z)*g_aFont[nCutVtx].fLengthFont;
		pVtx[0].pos.y = g_aFont[nCutVtx].pos.y - cosf(g_aFont[nCutVtx].fAngleFont - g_aFont[nCutVtx].rot.z)*g_aFont[nCutVtx].fLengthFont;
		pVtx[0].pos.z = 0.0f;

		pVtx[1].pos.x = g_aFont[nCutVtx].pos.x + sinf(g_aFont[nCutVtx].fAngleFont + g_aFont[nCutVtx].rot.z)*g_aFont[nCutVtx].fLengthFont;
		pVtx[1].pos.y = g_aFont[nCutVtx].pos.y - cosf(g_aFont[nCutVtx].fAngleFont + g_aFont[nCutVtx].rot.z)*g_aFont[nCutVtx].fLengthFont;
		pVtx[1].pos.z = 0.0f;

		pVtx[2].pos.x = g_aFont[nCutVtx].pos.x - sinf(g_aFont[nCutVtx].fAngleFont + g_aFont[nCutVtx].rot.z)*g_aFont[nCutVtx].fLengthFont;
		pVtx[2].pos.y = g_aFont[nCutVtx].pos.y + cosf(g_aFont[nCutVtx].fAngleFont + g_aFont[nCutVtx].rot.z)*g_aFont[nCutVtx].fLengthFont;
		pVtx[2].pos.z = 0.0f;

		pVtx[3].pos.x = g_aFont[nCutVtx].pos.x + sinf(g_aFont[nCutVtx].fAngleFont - g_aFont[nCutVtx].rot.z)*g_aFont[nCutVtx].fLengthFont;
		pVtx[3].pos.y = g_aFont[nCutVtx].pos.y + cosf(g_aFont[nCutVtx].fAngleFont - g_aFont[nCutVtx].rot.z)*g_aFont[nCutVtx].fLengthFont;
		pVtx[3].pos.z = 0.0f;

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
		pVtx[0].tex = D3DXVECTOR2(0, 0);
		pVtx[1].tex = D3DXVECTOR2(1, 0);
		pVtx[2].tex = D3DXVECTOR2(0, 1);
		pVtx[3].tex = D3DXVECTOR2(1, 1);
		pVtx += 4;

	}

	//���b�N����
	g_pVtxBuffFont->Unlock();

}

//�g�����g��Ȃ���
void SetUse(bool use) {
	g_aFont[3].bUse = use;
}