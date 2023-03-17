//=============================================================================
//
// Tutrial.cpp
// Author : 
//
//=============================================================================]
#include"tutrial.h"
#include"Input.h"
#include"application.h"
#include"explosion.h"
#include"rendere.h"
#include"object2D.h"
#include"fade.h"
#include"object2D.h"
#include"sound.h"
LPDIRECT3DTEXTURE9 CTutrial::m_ptex = {};
CTutrial::CTutrial()
{
	m_bf = false;
	m_sound = false;
}
CTutrial::~CTutrial()
{

}
//=============================================================================
// ポリゴンの初期化
//=============================================================================
HRESULT CTutrial::Init()
{
	m_bf = false;
	m_sound = false;
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRendere()->GetDevice();    //デバイスへのポイント		

																			//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data/texture/tutrial.png",
		&m_ptex);

	m_pObject = CObject2D::Create({ 640.0f,360.0f,0.0f });
	m_pObject->setsize({ 640.0f,360.0f,0.0f });

	m_pObject->BindTexture(m_ptex);

	return S_OK;
}
//=============================================================================
// ポリゴンの終了
//=============================================================================
void CTutrial::Uninit()
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
void CTutrial::Update()
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
		CFade::Set(CApplication::MODE_GAME);
		m_bf = true;
	}
}

//=============================================================================
// クリエイト
//=============================================================================
CTutrial *CTutrial::Create()
{
	CTutrial *pTutrial = nullptr;

	//動的生成
	pTutrial = new CTutrial;

	pTutrial->Init();

	return pTutrial;
}
