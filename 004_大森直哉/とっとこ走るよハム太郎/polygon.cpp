//=============================================================================
//
// �|���S������ [polygon.cpp]
// Author : AKIRA TANAKA
//
//=============================================================================
#include "polygon.h"
#include "input.h"
#include "bullet.h"
#include "enemy.h"
#include "number.h"
#include "explosion.h"
#include "life.h"
#include "fade.h"
#include "Enemybullet.h"
#include "sound.h"
//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void MakeVertexPolygon(LPDIRECT3DDEVICE9 pDevice);

#define MAX_ENEMY (128)

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9	g_pTexturePolygon = NULL;		// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPolygon = NULL;	//���_�o�b�t�@�̃|�C���^

int g_nCounterAnim = 0;
int g_nPatternAnim = 0;
int InvisibleCount = 0;
int KeyFlag;

Mine mine;

//=============================================================================
// ����������
//=============================================================================
void InitPolygon(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D)*4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffPolygon,
		NULL);

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,"data/TEXTURE/player000.png", &g_pTexturePolygon);

	mine.g_posPolygon = D3DXVECTOR3(630, 600, 0);
	mine.g_rotPolygon = D3DXVECTOR3(0, 0, 0);
	mine.g_fAnglePolygon = atan2f(50, 50);
	mine.g_fLengthPolygon = sqrtf(50 * 50 + 50 * 50);
	mine.PlayerHP = MAX_LIFE;
	mine.bUse = true;
	mine.bHit = false;
	KeyFlag = true;

	//���_�ݒ�
	MakeVertexPolygon(pDevice);

}

//=============================================================================
// �I������
//=============================================================================
void UninitPolygon(void)
{
	// �e�N�X�`���̊J��4
	if (g_pVtxBuffPolygon != NULL)
	{
		g_pVtxBuffPolygon->Release();
		g_pVtxBuffPolygon = NULL;
	}
	if (g_pTexturePolygon != NULL)
	{
		g_pTexturePolygon->Release();
		g_pTexturePolygon = NULL;
	}

}
//=============================================================================
// �X�V����
//=============================================================================
void UpdatePolygon(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	Enemy *pEnemy;
	VERTEX_2D *pVtx;
	int move;

	move = 5;

	//���b�N
	g_pVtxBuffPolygon->Lock(0,
		0,
		(void**)&pVtx,
		0);


		// �e�N�X�`�����W�̐ݒ�
		MakeVertexPolygon(pDevice);

		pVtx[0].pos.x = mine.g_posPolygon.x + sinf(-D3DX_PI + mine.g_fAnglePolygon + mine.g_rotPolygon.z)*mine.g_fLengthPolygon;
		pVtx[0].pos.y = mine.g_posPolygon.y + cosf(-D3DX_PI + mine.g_fAnglePolygon + mine.g_rotPolygon.z)*mine.g_fLengthPolygon;
		pVtx[0].pos.z = 0.0f;

		pVtx[1].pos.x = mine.g_posPolygon.x + sinf(3.14 - mine.g_fAnglePolygon + mine.g_rotPolygon.z)*mine.g_fLengthPolygon;
		pVtx[1].pos.y = mine.g_posPolygon.y + cosf(3.14 - mine.g_fAnglePolygon + mine.g_rotPolygon.z)*mine.g_fLengthPolygon;
		pVtx[1].pos.z = 0.0f;

		pVtx[2].pos.x = mine.g_posPolygon.x + sinf(-mine.g_fAnglePolygon + mine.g_rotPolygon.z)*mine.g_fLengthPolygon;
		pVtx[2].pos.y = mine.g_posPolygon.y + cosf(-mine.g_fAnglePolygon + mine.g_rotPolygon.z)*mine.g_fLengthPolygon;
		pVtx[2].pos.z = 0.0f;

		pVtx[3].pos.x = mine.g_posPolygon.x + sinf(mine.g_fAnglePolygon + mine.g_rotPolygon.z)*mine.g_fLengthPolygon;
		pVtx[3].pos.y = mine.g_posPolygon.y + cosf(mine.g_fAnglePolygon + mine.g_rotPolygon.z)*mine.g_fLengthPolygon;
		pVtx[3].pos.z = 0.0f;

	//���b�N����
	g_pVtxBuffPolygon->Unlock();

	if (KeyFlag == true) {

		if (GetKeyboardPress(DIK_W))
			mine.g_posPolygon.y -= move;

		if (GetKeyboardPress(DIK_S))
			mine.g_posPolygon.y += move;

		if (GetKeyboardPress(DIK_A))
			mine.g_posPolygon.x -= move;

		if (GetKeyboardPress(DIK_D))
			mine.g_posPolygon.x += move;

		if (GetKeyboardPress(DIK_LEFT))
			mine.g_rotPolygon.z += 0.05;

		if (GetKeyboardPress(DIK_RIGHT))
			mine.g_rotPolygon.z -= 0.05;

		if (GetKeyboardTrigger(DIK_SPACE))
			SetBullet(mine.g_posPolygon, D3DXVECTOR3(0, -7, 0), 100);
	}

	if (mine.PlayerHP == 0) {
		KeyFlag = false;
		SetFade(MODE_RESULT);				//�Q�[���I�[�o�[����
		mine.bUse = false;
	}

	//�G�̂O�Ԗڂ̏����擾
	pEnemy = GetEnemy();

	for (int nCutEnemy = 0; nCutEnemy < MAX_ENEMY; nCutEnemy++) {
		if (pEnemy->bUse == true) {
			//�v���C���[�ƓG�Ƃ̓����蔻��
			if (mine.bHit == false) {
				if (Collision(pEnemy->pos, mine.g_posPolygon, 10, 30) && mine.PlayerHP != 0)
				{
					mine.bHit = true;
					//pEnemy->bUse = (false);
					EnemyTotal();
					SubLife(1);
					Play(SOUND_LABEL_SE_HIT001);
				}
			}
		}

		pEnemy++;

	}

	if (mine.bHit == true) {
		InvisiblePlayer();
	}

}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawPolygon(void)
{
	if (!mine.bUse)
		return;
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//�f�[�^�X�g���[���ɃZ�b�g
	pDevice->SetStreamSource(0,
		g_pVtxBuffPolygon,
		0,
		sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTexturePolygon);

	// �|���S���̕`��
	pDevice -> DrawPrimitive(D3DPT_TRIANGLESTRIP,0,2);

}

//=============================================================================
// ���_���̍쐬
//=============================================================================
void MakeVertexPolygon(LPDIRECT3DDEVICE9 pDevice)
{

	VERTEX_2D *pVtx;

	//���b�N
	g_pVtxBuffPolygon->Lock(0,
		0,
		(void**)&pVtx,
		0);

	// ���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(0, 0, 0.0f);//xy���W�ňʒu����
	pVtx[1].pos = D3DXVECTOR3(100, 0, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0, 100, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(100, 100, 0.0f);


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
	  
	//���b�N����
	g_pVtxBuffPolygon->Unlock();

}

D3DXVECTOR3 GetMinePos(void) {
	return mine.g_posPolygon;
}

int GetPlayerHP(void) {
	return 	mine.PlayerHP;
}

void SubLife(int Life) {
	mine.PlayerHP -= Life;
}

void InvisiblePlayer(void) {

	if (mine.bUse && InvisibleCount % 5 == 0) {
		mine.bUse = false;
	}
	else if (!mine.bUse && InvisibleCount % 5 == 0) {
		mine.bUse = true;
	}
	InvisibleCount++;
	if (InvisibleCount >= 150)
	{
		InvisibleCount = 0;
		mine.bHit = false;
		mine.bUse = true;
	}
}

Mine *GetMine(void) {
	return &mine;
}