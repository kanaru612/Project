//============================================================================
//
// fade.cpp
// Author : �����@�t��
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
// �t�F�C�h�̏�����
//-------------------------------------------------------------------------
HRESULT CFade::Init(CApplication::MODE modeNext)
{
	CObject2D::Init();
	
	m_fade = FADE_IN;												//�t�F�[�h�C����Ԃ�
	m_color = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);					//�����t�F�C�h(�s����)�ɂ��Ă���
	m_modeNext = modeNext;											//���̉��(���[�h)��ݒ�

	CObject2D::Create(D3DXVECTOR3(640.0f, 360.0f, 0.0f));
	setsize(D3DXVECTOR3(1280.0f, 720.0f, 0.0f));
	setpos(D3DXVECTOR3(640.0f, 360.0f, 0.0f));
	CApplication::SetMode(m_modeNext);
	return S_OK;
}
//-------------------------------------------------------------------------
// �t�F�C�h�̏I��
//-------------------------------------------------------------------------
void CFade::Uninit()
{
	CObject2D::Release();
}

//-------------------------------------------------------------------------
// �t�F�C�h�̍X�V
//-------------------------------------------------------------------------
void CFade::Update()
{
	CObject2D::Update();
	if (m_fade != FADE_NONE)
	{
		if (m_fade == FADE_IN)
		{
			//�t�F�[�h�C�����
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
			//�t�F�[�h�A�E�g���
			if (m_color.a >= 1.0f)
			{
				m_color.a = 1.0f;

				m_fade = FADE_IN;
				//���[�h�̐ݒ�
				CApplication::SetMode(m_modeNext);
			}
		}
		CObject2D::setcolor(m_color.r, m_color.g, m_color.b, m_color.a);
	}
}
//-------------------------------------------------------------------------
// �t�F�C�h�̐ݒ�
//-------------------------------------------------------------------------
void CFade::Set(CApplication::MODE modeNext)
{
	m_fade = FADE_OUT;

	m_modeNext = modeNext;

	m_color = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
}
//-------------------------------------------------------------------------
// �t�F�C�h�̐���
//-------------------------------------------------------------------------
CFade *CFade::Create(CApplication::MODE modeNext)
{
	CFade *pFade = nullptr;

	//���I����
	pFade = new CFade;
	if (pFade != nullptr)
	{
		pFade->Init(modeNext);
	}
	return pFade;
}