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
// ������
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
// �I��
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
// �`��
//=============================================================================
void CApplication::Draw(void)
{
	m_pRendere->Draw();	
}
//=============================================================================
// �X�V
//=============================================================================
void CApplication::Update(void)
{
	m_pKey->Update();
	m_pMode->Update();
	m_pRendere->Update();
}
//=============================================================================
// �X�V
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
	//���݂̉�ʂ̏I������
	switch (m_mode)
	{
		//�^�C�g�����
	case CApplication::MODE_TITLE:
		m_pMode = CTitle::Create();
		break;
	case CApplication::MODE_TUTRIAL:
		m_pMode = CTutrial::Create();
		break;
		//�Q�[�����
	case CApplication::MODE_GAME:
		m_pMode = CGame::Create();
		break;
		//���U���g���
	case CApplication::MODE_RESULT:
		m_pMode = CResult::Create();
		break;
	case CApplication::MODE_RANKING:
		m_pMode = CRanking::Create();
		CRanking::SetRanking();
		break;
	}
	
}
