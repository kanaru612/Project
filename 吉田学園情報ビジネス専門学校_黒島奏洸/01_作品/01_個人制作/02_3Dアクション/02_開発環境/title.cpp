//============================================================================
//
// Title.cpp
// Author : 黒島　奏洸
//
//=============================================================================
#include"title.h"
#include"Input.h"
#include"application.h"
#include"rendere.h"
#include"object2D.h"
#include"fade.h"
#include"object2D.h"
#include"sound.h"

CTitle::CTitle() 
{
	m_bf = false;
	m_sound = false;
}
CTitle::~CTitle()
{

}
//-------------------------------------------------------------------------
// タイトルの初期化
//-------------------------------------------------------------------------
HRESULT CTitle::Init()
{
	m_bf = false;
	m_sound = false;
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRendere()->GetDevice();    //デバイスへのポイント		

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data/texture/title.png",
		&m_ptex);

	m_pObject = CObject2D::Create({ 640.0f,360.0f,0.0f });
	m_pObject->setsize({ 640.0f,360.0f,0.0f });

	m_pObject->BindTexture(m_ptex);

	return S_OK;
}
//-------------------------------------------------------------------------
// タイトルの終了
//-------------------------------------------------------------------------
void CTitle::Uninit()
{
	StopSound();
	CObject::Release();
}

//-------------------------------------------------------------------------
// タイトルの更新
//-------------------------------------------------------------------------
void CTitle::Update()
{
	if (m_sound == false)
	{
		PlaySound(SOUND_LABEL_BGM001);
		m_sound = true;
	}
	CInput *pInput = CApplication::GetKeyboard();
	//エンターキーで次の画面に

	if (pInput->GetTrriger(DIK_RETURN) == true && m_bf == false)
	{
		CFade::Set(CApplication::MODE_TUTRIAL);
		m_bf = true;
	}
}

//-------------------------------------------------------------------------
// タイトルの生成
//-------------------------------------------------------------------------
CTitle *CTitle::Create()
{
	CTitle *ptitle = nullptr;

	//動的生成
	ptitle = new CTitle;

	ptitle->Init();
	
	return ptitle;
}

