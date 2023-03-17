//=============================================================================
//
// game.h
// Author : 
//
//=============================================================================
#ifndef _GAME_H_
#define _GAME_H_
#include"main.h"
#include"application.h"
class CMode;
class CGame : public CMode
{
public:
	CGame();
	~CGame()override;
	HRESULT Init(void)override;
	void Uninit(void) override;
	void Update(void) override;


	static CGame *Create();
	static HRESULT Load(void);
	static void Unload(void);
	static CScore *GetScore(void) { return m_nScor; };

private:
	static LPDIRECT3DTEXTURE9 m_ptex;
	float m_fWidth;
	float m_fHeight;
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;
	static CScore *m_nScor;
	D3DXVECTOR3 m_pos;
};
#endif


