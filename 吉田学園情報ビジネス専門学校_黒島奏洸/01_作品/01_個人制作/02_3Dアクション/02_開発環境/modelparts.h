//============================================================================
//
// Modelparts.h
// Author : 黒島　奏洸
//
//=============================================================================
#pragma once

#ifndef _MODELPARTS_H_
#define _MODELPARTS_H_
#include "main.h"

class CModelparts
{
public:
	CModelparts();
	~CModelparts();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	D3DXMATRIX *GetMatrix(void) { return &m_mtxWorld; };
	D3DXVECTOR3 GetRot(void) { return m_rot; };
	D3DXVECTOR3 GetPos(void) { return m_pos; };
	int GetParent(void) { return nIdxmParent; };
	D3DXVECTOR3 GetVtxMax(void) { return m_vtxMax; };
	D3DXVECTOR3 GetVtxMin(void) { return m_vtxMin; };

	void SetMatrix(D3DXMATRIX *matrixparent) { m_mtxParent = matrixparent; };
	void SetParent(int parent) { nIdxmParent = parent; };
	void SetPos(D3DXVECTOR3 pos) { m_pos = pos; };
	void SetRot(D3DXVECTOR3 rot) { m_rot = rot; };
	void SetModel(char * pFile);

	static CModelparts *Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot);
private:
	int m_nNumvtx;							//頂点数
	DWORD m_sizeFVF;						//頂点フォーマットのサイズ
	BYTE *m_pVtxBuf;						//頂点バッファへのポインタ
	D3DXVECTOR3  m_vtxMin;					//最大値
	D3DXVECTOR3  m_vtxMax;					//最小値
	D3DXVECTOR3  m_rot;						//向き						
	D3DXVECTOR3 m_pos;						//位置
	//親のワールドマトリックス		
	D3DXMATRIX *m_mtxParent;
	//ワールドマトリックス	
	D3DXMATRIX m_mtxWorld;
	float m_fDistance;
	int nIdxmParent;
	LPD3DXBUFFER m_pBuffMat;
	DWORD        m_nNumMat;
	LPD3DXMESH   m_pMesh;
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;

};

#endif
