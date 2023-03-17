//============================================================================
//
// soil.h
// Author : 黒島　奏洸
//
//=============================================================================
#ifndef _SOIL_H_
#define _SOIL_H_
#include"model.h"
class CSoil : public CModel
{
public:
	explicit CSoil(int nPriority = 2);
	~CSoil()override;
	HRESULT Init(void)override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;
	static CSoil *Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot);
	void SetSoil(char * pFile);
	void setrot(const D3DXVECTOR3 rot) { m_rot = rot; };
	void Collision(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 size)override;
	bool OnCollision()override { return m_bOn; };
	void SetOnCollision(bool bOn)override { m_bOn = bOn; };

private:
	D3DXVECTOR3 m_rot;						//角度
	D3DXVECTOR3 m_pos;						//位置
	D3DXVECTOR3 m_posOld;						//位置
	D3DXVECTOR3 m_size;						//サイズ
	D3DXVECTOR3  m_vtxMin;					//最大値
	D3DXVECTOR3  m_vtxMax;					//最小値
	static LPDIRECT3DTEXTURE9 m_ptex;
	bool m_bOn;
	LPD3DXBUFFER m_pBuffMat;
	DWORD        m_nNumMat;
	LPD3DXMESH   m_pMesh;
	D3DXMATRIX   m_mtxWorld;
	bool bUse;
};

#endif

