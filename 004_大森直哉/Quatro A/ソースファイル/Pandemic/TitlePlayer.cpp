//=============================================================================
//
// タイトルプレイヤー（でかいほう）処理 [TitlePlayer.cpp]
// Author : NAOYA OMORI
//
//=============================================================================
#include "titleplayer.h"

//*****************************************************************************
// マクロ定義宣言
//*****************************************************************************
#define PLAYER_SIZE_X (150)
#define PLAYER_SIZE_Y (150)
#define MAX_PATTERN (4)
#define TITLEPLAYER_SPEED (5.0f)
#define TITLEPLAYER_ROTATION (0.5f)

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void MakeVertexTitlePlayer(LPDIRECT3DDEVICE9 pDevice);
int g_nCounterTitlePlayerAnim;
int g_nPattenTitlePlayerAnim;
float g_speed;
float g_rot;

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9	g_pTextureTitlePlayer = NULL;		// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTitlePlayer = NULL;	//頂点バッファのポインタ
TitlePlayer player;

//=============================================================================
// 初期化処理
//=============================================================================
void InitTitlePlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	player.pos = D3DXVECTOR3(-255, 165, 0);
	player.rot = D3DXVECTOR3(0, 0, 0);
	player.fAngle = atan2f(PLAYER_SIZE_X / 2, PLAYER_SIZE_Y / 2);
	player.fLength = sqrtf((PLAYER_SIZE_X / 2) * (PLAYER_SIZE_X / 2) + (PLAYER_SIZE_Y / 2) * (PLAYER_SIZE_Y / 2));
	player.bUse = true;
	g_speed = TITLEPLAYER_SPEED;
	g_rot = TITLEPLAYER_ROTATION;
	g_nCounterTitlePlayerAnim = 0;
	g_nPattenTitlePlayerAnim = 0;

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffTitlePlayer,
		NULL);

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/playeranim.png", &g_pTextureTitlePlayer);

	//頂点設定
	MakeVertexTitlePlayer(pDevice);

}

//=============================================================================
// 終了処理
//=============================================================================
void UninitTitlePlayer(void)
{
	// 頂点バッファの開放
	if (g_pVtxBuffTitlePlayer != NULL)
	{
		g_pVtxBuffTitlePlayer->Release();
		g_pVtxBuffTitlePlayer = NULL;
	}

	// テクスチャの開放
	if (g_pTextureTitlePlayer != NULL)
	{
		g_pTextureTitlePlayer->Release();
		g_pTextureTitlePlayer = NULL;
	}

}
//=============================================================================
// 更新処理
//=============================================================================
void UpdateTitlePlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	VERTEX_2D *pVtx;

	g_nCounterTitlePlayerAnim++;

	g_pVtxBuffTitlePlayer->Lock(0, 0, (void**)&pVtx, 0);

	//右に移動
	if (player.pos.x != 1000) {
		player.pos.x += g_speed;
		player.rot.z += 0.05f;
	}
	else
	{
		//テクスチャ座標の設定
		//特定の位置についたらアニメーション開始
		pVtx[0].tex = D3DXVECTOR2(g_nPattenTitlePlayerAnim*(1.0f / MAX_PATTERN), 0);
		pVtx[2].tex = D3DXVECTOR2(g_nPattenTitlePlayerAnim*(1.0f / MAX_PATTERN), 1);
		pVtx[1].tex = D3DXVECTOR2(g_nPattenTitlePlayerAnim*(1.0f / MAX_PATTERN) + 1.0f / MAX_PATTERN, 0);
		pVtx[3].tex = D3DXVECTOR2(g_nPattenTitlePlayerAnim*(1.0f / MAX_PATTERN) + 1.0f / MAX_PATTERN, 1);

		//アニメーション処理
		if (g_nCounterTitlePlayerAnim % 6 == 0)
		{
			g_nPattenTitlePlayerAnim = (g_nPattenTitlePlayerAnim + 1) % MAX_PATTERN;
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
	g_pVtxBuffTitlePlayer->Unlock();

}

//=============================================================================
// 描画処理
//=============================================================================
void DrawTitlePlayer(void)
{
	////true以外は表示しない
	//if (!player.bUse == true)
	//	return;

	//デバイスを取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//データストリームにセット
	pDevice->SetStreamSource(0, g_pVtxBuffTitlePlayer, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, g_pTextureTitlePlayer);

	// ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}

//=============================================================================
// 頂点情報の作成
//=============================================================================
void MakeVertexTitlePlayer(LPDIRECT3DDEVICE9 pDevice)
{

	VERTEX_2D *pVtx;

	//ロック
	g_pVtxBuffTitlePlayer->Lock(0, 0, (void**)&pVtx, 0);

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
	pVtx[0].tex = D3DXVECTOR2(g_nPattenTitlePlayerAnim*(1.0f / MAX_PATTERN), 0);
	pVtx[2].tex = D3DXVECTOR2(g_nPattenTitlePlayerAnim*(1.0f / MAX_PATTERN), 1);
	pVtx[1].tex = D3DXVECTOR2(g_nPattenTitlePlayerAnim*(1.0f / MAX_PATTERN) + 1.0f / MAX_PATTERN, 0);
	pVtx[3].tex = D3DXVECTOR2(g_nPattenTitlePlayerAnim*(1.0f / MAX_PATTERN) + 1.0f / MAX_PATTERN, 1);

	//ロック解除
	g_pVtxBuffTitlePlayer->Unlock();

}
