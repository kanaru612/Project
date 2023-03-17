//============================================================================
//
// Gimmick.h
// Author : 黒島　奏洸
//
//=============================================================================
#ifndef _GIMMICK_H_
#define _GIMMICK_H_
#include "main.h"
#include"model.h"
class CGimmick : public CModel
{
public:
	explicit CGimmick(int nPriority = 2);
	~CGimmick();
	HRESULT Init(void);
	void Uninit(void) ;
	void Update(void) ;
	void Draw(void) ;
	static CGimmick *Create(const D3DXVECTOR3 pos);
	void SetGimmick(char * pFile);
	void setrot(const D3DXVECTOR3 rot) { m_rot = rot; };
	void Collision(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 size);
	D3DXVECTOR3 GetPos() { return m_pos; }
	D3DXVECTOR3 GetRot() { return m_rot; }
	bool OnCollision()override { return m_bOn; };
	void SetOnCollision(bool bOn)override { m_bOn = bOn; };
	void SetPos(D3DXVECTOR3 pos) { m_pos = pos; }
	void SetRot(D3DXVECTOR3 rot) { m_rot = rot; }
	void SetAttackCnt(int nCnt) { m_nCnt = nCnt; };

private:
	D3DXVECTOR3 m_rot;						//角度
	D3DXVECTOR3 m_pos;						//位置
	D3DXVECTOR3 m_size;						//サイズ
	D3DXVECTOR3  m_vtxMin;					//最大値
	D3DXVECTOR3  m_vtxMax;					//最小値
	bool m_bOn;
	static LPDIRECT3DTEXTURE9 m_ptex;
	int m_nCnt;
	int m_nLife;
	bool m_bUse;
	LPD3DXBUFFER m_pBuffMat;
	DWORD        m_nNumMat;
	LPD3DXMESH   m_pMesh;
	D3DXMATRIX   m_mtxWorld;
};

#endif
