//============================================================================
//
// Strongbox.cpp
// Author : �����@�t��
//
//=============================================================================
#ifndef _STORONGBOX_H_
#define _STORONGBOX_H_
#include"model.h"

class CCoin;
class CStrongbox : public CModel
{
public:
	explicit CStrongbox(int nPriority = 2);
	~CStrongbox()override;
	HRESULT Init(void)override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;
	static CStrongbox *Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot);
	void SetStrongbox(char * pFile);
	void setrot(const D3DXVECTOR3 rot) { m_rot = rot; };
	void Collision(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 size)override;
	bool OnCollision()override { return m_bOn; };
	void SetOnCollision(bool bOn)override { m_bOn = bOn; };


	bool GetCoinCreateFlag(void) { return m_CoinCreateFlag; }
	void SetCoinCreateFlag(bool flag) { m_CoinCreateFlag = flag; }

	static CCoin *GetCoin() { return m_pCoin; }

private:
	D3DXVECTOR3 m_move;						//�ړ���
	D3DXVECTOR3 m_rot;						//�p�x
	D3DXVECTOR3 m_pos;						//�ʒu
	D3DXVECTOR3 m_size;						//�T�C�Y
	D3DXVECTOR3  m_vtxMin;					//�ő�l
	D3DXVECTOR3  m_vtxMax;					//�ŏ��l
	bool bOpen;
	static LPDIRECT3DTEXTURE9 m_ptex;
	int m_nCnt;
	int m_nLife;
	int m_nType;
	bool bUse;
	LPD3DXBUFFER m_pBuffMat;
	DWORD        m_nNumMat;
	LPD3DXMESH   m_pMesh;
	D3DXMATRIX   m_mtxWorld;
	bool m_bOn;

	bool m_CoinCreateFlag;
	static CCoin *m_pCoin;
};

#endif

