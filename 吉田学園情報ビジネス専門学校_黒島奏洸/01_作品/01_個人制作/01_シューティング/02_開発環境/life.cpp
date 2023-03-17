
//インクルード
#include <assert.h>
#include "life.h"
#include "application.h"
#include "rendere.h"
#include "explosion.h"
#include "fade.h"
#include "input.h"
#include "player.h"
#include "enemy.h"

CLife::CLife()
{

}

CLife::~CLife()
{

}

//敵の初期化処理
HRESULT CLife::Init(void)
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
	pVtx[1].pos = D3DXVECTOR3(1280.0f - LIFE_WIDTH * m_nLife, 720.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(1280.0f, 720.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(1280.0f - LIFE_WIDTH * m_nLife, 720.0f, 0.0f);

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

//敵の終了処理
void CLife::Uninit(void)
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

//敵の更新処理
void CLife::Update()
{
	for (int nCnt = 0; nCnt < MAX_OBJECT; nCnt++)
	{
		
		CObject *pObject;

		pObject = CObject::Getobject(nCnt, 3);

		if (pObject != nullptr)
		{
			if (pObject->GetObjType() == OBJTYPE_ENEMY)
			{
				m_nLife = CEnemy::Getlife();
			}
		}
	}
	VERTEX_2D*pVtx;		//頂点情報へのポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(50.0f, 670.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(50.0f + LIFE_WIDTH * m_nLife, 670.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(50.0f, 690.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(50.0f + LIFE_WIDTH * m_nLife, 690.0f, 0.0f);

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
	if (m_nLife <= 200)
	{
		SetColor(1.0f, 0.0f, 0.0f, 1.0f);
	}
	if (m_nLife <= 100)
	{
		SetColor(1.0f, 0.0f, 0.0f, 1.0f);
	}
	if (m_nLife <= 300 && m_nLife > 200)
	{
		SetColor(1.0f, 0.0f, 0.0f, 1.0f);
	}
	if (m_nLife >= 300)
	{
		//頂点バッファをロックし、頂点情報へのポインタを取得
		m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(50.0f, 670.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(50.0f + LIFE_WIDTH * 300, 670.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(50.0f, 690.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(50.0f + LIFE_WIDTH * 300, 690.0f, 0.0f);

		//頂点バッファをアンロックする
		m_pVtxBuff->Unlock();
	}
}

//敵の描画処理
void CLife::Draw()
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

//スポーンの生成
CLife *CLife::Create()
{
	CLife *pLife = nullptr;

	pLife = new CLife;

	pLife->Init();
		
	return pLife;
}
void CLife::SetColor(float r, float g, float b, float α)
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
