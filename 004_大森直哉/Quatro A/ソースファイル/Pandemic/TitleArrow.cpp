//=============================================================================
//
// タイトルセレクトキャラ処理 [TitleArrow.cpp]
// Author : NAOYA OMORI
//
//=============================================================================
#include "Titlearrow.h"
#include "input.h"
#include "fade.h"
#include "selectfont.h"
#include "sound.h"

//*****************************************************************************
// マクロ定義宣言
//*****************************************************************************
#define PLAYER_SIZE_X (75)
#define PLAYER_SIZE_Y (75)
#define MAX_PATTERN (4)

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void MakeVertexArrow(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9	g_pTextureArrow = NULL;			// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffArrow = NULL;		//頂点バッファのポインタ
Arrow arrow;

int SelectKey;
bool AnimFlag;
float g_ArrowSpeed;
int g_nCounterTitleArrowAnim;
int g_nPattenTitleArrowAnim;
D3DXVECTOR3 StartPos, TutorialPos, QuitPos;

const float g_arrowMoveTime = 1.0f;
const float PLAYER_START_X = 480.0f;
const float PLAYER_FINISH_X = 850.0f;
float g_eatSelectTime = 0.0f;

//=============================================================================
// 初期化処理
//=============================================================================
void InitArrow(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	arrow.pos = D3DXVECTOR3(480, 400, 0);
	arrow.rot = D3DXVECTOR3(0, 0, 0);
	arrow.fAngle = atan2f(PLAYER_SIZE_X / 2, PLAYER_SIZE_Y / 2);
	arrow.fLength = sqrtf((PLAYER_SIZE_X / 2) * (PLAYER_SIZE_X / 2) + (PLAYER_SIZE_Y / 2) * (PLAYER_SIZE_Y / 2));
	SelectKey = 1;
	g_nCounterTitleArrowAnim = 0;
	g_nPattenTitleArrowAnim = 0;
	AnimFlag = FALSE;
	g_ArrowSpeed = ARROW_SPEED;
	StartPos = D3DXVECTOR3(480, 400, 0);
	TutorialPos = D3DXVECTOR3(480, 500, 0);
	QuitPos = D3DXVECTOR3(480, 600, 0);
	g_eatSelectTime = 0.0f;

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffArrow,
		NULL);

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/playeranim.png", &g_pTextureArrow);

	//頂点設定
	MakeVertexArrow(pDevice);

}

//=============================================================================
// 終了処理
//=============================================================================
void UninitArrow(void)
{
	// 頂点バッファの開放
	if (g_pVtxBuffArrow != NULL)
	{
		g_pVtxBuffArrow->Release();
		g_pVtxBuffArrow = NULL;
	}

	// テクスチャの開放
	if (g_pTextureArrow != NULL)
	{
		g_pTextureArrow->Release();
		g_pTextureArrow = NULL;
	}

}
//=============================================================================
// 更新処理
//=============================================================================
void UpdateArrow(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	VERTEX_2D *pVtx;

	g_nCounterTitleArrowAnim++;

	g_pVtxBuffArrow->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].pos.x = arrow.pos.x - sinf(arrow.fAngle - arrow.rot.z)*arrow.fLength;
	pVtx[0].pos.y = arrow.pos.y - cosf(arrow.fAngle - arrow.rot.z)*arrow.fLength;
	pVtx[0].pos.z = 0.0f;

	pVtx[1].pos.x = arrow.pos.x + sinf(arrow.fAngle + arrow.rot.z)*arrow.fLength;
	pVtx[1].pos.y = arrow.pos.y - cosf(arrow.fAngle + arrow.rot.z)*arrow.fLength;
	pVtx[1].pos.z = 0.0f;

	pVtx[2].pos.x = arrow.pos.x - sinf(arrow.fAngle + arrow.rot.z)*arrow.fLength;
	pVtx[2].pos.y = arrow.pos.y + cosf(arrow.fAngle + arrow.rot.z)*arrow.fLength;
	pVtx[2].pos.z = 0.0f;

	pVtx[3].pos.x = arrow.pos.x + sinf(arrow.fAngle - arrow.rot.z)*arrow.fLength;
	pVtx[3].pos.y = arrow.pos.y + cosf(arrow.fAngle - arrow.rot.z)*arrow.fLength;
	pVtx[3].pos.z = 0.0f;

	//アニメーション処理
	if (g_nCounterTitleArrowAnim % 6 == 0)
	{
		g_nPattenTitleArrowAnim = (g_nPattenTitleArrowAnim + 1) % MAX_PATTERN;
	}

	//ロック解除
	g_pVtxBuffArrow->Unlock();

	if (SelectKey == 4) {
		SelectKey = 1;
	}
	if (SelectKey == 0) {
		SelectKey = 3;
	}

	if (GetKeyboardTrigger(DIK_DOWN) && AnimFlag == FALSE) {
		SelectKey += 1;
		Play(SOUND_LABEL_SE_SELECT);
	}

	if (GetKeyboardTrigger(DIK_UP) && AnimFlag == FALSE) {
		SelectKey -= 1;
		Play(SOUND_LABEL_SE_SELECT);
	}

	if (SelectKey == 1 && AnimFlag == FALSE) {
		arrow.pos = StartPos;
	}

	if (SelectKey == 2 && AnimFlag == FALSE) {
		arrow.pos = TutorialPos;
	}

	if (SelectKey == 3 && AnimFlag == FALSE) {
		arrow.pos = QuitPos;
	}

	if (GetKeyboardTrigger(DIK_RETURN))
	{
		Play(SOUND_LABEL_SE_DECIDE);
		AnimFlag = TRUE;
	}

	if (AnimFlag == TRUE &&SelectKey == 1) {
		MoveFont(0, g_eatSelectTime);
	}
	if (AnimFlag == TRUE &&SelectKey == 2) {
		MoveFont(1, g_eatSelectTime);
	}
	if (AnimFlag == TRUE &&SelectKey == 3) {
		MoveFont(2, g_eatSelectTime);
	}


	if (AnimFlag == TRUE && arrow.pos.x != 850) {

		arrow.pos.x += (PLAYER_FINISH_X - PLAYER_START_X) / (g_arrowMoveTime * 60.0f);
		g_eatSelectTime = (arrow.pos.x - PLAYER_START_X) / (PLAYER_FINISH_X - PLAYER_SIZE_X - PLAYER_START_X);

		if (arrow.pos.x >= 850 && AnimFlag == TRUE)
		{
			//AnimFlag = false;
			//arrow.pos.x = 850;

			if (SelectKey == 1) {
				SetFade(MODE_GAME);
			}

			if (SelectKey == 2) {
				SetFade(MODE_TUTORIAL);
			}

			if (SelectKey == 3) {
				PostQuitMessage(0);
			}

		}
	}

	if (AnimFlag == TRUE) {
		pVtx[0].tex = D3DXVECTOR2(g_nPattenTitleArrowAnim*(1.0f / MAX_PATTERN), 0);
		pVtx[2].tex = D3DXVECTOR2(g_nPattenTitleArrowAnim*(1.0f / MAX_PATTERN), 1);
		pVtx[1].tex = D3DXVECTOR2(g_nPattenTitleArrowAnim*(1.0f / MAX_PATTERN) + 1.0f / MAX_PATTERN, 0);
		pVtx[3].tex = D3DXVECTOR2(g_nPattenTitleArrowAnim*(1.0f / MAX_PATTERN) + 1.0f / MAX_PATTERN, 1);
	}

}

//=============================================================================
// 描画処理
//=============================================================================
void DrawArrow(void)
{
	//デバイスを取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//データストリームにセット
	pDevice->SetStreamSource(0, g_pVtxBuffArrow, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, g_pTextureArrow);

	// ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}

//=============================================================================
// 頂点情報の作成
//=============================================================================
void MakeVertexArrow(LPDIRECT3DDEVICE9 pDevice)
{

	VERTEX_2D *pVtx;

	//ロック
	g_pVtxBuffArrow->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点座標の設定
	pVtx[0].pos.x = arrow.pos.x - sinf(arrow.fAngle - arrow.rot.z)*arrow.fLength;
	pVtx[0].pos.y = arrow.pos.y - cosf(arrow.fAngle - arrow.rot.z)*arrow.fLength;
	pVtx[0].pos.z = 0.0f;

	pVtx[1].pos.x = arrow.pos.x + sinf(arrow.fAngle + arrow.rot.z)*arrow.fLength;
	pVtx[1].pos.y = arrow.pos.y - cosf(arrow.fAngle + arrow.rot.z)*arrow.fLength;
	pVtx[1].pos.z = 0.0f;

	pVtx[2].pos.x = arrow.pos.x - sinf(-arrow.fAngle + arrow.rot.z)*arrow.fLength;
	pVtx[2].pos.y = arrow.pos.y - cosf(-arrow.fAngle + arrow.rot.z)*arrow.fLength;
	pVtx[2].pos.z = 0.0f;

	pVtx[3].pos.x = arrow.pos.x + sinf(arrow.fAngle - arrow.rot.z)*arrow.fLength;
	pVtx[3].pos.y = arrow.pos.y + cosf(arrow.fAngle - arrow.rot.z)*arrow.fLength;
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

	pVtx[0].tex = D3DXVECTOR2(g_nPattenTitleArrowAnim*(1.0f / MAX_PATTERN), 0);
	pVtx[2].tex = D3DXVECTOR2(g_nPattenTitleArrowAnim*(1.0f / MAX_PATTERN), 1);
	pVtx[1].tex = D3DXVECTOR2(g_nPattenTitleArrowAnim*(1.0f / MAX_PATTERN) + 1.0f / MAX_PATTERN, 0);
	pVtx[3].tex = D3DXVECTOR2(g_nPattenTitleArrowAnim*(1.0f / MAX_PATTERN) + 1.0f / MAX_PATTERN, 1);

	//ロック解除
	g_pVtxBuffArrow->Unlock();

}