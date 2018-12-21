//=============================================================================
//
// �����L���O�����i�`����܂ށj[RankingScore.cpp]
// Author : NAOYA OMORI
//
//=============================================================================
#include "RankingScore.h"
#include "number.h"
#include "main.h"
#include "ball.h"
#include "timer.h"
#include "polygon.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAX_DIGIT	(8)		//����
#define MAX_RANKING (5)		//�l�̐��܂ŕ\��
#define MAX_PATTEN	(10)	//0�`9�܂�

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void MakeVertexRankingScore(LPDIRECT3DDEVICE9 pDevice);
LPDIRECT3DTEXTURE9 g_apTextureRankingScore = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffRankingScore = NULL;
RankingScore g_aRankingScore[MAX_RANKING][MAX_DIGIT];
int iRanking[MAX_RANKING] = { 1500000,1250000,1000000,750000,500000 };

//=============================================================================
// ����������
//=============================================================================
void InitRankingScore(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	int nCutRankingScore;
	int nCutRanking;

	//�����ݒ�
	for (nCutRankingScore = 0; nCutRankingScore < MAX_DIGIT; nCutRankingScore++)
		for (nCutRanking = 0; nCutRanking < MAX_RANKING; nCutRanking++) {
			{
				g_aRankingScore[nCutRanking][nCutRankingScore].bUse = false;
				g_aRankingScore[nCutRanking][nCutRankingScore].pos = D3DXVECTOR3(425.0f + 50.0f * nCutRankingScore, 185.0f + 100.0f * nCutRanking, 0.0f);
				g_aRankingScore[nCutRanking][nCutRankingScore].rot = D3DXVECTOR3(0, 0, 0);
			}
		}

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/number000.png", &g_apTextureRankingScore);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_DIGIT * MAX_RANKING,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffRankingScore,
		NULL);

	MakeVertexRankingScore(pDevice);

}

void UninitRankingScore(void) {

	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffRankingScore != NULL)
	{
		g_pVtxBuffRankingScore->Release();
		g_pVtxBuffRankingScore = NULL;
	}

	// �e�N�X�`���̊J��
	if (g_apTextureRankingScore != NULL) {
		g_apTextureRankingScore->Release();
		g_apTextureRankingScore = NULL;
	}
}

//=============================================================================
//�X�V����
//=============================================================================
void UpdateRankingScore(void)
{

}

void DrawRankingScore(void) {

	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//�f�[�^�X�g���[���ɃZ�b�g
	pDevice->SetStreamSource(0,
		g_pVtxBuffRankingScore,
		0,
		sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_apTextureRankingScore);


	for (int nCutRankingScore = 0; nCutRankingScore < MAX_DIGIT * MAX_RANKING; nCutRankingScore++) {

		//�|���S���̍쐬
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCutRankingScore * 4, 2);

	}
}

//=============================================================================
// ���_���̍쐬
//=============================================================================
void MakeVertexRankingScore(LPDIRECT3DDEVICE9 pDevice)
{
	VERTEX_2D *pVtx;
	int nCutVtx;

	//���b�N
	g_pVtxBuffRankingScore->Lock(0, 0, (void**)&pVtx, 0);

	for (nCutVtx = 0; nCutVtx < MAX_DIGIT; nCutVtx++) {
		for (int nCutVtxx = 0; nCutVtxx < MAX_RANKING; nCutVtxx++) {

			//���_���W�̐ݒ�
			pVtx[0].pos.x = g_aRankingScore[nCutVtxx][nCutVtx].pos.x;
			pVtx[1].pos.x = g_aRankingScore[nCutVtxx][nCutVtx].pos.x + 50;
			pVtx[2].pos.x = g_aRankingScore[nCutVtxx][nCutVtx].pos.x;
			pVtx[3].pos.x = g_aRankingScore[nCutVtxx][nCutVtx].pos.x + 50;

			pVtx[0].pos.y = g_aRankingScore[nCutVtxx][nCutVtx].pos.y;
			pVtx[1].pos.y = g_aRankingScore[nCutVtxx][nCutVtx].pos.y;
			pVtx[2].pos.y = g_aRankingScore[nCutVtxx][nCutVtx].pos.y + 50;
			pVtx[3].pos.y = g_aRankingScore[nCutVtxx][nCutVtx].pos.y + 50;

			//rhw�̐ݒ�
			pVtx[0].rhw = 1.0f;
			pVtx[1].rhw = 1.0f;
			pVtx[2].rhw = 1.0f;
			pVtx[3].rhw = 1.0f;

			// ���_�J���[�̐ݒ�
			pVtx[0].col = D3DCOLOR_RGBA(255, 255, 0, 255);//RGBA�̐F������
			pVtx[1].col = D3DCOLOR_RGBA(255, 255, 0, 255);
			pVtx[2].col = D3DCOLOR_RGBA(255, 255, 0, 255);
			pVtx[3].col = D3DCOLOR_RGBA(255, 255, 0, 255);

			int iPow = int (powf(10, float( MAX_DIGIT - nCutVtx)));
			float fScore = float( iRanking[nCutVtxx] % iPow / (iPow / 10));
			//�e�N�X�`�����W�̐ݒ�
			pVtx[0].tex = D3DXVECTOR2(fScore*(1.0f / MAX_PATTEN), 0);
			pVtx[1].tex = D3DXVECTOR2(fScore*(1.0f / MAX_PATTEN) + 1.0f / MAX_PATTEN, 0);
			pVtx[2].tex = D3DXVECTOR2(fScore*(1.0f / MAX_PATTEN), 1);
			pVtx[3].tex = D3DXVECTOR2(fScore*(1.0f / MAX_PATTEN) + 1.0f / MAX_PATTEN, 1);
			pVtx += 4;
		}
	}

	//���b�N����
	g_pVtxBuffRankingScore->Unlock();
}

void RankingRecord(void) {

	int GameScore;
	int Score;
	int TimeScore;
	int BulletScore;
	int life;

	Score = GetNumber();								//�Q�[���I�����̃X�R�A�������Ă���
	BulletScore = GetBulletCount();						//�Q�[���I�����̒e�̐��������Ă���
	TimeScore = GetTime();								//�Q�[���I�����̃^�C���������Ă���
	life = GetPlayerHP();
	GameScore = Score * BulletScore * TimeScore * life;		//�X�R�A�ƒe���Ǝ��Ԃ�������

														//�����L���O�̏�����
	for (int i = 0; i <= MAX_RANKING; i++) {
		if (iRanking[i] <= GameScore) {
			for (int j = MAX_RANKING; j >= i; j--) {
				iRanking[j] = iRanking[j - 1];			//�Q�[���X�R�A�̈��̐��ɑ�����
			}
			iRanking[i] = GameScore;
			break;
		}
	}
}