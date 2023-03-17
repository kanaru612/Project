//=============================================================================
//
// Meshfield.cpp
// Author : 黒島　奏洸
//
//=============================================================================
#include "meshfield.h"
#include"application.h"
#include"rendere.h"
#include"object.h"
#include"object2D.h"
LPDIRECT3DTEXTURE9 CMeshfield::m_pTexture = {};

CMeshfield::CMeshfield(int nPriority) : CObject(nPriority)
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

CMeshfield::~CMeshfield()
{
}
//-------------------------------------------------------------------------
//メッシュフィールドの初期化処理
//-------------------------------------------------------------------------
HRESULT CMeshfield::Init(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CApplication::GetRendere()->GetDevice();

	//頂点バッファの生成(インデックス)
	pDevice->CreateIndexBuffer(sizeof(WORD) *  MESHFIELD_INDEX_NUM,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&m_pIdxBuff,
		NULL);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MESHFIELD_VERTEX_NUM,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	//テクスチャの読み込み
	//インデックスへのポインタ0.
	WORD *pIdx;
	//頂点情報へのポインタ
	VERTEX_3D *pVtx;
	srand((unsigned int)time(NULL)); // 現在時刻の情報で初期化
	//頂点バッファをロックし、頂点情報へのポインタを生成
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt1 = 0; nCnt1 < MESHFIELD_Z_BLOCK + 1; nCnt1++)
	{
		for (int nCnt2 = 0; nCnt2 < MESHFIELD_X_BLOCK + 1; nCnt2++)
		{
			/*int nRand = rand() % 100 - 50;*/
			//頂点座標の設定
			//頂点座標の設定(ワールド座標ではなくローカル座標を設定)
			pVtx[nCnt2 + (nCnt1 * (MESHFIELD_X_BLOCK + 1))].pos = D3DXVECTOR3(-150.0f + (nCnt2 * 15.0f), 0.0f, 150.0f - (nCnt1 * 15.0f));
			//各頂点の法線の設定(※ベクトルの大きさは1にする必要がある)
			pVtx[nCnt2 + (nCnt1 * (MESHFIELD_X_BLOCK + 1))].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			//頂点カラーの設定						
			pVtx[nCnt2 + (nCnt1 * (MESHFIELD_X_BLOCK + 1))].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			//テクスチャ座標の設定				  
			pVtx[nCnt2 + (nCnt1 * (MESHFIELD_X_BLOCK + 1))].tex = D3DXVECTOR2((float)nCnt2, (float)nCnt1);
		}
	}
	//頂点情報をアンロックする
	m_pVtxBuff->Unlock();

	//インデックスバッファをロック
	m_pIdxBuff->Lock(0, 0, (void**)&pIdx, 0);

	for (int nCnt1 = 0; nCnt1 < MESHFIELD_Z_BLOCK; nCnt1++)
	{
		for (int nCnt2 = 0; nCnt2 < MESHFIELD_X_BLOCK + 1; nCnt2++)
		{
			pIdx[0] = (MESHFIELD_X_BLOCK + 1) + nCnt2 + nCnt1 * (MESHFIELD_X_BLOCK + 1);
			pIdx[1] = (MESHFIELD_X_BLOCK + 1) + nCnt2 + nCnt1 * (MESHFIELD_X_BLOCK + 1) - (MESHFIELD_X_BLOCK + 1);

			pIdx += 2;
		}
	}

	//インデックスバッファのアンロック
	m_pIdxBuff->Unlock();
	
	return S_OK;
}

//-------------------------------------------------------------------------
//メッシュフィールドの終了処理
//-------------------------------------------------------------------------
void CMeshfield::Uninit(void)
{
	
	if (m_pIdxBuff != NULL)
	{
		m_pIdxBuff->Release();
		m_pIdxBuff = NULL;
	}
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}
	Release();
}

//-------------------------------------------------------------------------
//メッシュフィールドの更新処理
//-------------------------------------------------------------------------
void CMeshfield::Update(void)
{
	
}

//------------------------------------------------------------------------
//メッシュフィールドの描画処理
//-------------------------------------------------------------------------
void CMeshfield::Draw(void)
{
	//GetDeviveの取得
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRendere()->GetDevice();

	//計算用マトリックス
	D3DXMATRIX mtxRot, mtxTrans;

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
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	//インデックスバッファをデータストリームに設定
	pDevice->SetIndices(m_pIdxBuff);

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	//テクスチャの設定
	pDevice->SetTexture(0, m_pTexture);

	//メッシュフィールドの描画
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, MESHFIELD_VERTEX_NUM, 0, MESHFIELD_PRIMITVE_NUM);

	//テクスチャの解除
	pDevice->SetTexture(0, nullptr);
}
CMeshfield *CMeshfield::Create()
{
	CMeshfield *pMesh = nullptr;

	//動的生成
	pMesh = new CMeshfield;
	if (pMesh != nullptr)
	{
		pMesh->Init();
		pMesh->SetType(OBJTYPE_MESHFIELD);
	}
	return pMesh;
}
void CMeshfield::Collision(D3DXVECTOR3 mpos)
{

	int primitive = MESHFIELD_PRIMITVE_NUM;
	VERTEX_3D* pVtx = NULL;			// 頂点情報へのポインタ
	WORD* pIdx;
	const int nTri = 3;
	
	// 頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
	// インデックスバッファをロック
	m_pIdxBuff->Lock(0, 0, (void**)&pIdx, 0);

	for (int nCnt = 0; nCnt < primitive; nCnt++)
	{
		D3DXVECTOR3 posPoly[nTri];

		// 頂点座標の取得
		posPoly[0] = pVtx[pIdx[nCnt + 0]].pos;
		posPoly[1] = pVtx[pIdx[nCnt + 1]].pos;
		posPoly[2] = pVtx[pIdx[nCnt + 2]].pos;

		if ((pIdx[nCnt + 0] == pIdx[nCnt + 1]) ||
			(pIdx[nCnt + 0] == pIdx[nCnt + 2]) ||
			(pIdx[nCnt + 2] == pIdx[nCnt + 1]))
		{// 縮退メッシュフィールドを飛ばす
			continue;
		}

		D3DXVECTOR3 vecLine[nTri];

		// 頂点座標の取得
		vecLine[0] = posPoly[1] - posPoly[0];
		vecLine[1] = posPoly[2] - posPoly[1];
		vecLine[2] = posPoly[0] - posPoly[2];

		D3DXVECTOR3 vecPlayer[nTri];

		// 頂点座標の取得
		vecPlayer[0] = m_pos - posPoly[0];
		vecPlayer[1] = m_pos - posPoly[1];
		vecPlayer[2] = m_pos - posPoly[2];

		float InOut[nTri];

		InOut[0] = vecLine[0].x * vecPlayer[0].x + vecLine[0].z * vecPlayer[0].z;
		InOut[1] = vecLine[1].x * vecPlayer[1].x + vecLine[1].z * vecPlayer[1].z;
		InOut[2] = vecLine[2].x * vecPlayer[2].x + vecLine[2].z * vecPlayer[2].z;


		if ((InOut[0] > 0 && InOut[1] > 0 && InOut[2] > 0)
			|| (InOut[0] < 0 && InOut[1] < 0 && InOut[2] < 0))
		{
			D3DXVECTOR3 V1 = posPoly[1] - posPoly[0];
			D3DXVECTOR3 V2 = posPoly[2] - posPoly[0];

			// 結果の箱
			D3DXVECTOR3 vecNormal;
			// メッシュの法線を求める
			D3DXVec3Cross(&vecNormal, &V1, &V2);
			// 大きさを１にする
			D3DXVec3Normalize(&vecNormal, &vecNormal);

			mpos.y = posPoly[0].y - (vecNormal.x * (mpos.x - posPoly[0].x) + vecNormal.z * (mpos.z - posPoly[0].z)) / vecNormal.y;
		}
	}
		// インデックスバッファのアンロック
		m_pVtxBuff->Unlock();
		// 頂点バッファをアンロックする
		m_pIdxBuff->Unlock();
}
//=============================================================================
// メッシュフィールドの描画
//=============================================================================
HRESULT CMeshfield::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRendere()->GetDevice();    //デバイスへのポイント		


	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data/texture/空.jpg",
		&m_pTexture);

	return S_OK;
}
//=============================================================================
// メッシュフィールドの描画
//=============================================================================
void CMeshfield::Unload(void)
{

	//テクスチャの破棄
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}

}


