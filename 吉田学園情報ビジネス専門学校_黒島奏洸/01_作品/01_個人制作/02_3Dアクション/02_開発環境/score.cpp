//============================================================================
//
// Score.cpp
// Author : 黒島　奏洸
//
//=============================================================================
#include "score.h"
#include "main.h"
#include"application.h"
#include"Input.h"
#include"rendere.h"
#include"ranking.h"
#include"stdio.h"
CScore::CScore() : CObject(4)
{

	for (int nCnt = 0; nCnt < MAX_SCORE; nCnt++)
	{
		m_pNum[nCnt] = nullptr;
	}
	m_nScore = 0;
}
CScore::~CScore()
{
}

//-------------------------------------------------------------------------
//スコアの初期化処理
//-------------------------------------------------------------------------
HRESULT CScore::Init(void)
{
	
	for (int nCnt = 0; nCnt < MAX_SCORE; nCnt++)
	{
		m_pNum[nCnt] = CNumber::Create(D3DXVECTOR3(60.0f *nCnt + 800.0f, 70.0f, 0.0f), D3DXVECTOR3(20.0f, 40.0f, 0.0f));
	}

	return S_OK;
}
//-------------------------------------------------------------------------
//スコアの設定処理
//-------------------------------------------------------------------------
void CScore::Set(int Score)
{
	int aPosTexU[8];		//各桁の数字を格納	
	m_nScore = Score;

	aPosTexU[0] = m_nScore % 100000000 / 10000000;
	aPosTexU[1] = m_nScore % 10000000 / 1000000;
	aPosTexU[2] = m_nScore % 1000000 / 100000;
	aPosTexU[3] = m_nScore % 100000 / 10000;
	aPosTexU[4] = m_nScore % 10000 / 1000;
	aPosTexU[5] = m_nScore % 1000 / 100;
	aPosTexU[6] = m_nScore % 100 / 10;
	aPosTexU[7] = m_nScore % 10 / 1;

	for (int nCnt = 0; nCnt < MAX_SCORE; nCnt++)
	{
		m_pNum[nCnt]->setTexture(0.0f + (float)aPosTexU[nCnt] / 10.0f, (float)aPosTexU[nCnt] / 10.0f + 1.0f / 10.0f, 0.0f, 1.0f);
	}
	CRanking::SetRankingScore(m_nScore);

}
//-------------------------------------------------------------------------
//スコアの加算処理
//-------------------------------------------------------------------------
void CScore::add(int nValue)
{
	m_nScore += nValue;
	//GetHighScore(g_nScore);
	Set(m_nScore);
}
//-------------------------------------------------------------------------
//スコアの終了処理
//-------------------------------------------------------------------------
void CScore::Uninit(void)
{
	for (int nCnt = 0; nCnt < MAX_SCORE; nCnt++)
	{
		if (m_pNum[nCnt] != nullptr)
		{
			m_pNum[nCnt]->Uninit();
		}
		m_pNum[nCnt] = nullptr;
	}
	CObject::Release();
}
//-------------------------------------------------------------------------
//スコアの更新処理
//-------------------------------------------------------------------------
void CScore::Update(void)
{
}
//-------------------------------------------------------------------------
//スコアの描画処理
//-------------------------------------------------------------------------
void CScore::Draw(void)
{
}
//=============================================================================
// ポリゴンの描画
//=============================================================================
CScore *CScore::Create(D3DXVECTOR3 pos)
{
	CScore *apbg = nullptr;

	//動的生成
	apbg = new CScore;
	apbg->Init();
	return apbg;
}