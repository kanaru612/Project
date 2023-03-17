//============================================================================
//
// Object3D.cpp
// Author : 黒島　奏洸
//
//=============================================================================
#include"object3D.h"
#include"rendere.h"
#include"application.h"
#include"input.h"
//-------------------------------------------------------------------------
// コンストラクタ
//-------------------------------------------------------------------------
CObject3D::CObject3D(int nPriority) : CObject(nPriority)
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
CObject3D::~CObject3D()
{
}
//-------------------------------------------------------------------------
// オブジェクトの初期化
//-------------------------------------------------------------------------
HRESULT CObject3D::Init()
{

	LPDIRECT3DDEVICE9 pDevice;    //デバイスへのポイント		
	pDevice = CApplication::GetRendere()->GetDevice();

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL
	);
	//頂点情報へのポインタ
	VERTEX_3D *pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを生成
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定(ローカル座標で)
	pVtx[0].pos = D3DXVECTOR3(m_pos.x - 100.0f, m_pos.y, m_pos.z + 100.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + 100.0f, m_pos.y, m_pos.z + 100.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - 100.0f, m_pos.y, m_pos.z - 100.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + 100.0f, m_pos.y, m_pos.z - 100.0f);

	//法線の設定(ベクトルの大きさは1にする必要がある)
	pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	//頂点カラーの設定
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	//頂点カラーの設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);


	m_fWidth = pVtx[2].pos.x - pVtx[0].pos.x;
	m_fHeight = pVtx[0].pos.y - pVtx[1].pos.y;


	//頂点情報をアンロックする
	m_pVtxBuff->Unlock();

	return S_OK;
}
//-------------------------------------------------------------------------
// オブジェクトの終了
//-------------------------------------------------------------------------
void CObject3D::Uninit()
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
void CObject3D::Update()
{
	//頂点情報へのポインタ
	VERTEX_3D *pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを生成
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定(ローカル座標で)
	pVtx[0].pos = D3DXVECTOR3(m_pos.x - m_Size.x, m_pos.y - m_Size.y, m_pos.z + m_Size.z);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + m_Size.x, m_pos.y - m_Size.y, m_pos.z + m_Size.z);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - m_Size.x, m_pos.y + m_Size.y, m_pos.z - m_Size.z);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + m_Size.x, m_pos.y + m_Size.y, m_pos.z - m_Size.z);

	//頂点情報をアンロックする
	m_pVtxBuff->Unlock();
}
//-------------------------------------------------------------------------
// オブジェクトの描画
//-------------------------------------------------------------------------
void CObject3D::Draw()
{
	LPDIRECT3DDEVICE9 pDevice;    //デバイスへのポイント

	pDevice = CApplication::GetRendere()->GetDevice();
	D3DXMATRIX mtxRot, mtxTrans; //計算用マトリックス

								 //ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);


	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0,
		m_pVtxBuff,
		0,
		sizeof(VERTEX_3D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	//テクスチャの設定
	pDevice->SetTexture(0, m_pTex);

	//オブジェクトの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	//テクスチャの設定
	pDevice->SetTexture(0, NULL);

}
//-------------------------------------------------------------------------
// pos設定
//-------------------------------------------------------------------------
void CObject3D::setpos(D3DXVECTOR3 pos)
{
	m_pos = pos;

	//頂点情報へのポインタ
	VERTEX_3D *pVtx;
	//頂点バッファをロックし、頂点情報へのポインタを生成
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].pos.x = m_pos.x + sinf(m_rot.z - D3DX_PI + m_fAngle) * m_fLength;
	pVtx[0].pos.y = m_pos.y + cosf(m_rot.z - D3DX_PI + m_fAngle) * m_fLength;
	pVtx[0].pos.z = 0;

	pVtx[1].pos.x = m_pos.x + sinf(m_rot.z + D3DX_PI - m_fAngle) * m_fLength;
	pVtx[1].pos.y = m_pos.y + cosf(m_rot.z + D3DX_PI - m_fAngle) * m_fLength;
	pVtx[1].pos.z = 0;

	pVtx[2].pos.x = m_pos.x + sinf(m_rot.z - m_fAngle) * m_fLength;
	pVtx[2].pos.y = m_pos.y + cosf(m_rot.z - m_fAngle) * m_fLength;
	pVtx[2].pos.z = 0;

	pVtx[3].pos.x = m_pos.x + sinf(m_rot.z + m_fAngle) * m_fLength;
	pVtx[3].pos.y = m_pos.y + cosf(m_rot.z + m_fAngle) * m_fLength;
	pVtx[3].pos.z = 0;

	//頂点情報をアンロックする
	m_pVtxBuff->Unlock();
}
//-------------------------------------------------------------------------
// クリエイト
//-------------------------------------------------------------------------
CObject3D *CObject3D::Create()
{
	CObject3D *apObject3D = nullptr;

	//動的生成
	apObject3D = new CObject3D;

	apObject3D->Init();
	apObject3D->Setpos3D({0.0f,0.0f,0.0f});
	apObject3D->Setsize3D(D3DXVECTOR3(200.0f, 0.0f, 200.0f));
	return apObject3D;
}
//-------------------------------------------------------------------------
// テクスチャの設定
//-------------------------------------------------------------------------
void CObject3D::BindTexture(LPDIRECT3DTEXTURE9 pTex)
{
	m_pTex = pTex;
}
//-------------------------------------------------------------------------
// サイズの設定
//-------------------------------------------------------------------------
void CObject3D::setsize(D3DXVECTOR3 size)
{
	m_Size = size;
	m_fHeight = size.y;
	m_fWidth = size.x;
	//対角線の長さ
	m_fLength = sqrtf(m_fHeight * m_fHeight + m_fWidth * m_fWidth);
	//対角線の角度
	m_fAngle = atan2f(m_fWidth, m_fHeight);

	//頂点情報へのポインタ
	VERTEX_3D *pVtx;
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
// テクスチャの反映
//-------------------------------------------------------------------------
void CObject3D::setTexture(float Upos1, float Upos2, float Bpos1, float Bpos2)
{
	//頂点情報へのポインタ
	VERTEX_3D *pVtx;
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
void CObject3D::settype(int type)
{
	m_nType = type;
}

//-------------------------------------------------------------------------
// ライフの設定
//-------------------------------------------------------------------------
void CObject3D::setlife(int life)
{
	m_nLife = life;
}
//-------------------------------------------------------------------------
// 角度の設定
//-------------------------------------------------------------------------
void CObject3D::setrotate(D3DXVECTOR3 rot)
{
	m_rot = rot;


	//頂点情報へのポインタ
	VERTEX_3D *pVtx;

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
void  CObject3D::setrevPara(D3DXVECTOR3 Center, float fSpeed, float fRadius)
{
	m_revCentor = Center;
	m_frevSpeed = fSpeed;
	m_frevRadius = fRadius;
}
//-------------------------------------------------------------------------
// 角度の設定
//-------------------------------------------------------------------------
void  CObject3D::setrevCenter(D3DXVECTOR3 revCenter)
{
	m_revCentor = revCenter;
}
//-------------------------------------------------------------------------
// 色の設定
//-------------------------------------------------------------------------
void CObject3D::setcolor(float r, float g, float b, float α)
{
	VERTEX_3D*pVtx;				//頂点情報へのポインタ

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
//-------------------------------------------------------------------------
// 位置の設定
//-------------------------------------------------------------------------
void CObject3D::Setpos3D(D3DXVECTOR3 pos)
{
	m_pos = pos;
	//頂点情報へのポインタ
	VERTEX_3D *pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを生成
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定(ローカル座標で)
	pVtx[0].pos = D3DXVECTOR3(m_pos.x - m_Size.x, m_pos.y - m_Size.y, m_pos.z + m_Size.z);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + m_Size.x, m_pos.y - m_Size.y, m_pos.z + m_Size.z);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - m_Size.x, m_pos.y + m_Size.y, m_pos.z - m_Size.z);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + m_Size.x, m_pos.y + m_Size.y, m_pos.z - m_Size.z);

	//頂点情報をアンロックする
	m_pVtxBuff->Unlock();
}
//-------------------------------------------------------------------------
// サイズの設定
//-------------------------------------------------------------------------
void CObject3D::Setsize3D(D3DXVECTOR3 size)
{
	VERTEX_3D *pVtx;        //頂点情報へのポインタ

	m_Size = size;
																			  //頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点情報の更新
	pVtx[0].pos = D3DXVECTOR3(m_pos.x - m_Size.x, m_pos.y - m_Size.y, m_pos.z + m_Size.z);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + m_Size.x, m_pos.y - m_Size.y, m_pos.z + m_Size.z);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - m_Size.x, m_pos.y + m_Size.y, m_pos.z - m_Size.z);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + m_Size.x, m_pos.y + m_Size.y, m_pos.z - m_Size.z);

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}
