//=============================================================================
//
// �����A�j���[�V�������� [Explosion.cpp]
// Author : NAOYA OMORI
//
//=============================================================================
#include "Explosion.h"
#include "sound.h"

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void MakeVertexExplosion(LPDIRECT3DDEVICE9 pDevice);

#define MAX_ANIM	8

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_apTextureExplosion;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffExplosion = NULL;
Explosion g_aExplosion[128];

//=============================================================================
// ����������
//=============================================================================
void InitExplosion(void)
{

	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	int nCutExp;

	//�����ݒ�
	for (nCutExp = 0; nCutExp < 128; nCutExp++) {
		g_aExplosion[nCutExp].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aExplosion[nCutExp].bUse = false;
		g_aExplosion[nCutExp].nCounterAnim = 0;
		g_aExplosion[nCutExp].nPatternAnim = 0;
	}

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/explosion000.png", &g_apTextureExplosion);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * 128,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffExplosion,
		NULL);

	MakeVertexExplosion(pDevice);

}

void UninitExplosion(void) {

	// �e�N�X�`���̊J��
	if (g_apTextureExplosion != NULL) {
		g_apTextureExplosion->Release();
		g_apTextureExplosion = NULL;
	}

	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffExplosion != NULL) {
		g_pVtxBuffExplosion->Release();
		g_pVtxBuffExplosion = NULL;
	}
}

//=============================================================================
//�X�V����
//=============================================================================
void UpdateExplosion(void) {

	VERTEX_2D *pVtx;
	int nCutEnemy;

	//���b�N
	g_pVtxBuffExplosion->Lock(0, 0, (void**)&pVtx, 0);

	for (nCutEnemy = 0; nCutEnemy <128; nCutEnemy++)
	{
		if (g_aExplosion[nCutEnemy].bUse == true)
		{

			if (g_aExplosion[nCutEnemy].nCounterAnim % 10 == 0) {

				g_aExplosion[nCutEnemy].nCounterAnim = 0;
				g_aExplosion[nCutEnemy].nPatternAnim++;

			}

			//�e�N�X�`�����W�̐ݒ�
			pVtx[0].tex = D3DXVECTOR2(g_aExplosion[nCutEnemy].nPatternAnim *(1.0f / MAX_ANIM), 1);
			pVtx[1].tex = D3DXVECTOR2(g_aExplosion[nCutEnemy].nPatternAnim*(1.0f / MAX_ANIM), 0);
			pVtx[2].tex = D3DXVECTOR2(g_aExplosion[nCutEnemy].nPatternAnim *(1.0f / MAX_ANIM) + 1.f / MAX_ANIM, 1);
			pVtx[3].tex = D3DXVECTOR2(g_aExplosion[nCutEnemy].nPatternAnim*(1.0f / MAX_ANIM) + 1.f / MAX_ANIM, 0);

			g_aExplosion[nCutEnemy].nCounterAnim++;

		}
		if (g_aExplosion[nCutEnemy].nPatternAnim == MAX_ANIM) {
			g_aExplosion[nCutEnemy].bUse = false;
		}
		pVtx += 4;
	}
	//���b�N����
	g_pVtxBuffExplosion->Unlock();
}

void DrawExplosion(void) {

	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//�f�[�^�X�g���[���ɃZ�b�g
	pDevice->SetStreamSource(0,
		g_pVtxBuffExplosion,
		0,
		sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nMori = 0; nMori < 128; nMori++)
	{
		if (g_aExplosion[nMori].bUse)
		{
			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_apTextureExplosion);
			// �|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nMori * 4, 2);
		}
	}
}

void SetExplosion(D3DXVECTOR3 pos) {

	VERTEX_2D *pVtx;
	int nCutEnemy;

	for (nCutEnemy = 0; nCutEnemy < 128; nCutEnemy++)
	{
		if (g_aExplosion[nCutEnemy].bUse == false)
		{
			g_aExplosion[nCutEnemy].pos = pos;
			g_aExplosion[nCutEnemy].bUse = true;
			g_aExplosion[nCutEnemy].nCounterAnim = 0;
			g_aExplosion[nCutEnemy].nPatternAnim = 0;

			//���b�N
			g_pVtxBuffExplosion->Lock(0, 0, (void**)&pVtx, 0);

			pVtx += nCutEnemy * 4;

			// ���_���W�̐ݒ�
			pVtx[0].pos.x = g_aExplosion[nCutEnemy].pos.x - 30;
			pVtx[1].pos.x = g_aExplosion[nCutEnemy].pos.x - 30;
			pVtx[2].pos.x = g_aExplosion[nCutEnemy].pos.x + 30;
			pVtx[3].pos.x = g_aExplosion[nCutEnemy].pos.x + 30;

			pVtx[0].pos.y = g_aExplosion[nCutEnemy].pos.y + 30;
			pVtx[1].pos.y = g_aExplosion[nCutEnemy].pos.y - 30;
			pVtx[2].pos.y = g_aExplosion[nCutEnemy].pos.y + 30;
			pVtx[3].pos.y = g_aExplosion[nCutEnemy].pos.y - 30;

			//���b�N����
			g_pVtxBuffExplosion->Unlock();

			Play(SOUND_LABEL_SE_EXPLOSION000);

			break;
		}
	}
}


//=============================================================================
// ���_���̍쐬
//=============================================================================
void MakeVertexExplosion(LPDIRECT3DDEVICE9 pDevice)
{
	VERTEX_2D *pVtx;
	int nCutVtx;

	//���b�N
	g_pVtxBuffExplosion->Lock(0, 0, (void**)&pVtx, 0);

	for (nCutVtx = 0; nCutVtx < 128; nCutVtx++) {

		// ���_���W�̐ݒ�
		pVtx[0].pos.x = g_aExplosion[nCutVtx].pos.x;
		pVtx[1].pos.x = g_aExplosion[nCutVtx].pos.x;
		pVtx[2].pos.x = g_aExplosion[nCutVtx].pos.x + 100;
		pVtx[3].pos.x = g_aExplosion[nCutVtx].pos.x + 100;

		pVtx[0].pos.y = g_aExplosion[nCutVtx].pos.y + 100;
		pVtx[1].pos.y = g_aExplosion[nCutVtx].pos.y;
		pVtx[2].pos.y = g_aExplosion[nCutVtx].pos.y + 100;
		pVtx[3].pos.y = g_aExplosion[nCutVtx].pos.y;

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
		pVtx[0].tex = D3DXVECTOR2(float (g_aExplosion[nCutVtx].nPatternAnim / MAX_ANIM), 1);
		pVtx[1].tex = D3DXVECTOR2(float (g_aExplosion[nCutVtx].nPatternAnim / MAX_ANIM), 0);
		pVtx[2].tex = D3DXVECTOR2(float (g_aExplosion[nCutVtx].nPatternAnim / MAX_ANIM + 1.f / MAX_ANIM), 1);
		pVtx[3].tex = D3DXVECTOR2(float (g_aExplosion[nCutVtx].nPatternAnim / MAX_ANIM + 1.f / MAX_ANIM), 0);
		pVtx += 4;

	}

	//���b�N����
	g_pVtxBuffExplosion->Unlock();

}
