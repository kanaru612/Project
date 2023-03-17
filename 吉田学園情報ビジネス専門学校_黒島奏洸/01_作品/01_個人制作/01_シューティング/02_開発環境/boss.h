//=============================================================================
//
// enemy.h
// Author : 
//
//=============================================================================
#ifndef _BOSS_H_
#define _BOSS_H_
#include"main.h"
#include"object2D.h"
class CBullet;
class CScore;
class CBoss : public CObject2D
{
public:
	CBoss();
	~CBoss()override;
	HRESULT Init(void)override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;
	static CBoss *Create(const D3DXVECTOR3 pos);
	static HRESULT Load(void);
	static void Unload(void);

private:
	D3DXVECTOR3 m_move;
	static CBullet *m_pBullet;
	static LPDIRECT3DTEXTURE9 m_ptex;
	CScore *m_pScore;
	int m_nCnt;
	int m_nLife;
};
#endif