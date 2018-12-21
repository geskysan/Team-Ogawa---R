//=============================================================================
//
// ���U���g��ʏ��� [Result.cpp]
// Author : NAOYA OMORI
//
//=============================================================================
#include "Result.h"
#include "input.h"
#include "Fade.h"
#include "sound.h"
#include "rankingscore.h"
#include "ResultScore.h"
#include "TotalScore.h"
#include "EndGameScore.h"

//=============================================================================
// �v���g�^�C�v�錾
//=============================================================================
void MakeVertexResult(LPDIRECT3DDEVICE9 pDevice);

//=============================================================================
// �O���[�o���ϐ�
//=============================================================================
LPDIRECT3DTEXTURE9 g_pTextureResult = NULL;		//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffResult = NULL;

//=============================================================================
// ����������
//=============================================================================
void InitResult(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/Result.jpg", &g_pTextureResult);

	//���_���̍쐬
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY, FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffResult,
		NULL);

	MakeVertexResult(pDevice);

	InitResultScore();
	InitTotalScore();
	InitEndGameScore();

	Stop(SOUND_LABEL_BGM001);
	Play(SOUND_LABEL_BGM002);

}

//=============================================================================
// �I������
//=============================================================================
void UninitResult(void)
{
	//���_�o�b�t�@�̊J��
	if (g_pVtxBuffResult != NULL) {
		g_pVtxBuffResult->Release();
		g_pVtxBuffResult = NULL;
	}

	//�e�N�X�`���̊J��
	if (g_pTextureResult != NULL) {
		g_pTextureResult->Release();
		g_pTextureResult = NULL;
	}
	UninitResultScore();
	UninitTotalScore();
	UninitEndGameScore();
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateResult(void)
{
	if (GetKeyboardPress(DIK_RETURN) == true && GetFade() == FADE_NONE) {
		SetFade(MODE_RANKING);
	}
	UpdateResultScore();
	UpdateTotalScore();
	UpdateEndGameScore();
}
//=============================================================================
// �`�揈��
//=============================================================================
void DrawResult(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//�f�[�^�X�g���[���ɃZ�b�g
	pDevice->SetStreamSource(0, g_pVtxBuffResult, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureResult);

	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
	DrawResultScore();
	DrawTotalScore();
	DrawEndGameScore();
}

//=============================================================================
// ���_���̍쐬
//=============================================================================
void MakeVertexResult(LPDIRECT3DDEVICE9 pDevice)
{
	VERTEX_2D *pVtx;

	//���b�N
	g_pVtxBuffResult->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(0, 0, 0.0f);						//xy���W�ňʒu����
	pVtx[1].pos = D3DXVECTOR3(1280, 0, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0, 720, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(1280, 720, 0.0f);

	//rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//���_�J���[�̐ݒ�
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);			//RGBA�̐F������
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0, 0);
	pVtx[1].tex = D3DXVECTOR2(1, 0);
	pVtx[2].tex = D3DXVECTOR2(0, 1);
	pVtx[3].tex = D3DXVECTOR2(1, 1);

	//���b�N����
	g_pVtxBuffResult->Unlock();

}