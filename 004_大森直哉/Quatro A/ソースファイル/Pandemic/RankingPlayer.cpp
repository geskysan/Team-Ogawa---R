//=============================================================================
//
// �����L���O�v���C���[(�ł����ق��j���� [RankingPlayer.h]
// Author : NAOYA OMORI
//
//=============================================================================
#include "rankingplayer.h"

//*****************************************************************************
// �}�N����`�錾
//*****************************************************************************
#define PLAYER_SIZE_X (115)
#define PLAYER_SIZE_Y (115)
#define MAX_PATTERN (4)
#define TITLEPLAYER_SPEED (5.0f)
#define TITLEPLAYER_ROTATION (0.5f)

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void MakeVertexRankingPlayer(LPDIRECT3DDEVICE9 pDevice);
int g_nCounterRankingPlayerAnim;
int g_nPattenRankingPlayerAnim;
float g_RankingPlayerspeed;
float g_RankingPlayerrot;

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9	g_pTextureRankingPlayer = NULL;		// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffRankingPlayer = NULL;	//���_�o�b�t�@�̃|�C���^
RankingPlayer player;

//=============================================================================
// ����������
//=============================================================================
void InitRankingPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	player.pos = D3DXVECTOR3(-255, 100, 0);
	player.rot = D3DXVECTOR3(0, 0, 0);
	player.fAngle = atan2f(PLAYER_SIZE_X / 2, PLAYER_SIZE_Y / 2);
	player.fLength = sqrtf((PLAYER_SIZE_X / 2) * (PLAYER_SIZE_X / 2) + (PLAYER_SIZE_Y / 2) * (PLAYER_SIZE_Y / 2));
	player.bUse = true;
	g_RankingPlayerspeed = TITLEPLAYER_SPEED;
	g_RankingPlayerrot = TITLEPLAYER_ROTATION;
	g_nCounterRankingPlayerAnim = 0;
	g_nPattenRankingPlayerAnim = 0;

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffRankingPlayer,
		NULL);

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/playeranim.png", &g_pTextureRankingPlayer);

	//���_�ݒ�
	MakeVertexRankingPlayer(pDevice);

}

//=============================================================================
// �I������
//=============================================================================
void UninitRankingPlayer(void)
{
	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffRankingPlayer != NULL)
	{
		g_pVtxBuffRankingPlayer->Release();
		g_pVtxBuffRankingPlayer = NULL;
	}

	// �e�N�X�`���̊J��
	if (g_pTextureRankingPlayer != NULL)
	{
		g_pTextureRankingPlayer->Release();
		g_pTextureRankingPlayer = NULL;
	}

}
//=============================================================================
// �X�V����
//=============================================================================
void UpdateRankingPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	VERTEX_2D *pVtx;

	g_nCounterRankingPlayerAnim++;

	g_pVtxBuffRankingPlayer->Lock(0, 0, (void**)&pVtx, 0);

	//�E�Ɉړ�
	if (player.pos.x != 865) {
		player.pos.x += g_RankingPlayerspeed;
		player.rot.z += 0.056f;
	}
	else
	{
		//�e�N�X�`�����W�̐ݒ�
		//����̈ʒu�ɂ�����A�j���[�V�����J�n
		pVtx[0].tex = D3DXVECTOR2(g_nPattenRankingPlayerAnim*(1.0f / MAX_PATTERN), 0);
		pVtx[2].tex = D3DXVECTOR2(g_nPattenRankingPlayerAnim*(1.0f / MAX_PATTERN), 1);
		pVtx[1].tex = D3DXVECTOR2(g_nPattenRankingPlayerAnim*(1.0f / MAX_PATTERN) + 1.0f / MAX_PATTERN, 0);
		pVtx[3].tex = D3DXVECTOR2(g_nPattenRankingPlayerAnim*(1.0f / MAX_PATTERN) + 1.0f / MAX_PATTERN, 1);

		//�A�j���[�V��������
		if (g_nCounterRankingPlayerAnim % 6 == 0)
		{
			g_nPattenRankingPlayerAnim = (g_nPattenRankingPlayerAnim + 1) % MAX_PATTERN;
		}
	}

	// ���_���W�̐ݒ�
	pVtx[0].pos.x = player.pos.x - sinf(player.fAngle - player.rot.z)*player.fLength;
	pVtx[0].pos.y = player.pos.y - cosf(player.fAngle - player.rot.z)*player.fLength;
	pVtx[0].pos.z = 0.0f;

	pVtx[1].pos.x = player.pos.x + sinf(player.fAngle + player.rot.z)*player.fLength;
	pVtx[1].pos.y = player.pos.y - cosf(player.fAngle + player.rot.z)*player.fLength;
	pVtx[1].pos.z = 0.0f;

	pVtx[2].pos.x = player.pos.x - sinf(player.fAngle + player.rot.z)*player.fLength;
	pVtx[2].pos.y = player.pos.y + cosf(player.fAngle + player.rot.z)*player.fLength;
	pVtx[2].pos.z = 0.0f;

	pVtx[3].pos.x = player.pos.x + sinf(player.fAngle - player.rot.z)*player.fLength;
	pVtx[3].pos.y = player.pos.y + cosf(player.fAngle - player.rot.z)*player.fLength;
	pVtx[3].pos.z = 0.0f;

	//���b�N����
	g_pVtxBuffRankingPlayer->Unlock();

}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawRankingPlayer(void)
{
	////true�ȊO�͕\�����Ȃ�
	//if (!player.bUse == true)
	//	return;

	//�f�o�C�X���擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//�f�[�^�X�g���[���ɃZ�b�g
	pDevice->SetStreamSource(0, g_pVtxBuffRankingPlayer, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureRankingPlayer);

	// �|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}

//=============================================================================
// ���_���̍쐬
//=============================================================================
void MakeVertexRankingPlayer(LPDIRECT3DDEVICE9 pDevice)
{

	VERTEX_2D *pVtx;

	//���b�N
	g_pVtxBuffRankingPlayer->Lock(0, 0, (void**)&pVtx, 0);

	// ���_���W�̐ݒ�
	pVtx[0].pos.x = player.pos.x - sinf(player.fAngle - player.rot.z)*player.fLength;
	pVtx[0].pos.y = player.pos.y - cosf(player.fAngle - player.rot.z)*player.fLength;
	pVtx[0].pos.z = 0.0f;

	pVtx[1].pos.x = player.pos.x + sinf(player.fAngle + player.rot.z)*player.fLength;
	pVtx[1].pos.y = player.pos.y - cosf(player.fAngle + player.rot.z)*player.fLength;
	pVtx[1].pos.z = 0.0f;

	pVtx[2].pos.x = player.pos.x - sinf(-player.fAngle + player.rot.z)*player.fLength;
	pVtx[2].pos.y = player.pos.y - cosf(-player.fAngle + player.rot.z)*player.fLength;
	pVtx[2].pos.z = 0.0f;

	pVtx[3].pos.x = player.pos.x + sinf(player.fAngle - player.rot.z)*player.fLength;
	pVtx[3].pos.y = player.pos.y + cosf(player.fAngle - player.rot.z)*player.fLength;
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
	pVtx[0].tex = D3DXVECTOR2(g_nPattenRankingPlayerAnim*(1.0f / MAX_PATTERN), 0);
	pVtx[2].tex = D3DXVECTOR2(g_nPattenRankingPlayerAnim*(1.0f / MAX_PATTERN), 1);
	pVtx[1].tex = D3DXVECTOR2(g_nPattenRankingPlayerAnim*(1.0f / MAX_PATTERN) + 1.0f / MAX_PATTERN, 0);
	pVtx[3].tex = D3DXVECTOR2(g_nPattenRankingPlayerAnim*(1.0f / MAX_PATTERN) + 1.0f / MAX_PATTERN, 1);

	//���b�N����
	g_pVtxBuffRankingPlayer->Unlock();

}