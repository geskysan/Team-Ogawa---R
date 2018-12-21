//=============================================================================
//
// �|���S������ [PressEnter.cpp]
// Author : NAOYA OMORI
//
//=============================================================================
#include "PressEnter.h"

//*****************************************************************************
// �}�N����`�錾
//*****************************************************************************
#define PRESSENTER_SIZE_X (300)
#define PRESSENTER_SIZE_Y (50)
#define MAX_ENTER (3)

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void MakeVertexPressEnter(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9	g_pTexturePressEnter = NULL;		// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPressEnter = NULL;	//���_�o�b�t�@�̃|�C���^
Enter enter[MAX_ENTER];
int g_col;

//=============================================================================
// ����������
//=============================================================================
void InitPressEnter(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	int nCntEnter;

	//�����ݒ�
	for (nCntEnter = 0; nCntEnter < MAX_ENTER; nCntEnter++) {
		enter[nCntEnter].pos = D3DXVECTOR3(0, 0, 0);
		enter[nCntEnter].rot = D3DXVECTOR3(0, 0, 0);
		enter[nCntEnter].fAngle = atan2f(PRESSENTER_SIZE_X / 2, PRESSENTER_SIZE_Y / 2);
		enter[nCntEnter].fLength = sqrtf((PRESSENTER_SIZE_X / 2) * (PRESSENTER_SIZE_X / 2) + (PRESSENTER_SIZE_Y / 2) * (PRESSENTER_SIZE_Y / 2));
		enter[nCntEnter].bUse = false;
	}

	g_col = 0;

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_ENTER,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffPressEnter,
		NULL);

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/press_enter.png", &g_pTexturePressEnter);

	//���_�ݒ�
	MakeVertexPressEnter(pDevice);

}

//=============================================================================
// �I������
//=============================================================================
void UninitPressEnter(void)
{
	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffPressEnter != NULL)
	{
		g_pVtxBuffPressEnter->Release();
		g_pVtxBuffPressEnter = NULL;
	}

	// �e�N�X�`���̊J��
	if (g_pTexturePressEnter != NULL)
	{
		g_pTexturePressEnter->Release();
		g_pTexturePressEnter = NULL;
	}

}
//=============================================================================
// �X�V����
//=============================================================================
void UpdatePressEnter(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	VERTEX_2D *pVtx;

	g_col -= 10;

	for (int nCntEnter = 0; nCntEnter < MAX_ENTER; nCntEnter++) {

		//���b�N
		g_pVtxBuffPressEnter->Lock(0, 0, (void**)&pVtx, 0);

		//���_���W�̐ݒ�
		pVtx[0].pos.x = enter[nCntEnter].pos.x - sinf(enter[nCntEnter].fAngle - enter[nCntEnter].rot.z)*enter[nCntEnter].fLength;
		pVtx[0].pos.y = enter[nCntEnter].pos.y - cosf(enter[nCntEnter].fAngle - enter[nCntEnter].rot.z)*enter[nCntEnter].fLength;
		pVtx[0].pos.z = 0.0f;

		pVtx[1].pos.x = enter[nCntEnter].pos.x + sinf(enter[nCntEnter].fAngle + enter[nCntEnter].rot.z)*enter[nCntEnter].fLength;
		pVtx[1].pos.y = enter[nCntEnter].pos.y - cosf(enter[nCntEnter].fAngle + enter[nCntEnter].rot.z)*enter[nCntEnter].fLength;
		pVtx[1].pos.z = 0.0f;

		pVtx[2].pos.x = enter[nCntEnter].pos.x - sinf(enter[nCntEnter].fAngle + enter[nCntEnter].rot.z)*enter[nCntEnter].fLength;
		pVtx[2].pos.y = enter[nCntEnter].pos.y + cosf(enter[nCntEnter].fAngle + enter[nCntEnter].rot.z)*enter[nCntEnter].fLength;
		pVtx[2].pos.z = 0.0f;

		pVtx[3].pos.x = enter[nCntEnter].pos.x + sinf(enter[nCntEnter].fAngle - enter[nCntEnter].rot.z)*enter[nCntEnter].fLength;
		pVtx[3].pos.y = enter[nCntEnter].pos.y + cosf(enter[nCntEnter].fAngle - enter[nCntEnter].rot.z)*enter[nCntEnter].fLength;
		pVtx[3].pos.z = 0.0f;

		// ���_�J���[�̐ݒ�
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, g_col);//RGBA�̐F������
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, g_col);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, g_col);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, g_col);

		//���b�N����
		g_pVtxBuffPressEnter->Unlock();
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawPressEnter(void)
{
	for (int nCntEnter = 0; nCntEnter < MAX_ENTER; nCntEnter++) {

		if (!enter[nCntEnter].bUse)
			return;

		//�f�o�C�X���擾
		LPDIRECT3DDEVICE9 pDevice = GetDevice();

		//�f�[�^�X�g���[���ɃZ�b�g
		pDevice->SetStreamSource(0, g_pVtxBuffPressEnter, 0, sizeof(VERTEX_2D));

		// ���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_2D);

		// �e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTexturePressEnter);

		// �|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4 * nCntEnter, 2);
	}
}
//=============================================================================
// ���_���̍쐬
//=============================================================================
void MakeVertexPressEnter(LPDIRECT3DDEVICE9 pDevice)
{

	VERTEX_2D *pVtx;
	for (int nCntEnter = 0; nCntEnter < MAX_ENTER; nCntEnter++) {
		//���b�N
		g_pVtxBuffPressEnter->Lock(0, 0, (void**)&pVtx, 0);

		// ���_���W�̐ݒ�
		pVtx[0].pos.x = enter[nCntEnter].pos.x - sinf(enter[nCntEnter].fAngle - enter[nCntEnter].rot.z)*enter[nCntEnter].fLength;
		pVtx[0].pos.y = enter[nCntEnter].pos.y - cosf(enter[nCntEnter].fAngle - enter[nCntEnter].rot.z)*enter[nCntEnter].fLength;
		pVtx[0].pos.z = 0.0f;

		pVtx[1].pos.x = enter[nCntEnter].pos.x + sinf(enter[nCntEnter].fAngle + enter[nCntEnter].rot.z)*enter[nCntEnter].fLength;
		pVtx[1].pos.y = enter[nCntEnter].pos.y - cosf(enter[nCntEnter].fAngle + enter[nCntEnter].rot.z)*enter[nCntEnter].fLength;
		pVtx[1].pos.z = 0.0f;

		pVtx[2].pos.x = enter[nCntEnter].pos.x - sinf(enter[nCntEnter].fAngle + enter[nCntEnter].rot.z)*enter[nCntEnter].fLength;
		pVtx[2].pos.y = enter[nCntEnter].pos.y + cosf(enter[nCntEnter].fAngle + enter[nCntEnter].rot.z)*enter[nCntEnter].fLength;
		pVtx[2].pos.z = 0.0f;

		pVtx[3].pos.x = enter[nCntEnter].pos.x + sinf(enter[nCntEnter].fAngle - enter[nCntEnter].rot.z)*enter[nCntEnter].fLength;
		pVtx[3].pos.y = enter[nCntEnter].pos.y + cosf(enter[nCntEnter].fAngle - enter[nCntEnter].rot.z)*enter[nCntEnter].fLength;
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
		pVtx[0].tex = D3DXVECTOR2(0, 0);
		pVtx[1].tex = D3DXVECTOR2(1, 0);
		pVtx[2].tex = D3DXVECTOR2(0, 1);
		pVtx[3].tex = D3DXVECTOR2(1, 1);

		//���b�N����
		g_pVtxBuffPressEnter->Unlock();
	}
}


void SetEnterPosition(D3DXVECTOR3 pos) {

	for (int nCntEnter = 0; nCntEnter < MAX_ENTER; nCntEnter++) {
		if (enter[nCntEnter].bUse == false)
		{
			enter[nCntEnter].pos = pos;
			enter[nCntEnter].bUse = true;
		}
	}
}