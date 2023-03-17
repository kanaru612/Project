//-------------------------------------------------------------------------================================
//
// Modelparts.cpp
// Author : 黒島　奏洸
//
//-------------------------------------------------------------------------=================================
#include"modelparts.h"
#include"application.h"
#include"Input.h"
#include"rendere.h"
#include"objectX.h"
#include"shadow.h"
#include"camera.h"

CModelparts::CModelparts()
{
	m_pVtxBuff = {};
	m_mtxWorld = {};
	//位置の初期化
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//向きの初期化
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}
CModelparts::~CModelparts()
{
}

//-------------------------------------------------------------------------
// モデルパーツの初期化
//-------------------------------------------------------------------------
HRESULT CModelparts::Init()
{
	
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRendere()->GetDevice();    
	//位置の設定
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//向きの設定
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	return S_OK;
}
//-------------------------------------------------------------------------
// モデルパーツの終了
//-------------------------------------------------------------------------
void CModelparts::Uninit()
{
	//頂点バッファの破棄
	if (m_pBuffMat != NULL)
	{
		m_pBuffMat->Release();
		m_pBuffMat = nullptr;
	}
	if (m_pMesh != NULL)
	{
		m_pMesh->Release();
		m_pMesh = nullptr;
	}
}

//-------------------------------------------------------------------------
// モデルパーツの更新
//-------------------------------------------------------------------------
void CModelparts::Update()
{
}
//-------------------------------------------------------------------------
// モデルパーツの描画
//-------------------------------------------------------------------------
void CModelparts::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRendere()->GetDevice();

	D3DXMATRIX mtxRot, mtxTrans;		//計算用マトリックス
	D3DMATERIAL9 matDef;				//現在のマテリアル保存用
	D3DXMATERIAL * pMat;				//マテリアルデータへのポインタ

	//ローカルマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);												

	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);			
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);						

	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);				
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, m_mtxParent);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);								

	//現在のマテリアルを保持
	pDevice->GetMaterial(&matDef);

	//マテリアルデータへのポインタを取得
	pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();
	for (int nCntMat = 0; nCntMat < (int)m_nNumMat; nCntMat++)
	{
		//マテリアルの設定
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

		//モデルパーツの描画
		m_pMesh->DrawSubset(nCntMat);
	}
	//保持していたマテリアルを戻す
	pDevice->SetMaterial(&matDef);
}
//-------------------------------------------------------------------------
// モデルパーツの生成
//-------------------------------------------------------------------------
CModelparts * CModelparts::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot)
{
	CModelparts *pModelparts = nullptr;

	// 3Dオブジェクトクラスの生成
	pModelparts = new CModelparts;				// 3Dオブジェクトのインスタンス生成

	// nullptrチェック
	if (pModelparts != nullptr)
	{
		// 初期化処理
		pModelparts->Init();
		pModelparts->m_pos = pos;
		pModelparts->m_rot = rot;
	}
	return pModelparts;
}
//-------------------------------------------------------------------------
// モデルパーツの設定
//-------------------------------------------------------------------------
void CModelparts::SetModel(char * pFile)
{
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRendere()->GetDevice();

	//Xファイルの読み込み
	D3DXLoadMeshFromX(pFile,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&m_pBuffMat,
		NULL,
		&m_nNumMat,
		&m_pMesh);

	//頂点数の取得
	m_nNumvtx = m_pMesh->GetNumVertices();

	//頂点フォーマットのサイズを取得
	m_sizeFVF = D3DXGetFVFVertexSize(m_pMesh->GetFVF());

	//頂点バッファのロック
	m_pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&m_pVtxBuf);

	for (int nCntvtx = 0; nCntvtx < m_nNumvtx; nCntvtx++)
	{
		//頂点座標を代入
		D3DXVECTOR3 vtx = *(D3DXVECTOR3*)m_pVtxBuf;

		//頂点座標を比較してモデルの最小値、最大値を取得(if文)
		if (vtx.x < m_vtxMin.x)
		{
			m_vtxMin.x = vtx.x;
		}
		if (vtx.y < m_vtxMin.y)
		{
			m_vtxMin.y = vtx.y;
		}
		if (vtx.z < m_vtxMin.z)
		{
			m_vtxMin.z = vtx.z;
		}
		if (vtx.x > m_vtxMax.x)
		{
			m_vtxMax.x = vtx.x;
		}
		if (vtx.y > m_vtxMax.y)
		{
			m_vtxMax.y = vtx.y;
		}
		if (vtx.z > m_vtxMax.z)
		{
			m_vtxMax.z = vtx.z;
		}
		//頂点フォーマットのサイズ分ポインタを進める
		m_pVtxBuf += m_sizeFVF;
	}


	//頂点バッファのアンロック
	m_pMesh->UnlockVertexBuffer();
}
