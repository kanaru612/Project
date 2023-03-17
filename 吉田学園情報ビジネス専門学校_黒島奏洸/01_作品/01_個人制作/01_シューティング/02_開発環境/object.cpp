//=============================================================================
//
// object.cpp
// Author : 
//
//=============================================================================
#include"object.h"
#include"object2D.h"
#include"rendere.h" 
//�ÓI�����o�ϐ��錾
CObject *CObject::m_pObject[5][MAX_OBJECT] = {};
int CObject::m_nNumAll = 0;
//=============================================================================
// �R���X�g���N�^
//=============================================================================
CObject::CObject(int nPriority )
{
	m_nPriority = nPriority;
	for (int nCnt = 0; nCnt < MAX_OBJECT; nCnt++)
	{
		if (m_pObject[nPriority][nCnt] == nullptr)
		{
			
			m_pObject[nPriority][nCnt] = this;
			m_nID = nCnt;
			m_nNumAll++;
			break;
		}
	}
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CObject::~CObject()
{
}
//=============================================================================
// �j��
//=============================================================================
void CObject::ReleaseAll(void)
{
	for (int nCntP = 0; nCntP < 5; nCntP++)
	{
		for (int nCnt = 0; nCnt < MAX_OBJECT; nCnt++)
		{
			if (m_pObject[nCntP][nCnt] != nullptr)
			{
				m_pObject[nCntP][nCnt]->Uninit();
				//
				delete m_pObject[nCntP][nCnt];
				m_pObject[nCntP][nCnt] = nullptr;
			}
		}
	}
}
//=============================================================================
// �X�V
//=============================================================================
void CObject::UpdataAll(void)
{
	for (int nCntP = 0; nCntP < 5; nCntP++)
	{
		for (int nCnt = 0; nCnt < MAX_OBJECT; nCnt++)
		{
			if (m_pObject[nCntP][nCnt] != nullptr)
			{
				m_pObject[nCntP][nCnt]->Update();
			}
		}
	}
}
//=============================================================================
// �`��
//=============================================================================
void CObject::DrawAll(void)
{
	for (int nCntP = 0; nCntP < 5; nCntP++)
	{
		for (int nCnt = 0; nCnt < MAX_OBJECT; nCnt++)
		{
			if (m_pObject[nCntP][nCnt] != nullptr)
			{
				m_pObject[nCntP][nCnt]->Draw();
			}
		}
	}
}
//=============================================================================
// �����[�X
//=============================================================================
void CObject::Release(void)
{
	if (m_pObject[m_nPriority][m_nID] != nullptr)
	{
		int nID = m_nID;
		int nPriority = m_nPriority;
		delete m_pObject[nPriority][m_nID];
		m_pObject[nPriority][nID] = nullptr;
	}
	m_nNumAll--;
}
//=============================================================================
// �����[�X
//=============================================================================
void CObject::SetType(ObjeType nType)
{
	m_nType = nType;
}
void CObject::ModeRelease(void)
{
	for (int nCntP = 0; nCntP < 5; nCntP++)
	{
		for (int nCnt = 0; nCnt < MAX_OBJECT; nCnt++)
		{
			if (m_pObject[nCntP][nCnt] != nullptr)
			{
				if (m_pObject[nCntP][nCnt]->GetObjType() != OBJTYPE_MODE)
				{
					m_pObject[nCntP][nCnt]->Uninit();
					//
				}
			}
		}
	}
}