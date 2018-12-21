//=============================================================================
//
// �e�̏��� [Enemy.cpp]
// Author : NAOYA OMORI
//
//=============================================================================
#include "Enemy.h"
#include "polygon.h"
#include "bullet.h"
#include "explosion.h"
#include "debugproc.h"
#include "wall.h"
#include "ball.h"

//*****************************************************************************
// �}�N����`�錾
//*****************************************************************************
#define MAX_ENEMY (4)
#define MAX_ENEMY_TEX (4)
#define ENEMY_SIZE_X (46)
#define ENEMY_SIZE_Y (46)

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void MakeVertexEnemy(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9 g_apTextureEnemy[MAX_ENEMY_TEX] = {};
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffEnemy = NULL;
Enemy g_aEnemy[MAX_ENEMY];

float g_move;					//�G�̑��x�p�̕ϐ�
bool AmbushMoveFlag;			//�G���ړ����邩���Ȃ����p�t���O
bool ChaseMoveFlag;				//�G���ړ����邩���Ȃ����p�t���O
bool MoodyMoveFlag;				//�G���ړ����邩���Ȃ����p�t���O
bool SillyMoveFlag;				//�G���ړ����邩���Ȃ����p�t���O
bool AmbushRestartFlag;			//���񂷂�G�p
bool AmbushCircumferenceFlag;	//���񂷂�G�p
bool ChaseRestartFlag;			//���񂷂�G�p
bool MoodyRestartFlag;			//���񂷂�G�p
bool SillyRestartFlag;			//���񂷂�G�p
bool InvisibleAmbushFlag;		//�����p�t���O
bool InvisibleChaseFlag;		//�����p�t���O
bool InvisibleMoodyFlag;		//�����p�t���O
bool InvisibleSillyFlag;		//�����p�t���O
int InvisibleAmbushCount;		//�����p�J�E���^
int InvisibleChaseCount;		//�����p�J�E���^
int InvisibleMoodyCount;		//�����p�J�E���^
int InvisibleSillyCount;		//�����p�J�E���^
int AmbushCircumference;		//���񂷂�G�p
int ChaseCircumference;			//���񂷂�G�p
int MoodyCircumference;			//���񂷂�G�p
int SillyCircumference;			//���񂷂�G�p

//=============================================================================
// ����������
//=============================================================================
void InitEnemy(void)
{

	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	int nCutEnemy;

	//�����ݒ�
	for (nCutEnemy = 0; nCutEnemy < MAX_ENEMY; nCutEnemy++) {
		g_aEnemy[nCutEnemy].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aEnemy[nCutEnemy].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aEnemy[nCutEnemy].fRadius = ENEMY_SIZE_X / 2;
		g_aEnemy[nCutEnemy].fAngleEnemy = atan2f(ENEMY_SIZE_X / 2, ENEMY_SIZE_Y / 2);
		g_aEnemy[nCutEnemy].fLengthEnemy = sqrtf((ENEMY_SIZE_X / 2) * (ENEMY_SIZE_X / 2) + (ENEMY_SIZE_Y / 2) * (ENEMY_SIZE_Y / 2));
		g_aEnemy[nCutEnemy].nType = 0;
		g_aEnemy[nCutEnemy].bUse = false;
		g_aEnemy[nCutEnemy].bHit = false;
	}

	//������
	InvisibleAmbushCount = 0;
	InvisibleChaseCount = 0;
	AmbushCircumference = 0;
	ChaseCircumference = 0;
	AmbushRestartFlag = true;
	AmbushCircumferenceFlag = false;
	ChaseRestartFlag = true;
	MoodyRestartFlag = true;
	SillyRestartFlag = true;
	AmbushMoveFlag = false;
	ChaseMoveFlag = false;
	MoodyMoveFlag = false;
	SillyMoveFlag = false;
	InvisibleAmbushFlag = false;
	InvisibleChaseFlag = false;
	InvisibleMoodyFlag = false;
	InvisibleSillyFlag = false;

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/ambush.png", &g_apTextureEnemy[0]);	//�s���N�F�̓G
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/chase.png", &g_apTextureEnemy[1]);		//�ԐF�̓G
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/moody.png", &g_apTextureEnemy[2]);		//���F�̓G
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/silly.png", &g_apTextureEnemy[3]);		//�I�����W�F�̓G

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_ENEMY,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffEnemy,
		NULL);

	MakeVertexEnemy(pDevice);

}

void UninitEnemy(void) {

	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffEnemy != NULL)
	{
		g_pVtxBuffEnemy->Release();
		g_pVtxBuffEnemy = NULL;
	}

	// �e�N�X�`���̊J��
	for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		if (g_apTextureEnemy[nCntEnemy] != NULL)
		{
			g_apTextureEnemy[nCntEnemy]->Release();
			g_apTextureEnemy[nCntEnemy] = NULL;
		}
	}
}

//=============================================================================
//�X�V����
//=============================================================================
void UpdateEnemy(void) {

	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	VERTEX_2D *pVtx;
	D3DXVECTOR3 pPos;		//�v���C���[�̈ʒu�p
	int nCutEnemy;

	pPos = GetMinePos();	//���@�̈ʒu���Ƃ��Ă���B

	g_move = MOVE_SPEED;	//�G�̈ړ��p�ϐ��ɑ���������

	for (nCutEnemy = 0; nCutEnemy < MAX_ENEMY; nCutEnemy++)
	{

		g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

		if (g_aEnemy[nCutEnemy].bUse == true) {

			// ���_���W�̐ݒ�
			pVtx += 4 * nCutEnemy;
			pVtx[0].pos.x = g_aEnemy[nCutEnemy].pos.x - sinf(g_aEnemy[nCutEnemy].fAngleEnemy - g_aEnemy[nCutEnemy].rot.z)*g_aEnemy[nCutEnemy].fLengthEnemy;
			pVtx[0].pos.y = g_aEnemy[nCutEnemy].pos.y - cosf(g_aEnemy[nCutEnemy].fAngleEnemy - g_aEnemy[nCutEnemy].rot.z)*g_aEnemy[nCutEnemy].fLengthEnemy;
			pVtx[0].pos.z = 0.0f;

			pVtx[1].pos.x = g_aEnemy[nCutEnemy].pos.x + sinf(g_aEnemy[nCutEnemy].fAngleEnemy + g_aEnemy[nCutEnemy].rot.z)*g_aEnemy[nCutEnemy].fLengthEnemy;
			pVtx[1].pos.y = g_aEnemy[nCutEnemy].pos.y - cosf(g_aEnemy[nCutEnemy].fAngleEnemy + g_aEnemy[nCutEnemy].rot.z)*g_aEnemy[nCutEnemy].fLengthEnemy;
			pVtx[1].pos.z = 0.0f;

			pVtx[2].pos.x = g_aEnemy[nCutEnemy].pos.x - sinf(g_aEnemy[nCutEnemy].fAngleEnemy + g_aEnemy[nCutEnemy].rot.z)*g_aEnemy[nCutEnemy].fLengthEnemy;
			pVtx[2].pos.y = g_aEnemy[nCutEnemy].pos.y + cosf(g_aEnemy[nCutEnemy].fAngleEnemy + g_aEnemy[nCutEnemy].rot.z)*g_aEnemy[nCutEnemy].fLengthEnemy;
			pVtx[2].pos.z = 0.0f;

			pVtx[3].pos.x = g_aEnemy[nCutEnemy].pos.x + sinf(g_aEnemy[nCutEnemy].fAngleEnemy - g_aEnemy[nCutEnemy].rot.z)*g_aEnemy[nCutEnemy].fLengthEnemy;
			pVtx[3].pos.y = g_aEnemy[nCutEnemy].pos.y + cosf(g_aEnemy[nCutEnemy].fAngleEnemy - g_aEnemy[nCutEnemy].rot.z)*g_aEnemy[nCutEnemy].fLengthEnemy;
			pVtx[3].pos.z = 0.0f;

			g_pVtxBuffEnemy->Unlock();
		}
	}

	MoveAmbush();
	MoveChase();
	MoveMoody();
	MoveSilly();

	if (g_aEnemy[0].bHit == TRUE) {
		InvisibleAmbush();
	}

	if (g_aEnemy[1].bHit == TRUE) {
		InvisibleChase();
	}

	if (g_aEnemy[2].bHit == TRUE) {
		InvisibleMoody();
	}

	if (g_aEnemy[3].bHit == TRUE) {
		InvisibleSilly();
	}

	//�f�o�b�N���O
	PrintDebug("�A���o�b�V��(�s���N�F)�̏��\n");
	PrintDebug("Enemy[0] Position(X:%f,Y:%f,Z:%f)\n", g_aEnemy[0].pos.x, g_aEnemy[0].pos.y, g_aEnemy[0].pos.z);
	PrintDebug("\n");
	PrintDebug("�`���[�Y(�ԐF)�̏��\n");
	PrintDebug("Enemy[1] Position(X:%f,Y:%f,Z:%f)\n", g_aEnemy[1].pos.x, g_aEnemy[1].pos.y, g_aEnemy[1].pos.z);
	PrintDebug("\n");
	PrintDebug("���[�f�B�[(���F)�̏��\n");
	PrintDebug("Enemy[2] Position(X:%f,Y:%f,Z:%f)\n", g_aEnemy[2].pos.x, g_aEnemy[2].pos.y, g_aEnemy[2].pos.z);
	PrintDebug("\n");
	PrintDebug("�V���\(�I�����W�F)�̏��\n");
	PrintDebug("Enemy[3] Position(X:%f,Y:%f,Z:%f)\n", g_aEnemy[3].pos.x, g_aEnemy[3].pos.y, g_aEnemy[3].pos.z);
	PrintDebug("\n");
	PrintDebug("AmbushRestartFlag:%d\n", AmbushRestartFlag);
	PrintDebug("==========================================================\n");
	PrintDebug("\n");

}

void DrawEnemy(void) {

	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	int nCutEnemy;

	//�f�[�^�X�g���[���ɃZ�b�g
	pDevice->SetStreamSource(0,
		g_pVtxBuffEnemy,
		0,
		sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (nCutEnemy = 0; nCutEnemy < MAX_ENEMY; nCutEnemy++)
	{
		if (g_aEnemy[nCutEnemy].bUse == true)
		{
			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_apTextureEnemy[g_aEnemy[nCutEnemy].nType]);

			// �|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCutEnemy * 4, 2);
		}
	}
}


void SetEnemy(D3DXVECTOR3 pos, int nType) {

	int nCutEnemy;

	for (nCutEnemy = 0; nCutEnemy < MAX_ENEMY; nCutEnemy++)
	{
		if (g_aEnemy[nCutEnemy].bUse == false)
		{
			g_aEnemy[nCutEnemy].pos = pos;
			g_aEnemy[nCutEnemy].nType = nType;
			g_aEnemy[nCutEnemy].bUse = true;
			break;
		}
	}
}

//=============================================================================
// ���_���̍쐬
//=============================================================================
void MakeVertexEnemy(LPDIRECT3DDEVICE9 pDevice)
{
	VERTEX_2D *pVtx;
	int nCutVtx;

	//���b�N
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

	for (nCutVtx = 0; nCutVtx < MAX_ENEMY; nCutVtx++) {

		// ���_���W�̐ݒ�
		pVtx[0].pos.x = g_aEnemy[nCutVtx].pos.x - sinf(g_aEnemy[nCutVtx].fAngleEnemy - g_aEnemy[nCutVtx].rot.z)*g_aEnemy[nCutVtx].fLengthEnemy;
		pVtx[0].pos.y = g_aEnemy[nCutVtx].pos.y - cosf(g_aEnemy[nCutVtx].fAngleEnemy - g_aEnemy[nCutVtx].rot.z)*g_aEnemy[nCutVtx].fLengthEnemy;
		pVtx[0].pos.z = 0.0f;

		pVtx[1].pos.x = g_aEnemy[nCutVtx].pos.x + sinf(g_aEnemy[nCutVtx].fAngleEnemy + g_aEnemy[nCutVtx].rot.z)*g_aEnemy[nCutVtx].fLengthEnemy;
		pVtx[1].pos.y = g_aEnemy[nCutVtx].pos.y - cosf(g_aEnemy[nCutVtx].fAngleEnemy + g_aEnemy[nCutVtx].rot.z)*g_aEnemy[nCutVtx].fLengthEnemy;
		pVtx[1].pos.z = 0.0f;

		pVtx[2].pos.x = g_aEnemy[nCutVtx].pos.x - sinf(g_aEnemy[nCutVtx].fAngleEnemy + g_aEnemy[nCutVtx].rot.z)*g_aEnemy[nCutVtx].fLengthEnemy;
		pVtx[2].pos.y = g_aEnemy[nCutVtx].pos.y + cosf(g_aEnemy[nCutVtx].fAngleEnemy + g_aEnemy[nCutVtx].rot.z)*g_aEnemy[nCutVtx].fLengthEnemy;
		pVtx[2].pos.z = 0.0f;

		pVtx[3].pos.x = g_aEnemy[nCutVtx].pos.x + sinf(g_aEnemy[nCutVtx].fAngleEnemy - g_aEnemy[nCutVtx].rot.z)*g_aEnemy[nCutVtx].fLengthEnemy;
		pVtx[3].pos.y = g_aEnemy[nCutVtx].pos.y + cosf(g_aEnemy[nCutVtx].fAngleEnemy - g_aEnemy[nCutVtx].rot.z)*g_aEnemy[nCutVtx].fLengthEnemy;
		pVtx[3].pos.z = 0.0f;

		// rhw�̐ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		// ���_�J���[�̐ݒ�
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		// �e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(1, 0);
		pVtx[1].tex = D3DXVECTOR2(0, 0);
		pVtx[2].tex = D3DXVECTOR2(1, 1);
		pVtx[3].tex = D3DXVECTOR2(0, 1);
		pVtx += 4;

	}

	//���b�N����
	g_pVtxBuffEnemy->Unlock();

}

void MoveAmbush(void) {

	D3DXVECTOR3 pPos;		//�v���C���[�̈ʒu�p

	pPos = GetMinePos();

	//TRUE�̏ꍇ�L�������ǔ�����
	if (AmbushMoveFlag == TRUE) {
		if (AmbushRestartFlag == true && g_aEnemy[0].pos.y != 249.5f) {
			AmbushCircumference = 1;
		}
		if (g_aEnemy[0].pos.y == 249.5f && AmbushRestartFlag == true) {
			AmbushCircumference = 3;
		}
		if (g_aEnemy[0].pos.x == 90 && AmbushRestartFlag == true) {
			AmbushCircumference = 1;
		}
		if (g_aEnemy[0].pos.x == 90 && g_aEnemy[0].pos.y == 101.5f && AmbushRestartFlag == true && AmbushCircumferenceFlag == false) {
			AmbushCircumference = 4;
			AmbushRestartFlag = false;
		}
		if (g_aEnemy[0].pos.x == 1190 && g_aEnemy[0].pos.y == 101.5f && AmbushRestartFlag == false && AmbushCircumferenceFlag == false) {
			AmbushCircumference = 2;
		}
		if (g_aEnemy[0].pos.x == 1190 && g_aEnemy[0].pos.y == 249.5f && AmbushRestartFlag == false && AmbushCircumferenceFlag == false) {
			AmbushCircumference = 3;
		}
		if (g_aEnemy[0].pos.x == 90 && g_aEnemy[0].pos.y == 249.5f && AmbushRestartFlag == false && AmbushCircumferenceFlag == false) {
			AmbushCircumference = 2;
		}
		if (g_aEnemy[0].pos.x == 90 && g_aEnemy[0].pos.y == 497.5f && AmbushRestartFlag == false && AmbushCircumferenceFlag == false) {
			AmbushCircumference = 4;
		}
		if (g_aEnemy[0].pos.x == 1190 && g_aEnemy[0].pos.y == 497.5f && AmbushRestartFlag == false && AmbushCircumferenceFlag == false) {
			AmbushCircumference = 2;
		}
		if (g_aEnemy[0].pos.x == 1190 && g_aEnemy[0].pos.y == 647.5 && AmbushRestartFlag == false && AmbushCircumferenceFlag == false) {
			AmbushCircumference = 3;
		}
		if (g_aEnemy[0].pos.x == 90 && g_aEnemy[0].pos.y == 647.5 && AmbushRestartFlag == false && AmbushCircumferenceFlag == false) {
			AmbushCircumference = 1;
			AmbushCircumferenceFlag = true;
		}
		if (g_aEnemy[0].pos.x == 90 && g_aEnemy[0].pos.y == 497.5f && AmbushRestartFlag == false && AmbushCircumferenceFlag == true) {
			AmbushCircumference = 4;
		}
		if (g_aEnemy[0].pos.x == 1190 && g_aEnemy[0].pos.y == 497.5f && AmbushRestartFlag == false && AmbushCircumferenceFlag == true) {
			AmbushCircumference = 1;
		}
		if (g_aEnemy[0].pos.x == 1190 && g_aEnemy[0].pos.y == 249.5f && AmbushRestartFlag == false && AmbushCircumferenceFlag == true) {
			AmbushCircumference = 3;
		}
		if (g_aEnemy[0].pos.x == 90 && g_aEnemy[0].pos.y == 249.5f && AmbushRestartFlag == false && AmbushCircumferenceFlag == true) {
			AmbushCircumference = 1;
		}
		if (g_aEnemy[0].pos.x == 90 && g_aEnemy[0].pos.y == 101.5f && AmbushRestartFlag == false && AmbushCircumferenceFlag == true) {
			AmbushCircumference = 4;
			AmbushCircumferenceFlag = false;
		}
		//�G[0]�L�����N�^�[�̈ړ�����
		if (AmbushCircumference == 1) {
			g_aEnemy[0].pos.y -= g_move;
		}
		if (AmbushCircumference == 2) {
			g_aEnemy[0].pos.y += g_move;
		}
		if (AmbushCircumference == 3) {
			g_aEnemy[0].pos.x -= g_move;
		}
		if (AmbushCircumference == 4) {
			g_aEnemy[0].pos.x += g_move;
		}


	}
}

void MoveChase(void) {

	//TRUE�̏ꍇ�L�������ړ�����
	if (ChaseMoveFlag == TRUE) {
		if (ChaseRestartFlag == true && g_aEnemy[1].pos.y != 250) {
			g_aEnemy[1].pos.y -= g_move;
		}
		if (g_aEnemy[1].pos.y == 250 && ChaseRestartFlag == true) {
			g_aEnemy[1].pos.x += g_move;
		}
		if (g_aEnemy[1].pos.x == 1190 && ChaseRestartFlag == true) {
			ChaseRestartFlag = false;
			ChaseCircumference = 1;
		}
		if (g_aEnemy[1].pos.x == 1190 && g_aEnemy[1].pos.y == 100 && ChaseRestartFlag == false) {
			ChaseCircumference = 3;
		}
		if (g_aEnemy[1].pos.x == 90 && g_aEnemy[1].pos.y == 100 && ChaseRestartFlag == false) {
			ChaseCircumference = 2;
		}
		if (g_aEnemy[1].pos.x == 90 && g_aEnemy[1].pos.y == 650 && ChaseRestartFlag == false) {
			ChaseCircumference = 4;
		}
		if (g_aEnemy[1].pos.x == 1190 && g_aEnemy[1].pos.y == 650 && ChaseRestartFlag == false) {
			ChaseCircumference = 1;
		}


		if (ChaseCircumference == 1) {
			g_aEnemy[1].pos.y -= g_move;
		}
		if (ChaseCircumference == 2) {
			g_aEnemy[1].pos.y += g_move;
		}
		if (ChaseCircumference == 3) {
			g_aEnemy[1].pos.x -= g_move;
		}
		if (ChaseCircumference == 4) {
			g_aEnemy[1].pos.x += g_move;
		}
	}
}

void MoveMoody(void) {

	//TRUE�̏ꍇ�L�������ړ�����
	if (MoodyMoveFlag == TRUE) {

		if (MoodyRestartFlag == true && g_aEnemy[2].pos.y != 250.0f) {
			MoodyCircumference = 1;
		}
		if (g_aEnemy[2].pos.y == 250.0f && MoodyRestartFlag == true) {
			MoodyCircumference = 3;
		}
		if (g_aEnemy[2].pos.x == 490.0f && MoodyRestartFlag == true) {
			MoodyCircumference = 2;
		}
		if (g_aEnemy[2].pos.y == 500.0f && MoodyRestartFlag == true) {
			MoodyCircumference = 3;
		}
		if (g_aEnemy[2].pos.x == 290.0f && MoodyRestartFlag == true) {
			MoodyCircumference = 2;
		}
		if (g_aEnemy[2].pos.y == 650.0f && MoodyRestartFlag == true) {
			MoodyCircumference = 3;
		}
		if (g_aEnemy[2].pos.x == 90.0f && MoodyRestartFlag == true) {
			MoodyCircumference = 1;
			MoodyRestartFlag = false;
		}
		if (g_aEnemy[2].pos.x == 90.0f && g_aEnemy[2].pos.y == 250.0f && MoodyRestartFlag == false) {
			MoodyCircumference = 4;
		}
		if (g_aEnemy[2].pos.x == 290.0f && g_aEnemy[2].pos.y == 250.0f && MoodyRestartFlag == false) {
			MoodyCircumference = 1;
		}
		if (g_aEnemy[2].pos.x == 290.0f && g_aEnemy[2].pos.y == 100.0f && MoodyRestartFlag == false) {
			MoodyCircumference = 4;
		}
		if (g_aEnemy[2].pos.x == 590.0f && g_aEnemy[2].pos.y == 100.0f && MoodyRestartFlag == false) {
			MoodyCircumference = 2;
		}
		if (g_aEnemy[2].pos.x == 590.0f && g_aEnemy[2].pos.y == 250.0f && MoodyRestartFlag == false) {
			MoodyCircumference = 4;
		}
		if (g_aEnemy[2].pos.x == 692.0f && g_aEnemy[2].pos.y == 250.0f && MoodyRestartFlag == false) {
			MoodyCircumference = 1;
		}
		if (g_aEnemy[2].pos.x == 692.0f && g_aEnemy[2].pos.y == 100.0f && MoodyRestartFlag == false) {
			MoodyCircumference = 4;
		}
		if (g_aEnemy[2].pos.x == 992.0f && g_aEnemy[2].pos.y == 100.0f && MoodyRestartFlag == false) {
			MoodyCircumference = 2;
		}
		if (g_aEnemy[2].pos.x == 992.0f && g_aEnemy[2].pos.y == 250.0f && MoodyRestartFlag == false) {
			MoodyCircumference = 4;
		}
		if (g_aEnemy[2].pos.x == 1190.0f && g_aEnemy[2].pos.y == 250.0f && MoodyRestartFlag == false) {
			MoodyCircumference = 2;
		}
		if (g_aEnemy[2].pos.x == 1190.0f && g_aEnemy[2].pos.y == 500.0f && MoodyRestartFlag == false) {
			MoodyCircumference = 3;
		}
		if (g_aEnemy[2].pos.x == 990.0f && g_aEnemy[2].pos.y == 500.0f && MoodyRestartFlag == false) {
			MoodyCircumference = 2;
		}
		if (g_aEnemy[2].pos.x == 990.0f && g_aEnemy[2].pos.y == 650.0f && MoodyRestartFlag == false) {
			MoodyCircumference = 3;
		}
		if (g_aEnemy[2].pos.x == 692.0f && g_aEnemy[2].pos.y == 650.0f && MoodyRestartFlag == false) {
			MoodyCircumference = 1;
		}
		if (g_aEnemy[2].pos.x == 692.0f && g_aEnemy[2].pos.y == 500.0f && MoodyRestartFlag == false) {
			MoodyCircumference = 3;
		}
		if (g_aEnemy[2].pos.x == 590.0f && g_aEnemy[2].pos.y == 500.0f && MoodyRestartFlag == false) {
			MoodyCircumference = 2;
		}
		if (g_aEnemy[2].pos.x == 590.0f && g_aEnemy[2].pos.y == 650.0f && MoodyRestartFlag == false) {
			MoodyCircumference = 3;
		}
		if (g_aEnemy[2].pos.x == 290.0f && g_aEnemy[2].pos.y == 650.0f && MoodyRestartFlag == false) {
			MoodyCircumference = 1;
		}
		if (g_aEnemy[2].pos.x == 290.0f && g_aEnemy[2].pos.y == 500.0f && MoodyRestartFlag == false) {
			MoodyCircumference = 3;
		}
		if (g_aEnemy[2].pos.x == 90.0f && g_aEnemy[2].pos.y == 500.0f && MoodyRestartFlag == false) {
			MoodyCircumference = 1;
		}

		//�G[2]�L�����N�^�[�̈ړ�����
		if (MoodyCircumference == 1) {
			g_aEnemy[2].pos.y -= g_move;
		}
		if (MoodyCircumference == 2) {
			g_aEnemy[2].pos.y += g_move;
		}
		if (MoodyCircumference == 3) {
			g_aEnemy[2].pos.x -= g_move;
		}
		if (MoodyCircumference == 4) {
			g_aEnemy[2].pos.x += g_move;
		}
	}
}

void MoveSilly(void) {

	//TRUE�̏ꍇ�L�������ړ�����
	if (SillyMoveFlag == TRUE) {

		if (SillyRestartFlag == true && g_aEnemy[3].pos.y != 250.0f) {
			SillyCircumference = 1;
		}
		if (g_aEnemy[3].pos.y == 250.0f && SillyRestartFlag == true) {
			SillyCircumference = 4;
		}
		if (g_aEnemy[3].pos.x == 790.0f && SillyRestartFlag == true) {
			SillyCircumference = 2;
		}
		if (g_aEnemy[3].pos.y == 500.0f && SillyRestartFlag == true) {
			SillyCircumference = 4;
		}
		if (g_aEnemy[3].pos.x == 990.0f && SillyRestartFlag == true) {
			SillyCircumference = 2;
		}
		if (g_aEnemy[3].pos.y == 650.0f && SillyRestartFlag == true) {
			SillyCircumference = 4;
		}
		if (g_aEnemy[3].pos.x == 1192.0f && SillyRestartFlag == true) {
			SillyCircumference = 1;
			SillyRestartFlag = false;
		}
		if (g_aEnemy[3].pos.x == 1192.0f && g_aEnemy[3].pos.y == 500.0f && SillyRestartFlag == false) {
			SillyCircumference = 3;
		}
		if (g_aEnemy[3].pos.x == 792.0f && g_aEnemy[3].pos.y == 500.0f && SillyRestartFlag == false) {
			SillyCircumference = 1;
		}
		if (g_aEnemy[3].pos.x == 792.0f && g_aEnemy[3].pos.y == 250.0f && SillyRestartFlag == false) {
			SillyCircumference = 3;
		}
		if (g_aEnemy[3].pos.x == 690.0f && g_aEnemy[3].pos.y == 250.0f && SillyRestartFlag == false) {
			SillyCircumference = 1;
		}
		if (g_aEnemy[3].pos.x == 690.0f && g_aEnemy[3].pos.y == 100.0f && SillyRestartFlag == false) {
			SillyCircumference = 3;
		}
		if (g_aEnemy[3].pos.x == 590.0f && g_aEnemy[3].pos.y == 100.0f && SillyRestartFlag == false) {
			SillyCircumference = 2;
		}
		if (g_aEnemy[3].pos.x == 590.0f && g_aEnemy[3].pos.y == 250.0f && SillyRestartFlag == false) {
			SillyCircumference = 3;
		}
		if (g_aEnemy[3].pos.x == 492.0f && g_aEnemy[3].pos.y == 250.0f && SillyRestartFlag == false) {
			SillyCircumference = 2;
		}
		if (g_aEnemy[3].pos.x == 492.0f && g_aEnemy[3].pos.y == 500.0f && SillyRestartFlag == false) {
			SillyCircumference = 4;
		}
		if (g_aEnemy[3].pos.x == 590.0f && g_aEnemy[3].pos.y == 500.0f && SillyRestartFlag == false) {
			SillyCircumference = 2;
		}
		if (g_aEnemy[3].pos.x == 590.0f && g_aEnemy[3].pos.y == 650.0f && SillyRestartFlag == false) {
			SillyCircumference = 4;
		}
		if (g_aEnemy[3].pos.x == 690.0f && g_aEnemy[3].pos.y == 650.0f && SillyRestartFlag == false) {
			SillyCircumference = 1;
		}
		if (g_aEnemy[3].pos.x == 690.0f && g_aEnemy[3].pos.y == 500.0f && SillyRestartFlag == false) {
			SillyCircumference = 4;
		}


		//�G[3]�L�����N�^�[�̈ړ�����
		if (SillyCircumference == 1) {
			g_aEnemy[3].pos.y -= g_move;
		}
		if (SillyCircumference == 2) {
			g_aEnemy[3].pos.y += g_move;
		}
		if (SillyCircumference == 3) {
			g_aEnemy[3].pos.x -= g_move;
		}
		if (SillyCircumference == 4) {
			g_aEnemy[3].pos.x += g_move;
		}
		
	}
}

void Reset(void) {
	AmbushRestartFlag = true;
	ChaseRestartFlag = true;
	MoodyRestartFlag = true;
	SillyRestartFlag = true;
}

//�G�L�������`�J�`�J�����鏈��
void InvisibleAmbush(void) {
	InvisibleAmbushCount++;
	if (g_aEnemy[0].bUse == true && InvisibleAmbushCount % 5 == 0) {
		g_aEnemy[0].bUse = false;
	}
	else if (!g_aEnemy[0].bUse && InvisibleAmbushCount % 5 == 0) {
		g_aEnemy[0].bUse = true;
	}
	if (InvisibleAmbushCount == 120)
	{
		InvisibleAmbushCount = 0;
		g_aEnemy[0].bUse = true;
		g_aEnemy[0].bHit = false;
	}
}

//�G�L�������`�J�`�J�����鏈��
void InvisibleChase(void) {
	InvisibleChaseCount++;
	if (g_aEnemy[1].bUse == true && InvisibleChaseCount % 5 == 0) {
		g_aEnemy[1].bUse = false;
	}
	else if (!g_aEnemy[1].bUse && InvisibleChaseCount % 5 == 0) {
		g_aEnemy[1].bUse = true;
	}
	if (InvisibleChaseCount == 120)
	{
		InvisibleChaseCount = 0;
		g_aEnemy[1].bUse = true;
		g_aEnemy[1].bHit = false;
	}
}

//�G�L�������`�J�`�J�����鏈��
void InvisibleMoody(void) {
	InvisibleMoodyCount++;
	if (g_aEnemy[2].bUse == true && InvisibleMoodyCount % 5 == 0) {
		g_aEnemy[2].bUse = false;
	}
	else if (!g_aEnemy[2].bUse && InvisibleMoodyCount % 5 == 0) {
		g_aEnemy[2].bUse = true;
	}
	if (InvisibleMoodyCount == 120)
	{
		InvisibleMoodyCount = 0;
		g_aEnemy[2].bUse = true;
		g_aEnemy[2].bHit = false;
	}
}

//�G�L�������`�J�`�J�����鏈��
void InvisibleSilly(void) {
	InvisibleSillyCount++;
	if (g_aEnemy[3].bUse == true && InvisibleSillyCount % 5 == 0) {
		g_aEnemy[3].bUse = false;
	}
	else if (!g_aEnemy[3].bUse && InvisibleSillyCount % 5 == 0) {
		g_aEnemy[3].bUse = true;
	}
	if (InvisibleSillyCount == 120)
	{
		InvisibleSillyCount = 0;
		g_aEnemy[3].bUse = true;
		g_aEnemy[3].bHit = false;
	}
}

void ResetChase(void) {
	ChaseRestartFlag = true;
	ChaseCircumference = 0;
}

D3DXVECTOR3 *GetEnemy(void) {
	return &g_aEnemy[0].pos;
}

D3DXVECTOR3 *GetChase(void) {
	return &g_aEnemy[1].pos;
}

D3DXVECTOR3 *GetMoody(void) {
	return &g_aEnemy[2].pos;
}

D3DXVECTOR3 *GetSilly(void) {
	return &g_aEnemy[3].pos;
}

D3DXVECTOR3 GetEnemyPos(void) {
	return g_aEnemy[0].pos;
}

void SetAmbushPosition(D3DXVECTOR3 pos) {
	g_aEnemy[0].pos = pos;
}

void SetAmbushMoveKey(bool key) {
	AmbushMoveFlag = key;
}

void SetChaseMoveKey(bool key) {
	ChaseMoveFlag = key;
}

void SetMoodyMoveKey(bool key) {
	MoodyMoveFlag = key;
}

void SetSillyMoveKey(bool key) {
	SillyMoveFlag = key;
}

void SetEnemyPos(D3DXVECTOR3 pos) {
	g_aEnemy[0].pos = pos;
}

void SetAmbushHitKey(bool hit) {
	g_aEnemy[0].bHit = hit;
}

void SetChaseHitKey(bool hit) {
	g_aEnemy[1].bHit = hit;
}

void SetMoodyHitKey(bool hit) {
	g_aEnemy[2].bHit = hit;
}

void SetSillyHitKey(bool hit) {
	g_aEnemy[3].bHit = hit;
}

float GetEnemyRadius(void) {
	return g_aEnemy[0].fRadius;
}