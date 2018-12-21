//=============================================================================
//
// �|���S������ [polygon.cpp]
// Author : NAOYA OMORI
//
//=============================================================================
#include "polygon.h"
#include "input.h"
#include "fade.h"
#include "sound.h"
#include "DebugProc.h"
#include "bullet.h"
#include "Enemy.h"
#include "wall.h"
#include "map.h"
#include "life.h"
#include "ball.h"
#include "explosion.h"
#include "timer.h"
#include "font.h"
#include "ball.h"

//*****************************************************************************
// �}�N����`�錾
//*****************************************************************************
#define PLAYER_SIZE_X (45)
#define PLAYER_SIZE_Y (45)
#define MAX_PATTERN (4)

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void MakeVertexPolygon(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9	g_pTexturePolygon = NULL;		// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPolygon = NULL;	//���_�o�b�t�@�̃|�C���^
Mine mine;

int g_nCounterEnemyAnim;	//�A�j���[�V�����p
int g_nPattenEnemyAnim;		//�A�j���[�V�����p
int InvisibleCount;			//���L������_�ł�����悤
int PlayerMoveKey;			//�ǂ̕����ɓ��������̕ϐ�
int SpawnCount;				//�����p
bool SpawnFlag;				//�����p
bool KeyFlag;				//���L�����𓮂������������Ȃ����̃t���O

//=============================================================================
// ����������
//=============================================================================
void InitPolygon(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//�����ݒ�
	mine.pos = D3DXVECTOR3(0, 0, 0);
	mine.rot = D3DXVECTOR3(0, 0, 0);
	mine.fAngle = atan2f(PLAYER_SIZE_X / 2, PLAYER_SIZE_Y / 2);
	mine.fLength = sqrtf((PLAYER_SIZE_X / 2) * (PLAYER_SIZE_X / 2) + (PLAYER_SIZE_Y / 2) * (PLAYER_SIZE_Y / 2));
	mine.iHP = MAX_LIFE;
	mine.bUse = false;
	mine.bHit = false;
	PlayerMoveKey = 3;
	KeyFlag = true;
	SpawnFlag = true;
	SpawnCount = 0;
	g_nCounterEnemyAnim = 0;
	g_nPattenEnemyAnim = 0;

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffPolygon,
		NULL);

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/playeranim.png", &g_pTexturePolygon);

	//���_�ݒ�
	MakeVertexPolygon(pDevice);

}

//=============================================================================
// �I������
//=============================================================================
void UninitPolygon(void)
{
	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffPolygon != NULL)
	{
		g_pVtxBuffPolygon->Release();
		g_pVtxBuffPolygon = NULL;
	}

	// �e�N�X�`���̊J��
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
	VERTEX_2D *pVtx;
	D3DXVECTOR3 *ePos[MAX_ENEMY];
	int bCount;

	ePos[0] = GetEnemy();			//�G�̈ʒu���Ƃ��Ă���
	ePos[1] = GetChase();			//�G�̈ʒu���Ƃ��Ă���
	ePos[2] = GetMoody();			//�G�̈ʒu���Ƃ��Ă���
	ePos[3] = GetSilly();			//�G�̈ʒu���Ƃ��Ă���
	bCount = GetBulletCount();		//�e�̏����Ƃ��Ă���

	if (SpawnFlag == true || mine.bHit == false) {
		g_nCounterEnemyAnim++;
	}

	//�A�j���[�V��������
	if (g_nCounterEnemyAnim % 6 == 0)
	{
		g_nPattenEnemyAnim = (g_nPattenEnemyAnim + 1) % MAX_PATTERN;
	}

	if (g_nCounterEnemyAnim % 15 == 0) {

		//���b�N
		g_pVtxBuffPolygon->Lock(0, 0, (void**)&pVtx, 0);
		// �e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(g_nPattenEnemyAnim*(1.0f / MAX_PATTERN) + 1.0f, 0);
		pVtx[1].tex = D3DXVECTOR2(g_nPattenEnemyAnim*(1.0f / MAX_PATTERN) / MAX_PATTERN, 0);
		pVtx[2].tex = D3DXVECTOR2(g_nPattenEnemyAnim*(1.0f / MAX_PATTERN) + 1.0f, 1);
		pVtx[3].tex = D3DXVECTOR2(g_nPattenEnemyAnim*(1.0f / MAX_PATTERN) / MAX_PATTERN, 1);
		//���b�N����
		g_pVtxBuffPolygon->Unlock();

	}

	//TRUE��������ȉ��̏��������s
	if (SpawnFlag == TRUE) {
		SetSpawn();		//���L�����𕜊�������
		SetUse(true);	//������\��������
	}

	//FALSE��������ȉ��̏��������s
	if (SpawnFlag == false) {
		SetUse(false);	//�������B��
	}

	for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++) {
		//�G�Ǝ��L�������Ԃ������Ƃ��̏���
		if (Collision(*ePos[nCntEnemy], mine.pos, 23, PLAYER_SIZE_Y / 2) && mine.bHit == false && mine.iHP != 0 && mine.bUse == true) {
			mine.bHit = true;
			SetPlayerKey(false);
			SetChaseMoveKey(false);		//�G�𓮂��悤�ɂ���
			SetAmbushMoveKey(false);	//�G�𓮂��悤�ɂ���
			SetMoodyMoveKey(false);		//�G�𓮂��悤�ɂ���
			SetSillyMoveKey(false);		//�G�𓮂��悤�ɂ���
			SetTimerKey(false);
			SubLife(1);					//���C�t�����炷
			ResetChase();
			SetExplosion(mine.pos);
			Play(SOUND_LABEL_SE_EXPLOSION000);
		}
	}

	//������HP��0�̏ꍇ
	if (mine.iHP == 0) {
		KeyFlag = false;
		SetFade(MODE_RESULT);
	}

	//bHit(�Ԃ������Ƃ�)��true�������ꍇ�̏���
	if (mine.bHit == true) {
		InvisiblePlayer();
	}

	//���ꂪtrue�̎��Ɉړ�����悤�ɂȂ�
	if (KeyFlag == true) {

		//	��ړ�
		if (GetKeyboardPress(DIK_UP)) {
			PlayerMoveKey = 1;
		}

		//	���ړ�
		else if (GetKeyboardPress(DIK_DOWN)) {
			PlayerMoveKey = 2;
		}

		//	���ړ�
		else if (GetKeyboardPress(DIK_LEFT)) {
			PlayerMoveKey = 3;
		}

		//	�E�ړ�
		else if (GetKeyboardPress(DIK_RIGHT)) {
			PlayerMoveKey = 4;
		}


		//�v���C���[�̈ړ�����
		//������Ɉړ�
		if (PlayerMoveKey == 1) {
			mine.pos.y -= MAX_SPEED;
			//���b�N
			g_pVtxBuffPolygon->Lock(0, 0, (void**)&pVtx, 0);
			pVtx[3].tex = D3DXVECTOR2(g_nPattenEnemyAnim*(1.0f / MAX_PATTERN), 0);
			pVtx[2].tex = D3DXVECTOR2(g_nPattenEnemyAnim*(1.0f / MAX_PATTERN), 1);
			pVtx[1].tex = D3DXVECTOR2(g_nPattenEnemyAnim*(1.0f / MAX_PATTERN) + 1.0f / MAX_PATTERN, 0);
			pVtx[0].tex = D3DXVECTOR2(g_nPattenEnemyAnim*(1.0f / MAX_PATTERN) + 1.0f / MAX_PATTERN, 1);
			//���b�N����
			g_pVtxBuffPolygon->Unlock();
			if (GetKeyboardTrigger(DIK_SPACE)) {
				if (bCount != 0) {
					SetBullet(mine.pos, D3DXVECTOR3(0, -7, 0), 80);
					SubBulletCount(1);
				}
			}
		}

		//�������Ɉړ�
		else if (PlayerMoveKey == 2) {
			mine.pos.y += MAX_SPEED;
			//���b�N
			g_pVtxBuffPolygon->Lock(0, 0, (void**)&pVtx, 0);
			pVtx[0].tex = D3DXVECTOR2(g_nPattenEnemyAnim*(1.0f / MAX_PATTERN), 0);
			pVtx[1].tex = D3DXVECTOR2(g_nPattenEnemyAnim*(1.0f / MAX_PATTERN), 1);
			pVtx[2].tex = D3DXVECTOR2(g_nPattenEnemyAnim*(1.0f / MAX_PATTERN) + 1.0f / MAX_PATTERN, 0);
			pVtx[3].tex = D3DXVECTOR2(g_nPattenEnemyAnim*(1.0f / MAX_PATTERN) + 1.0f / MAX_PATTERN, 1);
			//���b�N����
			g_pVtxBuffPolygon->Unlock();
			if (GetKeyboardTrigger(DIK_SPACE)) {
				if (bCount != 0) {
					SetBullet(mine.pos, D3DXVECTOR3(0, 7, 0), 80);
					SubBulletCount(1);
				}
			}
		}

		//���Ɉړ�
		else if (PlayerMoveKey == 3) {
			mine.pos.x -= MAX_SPEED;
			//���b�N
			g_pVtxBuffPolygon->Lock(0, 0, (void**)&pVtx, 0);
			pVtx[0].tex = D3DXVECTOR2(g_nPattenEnemyAnim*(1.0f / MAX_PATTERN) + 1.0f / MAX_PATTERN, 0);
			pVtx[1].tex = D3DXVECTOR2(g_nPattenEnemyAnim*(1.0f / MAX_PATTERN), 0);
			pVtx[2].tex = D3DXVECTOR2(g_nPattenEnemyAnim*(1.0f / MAX_PATTERN) + 1.0f / MAX_PATTERN, 1);
			pVtx[3].tex = D3DXVECTOR2(g_nPattenEnemyAnim*(1.0f / MAX_PATTERN), 1);
			//���b�N����
			g_pVtxBuffPolygon->Unlock();
			if (GetKeyboardTrigger(DIK_SPACE)) {
				if (bCount != 0) {
					SetBullet(mine.pos, D3DXVECTOR3(-7, 0, 0), 80);
					SubBulletCount(1);
				}
			}
		}

		//�E�Ɉړ�
		else if (PlayerMoveKey == 4) {
			mine.pos.x += MAX_SPEED;
			//���b�N
			g_pVtxBuffPolygon->Lock(0, 0, (void**)&pVtx, 0);
			pVtx[0].tex = D3DXVECTOR2(g_nPattenEnemyAnim*(1.0f / MAX_PATTERN), 0);
			pVtx[2].tex = D3DXVECTOR2(g_nPattenEnemyAnim*(1.0f / MAX_PATTERN), 1);
			pVtx[1].tex = D3DXVECTOR2(g_nPattenEnemyAnim*(1.0f / MAX_PATTERN) + 1.0f / MAX_PATTERN, 0);
			pVtx[3].tex = D3DXVECTOR2(g_nPattenEnemyAnim*(1.0f / MAX_PATTERN) + 1.0f / MAX_PATTERN, 1);
			//���b�N����
			g_pVtxBuffPolygon->Unlock();
			if (GetKeyboardTrigger(DIK_SPACE)) {
				if (bCount != 0) {
					SetBullet(mine.pos, D3DXVECTOR3(7, 0, 0), 80);
					SubBulletCount(1);
				}
			}
		}

		PrintDebug("\n");
		PrintDebug("�W�����L�[�̏��\n");
		PrintDebug("Player Position(X:%f,Y:%f,Z:%f)\n", mine.pos.x, mine.pos.y, mine.pos.z);
		PrintDebug("Player Rotation(X:%f,Y:%f,Z:%f)\n", mine.rot.x, mine.rot.y, mine.rot.z);
		PrintDebug("\n");

	}

	{

		//���b�N
		g_pVtxBuffPolygon->Lock(0, 0, (void**)&pVtx, 0);

		//���_���W�̐ݒ�
		pVtx[0].pos.x = mine.pos.x - sinf(mine.fAngle - mine.rot.z)*mine.fLength;
		pVtx[0].pos.y = mine.pos.y - cosf(mine.fAngle - mine.rot.z)*mine.fLength;
		pVtx[0].pos.z = 0.0f;

		pVtx[1].pos.x = mine.pos.x + sinf(mine.fAngle + mine.rot.z)*mine.fLength;
		pVtx[1].pos.y = mine.pos.y - cosf(mine.fAngle + mine.rot.z)*mine.fLength;
		pVtx[1].pos.z = 0.0f;

		pVtx[2].pos.x = mine.pos.x - sinf(mine.fAngle + mine.rot.z)*mine.fLength;
		pVtx[2].pos.y = mine.pos.y + cosf(mine.fAngle + mine.rot.z)*mine.fLength;
		pVtx[2].pos.z = 0.0f;

		pVtx[3].pos.x = mine.pos.x + sinf(mine.fAngle - mine.rot.z)*mine.fLength;
		pVtx[3].pos.y = mine.pos.y + cosf(mine.fAngle - mine.rot.z)*mine.fLength;
		pVtx[3].pos.z = 0.0f;

		//���b�N����
		g_pVtxBuffPolygon->Unlock();

	}

}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawPolygon(void)
{
	if (!mine.bUse)
		return;
	//�f�o�C�X���擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//�f�[�^�X�g���[���ɃZ�b�g
	pDevice->SetStreamSource(0, g_pVtxBuffPolygon, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTexturePolygon);

	// �|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

}

//=============================================================================
// ���_���̍쐬
//=============================================================================
void MakeVertexPolygon(LPDIRECT3DDEVICE9 pDevice)
{

	VERTEX_2D *pVtx;

	//���b�N
	g_pVtxBuffPolygon->Lock(0, 0, (void**)&pVtx, 0);

	// ���_���W�̐ݒ�
	pVtx[0].pos.x = mine.pos.x - sinf(mine.fAngle - mine.rot.z)*mine.fLength;
	pVtx[0].pos.y = mine.pos.y - cosf(mine.fAngle - mine.rot.z)*mine.fLength;
	pVtx[0].pos.z = 0.0f;

	pVtx[1].pos.x = mine.pos.x + sinf(mine.fAngle + mine.rot.z)*mine.fLength;
	pVtx[1].pos.y = mine.pos.y - cosf(mine.fAngle + mine.rot.z)*mine.fLength;
	pVtx[1].pos.z = 0.0f;

	pVtx[2].pos.x = mine.pos.x - sinf(-mine.fAngle + mine.rot.z)*mine.fLength;
	pVtx[2].pos.y = mine.pos.y - cosf(-mine.fAngle + mine.rot.z)*mine.fLength;
	pVtx[2].pos.z = 0.0f;

	pVtx[3].pos.x = mine.pos.x + sinf(mine.fAngle - mine.rot.z)*mine.fLength;
	pVtx[3].pos.y = mine.pos.y + cosf(mine.fAngle - mine.rot.z)*mine.fLength;
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
	pVtx[0].tex = D3DXVECTOR2(g_nPattenEnemyAnim*(1.0f / MAX_PATTERN) + 1.0f / MAX_PATTERN, 0);
	pVtx[1].tex = D3DXVECTOR2(g_nPattenEnemyAnim*(1.0f / MAX_PATTERN), 0);
	pVtx[2].tex = D3DXVECTOR2(g_nPattenEnemyAnim*(1.0f / MAX_PATTERN) + 1.0f / MAX_PATTERN, 1);
	pVtx[3].tex = D3DXVECTOR2(g_nPattenEnemyAnim*(1.0f / MAX_PATTERN), 1);

	//���b�N����
	g_pVtxBuffPolygon->Unlock();

}

D3DXVECTOR3 GetMinePos(void) {
	return mine.pos;
}

//���L�������`�J�`�J�����鏈��
void InvisiblePlayer(void) {

	if (mine.bUse && InvisibleCount % 5 == 0) {
		mine.bUse = false;
	}
	else if (!mine.bUse && InvisibleCount % 5 == 0) {
		mine.bUse = true;
	}
	InvisibleCount++;
	if (InvisibleCount == 60)
	{
		InvisibleCount = 0;
		mine.bHit = false;
		mine.bUse = false;
		SpawnFlag = TRUE;
	}
}

void SetPlayer(D3DXVECTOR3 pos) {

	if (mine.bUse == false)
	{
		mine.pos = pos;
		mine.bUse = true;
	}
}

void SetSpawn(void) {

	D3DXVECTOR3 *ePos[MAX_ENEMY];	//�G�̏��p
	VERTEX_2D *pVtx;
	mine.bUse = true;
	ePos[0] = GetEnemy();
	ePos[1] = GetChase();
	ePos[2] = GetMoody();
	ePos[3] = GetSilly();
	mine.pos = D3DXVECTOR3(1190.0f, 100.0f, 0.0f);
	ePos[0]->x = 590;
	ePos[0]->y = 350;
	ePos[1]->x = 690;
	ePos[1]->y = 350;
	ePos[2]->x = 590;
	ePos[2]->y = 400;
	ePos[3]->x = 690;
	ePos[3]->y = 400;

	SpawnCount++;

	//���b�N
	g_pVtxBuffPolygon->Lock(0, 0, (void**)&pVtx, 0);
	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(g_nPattenEnemyAnim*(1.0f / MAX_PATTERN) + 1.0f / MAX_PATTERN, 0);
	pVtx[1].tex = D3DXVECTOR2(g_nPattenEnemyAnim*(1.0f / MAX_PATTERN), 0);
	pVtx[2].tex = D3DXVECTOR2(g_nPattenEnemyAnim*(1.0f / MAX_PATTERN) + 1.0f / MAX_PATTERN, 1);
	pVtx[3].tex = D3DXVECTOR2(g_nPattenEnemyAnim*(1.0f / MAX_PATTERN), 1);
	//���b�N����
	g_pVtxBuffPolygon->Unlock();

	if (SpawnCount == 120) {
		KeyFlag = 1;
		Reset();
		SetAmbushMoveKey(TRUE);		//�G�𓮂��悤�ɂ���
		SetChaseMoveKey(TRUE);		//�G�𓮂��悤�ɂ���
		SetMoodyMoveKey(TRUE);		//�G�𓮂��悤�ɂ���
		SetSillyMoveKey(TRUE);		//�G�𓮂��悤�ɂ���
		SetTimerKey(true);
		SpawnFlag = false;
		SpawnCount = 0;
	}
}

void SetPosition(D3DXVECTOR3 pos) {
	mine.pos = pos;
}

int GetKey(void) {
	return PlayerMoveKey;
}

int GetPlayerHP(void) {
	return 	mine.iHP;
}

void SubLife(int Life) {
	mine.iHP -= Life;
}

void SetPlayerKey(bool key) {
	KeyFlag = key;
}