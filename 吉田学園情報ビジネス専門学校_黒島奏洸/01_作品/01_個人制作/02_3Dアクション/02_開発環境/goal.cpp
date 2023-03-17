//============================================================================
//
// Goal.cpp
// Author : 黒島　奏洸
//
//=============================================================================
#include"goal.h"
#include"Input.h"
#include"application.h"
#include"rendere.h"
#include"score.h"
#include"game.h"
#include"fade.h"
#include"player.h"
CGoal::CGoal(int nPriority) : CModel(nPriority)
{
	m_pos = { 0.0f,0.0f,0.0f };
	m_nLife = 0;
	m_vtxMax = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_vtxMin = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	bUse = false;
}

CGoal::~CGoal()
{
}
//-------------------------------------------------------------------------
// ゴールの初期化
//-------------------------------------------------------------------------
HRESULT CGoal::Init()
{
	m_FadeFlag = false;
	CModel::Init();
	SetGoal("data/model/goal.x");
	return S_OK;
}
//-------------------------------------------------------------------------
// ゴールの終了
//-------------------------------------------------------------------------
void CGoal::Uninit()
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

	//Release();
}

//-------------------------------------------------------------------------
// ゴールの更新
//-------------------------------------------------------------------------
void CGoal::Update()
{
	if (m_GoalFlag == true && m_FadeFlag == false)
	{
		CFade::Set(CApplication::MODE_RANKING);
		m_FadeFlag = true;
	}
}
//-------------------------------------------------------------------------
// ゴールの描画
//-------------------------------------------------------------------------
void CGoal::Draw()
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
// ゴールの生成
//-------------------------------------------------------------------------
CGoal *CGoal::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot)
{
	CGoal *pGoal = nullptr;

	//動的生成
	pGoal = new CGoal;
	if (pGoal != nullptr)
	{
		pGoal->Init();
		pGoal->m_pos = pos;
		pGoal->SetType(OBJTYPE_ENEMY);
		pGoal->m_rot = rot;
		pGoal->bUse = true;
	}
	return pGoal;
}
//============================================
// ゴールの設定
//============================================
void CGoal::SetGoal(char * pFile)
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
//ゴールとプレイヤーの当たり判定
//-------------------------------------------------------------------------
void CGoal::Collision(D3DXVECTOR3 *pPos,			//現在の位置
	D3DXVECTOR3 *pPosOld,								//前回の位置
	D3DXVECTOR3 size)									//サイズ
{

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
			pPos->z = m_pos.z + m_vtxMax.z + size.z / 2.0f;
			m_GoalFlag = true;
			//bUse = false;
			//CFade::Create(CApplication::MODE_RANKING);
		}
		//手前の当たり判定 
		if (
			pPosOld->z <= m_pos.z + m_vtxMin.z - size.z / 2.0f
			&& pPos->z > m_pos.z + m_vtxMin.z - size.z / 2.0f
			)
		{
			pPos->z = m_pos.z + m_vtxMin.z - size.z / 2.0f;
			m_GoalFlag = true;
			//bUse = false;
			//CFade::Create(CApplication::MODE_RANKING);
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
			pPos->x = m_pos.x + m_vtxMin.x - size.x / 2;
			m_GoalFlag = true;
			//bUse = false;
			//CFade::Create(CApplication::MODE_RANKING);
		}
		//右の当たり判定
		if (
			pPosOld->x >= m_pos.x + m_vtxMax.x + size.x / 2
			&& pPos->x < m_pos.x + m_vtxMax.x + size.x / 2
			)
		{
			pPos->x = m_pos.x + m_vtxMax.x + size.x / 2;
			m_GoalFlag = true;
			//bUse = false;
			//CFade::Create(CApplication::MODE_RANKING);
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
			pPos->y = m_pos.y + m_vtxMax.y + m_size.y / 2;
			m_GoalFlag = true;
			//bUse = false;
			//CFade::Create(CApplication::MODE_RANKING);
		}
		//下の当たり判定
		if (pPosOld->y + size.y / 2 <= m_pos.y + m_vtxMin.y
			&& pPos->y + size.y / 2 > m_pos.y + m_vtxMin.y
			)

		{
			pPos->y = m_pos.y + m_vtxMin.y - size.y;
			m_GoalFlag = true;
			//bUse = false;
			//CFade::Create(CApplication::MODE_RANKING);

		}
	}
}