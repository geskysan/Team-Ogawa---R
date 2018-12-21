//=============================================================================
//
// �e�̏��� [bullet.cpp]
// Author : 
//
//=============================================================================
#include "EnemyBullet.h"
#include "Explosion.h"
#include "Enemy.h"
#include "math.h"
#include "number.h"
#include "bullet.h"
#include "life.h"
#include "polygon.h"
#include "sound.h"
//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void MakeVertexEnemyBullet(LPDIRECT3DDEVICE9 pDevice);	//���_���W�쐬

//*****************************************************************************
// �G�̒e�̍\���̒�`
//*****************************************************************************
typedef struct
{
	D3DXVECTOR3 pos;	//�ʒu
	D3DXVECTOR3 move;	//�ړ���
	int nLife;			//����
	bool bUse;			//�g�p���Ă��邩�ǂ���
}EnemyBullet;			//�\���̖�

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
LPDIRECT3DTEXTURE9 g_pTextureEnemyBullet = NULL;		//�G�̒e��
LPDIRECT3DVERTEXBUFFER9 g_VexBuffEnemyBullet = NULL;	//�G�̒e��
EnemyBullet g_aEnemyBullet[MAX_ENEMYBULLET];			//�G�̒e�̑���

//=============================================================================
// ����������
//=============================================================================
void InitEnemyBullet(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//�\���̂̒��g�̏�����
	for (int i = 0; i < MAX_ENEMYBULLET; i++) {
		g_aEnemyBullet[i].move = D3DXVECTOR3(0, 0, 0);	//�ړ���
		g_aEnemyBullet[i].nLife = 0;					//����
		g_aEnemyBullet[i].pos = D3DXVECTOR3(0, 0, 0);	//�ʒu
		g_aEnemyBullet[i].bUse = false;					//�g�p���Ă��邩�ǂ���
	}

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/bullet000.png", &g_pTextureEnemyBullet);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_ENEMYBULLET,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_VexBuffEnemyBullet,
		NULL);

	//���_���W�̌Ăяo��
	MakeVertexEnemyBullet(pDevice);

}
//=============================================================================
// �I������
//=============================================================================
void UninitEnemyBullet(void) {

	if (g_VexBuffEnemyBullet != NULL)
	{
		g_VexBuffEnemyBullet->Release();
		g_VexBuffEnemyBullet = NULL;
	}

	// �e�N�X�`���̊J��
	if (g_pTextureEnemyBullet != NULL) 
	{
		g_pTextureEnemyBullet->Release();
		g_pTextureEnemyBullet = NULL;
	}

}
//=============================================================================
//�X�V����
//=============================================================================
void UpdateEnemyBullet(void) {

	VERTEX_2D *pVtx;
	D3DXVECTOR3 PolygonPos;
	Mine *pMine;
	bool PHit;
	int nCutEnemyBullet;

	pMine = GetMine();

	g_VexBuffEnemyBullet->Lock(0, 0, (void**)&pVtx, 0);
	for (nCutEnemyBullet = 0; nCutEnemyBullet <MAX_ENEMYBULLET; nCutEnemyBullet++)
	{
		PolygonPos = GetMinePos();

		if (g_aEnemyBullet[nCutEnemyBullet].bUse == true)
		{

			g_aEnemyBullet[nCutEnemyBullet].pos += g_aEnemyBullet[nCutEnemyBullet].move;
			g_aEnemyBullet[nCutEnemyBullet].nLife--;


			pVtx[0].pos.x = g_aEnemyBullet[nCutEnemyBullet].pos.x - 10;
			pVtx[1].pos.x = g_aEnemyBullet[nCutEnemyBullet].pos.x - 10;
			pVtx[2].pos.x = g_aEnemyBullet[nCutEnemyBullet].pos.x + 10;
			pVtx[3].pos.x = g_aEnemyBullet[nCutEnemyBullet].pos.x + 10;

			pVtx[0].pos.y = g_aEnemyBullet[nCutEnemyBullet].pos.y + 10;
			pVtx[1].pos.y = g_aEnemyBullet[nCutEnemyBullet].pos.y - 10;
			pVtx[2].pos.y = g_aEnemyBullet[nCutEnemyBullet].pos.y + 10;
			pVtx[3].pos.y = g_aEnemyBullet[nCutEnemyBullet].pos.y - 10;

			//[���_�o�b�t�@�̓��e���X�V]
			if (g_aEnemyBullet[nCutEnemyBullet].nLife == 0 || g_aEnemyBullet[nCutEnemyBullet].pos.y >= SCREEN_HEIGHT)
			{
				g_aEnemyBullet[nCutEnemyBullet].bUse = false;
				//SetExplosion(g_aEnemyBullet[nCutEnemyBullet].pos);
			}

			if (Collision(g_aEnemyBullet[nCutEnemyBullet].pos, PolygonPos, 10, 30) && pMine->bHit == false && pMine->PlayerHP != 0) {	//�G�̒e�Ǝ��@�̓����蔻��
				g_aEnemyBullet[nCutEnemyBullet].bUse = false;							//���@�Ɠ��������e������
				pMine->bHit = (true);
				SubLife(1);
				Play(SOUND_LABEL_SE_HIT001);
			}
		}
		pVtx += 4;
	}
	//�A�����b�N
	g_VexBuffEnemyBullet->Unlock();
}

void DrawEnemyBullet(void) {

	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	int nCutBullet;

	pDevice->SetStreamSource(0,
		g_VexBuffEnemyBullet,
		0,
		sizeof(VERTEX_2D));

	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureEnemyBullet);

	for (nCutBullet = 0; nCutBullet <MAX_ENEMYBULLET; nCutBullet++)
	{
		if (g_aEnemyBullet[nCutBullet].bUse == true)
		{
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCutBullet * 4, 2);
		}
	}
}

void SetEnemyBullet(D3DXVECTOR3 pos, D3DXVECTOR3 move, int nLife) {

	VERTEX_2D *pVtx;
	int nCutEnemyBullet;

	for (nCutEnemyBullet = 0; nCutEnemyBullet < MAX_ENEMYBULLET; nCutEnemyBullet++)
	{
		if (g_aEnemyBullet[nCutEnemyBullet].bUse == false)
		{
			g_aEnemyBullet[nCutEnemyBullet].pos = pos;

			//���b�N
			g_VexBuffEnemyBullet->Lock(0, 0, (void**)&pVtx, 0);

			pVtx += nCutEnemyBullet * 4;
			pVtx[0].pos.x = g_aEnemyBullet[nCutEnemyBullet].pos.x - 10;
			pVtx[1].pos.x = g_aEnemyBullet[nCutEnemyBullet].pos.x - 10;
			pVtx[2].pos.x = g_aEnemyBullet[nCutEnemyBullet].pos.x + 10;
			pVtx[3].pos.x = g_aEnemyBullet[nCutEnemyBullet].pos.x + 10;

			pVtx[0].pos.y = g_aEnemyBullet[nCutEnemyBullet].pos.y + 10;
			pVtx[1].pos.y = g_aEnemyBullet[nCutEnemyBullet].pos.y - 10;
			pVtx[2].pos.y = g_aEnemyBullet[nCutEnemyBullet].pos.y + 10;
			pVtx[3].pos.y = g_aEnemyBullet[nCutEnemyBullet].pos.y - 10;
			g_VexBuffEnemyBullet->Unlock();

			g_aEnemyBullet[nCutEnemyBullet].move = move;
			g_aEnemyBullet[nCutEnemyBullet].nLife = nLife;
			g_aEnemyBullet[nCutEnemyBullet].bUse = true;
			break;
		}
	}
}


//=============================================================================
// ���_���̍쐬
//=============================================================================
void MakeVertexEnemyBullet(LPDIRECT3DDEVICE9 pDevice)
{
	VERTEX_2D *pVtx;
	int nCutVtx;


	//���b�N
	g_VexBuffEnemyBullet->Lock(0, 0, (void**)&pVtx, 0);

	for (nCutVtx = 0; nCutVtx < MAX_ENEMYBULLET; nCutVtx++) {

		pVtx[0].pos.x = g_aEnemyBullet[nCutVtx].pos.x - 20;
		pVtx[1].pos.x = g_aEnemyBullet[nCutVtx].pos.x - 20;
		pVtx[2].pos.x = g_aEnemyBullet[nCutVtx].pos.x + 20;
		pVtx[3].pos.x = g_aEnemyBullet[nCutVtx].pos.x + 20;

		pVtx[0].pos.y = g_aEnemyBullet[nCutVtx].pos.y + 20;
		pVtx[1].pos.y = g_aEnemyBullet[nCutVtx].pos.y - 20;
		pVtx[2].pos.y = g_aEnemyBullet[nCutVtx].pos.y + 20;
		pVtx[3].pos.y = g_aEnemyBullet[nCutVtx].pos.y - 20;

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
	g_VexBuffEnemyBullet->Unlock();

}