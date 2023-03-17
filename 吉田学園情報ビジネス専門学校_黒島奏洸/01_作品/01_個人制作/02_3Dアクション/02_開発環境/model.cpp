//-------------------------------------------------------------------------================================
//
// Mode.cpp
// Author : 黒島　奏洸
//
//-------------------------------------------------------------------------=================================
#include"model.h"
#include"application.h"
#include"Input.h"
#include"rendere.h"
#include"objectX.h"
#include"shadow.h"
#include"camera.h"
#include"model.h"
#include"player.h"
#include"game.h"

CModel::CModel(int nPriority) : CObject(nPriority)
{
	//位置の初期化
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//向きの初期化
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}
CModel::~CModel()
{
}

//-------------------------------------------------------------------------
// モードの初期化
//-------------------------------------------------------------------------
HRESULT CModel::Init()
{
	//位置の設定
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//向きの設定
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	return S_OK;
}
//-------------------------------------------------------------------------
// モードの終了
//-------------------------------------------------------------------------
void CModel::Uninit()
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
	Release();
}

//-------------------------------------------------------------------------
// モードの更新
//-------------------------------------------------------------------------
void CModel::Update()
{
	setpos(m_pos);
}
//-------------------------------------------------------------------------
// モードの描画
//-------------------------------------------------------------------------
void CModel::Draw()
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

	//位置の反映
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

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
// 生成
//-------------------------------------------------------------------------
CModel * CModel::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	CModel *pweapon = nullptr;

	pweapon = new CModel;				// 3Dオブジェクトのインスタンス生成

	// nullチェック
	if (pweapon != nullptr)
	{
		pweapon->Init();
		pweapon->m_pos = pos;
		pweapon->m_rot = rot;
	}

	return pweapon;
}
//-------------------------------------------------------------------------
// モデルの設定
//-------------------------------------------------------------------------
void CModel::SetModel(char * pFile)
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

	
}
//-------------------------------------------------------------------------
//モデルとプレイヤーの当たり判定
//-------------------------------------------------------------------------
void CModel::Collision(D3DXVECTOR3 *pPos,				//現在の位置
	D3DXVECTOR3 *pPosOld,								//前回の位置
	D3DXVECTOR3 size)									//サイズ
{
	CInput *pInput = CApplication::GetKeyboard();
	CPlayer *pPlayer = CGame::GetPlayer();
	D3DXVECTOR3 pos = pPlayer->Getpos();

	if (pPos->x - size.x / 2 < m_pos.x + m_vtxMax.x
		&& pPos->x + size.x / 2 > m_pos.x + m_vtxMin.x)
	{
		//奥の当たり判定
		if (
			pPosOld->z >= m_pos.z + m_vtxMax.z + size.z / 2.0f
			&& pPos->z < m_pos.z + m_vtxMax.z + size.z / 2.0f
			)
		{
			pPos->z = m_pos.z + m_vtxMax.z + size.z / 2.0f;
			m_bOn = false;
		}
		//手前の当たり判定 
		if (
			pPosOld->z <= m_pos.z + m_vtxMin.z - size.z / 2.0f
			&& pPos->z > m_pos.z + m_vtxMin.z - size.z / 2.0f

			)
		{
			pPos->z = m_pos.z + m_vtxMin.z - size.z / 2.0f;
			m_bOn = false;
		}
	}
	if (pPos->z - size.z / 2.0f < m_pos.z + m_vtxMax.z
		&& pPos->z + size.z / 2.0f > m_pos.z + m_vtxMin.z)
	{

		//左の当たり判定
		if (
			pPosOld->x <= m_pos.x + m_vtxMin.x - size.x / 2
			&& pPos->x > m_pos.x + m_vtxMin.x - size.x / 2
			)
		{
			pPos->x = m_pos.x + m_vtxMin.x - size.x / 2;
			m_bOn = false;
		}
		//右の当たり判定
		if (
			pPosOld->x >= m_pos.x + m_vtxMax.x + size.x / 2
			&& pPos->x < m_pos.x + m_vtxMax.x + size.x / 2
			)
		{
			pPos->x = m_pos.x + m_vtxMax.x + size.x / 2;
			m_bOn = false;
		}
	}

	if (pPos->x - size.x / 2.0f < m_pos.x + m_vtxMax.x
		&& pPos->x + size.x / 2.0f > m_pos.x + m_vtxMin.x
		&&pPosOld->z >= m_pos.z + m_vtxMax.z + size.z / 2.0f
		&&pPos->z < m_pos.z + m_vtxMax.z + size.z / 2.0f)
	{
		//上の当たり判定
		if (pPosOld->y >= m_pos.y + m_vtxMax.y
			&& pPos->y < m_pos.y + m_vtxMax.y)
		{
			pPos->y = m_pos.y + m_vtxMax.y;
			m_bOn = true;
		}
		//下の当たり判定
		if (pPosOld->y + size.y <= m_pos.y + m_vtxMin.y
			&& pPos->y + size.y > m_pos.y + m_vtxMin.y)
		{
			pPos->y = m_pos.y + m_vtxMin.y - size.y;
			m_bOn = false;
		}
	}
}
//-------------------------------------------------------------------------
//サイズ
//-------------------------------------------------------------------------
void CModel::Vtx(void)
{
	int nNumvtx;						//頂点数				
	DWORD sizeFVF;						//頂点フォーマットのサイズ
	BYTE *pVtxBuf;						//頂点バッファへのポインタ
										//頂点数の取得
	nNumvtx = m_pMesh->GetNumVertices();

	//頂点フォーマットのサイズを取得
	sizeFVF = D3DXGetFVFVertexSize(m_pMesh->GetFVF());

	//頂点バッファのロック
	m_pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuf);

	for (int nCntvtx = 0; nCntvtx < nNumvtx; nCntvtx++)
	{
		//頂点座標を代入
		D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuf;

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
		pVtxBuf += sizeFVF;
	}
	m_size.x = m_vtxMax.x - m_vtxMin.x;
	m_size.y = m_vtxMax.y - m_vtxMin.y;
	m_size.z = m_vtxMax.z - m_vtxMin.z;

	//頂点バッファのアンロック
	m_pMesh->UnlockVertexBuffer();
}