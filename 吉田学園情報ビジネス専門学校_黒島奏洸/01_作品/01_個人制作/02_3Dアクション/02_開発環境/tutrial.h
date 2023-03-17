//============================================================================
//
// Tutrial.h
// Author : çïìáÅ@ëtü©
//
//=============================================================================
#ifndef _TUTRIAL_H_
#define _TUTRIAL_H_
#include"main.h"
#include"mode.h"
class CMode;
class CFade;
class CTutrial : public CMode
{
public:
	CTutrial();
	~CTutrial()override;
	HRESULT Init(void)override;
	void Uninit(void) override;
	void Update(void) override;

	static CTutrial *Create(); 
  
private:
	static LPDIRECT3DTEXTURE9 m_ptex;
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;
	CObject2D *m_pObject;
	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_size;
	CFade *m_pFade;
	bool m_bf;
	bool m_sound;
};
#endif



