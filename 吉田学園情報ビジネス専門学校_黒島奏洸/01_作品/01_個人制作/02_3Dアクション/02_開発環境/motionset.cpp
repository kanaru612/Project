//=============================================================================
//
// Motionset.h
// Author : �����@�t��
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
// ���[�V�����̏���������
//-------------------------------------------------------------------------
HRESULT CMotionset::Init(void)
{

	m_Loop = 0;								
	m_Num_Key = 0;							
	m_NumParts = 0;							

	for (int nCnt = 0; nCnt < KEY_NUMBER; nCnt++)
	{
		//�L�[�ݒ�̐���
		m_apKeySet[nCnt] = CKeyset::Create();
	}

	return S_OK;
}

//-------------------------------------------------------------------------
// ���[�V�����̏I������
//-------------------------------------------------------------------------
void CMotionset::Uninit()
{
	//�L�[�̏I������
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
// ���[�V�����̐���
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