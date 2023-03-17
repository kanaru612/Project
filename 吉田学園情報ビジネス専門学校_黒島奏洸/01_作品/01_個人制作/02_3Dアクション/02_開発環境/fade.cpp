//============================================================================
//
// fade.cpp
// Author : 黒島　奏洸
//
//=============================================================================
#include"fade.h"
#include"application.h"
#include"rendere.h"

CFade::FADE CFade::m_fade = {};
CApplication::MODE CFade::m_modeNext = {};
D3DXCOLOR CFade::m_color = { 0.0f, 0.0f, 0.0f, 1.0f };

CFade::CFade() : CObject2D(PRIORITY_FADE)
{
	SetType(OBJTYPE_MODE);
}

CFade::~CFade()
{
}
//-------------------------------------------------------------------------
// フェイドの初期化
//-------------------------------------------------------------------------
HRESULT CFade::Init(CApplication::MODE modeNext)
{
	CObject2D::Init();
	
	m_fade = FADE_IN;												//フェードイン状態に
	m_color = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);					//黒いフェイド(不透明)にしておく
	m_modeNext = modeNext;											//次の画面(モード)を設定

	CObject2D::Create(D3DXVECTOR3(640.0f, 360.0f, 0.0f));
	setsize(D3DXVECTOR3(1280.0f, 720.0f, 0.0f));
	setpos(D3DXVECTOR3(640.0f, 360.0f, 0.0f));
	CApplication::SetMode(m_modeNext);
	return S_OK;
}
//-------------------------------------------------------------------------
// フェイドの終了
//-------------------------------------------------------------------------
void CFade::Uninit()
{
	CObject2D::Release();
}

//-------------------------------------------------------------------------
// フェイドの更新
//-------------------------------------------------------------------------
void CFade::Update()
{
	CObject2D::Update();
	if (m_fade != FADE_NONE)
	{
		if (m_fade == FADE_IN)
		{
			//フェードイン状態
			m_color.a -= 0.027f;

			if (m_color.a <= 0.0f)
			{
				m_color.a = 0.0f;
				m_fade = FADE_NONE;
			}
		}
			
		else if (m_fade == FADE_OUT)
		{
			m_color.a += 0.027f;
			//フェードアウト状態
			if (m_color.a >= 1.0f)
			{
				m_color.a = 1.0f;

				m_fade = FADE_IN;
				//モードの設定
				CApplication::SetMode(m_modeNext);
			}
		}
		CObject2D::setcolor(m_color.r, m_color.g, m_color.b, m_color.a);
	}
}
//-------------------------------------------------------------------------
// フェイドの設定
//-------------------------------------------------------------------------
void CFade::Set(CApplication::MODE modeNext)
{
	m_fade = FADE_OUT;

	m_modeNext = modeNext;

	m_color = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
}
//-------------------------------------------------------------------------
// フェイドの生成
//-------------------------------------------------------------------------
CFade *CFade::Create(CApplication::MODE modeNext)
{
	CFade *pFade = nullptr;

	//動的生成
	pFade = new CFade;
	if (pFade != nullptr)
	{
		pFade->Init(modeNext);
	}
	return pFade;
}