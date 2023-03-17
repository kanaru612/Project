//=============================================================================
//
// object.h
// Author : 
//
//=============================================================================
#ifndef _NUMBER_H_
#define _NUMBER_H_
#include "object2D.h"
class CNumber : public CObject2D
{
public:
	CNumber();	//コンストラクタ
	~CNumber();	//デストラクタ

	HRESULT Init() override;	//初期化処理
	void Uninit(void) override; //
	void Update(void) override; //
	void Draw(void) override;   //
	static CNumber *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);	

	static HRESULT Load();		
	static void Unload();		

private:
	static LPDIRECT3DTEXTURE9	m_ptex;		
};
#endif

