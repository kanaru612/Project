//============================================================================
//
// Object.cpp
// Author : �����@�t��
//
//=============================================================================
#include"object.h"
#include"object2D.h"
#include"rendere.h" 
//�ÓI�����o�ϐ��錾
int CObject::m_nNumAll = 0;
CObject *CObject::m_pTop[PRIORITY_MAX] = {};
CObject *CObject::m_pCurrent[PRIORITY_MAX] = {};
//-------------------------------------------------------------------------
// �R���X�g���N�^
//-------------------------------------------------------------------------
CObject::CObject(int nPriority )
{
	m_pNext = nullptr;
	m_pPrev = nullptr;
	m_bDeth = false;
	//�v���C�I���e�B�̕ۑ�
	m_nPriority = nPriority;

	//�I�u�W�F�N�g(�������g)���A���X�g�ɒǉ�
	if (m_pTop[nPriority] == nullptr)
	{
		m_pTop[nPriority] = this;
	}
	else if (m_pTop[nPriority] != nullptr)
	{
		m_pCurrent[nPriority]->m_pNext = this;
		this->m_pPrev = m_pCurrent[nPriority];
	}

	m_pCurrent[nPriority] = this;
}

//-------------------------------------------------------------------------
// �f�X�g���N�^
//-------------------------------------------------------------------------
CObject::~CObject()
{

}
//-------------------------------------------------------------------------
// �j��
//-------------------------------------------------------------------------
void CObject::ReleaseAll(void)
{
	for (int nCnt = 0; nCnt < PRIORITY_MAX; nCnt++)
	{
		CObject *pObj = m_pTop[nCnt];

		while (pObj)
		{
			CObject *pObjNext = pObj->m_pNext;

			pObj->Release();
			pObj = pObjNext;
		}
		pObj = m_pTop[nCnt];
		while (pObj != nullptr)
		{
		
			CObject *pObjNext = pObj->m_pNext;

			if (pObj->m_bDeth == true)
			{
				pObj->Death();
			}
			
			pObj = pObjNext;
		}
	}
}
//-------------------------------------------------------------------------
// �X�V
//-------------------------------------------------------------------------
void CObject::UpdataAll(void)
{
	bool isPause = false;

	for (int nCnt = 0; nCnt < PRIORITY_MAX; nCnt++)
	{
		CObject *pObj = m_pTop[nCnt];

		while (pObj != nullptr)
		{
			//pNext�̕ۑ�
			CObject *pObjectNext = pObj->m_pNext;

			if (pObj->m_bDeth == false)
			{
				if (pObj->GetObjType() == OBJTYPE_PAUSE)
				{
					isPause = true;
				}

				if (isPause)
				{
					if (pObj->m_canPoseUpdate)
					{
						pObj->Update();
					}
				}
				else
				{
					pObj->Update();
				}
			}

			//pObject��pObject��pNext����
			pObj = pObjectNext;
		}

		pObj = m_pTop[nCnt];

		while (pObj != nullptr)
		{
			//pNext�̕ۑ�
			CObject *pObjectNext = pObj->m_pNext;

			if (pObj->m_bDeth == true)
			{
				pObj->Death();
			}
			//pObject��pObject��pNext����
			pObj = pObjectNext;
		}
	}
}

//-------------------------------------------------------------------------
// �`��
//-------------------------------------------------------------------------
void CObject::DrawAll(void)
{
	for (int nPriority = 0; nPriority < PRIORITY_MAX; nPriority++)
	{
		CObject *pObject = m_pTop[nPriority];

		while (pObject != nullptr)
		{
			//pNext�̕ۑ�
			CObject *pObjectNext = pObject->m_pNext;	//Update()�ō폜�����ƁApNext��������̂Ŏ��O�ɕۑ����Ă���

			if (pObject->m_bDeth == false)
			{
				//�`�揈���̊֐��Ăяo��
				pObject->Draw();
			}

			//pObject��pObject��pNext����
			pObject = pObjectNext;
		}
	}
	
}
//-------------------------------------------------------------------------
// �����[�X
//-------------------------------------------------------------------------
void CObject::Release(void)
{
	m_bDeth = true;
}
//-------------------------------------------------------------------------
// �����[�X
//-------------------------------------------------------------------------
void CObject::SetType(ObjeType nType)
{
	m_nType = nType;
}
void CObject::ModeRelease(void)
{
	for (int nPriority = 0; nPriority < PRIORITY_MAX; nPriority++)
	{
		{
			CObject *pObject = m_pTop[nPriority];

			while (pObject != nullptr)
			{
				//pNext�̕ۑ�
				CObject *pObjectNext = pObject->m_pNext;

				if (pObject->GetObjType() != OBJTYPE_MODE)
				{
					//�I�������̊֐��Ăяo��
					pObject->Release();
				}

				//pObject��pObject��pNext����
				pObject = pObjectNext;
			}
		}
		{
			CObject *pObject = m_pTop[nPriority];

			while (pObject != nullptr)
			{
				//pNext�̕ۑ�
				CObject *pObjectNext = pObject->m_pNext;

				if (pObject->GetObjType() != OBJTYPE_MODE)
				{
					pObject->Death();
				}

				//pObject��pObject��pNext����
				pObject = pObjectNext;
			}
		}
	}
}
//-------------------------------------------------------------------------
// �I�u�W�F�N�g�j������
//-------------------------------------------------------------------------
void CObject::Death(void)
{
	//�I�u�W�F�N�g�̎��ɏ�񂪓����Ă���Ƃ�
	if (m_pNext != nullptr)
	{
		//�I�u�W�F�N�g�̑O�ɏ�񂪓����Ă���Ƃ�
		if (m_pPrev != nullptr)
		{
			//�������g��m_pNext��O�̃I�u�W�F�N�g��m_pNext�ɑ��
			m_pPrev->m_pNext = this->m_pNext;

			//�������g��m_pPrev������m_pPrev�ɑ��
			m_pNext->m_pPrev = this->m_pPrev;
		}

		//�I�u�W�F�N�g�̑O�ɏ�񂪓����Ă��Ȃ��Ƃ�
		else
		{
			//�������g��m_pNext��擪�ɑ��
			m_pTop[m_nPriority] = this->m_pNext;

			//�������g��m_pPrev�����̃I�u�W�F�N�g��m_pPrev�ɑ��
			m_pNext->m_pPrev = this->m_pPrev;
		}
	}

	//�I�u�W�F�N�g�̎��ɏ�񂪓����Ă��Ȃ��Ƃ�
	else
	{
		//�I�u�W�F�N�g�̑O�ɏ�񂪓����Ă���Ƃ�
		if (m_pPrev != nullptr)
		{
			//����m_pPrev��nullptr����
			m_pCurrent[m_nPriority] = this->m_pPrev;

			//����m_pNext��O�̃I�u�W�F�N�g��m_pNext�ɑ��
			m_pPrev->m_pNext = this->m_pNext;
		}

		//�I�u�W�F�N�g�̑O�ɏ�񂪓����Ă��Ȃ��Ƃ�
		else
		{
			//�擪�̃I�u�W�F�N�g��nullptr����
			m_pTop[m_nPriority] = nullptr;

			//���̃I�u�W�F�N�g��nullptr����
			m_pCurrent[m_nPriority] = nullptr;
		}
	}

	//�I�u�W�F�N�g(�������g)���A�j��
	this->Uninit();		// �I������
	delete this;
}