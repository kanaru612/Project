//============================================================================
//
// Result.h
// Author : çïìáÅ@ëtü©
//
//=============================================================================
#ifndef _RESULT_H_
#define _RESULT_H_
#include"main.h"
#include"mode.h"
#include"score.h"
class CMode;
class CResult : public CMode
{
public:
	CResult();
	~CResult()override;
	HRESULT Init(void)override;
	void Uninit(void) override;
	void Update(void) override;

	static CResult *Create();
	CNumber *m_pNum[MAX_SCORE];

private:
	static LPDIRECT3DTEXTURE9 m_ptex[2];
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;
	CObject2D *m_pObject;
	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_size;

	bool m_bfr;
	bool m_sound;
};
#endif


