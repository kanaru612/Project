//=============================================================================
//
// Keyset.h
// Author : �����@�t��
//
//============================================================================
#include <assert.h>
#include <stdio.h>
#include "keyset.h"
#include "application.h"
#include "rendere.h"
#include "key.h"
CKeyset::CKeyset()
{
	m_Frame = 0;					
	m_pKey[MAX_MODEL] = {};		
}
CKeyset::~CKeyset()
{
	
}
//-------------------------------------------------------------------------
// �L�[�Z�b�g�̏���������
//-------------------------------------------------------------------------=

HRESULT CKeyset::Init(void)
{
	m_Frame = 0;	

	for (int nCnt = 0; nCnt < MAX_MODEL; nCnt++)
	{
		m_pKey[nCnt] = CKey::Create();
	}

	return S_OK;
}
//-------------------------------------------------------------------------
// �L�[�Z�b�g�̏I������
//-------------------------------------------------------------------------=
void CKeyset::Uninit()
{

	for (int nCnt = 0; nCnt < MAX_MODEL; nCnt++)
	{
		if (m_pKey[nCnt] != nullptr)
		{
			m_pKey[nCnt]->Uninit();
			delete m_pKey[nCnt];
			m_pKey[nCnt] = nullptr;
		}
	}
}
//-------------------------------------------------------------------------
// �L�[�Z�b�g�̐���
//-------------------------------------------------------------------------=
CKeyset * CKeyset::Create()
{
	CKeyset *pKeySet = nullptr;

	pKeySet = new CKeyset;				

	if (pKeySet != nullptr)
	{
		// ����������
		pKeySet->Init();
	}
	return pKeySet;
}