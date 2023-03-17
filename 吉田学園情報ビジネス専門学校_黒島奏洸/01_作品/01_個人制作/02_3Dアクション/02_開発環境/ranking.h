//============================================================================
//
// Ranking.h
// Author : çïìáÅ@ëtü©
//
//=============================================================================
#ifndef _RANKING_H_
#define _RANKING_H_
#include"main.h"
#include"score.h"
#include"mode.h"
class CObject2D;
class CRanking : public CMode
{
public:
	CRanking();
	~CRanking()override;

	HRESULT Init(void)override;
	void Uninit(void) override;
	void Update(void) override;

	static CRanking *Create();

	void LoadRanking(void);
	void SaveRanking(void);
	static void SetRanking();
	static void SetRankingScore(int nScore);

private:
	static LPDIRECT3DTEXTURE9 m_ptex[2];
	CObject2D *m_pObject2D[2];
	static CNumber *m_pNumber[5][MAX_SCORE];
	static int m_nData[5];
	static int m_nRank;
	int m_nScore;
	bool m_fra;
	bool m_sound;
};
#endif

