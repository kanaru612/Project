//=============================================================================
//
// object.h
// Author : 
//
//=============================================================================
#ifndef _TAIL_H_
#define _TAIL_H_
#include"main.h"
#include"object2D.h"
#define MAX_SIZET	(80)
#define MAX_TAIL	(56)
class CTail : public CObject2D
{
public:
	CTail();
	~CTail()override;
	HRESULT Init(void)override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;
	static CTail *Create(D3DXVECTOR3 pos);
	static HRESULT Load(void);
	static void Unload(void);
	//static void ReleaseTail(void);
private:
	ObjeType m_nType;
	static LPDIRECT3DTEXTURE9 m_ptex;
	//static CTail *m_ptail[MAX_TAIL];
	
};
#endif

