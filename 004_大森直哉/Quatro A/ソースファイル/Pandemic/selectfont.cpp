//=============================================================================
//
// �Z���N�g�t�H���g�̏��� [Selectfont.cpp]
// Author :  NAOYA OMORI
//
//=============================================================================
#include "Selectfont.h"
#include "Titlearrow.h"

//*****************************************************************************
// �}�N����`�錾
//*****************************************************************************
#define MAX_SELECTFONT_TEX (3)
#define SELECTFONT_SIZE_X (250)
#define SELECTFONT_SIZE_Y (25)

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void MakeVertexSelectFont(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9 g_apTextureSelectfont[MAX_SELECTFONT_TEX] = {};
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffSelectfont = NULL;
Selectfont g_aSelectfont[MAX_SELECTFONT];

float g_leftVtxPosX = 0.0f;

//=============================================================================
// ����������
//=============================================================================
void InitSelectfont(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	int nCntSelectfont;

	for (nCntSelectfont = 0; nCntSelectfont < MAX_SELECTFONT; nCntSelectfont++) {
		g_aSelectfont[nCntSelectfont].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aSelectfont[nCntSelectfont].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aSelectfont[nCntSelectfont].fAngleSelectfont = atan2f(SELECTFONT_SIZE_X / 2, SELECTFONT_SIZE_Y / 2);
		g_aSelectfont[nCntSelectfont].fLengthSelectfont = sqrtf((SELECTFONT_SIZE_X / 2) * (SELECTFONT_SIZE_X / 2) + (SELECTFONT_SIZE_Y / 2) * (SELECTFONT_SIZE_Y / 2));
		g_aSelectfont[nCntSelectfont].nType = 0;
		g_aSelectfont[nCntSelectfont].bUse = false;
	}

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/StartGameFont.png", &g_apTextureSelectfont[0]);		//�Q�[���X�^�[�g�̕���
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/TutorialFont.png", &g_apTextureSelectfont[1]);			//�`���[�g���A���̕���
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/QuitGameFont.png", &g_apTextureSelectfont[2]);			//�N�C�b�g�Q�[���̕���


																											//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_SELECTFONT,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffSelectfont,
		NULL);

	MakeVertexSelectFont(pDevice);

}

//=============================================================================
// �I������
//=============================================================================
void UninitSelectfont(void) {

	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffSelectfont != NULL)
	{
		g_pVtxBuffSelectfont->Release();
		g_pVtxBuffSelectfont = NULL;
	}

	// �e�N�X�`���̊J��
	for (int nCntEnemy = 0; nCntEnemy < MAX_SELECTFONT; nCntEnemy++)
	{
		if (g_apTextureSelectfont[nCntEnemy] != NULL)
		{
			g_apTextureSelectfont[nCntEnemy]->Release();
			g_apTextureSelectfont[nCntEnemy] = NULL;
		}
	}

}

//=============================================================================
//�X�V����
//=============================================================================
void UpdateSelectfont(void)
{

}

void DrawSelectfont(void) {

	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	int nCntSelectfont;

	pDevice->SetStreamSource(0,
		g_pVtxBuffSelectfont,
		0,
		sizeof(VERTEX_2D));

	// �e�N�X�`���̐ݒ�
	for (nCntSelectfont = 0; nCntSelectfont < MAX_SELECTFONT; nCntSelectfont++)
	{
		if (g_aSelectfont[nCntSelectfont].bUse == true)
		{

	pDevice->SetFVF(FVF_VERTEX_2D);

			pDevice->SetTexture(0, g_apTextureSelectfont[g_aSelectfont[nCntSelectfont].nType]);

			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntSelectfont * 4, 2);
		}
	}
}

void SetSelectfont(D3DXVECTOR3 pos, int nType) {

	int nCntSelectfont;
	VERTEX_2D *pVtx;

	g_leftVtxPosX = pos.x - SELECTFONT_SIZE_X / 2.0f;

	for (nCntSelectfont = 0; nCntSelectfont < MAX_SELECTFONT; nCntSelectfont++)
	{
		if (g_aSelectfont[nCntSelectfont].bUse == false)
		{
			g_aSelectfont[nCntSelectfont].pos = pos;
			g_aSelectfont[nCntSelectfont].nType = nType;
			g_aSelectfont[nCntSelectfont].bUse = true;

			g_pVtxBuffSelectfont->Lock(0, 0, (void**)&pVtx, 0);

			pVtx += 4 * nCntSelectfont;
			pVtx[0].pos.x = g_aSelectfont[nCntSelectfont].pos.x - sinf(g_aSelectfont[nCntSelectfont].fAngleSelectfont - g_aSelectfont[nCntSelectfont].rot.z)*g_aSelectfont[nCntSelectfont].fLengthSelectfont;
			pVtx[0].pos.y = g_aSelectfont[nCntSelectfont].pos.y - cosf(g_aSelectfont[nCntSelectfont].fAngleSelectfont - g_aSelectfont[nCntSelectfont].rot.z)*g_aSelectfont[nCntSelectfont].fLengthSelectfont;
			pVtx[0].pos.z = 0.0f;

			pVtx[1].pos.x = g_aSelectfont[nCntSelectfont].pos.x + sinf(g_aSelectfont[nCntSelectfont].fAngleSelectfont + g_aSelectfont[nCntSelectfont].rot.z)*g_aSelectfont[nCntSelectfont].fLengthSelectfont;
			pVtx[1].pos.y = g_aSelectfont[nCntSelectfont].pos.y - cosf(g_aSelectfont[nCntSelectfont].fAngleSelectfont + g_aSelectfont[nCntSelectfont].rot.z)*g_aSelectfont[nCntSelectfont].fLengthSelectfont;
			pVtx[1].pos.z = 0.0f;

			pVtx[2].pos.x = g_aSelectfont[nCntSelectfont].pos.x - sinf(g_aSelectfont[nCntSelectfont].fAngleSelectfont + g_aSelectfont[nCntSelectfont].rot.z)*g_aSelectfont[nCntSelectfont].fLengthSelectfont;
			pVtx[2].pos.y = g_aSelectfont[nCntSelectfont].pos.y + cosf(g_aSelectfont[nCntSelectfont].fAngleSelectfont + g_aSelectfont[nCntSelectfont].rot.z)*g_aSelectfont[nCntSelectfont].fLengthSelectfont;
			pVtx[2].pos.z = 0.0f;

			pVtx[3].pos.x = g_aSelectfont[nCntSelectfont].pos.x + sinf(g_aSelectfont[nCntSelectfont].fAngleSelectfont - g_aSelectfont[nCntSelectfont].rot.z)*g_aSelectfont[nCntSelectfont].fLengthSelectfont;
			pVtx[3].pos.y = g_aSelectfont[nCntSelectfont].pos.y + cosf(g_aSelectfont[nCntSelectfont].fAngleSelectfont - g_aSelectfont[nCntSelectfont].rot.z)*g_aSelectfont[nCntSelectfont].fLengthSelectfont;
			pVtx[3].pos.z = 0.0f;

			g_pVtxBuffSelectfont->Unlock();
			break;
		}
	}
}

//=============================================================================
// ���_���̍쐬
//=============================================================================
void MakeVertexSelectFont(LPDIRECT3DDEVICE9 pDevice)
{
	VERTEX_2D *pVtx;
	int nCutVtx;

	//���b�N
	g_pVtxBuffSelectfont->Lock(0, 0, (void**)&pVtx, 0);

	for (nCutVtx = 0; nCutVtx < MAX_SELECTFONT; nCutVtx++) {

		pVtx[0].pos.x = g_aSelectfont[nCutVtx].pos.x - sinf(g_aSelectfont[nCutVtx].fAngleSelectfont - g_aSelectfont[nCutVtx].rot.z)*g_aSelectfont[nCutVtx].fLengthSelectfont;
		pVtx[0].pos.y = g_aSelectfont[nCutVtx].pos.y - cosf(g_aSelectfont[nCutVtx].fAngleSelectfont - g_aSelectfont[nCutVtx].rot.z)*g_aSelectfont[nCutVtx].fLengthSelectfont;
		pVtx[0].pos.z = 0.0f;

		pVtx[1].pos.x = g_aSelectfont[nCutVtx].pos.x + sinf(g_aSelectfont[nCutVtx].fAngleSelectfont + g_aSelectfont[nCutVtx].rot.z)*g_aSelectfont[nCutVtx].fLengthSelectfont;
		pVtx[1].pos.y = g_aSelectfont[nCutVtx].pos.y - cosf(g_aSelectfont[nCutVtx].fAngleSelectfont + g_aSelectfont[nCutVtx].rot.z)*g_aSelectfont[nCutVtx].fLengthSelectfont;
		pVtx[1].pos.z = 0.0f;

		pVtx[2].pos.x = g_aSelectfont[nCutVtx].pos.x - sinf(g_aSelectfont[nCutVtx].fAngleSelectfont + g_aSelectfont[nCutVtx].rot.z)*g_aSelectfont[nCutVtx].fLengthSelectfont;
		pVtx[2].pos.y = g_aSelectfont[nCutVtx].pos.y + cosf(g_aSelectfont[nCutVtx].fAngleSelectfont + g_aSelectfont[nCutVtx].rot.z)*g_aSelectfont[nCutVtx].fLengthSelectfont;
		pVtx[2].pos.z = 0.0f;

		pVtx[3].pos.x = g_aSelectfont[nCutVtx].pos.x + sinf(g_aSelectfont[nCutVtx].fAngleSelectfont - g_aSelectfont[nCutVtx].rot.z)*g_aSelectfont[nCutVtx].fLengthSelectfont;
		pVtx[3].pos.y = g_aSelectfont[nCutVtx].pos.y + cosf(g_aSelectfont[nCutVtx].fAngleSelectfont - g_aSelectfont[nCutVtx].rot.z)*g_aSelectfont[nCutVtx].fLengthSelectfont;
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

		pVtx[0].tex = D3DXVECTOR2(0, 0);
		pVtx[1].tex = D3DXVECTOR2(1, 0);
		pVtx[2].tex = D3DXVECTOR2(0, 1);
		pVtx[3].tex = D3DXVECTOR2(1, 1);

		pVtx += 4;

	}

	//���b�N����
	g_pVtxBuffSelectfont->Unlock();

}

void MoveFont(int type, float time) {

	VERTEX_2D *pVtx;
	float tex;

	tex = ARROW_SPEED;

	//���b�N
	g_pVtxBuffSelectfont->Lock(0, 0, (void**)&pVtx, 0);
	pVtx += 4 * type;

	if (pVtx[0].pos.x <= pVtx[1].pos.x)
	{
		pVtx[0].pos.x = g_leftVtxPosX + SELECTFONT_SIZE_X * time;
		pVtx[2].pos.x = g_leftVtxPosX + SELECTFONT_SIZE_X * time;

		pVtx[0].tex.x = time;
		pVtx[2].tex.x = time;

	}
	//���b�N����
	g_pVtxBuffSelectfont->Unlock();
}