//=============================================================================
//
// enemy.h
// Author : 
//
//=============================================================================
#ifndef _ENEMY_H_
#define _ENEMY_H_
#include"main.h"
#include"object2D.h"
#define MAX_SIZEH	(300)
#define MAX_SIZEW	(150)
class CBullet;
class CScore;
class CEnemy : public CObject2D
{
public:
	CEnemy();
	~CEnemy()override;
	HRESULT Init(void)override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;
	static CEnemy *Create(const D3DXVECTOR3 pos,int nLife);
	static HRESULT Load(void);
	static void Unload(void);
	void setlife(int life)override;
	static int Getlife(void) { return m_nLife; };
private:
	D3DXVECTOR3 m_move;
	static CBullet *m_pBullet;
	static LPDIRECT3DTEXTURE9 m_ptex;
	CScore *m_pScore;
	int m_nCnt;
	static int m_nLife; 
};
#endif
