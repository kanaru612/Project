//============================================================================
//
// Key.cpp
// Author : 黒島　奏洸
//
//=============================================================================

#include <assert.h>
#include <stdio.h>
#include "key.h"
#include "application.h"
#include "rendere.h"

CKey::CKey()
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

CKey::~CKey()
{

}
//-------------------------------------------------------------------------
// キーの初期化
//-------------------------------------------------------------------------
HRESULT CKey::Init(void)
{

	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	return S_OK;
}
//-------------------------------------------------------------------------
// キーの終了
//-------------------------------------------------------------------------
void CKey::Uninit()
{

}

//-------------------------------------------------------------------------
// キーの生成
//-------------------------------------------------------------------------
CKey * CKey::Create()
{
	CKey *pKey = nullptr;	
	pKey = new CKey;				
	if (pKey != nullptr)
	{
		pKey->Init();
	}
	return pKey;
}