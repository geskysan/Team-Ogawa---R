//=============================================================================
//
// ランキング処理（描画も含む）[RankingScore.cpp]
// Author : 
//
//=============================================================================
#include "RankingScore.h"
#include "number.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MAX_DIGIT	(8)
#define MAX_RANKING (5)
#define MAX_PATTEN	(10)
//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void MakeVertexRankingScore(LPDIRECT3DDEVICE9 pDevice);
LPDIRECT3DTEXTURE9 g_apTextureRankingScore = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffRankingScore = NULL;
RankingScore g_aRankingScore[MAX_RANKING][MAX_DIGIT];
int iRanking[MAX_RANKING] = {550,450,350,250,150};

//=============================================================================
// 初期化処理
//=============================================================================
void InitRankingScore(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	int nCutRankingScore;
	int nCutRanking;
	int GameScore;

	GameScore = GetNumber();	//ゲーム終了時のスコアを持ってくる

	for (nCutRankingScore = 0; nCutRankingScore < MAX_DIGIT; nCutRankingScore++)
		for (nCutRanking = 0; nCutRanking < MAX_RANKING; nCutRanking++) {
			{
				g_aRankingScore[nCutRanking][nCutRankingScore].bUse = false;
				g_aRankingScore[nCutRanking][nCutRankingScore].pos = D3DXVECTOR3(450 + 50 * nCutRankingScore, 125 + 100 * nCutRanking, 0);
				g_aRankingScore[nCutRanking][nCutRankingScore].rot = D3DXVECTOR3(0, 0, 0);
			}
		}

	//ランキングの処理
	//for (int i = 0; i <= MAX_RANKING; i++) {
	//	if (iRanking[i] <= GameScore) {
	//		iRanking[i] = iRanking[i -1];	//ゲームスコアの一個上の数に揃える
	//		iRanking[i] = 0; //ゲーム内スコアの下の奴らをすべて０にする
	//	}
	//}

	//ランキングの処理改
	for (int i = 0; i <= MAX_RANKING; i++) {
		if (iRanking[i] <= GameScore) {
			for (int j = MAX_RANKING; j >= i; j--) {
			iRanking[j] = iRanking[j -1];	//ゲームスコアの一個上の数に揃える
			}
			iRanking[i] = GameScore;
			break;
		}
	}

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/number000.png", &g_apTextureRankingScore);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_DIGIT * MAX_RANKING,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffRankingScore,
		NULL);

	MakeVertexRankingScore(pDevice);

}

void UninitRankingScore(void) {

	if (g_pVtxBuffRankingScore != NULL)
	{
		g_pVtxBuffRankingScore->Release();
		g_pVtxBuffRankingScore = NULL;
	}

	// テクスチャの開放
	if (g_apTextureRankingScore != NULL) {
		g_apTextureRankingScore->Release();
		g_apTextureRankingScore = NULL;
	}
}
//=============================================================================
//更新処理
//=============================================================================
void UpdateRankingScore(void)
{

}

void DrawRankingScore(void) {

	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	pDevice->SetStreamSource(0,
		g_pVtxBuffRankingScore,
		0,
		sizeof(VERTEX_2D));

	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, g_apTextureRankingScore);


		for (int nCutRankingScore = 0; nCutRankingScore < MAX_DIGIT * MAX_RANKING; nCutRankingScore++) {

				//ポリゴンの作成
				pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCutRankingScore * 4, 2);

	}
}

//void SetRankingScore(D3DXVECTOR3 pos) {
//
//	VERTEX_2D *pVtx;
//	int nCutRankingScore;
//	int nCutRanking;
//
//	for (nCutRankingScore = 0; nCutRankingScore < MAX_DIGIT; nCutRankingScore++)
//	{
//		for (int nCutRanking = 0; nCutRanking < MAX_RANKING; nCutRanking++)
//		{
//
//			if (g_aRankingScore[nCutRanking][nCutRankingScore].bUse == false)
//			{
//				g_aRankingScore[nCutRanking][nCutRankingScore].pos = pos;
//				g_aRankingScore[nCutRanking][nCutRankingScore].bUse = true;
//
//				//ロック
//				g_pVtxBuffRankingScore->Lock(0, 0, (void**)&pVtx, 0);
//
//				pVtx += nCutRanking * nCutRankingScore * 4;
//
//				pVtx[0].pos = g_aRankingScore[nCutRanking][nCutRankingScore].pos;
//				pVtx[1].pos = g_aRankingScore[nCutRanking][nCutRankingScore].pos;
//				pVtx[2].pos = g_aRankingScore[nCutRanking][nCutRankingScore].pos;
//				pVtx[3].pos = g_aRankingScore[nCutRanking][nCutRankingScore].pos;
//
//				g_pVtxBuffRankingScore->Unlock();
//
//				break;
//			}
//		}
//	}
//}


//=============================================================================
// 頂点情報の作成
//=============================================================================
void MakeVertexRankingScore(LPDIRECT3DDEVICE9 pDevice)
{
	VERTEX_2D *pVtx;
	int nCutVtx;

	//ロック
	g_pVtxBuffRankingScore->Lock(0, 0, (void**)&pVtx, 0);

	for (nCutVtx = 0; nCutVtx < MAX_DIGIT; nCutVtx++) {
		for (int nCutVtxx = 0; nCutVtxx < MAX_RANKING;nCutVtxx++) {

			pVtx[0].pos.x = g_aRankingScore[nCutVtxx][nCutVtx].pos.x;
			pVtx[1].pos.x = g_aRankingScore[nCutVtxx][nCutVtx].pos.x + 50;
			pVtx[2].pos.x = g_aRankingScore[nCutVtxx][nCutVtx].pos.x;
			pVtx[3].pos.x = g_aRankingScore[nCutVtxx][nCutVtx].pos.x + 50;

			pVtx[0].pos.y = g_aRankingScore[nCutVtxx][nCutVtx].pos.y;
			pVtx[1].pos.y = g_aRankingScore[nCutVtxx][nCutVtx].pos.y;
			pVtx[2].pos.y = g_aRankingScore[nCutVtxx][nCutVtx].pos.y + 50;
			pVtx[3].pos.y = g_aRankingScore[nCutVtxx][nCutVtx].pos.y + 50;

			// rhwの設定
			pVtx[0].rhw = 1.0f;
			pVtx[1].rhw = 1.0f;
			pVtx[2].rhw = 1.0f;
			pVtx[3].rhw = 1.0f;

			// 頂点カラーの設定

			pVtx[0].col = D3DCOLOR_RGBA(255, 0, 0, 255);//RGBAの色を入れる
			pVtx[1].col = D3DCOLOR_RGBA(255, 0, 0, 255);
			pVtx[2].col = D3DCOLOR_RGBA(255, 0, 0, 255);
			pVtx[3].col = D3DCOLOR_RGBA(255, 0, 0, 255);

			int iPow = powf(10, MAX_DIGIT - nCutVtx);
			float fScore = iRanking[nCutVtxx] % iPow / (iPow / 10);
			pVtx[0].tex = D3DXVECTOR2(fScore*(1.0f / MAX_PATTEN), 0);
			pVtx[1].tex = D3DXVECTOR2(fScore*(1.0f / MAX_PATTEN) + 1.0f / MAX_PATTEN, 0);
			pVtx[2].tex = D3DXVECTOR2(fScore*(1.0f / MAX_PATTEN), 1);
			pVtx[3].tex = D3DXVECTOR2(fScore*(1.0f / MAX_PATTEN) + 1.0f / MAX_PATTEN, 1);
			pVtx += 4;
		}
	}

	//ロック解除
	g_pVtxBuffRankingScore->Unlock();
}