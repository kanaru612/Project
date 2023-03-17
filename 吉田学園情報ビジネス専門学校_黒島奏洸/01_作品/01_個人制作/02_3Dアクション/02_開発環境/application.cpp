//============================================================================
//
// Application.cpp
// Author : 黒島　奏洸
//
//=============================================================================
#include"application.h"
#include"rendere.h"
#include"input.h"
#include"light.h"
#include"player.h"
#include"camera.h"
#include"object.h"
#include"object3D.h"
#include"object2D.h"
#include"meshfield.h"
#include"title.h"
#include"result.h"
#include"game.h"
#include"ranking.h"
#include"tutrial.h"
#include"fade.h"
#include"mode.h"
#include"enemy.h"
CRendere *CApplication::m_pRendere = {};
CInput *CApplication::m_pKey = {};
CApplication::MODE CApplication::m_mode = {};
CMode *CApplication::m_pMode = {};
CCamera *CApplication::m_pCamera = {};

CApplication::CApplication()
{
}

CApplication::~CApplication()
{
}
//-------------------------------------------------------------------------
// 初期化
//-------------------------------------------------------------------------
HRESULT CApplication::Init(HINSTANCE hInstance, HWND hWnd, bool bWindow)
{
	m_pRendere = new CRendere;
	m_pKey = new CInput;
	m_pCamera = new CCamera;

	m_pCamera->Init();
	m_pRendere->Init(hWnd, bWindow);
	m_pKey->Init(hInstance, hWnd);

	//CLight::Create();
	/*CPlayer::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), 5);
	CEnemy::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), 100);*/
	CFade::Create(MODE_TITLE);
	return S_OK;
}
//-------------------------------------------------------------------------
// 終了
//-------------------------------------------------------------------------
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
	if (m_pCamera != nullptr)
	{
		m_pCamera->Uninit();
		delete m_pCamera;
		m_pCamera = nullptr;
	}

	//CObject::ReleaseAll();	
}
//-------------------------------------------------------------------------
// 描画
//-------------------------------------------------------------------------
void CApplication::Draw(void)
{
	m_pRendere->Draw();
}
//-------------------------------------------------------------------------
// 更新
//-------------------------------------------------------------------------
void CApplication::Update(void)
{
	m_pKey->Update();
	m_pRendere->Update();
	m_pCamera->Update();
	m_pMode->Update();
}
//-------------------------------------------------------------------------
// 更新
//-------------------------------------------------------------------------
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
