//============================================================================
//
// ObjectX.cpp
// Author : 黒島　奏洸
//
//=============================================================================
#include"main.h"
#include"object.h"
#include"objectX.h"
#include"rendere.h"
#include"application.h"
#include"input.h"
#include"game.h"
//-------------------------------------------------------------------------
// コンストラクタ
//-------------------------------------------------------------------------
CObjectX::CObjectX(int nPriority) : CObject(nPriority)
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
	m_bUse = false;
}

//-------------------------------------------------------------------------
// デストラクタ
//-------------------------------------------------------------------------
CObjectX::~CObjectX()
{
}
//-------------------------------------------------------------------------
// オブジェクトの初期化
//-------------------------------------------------------------------------
HRESULT CObjectX::Init()
{
	m_bUse = false;
	set("data/model/ken.x");
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

	// 頂点情報を設定
	pVtx[0].pos = D3DXVECTOR3(m_pos.x - m_Size.x, m_pos.y - m_Size.y, m_pos.z - m_Size.z);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + m_Size.x, m_pos.y - m_Size.y, m_pos.z - m_Size.z);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - m_Size.x, m_pos.y + m_Size.y, m_pos.z + m_Size.z);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + m_Size.x, m_pos.y + m_Size.y, m_pos.z + m_Size.z);

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

	//対角線の長さ
	m_fLength = sqrtf(m_fHeight * m_fHeight + m_fWidth * m_fWidth) / 2.0f;
	//対角線の角度
	m_fAngle = atan2f(m_fWidth, m_fHeight);

	//頂点情報をアンロックする
	m_pVtxBuff->Unlock();

	return S_OK;
}
//-------------------------------------------------------------------------
// オブジェクトの終了
//-------------------------------------------------------------------------
void CObjectX::Uninit()
{
	//頂点バッファの破棄
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = nullptr;
	}
	if (m_pMesh != NULL)
	{
		m_pMesh->Release();
		m_pMesh = nullptr;
	}
	Release();
}

//-------------------------------------------------------------------------
// オブジェクトの更新
//-------------------------------------------------------------------------
void CObjectX::Update()
{
	//頂点情報へのポインタ
	VERTEX_3D *pVtx;
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
void CObjectX::Draw()
{
	LPDIRECT3DDEVICE9 pDevice;    //デバイスへのポイント

	pDevice = CApplication::GetRendere()->GetDevice();
	D3DXMATRIX mtxRot, mtxTrans; //計算用マトリックス
	D3DMATERIAL9 matDef;
	D3DXMATERIAL *pMat;

	for (int nCnt = 0; nCnt < MAX_MODELFLOOR; nCnt++)
	{
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

		//現在のマテリアルの保持
		pDevice->GetMaterial(&matDef);

		////マテリアルデータへのポインタを取得
		pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)m_nNumMat; nCntMat++)
		{
			//マテリアルの設定
			pDevice->SetMaterial(&pMat[nCntMat].MatD3D);
			//モデルパーツの描画
			m_pMesh->DrawSubset(nCntMat);
		}

	}
	//保持していたマテリアルを戻す
	pDevice->SetMaterial(&matDef);
}
//-------------------------------------------------------------------------
// pos設定
//-------------------------------------------------------------------------
void CObjectX::setpos(D3DXVECTOR3 pos)
{
	m_pos = pos;
}
//-------------------------------------------------------------------------
// オブジェクトの生成
//-------------------------------------------------------------------------
CObjectX *CObjectX::Create(const D3DXVECTOR3 pos)
{
	CObjectX *apObject2D = nullptr;

	//動的生成
	apObject2D = new CObjectX;

	apObject2D->Init();
	apObject2D->setpos(pos);

	return apObject2D;
}
//-------------------------------------------------------------------------
// テクスチャの設定
//-------------------------------------------------------------------------
void CObjectX::BindTexture(LPDIRECT3DTEXTURE9 pTex)
{
	m_pTex = pTex;
}
//-------------------------------------------------------------------------
// サイズの設定
//-------------------------------------------------------------------------
void CObjectX::setsize(D3DXVECTOR3 size)
{
	m_Size = size;
}
//-------------------------------------------------------------------------
// テクスチャの反映
//-------------------------------------------------------------------------
void CObjectX::setTexture(float Upos1, float Upos2, float Bpos1, float Bpos2)
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
void CObjectX::settype(int type)
{
	m_nType = type;
}
//-------------------------------------------------------------------------
// ライフの設定
//-------------------------------------------------------------------------
void CObjectX::setlife(int life)
{
	m_nLife = life;
}
//-------------------------------------------------------------------------
// 角度の設定
//-------------------------------------------------------------------------
void CObjectX::setrotate(D3DXVECTOR3 rot)
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
void  CObjectX::setrevPara(D3DXVECTOR3 Center, float fSpeed, float fRadius)
{
	m_revCentor = Center;
	m_frevSpeed = fSpeed;
	m_frevRadius = fRadius;
}
//-------------------------------------------------------------------------
// 角度の設定
//-------------------------------------------------------------------------
void  CObjectX::setrevCenter(D3DXVECTOR3 revCenter)
{
	m_revCentor = revCenter;
}
//-------------------------------------------------------------------------
// 色の設定
//-------------------------------------------------------------------------
void CObjectX::setcolor(float r, float g, float b, float α)
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
// 設定
//-------------------------------------------------------------------------
CObjectX *CObjectX::set(char *pFilename)
{
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRendere()->GetDevice();    //デバイスへのポイント		
	for (int nCnt = 0; nCnt < MAX_MODELFLOOR; nCnt++)
	{
		//Xファイルの読み込み
		D3DXLoadMeshFromX(
			//ファイル名,
			pFilename,
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&m_pBuffMat,
			NULL,
			&m_nNumMat,
			&m_pMesh
		);
	}
	m_bUse = true;
	return S_OK;
}
