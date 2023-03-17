//=============================================================================
//
// Motionset.h
// Author : 黒島　奏洸
//
//=============================================================================
#include <assert.h>
#include <stdio.h>
#include "motionset.h"
#include "application.h"
#include "rendere.h"
#include "keyset.h"

CMotionset::CMotionset()
{
	m_Loop = false;						
	m_Num_Key = 0;						
	m_NumParts = 0;						
	m_apKeySet[KEY_NUMBER] = {};		
}

CMotionset::~CMotionset()
{

}

//-------------------------------------------------------------------------
// モーションの初期化処理
//-------------------------------------------------------------------------
HRESULT CMotionset::Init(void)
{

	m_Loop = 0;								
	m_Num_Key = 0;							
	m_NumParts = 0;							

	for (int nCnt = 0; nCnt < KEY_NUMBER; nCnt++)
	{
		//キー設定の生成
		m_apKeySet[nCnt] = CKeyset::Create();
	}

	return S_OK;
}

//-------------------------------------------------------------------------
// モーションの終了処理
//-------------------------------------------------------------------------
void CMotionset::Uninit()
{
	//キーの終了処理
	for (int nCnt = 0; nCnt < KEY_NUMBER; nCnt++)
	{
		if (m_apKeySet[nCnt] != nullptr)
		{
			m_apKeySet[nCnt]->Uninit();
			delete m_apKeySet[nCnt];
			m_apKeySet[nCnt] = nullptr;
		}
	}
}

//-------------------------------------------------------------------------
// モーションの生成
//-------------------------------------------------------------------------
CMotionset * CMotionset::Create()
{
	CMotionset *pMotionset = nullptr;


	pMotionset = new CMotionset;
	if (pMotionset != nullptr)
	{
	
		pMotionset->Init();
	}
	return pMotionset;
}