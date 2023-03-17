//=============================================================================
//
// object.h
// Author : 
//
//=============================================================================
#ifndef _SCORE_H_
#define _SCORE_H_
#include"main.h"
#include"object.h"
#include"number.h"

#define MAX_SCORE	(8)		

class CScore : public CObject
{
public:
	CScore();
	~CScore()override;
	HRESULT Init(void)override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;
	void Set(int Score);
	void add(int nValue);
	static CScore *Create(D3DXVECTOR3 pos);
	/*static void LoadScore(void);
	static void SaveScore(void);*/
	void setpos(const D3DXVECTOR3 pos) override {};
	void setlife(int life) override {};
	D3DXVECTOR3 Getpos(void) override { return  D3DXVECTOR3(); };
	D3DXVECTOR3 Getsize(void) override { return D3DXVECTOR3();};
	int Gettype(void) override { return m_nLife; };
	int Getlife(void) override { return m_ntype; };
	D3DXVECTOR3 Getrot(void) override { return D3DXVECTOR3();
	};
	int GetScore(void) { return m_nScore ;};
private:
	ObjeType m_nType;
	static LPDIRECT3DTEXTURE9 m_ptex;
	int m_nScore;
	CNumber *m_pNum[MAX_SCORE];
	int m_nLife = 0;
	int m_ntype = 0; 
};

#endif