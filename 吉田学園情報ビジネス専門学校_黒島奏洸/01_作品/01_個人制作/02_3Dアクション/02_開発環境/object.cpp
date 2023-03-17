//============================================================================
//
// Object.cpp
// Author : 黒島　奏洸
//
//=============================================================================
#include"object.h"
#include"object2D.h"
#include"rendere.h" 
//静的メンバ変数宣言
int CObject::m_nNumAll = 0;
CObject *CObject::m_pTop[PRIORITY_MAX] = {};
CObject *CObject::m_pCurrent[PRIORITY_MAX] = {};
//-------------------------------------------------------------------------
// コンストラクタ
//-------------------------------------------------------------------------
CObject::CObject(int nPriority )
{
	m_pNext = nullptr;
	m_pPrev = nullptr;
	m_bDeth = false;
	//プライオリティの保存
	m_nPriority = nPriority;

	//オブジェクト(自分自身)を、リストに追加
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
// デストラクタ
//-------------------------------------------------------------------------
CObject::~CObject()
{

}
//-------------------------------------------------------------------------
// 破棄
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
// 更新
//-------------------------------------------------------------------------
void CObject::UpdataAll(void)
{
	bool isPause = false;

	for (int nCnt = 0; nCnt < PRIORITY_MAX; nCnt++)
	{
		CObject *pObj = m_pTop[nCnt];

		while (pObj != nullptr)
		{
			//pNextの保存
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

			//pObjectにpObjectのpNextを代入
			pObj = pObjectNext;
		}

		pObj = m_pTop[nCnt];

		while (pObj != nullptr)
		{
			//pNextの保存
			CObject *pObjectNext = pObj->m_pNext;

			if (pObj->m_bDeth == true)
			{
				pObj->Death();
			}
			//pObjectにpObjectのpNextを代入
			pObj = pObjectNext;
		}
	}
}

//-------------------------------------------------------------------------
// 描画
//-------------------------------------------------------------------------
void CObject::DrawAll(void)
{
	for (int nPriority = 0; nPriority < PRIORITY_MAX; nPriority++)
	{
		CObject *pObject = m_pTop[nPriority];

		while (pObject != nullptr)
		{
			//pNextの保存
			CObject *pObjectNext = pObject->m_pNext;	//Update()で削除されると、pNextも消えるので事前に保存しておく

			if (pObject->m_bDeth == false)
			{
				//描画処理の関数呼び出し
				pObject->Draw();
			}

			//pObjectにpObjectのpNextを代入
			pObject = pObjectNext;
		}
	}
	
}
//-------------------------------------------------------------------------
// リリース
//-------------------------------------------------------------------------
void CObject::Release(void)
{
	m_bDeth = true;
}
//-------------------------------------------------------------------------
// リリース
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
				//pNextの保存
				CObject *pObjectNext = pObject->m_pNext;

				if (pObject->GetObjType() != OBJTYPE_MODE)
				{
					//終了処理の関数呼び出し
					pObject->Release();
				}

				//pObjectにpObjectのpNextを代入
				pObject = pObjectNext;
			}
		}
		{
			CObject *pObject = m_pTop[nPriority];

			while (pObject != nullptr)
			{
				//pNextの保存
				CObject *pObjectNext = pObject->m_pNext;

				if (pObject->GetObjType() != OBJTYPE_MODE)
				{
					pObject->Death();
				}

				//pObjectにpObjectのpNextを代入
				pObject = pObjectNext;
			}
		}
	}
}
//-------------------------------------------------------------------------
// オブジェクト破棄処理
//-------------------------------------------------------------------------
void CObject::Death(void)
{
	//オブジェクトの次に情報が入っているとき
	if (m_pNext != nullptr)
	{
		//オブジェクトの前に情報が入っているとき
		if (m_pPrev != nullptr)
		{
			//自分自身のm_pNextを前のオブジェクトのm_pNextに代入
			m_pPrev->m_pNext = this->m_pNext;

			//自分自身のm_pPrevを後ろのm_pPrevに代入
			m_pNext->m_pPrev = this->m_pPrev;
		}

		//オブジェクトの前に情報が入っていないとき
		else
		{
			//自分自身のm_pNextを先頭に代入
			m_pTop[m_nPriority] = this->m_pNext;

			//自分自身のm_pPrevを次のオブジェクトのm_pPrevに代入
			m_pNext->m_pPrev = this->m_pPrev;
		}
	}

	//オブジェクトの次に情報が入っていないとき
	else
	{
		//オブジェクトの前に情報が入っているとき
		if (m_pPrev != nullptr)
		{
			//後ろのm_pPrevにnullptrを代入
			m_pCurrent[m_nPriority] = this->m_pPrev;

			//後ろのm_pNextを前のオブジェクトのm_pNextに代入
			m_pPrev->m_pNext = this->m_pNext;
		}

		//オブジェクトの前に情報が入っていないとき
		else
		{
			//先頭のオブジェクトにnullptrを代入
			m_pTop[m_nPriority] = nullptr;

			//後ろのオブジェクトにnullptrを代入
			m_pCurrent[m_nPriority] = nullptr;
		}
	}

	//オブジェクト(自分自身)を、破棄
	this->Uninit();		// 終了処理
	delete this;
}