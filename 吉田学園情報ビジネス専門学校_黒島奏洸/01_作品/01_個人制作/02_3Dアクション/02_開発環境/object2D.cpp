//============================================================================
//
// Object2D.cpp
// Author : 黒島　奏洸
//
//=============================================================================
#include"object2D.h"
#include"rendere.h"
#include"application.h"
#include"input.h"

//-------------------------------------------------------------------------
// コンストラクタ
//-------------------------------------------------------------------------
CObject2D::CObject2D(int nPriority) : CObject(nPriority)
{
	m_pVtxBuff = nullptr;
	m_pos = {};
	m_fAngle = 0.0f;
	m_fHeight = 0.0f;
	m_fLength = 0.0f;
	m_fWidth = 0.0f;
	m_rot = { 0.0f,0.0f,0.0f };
	m_Size = { 0.0f,0.0f,0.0f };
	m_frevAngle = 0.0f;
	m_frevRadius = 0.0f;
	m_frevSpeed = 0.0f;
	m_revCentor = { 0.0f,0.0f,0.0f };
}

//-------------------------------------------------------------------------
// デストラクタ
//-------------------------------------------------------------------------
CObject2D::~CObject2D()
{
}
//-------------------------------------------------------------------------
// オブジェクトの初期化
//-------------------------------------------------------------------------
HRESULT CObject2D::Init()
{

	LPDIRECT3DDEVICE9 pDevice;    //デバイスへのポイント		
	pDevice = CApplication::GetRendere()->GetDevice();

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL
	);
	//頂点情報へのポインタ
	VERTEX_2D *pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを生成
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点情報を設定
	pVtx[0].pos = D3DXVECTOR3(m_pos.x - m_Size.x, m_pos.y - m_Size.y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + m_Size.x, m_pos.y - m_Size.y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - m_Size.x, m_pos.y + m_Size.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + m_Size.x, m_pos.y + m_Size.y, 0.0f);

	//テクスチャの座標
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	pVtx[0].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[2].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[3].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	m_fWidth = pVtx[2].pos.x - pVtx[0].pos.x;
	m_fHeight = pVtx[0].pos.y - pVtx[1].pos.y;

	//対角線の長さ
	m_fLength = sqrtf(m_fHeight * m_fHeight + m_fWidth * m_fWidth) / 2.0f;
	//対角線の角度
	m_fAngle = atan2f(m_fWidth, m_fHeight);

	// rhwの設定
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	// 頂点カラーの設定
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	//頂点情報をアンロックする
	m_pVtxBuff->Unlock();

	return S_OK;
}
//-------------------------------------------------------------------------
// オブジェクトの終了
//-------------------------------------------------------------------------
void CObject2D::Uninit()
{
	//頂点バッファの破棄
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = nullptr;
	}

	Release();
}

//-------------------------------------------------------------------------
// オブジェクトの更新
//-------------------------------------------------------------------------
void CObject2D::Update()
{
	//頂点情報へのポインタ
	VERTEX_2D *pVtx;
	//頂点バッファをロックし、頂点情報へのポインタを生成
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	if (m_frevRadius != 0.0f)
	{
		m_pos.x = m_revCentor.x + cosf(m_frevAngle) * m_frevRadius;
		m_pos.y = m_revCentor.y + sinf(m_frevAngle) * m_frevRadius;
	}
	pVtx[0].pos.x = m_pos.x + sinf(m_rot.z - D3DX_PI + m_fAngle) * m_fLength;
	pVtx[0].pos.y = m_pos.y + cosf(m_rot.z - D3DX_PI + m_fAngle) * m_fLength;
	pVtx[0].pos.z = 0.0f;

	pVtx[1].pos.x = m_pos.x + sinf(m_rot.z + D3DX_PI - m_fAngle) * m_fLength;
	pVtx[1].pos.y = m_pos.y + cosf(m_rot.z + D3DX_PI - m_fAngle) * m_fLength;
	pVtx[1].pos.z = 0.0f;

	pVtx[2].pos.x = m_pos.x + sinf(m_rot.z - m_fAngle) * m_fLength;
	pVtx[2].pos.y = m_pos.y + cosf(m_rot.z - m_fAngle) * m_fLength;
	pVtx[2].pos.z = 0.0f;

	pVtx[3].pos.x = m_pos.x + sinf(m_rot.z + m_fAngle) * m_fLength;
	pVtx[3].pos.y = m_pos.y + cosf(m_rot.z + m_fAngle) * m_fLength;
	pVtx[3].pos.z = 0.0f;

	m_frevAngle += m_frevSpeed;
	//頂点情報をアンロックする
	m_pVtxBuff->Unlock();
}
//-------------------------------------------------------------------------
// オブジェクトの描画
//-------------------------------------------------------------------------
void CObject2D::Draw()
{
	LPDIRECT3DDEVICE9 pDevice;    //デバイスへのポイント

	pDevice = CApplication::GetRendere()->GetDevice();
	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0,
		m_pVtxBuff,
		0,
		sizeof(VERTEX_2D));
	
	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);
	
	//テクスチャの設定
	pDevice->SetTexture(0, m_pTex);
	
	//オブジェクトの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
	//テクスチャの解除
	pDevice->SetTexture(0, NULL);

}
//-------------------------------------------------------------------------
// pos設定
//-------------------------------------------------------------------------
void CObject2D::setpos(D3DXVECTOR3 pos)
{
	m_pos = pos;

	//頂点情報へのポインタ
	VERTEX_2D *pVtx;
	//頂点バッファをロックし、頂点情報へのポインタを生成
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].pos.x = m_pos.x + sinf(m_rot.z - D3DX_PI + m_fAngle) * m_fLength;
	pVtx[0].pos.y = m_pos.y + cosf(m_rot.z - D3DX_PI + m_fAngle) * m_fLength;
	pVtx[0].pos.z = 0.0f;

	pVtx[1].pos.x = m_pos.x + sinf(m_rot.z + D3DX_PI - m_fAngle) * m_fLength;
	pVtx[1].pos.y = m_pos.y + cosf(m_rot.z + D3DX_PI - m_fAngle) * m_fLength;
	pVtx[1].pos.z = 0.0f;

	pVtx[2].pos.x = m_pos.x + sinf(m_rot.z - m_fAngle) * m_fLength;
	pVtx[2].pos.y = m_pos.y + cosf(m_rot.z - m_fAngle) * m_fLength;
	pVtx[2].pos.z = 0.0f;

	pVtx[3].pos.x = m_pos.x + sinf(m_rot.z + m_fAngle) * m_fLength;
	pVtx[3].pos.y = m_pos.y + cosf(m_rot.z + m_fAngle) * m_fLength;
	pVtx[3].pos.z = 0.0f;

	//頂点情報をアンロックする
	m_pVtxBuff->Unlock();
}
//-------------------------------------------------------------------------
// 生成
//-------------------------------------------------------------------------
CObject2D *CObject2D::Create(const D3DXVECTOR3 pos)
{
	CObject2D *apObject2D = nullptr;
	
	//動的生成
	apObject2D = new CObject2D;
	
	apObject2D->Init();
	apObject2D->setpos(pos);

	return apObject2D;
}
//-------------------------------------------------------------------------
// テクスチャの設定
//-------------------------------------------------------------------------
void CObject2D::BindTexture(LPDIRECT3DTEXTURE9 pTex)
{
	m_pTex = pTex;
}
//-------------------------------------------------------------------------
// サイズの設定
//-------------------------------------------------------------------------
void CObject2D::setsize(D3DXVECTOR3 size)
{
	m_Size = size;
	m_fHeight = size.y;
	m_fWidth = size.x;
	//対角線の長さ
	m_fLength = sqrtf(m_fHeight * m_fHeight + m_fWidth * m_fWidth);
	//対角線の角度
	m_fAngle = atan2f(m_fWidth, m_fHeight);

	//頂点情報へのポインタ
	VERTEX_2D *pVtx;
	//頂点バッファをロックし、頂点情報へのポインタを生成
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].pos.x = m_pos.x + sinf(m_rot.z - D3DX_PI + m_fAngle) * m_fLength;
	pVtx[0].pos.y = m_pos.y + cosf(m_rot.z - D3DX_PI + m_fAngle) * m_fLength;
	pVtx[0].pos.z = 0.0f;

	pVtx[1].pos.x = m_pos.x + sinf(m_rot.z + D3DX_PI - m_fAngle) * m_fLength;
	pVtx[1].pos.y = m_pos.y + cosf(m_rot.z + D3DX_PI - m_fAngle) * m_fLength;
	pVtx[1].pos.z = 0.0f;

	pVtx[2].pos.x = m_pos.x + sinf(m_rot.z - m_fAngle) * m_fLength;
	pVtx[2].pos.y = m_pos.y + cosf(m_rot.z - m_fAngle) * m_fLength;
	pVtx[2].pos.z = 0.0f;

	pVtx[3].pos.x = m_pos.x + sinf(m_rot.z + m_fAngle) * m_fLength;
	pVtx[3].pos.y = m_pos.y + cosf(m_rot.z + m_fAngle) * m_fLength;
	pVtx[3].pos.z = 0.0f;

	//頂点情報をアンロックする
	m_pVtxBuff->Unlock();
}
//-------------------------------------------------------------------------
// テクスチャの設定
//-------------------------------------------------------------------------
void CObject2D::setTexture(float Upos1, float Upos2, float Bpos1 ,float Bpos2)
{
	//頂点情報へのポインタ
	VERTEX_2D *pVtx;
	//頂点バッファをロックし、頂点情報へのポインタを生成

	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//テクスチャの座標
	pVtx[0].tex = D3DXVECTOR2(Upos1, Bpos1);
	pVtx[1].tex = D3DXVECTOR2(Upos2, Bpos1);
	pVtx[2].tex = D3DXVECTOR2(Upos1, Bpos2);
	pVtx[3].tex = D3DXVECTOR2(Upos2, Bpos2);

	//頂点情報をアンロックする
	m_pVtxBuff->Unlock();
}
//-------------------------------------------------------------------------
// タイプの設定
//-------------------------------------------------------------------------
void CObject2D::settype(int type)
{
	m_nType = type;
}
//-------------------------------------------------------------------------
//　ライフの設定
//-------------------------------------------------------------------------
void CObject2D::setlife(int life)
{
	m_nLife = life;
}
//-------------------------------------------------------------------------
// 角度の設定
//-------------------------------------------------------------------------
void CObject2D::setrotate(D3DXVECTOR3 rot)
{
	m_rot = rot;


	//頂点情報へのポインタ
	VERTEX_2D *pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを生成
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].pos.x = m_pos.x + sinf(m_rot.z - D3DX_PI + m_fAngle) * m_fLength;
	pVtx[0].pos.y = m_pos.y + cosf(m_rot.z - D3DX_PI + m_fAngle) * m_fLength;
	pVtx[0].pos.z = 0.0f;

	pVtx[1].pos.x = m_pos.x + sinf(m_rot.z + D3DX_PI - m_fAngle) * m_fLength;
	pVtx[1].pos.y = m_pos.y + cosf(m_rot.z + D3DX_PI - m_fAngle) * m_fLength;
	pVtx[1].pos.z = 0.0f;

	pVtx[2].pos.x = m_pos.x + sinf(m_rot.z - m_fAngle) * m_fLength;
	pVtx[2].pos.y = m_pos.y + cosf(m_rot.z - m_fAngle) * m_fLength;
	pVtx[2].pos.z = 0.0f;

	pVtx[3].pos.x = m_pos.x + sinf(m_rot.z + m_fAngle) * m_fLength;
	pVtx[3].pos.y = m_pos.y + cosf(m_rot.z + m_fAngle) * m_fLength;
	pVtx[3].pos.z = 0.0f;

	//頂点情報をアンロックする
	m_pVtxBuff->Unlock();
}
//-------------------------------------------------------------------------
// 角度の設定
//-------------------------------------------------------------------------
void  CObject2D::setrevPara(D3DXVECTOR3 Center, float fSpeed, float fRadius)
{
	m_revCentor = Center;
	m_frevSpeed = fSpeed;
	m_frevRadius = fRadius;
}
//-------------------------------------------------------------------------
// 角度の設定
//-------------------------------------------------------------------------
void  CObject2D::setrevCenter(D3DXVECTOR3 revCenter)
{
	m_revCentor = revCenter;
}
//-------------------------------------------------------------------------
// 色の設定
//-------------------------------------------------------------------------
void CObject2D::setcolor(float r, float g, float b, float α)
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
