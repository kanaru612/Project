//=======;======================================================================
//
// application.cpp
// Author : 
//
//=============================================================================
#include"application.h"
#include"rendere.h"
#include"object.h"
#include"object2D.h"
#include"input.h"
#include"title.h"
#include"game.h"
#include"result.h"
#include"fade.h"
#include"ranking.h"
#include"tutrial.h"

CRendere *CApplication::m_pRendere = {};
CInput *CApplication::m_pKey = {};
CObject *g_pObject = nullptr;
CApplication::MODE CApplication::m_mode = {};
CMode *CApplication::m_pMode = {};

CApplication::CApplication()
{
}

CApplication::~CApplication()
{
}
CMode::CMode()	: CObject(3)
{
}

CMode::~CMode()
{
}
//=============================================================================
// 初期化
//=============================================================================
HRESULT CApplication::Init(HINSTANCE hInstance,HWND hWnd, bool bWindow)
{
	m_pRendere = new CRendere;
	m_pKey = new CInput;
	m_pRendere->Init(hWnd, bWindow);
	m_pKey->Init(hInstance, hWnd);
	CFade::Create(MODE_TITLE);
	return S_OK;
}
//=============================================================================
// 終了
//=============================================================================
void CApplication::Uninit(void)
{
	if (m_pRendere != nullptr)
	{
		m_pRendere->Uninit();
		delete m_pRendere;
		m_pRendere = nullptr;
	}
	if (m_pKey != nullptr)
	{
		m_pKey->Uninit();
		delete m_pKey;
		m_pKey = nullptr;
	}

	CObject2D::ReleaseAll();	
}
//=============================================================================
// 描画
//=============================================================================
void CApplication::Draw(void)
{
	m_pRendere->Draw();	
}
//=============================================================================
// 更新
//=============================================================================
void CApplication::Update(void)
{
	m_pKey->Update();
	m_pMode->Update();
	m_pRendere->Update();
}
//=============================================================================
// 更新
//=============================================================================
void CApplication::SetMode(MODE mode)
{
	if (m_pMode != nullptr)
	{
		m_pMode->Uninit();  
		m_pMode = nullptr;
	}
	CObject::ModeRelease();
	m_mode = mode;
	//現在の画面の終了処理
	switch (m_mode)
	{
		//タイトル画面
	case CApplication::MODE_TITLE:
		m_pMode = CTitle::Create();
		break;
	case CApplication::MODE_TUTRIAL:
		m_pMode = CTutrial::Create();
		break;
		//ゲーム画面
	case CApplication::MODE_GAME:
		m_pMode = CGame::Create();
		break;
		//リザルト画面
	case CApplication::MODE_RESULT:
		m_pMode = CResult::Create();
		break;
	case CApplication::MODE_RANKING:
		m_pMode = CRanking::Create();
		CRanking::SetRanking();
		break;
	}
	
}
