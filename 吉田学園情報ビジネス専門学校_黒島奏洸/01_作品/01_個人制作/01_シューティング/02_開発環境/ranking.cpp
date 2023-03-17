#include "ranking.h"
#include "main.h"
#include"application.h"
#include"Input.h"
#include"rendere.h"
#include"stdio.h"
#include"fade.h"
#include"sound.h"
LPDIRECT3DTEXTURE9 CRanking::m_ptex[2] = {};
CNumber *CRanking::m_pNumber[5][MAX_SCORE] = {};
int CRanking::m_nData[5] = {};
int CRanking::m_nRank = {};
CRanking::CRanking()
{
	m_fra = false;
}
CRanking::~CRanking()
{
}

//-------------------------------------------------------------------------
//スコアの初期化処理
//-------------------------------------------------------------------------
HRESULT CRanking::Init(void)
{
	m_fra = false;
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRendere()->GetDevice();    //デバイスへのポイント		
	PlaySound(SOUND_LABEL_BGM001);
	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data/texture/ranking2.png",
		&m_ptex[0]);

	D3DXCreateTextureFromFile(pDevice,
		"data/texture/number000.png",
		&m_ptex[1]);

	m_pObject2D[0] = CObject2D::Create({ 640.0f,360.0f,0.0f });
	m_pObject2D[0]->setsize({ 640.0f,360.0f,0.0f });
	m_pObject2D[0]->BindTexture(m_ptex[0]);

	for (int nCnt = 0; nCnt < 5; nCnt++)
	{
		for (int nScore = 0; nScore < MAX_SCORE; nScore++)
		{
			m_pNumber[nCnt][nScore] = CNumber::Create(D3DXVECTOR3(300.0f+ 100.0f *nScore ,200.0f + 100.0f * nCnt, 0.0f), D3DXVECTOR3(20.0f, 40.0f, 0.0f));
			m_pNumber[nCnt][nScore]->BindTexture(m_ptex[1]);
		}
	}
	CRanking::LoadRanking();

	return S_OK;

}
//-------------------------------------------------------------------------
//スコアの終了処理
//-------------------------------------------------------------------------
void CRanking::Uninit(void)
{
	StopSound();
	for (int nCnt = 0; nCnt < 5; nCnt++)
	{
		for (int nScore = 0; nScore < MAX_SCORE; nScore++)
		{
			if (m_pNumber[nCnt][nScore] != nullptr)
			{
				m_pNumber[nCnt][nScore]->Uninit();
			}
		}
	}
	CObject::Release();
}
//-------------------------------------------------------------------------
//スコアの更新処理
//-------------------------------------------------------------------------
void CRanking::Update(void)
{
	CInput *pInput = CApplication::GetKeyboard();
	//エンターキーで次の画面に

	if (pInput->GetTrriger(DIK_RETURN) == true && m_fra == false)
	{
		SaveRanking();
		CFade::Set(CApplication::MODE_TITLE);
		m_fra = true;
	}
}

//=============================================================================
// ポリゴンの描画
//=============================================================================
CRanking *CRanking::Create()
{
	CRanking *apbg = nullptr;

	//動的生成
	apbg = new CRanking;
	apbg->Init();
	return apbg;
}

void CRanking::LoadRanking(void)
{
	FILE *pFile;
	pFile = fopen("data/ranking/ranking.txt", " r");
	if (pFile != nullptr)
	{
		for (int nCnt = 0; nCnt < 5; nCnt++)
		{
			fscanf(pFile, "%d\n", &m_nData[nCnt]);
		}
		fclose(pFile);
	}
}
void CRanking::SaveRanking(void)
{
	FILE *pFile;
	pFile = fopen("data/ranking/ranking.txt", "w");
	if (pFile != nullptr)
	{
		for (int nCnt = 0; nCnt < 5; nCnt++)
		{
			fprintf(pFile, "%d\n", m_nData[nCnt]);
		}
		fclose(pFile);
	}
}
void CRanking::SetRanking()
{
	int aPosTexU[5][MAX_SCORE];		//各桁の数字を格納	
	
	if (m_nRank > m_nData[4])
	{
		m_nData[4] = m_nRank;
	}
	
	for (int nCnt = 0; nCnt < 4; nCnt++)
	{
		for (int nCnt2 = nCnt + 1; nCnt2 < 5; nCnt2++)
		{
			if (m_nData[nCnt] < m_nData[nCnt2])
			{
				int nData = m_nData[nCnt];
				m_nData[nCnt] = m_nData[nCnt2];
				m_nData[nCnt2] = nData;
			}
		}
	}
	for (int nCnt = 0; nCnt < 5; nCnt++)
	{
		aPosTexU[nCnt][0] = m_nData[nCnt] % 100000000 / 10000000;
		aPosTexU[nCnt][1] = m_nData[nCnt] % 10000000 / 1000000;
		aPosTexU[nCnt][2] = m_nData[nCnt] % 1000000 / 100000;
		aPosTexU[nCnt][3] = m_nData[nCnt] % 100000 / 10000;
		aPosTexU[nCnt][4] = m_nData[nCnt] % 10000 / 1000;
		aPosTexU[nCnt][5] = m_nData[nCnt] % 1000 / 100;
		aPosTexU[nCnt][6] = m_nData[nCnt] % 100 / 10;
		aPosTexU[nCnt][7] = m_nData[nCnt] % 10 / 1;
	}

	for (int nCnt = 0; nCnt < 5; nCnt++)
	{
		for (int nScore = 0; nScore < MAX_SCORE; nScore++)
		{
			m_pNumber[nCnt][nScore]->setTexture(0.0f + (float)aPosTexU[nCnt][nScore] / 10.0f, (float)aPosTexU[nCnt][nScore] / 10.0f + 1.0f / 10.0f, 0.0f, 1.0f);
		}
	}
}
void CRanking::SetRankingScore(int nScore)
{
	m_nRank = nScore;
}