//=============================================================================
//
// Gimmick.cpp
// Author : 黒島　奏洸
//
//=============================================================================
#include <assert.h>
#include <stdio.h>
#include "gimmick.h"
#include "application.h"
#include "rendere.h"
#include"Input.h"
#include"score.h"
#include"game.h"
#include"fade.h"
#include"player.h"
#include"goal.h"
CGimmick::CGimmick(int nPriority) : CModel(nPriority)
{

	m_pos = { 0.0f,0.0f,0.0f };
	m_nLife = 0;
	m_vtxMax = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_vtxMin = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_bUse = false;
	m_bOn = false;
}

CGimmick::~CGimmick()
{

}
//-------------------------------------------------------------------------
// ギミックの初期化
//-------------------------------------------------------------------------
HRESULT CGimmick::Init(void)
{
	CModel::Init();
	CModel::SetModel("data/model/egg.x");
	CModel::Vtx();
	return S_OK;
}
//-------------------------------------------------------------------------
// ギミックの終了
//-------------------------------------------------------------------------
void CGimmick::Uninit()
{
	CModel::Uninit();
}
//-------------------------------------------------------------------------
// ギミックの更新
//-------------------------------------------------------------------------
void CGimmick::Update()
{
	m_pos = Getpos();
}
//-------------------------------------------------------------------------
// ギミックの描画
//-------------------------------------------------------------------------
void CGimmick::Draw()
{
	CModel::Draw();
}
//-------------------------------------------------------------------------
// ギミックの生成
//-------------------------------------------------------------------------
CGimmick * CGimmick::Create(const D3DXVECTOR3 pos)
{
	CGimmick *pGimmick = nullptr;
	pGimmick = new CGimmick;
	if (pGimmick != nullptr)
	{
		pGimmick->Init();
		pGimmick->setpos(pos);
		pGimmick->SetType(OBJTYPE_ENEMY);
		pGimmick->m_bUse = true;
	}
	return pGimmick;
}
//-------------------------------------------------------------------------
// ギミックの設定
//-------------------------------------------------------------------------
void CGimmick::SetGimmick(char * pFile)
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
//プレイヤーとギミックの当たり判定
//-------------------------------------------------------------------------
void CGimmick::Collision(D3DXVECTOR3 *pPos,				//現在の位置
	D3DXVECTOR3 *pPosOld,								//前回の位置
	D3DXVECTOR3 size)									//サイズ
{
	CInput *pInput = CApplication::GetKeyboard();
	CPlayer *pPlayer = CGame::GetPlayer();

	m_vtxMax = CModel::GetvtxMax();
	m_vtxMin = CModel::GetvtxMin();

	m_size.x = m_vtxMax.x - m_vtxMin.x;
	m_size.y = m_vtxMax.y - m_vtxMin.y;
	m_size.z = m_vtxMax.z - m_vtxMin.z;

	if (   pPos->x - size.x / 2 < m_pos.x + m_vtxMax.x
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
			if (pInput->GetTrriger(DIK_RETURN) == true)
			{
				pPlayer->SetHitegg(true);
			}
			m_bOn = false;
		}
		//手前の当たり判定 
		if (
			pPosOld->z <= m_pos.z + m_vtxMin.z - size.z / 2.0f
			&& pPos->z > m_pos.z + m_vtxMin.z - size.z / 2.0f


			)
		{
			pPos->z = m_pos.z + m_vtxMin.z - size.z / 2.0f;
			if (pInput->GetTrriger(DIK_RETURN) == true)
			{
				pPlayer->SetHitegg(true);
				
			}
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
			pPos->x = m_pos.x + m_vtxMin.x - size.x / 2;
			if (pInput->GetTrriger(DIK_RETURN) == true)
			{
				pPlayer->SetHitegg(true);
			}
			m_bOn = false;
		}
		//右の当たり判定
		if (
			pPosOld->x >= m_pos.x + m_vtxMax.x + size.x / 2
			&& pPos->x < m_pos.x + m_vtxMax.x + size.x / 2

			)
		{
			pPos->x = m_pos.x + m_vtxMax.x + size.x / 2;
			if (pInput->GetTrriger(DIK_RETURN) == true)
			{
				pPlayer->SetHitegg(true);
			}
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
			pPos->y = m_pos.y + m_vtxMax.y + m_size.y / 2;
			m_bOn = true;
		}
		//下の当たり判定
		if (pPosOld->y + size.y / 2 <= m_pos.y + m_vtxMin.y
			&& pPos->y + size.y / 2 > m_pos.y + m_vtxMin.y
			)

		{
			pPos->y = m_pos.y + m_vtxMin.y - size.y;
			m_bOn = false;
		}
	}

}