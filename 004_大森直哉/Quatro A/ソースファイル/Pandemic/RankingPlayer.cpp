//=============================================================================
//
// ランキングプレイヤー(でかいほう）処理 [RankingPlayer.h]
// Author : NAOYA OMORI
//
//=============================================================================
#include "rankingplayer.h"

//*****************************************************************************
// マクロ定義宣言
//*****************************************************************************
#define PLAYER_SIZE_X (115)
#define PLAYER_SIZE_Y (115)
#define MAX_PATTERN (4)
#define TITLEPLAYER_SPEED (5.0f)
#define TITLEPLAYER_ROTATION (0.5f)

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void MakeVertexRankingPlayer(LPDIRECT3DDEVICE9 pDevice);
int g_nCounterRankingPlayerAnim;
int g_nPattenRankingPlayerAnim;
float g_RankingPlayerspeed;
float g_RankingPlayerrot;

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9	g_pTextureRankingPlayer = NULL;		// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffRankingPlayer = NULL;	//頂点バッファのポインタ
RankingPlayer player;

//=============================================================================
// 初期化処理
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

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffRankingPlayer,
		NULL);

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/playeranim.png", &g_pTextureRankingPlayer);

	//頂点設定
	MakeVertexRankingPlayer(pDevice);

}

//=============================================================================
// 終了処理
//=============================================================================
void UninitRankingPlayer(void)
{
	// 頂点バッファの開放
	if (g_pVtxBuffRankingPlayer != NULL)
	{
		g_pVtxBuffRankingPlayer->Release();
		g_pVtxBuffRankingPlayer = NULL;
	}

	// テクスチャの開放
	if (g_pTextureRankingPlayer != NULL)
	{
		g_pTextureRankingPlayer->Release();
		g_pTextureRankingPlayer = NULL;
	}

}
//=============================================================================
// 更新処理
//=============================================================================
void UpdateRankingPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	VERTEX_2D *pVtx;

	g_nCounterRankingPlayerAnim++;

	g_pVtxBuffRankingPlayer->Lock(0, 0, (void**)&pVtx, 0);

	//右に移動
	if (player.pos.x != 865) {
		player.pos.x += g_RankingPlayerspeed;
		player.rot.z += 0.056f;
	}
	else
	{
		//テクスチャ座標の設定
		//特定の位置についたらアニメーション開始
		pVtx[0].tex = D3DXVECTOR2(g_nPattenRankingPlayerAnim*(1.0f / MAX_PATTERN), 0);
		pVtx[2].tex = D3DXVECTOR2(g_nPattenRankingPlayerAnim*(1.0f / MAX_PATTERN), 1);
		pVtx[1].tex = D3DXVECTOR2(g_nPattenRankingPlayerAnim*(1.0f / MAX_PATTERN) + 1.0f / MAX_PATTERN, 0);
		pVtx[3].tex = D3DXVECTOR2(g_nPattenRankingPlayerAnim*(1.0f / MAX_PATTERN) + 1.0f / MAX_PATTERN, 1);

		//アニメーション処理
		if (g_nCounterRankingPlayerAnim % 6 == 0)
		{
			g_nPattenRankingPlayerAnim = (g_nPattenRankingPlayerAnim + 1) % MAX_PATTERN;
		}
	}

	// 頂点座標の設定
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

	//ロック解除
	g_pVtxBuffRankingPlayer->Unlock();

}

//=============================================================================
// 描画処理
//=============================================================================
void DrawRankingPlayer(void)
{
	////true以外は表示しない
	//if (!player.bUse == true)
	//	return;

	//デバイスを取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//データストリームにセット
	pDevice->SetStreamSource(0, g_pVtxBuffRankingPlayer, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, g_pTextureRankingPlayer);

	// ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}

//=============================================================================
// 頂点情報の作成
//=============================================================================
void MakeVertexRankingPlayer(LPDIRECT3DDEVICE9 pDevice)
{

	VERTEX_2D *pVtx;

	//ロック
	g_pVtxBuffRankingPlayer->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点座標の設定
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

	// rhwの設定
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	// 頂点カラーの設定
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);//RGBAの色を入れる
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	//テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(g_nPattenRankingPlayerAnim*(1.0f / MAX_PATTERN), 0);
	pVtx[2].tex = D3DXVECTOR2(g_nPattenRankingPlayerAnim*(1.0f / MAX_PATTERN), 1);
	pVtx[1].tex = D3DXVECTOR2(g_nPattenRankingPlayerAnim*(1.0f / MAX_PATTERN) + 1.0f / MAX_PATTERN, 0);
	pVtx[3].tex = D3DXVECTOR2(g_nPattenRankingPlayerAnim*(1.0f / MAX_PATTERN) + 1.0f / MAX_PATTERN, 1);

	//ロック解除
	g_pVtxBuffRankingPlayer->Unlock();

}