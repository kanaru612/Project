//============================================================================
//
// Player.h
// Author : 黒島　奏洸
//
//=============================================================================
#include <assert.h>
#include "plife.h"
#include "application.h"
#include "rendere.h"
#include "fade.h"
#include "input.h"
#include "player.h"
#include "enemy.h"
#include "game.h"
CPlife::CPlife()
{

}

CPlife::~CPlife()
{

}

//-------------------------------------------------------------------------
//プレイヤーのHPバーの初期化
//-------------------------------------------------------------------------
HRESULT CPlife::Init(void)
{

	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRendere()->GetDevice();


	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	VERTEX_2D*pVtx;

	m_nLife = 0;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(1280.0f, 720.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(1280.0f - PLIFE_WIDTH * m_nLife, 720.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(1280.0f, 720.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(1280.0f - PLIFE_WIDTH * m_nLife, 720.0f, 0.0f);

	// rhwの設定
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	// 頂点カラーの設定
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();

	return S_OK;
}

//-------------------------------------------------------------------------
//プレイヤーのHPバーの終了
//-------------------------------------------------------------------------
void CPlife::Uninit(void)
{
	//頂点バッファの破棄
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

	//破棄処理
	CObject::Release();
}

//-------------------------------------------------------------------------
//プレイヤーのHPバーの更新
//-------------------------------------------------------------------------
void CPlife::Update()
{
	CPlayer *pPlayer = CGame::GetPlayer();
	m_nLife = pPlayer->Getlife();
	VERTEX_2D*pVtx;		//頂点情報へのポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(300.0f - PLIFE_WIDTH * m_nLife, 10.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(300.0f, 10.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(300.0f - PLIFE_WIDTH * m_nLife, 30.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(300.0f, 30.0f, 0.0f);

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
	if (m_nLife <= 2)
	{
		SetColor(0.0f, 1.0f, 0.0f, 1.0f);
	}
	if (m_nLife <= 1)
	{
		SetColor(0.0f, 1.0f, 0.0f, 1.0f);
	}
	if (m_nLife <= 5 && m_nLife > 2)
	{
		SetColor(0.0f, 1.0f, 0.0f, 1.0f);
	}
	if (m_nLife > 5)
	{
		//頂点バッファをロックし、頂点情報へのポインタを取得
		m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(300.0f - PLIFE_WIDTH * m_nLife, 10.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(300.0f, 10.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(300.0f - PLIFE_WIDTH * m_nLife, 30.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(300.0f, 30.0f, 0.0f);

		//頂点バッファをアンロックする
		m_pVtxBuff->Unlock();
	}
}
//-------------------------------------------------------------------------
//プレイヤーのHPバーの描画
//-------------------------------------------------------------------------
void CPlife::Draw()
{
	//GetDeviveの取得
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRendere()->GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}

//-------------------------------------------------------------------------
//プレイヤーのHPバーの生成
//-------------------------------------------------------------------------
CPlife *CPlife::Create(D3DXVECTOR3 pos)
{
	CPlife *pLife = nullptr;

	pLife = new CPlife;

	pLife->Init();
	pLife->setpos(pos);
	return pLife;
}
//-------------------------------------------------------------------------
//プレイヤーのHPバーの色の設定
//-------------------------------------------------------------------------
void CPlife::SetColor(float r, float g, float b, float α)
{
	VERTEX_2D*pVtx;				//頂点情報へのポインタ

	LPDIRECT3DVERTEXBUFFER9 Buffer = GetBuffer();

	//頂点バッファをロックし、頂点情報へのポインタを取得
	Buffer->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点カラーの設定
	pVtx[0].col = D3DXCOLOR(r, g, b, α);
	pVtx[1].col = D3DXCOLOR(r, g, b, α);
	pVtx[2].col = D3DXCOLOR(r, g, b, α);
	pVtx[3].col = D3DXCOLOR(r, g, b, α);

	//頂点バッファをアンロックする
	Buffer->Unlock();
}
