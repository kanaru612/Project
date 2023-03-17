//============================================================================
//
// Title.cpp
// Author : çïìáÅ@ëtü©
//
//=============================================================================
#ifndef _TITLE_H_
#define _TITLE_H_
#include"main.h"
#include"mode.h"
class CMode;
class CFade;
class CTitle : public CMode
{
public:
	CTitle();
	~CTitle()override;
	HRESULT Init(void)override;
	void Uninit(void)override;
	void Update(void) override;
	void Draw(void)override {};		
	static CTitle *Create();
private:
	LPDIRECT3DTEXTURE9 m_ptex;
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;
	CObject2D *m_pObject;
	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_size;
	CFade *m_pFade;
	bool m_bf;
	bool m_sound;
};
#endif


