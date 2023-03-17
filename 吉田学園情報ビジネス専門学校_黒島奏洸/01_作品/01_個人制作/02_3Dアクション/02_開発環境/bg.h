//=============================================================================
//
// object.h
// Author : 
//
//=============================================================================
#ifndef _BG_H_
#define _BG_H_
#include"main.h"
#include"object2d.h"

class CBg : public CObject2D
{
public:
	CBg();
	~CBg()override;
	HRESULT Init(void)override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;
	static CBg *Create(D3DXVECTOR3 pos);
	static HRESULT Load(void);
	static void Unload(void);
	//static void ReleaseTail(void);
private:
	ObjeType m_nType;
	static LPDIRECT3DTEXTURE9 m_ptex;
	//static CBg *m_ptail[MAX_TAIL];
	CObject2D *m_pObj2D;
};
#endif

