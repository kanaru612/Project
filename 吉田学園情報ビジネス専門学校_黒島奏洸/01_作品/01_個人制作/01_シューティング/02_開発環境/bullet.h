//=============================================================================
//
// bullet.h
// Author : 
//
//=============================================================================
#ifndef _BULLET_H_
#define _BULLET_H_
#include"main.h"
#include"object2D.h"
#define MAX_SIZEB	(25.0f)
#define NUM_BULLET	(4)
class CEnemy;
class CPlayer;
class CBullet : public CObject2D
{
public:
	CBullet();
	~CBullet();
	HRESULT Init(void)override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;
	static CBullet *Create(const D3DXVECTOR3 pos, D3DXVECTOR3 move,int nType);
	static HRESULT Load(void);
	static void Unload(void);
	void settype(int type);
private:
	D3DXVECTOR3 m_move;
	static LPDIRECT3DTEXTURE9 m_pTex[NUM_BULLET];
	int m_nLife;
	int m_nType;
	CPlayer *m_pPlayer;
};
#endif
