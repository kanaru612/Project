//=============================================================================
//
// title.cpp
// Author : 
//
//=============================================================================]
#include"title.h"
#include"Input.h"
#include"application.h"
#include"explosion.h"
#include"rendere.h"
#include"object2D.h"
#include"fade.h"
#include"object2D.h"
#include"sound.h"
LPDIRECT3DTEXTURE9 CTitle::m_ptex = {};
CTitle::CTitle() 
{
	m_bf = false;
	m_sound = false;
}
CTitle::~CTitle()
{

}
//=============================================================================
// ポリゴンの初期化
//=============================================================================
HRESULT CTitle::Init()
{
	m_bf = false;
	m_sound = false;
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRendere()->GetDevice();    //デバイスへのポイント		

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data/texture/title.jpg",
		&m_ptex);

	m_pObject = CObject2D::Create({ 640.0f,360.0f,0.0f });
	m_pObject->setsize({ 640.0f,360.0f,0.0f });

	m_pObject->BindTexture(m_ptex);

	return S_OK;
}
//=============================================================================
// ポリゴンの終了
//=============================================================================
void CTitle::Uninit()
{
	StopSound();
	if (m_pObject != nullptr)
	{
		m_pObject->Uninit();
		m_pObject = nullptr;
	}
	//テクスチャの破棄
	if (m_ptex != NULL)
	{
		m_ptex->Release();
		m_ptex = NULL;
	}
}

//=============================================================================
// ポリゴンの更新
//=============================================================================
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

//=============================================================================
// クリエイト
//=============================================================================
CTitle *CTitle::Create()
{
	CTitle *ptitle = nullptr;

	//動的生成
	ptitle = new CTitle;

	ptitle->Init();
	
	return ptitle;
}
