//============================================================================
//
// Model.h
// Author : 黒島　奏洸
//
//=============================================================================
#pragma once

#ifndef _MODEL_H_
#define _MODEL_H_
#include "main.h"
#include"object.h"
class CModel : public CObject
{
public:
	explicit CModel(int nPriority = 2);
	~CModel()override;
	HRESULT Init(void)override;
	void Uninit(void)override;
	void Update(void)override;
	void Draw(void)override;

	void setpos(const D3DXVECTOR3 pos) override { m_pos = pos; };
	void setlife(int life) override { m_nLife = life; };

	D3DXVECTOR3 Getpos(void) override { return m_pos; };
	D3DXVECTOR3 Getsize(void) override { return m_size; };
	int Gettype(void) override { return m_nType; };
	int Getlife(void) override { return m_nLife; };
	D3DXVECTOR3 Getrot(void) override { return m_rot; };
	D3DXVECTOR3 GetvtxMax(void) { return m_vtxMax; };
	D3DXVECTOR3 GetvtxMin(void) { return m_vtxMin; }
	void Vtx(void);
	void SetModel(char * pFile);
	static CModel *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);
	virtual void Collision(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 size);
	virtual bool OnCollision() { return m_bOn; };
	virtual void SetOnCollision(bool bOn) { m_bOn = bOn; };
private:
	D3DXVECTOR3 m_rot;								//向き
	D3DXVECTOR3 m_pos;								//位置
	D3DXVECTOR3 m_size;								//サイズ
	D3DXVECTOR3 m_vtxMax;							//最大値
	D3DXVECTOR3 m_vtxMin;							//最小値
	D3DXMATRIX *m_mtxParent;						//親のワールドマトリックス	
	D3DXMATRIX m_mtxWorld;							//ワールドマトリックス	
	int m_nLife;									//体力
	int m_nType;									//種類
	bool m_bOn;
	LPD3DXBUFFER m_pBuffMat;
	DWORD        m_nNumMat;
	LPD3DXMESH   m_pMesh;
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;
};

#endif

