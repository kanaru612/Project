//=============================================================================
//
// explosion.h
// Author : 
//
//=============================================================================
#ifndef _EXPLOSION_H_
#define _EXPLOSION_H_
#include"main.h"
#include"object2D.h"
class CExplosion : public CObject2D
{
public:
	CExplosion();
	~CExplosion();

	HRESULT Init(void)override;
	void Uninit(void)override;
	void Update(void)override;
	void Draw(void)override;
	static HRESULT Load();
	static void Unload();
	static CExplosion *Create(const D3DXVECTOR3 pos);
private:
	static LPDIRECT3DTEXTURE9 m_ptex;
	int m_nPattern;
	int nCntAnim;
};

#endif
