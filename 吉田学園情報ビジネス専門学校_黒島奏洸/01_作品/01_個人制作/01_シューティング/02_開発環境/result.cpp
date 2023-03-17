//=============================================================================
//
// block.cpp
// Author : 
//
//=============================================================================]
#include"result.h"
#include"Input.h"
#include"application.h"
#include"explosion.h"
#include"rendere.h"
#include"fade.h"
#include"score.h"
#include"sound.h"
LPDIRECT3DTEXTURE9 CResult::m_ptex[2] = {};
CResult::CResult()
{
	m_bfr = false;
}
CResult::~CResult()
{

}
//=============================================================================
// ポリゴンの初期化
//=============================================================================
HRESULT CResult::Init()
{

	m_bfr = false;
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRendere()->GetDevice();    //デバイスへのポイント		
	PlaySound(SOUND_LABEL_BGM002);
	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data/texture/result.jpg",
		&m_ptex[0]);
	

	m_pObject = CObject2D::Create({ 640.0f,360.0f,0.0f });
	m_pObject->setsize({ 640.0f,360.0f,0.0f });
	m_pObject->BindTexture(m_ptex[0]);

	return S_OK;
}
//=============================================================================
// ポリゴンの終了
//=============================================================================
void CResult::Uninit()
{
	StopSound();
	if (m_pObject != nullptr)
	{
		m_pObject->Uninit();
		m_pObject = nullptr;
	}
	//テクスチャの破棄
	for (int nCnt = 0; nCnt < 2; nCnt++)
	{

		if (m_ptex[nCnt] != NULL)
		{
			m_ptex[nCnt]->Release();
			m_ptex[nCnt] = NULL;
		}
	}
}

//=============================================================================
// ポリゴンの更新
//=============================================================================
void CResult::Update()
{
	CInput *pInput = CApplication::GetKeyboard();
	//エンターキーで次の画面に

	if (pInput->GetTrriger(DIK_RETURN) == true && m_bfr == false)
	{
		CFade::Set(CApplication::MODE_RANKING);
		m_bfr = true;
	}
}

//=============================================================================
// クリエイト
//=============================================================================
CResult *CResult::Create()
{
	CResult *presult = nullptr;

	//動的生成
	presult = new CResult;

	presult->Init();
	return presult;
}