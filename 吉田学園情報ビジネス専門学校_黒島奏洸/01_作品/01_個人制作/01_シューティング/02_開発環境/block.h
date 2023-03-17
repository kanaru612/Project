//=============================================================================
//
// enemy.h
// Author : 
//
//=============================================================================
#ifndef _BLOCK_H_
#define _BLOCK_H_
#include"main.h"
#include"object2D.h"
#define MAX_SIZEBLOCK	(40)
class CBullet;
class CBlock : public CObject2D
{
public:
	CBlock();
	~CBlock()override;
	HRESULT Init(void)override;
	void Uninit(void) override;
	void Update(void) override; 
	void Draw(void) override;
	static CBlock *Create(const D3DXVECTOR3 pos, float fWidth, float fHeight);
	static HRESULT Load(void);
	static void Unload(void);
private:
	D3DXVECTOR3 m_move;
	static CBullet *m_pBullet;
	static LPDIRECT3DTEXTURE9 m_ptex;
	float m_fWidth;
	float m_fHeight;
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;
};
#endif

