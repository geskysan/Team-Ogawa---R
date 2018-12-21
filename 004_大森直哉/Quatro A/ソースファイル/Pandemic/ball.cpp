//=============================================================================
//
// �{�[������ [ball.cpp]
// Author : NAOYA OMORI
//
//=============================================================================
#include "ball.h"
#include "polygon.h"
#include "explosion.h"
#include "DebugProc.h"
#include "input.h"
#include "sound.h"
//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void MakeVertexBall(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// �}�N����`�錾
//*****************************************************************************
#define MAX_BALL	(135)
#define BALL_SIZE_X	(30)
#define BALL_SIZE_Y (30)

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9	g_pTextureBall = NULL;	// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBall = NULL;//���_�o�b�t�@�̃|�C���^
BALL g_ball[MAX_BALL];

int g_BallCount;		//�{�[���̐��𐔂���ϐ�
int g_ScoreCount;		//�X�R�A�𐔂���ϐ�
int g_BulletCounter;	//�e�i�o���b�g�j�̐�����ϐ�
int g_BulletCount;		//BulletCounter��ύX���邽�߂̕ϐ�

//=============================================================================
// ����������
//=============================================================================
void InitBall(void)
{

	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//�e�̏����ݒ�
	for (int nCntBall = 0; nCntBall < MAX_BALL; nCntBall++) {
		g_ball[nCntBall].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_ball[nCntBall].rot = D3DXVECTOR3(0, 0, 0);
		g_ball[nCntBall].fAngleBall = atan2f(BALL_SIZE_X / 2, BALL_SIZE_Y / 2);
		g_ball[nCntBall].fLengthBall = sqrtf((BALL_SIZE_X / 2) * (BALL_SIZE_X / 2) + (BALL_SIZE_Y / 2) * (BALL_SIZE_Y / 2));
		g_ball[nCntBall].bUse = false;
	}

	//�ϐ��̏����ݒ�
	g_ScoreCount = 0;
	g_BallCount = 0;
	g_BulletCount = 0;
	g_BulletCounter = 0;

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_BALL,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBall,
		NULL);

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/ball.png", &g_pTextureBall);

	//���_�ݒ�
	MakeVertexBall(pDevice);

}

//=============================================================================
// �I������
//=============================================================================
void UninitBall(void)
{
	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffBall != NULL)
	{
		g_pVtxBuffBall->Release();
		g_pVtxBuffBall = NULL;
	}

	// �e�N�X�`���̊J��
	if (g_pTextureBall != NULL)
	{
		g_pTextureBall->Release();
		g_pTextureBall = NULL;
	}

}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateBall(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXVECTOR3 PlayerPos;	//���@�̈ʒu�p
	VERTEX_2D *pVtx;
	int nCntBall;

	PlayerPos = GetMinePos();	//�v���C���[�̃|�W�V�����������Ă���B

	for (nCntBall = 0; nCntBall < MAX_BALL; nCntBall++) {
		if (g_ball[nCntBall].bUse == true) {

			//���b�N
			g_pVtxBuffBall->Lock(0, 0, (void**)&pVtx, 0);

			pVtx += 4 * nCntBall;

			// ���_���W�̐ݒ�
			pVtx[0].pos.x = g_ball[nCntBall].pos.x - sinf(g_ball[nCntBall].fAngleBall - g_ball[nCntBall].rot.z)*g_ball[nCntBall].fLengthBall;
			pVtx[0].pos.y = g_ball[nCntBall].pos.y - cosf(g_ball[nCntBall].fAngleBall - g_ball[nCntBall].rot.z)*g_ball[nCntBall].fLengthBall;
			pVtx[0].pos.z = 0.0f;

			pVtx[1].pos.x = g_ball[nCntBall].pos.x + sinf(g_ball[nCntBall].fAngleBall + g_ball[nCntBall].rot.z)*g_ball[nCntBall].fLengthBall;
			pVtx[1].pos.y = g_ball[nCntBall].pos.y - cosf(g_ball[nCntBall].fAngleBall + g_ball[nCntBall].rot.z)*g_ball[nCntBall].fLengthBall;
			pVtx[1].pos.z = 0.0f;

			pVtx[2].pos.x = g_ball[nCntBall].pos.x - sinf(g_ball[nCntBall].fAngleBall + g_ball[nCntBall].rot.z)*g_ball[nCntBall].fLengthBall;
			pVtx[2].pos.y = g_ball[nCntBall].pos.y + cosf(g_ball[nCntBall].fAngleBall + g_ball[nCntBall].rot.z)*g_ball[nCntBall].fLengthBall;
			pVtx[2].pos.z = 0.0f;

			pVtx[3].pos.x = g_ball[nCntBall].pos.x + sinf(g_ball[nCntBall].fAngleBall - g_ball[nCntBall].rot.z)*g_ball[nCntBall].fLengthBall;
			pVtx[3].pos.y = g_ball[nCntBall].pos.y + cosf(g_ball[nCntBall].fAngleBall - g_ball[nCntBall].rot.z)*g_ball[nCntBall].fLengthBall;
			pVtx[3].pos.z = 0.0f;

			//�����i�A�����b�N�j
			g_pVtxBuffBall->Unlock();

			//�ʂƃv���C���[�̐ڐG���̓����蔻��
			if (Collision(g_ball[nCntBall].pos, PlayerPos, 10, 20)) {
				g_ball[nCntBall].bUse = false;
				g_ScoreCount += 10;
				g_BulletCounter += 1;
				BallTotal();
				Play(SOUND_LABEL_SE_EATING);
			}
		}
	}

	//�ʂ��P�O�Ƃ�ƒe�̐�����1������悤��
	if (g_BulletCounter == 10) {
		g_BulletCount += 1;
		g_BulletCounter = 0;
	}

	//�������O�ȉ��ɂȂ�Ȃ��悤��
	if (g_BulletCount <= 0) {
		g_BulletCount = 0;
	}

	PrintDebug("\n");
	PrintDebug("\n");
	PrintDebug("�ʂ̐��F%d\n", g_BallCount);
	PrintDebug("testcount:%d\n", g_BulletCounter);

}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawBall(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	int nCntBall;

	for (nCntBall = 0; nCntBall < MAX_BALL; nCntBall++) {

		if (g_ball[nCntBall].bUse == true) {

			//�f�[�^�X�g���[���ɃZ�b�g
			pDevice->SetStreamSource(0,
				g_pVtxBuffBall,
				0,
				sizeof(VERTEX_2D));

			// ���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_2D);

			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureBall);

			// �|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntBall * 4, 2);
		}
	}

}

//=============================================================================
// ���_���̍쐬
//=============================================================================
void MakeVertexBall(LPDIRECT3DDEVICE9 pDevice)
{
	VERTEX_2D *pVtx;
	int nCutVtx;

	//���b�N
	g_pVtxBuffBall->Lock(0, 0, (void**)&pVtx, 0);

	for (nCutVtx = 0; nCutVtx < MAX_BALL; nCutVtx++) {

		// ���_���W�̐ݒ�
		pVtx[0].pos.x = g_ball[nCutVtx].pos.x - sinf(g_ball[nCutVtx].fAngleBall - g_ball[nCutVtx].rot.z)*g_ball[nCutVtx].fLengthBall;
		pVtx[0].pos.y = g_ball[nCutVtx].pos.y - cosf(g_ball[nCutVtx].fAngleBall - g_ball[nCutVtx].rot.z)*g_ball[nCutVtx].fLengthBall;
		pVtx[0].pos.z = 0.0f;

		pVtx[1].pos.x = g_ball[nCutVtx].pos.x + sinf(g_ball[nCutVtx].fAngleBall + g_ball[nCutVtx].rot.z)*g_ball[nCutVtx].fLengthBall;
		pVtx[1].pos.y = g_ball[nCutVtx].pos.y - cosf(g_ball[nCutVtx].fAngleBall + g_ball[nCutVtx].rot.z)*g_ball[nCutVtx].fLengthBall;
		pVtx[1].pos.z = 0.0f;

		pVtx[2].pos.x = g_ball[nCutVtx].pos.x - sinf(g_ball[nCutVtx].fAngleBall + g_ball[nCutVtx].rot.z)*g_ball[nCutVtx].fLengthBall;
		pVtx[2].pos.y = g_ball[nCutVtx].pos.y + cosf(g_ball[nCutVtx].fAngleBall + g_ball[nCutVtx].rot.z)*g_ball[nCutVtx].fLengthBall;
		pVtx[2].pos.z = 0.0f;

		pVtx[3].pos.x = g_ball[nCutVtx].pos.x + sinf(g_ball[nCutVtx].fAngleBall - g_ball[nCutVtx].rot.z)*g_ball[nCutVtx].fLengthBall;
		pVtx[3].pos.y = g_ball[nCutVtx].pos.y + cosf(g_ball[nCutVtx].fAngleBall - g_ball[nCutVtx].rot.z)*g_ball[nCutVtx].fLengthBall;
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

		// �e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0, 1);
		pVtx[1].tex = D3DXVECTOR2(0, 0);
		pVtx[2].tex = D3DXVECTOR2(1, 1);
		pVtx[3].tex = D3DXVECTOR2(1, 0);
		pVtx += 4;
	}

	//���b�N����
	g_pVtxBuffBall->Unlock();
}


//�{�[������ׂ邽�߂̏���
void SetBall(D3DXVECTOR3 pos) {

	int nCntBall;

	for (nCntBall = 0; nCntBall < MAX_BALL; nCntBall++) {

		if (g_ball[nCntBall].bUse == false)
		{
			g_ball[nCntBall].pos = pos;
			g_ball[nCntBall].bUse = true;
			g_BallCount++;
			break;
		}
	}
}

//�ǂ��ł��g���邠���蔻��̊�{�i�~ver�j
bool Collision(D3DXVECTOR3 C1, D3DXVECTOR3 C2, float R1, float R2) {
	double dx, dy, dr;
	dx = fabs(C1.x - C2.x);
	dy = fabs(C1.y - C2.y);
	dr = R1 + R2;
	if (dx * 2 + dy * 2 <= dr * 2)
		return true;
	else
		return false;
}

int GetBallCount(void) {
	return g_BallCount;
}

void BallTotal(void) {
	g_BallCount--;
}

int GetScore(void) {
	return g_ScoreCount;
}

int GetBulletCount(void) {
	return g_BulletCount;
}

void SubBulletCount(int number) {
	g_BulletCount -= number;
}
