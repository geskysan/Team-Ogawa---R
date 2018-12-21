//=============================================================================
//
// �e�̏��� [bullet.cpp]
// Author : NAOYA OMORI
//
//=============================================================================
#include "bullet.h"
#include "Explosion.h"
#include "math.h"
#include "sound.h"
#include "ball.h"
#include "enemy.h"
#include "debugproc.h"
#include "wall.h"

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void MakeVertexBullet(LPDIRECT3DDEVICE9 pDevice);
LPDIRECT3DTEXTURE9 g_pTextureBullet = NULL;
LPDIRECT3DVERTEXBUFFER9 g_VexBuffBullet = NULL;
Bullet g_aBullet[MAX_BULLET];	//�e�̑���

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
int g_Count = 0;
bool g_Flag = false;

//=============================================================================
// ����������
//=============================================================================
void InitBullet(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//�����ݒ�
	for (int i = 0; i < MAX_BULLET; i++) {
		g_aBullet[i].move = D3DXVECTOR3(0, 0, 0);
		g_aBullet[i].nLife = 0;
		g_aBullet[i].pos = D3DXVECTOR3(0, 0, 0);
		g_aBullet[i].bUse = false;
	}

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/bullet000.png", &g_pTextureBullet);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_BULLET,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_VexBuffBullet,
		NULL);

	MakeVertexBullet(pDevice);

}

void UninitBullet(void) {

	// ���_�o�b�t�@�̊J��
	if (g_VexBuffBullet != NULL)
	{
		g_VexBuffBullet->Release();
		g_VexBuffBullet = NULL;
	}

	// �e�N�X�`���̊J��
	if (g_pTextureBullet != NULL)
	{
		g_pTextureBullet->Release();
		g_pTextureBullet = NULL;
	}
}
//=============================================================================
//�X�V����
//=============================================================================
void UpdateBullet(void) {

	D3DXVECTOR3 *ePos[MAX_ENEMY];
	VERTEX_2D *pVtx;
	int nCutBullet;

	ePos[0] = GetEnemy();			//�G�̈ʒu���Ƃ��Ă���
	ePos[1] = GetChase();			//�G�̈ʒu���Ƃ��Ă���
	ePos[2] = GetMoody();			//�G�̈ʒu���Ƃ��Ă���
	ePos[3] = GetSilly();			//�G�̈ʒu���Ƃ��Ă���

									//�����������J�E���g�J�n
	if (g_Flag == false) {
		g_Count++;
	}

	//�J�E���g��120�ɒB������ȉ��̏������s��
	if (g_Count == 120) {
		g_Count = 0;				//���Z�b�g
		g_Flag = true;				//Flag��true��
		SetChaseMoveKey(TRUE);		//�G�𓮂��悤�ɂ���
		SetAmbushMoveKey(TRUE);		//�G�𓮂��悤�ɂ���
		SetMoodyMoveKey(TRUE);		//�G�𓮂��悤�ɂ���
		SetSillyMoveKey(TRUE);		//�G�𓮂��悤�ɂ���
	}

	//���b�N
	g_VexBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	for (nCutBullet = 0; nCutBullet < MAX_BULLET; nCutBullet++)
	{
		//�e�ƓG�̓����蔻��
		if (Collision(g_aBullet[nCutBullet].pos, *ePos[0], 10, 20) && g_aBullet[nCutBullet].bUse == true) {
			g_aBullet[nCutBullet].bUse = false;		//���������e������
			SetExplosion(*ePos[0]);					//�G�̈ʒu�ɔ����G�t�F�N�g
			EnemyHit();								//�q�b�g���̓G�̊֐��Ăяo��
			SetAmbushHitKey(TRUE);
		}

		//�e�ƓG�̓����蔻��
		if (Collision(g_aBullet[nCutBullet].pos, *ePos[1], 10, 20) && g_aBullet[nCutBullet].bUse == true) {
			g_aBullet[nCutBullet].bUse = false;		//���������e������
			SetExplosion(*ePos[1]);					//�G�̈ʒu�ɔ����G�t�F�N�g
			SetChaseMoveKey(false);					//�G�𓮂��悤�ɂ���
			g_Flag = false;
			SetChaseHitKey(TRUE);
		}

		//�e�ƓG�̓����蔻��
		if (Collision(g_aBullet[nCutBullet].pos, *ePos[2], 10, 20) && g_aBullet[nCutBullet].bUse == true) {
			g_aBullet[nCutBullet].bUse = false;		//���������e������
			SetExplosion(*ePos[2]);					//�G�̈ʒu�ɔ����G�t�F�N�g
			SetMoodyMoveKey(false);					//�G�𓮂��悤�ɂ���
			g_Flag = false;
			SetMoodyHitKey(TRUE);
		}

		//�e�ƓG�̓����蔻��
		if (Collision(g_aBullet[nCutBullet].pos, *ePos[3], 10, 20) && g_aBullet[nCutBullet].bUse == true) {
			g_aBullet[nCutBullet].bUse = false;		//���������e������
			SetExplosion(*ePos[3]);					//�G�̈ʒu�ɔ����G�t�F�N�g
			SetSillyMoveKey(false);					//�G�𓮂��悤�ɂ���
			g_Flag = false;
			SetSillyHitKey(TRUE);
		}

		//�e��ture�̏ꍇ
		if (g_aBullet[nCutBullet].bUse == true)
		{
			g_aBullet[nCutBullet].pos += g_aBullet[nCutBullet].move;

			g_aBullet[nCutBullet].nLife--;

			// ���_���W�̐ݒ�
			pVtx[0].pos.x = g_aBullet[nCutBullet].pos.x - 10;
			pVtx[1].pos.x = g_aBullet[nCutBullet].pos.x - 10;
			pVtx[2].pos.x = g_aBullet[nCutBullet].pos.x + 10;
			pVtx[3].pos.x = g_aBullet[nCutBullet].pos.x + 10;

			pVtx[0].pos.y = g_aBullet[nCutBullet].pos.y + 10;
			pVtx[1].pos.y = g_aBullet[nCutBullet].pos.y - 10;
			pVtx[2].pos.y = g_aBullet[nCutBullet].pos.y + 10;
			pVtx[3].pos.y = g_aBullet[nCutBullet].pos.y - 10;

			pVtx += 4;

			//��ʊO�ɏo���玩�@�̒e������
			if (g_aBullet[nCutBullet].nLife == 0 || g_aBullet[nCutBullet].pos.y <= 0)
			{
				g_aBullet[nCutBullet].bUse = false;				//�e������
				SetExplosion(g_aBullet[nCutBullet].pos);		//���������Ŕ����G�t�F�N�g���o��
			}
		}
	}
	//���b�N����
	g_VexBuffBullet->Unlock();
}

void DrawBullet(void) {

	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//�f�o�C�X�̎擾

	int nCutBullet;

	//�f�[�^�X�g���[���ɃZ�b�g
	pDevice->SetStreamSource(0,
		g_VexBuffBullet,
		0,
		sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureBullet);

	for (nCutBullet = 0; nCutBullet <MAX_BULLET; nCutBullet++)
	{
		if (g_aBullet[nCutBullet].bUse == true)
		{
			// �|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCutBullet * 4, 2);
		}
	}
}


void SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 move, int nLife) {

	VERTEX_2D *pVtx;
	int nCutBullet;

	for (nCutBullet = 0; nCutBullet < MAX_BULLET; nCutBullet++)
	{
		if (g_aBullet[nCutBullet].bUse == false)
		{
			g_aBullet[nCutBullet].pos = pos;

			//���b�N
			g_VexBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

			// ���_���W�̐ݒ�
			pVtx += nCutBullet * 4;
			pVtx[0].pos = g_aBullet[nCutBullet].pos;
			pVtx[1].pos = g_aBullet[nCutBullet].pos;
			pVtx[2].pos = g_aBullet[nCutBullet].pos;
			pVtx[3].pos = g_aBullet[nCutBullet].pos;

			//���b�N����
			g_VexBuffBullet->Unlock();

			g_aBullet[nCutBullet].move = move;

			g_aBullet[nCutBullet].nLife = nLife;

			g_aBullet[nCutBullet].bUse = true;

			Play(SOUND_LABEL_SE_SHOT000);
			break;
		}
	}
}


//=============================================================================
// ���_���̍쐬
//=============================================================================
void MakeVertexBullet(LPDIRECT3DDEVICE9 pDevice)
{
	VERTEX_2D *pVtx;
	int nCutVtx;

	//���b�N
	g_VexBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	for (nCutVtx = 0; nCutVtx < MAX_BULLET; nCutVtx++) {

		// ���_���W�̐ݒ�
		pVtx[0].pos.x = g_aBullet[nCutVtx].pos.x;
		pVtx[1].pos.x = g_aBullet[nCutVtx].pos.x;
		pVtx[2].pos.x = g_aBullet[nCutVtx].pos.x + 20;
		pVtx[3].pos.x = g_aBullet[nCutVtx].pos.x + 20;

		pVtx[0].pos.y = g_aBullet[nCutVtx].pos.y + 20;
		pVtx[1].pos.y = g_aBullet[nCutVtx].pos.y;
		pVtx[2].pos.y = g_aBullet[nCutVtx].pos.y + 20;
		pVtx[3].pos.y = g_aBullet[nCutVtx].pos.y;

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

		// �e�N�X�`���̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0, 0);
		pVtx[1].tex = D3DXVECTOR2(1, 0);
		pVtx[2].tex = D3DXVECTOR2(0, 1);
		pVtx[3].tex = D3DXVECTOR2(1, 1);
		pVtx += 4;

	}

	//���b�N����
	g_VexBuffBullet->Unlock();
}

void EnemyHit(void) {
	SetAmbushMoveKey(false);		//�G�𓮂��悤�ɂ���
	g_Flag = false;
}