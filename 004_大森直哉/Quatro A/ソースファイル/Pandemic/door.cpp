//=============================================================================
//
// ドア処理 [door.cpp]
// Author : NAOYA OMORI
//
//=============================================================================
#include "door.h"
#include "debugproc.h"
#include "Polygon.h"
#include "DebugProc.h"
#include "collision.h"
#include "enemy.h"

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void MakeVertexDoor(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// マクロ定義宣言
//*****************************************************************************
#define MAX_DOOR (3)
#define DOOR_SIZE_X (55)
#define DOOR_SIZE_Y (55)

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9	g_pTextureDoor = NULL;	// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffDoor = NULL;//頂点バッファのポインタ

DOOR g_door[MAX_DOOR];

//=============================================================================
// 初期化処理
//=============================================================================
void InitDoor(void)
{

	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//初期設定
	for (int nCntDoor = 0; nCntDoor < MAX_DOOR; nCntDoor++) {
		g_door[nCntDoor].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_door[nCntDoor].rot = D3DXVECTOR3(0, 0, 0);
		g_door[nCntDoor].fAngle = atan2f(DOOR_SIZE_X / 2, DOOR_SIZE_Y / 2);
		g_door[nCntDoor].fLength = sqrtf((DOOR_SIZE_X / 2) * (DOOR_SIZE_X / 2) + (DOOR_SIZE_Y / 2) * (DOOR_SIZE_Y / 2));
		g_door[nCntDoor].nType = 0;
		g_door[nCntDoor].bUse = false;
	}

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_DOOR,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffDoor,
		NULL);

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/line.png", &g_pTextureDoor);

	//頂点設定
	MakeVertexDoor(pDevice);

}

//=============================================================================
// 終了処理
//=============================================================================
void UninitDoor(void)
{
	// 頂点バッファの開放
	if (g_pVtxBuffDoor != NULL)
	{
		g_pVtxBuffDoor->Release();
		g_pVtxBuffDoor = NULL;
	}

	// テクスチャの開放
	if (g_pTextureDoor != NULL)
	{
		g_pTextureDoor->Release();
		g_pTextureDoor = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateDoor(void)
{

	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXVECTOR3 pPos;	//自機用
	D3DXVECTOR3 ePos;	//敵用
	VERTEX_2D *pVtx;
	int MoveFlag;

	pPos = GetMinePos();	//自機の位置を取得する
	ePos = GetEnemyPos();	//敵の位置を取得する
	MoveFlag = GetKey();


	for (int nCntDoor = 0; nCntDoor < MAX_DOOR; nCntDoor++) {

		if (g_door[nCntDoor].bUse == true) {

			//ロック
			g_pVtxBuffDoor->Lock(0, 0, (void**)&pVtx, 0);

			pVtx += 4 * nCntDoor;

			// 頂点座標の設定
			pVtx[0].pos.x = g_door[nCntDoor].pos.x - sinf(g_door[nCntDoor].fAngle - g_door[nCntDoor].rot.z)*g_door[nCntDoor].fLength;
			pVtx[0].pos.y = g_door[nCntDoor].pos.y - cosf(g_door[nCntDoor].fAngle - g_door[nCntDoor].rot.z)*g_door[nCntDoor].fLength;
			pVtx[0].pos.z = 0.0f;

			pVtx[1].pos.x = g_door[nCntDoor].pos.x + sinf(g_door[nCntDoor].fAngle + g_door[nCntDoor].rot.z)*g_door[nCntDoor].fLength;
			pVtx[1].pos.y = g_door[nCntDoor].pos.y - cosf(g_door[nCntDoor].fAngle + g_door[nCntDoor].rot.z)*g_door[nCntDoor].fLength;
			pVtx[1].pos.z = 0.0f;

			pVtx[2].pos.x = g_door[nCntDoor].pos.x - sinf(g_door[nCntDoor].fAngle + g_door[nCntDoor].rot.z)*g_door[nCntDoor].fLength;
			pVtx[2].pos.y = g_door[nCntDoor].pos.y + cosf(g_door[nCntDoor].fAngle + g_door[nCntDoor].rot.z)*g_door[nCntDoor].fLength;
			pVtx[2].pos.z = 0.0f;

			pVtx[3].pos.x = g_door[nCntDoor].pos.x + sinf(g_door[nCntDoor].fAngle - g_door[nCntDoor].rot.z)*g_door[nCntDoor].fLength;
			pVtx[3].pos.y = g_door[nCntDoor].pos.y + cosf(g_door[nCntDoor].fAngle - g_door[nCntDoor].rot.z)*g_door[nCntDoor].fLength;
			pVtx[3].pos.z = 0.0f;
		}

		//ドアと敵の当たり判定
		if (isHit(g_door[nCntDoor].pos.x, g_door[nCntDoor].pos.y, 50, 5, ePos.x, ePos.y, 50, 35) == true) {
			SetEnemyPos(D3DXVECTOR3(ePos.x, ePos.y - 2.5f, ePos.z));
		}

		//ドアと自機の当たり判定
		if (isHit(g_door[nCntDoor].pos.x, g_door[nCntDoor].pos.y, 50, 5, pPos.x, pPos.y, 50, 35) == true)
		{
			if (MoveFlag == 1) {
				SetPosition(D3DXVECTOR3(pPos.x, pPos.y + 2.5f, pPos.z));
			}
			if (MoveFlag == 2) {
				SetPosition(D3DXVECTOR3(pPos.x, pPos.y - 2.5f, pPos.z));
			}
			if (MoveFlag == 3) {
				SetPosition(D3DXVECTOR3(pPos.x + 2.5f, pPos.y, pPos.z));
			}
			if (MoveFlag == 4) {
				SetPosition(D3DXVECTOR3(pPos.x - 2.5f, pPos.y, pPos.z));
			}
		}
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawDoor(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for (int nCntDoor = 0; nCntDoor < MAX_DOOR; nCntDoor++) {

		if (g_door[nCntDoor].bUse == true) {

			//データストリームにセット
			pDevice->SetStreamSource(0,
				g_pVtxBuffDoor,
				0,
				sizeof(VERTEX_2D));

			// 頂点フォーマットの設定
			pDevice->SetFVF(FVF_VERTEX_2D);

			for (int nCntDoor = 0; nCntDoor < MAX_DOOR; nCntDoor++) {

				// テクスチャの設定
				pDevice->SetTexture(0, g_pTextureDoor);

				// ポリゴンの描画
				pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntDoor * 4, 2);

			}
		}
	}
}

//=============================================================================
// 頂点情報の作成
//=============================================================================
void MakeVertexDoor(LPDIRECT3DDEVICE9 pDevice)
{
	VERTEX_2D *pVtx;
	int nCutVtx;

	//ロック
	g_pVtxBuffDoor->Lock(0, 0, (void**)&pVtx, 0);

	for (nCutVtx = 0; nCutVtx < MAX_DOOR; nCutVtx++) {

		// 頂点座標の設定
		pVtx[0].pos.x = g_door[nCutVtx].pos.x - sinf(g_door[nCutVtx].fAngle - g_door[nCutVtx].rot.z)*g_door[nCutVtx].fLength;
		pVtx[0].pos.y = g_door[nCutVtx].pos.y - cosf(g_door[nCutVtx].fAngle - g_door[nCutVtx].rot.z)*g_door[nCutVtx].fLength;
		pVtx[0].pos.z = 0.0f;

		pVtx[1].pos.x = g_door[nCutVtx].pos.x + sinf(g_door[nCutVtx].fAngle + g_door[nCutVtx].rot.z)*g_door[nCutVtx].fLength;
		pVtx[1].pos.y = g_door[nCutVtx].pos.y - cosf(g_door[nCutVtx].fAngle + g_door[nCutVtx].rot.z)*g_door[nCutVtx].fLength;
		pVtx[1].pos.z = 0.0f;

		pVtx[2].pos.x = g_door[nCutVtx].pos.x - sinf(g_door[nCutVtx].fAngle + g_door[nCutVtx].rot.z)*g_door[nCutVtx].fLength;
		pVtx[2].pos.y = g_door[nCutVtx].pos.y + cosf(g_door[nCutVtx].fAngle + g_door[nCutVtx].rot.z)*g_door[nCutVtx].fLength;
		pVtx[2].pos.z = 0.0f;

		pVtx[3].pos.x = g_door[nCutVtx].pos.x + sinf(g_door[nCutVtx].fAngle - g_door[nCutVtx].rot.z)*g_door[nCutVtx].fLength;
		pVtx[3].pos.y = g_door[nCutVtx].pos.y + cosf(g_door[nCutVtx].fAngle - g_door[nCutVtx].rot.z)*g_door[nCutVtx].fLength;
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

		// テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(1, 0);
		pVtx[1].tex = D3DXVECTOR2(0, 0);
		pVtx[2].tex = D3DXVECTOR2(1, 1);
		pVtx[3].tex = D3DXVECTOR2(0, 1);
		pVtx += 4;

	}

	//ロック解除
	g_pVtxBuffDoor->Unlock();
}

void SetDoor(D3DXVECTOR3 pos) {

	int nCntDoor;

	for (nCntDoor = 0; nCntDoor < MAX_DOOR; nCntDoor++) {

		if (g_door[nCntDoor].bUse == false)
		{
			g_door[nCntDoor].pos = pos;
			g_door[nCntDoor].bUse = true;
			break;
		}
	}
}
