//=============================================================================
//
// �ǂ̏��� [wall.cpp]
// Author : NAOYA OMORI
//
//=============================================================================
#include "wall.h"
#include "debugproc.h"
#include "Polygon.h"
#include "DebugProc.h"
#include "Enemy.h"
#include "collision.h"
#include "map.h"
#include "input.h"
#include "bullet.h"

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void MakeVertexWall(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// �}�N����`�錾
//*****************************************************************************
#define MIN_WALL (0)
#define WALL_SIZE_X (50)
#define WALL_SIZE_Y (50)
#define MAX_OBJ_X 26	//����
#define MAX_OBJ_Y 16	//�c��

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9	g_pTextureWall = NULL;	// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffWall = NULL;//���_�o�b�t�@�̃|�C���^

WALL g_wall[MAX_WALL];
bool WallContactFlag;

//=============================================================================
// ����������
//=============================================================================
void InitWall(void)
{

	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for (int nCntWall = 0; nCntWall < MAX_WALL; nCntWall++) {
		g_wall[nCntWall].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_wall[nCntWall].rot = D3DXVECTOR3(0, 0, 0);
		g_wall[nCntWall].fAngleWall = atan2f(WALL_SIZE_X / 2, WALL_SIZE_Y / 2);
		g_wall[nCntWall].fLengthWall = sqrtf((WALL_SIZE_X / 2) * (WALL_SIZE_X / 2) + (WALL_SIZE_Y / 2) * (WALL_SIZE_Y / 2));
		g_wall[nCntWall].bUse = false;
	}

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_WALL,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffWall,
		NULL);

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/wall000.jpg", &g_pTextureWall);

	//���_�ݒ�
	MakeVertexWall(pDevice);

}

//=============================================================================
// �I������
//=============================================================================
void UninitWall(void)
{
	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffWall != NULL)
	{
		g_pVtxBuffWall->Release();
		g_pVtxBuffWall = NULL;
	}

	// �e�N�X�`���̊J��
	if (g_pTextureWall != NULL)
	{
		g_pTextureWall->Release();
		g_pTextureWall = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateWall(void)
{

	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXVECTOR3 pPos;				//���@�̏��p
	D3DXVECTOR3 *ePos[MAX_ENEMY];	//�G�̏��p
	VERTEX_2D *pVtx;
	int MoveFlag;					//�v���C���[�̓����蔻��p
	int nCntWall;

	pPos = GetMinePos();
	ePos[0] = GetEnemy();
	MoveFlag = GetKey();

	for (nCntWall = 0; nCntWall < MAX_WALL; nCntWall++) {
		if (g_wall[nCntWall].bUse == true) {
			g_pVtxBuffWall->Lock(0, 0, (void**)&pVtx, 0);

			pVtx += 4 * nCntWall;

			pVtx[0].pos.x = g_wall[nCntWall].pos.x - sinf(g_wall[nCntWall].fAngleWall - g_wall[nCntWall].rot.z)*g_wall[nCntWall].fLengthWall;
			pVtx[0].pos.y = g_wall[nCntWall].pos.y - cosf(g_wall[nCntWall].fAngleWall - g_wall[nCntWall].rot.z)*g_wall[nCntWall].fLengthWall;
			pVtx[0].pos.z = 0.0f;

			pVtx[1].pos.x = g_wall[nCntWall].pos.x + sinf(g_wall[nCntWall].fAngleWall + g_wall[nCntWall].rot.z)*g_wall[nCntWall].fLengthWall;
			pVtx[1].pos.y = g_wall[nCntWall].pos.y - cosf(g_wall[nCntWall].fAngleWall + g_wall[nCntWall].rot.z)*g_wall[nCntWall].fLengthWall;
			pVtx[1].pos.z = 0.0f;

			pVtx[2].pos.x = g_wall[nCntWall].pos.x - sinf(g_wall[nCntWall].fAngleWall + g_wall[nCntWall].rot.z)*g_wall[nCntWall].fLengthWall;
			pVtx[2].pos.y = g_wall[nCntWall].pos.y + cosf(g_wall[nCntWall].fAngleWall + g_wall[nCntWall].rot.z)*g_wall[nCntWall].fLengthWall;
			pVtx[2].pos.z = 0.0f;

			pVtx[3].pos.x = g_wall[nCntWall].pos.x + sinf(g_wall[nCntWall].fAngleWall - g_wall[nCntWall].rot.z)*g_wall[nCntWall].fLengthWall;
			pVtx[3].pos.y = g_wall[nCntWall].pos.y + cosf(g_wall[nCntWall].fAngleWall - g_wall[nCntWall].rot.z)*g_wall[nCntWall].fLengthWall;
			pVtx[3].pos.z = 0.0f;

			g_pVtxBuffWall->Unlock();
		}

		//�v���C���[�ƕǂ̓����蔻��
		if (isHit(g_wall[nCntWall].pos.x, g_wall[nCntWall].pos.y, 42.5f, 42.5f, pPos.x, pPos.y, 42.5f, 42.5f) == true) {

			if (MoveFlag == 1) {
				SetPosition(D3DXVECTOR3(pPos.x, pPos.y + MAX_SPEED, pPos.z));
			}
			if (MoveFlag == 2) {
				SetPosition(D3DXVECTOR3(pPos.x, pPos.y - MAX_SPEED, pPos.z));
			}
			if (MoveFlag == 3) {
				SetPosition(D3DXVECTOR3(pPos.x + MAX_SPEED, pPos.y, pPos.z));
			}
			if (MoveFlag == 4) {
				SetPosition(D3DXVECTOR3(pPos.x - MAX_SPEED, pPos.y, pPos.z));
			}
		}

		//�G�L�����̓����蔻��
		if (GetKeyboardPress(DIK_W))
		{
			ePos[0]->y -= 0.01f;
		}

		else if (GetKeyboardPress(DIK_S))
		{
			ePos[0]->y += 0.01f;
		}

		else if (GetKeyboardPress(DIK_A))
		{
			ePos[0]->x -= 0.01f;
		}

		else if (GetKeyboardPress(DIK_D))
		{
			ePos[0]->x += 0.01f;
		}

		//if (g_wall[nCntWall].bUse == TRUE) {

		//	fWallMaxX = g_wall[nCntWall].pos.x + 25.0f + 15.0f;
		//	fWallMinX = g_wall[nCntWall].pos.x - 25.0f - 15.0f;
		//	fWallMaxY = g_wall[nCntWall].pos.y + 25.0f + 15.0f;
		//	fWallMinY = g_wall[nCntWall].pos.y - 25.0f - 15.0f;

		//	double fRight = fWallMaxX - ePos[0]->x;
		//	double fLeft = fWallMinX - ePos[0]->x;
		//	double fBack = fWallMaxY - ePos[0]->y;
		//	double fFront = fWallMinY - ePos[0]->y;

		//	if (fWallMinX < ePos[0]->x && ePos[0]->x < fWallMaxX  && fWallMinY < ePos[0]->y && ePos[0]->y < fWallMaxY) {

		//		if (fRight < fLeft && fRight < fBack&& fRight < fFront) {
		//			ePos[0]->x = fWallMaxX;
		//			ePos[0]->x += 0.01f;
		//			ePos[0]->y += 0.01f;
		//			PrintDebug("MAX_X\n");	
		//		}
		//		else if (fLeft < fBack&& fLeft < fFront) {
		//			ePos[0]->x = fWallMinX;
		//			ePos[0]->x -= 0.01f;
		//			ePos[0]->y -= 0.01f;
		//			PrintDebug("MIN_X\n");
		//		}
		//		else if (fBack < fFront ) {
		//			ePos[0]->y = fWallMaxY;
		//			ePos[0]->x += 0.01f;
		//			ePos[0]->y += 0.01f;
		//			PrintDebug("MAX_Y\n");
		//		}
		//		else
		//		{
		//			ePos[0]->y = fWallMinY;
		//			ePos[0]->x -= 0.001f;
		//			ePos[0]->y -= 0.001f;
		//			PrintDebug("MIN_Y\n");
		//		}
		//	}
		//}
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawWall(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	int nCntWall;

	for (nCntWall = 0; nCntWall < MAX_WALL; nCntWall++) {

		if (g_wall[nCntWall].bUse == true) {

			//�f�[�^�X�g���[���ɃZ�b�g
			pDevice->SetStreamSource(0, g_pVtxBuffWall, 0, sizeof(VERTEX_2D));

			// ���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_2D);

			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureWall);

			// �|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntWall * 4, 2);

		}
	}
}

//=============================================================================
// ���_���̍쐬
//=============================================================================
void MakeVertexWall(LPDIRECT3DDEVICE9 pDevice)
{
	VERTEX_2D *pVtx;
	int nCutVtx;

	//���b�N
	g_pVtxBuffWall->Lock(0, 0, (void**)&pVtx, 0);

	for (nCutVtx = 0; nCutVtx < MAX_WALL; nCutVtx++) {

		// ���_���W�̐ݒ�
		pVtx[0].pos.x = g_wall[nCutVtx].pos.x - sinf(g_wall[nCutVtx].fAngleWall - g_wall[nCutVtx].rot.z)*g_wall[nCutVtx].fLengthWall;
		pVtx[0].pos.y = g_wall[nCutVtx].pos.y - cosf(g_wall[nCutVtx].fAngleWall - g_wall[nCutVtx].rot.z)*g_wall[nCutVtx].fLengthWall;
		pVtx[0].pos.z = 0.0f;

		pVtx[1].pos.x = g_wall[nCutVtx].pos.x + sinf(g_wall[nCutVtx].fAngleWall + g_wall[nCutVtx].rot.z)*g_wall[nCutVtx].fLengthWall;
		pVtx[1].pos.y = g_wall[nCutVtx].pos.y - cosf(g_wall[nCutVtx].fAngleWall + g_wall[nCutVtx].rot.z)*g_wall[nCutVtx].fLengthWall;
		pVtx[1].pos.z = 0.0f;

		pVtx[2].pos.x = g_wall[nCutVtx].pos.x - sinf(g_wall[nCutVtx].fAngleWall + g_wall[nCutVtx].rot.z)*g_wall[nCutVtx].fLengthWall;
		pVtx[2].pos.y = g_wall[nCutVtx].pos.y + cosf(g_wall[nCutVtx].fAngleWall + g_wall[nCutVtx].rot.z)*g_wall[nCutVtx].fLengthWall;
		pVtx[2].pos.z = 0.0f;

		pVtx[3].pos.x = g_wall[nCutVtx].pos.x + sinf(g_wall[nCutVtx].fAngleWall - g_wall[nCutVtx].rot.z)*g_wall[nCutVtx].fLengthWall;
		pVtx[3].pos.y = g_wall[nCutVtx].pos.y + cosf(g_wall[nCutVtx].fAngleWall - g_wall[nCutVtx].rot.z)*g_wall[nCutVtx].fLengthWall;
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
	g_pVtxBuffWall->Unlock();
}

void SetWall(D3DXVECTOR3 pos) {

	int nCntWall;

	for (nCntWall = 0; nCntWall < MAX_WALL; nCntWall++) {

		if (g_wall[nCntWall].bUse == false)
		{
			g_wall[nCntWall].pos = pos;
			g_wall[nCntWall].bUse = true;
			break;
		}
	}
}

//�ǂɂԂ����Ă��邩���Ȃ���
bool GetWallContactFlag(void) {
	return WallContactFlag;
}

WALL *GetWall(void) {
	return &g_wall[0];
}

bool Wallcollision(D3DXVECTOR3 pos) {
	float fWallMaxX, fWallMinX, fWallMaxY, fWallMinY;
	D3DXVECTOR3 ePos;	//�G�̏��p

	ePos = pos;
	for (int nCntWall = 0; nCntWall < MAX_WALL; nCntWall++) {
		if (g_wall[nCntWall].bUse == TRUE) {

			fWallMaxX = g_wall[nCntWall].pos.x + 25.0f + 15.0f;
			fWallMinX = g_wall[nCntWall].pos.x - 25.0f - 15.0f;
			fWallMaxY = g_wall[nCntWall].pos.y + 25.0f + 15.0f;
			fWallMinY = g_wall[nCntWall].pos.y - 25.0f - 15.0f;

			double fRight = fabs(fWallMaxX - ePos.x);
			double fLeft = fabs(ePos.x - fWallMinX);
			double fBack = fabs(fWallMaxY - ePos.y);
			double fFront = fabs(ePos.y - fWallMinY);

			if (fWallMinX < ePos.x && ePos.x < fWallMaxX  && fWallMinY < ePos.y && ePos.y < fWallMaxY) {

				if (fRight < fLeft && fRight < fBack&& fRight < fFront) {
					PrintDebug("MAX_X\n");
					return TRUE;
				}
				else if (fLeft < fBack&& fLeft < fFront) {
					PrintDebug("MIN_X\n");
					return TRUE;
				}
				else if (fBack < fFront) {
					PrintDebug("Max_Y\n");
					return TRUE;
				}
				else if (fBack > fFront) {
					PrintDebug("MIN_Y\n");
					return TRUE;
				}
			}
			return FALSE;
		}
	}
}