//-------------------------------------------------------------------------================================
//
// Coin.cpp
// Author : 黒島　奏洸
//
//-------------------------------------------------------------------------=================================
#include"Coin.h"
#include"Input.h"
#include"application.h"
#include"rendere.h"
#include"score.h"
#include"game.h"
#include"fade.h"
#include"player.h"
#include"sound.h"
CCoin::CCoin(int nPriority) : CModel(nPriority)
{
	m_pos = { 0.0f,0.0f,0.0f };
	m_vtxMax = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_vtxMin = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	bUse = false;
	m_bOn = false;
}

CCoin::~CCoin()
{
}
//-------------------------------------------------------------------------
// コインの初期化
//-------------------------------------------------------------------------
HRESULT CCoin::Init()
{
	m_CoinSEFlag = true;
	CModel::Init();
	SetCoin("data/model/coin.x");
	return S_OK;
}
//-------------------------------------------------------------------------
// コインの終了
//-------------------------------------------------------------------------
void CCoin::Uninit()
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
// コインの更新
//-------------------------------------------------------------------------
void CCoin::Update()
{
	if (m_CoinSEFlag == false)
	{
		PlaySound(SOUND_LABEL_SE_COIN);
		m_CoinSEFlag = true;
	}
}
//-------------------------------------------------------------------------
// コインの描画
//-------------------------------------------------------------------------
void CCoin::Draw()
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
		if (bUse == true)
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
// コインの生成
//-------------------------------------------------------------------------
CCoin *CCoin::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot)
{
	CCoin *pSbox = nullptr;

	//動的生成
	pSbox = new CCoin;
	if (pSbox != nullptr)
	{
		pSbox->Init();
		pSbox->m_pos = pos;
		pSbox->SetType(OBJTYPE_ENEMY);
		pSbox->m_rot = rot;
		pSbox->bUse = true;
	}
	return pSbox;
}
//-------------------------------------------------------------------------
// コインの設定
//-------------------------------------------------------------------------
void CCoin::SetCoin(char * pFile)
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
//-------------------------------------------------------------------------
//コインとプレイヤーの当たり判定
//-------------------------------------------------------------------------
void CCoin::Collision(D3DXVECTOR3 *pPos,			//現在の位置
	D3DXVECTOR3 *pPosOld,								//前回の位置
	D3DXVECTOR3 size)									//サイズ
{
	if (bUse == true)
	{
		CInput *pInput = CApplication::GetKeyboard();

		if (pPos->x - size.x / 2 < m_pos.x + m_vtxMax.x
			&& pPos->x + size.x / 2 > m_pos.x + m_vtxMin.x
			&& pPos->y + size.y / 2 > m_pos.y + m_vtxMin.y
			&& pPos->y - size.y / 2 < m_pos.y + m_vtxMax.y
			)
		{
			//奥の当たり判定
			if (
				pPosOld->z >= m_pos.z + m_vtxMax.z + size.z / 2.0f
				&& pPos->z < m_pos.z + m_vtxMax.z + size.z / 2.0f

				)
			{
				CGame::GetScore()->add(500);
				m_CoinSEFlag = false;
				bUse = false;
				m_bOn = false;
			}
			//手前の当たり判定 
			if (
				pPosOld->z <= m_pos.z + m_vtxMin.z - size.z / 2.0f
				&& pPos->z > m_pos.z + m_vtxMin.z - size.z / 2.0f


				)
			{
				CGame::GetScore()->add(500);
				m_CoinSEFlag = false;
				bUse = false;
				m_bOn = false;

			}
		}
		if (pPos->z - size.z / 2.0f < m_pos.z + m_vtxMax.z
			&& pPos->z + size.z / 2.0f > m_pos.z + m_vtxMin.z
			&& pPos->y + size.y / 2 > m_pos.y + m_vtxMin.y
			&& pPos->y - size.y / 2 < m_pos.y + m_vtxMax.y
			)
		{

			//左の当たり判定
			if (
				pPosOld->x <= m_pos.x + m_vtxMin.x - size.x / 2
				&& pPos->x > m_pos.x + m_vtxMin.x - size.x / 2

				)
			{
				CGame::GetScore()->add(500);
				m_CoinSEFlag = false;
				bUse = false;
				m_bOn = false;

			}
			//右の当たり判定
			if (
				pPosOld->x >= m_pos.x + m_vtxMax.x + size.x / 2
				&& pPos->x < m_pos.x + m_vtxMax.x + size.x / 2

				)
			{
				CGame::GetScore()->add(500);
				m_CoinSEFlag = false;
				bUse = false;
				m_bOn = false;

			}
		}

		if (pPos->x - size.x / 2 < m_pos.x + m_vtxMax.x
			&& pPos->x + size.x / 2 > m_pos.x + m_vtxMin.x
			&& pPos->z - size.z / 2.0f < m_pos.z + m_vtxMax.z
			&& pPos->z + size.z / 2.0f > m_pos.z + m_vtxMin.z
			)

		{
			//上の当たり判定
			if (pPosOld->y + m_size.y / 2 >= m_pos.y + m_vtxMax.y
				&& pPos->y - m_size.y / 2 < m_pos.y + m_vtxMax.y)
			{
				CGame::GetScore()->add(500);
				m_CoinSEFlag = false;
				bUse = false;
				m_bOn = true;
			}
			//下の当たり判定
			if (pPosOld->y + size.y / 2 <= m_pos.y + m_vtxMin.y
				&& pPos->y + size.y / 2 > m_pos.y + m_vtxMin.y
				)

			{
				CGame::GetScore()->add(500);
				m_CoinSEFlag = false;
				bUse = false;
				m_bOn = false;
			}
		}
	}
}